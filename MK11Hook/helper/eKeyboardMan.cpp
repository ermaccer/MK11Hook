#include "eKeyboardMan.h"
#include <iostream>
#include <Windows.h>
bool		   eKeyboardMan::ms_keyboardBuffer[VK_KEY_MAX];
bool		   eKeyboardMan::ms_keyboardBufferJustPressed[VK_KEY_MAX];
int			   eKeyboardMan::ms_lastKey = 0;

eVKKeyCode eKeyboardMan::GetLastKey()
{
	return (eVKKeyCode)ms_lastKey;
}

const char* eKeyboardMan::KeyToString(int code)
{
	static char buff[128] = {};
	UINT key = MapVirtualKey(code, MAPVK_VK_TO_VSC);

	int result = GetKeyNameTextA((key << 16), buff, sizeof(buff));

	if (code == VK_UP)
		return "Up";
	else if (code == VK_DOWN)
		return "Down";
	else if (code == VK_LEFT)
		return "Left";
	else if (code == VK_RIGHT)
		return "Right";
	else if (result)
		return buff;
	else
		return "Unknown";
}

void eKeyboardMan::SetKeyStatus(int vkKey, bool isDown)
{
	if (!(vkKey >= 0 && vkKey < VK_KEY_MAX))
		return;


	ms_keyboardBuffer[vkKey] = isDown;
	ms_keyboardBufferJustPressed[vkKey] = isDown;
}

void eKeyboardMan::SetLastPressedKey(int vkKey)
{
	ms_lastKey = vkKey;
}

void eKeyboardMan::ResetKeys()
{
	ZeroMemory(ms_keyboardBuffer, sizeof(ms_keyboardBuffer));
	ZeroMemory(ms_keyboardBufferJustPressed, sizeof(ms_keyboardBufferJustPressed));
}

int eKeyboardMan::GetKeyState(int vkKey)
{
	if (!(vkKey >= 0 && vkKey < VK_KEY_MAX))
		return 0;

	int state = 0x0;

	if (ms_keyboardBufferJustPressed[vkKey])
	{
		state |= 0x1;
		ms_keyboardBufferJustPressed[vkKey] = false;
	}

	if (ms_keyboardBuffer[vkKey])
		state |= 0x8000;


	return state;
}

int eKeyboardMan::GetNumPressedKeys()
{
	int keys = 0;

	for (int i = 0; i < VK_KEY_MAX; i++)
	{
		if (GetKeyState(i))
			keys++;
	}

	return keys;
}

void eKeyboardMan::OnFocusLost()
{
	ResetKeys();
	SetLastPressedKey(0);
}
