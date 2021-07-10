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

#include <iostream>

using namespace Memory::VP;

int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() { }


bool ValidateGameVersion()
{
	char* gameName = (char*)_addr(0x142600C68);

	if (strcmp(gameName, "Mortal Kombat 11") == 0)
		return true;
	else
	{
		MessageBoxA(0, "Invalid game version!\nMK11Hook only supports latest (or it needs to be updated) Steam executable, not DirectX12 one.", 0, MB_ICONINFORMATION);
		return false;
	}
}

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
	InjectHook(_addr(0x14092B853), tramp->Jump(MK11Hooks::HookProcessStuff));
	InjectHook(_addr(0x14090CF53), tramp->Jump(MK11Hooks::HookStartupFightRecording));
	InjectHook(_addr(0x14090D617), tramp->Jump(MK11Hooks::PostLoadHook));

	
	Nop(_addr(0x1419A9763), 7);
	Nop(_addr(0x1419A9773), 8);
	InjectHook(_addr(0x1419A9781), tramp->Jump(&MKCamera::HookedSetPosition));
	InjectHook(_addr(0x1419A978E), tramp->Jump(&MKCamera::HookedSetRotation));

	InjectHook(_addr(0x1408F881D), tramp->Jump(MK11Hooks::HookLoadCharacter));


	InjectHook(_addr(0x140976DF4), tramp->Jump(MK11::SetKryptCharacter));
	InjectHook(_addr(0x140976E0B), tramp->Jump(MK11::SetKryptCharacterL));
	InjectHook(_addr(0x140976E6A), tramp->Jump(MK11::SetKryptCharacterClass));


	if (SettingsMgr->bMakeAllAbilities1Slot)
		InjectHook(_addr(0x140720E90), tramp->Jump(GenericTrueReturn), PATCH_JUMP);


	InjectHook(_addr(0x141A806B0), tramp->Jump(MK11Hooks::HookReadPropertyValue), PATCH_JUMP);
	InjectHook(_addr(0x14129FE98), tramp->Jump(MK11Hooks::HookSetProperty));

	InjectHook(_addr(0x14084B658), tramp->Jump(MK11Hooks::HookLoadouts));

	InjectHook(_addr(0x141B45ED4), tramp->Jump(MK11Hooks::HookDispatch));


    //InjectHook(_addr(0x14056A258), tramp->Jump(&MKCharacter::GetCharacterData));

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