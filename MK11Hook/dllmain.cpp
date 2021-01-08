#include "includes.h"
#include "code/eSettingsManager.h"

#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"
#include "code/mk10utils.h"
#include "code/mk11.h"
#include "code/mk11menu.h"
#include <iostream>


extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)& pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)& pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::GetIO().MouseDrawCursor = false;
	if (TheMenu->GetActiveState())
	{
		TheMenu->Draw();
	}

	ImGui::EndFrame();

	ImGui::Render();

	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}


using namespace Memory::VP;
using namespace hook;



int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() { }




void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);

	}

	printf("MK11Hook::OnInitializeHook() | Begin!\n");
	TheMenu->Initialize();

	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(_mk11addr(0x14092A223), tramp->Jump(MK11Hooks::HookProcessStuff));
	InjectHook(_mk11addr(0x14090B97A), tramp->Jump(MK11Hooks::HookStartupFightRecording));

	InjectHook(_mk11addr(0x140442B48), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140454DA8), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140454E52), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140455267), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140455417), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14045D079), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14045D44C), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140462608), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14046267F), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140463728), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14059CB74), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14063F214), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14063F792), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140660435), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x1406625EA), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14085AECD), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14085B159), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140869E6C), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x1408727BB), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140872C15), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x14090EF7B), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140975C8A), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x1409ABA82), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x1409C9055), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x1409DA08B), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140AFCAE5), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140B57741), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140D9E53F), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140D9F87F), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x140D9F993), tramp->Jump(MK11Hooks::HookCamSetRot));
	InjectHook(_mk11addr(0x143E1892F), tramp->Jump(MK11Hooks::HookCamSetRot));

	InjectHook(_mk11addr(0x140442B39), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140454D9B), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140454E45), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x1404550F1), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140455258), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140455408), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x14045D432), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x1404625F9), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x14046268C), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140463719), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140465847), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x1404659AF), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x14059CB65), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x14063F208), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x14063F783), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140660429), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x1406625DD), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x14085AEC0), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x14085B14C), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140869E5F), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x1408727AE), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140872C06), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x14090EF65), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140975C7E), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x1409ABA75), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x1409C9046), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x1409D9FFF), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140AFCAD9), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140B57732), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140CFDF66), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140D9E530), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x140D9F7F2), tramp->Jump(MK11Hooks::HookCamSetPos));
	InjectHook(_mk11addr(0x143E18920), tramp->Jump(MK11Hooks::HookCamSetPos));


	InjectHook(_mk11addr(0x1408F71ED), tramp->Jump(MK11Hooks::HookLoadCharacter));
	

}


bool CheckGame()
{
	char* gameName = (char*)_mk11addr(0x1425FDAF8);

	if (strcmp(gameName, "Mortal Kombat 11") == 0)
	{
		return true;
	}
	else
	{
		MessageBoxA(0, "Invalid game version!\nMK11Hook only supports latest (or it needs to be updated) Steam executable, not DirectX12 one.", 0, MB_ICONINFORMATION);
		return false;
	}
}



BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (CheckGame())
		{
			SettingsMgr->Init();
			DisableThreadLibraryCalls(hMod);
			CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
			OnInitializeHook();
		}

		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}