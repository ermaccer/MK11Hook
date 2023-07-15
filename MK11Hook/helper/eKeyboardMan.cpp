#include "eKeyboardMan.h"
#include <iostream>
#include <Windows.h>


eVKKeyCode eKeyboardMan::GetLastKey()
{
	eVKKeyCode key = VK_KEY_NULL;
	for (int i = 0; i < VK_KEY_MAX; i++)
	{
		if (GetKeyState(i) & 0x8000)
		{
			key = (eVKKeyCode)i;
			break;
		}
	}
	return key;
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
