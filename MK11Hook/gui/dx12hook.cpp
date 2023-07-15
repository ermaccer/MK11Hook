#include "dx12hook.h"
#include <iostream>
#include <Windows.h>
#include <assert.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx12.h"
#include "imgui/imgui_impl_win32.h"

DX12Hook::DX12Hook()
{
	presentPtr = 0;
	resizeBuffersPtr = 0;
	presentOriginalPtr = 0;
	resizeBuffersOriginalPtr = 0;
	executeCommandsPtr = 0;
	executeCommandsOriginalPtr = 0;
	commandQueueOffset = 0;
	commandQueue = nullptr;
}

DX12Hook::~DX12Hook()
{
	MH_DisableHook((void*)presentPtr);
	MH_DisableHook((void*)resizeBuffersPtr);
	MH_DisableHook((void*)executeCommandsPtr);
}

bool DX12Hook::Initialize()
{
	eLog::Message(__FUNCTION__, "INFO: Init");

	auto hD3D12 = GetModuleHandleW(L"d3d12.dll");
	if (!hD3D12)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain d3d12.dll! Error code: %d", GetLastError());
		return false;
	}

	bool isDXGILoaded = false;
	auto hDXGI = GetModuleHandleW(L"dxgi.dll");
	if (!hDXGI)
		hDXGI = LoadLibraryW(L"dxgi.dll");
	else
		isDXGILoaded = true;

	if (!hDXGI && !isDXGILoaded)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain dxgi.dll! Error code: %d", GetLastError());
		return false;
	}

	ID3D12Device* device = nullptr;
	ID3D12CommandQueue* commandQueue = nullptr;
	IDXGISwapChain3* swapChain = nullptr;
	IDXGIFactory4* factory = nullptr;
	HWND hWnd = 0;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;


	auto pD3D12CreateDevice = GetProcAddress(hD3D12, "D3D12CreateDevice");
	if (pD3D12CreateDevice == NULL)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain D3D12CreateDevice! Error code: %d", GetLastError());
		return false;
	}

	auto pCreateDXGIFactory = GetProcAddress(hDXGI, "CreateDXGIFactory");
	if (pCreateDXGIFactory == NULL)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to obtain CreateDXGIFactory! Error code: %d", GetLastError());
		return false;
	}


	HRESULT hResult = ((HRESULT(WINAPI*)(IUnknown*, D3D_FEATURE_LEVEL, const IID&, void**))(pD3D12CreateDevice))(nullptr, featureLevel, __uuidof(ID3D12Device), (void**)&device);

	if (FAILED(hResult))
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to create D3D12 device. Error code: 0x%X", hResult);
		return false;
	}

	D3D12_COMMAND_QUEUE_DESC queueDesc;
	ZeroMemory(&queueDesc, sizeof(D3D12_COMMAND_QUEUE_DESC));
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Priority = 0;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.NodeMask = 0;


	hResult = device->CreateCommandQueue(&queueDesc, __uuidof(ID3D12CommandQueue), (void**)&commandQueue);

	if (FAILED(hResult))
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to create D3D12 command queue. Error code: 0x%X", hResult);
		return false;
	}

	if (((HRESULT(WINAPI*)(const IID&, void**))(pCreateDXGIFactory))(__uuidof(IDXGIFactory), (void**)&factory) < 0)
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to create DXGI factory! Error code: %d", GetLastError());
		return false;
	}

	hWnd = CreateDummyWindow();
	DXGI_SWAP_CHAIN_DESC1 swapChainDescription;
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC1));
	swapChainDescription.BufferCount = NUM_BACK_BUFFERS;
	swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

	hResult = factory->CreateSwapChainForHwnd(commandQueue, hWnd, &swapChainDescription, NULL, NULL, (IDXGISwapChain1**)&swapChain);

	if (FAILED(hResult))
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to create swapchain! Error code: 0x%X", hResult);
		return false;
	}

	uintptr_t* vTable = *(uintptr_t**)(swapChain);
	uintptr_t* queuevTable = *(uintptr_t**)(commandQueue);
	if (vTable == nullptr)
	{
		eLog::Message(__FUNCTION__, "ERROR: Could not obtain D3D12 vTable!");
		return false;
	}

	if (queuevTable == nullptr)
	{
		eLog::Message(__FUNCTION__, "ERROR: Could not obtain D3D12 CommandQueue vTable!");
		return false;
	}

	presentPtr = vTable[8];
	resizeBuffersPtr = vTable[13];

	executeCommandsPtr = queuevTable[10];

	for (int i = 0; i < 1024; i++)
	{
		uintptr_t swPtr = (uintptr_t)swapChain;
		uintptr_t target = swPtr + (i * sizeof(uintptr_t));
		if (IsBadReadPtr((void*)target, sizeof(uintptr_t)))
		{
			break;
		}

		uintptr_t value = *(uintptr_t*)(target);

		if (value == (uintptr_t)commandQueue)
		{
			commandQueueOffset = (i * sizeof(uintptr_t));
			break;
		}

	}



	eLog::Message(__FUNCTION__, "INFO: D3D12 vTable: 0x%p", vTable);
	eLog::Message(__FUNCTION__, "INFO: D3D12 CommandQueue vTable: 0x%p", queuevTable);
	eLog::Message(__FUNCTION__, "INFO: D3D12 Present: 0x%p", presentPtr);
	eLog::Message(__FUNCTION__, "INFO: D3D12 ResizeBuffers: 0x%p", resizeBuffersPtr);
	eLog::Message(__FUNCTION__, "INFO: D3D12 CommandQueue ExecuteCommandList: 0x%p", executeCommandsPtr);
	eLog::Message(__FUNCTION__, "INFO: CommandQueue Offset: %d", commandQueueOffset);
	assert(presentPtr);
	assert(resizeBuffersPtr);
	assert(executeCommandsPtr);

	commandQueue->Release();
	swapChain->Release();
	factory->Release();
	device->Release();

	MH_Initialize();

	if (!isDXGILoaded)
		FreeLibrary(hDXGI);

	if (hWnd)
		DestroyWindow(hWnd);

	eLog::Message(__FUNCTION__, "INFO: Finished");
	return true;
}

