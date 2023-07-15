#include "gui_impl.h"
#include "log.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_dx12.h"
#include "font.h"
#include "../plugin/Menu.h"
#include "../plugin/Settings.h"
#include "notifications.h"
#include "../helper/eKeyboardMan.h"
#include "dx12hook.h"
#include "../helper/eGamepadManager.h"

bool  GUIImplementation::ms_bInit;
bool  GUIImplementation::ms_bFailed;
bool  GUIImplementation::ms_bShouldReloadFonts;;
bool  GUIImplementation::ms_bShouldRefreshRenderTarget;
HWND  GUIImplementation::ms_hWindow;
ID3D11RenderTargetView* GUIImplementation::ms_pRenderTarget;
WNDPROC GUIImplementation::ms_pWndProc;
GUIImplementationMode		GUIImplementation::ms_mode;
ID3D12DescriptorHeap* GUIImplementation::g_pd3dRtvDescHeap = nullptr;
ID3D12DescriptorHeap* GUIImplementation::g_pd3dSrvDescHeap = nullptr;
ID3D12CommandQueue* GUIImplementation::g_pd3dCommandQueue = nullptr;
ID3D12GraphicsCommandList* GUIImplementation::g_pd3dCommandList = nullptr;
ID3D12Resource* GUIImplementation::g_mainRenderTargetResource[NUM_BACK_BUFFERS] = {};
D3D12_CPU_DESCRIPTOR_HANDLE  GUIImplementation::g_mainRenderTargetDescriptor[NUM_BACK_BUFFERS] = {};
ID3D12CommandAllocator* GUIImplementation::g_commandAllocators[NUM_BACK_BUFFERS] = {};
ID3D11DeviceContext* GUIImplementation::ms_cachedContext;
void GUIImplementation::Init(GUIImplementationMode mode)
{
	eLog::Message(__FUNCTION__, "INFO: Init");
	ms_bInit = false;
	ms_bFailed = false;
	ms_hWindow = 0;
	ms_pRenderTarget = nullptr;
	ms_bShouldReloadFonts = false;
	ms_bShouldRefreshRenderTarget = false;
	ms_pWndProc = 0;
	ms_cachedContext = nullptr;
	ms_mode = mode;
}

bool GUIImplementation::ImGui_Init(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, HWND hWindow)
{
	if (!ImGui::CreateContext())
	{
		eLog::Message(__FUNCTION__, "Failed to create ImGui context!");
		return false;
	}

	ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	if (!ImGui_ImplWin32_Init(ms_hWindow))
	{
		eLog::Message(__FUNCTION__, "Failed to init Win32 Backend!");
		return false;
	}

	if (!ImGui_ImplDX11_Init(pDevice, pContext))
	{
		eLog::Message(__FUNCTION__, "Failed to init DX11 Backend!");
		return false;
	}

	ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

	if (!ms_pWndProc)
	{
		eLog::Message(__FUNCTION__, "Failed to set Window Procedure! Error code: %d", GetLastError());
		return false;
	}

	ImGui_SetStyle();
	eLog::Message(__FUNCTION__, "INFO: Init OK");
	return true;
}

