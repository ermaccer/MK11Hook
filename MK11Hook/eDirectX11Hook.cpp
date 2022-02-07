#include "eDirectX11Hook.h"
#include "code/mk11menu.h"
#include "code/eNotifManager.h"
#include "code/eSettingsManager.h"
#include "code/eGamepadManager.h"
#include "font.h"
#include <chrono>

Present eDirectX11Hook::m_pPresent;
ResizeBuffers eDirectX11Hook::m_pResizeBuffers;
HWND eDirectX11Hook::ms_hWindow;
WNDPROC eDirectX11Hook::ms_pWndProc;
ID3D11Device* eDirectX11Hook::pDevice;
ID3D11DeviceContext* eDirectX11Hook::pContext;
ID3D11RenderTargetView* eDirectX11Hook::mainRenderTargetView;
bool eDirectX11Hook::ms_bInit;
bool eDirectX11Hook::ms_bFirstDraw;
bool eDirectX11Hook::ms_bShouldReloadFonts;
ImGuiStyle eDirectX11Hook::ms_localStyleCopy;

// compat
bool bInitShared= false;
void InitShared(ImGuiContext* ctx) 
{
	bInitShared = true;
	ImGui::SetCurrentContext(ctx);
}

void SharedStyle()
{
	eDirectX11Hook::SetImGuiStyle();
}

void SharedPresent()
{
	if (eDirectX11Hook::ms_bFirstDraw)
	{
		Notifications->SetNotificationTime(7500);
		Notifications->PushNotification("MK11Hook %s is running! Press F1 (or L3+R3 on a controller if controller support enabled) to open the menu. Build date: %s\n", MK11HOOK_VERSION, __DATE__);
		eDirectX11Hook::ms_bFirstDraw = false;
	}


	Notifications->Draw();

	if (TheMenu->GetActiveState())
	{
		TheMenu->Draw();
	}
}

inline bool ShouldHookDX(float timeout = 2.5f)
{
	auto start = std::chrono::system_clock::now();
	while (!bInitShared)
	{
		std::chrono::duration<double> now = std::chrono::system_clock::now() - start;
		if (now.count() > timeout)
		{
			return false;
		}
	}
	return true;

}


void eDirectX11Hook::Init()
{
	m_pPresent = 0;
	m_pResizeBuffers = 0;
	pDevice = 0;
	pContext = 0;
	ms_bFirstDraw = true;
	ms_bInit = false;
	ms_bShouldReloadFonts = false;
	ms_hWindow = 0;

}

void eDirectX11Hook::SetImGuiStyle()
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

	ms_localStyleCopy = ImGui::GetStyle();


	ReloadImGuiFont();
}

void eDirectX11Hook::InitImGui()
{
	ImGui::CreateContext();
	ImGui::GetIO().ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplWin32_Init(ms_hWindow);
	ImGui_ImplDX11_Init(pDevice, pContext);
	if (SettingsMgr->bEnableGamepadSupport)
		CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(GamepadThread), nullptr, 0, nullptr);
	SharedStyle();
}

