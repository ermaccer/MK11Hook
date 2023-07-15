#pragma once
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi.h>
#include <dxgi1_6.h>
#include <vector>
#include "const.h"
#include "..\plugin\PluginInterface.h"

enum GUIImplementationMode {
	GIM_DX11 = 1,
	GIM_DX12
};

class GUIImplementation {
public:
	static bool							ms_bInit;
	static bool							ms_bFailed;
	static bool							ms_bShouldReloadFonts;
	static bool							ms_bShouldRefreshRenderTarget;
	static HWND							ms_hWindow;
	static WNDPROC						ms_pWndProc;
	static ID3D11RenderTargetView*		ms_pRenderTarget;
	static GUIImplementationMode		ms_mode;
	// dx11
	static ID3D11DeviceContext*			ms_cachedContext;
	// dx12
	static ID3D12DescriptorHeap*	    g_pd3dRtvDescHeap;
	static ID3D12DescriptorHeap*	    g_pd3dSrvDescHeap;
	static ID3D12CommandQueue*		    g_pd3dCommandQueue;
	static ID3D12GraphicsCommandList*   g_pd3dCommandList;
	static ID3D12Resource*				g_mainRenderTargetResource[NUM_BACK_BUFFERS];
	static D3D12_CPU_DESCRIPTOR_HANDLE  g_mainRenderTargetDescriptor[NUM_BACK_BUFFERS];
	static ID3D12CommandAllocator*		g_commandAllocators[NUM_BACK_BUFFERS];

	static void Init(GUIImplementationMode mode);
	static void Shutdown();
	static bool ImGui_Init(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, HWND hWindow);
	static bool ImGui_InitDX12(IDXGISwapChain* pSwapChain, HWND hWindow);
	static void ImGui_SetupRenderTargetsDX12(IDXGISwapChain* pSwapChain);
	static void ImGui_DeleteRenderTargetsDX12(IDXGISwapChain* pSwapChain);
	static void ImGui_Reload(IDXGISwapChain* pSwapChain);

	static void ImGui_SetStyle();
	static void	ImGui_ReloadFont();

	static void OnPresent(IDXGISwapChain* pSwapChain);
	static void OnPresent_GUIStart(IDXGISwapChain* pSwapChain);

	static void ImGui_Process(ID3D11DeviceContext* pContext);
	static void ImGui_ProcessDX12(ID3D12Device* pDevice, IDXGISwapChain3* pSwapChain);
	
	static void GUI_Process();

	static void OnBeforeResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
	static void OnAfterResize(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);


	static float GetDeltaTime();
	static void  RequestFontReload();

	static LRESULT WINAPI WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);