bool GUIImplementation::ImGui_InitDX12(IDXGISwapChain* pSwapChain, HWND hWindow)
{

	if (!ImGui::CreateContext())
	{
		eLog::Message(__FUNCTION__, "Failed to create ImGui context!");
		return false;
	}

	ImGui::GetIO().ConfigFlags  = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	if (!ImGui_ImplWin32_Init(ms_hWindow))
	{
		eLog::Message(__FUNCTION__, "Failed to init Win32 Backend!");
		return false;
	}


	ID3D12Device* pDevice = nullptr;

	HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
	if (FAILED(hResult))
	{
		ms_bFailed = true;
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D12 device! Error code: 0x%X", hResult);
		return false;
	}

	{
		D3D12_DESCRIPTOR_HEAP_DESC desc;
		ZeroMemory(&desc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		desc.NumDescriptors = NUM_BACK_BUFFERS;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		desc.NodeMask = 1;
		HRESULT hResult = pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dRtvDescHeap));

		if (FAILED(hResult))
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to create g_pd3dRtvDescHeap! Error code: 0x%X", hResult);
			return false;
		}

		SIZE_T rtvDescriptorSize = pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = g_pd3dRtvDescHeap->GetCPUDescriptorHandleForHeapStart();

		for (UINT i = 0; i < NUM_BACK_BUFFERS; i++)
		{
			g_mainRenderTargetDescriptor[i] = rtvHandle;
			rtvHandle.ptr += rtvDescriptorSize;
		}
	}

	{
		D3D12_DESCRIPTOR_HEAP_DESC desc;
		ZeroMemory(&desc, sizeof(D3D12_DESCRIPTOR_HEAP_DESC));
		desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
		desc.NumDescriptors = 1;
		desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
		HRESULT hResult = pDevice->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&g_pd3dSrvDescHeap));

		if (FAILED(hResult))
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to create g_pd3dSrvDescHeap! Error code: 0x%X", hResult);
			return false;
		}
	}

	for (UINT i = 0; i < NUM_BACK_BUFFERS; ++i)
	{
		hResult = pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&g_commandAllocators[i]));
		if (FAILED(hResult))
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to create command allocator [%d]! Error code: 0x%X", i, hResult);
			return false;
		}
	}


	if (pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, g_commandAllocators[0], nullptr, IID_PPV_ARGS(&g_pd3dCommandList)) != S_OK ||
		g_pd3dCommandList->Close() != S_OK)
	{
		ms_bFailed = true;
		eLog::Message(__FUNCTION__, "ERROR: Failed to create command list! Error code: 0x%X", hResult);
		return false;
	}

	if (!ImGui_ImplDX12_Init(pDevice, NUM_BACK_BUFFERS,
		DXGI_FORMAT_R8G8B8A8_UNORM, g_pd3dSrvDescHeap, g_pd3dSrvDescHeap->GetCPUDescriptorHandleForHeapStart(), g_pd3dSrvDescHeap->GetGPUDescriptorHandleForHeapStart()))
	{
		eLog::Message(__FUNCTION__, "Failed to init DX12 Backend!");
		return false;
	}

	ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);

	if (!ms_pWndProc)
	{
		eLog::Message(__FUNCTION__, "Failed to set Window Procedure! Error code: %d", GetLastError());
		return false;
	}

	ImGui_SetStyle();
	eLog::Message(__FUNCTION__, "INFO: Init OK");
	return true;
}

void GUIImplementation::ImGui_SetStyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowRounding = 6.0f;
	style->ItemSpacing = ImVec2(7, 5.5);
	style->FrameRounding = 2.0f;
	style->FramePadding = ImVec2(6, 4.25);
	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(0.92f, 0.92f, 0.92f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.81f, 0.83f, 0.81f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.93f, 0.65f, 0.14f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.51f, 0.36f, 0.15f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.91f, 0.64f, 0.13f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.55f, 0.21f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	ImGui_ReloadFont();
}

void GUIImplementation::ImGui_ReloadFont()
{
	float fontSize = 16.0f;
	float fMenuScale = SettingsMgr->fMenuScale;
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGuiIO io = ImGui::GetIO();
	io.Fonts->Clear();
	io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, fontSize * fMenuScale);
	io.Fonts->Build();

	if (ms_mode == GIM_DX11)
		ImGui_ImplDX11_InvalidateDeviceObjects();
	else
		ImGui_ImplDX12_InvalidateDeviceObjects();

	if (ms_bShouldReloadFonts)
		ms_bShouldReloadFonts = false;
}

void GUIImplementation::OnPresent(IDXGISwapChain* pSwapChain)
{
	if (ms_bFailed)
		return;

	if (!ms_bInit)
		OnPresent_GUIStart(pSwapChain);

	if (ms_mode == GIM_DX11)
	{
		ID3D11Device* pDevice = nullptr;
		ID3D11DeviceContext* pContext = nullptr;

		HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice);
		if (FAILED(hResult)) return;

		pDevice->GetImmediateContext(&pContext);

		ImGui_Process(pContext);
	}
	if (ms_mode == GIM_DX12)
	{
		ID3D12Device* pDevice = nullptr;

		HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
		if (FAILED(hResult)) return;

		ImGui_ProcessDX12(pDevice, (IDXGISwapChain3*)pSwapChain);
	}

}

