#pragma once
#include "../minhook/include/MinHook.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include "gui_impl.h"
#include "log.h"
#include "const.h"

class DX12Hook {
private:
	DX12Hook();
	~DX12Hook();

	uintptr_t presentPtr;
	uintptr_t resizeBuffersPtr;
	uintptr_t executeCommandsPtr;

	uintptr_t presentOriginalPtr;
	uintptr_t resizeBuffersOriginalPtr;
	uintptr_t executeCommandsOriginalPtr;

	uintptr_t commandQueueOffset;

	ID3D12CommandQueue* commandQueue;
public:
	bool Initialize();
	bool Enable();

	static DX12Hook* Get();

	uintptr_t GetPresentAddress();
	uintptr_t GetResizeBuffersAddress();
	uintptr_t GetExecuteCommandsAddress();
	uintptr_t GetCommandQueueOffsetForSwapChain();
	ID3D12CommandQueue* GetCommandQueue();

	HWND CreateDummyWindow();

	void OnPresent(IDXGISwapChain* pSwapChain);
	void OnBeforeResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	void OnAfterResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	void OnExecuteCommandLists(ID3D12CommandQueue* pQueue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists);

	static HRESULT WINAPI Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	static HRESULT WINAPI ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	static void WINAPI ExecuteCommandLists(ID3D12CommandQueue* pQueue, UINT NumCommandLists, ID3D12CommandList* ppCommandLists);
};

DWORD WINAPI DX12Hook_Thread();