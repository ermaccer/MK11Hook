#pragma once
#include "../minhook/include/MinHook.h"
#include <d3d11.h>
#include "gui_impl.h"
#include "log.h"


class DX11Hook {
private:
	DX11Hook();
	~DX11Hook();

	uintptr_t presentPtr;
	uintptr_t resizeBuffersPtr;

	uintptr_t presentOriginalPtr;
	uintptr_t resizeBuffersOriginalPtr;

public:
	bool Initialize();
	bool Enable();

	static DX11Hook* Get();

	uintptr_t GetPresentAddress();
	uintptr_t GetResizeBuffersAddress();

	void OnPresent(IDXGISwapChain* pSwapChain);
	void OnBeforeResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	void OnAfterResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

	static HRESULT WINAPI Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static HRESULT WINAPI ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
};

DWORD WINAPI DX11Hook_Thread();