void GUIImplementation::OnPresent_GUIStart(IDXGISwapChain* pSwapChain)
{
	if (ms_bInit)
		return;

	if (ms_mode == GIM_DX11)
	{
		ID3D11Device* pDevice = nullptr;
		ID3D11DeviceContext* pContext = nullptr;
		ID3D11Texture2D* pBackBuffer = nullptr;

		HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice);
		if (FAILED(hResult))
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D11 device! Error code: 0x%X", hResult);
			return;
		}

		pDevice->GetImmediateContext(&pContext);
		DXGI_SWAP_CHAIN_DESC swapChainDescription;
		ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

		pSwapChain->GetDesc(&swapChainDescription);

		ms_hWindow = swapChainDescription.OutputWindow;

		if (!ms_hWindow)
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D11 device window!");
			return;
		}

		hResult = pSwapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

		if (FAILED(hResult))
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D11 device backbuffer! Error code: 0x%X", hResult);
			return;
		}

		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &ms_pRenderTarget);
		pBackBuffer->Release();

		if (ImGui_Init(pDevice, pContext, ms_hWindow))
		{
			ms_cachedContext = pContext;
			ms_bInit = true;
			ms_bFailed = false;
			eLog::Message(__FUNCTION__, "INFO: Init OK");
		}
	}
	if (ms_mode == GIM_DX12)
	{
		ID3D12Device* pDevice = nullptr;

		HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
		if (FAILED(hResult))
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D12 device! Error code: 0x%X", hResult);
			return;
		}

		DXGI_SWAP_CHAIN_DESC swapChainDescription;
		ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

		pSwapChain->GetDesc(&swapChainDescription);

		ms_hWindow = swapChainDescription.OutputWindow;

		if (!ms_hWindow)
		{
			ms_bFailed = true;
			eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D12 device window!");
			return;
		}

		if (ImGui_InitDX12(pSwapChain, ms_hWindow))
		{
			ms_bInit = true;
			ms_bFailed = false;
			eLog::Message(__FUNCTION__, "INFO: Init OK");
		}
		ms_bShouldRefreshRenderTarget = true;
	}


	if (SettingsMgr->bEnableGamepadSupport && ms_bInit)
		CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GamepadThread), 0, NULL, 0);

	// load plugins only after gui was ok
	PluginInterface::LoadPlugins();

}

void GUIImplementation::ImGui_Process(ID3D11DeviceContext* pContext)
{
	if (!ms_bInit)
		return;

	if (!pContext)
		return;

	if (ms_bShouldReloadFonts)
		ImGui_ReloadFont();


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	GUI_Process();

	ImGui::EndFrame();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &ms_pRenderTarget, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void GUIImplementation::ImGui_ProcessDX12(ID3D12Device* pDevice, IDXGISwapChain3* pSwapChain)
{
	if (!ms_bInit)
		return;

	if (!pDevice)
		return;

	g_pd3dCommandQueue = DX12Hook::Get()->GetCommandQueue();

	if (!g_pd3dCommandQueue)
		return;

	if (ms_bShouldReloadFonts)
		ImGui_ReloadFont();

	if (ms_bShouldRefreshRenderTarget)
	{
		ImGui_SetupRenderTargetsDX12(pSwapChain);
		ms_bShouldRefreshRenderTarget = false;
	}

	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	GUI_Process();

	ImGui::Render();

	UINT backBufferIdx = pSwapChain->GetCurrentBackBufferIndex();
	ID3D12CommandAllocator* commandAllocator = g_commandAllocators[backBufferIdx];
	commandAllocator->Reset();

	D3D12_RESOURCE_BARRIER barrier = { };
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = g_mainRenderTargetResource[backBufferIdx];
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	g_pd3dCommandList->Reset(commandAllocator, nullptr);
	g_pd3dCommandList->ResourceBarrier(1, &barrier);

	g_pd3dCommandList->OMSetRenderTargets(1, &g_mainRenderTargetDescriptor[backBufferIdx], FALSE, nullptr);
	g_pd3dCommandList->SetDescriptorHeaps(1, &g_pd3dSrvDescHeap);
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), g_pd3dCommandList);
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	g_pd3dCommandList->ResourceBarrier(1, &barrier);
	g_pd3dCommandList->Close();

	g_pd3dCommandQueue->ExecuteCommandLists(1, reinterpret_cast<ID3D12CommandList* const*>(&g_pd3dCommandList));
}

void GUIImplementation::OnBeforeResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (ms_mode == GIM_DX11)
	{
		ID3D11Device* pDevice = nullptr;
		ID3D11DeviceContext* pContext = ms_cachedContext;

		if (pContext)
		{
			HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice);
			if (FAILED(hResult))
				return;

			assert(pDevice);

			if (ms_pRenderTarget)
			{
				pContext->OMSetRenderTargets(0, nullptr, nullptr);
				ms_pRenderTarget->Release();
			}
		}

	}
	if (ms_mode == GIM_DX12)
	{
		ImGui_Reload(pSwapChain);
	}

}

void GUIImplementation::OnAfterResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	if (ms_mode == GIM_DX11)
	{
		ID3D11Device* pDevice = nullptr;
		ID3D11DeviceContext* pContext = ms_cachedContext;
		ID3D11Texture2D* pBackBuffer = nullptr;

		if (pContext)
		{
			HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice);
			if (FAILED(hResult))
				return;

			assert(pDevice);
			pDevice->GetImmediateContext(&pContext);

			hResult = pSwapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), (void**)&pBackBuffer);

			if (FAILED(hResult))
				return;

			assert(pBackBuffer);

			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &ms_pRenderTarget);
			pBackBuffer->Release();

			D3D11_VIEWPORT viewport;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = (FLOAT)Width;
			viewport.Height = (FLOAT)Height;

			pContext->OMSetRenderTargets(1, &ms_pRenderTarget, NULL);
			pContext->RSSetViewports(1, &viewport);
		}


	}	
}

