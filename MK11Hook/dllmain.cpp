#include "code/eSettingsManager.h"
#include "eDirectX11Hook.h"

#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"
#include "code/mk10utils.h"
#include "code/mk11.h"
#include "code/mk11menu.h"
#include "code/eNotifManager.h"
#include "code/mkcamera.h"
#include "code/helper/eGamepadManager.h"
#include "code/helper/eAbilityNames.h"
#include "code/MKObject.h"
#include <iostream>

using namespace Memory::VP;
int64 __fastcall GenericTrue2Return() { return 2; }
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
	Notifications->Init();

	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(_addr(0x1409312C3), tramp->Jump(MK11Hooks::HookProcessStuff));
	InjectHook(_addr(0x140910F53), tramp->Jump(MK11Hooks::HookStartupFightRecording));


	// 0xFE00
	Nop(_addr(0x1419B86F3), 7);
	Nop(_addr(0x1419B8703), 8);
	InjectHook(_addr(0x1419B8711), tramp->Jump(&MKCamera::HookedSetPosition));
	InjectHook(_addr(0x1419B871E), tramp->Jump(&MKCamera::HookedSetRotation));



	InjectHook(_addr(0x140871510), tramp->Jump(MK11Hooks::HookSetSelectScreen), PATCH_JUMP);
	InjectHook(_addr(0x14059D14E), tramp->Jump(MK11Hooks::HookSetLadderScreen));



	InjectHook(_addr(0x14097F8E4), tramp->Jump(SetKryptCharacter));
	InjectHook(_addr(0x14097F8FB), tramp->Jump(SetKryptCharacterL));
	InjectHook(_addr(0x14097F95A), tramp->Jump(SetKryptCharacterClass));


	if (SettingsMgr->bMakeAllAbilities1Slot)
		InjectHook(_addr(0x140724F40), tramp->Jump(GenericTrueReturn), PATCH_JUMP);


	InjectHook(_addr(0x141A8BBF0), tramp->Jump(MK11Hooks::HookReadPropertyValue), PATCH_JUMP);
	InjectHook(_addr(0x1412B96C8), tramp->Jump(MK11Hooks::HookSetProperty));


	InjectHook(_addr(0x141B5D7E4), tramp->Jump(MK11Hooks::HookDispatch));

	//gamepad
	if (SettingsMgr->bEnableGamepadSupport)
		InjectHook(_addr(0x1423A2291), tramp->Jump(XInputGetState_Hook), PATCH_JUMP);

}

bool ValidateGameVersion()
{
	char* gameName = (char*)_addr(0x14261CEA0);

	if (strcmp(gameName, "Mortal Kombat 11") == 0)
		return true;
	else
	{
		MessageBoxA(0, "Invalid game version!\nMK11Hook only supports latest Steam executable, not DirectX12 one.\n\n"
			"If you still cannot run the plugin and made sure that the game is updated, MK11Hook needs to be updated.", 0, MB_ICONINFORMATION);
		return false;
	}
}




BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		if (ValidateGameVersion())
		{
			eDirectX11Hook::Init();
			SettingsMgr->Init();
			eAbiltityNames::Init();
			DisableThreadLibraryCalls(hMod);
			CreateThread(nullptr, 0, DirectXHookThread, hMod, 0, nullptr);

			OnInitializeHook();
		}
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}