#include "mk11menu.h"
#include <Windows.h>
#include "mk10utils.h"
#include <iostream>
#include "..\imgui\imgui.h"

static int64 timer = GetTickCount64();

const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Third Person",
	"Third Person #2",
	"First Person",
	"First Person Mid"
};

int GetCamMode(const char* mode)
{
	for (int i = 0; i < TOTAL_CUSTOM_CAMERAS; i++)
	{
		if (strcmp(mode, szCameraModes[i]) == 0)
		{
			return i;
			break;
		}
	}
	return -1;
}


MK11Menu* TheMenu = new MK11Menu();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void MK11Menu::Initialize()
{
	bCustomCamera = false;
	bCustomCameraRot = false;
	iCurrentTab = 0;
	bSlowMotionEnabled = 0;
	fSlowMotionSpeed = 0.5f;

	bYObtained = false;
	fFreeCameraSpeed = 5.25f;
	iFreeCameraRotSpeed = 120;
	bEnableCustomCameras = false;
	iCurrentCustomCamera = -1;
	fAdjustCamZ = 161.0f;
	fAdjustCamX = -10.0f;
	sprintf(szCurrentCameraOption, szCameraModes[0]);
}

void MK11Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin("MK11Hook by ermaccer (0.1)");

	if (ImGui::Button("Speed Modifier")) iCurrentTab = TAB_SPEED;
	ImGui::SameLine();
	if (ImGui::Button("Player Control")) iCurrentTab = TAB_PLAYER_CONTROL;
	ImGui::SameLine();
	if (ImGui::Button("Camera Control")) iCurrentTab = TAB_CAMERA;
	ImGui::Separator();

	if (iCurrentTab == TAB_SPEED)
	{
		ImGui::Text("Gamespeed Control");
		ImGui::InputFloat("", &fSlowMotionSpeed, 0.1);

		if (fSlowMotionSpeed > 2.0f) fSlowMotionSpeed = 2.0f;
		if (fSlowMotionSpeed < 0.0f) fSlowMotionSpeed = 0.0f;
		ImGui::Checkbox("Enable", &bSlowMotionEnabled);
	}
	if (iCurrentTab == TAB_CAMERA)
	{
		ImGui::Checkbox("Custom Camera Position", &bCustomCamera);
		ImGui::InputFloat3("X | Y | Z", &camPos.X);
		ImGui::Checkbox("Custom Camera Rotation", &bCustomCameraRot);
		ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);
		ImGui::Checkbox("Enable Freecam", &bFreeCameraMovement);
		ImGui::SameLine(); ShowHelpMarker("Requires both toggles enabled!\n You can configure keys in .ini file.");
		ImGui::InputFloat("Freecam Speed", &fFreeCameraSpeed);
		ImGui::InputInt("Freecam Rotation Speed", &iFreeCameraRotSpeed);


		ImGui::Separator();

		ImGui::Checkbox("Custom Cameras", &bEnableCustomCameras);

		if (ImGui::BeginCombo("Mode", szCurrentCameraOption))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szCameraModes); n++)
			{
				bool is_selected = (szCurrentCameraOption == szCameraModes[n]);
				if (ImGui::Selectable(szCameraModes[n], is_selected))
					sprintf(szCurrentCameraOption, szCameraModes[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		iCurrentCustomCamera = GetCamMode(szCurrentCameraOption);
		ImGui::InputFloat("FPS Camera Offset", &fAdjustCam);
		ImGui::InputFloat("FPS Up/Down Offset", &fAdjustCamZ);
		ImGui::InputFloat("FPS Left/Right Offset", &fAdjustCamX);
	}
	if (iCurrentTab == TAB_PLAYER_CONTROL)
	{
		ImGui::Text("Position");
		ImGui::SameLine(); ShowHelpMarker("Preview only!");
		if (MK11::GetCharacterObject(PLAYER1))
		{
			MK11::GetCharacterPosition(&plrPos, PLAYER1);
			ImGui::InputFloat3("X | Y | Z", &plrPos.X);
		}
		if (MK11::GetCharacterObject(PLAYER2))
		{
			MK11::GetCharacterPosition(&plrPos2, PLAYER2);
			ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
		}




	}
}

void MK11Menu::Process()
{
	UpdateControls();
}

void MK11Menu::UpdateControls()
{

	if (GetAsyncKeyState(VK_F1))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		bIsActive ^= 1;
	}

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

bool MK11Menu::GetActiveState()
{
	return bIsActive;
}