bool DX12Hook::Enable()
{
	eLog::Message(__FUNCTION__, "INFO: Init");

	MH_STATUS s = MH_CreateHook((void*)presentPtr, Present, (void**)&presentOriginalPtr);

	if (s == MH_OK)
	{
		eLog::Message(__FUNCTION__, "INFO: Present hooked!");
		MH_EnableHook((void*)presentPtr);
	}
	else
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to hook Present! Error code: (MH)%d", s);
		return false;
	}

	s = MH_CreateHook((void*)resizeBuffersPtr, ResizeBuffers, (void**)&resizeBuffersOriginalPtr);

	if (s == MH_OK)
	{
		eLog::Message(__FUNCTION__, "INFO: ResizeBuffers hooked!");
		MH_EnableHook((void*)resizeBuffersPtr);
	}
	else
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to hook ResizeBuffers! Error code: (MH)%d", s);
		return false;
	}

	s = MH_CreateHook((void*)executeCommandsPtr, ExecuteCommandLists, (void**)&executeCommandsOriginalPtr);

	if (s == MH_OK)
	{
		eLog::Message(__FUNCTION__, "INFO: ExecuteCommandsList hooked!");
		MH_EnableHook((void*)executeCommandsPtr);
	}
	else
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to hook ExecuteCommandsList! Error code: (MH)%d", s);
		return false;
	}


	eLog::Message(__FUNCTION__, "INFO: Finished");
	return true;
}

DX12Hook* DX12Hook::Get()
{
	static DX12Hook* gD3D12Hook = nullptr;

	if (gD3D12Hook == nullptr)
		gD3D12Hook = new DX12Hook();

	assert(gD3D12Hook != nullptr);

	return gD3D12Hook;
}

uintptr_t DX12Hook::GetPresentAddress()
{
	return presentOriginalPtr;
}

uintptr_t DX12Hook::GetResizeBuffersAddress()
{
	return resizeBuffersOriginalPtr;
}

uintptr_t DX12Hook::GetExecuteCommandsAddress()
{
	return executeCommandsOriginalPtr;
}

uintptr_t DX12Hook::GetCommandQueueOffsetForSwapChain()
{
	return commandQueueOffset;
}

ID3D12CommandQueue* DX12Hook::GetCommandQueue()
{
	return commandQueue;
}

HWND DX12Hook::CreateDummyWindow()
{
	WNDCLASS windowClass;
	ZeroMemory(&windowClass, sizeof(WNDCLASS));

	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.hInstance = GetModuleHandle(nullptr);
	windowClass.lpszClassName = "DX12HOOKDUMMY";

	RegisterClass(&windowClass);

	return CreateWindow(windowClass.lpszClassName, "DX12HOOKWND", WS_OVERLAPPEDWINDOW, 0, 0, 1, 1, NULL, NULL, windowClass.hInstance, NULL);
}


void DX12Hook::OnPresent(IDXGISwapChain* pSwapChain)
{
	GUIImplementation::OnPresent(pSwapChain);
}

void DX12Hook::OnBeforeResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	GUIImplementation::OnBeforeResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

void DX12Hook::OnAfterResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	GUIImplementation::OnAfterResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

void DX12Hook::OnExecuteCommandLists(ID3D12CommandQueue* pQueue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists)
{
	commandQueue = pQueue;
	//GUIImplementation::OnExecuteCommandLists(pQueue, NumCommandLists, ppCommandLists);
}

HRESULT __stdcall DX12Hook::Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	uintptr_t addr = DX12Hook::Get()->GetPresentAddress();
	assert(addr != 0);

	DX12Hook::Get()->OnPresent(pSwapChain);

	return ((HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT))addr)(pSwapChain, SyncInterval, Flags);
}

HRESULT __stdcall DX12Hook::ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	uintptr_t addr = DX12Hook::Get()->GetResizeBuffersAddress();
	assert(addr != 0);

	DX12Hook::Get()->OnBeforeResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	HRESULT result = ((HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT))addr)(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	DX12Hook::Get()->OnAfterResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	return result;
}

void __stdcall DX12Hook::ExecuteCommandLists(ID3D12CommandQueue* pQueue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists)
{
	uintptr_t addr = DX12Hook::Get()->GetExecuteCommandsAddress();
	assert(addr != 0);

	DX12Hook::Get()->OnExecuteCommandLists(pQueue, NumCommandLists, ppCommandLists);

	((void(WINAPI*)(ID3D12CommandQueue*, UINT, ID3D12CommandList*))addr)(pQueue, NumCommandLists, ppCommandLists);
}

DWORD __stdcall DX12Hook_Thread()
{
	if (!DX12Hook::Get()->Initialize())
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to initialize DX12Hook\n");
		return FALSE;
	}

	if (!DX12Hook::Get()->Enable())
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to enable DX12Hook\n");
		return FALSE;
	}

	eLog::Message(__FUNCTION__, "INFO: DX12Hook initialized OK");

	GUIImplementation::Init(GIM_DX12);
	return TRUE;
}
