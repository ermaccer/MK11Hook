#include "eGamepadManager.h"
#include "../plugin/Menu.h"
#include "../utils.h"
#include "../gui/imgui/imgui.h"
#include "../gui/gui_impl.h"
#include "../gui/log.h"
#include "../plugin/Settings.h"

uintptr_t eGamepadManager::pXInputGetStateFunc = 0;
HMODULE eGamepadManager::hXInputDLL = 0;

eGamepadState eGamepadManager::ms_gamepadState = {};


void eGamepadManager::Initialize()
{
	static const char* xinputDlls[5] =
	{
		"xinput1_4.dll",   // Windows 8+
		"xinput1_3.dll",   // DirectX SDK
		"xinput9_1_0.dll", // Windows Vista, Windows 7
		"xinput1_2.dll",   // DirectX SDK
		"xinput1_1.dll"    // DirectX SDK
	};

	int loadedDll = -1;
	for (int i = 0; i < 5; i++)
	{
		hXInputDLL = LoadLibraryA(xinputDlls[i]);
		if (hXInputDLL)
		{
			pXInputGetStateFunc = (uintptr_t)GetProcAddress(hXInputDLL, "XInputGetState");
			loadedDll = i;
			break;
		}
	}

	if (hXInputDLL && pXInputGetStateFunc && loadedDll >= 0)
		eLog::Message(__FUNCTION__, "XInput loaded! (DLL: %s)", xinputDlls[loadedDll]);
	else
		eLog::Message(__FUNCTION__, "Failed to initialize XInput!");
}

void eGamepadManager::Update()
{
	ProcessPad();
	UpdateImGui();
}

void eGamepadManager::UpdateImGui()
{
	ToggleMenuWithGamepad();

	if (TheMenu->m_bPressingKey)
		return;

	ImGuiIO& io = ImGui::GetIO();
	io.NavInputs[ImGuiNavInput_Activate] = ms_gamepadState.rawState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	io.NavInputs[ImGuiNavInput_Cancel] = ms_gamepadState.rawState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	io.NavInputs[ImGuiNavInput_Input] = ms_gamepadState.rawState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	io.NavInputs[ImGuiNavInput_Menu] = ms_gamepadState.rawState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	io.NavInputs[ImGuiNavInput_DpadLeft] = ms_gamepadState.rawState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	io.NavInputs[ImGuiNavInput_DpadRight] = ms_gamepadState.rawState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	io.NavInputs[ImGuiNavInput_DpadUp] = ms_gamepadState.rawState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	io.NavInputs[ImGuiNavInput_DpadDown] = ms_gamepadState.rawState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	

}

void eGamepadManager::Reset()
{
	if (!SettingsMgr->bEnableGamepadSupport)
		return;

	for (int i = 0; i < BUTTON_MAX; i++)
	{
		ms_gamepadState.buttonStatePrev[i] = ms_gamepadState.buttonState[i];
	}
}


void eGamepadManager::ToggleMenuWithGamepad()
{
	static int64 gamepad_timer = GetTickCount64();
	if (ButtonPressed(XINPUT_GAMEPAD_LEFT_THUMB) && ButtonPressed(XINPUT_GAMEPAD_RIGHT_THUMB))
	{
		if (GetTickCount64() - gamepad_timer <= 150) return;
		gamepad_timer = GetTickCount64();
		TheMenu->m_bIsActive ^= 1;
	}
}

void eGamepadManager::ProcessPad(int padNum)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	ms_gamepadState.lastButton = -1;

	if (!pXInputGetStateFunc)
		return;

	if (((DWORD(WINAPI*)(DWORD, XINPUT_STATE*))(pXInputGetStateFunc))(padNum, &state) == ERROR_SUCCESS)
	{
		ms_gamepadState.rawState = state;
		static const WORD buttonFlags[BUTTON_DIGITAL_MAX] = {
				XINPUT_GAMEPAD_A, 
				XINPUT_GAMEPAD_B, 
				XINPUT_GAMEPAD_X, 
				XINPUT_GAMEPAD_Y,
				XINPUT_GAMEPAD_LEFT_SHOULDER,
				XINPUT_GAMEPAD_RIGHT_SHOULDER,
				XINPUT_GAMEPAD_BACK,
				XINPUT_GAMEPAD_START,
				XINPUT_GAMEPAD_LEFT_THUMB, 
				XINPUT_GAMEPAD_RIGHT_THUMB,
				XINPUT_GAMEPAD_DPAD_UP, 
				XINPUT_GAMEPAD_DPAD_DOWN,
				XINPUT_GAMEPAD_DPAD_LEFT,
				XINPUT_GAMEPAD_DPAD_RIGHT
		};

		for (int i = 0; i < BUTTON_DIGITAL_MAX; i++)
		{
			bool isDown = state.Gamepad.wButtons & buttonFlags[i];

			if (isDown)
				ms_gamepadState.lastButton = i;

			ms_gamepadState.buttonState[i] = isDown;
		}

		ms_gamepadState.leftTrigger = state.Gamepad.bLeftTrigger / 255.0f;
		ms_gamepadState.rightTrigger = state.Gamepad.bRightTrigger / 255.0f;

		ms_gamepadState.leftStick.x = state.Gamepad.sThumbLX / 32767.0f;
		ms_gamepadState.leftStick.y = state.Gamepad.sThumbLY / 32767.0f;
		ms_gamepadState.rightStick.x = state.Gamepad.sThumbRX / 32767.0f;
		ms_gamepadState.rightStick.y = state.Gamepad.sThumbRY / 32767.0f;


		static float minMovement = 0.5f;

		// digital buttons for analog sticks
		SetState(BUTTON_LEFT_STICK_LEFT, ms_gamepadState.leftStick.x < -minMovement);
		SetState(BUTTON_LEFT_STICK_RIGHT, ms_gamepadState.leftStick.x > minMovement);
		SetState(BUTTON_LEFT_STICK_UP, ms_gamepadState.leftStick.y > minMovement);
		SetState(BUTTON_LEFT_STICK_DOWN, ms_gamepadState.leftStick.y < -minMovement);

		SetState(BUTTON_RIGHT_STICK_LEFT, ms_gamepadState.rightStick.x < -minMovement);
		SetState(BUTTON_RIGHT_STICK_RIGHT, ms_gamepadState.rightStick.x > minMovement);
		SetState(BUTTON_RIGHT_STICK_UP, ms_gamepadState.rightStick.y > minMovement);
		SetState(BUTTON_RIGHT_STICK_DOWN, ms_gamepadState.rightStick.y < -minMovement);

		SetState(BUTTON_LEFT_TRIGGER, ms_gamepadState.leftTrigger > minMovement);
		SetState(BUTTON_RIGHT_TRIGGER, ms_gamepadState.rightTrigger > minMovement);

	}
	else
	{
		ZeroMemory(&ms_gamepadState, sizeof(eGamepadState));
		ms_gamepadState.lastButton = -1;
	}
}