void eDirectX11Hook::ReloadImGuiFont()
{
	if (!(SettingsMgr->fMenuScale < 1.0f))
	{
		float fontSize = 13.0f;
		ImGuiStyle * style = &ImGui::GetStyle();
		ImGuiIO io = ImGui::GetIO();

		if (!io.Fonts->Locked && !bInitShared)
		{
			io.Fonts->Clear();
			io.Fonts->AddFontFromMemoryCompressedTTF(Font_compressed_data, Font_compressed_size, fontSize * SettingsMgr->fMenuScale);
			io.Fonts->Build();
		}

		style->WindowPadding = ms_localStyleCopy.WindowPadding;
		style->WindowRounding = ms_localStyleCopy.WindowRounding;
		style->WindowMinSize = ms_localStyleCopy.WindowMinSize;
		style->ChildRounding = ms_localStyleCopy.ChildRounding;
		style->PopupRounding = ms_localStyleCopy.PopupRounding;
		style->FramePadding = ms_localStyleCopy.FramePadding;
		style->FrameRounding = ms_localStyleCopy.FrameRounding;
		style->ItemSpacing = ms_localStyleCopy.ItemSpacing;
		style->ItemInnerSpacing = ms_localStyleCopy.ItemInnerSpacing;
		style->CellPadding = ms_localStyleCopy.CellPadding;
		style->TouchExtraPadding = ms_localStyleCopy.TouchExtraPadding;
		style->IndentSpacing = ms_localStyleCopy.IndentSpacing;
		style->ColumnsMinSpacing = ms_localStyleCopy.ColumnsMinSpacing;
		style->ScrollbarSize = ms_localStyleCopy.ScrollbarSize;
		style->ScrollbarRounding = ms_localStyleCopy.ScrollbarRounding;
		style->GrabMinSize = ms_localStyleCopy.GrabMinSize;
		style->GrabRounding = ms_localStyleCopy.GrabRounding;
		style->LogSliderDeadzone = ms_localStyleCopy.LogSliderDeadzone;
		style->TabRounding = ms_localStyleCopy.TabRounding;
		style->TabMinWidthForCloseButton = ms_localStyleCopy.TabMinWidthForCloseButton;
		style->DisplayWindowPadding = ms_localStyleCopy.DisplayWindowPadding;
		style->DisplaySafeAreaPadding = ms_localStyleCopy.DisplaySafeAreaPadding;
		style->MouseCursorScale = ms_localStyleCopy.MouseCursorScale;

		style->ScaleAllSizes(SettingsMgr->fMenuScale);
		ImGui_ImplDX11_InvalidateDeviceObjects();

		if (ms_bShouldReloadFonts)
			ms_bShouldReloadFonts = false;


	}
}

HRESULT __stdcall eDirectX11Hook::Present(IDXGISwapChain * pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!ms_bInit)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			ms_hWindow = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			ms_pWndProc = (WNDPROC)SetWindowLongPtr(ms_hWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			ms_bInit = true;
		}
		else
			return m_pPresent(pSwapChain, SyncInterval, Flags);
	}
	
	if (ms_bShouldReloadFonts)
		ReloadImGuiFont();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = false;

	if (ms_bFirstDraw)
	{
		Notifications->SetNotificationTime(4500);
		Notifications->PushNotification("MK11Hook %s is running! Press F1 (or L3+R3 on a controller if controller support enabled) to open the menu. Build date: %s\n", MK11HOOK_VERSION, __DATE__);
		ms_bFirstDraw = false;
	}

	Notifications->Draw();

	if (TheMenu->GetActiveState())
		TheMenu->Draw();


#ifdef _DEBUG
	MK11Menu::DrawDebug();
#endif // _DEBUG


	ImGui::EndFrame();
	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return m_pPresent(pSwapChain, SyncInterval, Flags);
}

LRESULT __stdcall eDirectX11Hook::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
		break;
	default:
		break;
	}

	if (TheMenu->GetActiveState())
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
		return true;
	}

	return CallWindowProc(ms_pWndProc, hWnd, uMsg, wParam, lParam);
}

HRESULT __stdcall eDirectX11Hook::ResizeBuffers(IDXGISwapChain * pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	// somehow pdevice handle is missing in mk11 and i2? no idea
	if (pDevice)
	{
		if (mainRenderTargetView)
		{
			pContext->OMSetRenderTargets(0, 0, 0);
			mainRenderTargetView->Release();
		}
	}


	HRESULT result = m_pResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	if (pDevice)
	{
		ID3D11Texture2D* pBackBuffer;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
		pBackBuffer->Release();

		D3D11_VIEWPORT viewport;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (float)Width;
		viewport.Height = (float)Height;
		
		
		
		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		pContext->RSSetViewports(1, &viewport);

	}

	return  result;
}

DWORD __stdcall DirectXHookThread(LPVOID lpReserved)
{
	if (ShouldHookDX(2.5f))
		return true;

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&eDirectX11Hook::m_pPresent, eDirectX11Hook::Present);
			kiero::bind(13, (void**)&eDirectX11Hook::m_pResizeBuffers, eDirectX11Hook::ResizeBuffers);
			init_hook = true;
		}
	} while (!init_hook);

	return TRUE;
}