void GUIImplementation::ImGui_SetupRenderTargetsDX12(IDXGISwapChain* pSwapChain)
{
	ID3D12Device* pDevice = nullptr;

	HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
	if (FAILED(hResult))
		return;

	for (UINT i = 0; i < NUM_BACK_BUFFERS; ++i)
	{
		ID3D12Resource* pBackBuffer = NULL;
		pSwapChain->GetBuffer(i, IID_PPV_ARGS(&pBackBuffer));
		if (pBackBuffer)
		{
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
			pSwapChain->GetDesc(&sd);

			D3D12_RENDER_TARGET_VIEW_DESC desc;
			ZeroMemory(&desc, sizeof(D3D12_RENDER_TARGET_VIEW_DESC));
			desc.Format = sd.BufferDesc.Format;
			desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

			pDevice->CreateRenderTargetView(pBackBuffer, &desc, g_mainRenderTargetDescriptor[i]);
			g_mainRenderTargetResource[i] = pBackBuffer;
		}
	}
}

void GUIImplementation::Shutdown()
{
	if (!ms_bInit)
		return;

	ImGui_ImplWin32_Shutdown();
	if (ms_mode == GIM_DX11)
		ImGui_ImplDX11_Shutdown();
	if (ms_mode == GIM_DX12)
		ImGui_ImplDX12_Shutdown();
}

void GUIImplementation::ImGui_DeleteRenderTargetsDX12(IDXGISwapChain* pSwapChain)
{
	ID3D12Device* pDevice = nullptr;

	HRESULT hResult = pSwapChain->GetDevice(__uuidof(ID3D12Device), (void**)&pDevice);
	if (FAILED(hResult))
		return;

	for (UINT i = 0; i < NUM_BACK_BUFFERS; ++i)
	{
		if (g_mainRenderTargetResource[i])
		{
			g_mainRenderTargetResource[i]->Release();
			g_mainRenderTargetResource[i] = nullptr;
		}
	}
}

float GUIImplementation::GetDeltaTime()
{
	float delta = 1.0f / 60.0f;
	if (ms_bInit)
		delta = 1.0f / ImGui::GetIO().Framerate;

	return delta;
}

void GUIImplementation::RequestFontReload()
{
	ms_bShouldReloadFonts = true;
}

void GUIImplementation::ImGui_Reload(IDXGISwapChain* pSwapChain)
{
	ImGui_DeleteRenderTargetsDX12(pSwapChain);
	ms_bShouldRefreshRenderTarget = true;
}

LRESULT WINAPI GUIImplementation::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KILLFOCUS:
		TheMenu->m_bIsFocused = false;
		break;
	case WM_SETFOCUS:
		TheMenu->m_bIsFocused = true;
		break;
	case WM_KEYDOWN:
		if (wParam == SettingsMgr->iHookMenuOpenKey)
			TheMenu->OnActivate();
		if (wParam == SettingsMgr->iToggleSlowMoKey)
			TheMenu->OnToggleSlowMotion();
		if (wParam == SettingsMgr->iToggleFreezeWorldKey)
			TheMenu->OnToggleFreezeWorld();
		if (wParam == SettingsMgr->iToggleCustomCamKey)
			TheMenu->OnToggleCustomCameras();
		if (wParam == SettingsMgr->iResetStageInteractablesKey)
			TheMenu->OnResetStageInteractables();
		if (wParam == SettingsMgr->iToggleFreeCameraKey)
			TheMenu->OnToggleFreeCamera();
		break;
	default:
		break;
	}
	if (TheMenu->m_bIsActive)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}


	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}

void GUIImplementation::GUI_Process()
{
	ImGui::GetIO().MouseDrawCursor = false;

	static bool ms_bFirstDraw = true;

	if (ms_bFirstDraw)
	{
		Notifications->SetNotificationTime(4500);
		Notifications->PushNotification("MK11Hook %s is running! Press %s or L3 + R3 on a controller to open the menu. Build date: %s\n", MK11HOOK_VERSION, eKeyboardMan::KeyToString(SettingsMgr->iHookMenuOpenKey), __DATE__);
		ms_bFirstDraw = false;
	}
	Notifications->Draw();
	TheMenu->Draw();

}
