#pragma once
#include <Windows.h>
#include <Xinput.h>

class eGamepadManager {
public:
	static bool m_bEstablishedConnection;
	bool IsConnected();
	XINPUT_STATE GetGamepad();
	bool		 ButtonPressed(unsigned int button);
	void ToggleMenuWithGamepad();
};

extern eGamepadManager* TheGamepad;

void GamepadThread();
DWORD WINAPI XInputGetState_Hook(DWORD dwUserIndex, XINPUT_STATE* pState);
