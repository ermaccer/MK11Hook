#include "dx11hook.h"
#include <iostream>
#include <Windows.h>
#include <assert.h>


DX11Hook::DX11Hook()
{
	presentPtr = 0;
	resizeBuffersPtr = 0;
	presentOriginalPtr = 0;
	resizeBuffersOriginalPtr = 0;
}

DX11Hook::~DX11Hook()
{
	MH_DisableHook((void*)presentPtr);
	MH_DisableHook((void*)resizeBuffersPtr);
}

bool DX11Hook::Initialize()
{
	eLog::Message(__FUNCTION__, "INFO: Init");
	HWND hWnd = GetDesktopWindow();
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;

	IDXGISwapChain* swapChain = nullptr;
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;


	swapChainDescription.OutputWindow = hWnd;
	swapChainDescription.Windowed = true;

	swapChainDescription.BufferCount = 1;
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // >= 9.1
	swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	swapChainDescription.SampleDesc.Count = 1;

	HRESULT hResult = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_NULL, nullptr, 0, &featureLevel, 1,
		D3D11_SDK_VERSION, &swapChainDescription, &swapChain, &device, nullptr, &context);

	if (FAILED(hResult))
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to create D3D11 device. Error code: 0x%X", hResult);
		return false;
	}


	uintptr_t* vTable = *(uintptr_t**)(swapChain);

	if (vTable == nullptr)
	{
		eLog::Message(__FUNCTION__, "ERROR: Could not obtain D3D11 vTable!");
		return false;
	}

	presentPtr = vTable[8];
	resizeBuffersPtr = vTable[13];

	eLog::Message(__FUNCTION__, "INFO: D3D11 vTable: 0x%p",vTable);
	eLog::Message(__FUNCTION__, "INFO: D3D11 Present: 0x%p", presentPtr);
	eLog::Message(__FUNCTION__, "INFO: D3D11 ResizeBuffers: 0x%p", resizeBuffersPtr);
	assert(presentPtr);
	assert(resizeBuffersPtr);
	

	MH_Initialize();

	device->Release();
	swapChain->Release();
	context->Release();
	device = nullptr;
	swapChain = nullptr;
	context = nullptr;
	eLog::Message(__FUNCTION__, "INFO: Finished");
	return true;
}

bool DX11Hook::Enable()
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
	eLog::Message(__FUNCTION__, "INFO: Finished");
	return true;

}

DX11Hook* DX11Hook::Get()
{
	static DX11Hook* gD3D11Hook = nullptr;

	if (gD3D11Hook == nullptr)
		gD3D11Hook = new DX11Hook();

	assert(gD3D11Hook != nullptr);

	return gD3D11Hook;
}

uintptr_t DX11Hook::GetPresentAddress()
{
	return presentOriginalPtr;
}

uintptr_t DX11Hook::GetResizeBuffersAddress()
{
	return resizeBuffersOriginalPtr;
}

void DX11Hook::OnPresent(IDXGISwapChain* pSwapChain)
{
	GUIImplementation::OnPresent(pSwapChain);
}

void DX11Hook::OnBeforeResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	GUIImplementation::OnBeforeResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

void DX11Hook::OnAfterResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	GUIImplementation::OnAfterResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

HRESULT WINAPI DX11Hook::Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	uintptr_t addr = DX11Hook::Get()->GetPresentAddress();
	assert(addr != 0);

	DX11Hook::Get()->OnPresent(pSwapChain);

	return ((HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT))addr)(pSwapChain, SyncInterval, Flags);
}

HRESULT WINAPI DX11Hook::ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	uintptr_t addr = DX11Hook::Get()->GetResizeBuffersAddress();
	assert(addr != 0);

	DX11Hook::Get()->OnBeforeResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	HRESULT result = ((HRESULT(WINAPI*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT))addr)(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
	DX11Hook::Get()->OnAfterResize(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	return result;
}

DWORD __stdcall DX11Hook_Thread()
{
	if (!DX11Hook::Get()->Initialize())
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to initialize DX11Hook\n");
		return FALSE;
	}

	if (!DX11Hook::Get()->Enable())
	{
		eLog::Message(__FUNCTION__, "ERROR: Failed to enable DX11Hook\n");
		return FALSE;
	}

	eLog::Message(__FUNCTION__, "INFO: DX11Hook initialized OK");

	GUIImplementation::Init(GIM_DX11);
	return TRUE;
}
