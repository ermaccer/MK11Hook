#include "eGamepadManager.h"
#include "..\imgui\imgui.h"
#include "mk11menu.h"
#include <iostream>
bool eGamepadManager::m_bEstablishedConnection = false;
static int64 gamepad_timer = GetTickCount64();
eGamepadManager* TheGamepad = new eGamepadManager();
bool eGamepadManager::IsConnected()
{
	XINPUT_STATE p1 = {};
	return XInputGetState(0, &p1) == ERROR_SUCCESS;
}

XINPUT_STATE eGamepadManager::GetGamepad()
{
	XINPUT_STATE p1 = {};
	if (IsConnected())
	{
		if (!m_bEstablishedConnection)
			m_bEstablishedConnection = true;

		XInputGetState(0, &p1);
	}

	return p1;
}

bool eGamepadManager::ButtonPressed(unsigned int button)
{
	return GetGamepad().Gamepad.wButtons & button;
}

void eGamepadManager::ToggleMenuWithGamepad()
{
	if (TheGamepad->ButtonPressed(XINPUT_GAMEPAD_LEFT_THUMB) && TheGamepad->ButtonPressed(XINPUT_GAMEPAD_RIGHT_THUMB))
	{
		if (GetTickCount64() - gamepad_timer <= 150) return;
		gamepad_timer = GetTickCount64();
		TheMenu->m_bIsActive ^= 1;
	}
}


void GamepadThread()
{
	while (true)
	{
		if (TheGamepad->IsConnected())
		{
			ImGuiIO& io = ImGui::GetIO();
			io.NavInputs[ImGuiNavInput_Activate] = TheGamepad->ButtonPressed(XINPUT_GAMEPAD_A);
			io.NavInputs[ImGuiNavInput_Cancel] = TheGamepad->ButtonPressed(XINPUT_GAMEPAD_B);
			io.NavInputs[ImGuiNavInput_Input] = TheGamepad->ButtonPressed(XINPUT_GAMEPAD_Y);
			io.NavInputs[ImGuiNavInput_Menu] = TheGamepad->ButtonPressed(XINPUT_GAMEPAD_X);
			io.NavInputs[ImGuiNavInput_DpadLeft] = TheGamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_LEFT);
			io.NavInputs[ImGuiNavInput_DpadRight] = TheGamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_RIGHT);
			io.NavInputs[ImGuiNavInput_DpadUp] = TheGamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_UP);
			io.NavInputs[ImGuiNavInput_DpadDown] = TheGamepad->ButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN);
			TheGamepad->ToggleMenuWithGamepad();
		}
		Sleep(1);
	}
}

DWORD __stdcall XInputGetState_Hook(DWORD dwUserIndex, XINPUT_STATE * pState)
{
	DWORD result = XInputGetState(dwUserIndex, pState);

	if (TheMenu->m_bIsActive)
		pState->Gamepad = {};

	return result;
}
