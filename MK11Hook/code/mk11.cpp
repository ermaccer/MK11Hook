#include "mk11.h"
#include <iostream>
#include <Windows.h>
#include "mk11menu.h"

void __fastcall MK11Hooks::HookProcessStuff()
{
	TheMenu->Process();

	if (TheMenu->bSlowMotionEnabled)
		((void(__fastcall*)(float, int, int))_mk11addr(0x1405BEDD0))(TheMenu->fSlowMotionSpeed, 10, 0);

	((void(__fastcall*)())_mk11addr(0x1411518C0))();
}

void __fastcall MK11Hooks::HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	((void(__fastcall*)(int64,int64,int64,int64))_mk11addr(0x141157850))(eventID,a2,a3,a4);

}
