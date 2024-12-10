// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <iostream>

#include "gui/dx11hook.h"
#include "gui/dx12hook.h"
#include "gui/log.h"
#include "gui/notifications.h"

#include "plugin/Menu.h"
#include "plugin/Settings.h"
#include "plugin/Hooks.h"
#include "plugin/PatternSolver.h"
#include "plugin/PluginInterface.h"

#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"

#include "mk/GameInfo.h"
#include "mk/Krypt.h"
#include "mk/Scaleform.h"

#include "helper/eGamepadManager.h"
#include "helper/eAbilityNames.h"

#include <Commctrl.h>

#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32.lib")

using namespace Memory::VP;
int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() { }


bool IsDX12()
{
	return GetModuleHandle("d3d12.dll") ? true : false;
}

void OnInitializeHook()
{
	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}

	eLog::Message(__FUNCTION__, "INFO: MK11Hook (%s | %s) Begin!", MK11HOOK_VERSION, __DATE__);
	eLog::Message(__FUNCTION__, "INFO: Is DirectX12 - %s", IsDX12() ? "Yes" : "No");

	Notifications->Init();
	eAbiltityNames::Init();
	FGGameInfo::FindGameInfo();
	Krypt::FindKrypt();
	Scaleform::FindData();

	if (SettingsMgr->bEnableGamepadSupport)
		eGamepadManager::Initialize();

	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(_pattern(PATID_MKProcDispatch_Hook), tramp->Jump(MKProcDispatch_Hook));
	InjectHook(_pattern(PATID_RecordEvent_Hook), tramp->Jump(RecordEvent_Hook));

	Nop(_pattern(PATID_CameraPositionNOP), 7);
	Nop(_pattern(PATID_CameraRotationNOP), 8);

	InjectHook(_pattern(PATID_CameraPositionHook), tramp->Jump(&MKCamera::HookedSetPosition));
	InjectHook(_pattern(PATID_CameraRotationHook), tramp->Jump(&MKCamera::HookedSetRotation));

	InjectHook(_pattern(PATID_SetSelectScreen_Hook), tramp->Jump(SetSelectScreen_Hook), HookType::Jump);
	InjectHook(_pattern(PATID_SetCharacterLadder_Hook), tramp->Jump(SetCharacterLadder_Hook));

	InjectHook(_pattern(PATID_ReadPropertyValue_Hook), tramp->Jump(ReadPropertyValue_Hook), HookType::Jump);
	InjectHook(_pattern(PATID_SetProperty_Hook), tramp->Jump(SetProperty));


	InjectHook(_pattern(PATID_Dispatch_Hook), tramp->Jump(Dispatch_Hook));

	if (SettingsMgr->bMakeAllAbilities1Slot)
		InjectHook(_pattern(PATID_1SlotAbilitiesHook), tramp->Jump(GenericTrueReturn), HookType::Jump);

	InjectHook(_pattern(PATID_SetKryptCharacter_Hook), tramp->Jump(SetKryptCharacter));
	InjectHook(_pattern(PATID_SetKryptCharacterL_Hook), tramp->Jump(SetKryptCharacterL));
	InjectHook(_pattern(PATID_SetKryptCharacterClass_Hook), tramp->Jump(SetKryptCharacterClass));


	ReadCall(_pattern(PATID_ProcessDOFSettings), pProcessDOFSettings);
	InjectHook(_pattern(PATID_ProcessDOFSettings), tramp->Jump(ProcessDOFSettings));

	ReadCall(_pattern(PATID_FightStartupAddModifiers), pPluginFightStartupAddModifiers);
	InjectHook(_pattern(PATID_FightStartupAddModifiers), tramp->Jump(PluginFightStartupAddModifiers));

	MH_CreateHook((void*)_pattern(PATID_FightStartupQueueModifiers), &PluginFightStartupQueueModifiers, (void**)&pPluginFightStartupQueueModifiers);
	MH_EnableHook((void*)_pattern(PATID_FightStartupQueueModifiers));

	//gamepad
	if (SettingsMgr->bEnableGamepadSupport)
	{
		// only hook if xinputgetstate was loaded
		if (eGamepadManager::hXInputDLL && eGamepadManager::pXInputGetStateFunc)
		{
			uintptr_t xinput_addr = _pattern(PATID_XInputGetState_Hook);
			xinput_addr += *(unsigned int*)(xinput_addr)+4;

			InjectHook(xinput_addr, tramp->Jump(XInputGetState_Hook), HookType::Jump);
		}

	}

	HANDLE h = 0;

	if (IsDX12())
		h = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DX12Hook_Thread), 0, NULL, 0);
	else
		h = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DX11Hook_Thread), 0, NULL, 0);

	if (!(h == nullptr)) CloseHandle(h);
}

bool ValidateGameVersion()
{
	PatternSolver::Initialize();

	if (PatternSolver::CheckMissingPatterns())
	{
		int nButtonPressed = 0;
		TASKDIALOGCONFIG config;
		ZeroMemory(&config, sizeof(TASKDIALOGCONFIG));

		const TASKDIALOG_BUTTON buttons[] = {
			{ IDOK, L"Launch anyway\nThe game might crash or have missing features!" },
			{ IDNO, L"Exit" }
		};
		config.cbSize = sizeof(config);

		config.dwFlags = TDF_ENABLE_HYPERLINKS | TDF_CAN_BE_MINIMIZED | TDF_USE_COMMAND_LINKS;
		config.pszMainIcon = TD_WARNING_ICON;

		config.pszWindowTitle = L"Warning";
		config.pszMainInstruction = L"MK11Hook";
		config.pszContent = L"Could not start MK11Hook!\n\n"
			L"One or more code patterns could not be found, this might indicate"
			L" that game version is not supported or the plugin has not been updated.\n\n"
			L"MK11Hook officially is only tested with latest Steam version.\n"
			L"Check log for more details.\n";


		config.pButtons = buttons;
		config.cButtons = ARRAYSIZE(buttons);

		if (SUCCEEDED(TaskDialogIndirect(&config, &nButtonPressed, NULL, NULL)))
		{
			switch (nButtonPressed)
			{
			case IDOK:
				return true;
				break;
			case IDNO:
				exit(0);
				break;
			default:
				break;
			}
		}
	}

	return true;
}

extern "C"
{
	__declspec(dllexport) void InitializeASI()
	{
		MH_Initialize();
		eLog::Initialize();

		if (ValidateGameVersion())
		{
			OnInitializeHook();
		}

	}
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		eGamepadManager::Shutdown();
		GUIImplementation::Shutdown();
		PluginInterface::UnloadPlugins();
		break;
	}
	return TRUE;
}