int eGamepadManager::GetState(eGamepad_ButtonID buttonID)
{
	return ms_gamepadState.buttonState[buttonID] == false && ms_gamepadState.buttonStatePrev[buttonID] == true;
}

bool eGamepadManager::ButtonPressed(unsigned int button)
{
	return ms_gamepadState.rawState.Gamepad.wButtons & button;
}

void eGamepadManager::SetState(eGamepad_ButtonID buttonID, bool state)
{
	if (state)
		ms_gamepadState.lastButton = buttonID;

	ms_gamepadState.buttonState[buttonID] = state;
}

int eGamepadManager::GetNumPressedButtons()
{
	int buttons = 0;

	for (int i = 0; i < BUTTON_MAX; i++)
	{
		if (GetState((eGamepad_ButtonID)i))
			buttons++;
	}

	return buttons;
}

eGamepad_ButtonID eGamepadManager::GetLastButton()
{
	eGamepad_ButtonID button = (eGamepad_ButtonID)ms_gamepadState.lastButton;
	ms_gamepadState.lastButton = -1;
	return button;
}

const char* eGamepadManager::ButtonToString(int buttonID)
{
	static char buff[128] = {};

	switch (buttonID)
	{
	case BUTTON_A:
		sprintf_s(buff, "A");
		break;
	case BUTTON_B:
		sprintf_s(buff, "B");
		break;
	case BUTTON_X:
		sprintf_s(buff, "X");
		break;
	case BUTTON_Y:
		sprintf_s(buff, "Y");
		break;
	case BUTTON_LEFT_SHOULDER:
		sprintf_s(buff, "L1");
		break;
	case BUTTON_RIGHT_SHOULDER:
		sprintf_s(buff, "R1");
		break;
	case BUTTON_BACK:
		sprintf_s(buff, "Back");
		break;
	case BUTTON_START:
		sprintf_s(buff, "Start");
		break;
	case BUTTON_LEFT_THUMB:
		sprintf_s(buff, "L3");
		break;
	case BUTTON_RIGHT_THUMB:
		sprintf_s(buff, "R3");
		break;
	case BUTTON_DPAD_UP:
		sprintf_s(buff, "D-Pad Up");
		break;
	case BUTTON_DPAD_DOWN:
		sprintf_s(buff, "D-Pad Down");
		break;
	case BUTTON_DPAD_LEFT:
		sprintf_s(buff, "D-Pad Left");
		break;
	case BUTTON_DPAD_RIGHT:
		sprintf_s(buff, "D-Pad Right");
		break;
	case BUTTON_LEFT_STICK_UP:
		sprintf_s(buff, "L Stick Up");
		break;
	case BUTTON_LEFT_STICK_DOWN:
		sprintf_s(buff, "L Stick Down");
		break;
	case BUTTON_LEFT_STICK_RIGHT:
		sprintf_s(buff, "L Stick Right");
		break;
	case BUTTON_LEFT_STICK_LEFT:
		sprintf_s(buff, "L Stick Left");
		break;
	case BUTTON_RIGHT_STICK_UP:
		sprintf_s(buff, "R Stick Up");
		break;
	case BUTTON_RIGHT_STICK_DOWN:
		sprintf_s(buff, "R Stick Down");
		break;
	case BUTTON_RIGHT_STICK_RIGHT:
		sprintf_s(buff, "R Stick Right");
		break;
	case BUTTON_RIGHT_STICK_LEFT:
		sprintf_s(buff, "R Stick Left");
		break;
	case BUTTON_LEFT_TRIGGER:
		sprintf_s(buff, "L2");
		break;
	case BUTTON_RIGHT_TRIGGER:
		sprintf_s(buff, "R2");
		break;
	default:
		sprintf_s(buff, "Unknown");
		break;
	}

	return buff;
}

void eGamepadManager::Shutdown()
{
	if (hXInputDLL)
	{
		FreeLibrary(hXInputDLL);
		hXInputDLL = 0;
	}
}

DWORD __stdcall XInputGetState_Hook(DWORD dwUserIndex, XINPUT_STATE * pState)
{
	DWORD result = ERROR_DEVICE_NOT_CONNECTED;

	if (eGamepadManager::pXInputGetStateFunc)
		result = ((DWORD(WINAPI*)(DWORD, XINPUT_STATE*))(eGamepadManager::pXInputGetStateFunc))(dwUserIndex, pState);

	if (TheMenu->m_bIsActive)
		pState->Gamepad = {};

	return result;
}
