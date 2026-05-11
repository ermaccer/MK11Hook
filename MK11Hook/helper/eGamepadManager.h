#pragma once
#include <Windows.h>
#include <Xinput.h>
#include "..\gui\gui_impl.h"

struct eGamepadAnalogInput {
	float x, y;
};

enum eGamepad_ButtonID {
	BUTTON_A,
	BUTTON_B,
	BUTTON_X,
	BUTTON_Y,
	BUTTON_LEFT_SHOULDER,
	BUTTON_RIGHT_SHOULDER,
	BUTTON_BACK,
	BUTTON_START,
	BUTTON_LEFT_THUMB,
	BUTTON_RIGHT_THUMB,
	BUTTON_DPAD_UP,
	BUTTON_DPAD_DOWN,
	BUTTON_DPAD_LEFT,
	BUTTON_DPAD_RIGHT,
	BUTTON_DIGITAL_MAX, // store only digital buttons for booleans, more ids for last pressed key
	BUTTON_LEFT_STICK_UP,
	BUTTON_LEFT_STICK_DOWN,
	BUTTON_LEFT_STICK_RIGHT,
	BUTTON_LEFT_STICK_LEFT,
	BUTTON_RIGHT_STICK_UP,
	BUTTON_RIGHT_STICK_DOWN,
	BUTTON_RIGHT_STICK_RIGHT,
	BUTTON_RIGHT_STICK_LEFT,
	BUTTON_LEFT_TRIGGER,
	BUTTON_RIGHT_TRIGGER,
	BUTTON_MAX,

};


struct eGamepadState {
	bool buttonState[BUTTON_MAX];
	bool buttonStatePrev[BUTTON_MAX];

	float leftTrigger;
	float rightTrigger;
	eGamepadAnalogInput leftStick;
	eGamepadAnalogInput rightStick;

	XINPUT_STATE rawState;

	int lastButton;
};

class eGamepadManager {
public:
	static eGamepadState ms_gamepadState;
	
	static uintptr_t pXInputGetStateFunc;
	static HMODULE hXInputDLL;

	static void Initialize();
	static void Update();
	static void UpdateImGui();
	static void Reset();

	static void ToggleMenuWithGamepad();

	static void ProcessPad(int padNum = 0);
	static int  GetState(eGamepad_ButtonID buttonID);
	static bool ButtonPressed(unsigned int button);
	static void SetState(eGamepad_ButtonID buttonID, bool state);
	static int  GetNumPressedButtons();
	static eGamepad_ButtonID GetLastButton();

	static const char* ButtonToString(int buttonID);

	static void Shutdown();
};

DWORD WINAPI XInputGetState_Hook(DWORD dwUserIndex, XINPUT_STATE* pState);
