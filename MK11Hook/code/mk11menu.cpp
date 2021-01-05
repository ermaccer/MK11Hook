#include "mk11menu.h"
#include <Windows.h>
#include "mk10utils.h"
#include <iostream>

static int64 timer = GetTickCount64();

MK11Menu* TheMenu = new MK11Menu();

void MK11Menu::Initialize()
{
	bSlowMotionEnabled = 0;
	fSlowMotionSpeed = 0.5f;
}

void MK11Menu::Process()
{
	UpdateControls();
}

void MK11Menu::UpdateControls()
{
	if (GetAsyncKeyState(VK_F5))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		bSlowMotionEnabled ^= 1;
		printf("Slowmotion status %d\n", bSlowMotionEnabled);
	}

	if (bSlowMotionEnabled)
	{
		if (GetAsyncKeyState(VK_F6))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			fSlowMotionSpeed += 0.1f;
			printf("Current speed %f\n",fSlowMotionSpeed);
		}
		if (GetAsyncKeyState(VK_F7))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			fSlowMotionSpeed -= 0.1f;
			printf("Current speed %f\n", fSlowMotionSpeed);
		}
	}

}
