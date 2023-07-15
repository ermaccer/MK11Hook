#include "eGamepadManager.h"
#include "../plugin/Menu.h"
#include "../utils.h"
#include "../gui/imgui/imgui.h"
#include "../gui/gui_impl.h"
#include "../gui/log.h"

bool eGamepadManager::m_bEstablishedConnection = false;
static int64 gamepad_timer = GetTickCount64();

uintptr_t eGamepadManager::pXInputGetStateFunc = 0;
HMODULE eGamepadManager::hXInputDLL = 0;

eGamepadManager* TheGamepad = new eGamepadManager();
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
bool eGamepadManager::IsConnected()
{
	XINPUT_STATE p1 = {};


	if (pXInputGetStateFunc)
		return ((DWORD(WINAPI*)(DWORD, XINPUT_STATE*))(pXInputGetStateFunc))(0, &p1) == ERROR_SUCCESS;


	return false;
}

XINPUT_STATE eGamepadManager::GetGamepad()
{
	XINPUT_STATE p1 = {};
	if (IsConnected())
	{
		if (!m_bEstablishedConnection)
			m_bEstablishedConnection = true;

		if (pXInputGetStateFunc)
			((DWORD(WINAPI*)(DWORD, XINPUT_STATE*))(pXInputGetStateFunc))(0, &p1);
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

void eGamepadManager::Shutdown()
{
	if (hXInputDLL)
	{
		FreeLibrary(hXInputDLL);
		hXInputDLL = 0;
	}
}


void GamepadThread()
{
	while (true)
	{
		if (TheGamepad->IsConnected() && GUIImplementation::ms_bInit)
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
	DWORD result = ERROR_DEVICE_NOT_CONNECTED;

	if (eGamepadManager::pXInputGetStateFunc)
		result = ((DWORD(WINAPI*)(DWORD, XINPUT_STATE*))(eGamepadManager::pXInputGetStateFunc))(dwUserIndex, pState);

	if (TheMenu->m_bIsActive)
		pState->Gamepad = {};

	return result;
}
