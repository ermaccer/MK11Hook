#pragma once
#include <Windows.h>
#include <Xinput.h>
#include "..\gui\gui_impl.h"

class eGamepadManager {
public:
	static bool m_bEstablishedConnection;
	static uintptr_t pXInputGetStateFunc;
	static HMODULE hXInputDLL;
	static void Initialize();

	bool IsConnected();
	XINPUT_STATE GetGamepad();
	bool		 ButtonPressed(unsigned int button);
	void ToggleMenuWithGamepad();

	static void Shutdown();
};

extern eGamepadManager* TheGamepad;

void GamepadThread();
DWORD WINAPI XInputGetState_Hook(DWORD dwUserIndex, XINPUT_STATE* pState);
