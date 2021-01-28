#include "mk11menu.h"
#include <Windows.h>
#include "mk10utils.h"
#include "mk11.h"
#include <iostream>
#include "..\imgui\imgui.h"
#include "eSettingsManager.h"
#include "..\utils\MemoryMgr.h"

static int64 timer = GetTickCount64();
static int64 func_timer = GetTickCount64();
char textBuffer[260] = {};
const char* szCharacters[] = {
	// place npcs first for easy access
	"CHAR_Cyrax",
	"CHAR_Sektor",
	"CHAR_FireGod",
	"CHAR_Kronika",
	// rest of the cast
	"CHAR_Baraka",
	"CHAR_Cage",
	"CHAR_Cassie",
	"CHAR_Cetrion",
	"CHAR_DVorah",
	"CHAR_ErronBlack",
	"CHAR_Jacqui",
	"CHAR_Jade",
	"CHAR_Jax",
	"CHAR_Kabal",
	"CHAR_Kano",
	"CHAR_Kitana",
	"CHAR_Kollector",
	"CHAR_Kotal",
	"CHAR_Kronika",
	"CHAR_KungLao",
	"CHAR_LiuKang",
	"CHAR_Noob",
	"CHAR_Raiden",
	"CHAR_Scorpion",
	"CHAR_Skarlet",
	"CHAR_Sonya",
	"CHAR_SubZero",
	"CHAR_Terminas"

};

const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Third Person",
	"Third Person #2",
	"First Person",
	"First Person Mid",
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
	bPlayer1ModifierEnabled = false;
	bPlayer2ModifierEnabled = false;

	bCustomCamera = false;
	bCustomCameraRot = false;
	bCustomFOV = false;
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
	fAdjustCam3 = 0;
	fAdjustCamX3 = 0;
	fAdjustCamZ3 = 0;
	camFov = 0;
	sprintf(szCurrentCameraOption, szCameraModes[0]);

	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	orgMouse.x = GetSystemMetrics(SM_CXSCREEN) / 2;
	orgMouse.y = GetSystemMetrics(SM_CYSCREEN) / 2;
	mouseSpeedX = 0;
	mouseSpeedY = 0;
	mouseScroll = 0;
	mouseSens = 5;
	bInvertMouseY = true;
	bFreezeWorld = false;
	bFocused = false;
	bAboutWindow = false;

	bChangePlayerSpeed = false;
	fPlayer1Speed = 1.0f;
	fPlayer2Speed = 1.0f;


	bInfiniteHealthPlayer1 = false;
	bInfiniteHealthPlayer2 = false;
	bInfiniteSuperBarPlayer1 = false;
	bInfiniteSuperBarPlayer2 = false;
}

void MK11Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetMK11HookVersion());
	if (ImGui::Button("Character Modifier")) iCurrentTab = TAB_CHARACTER_MODIFIER;
	ImGui::SameLine();
	if (ImGui::Button("Speed Modifier")) iCurrentTab = TAB_SPEED;
	ImGui::SameLine();
	if (ImGui::Button("Player Control")) iCurrentTab = TAB_PLAYER_CONTROL;
	ImGui::SameLine();
	if (ImGui::Button("Camera Control")) iCurrentTab = TAB_CAMERA;
	ImGui::SameLine();
	if (ImGui::Button("Cheats")) iCurrentTab = TAB_CHEATS;
	ImGui::SameLine();
	if (ImGui::Button("Misc.")) iCurrentTab = TAB_MISC;
	ImGui::Separator();


	if (iCurrentTab == TAB_CHARACTER_MODIFIER)
	{
		ImGui::Checkbox("Enable Player 1 Modifier", &bPlayer1ModifierEnabled);
		ImGui::SameLine(); ShowHelpMarker("Should work in all game modes, to reset character cell (in case it gets stuck) please exit and enter game mode again, or just select original character from modifier list. You'll most likely need a gamepad for tower modes. NB: Doesn't work with DLC characters!");

		if (ImGui::BeginCombo("Player 1 Character", szPlayer1ModifierCharacter))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
			{
				bool is_selected = (szPlayer1ModifierCharacter == szCharacters[n]);
				if (ImGui::Selectable(szCharacters[n], is_selected))
					sprintf(szPlayer1ModifierCharacter, szCharacters[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();

			}
			ImGui::EndCombo();
		}
		ImGui::Separator();
		ImGui::Checkbox("Enable Player 2 Modifier", &bPlayer2ModifierEnabled);

		if (ImGui::BeginCombo("Player 2 Character", szPlayer2ModifierCharacter))
		{
			for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
			{
				bool is_selected = (szPlayer2ModifierCharacter == szCharacters[n]);
				if (ImGui::Selectable(szCharacters[n], is_selected))
					sprintf(szPlayer2ModifierCharacter, szCharacters[n]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::Separator();


	}

	if (iCurrentTab == TAB_SPEED)
	{
		ImGui::Text("Gamespeed Control");
		ImGui::InputFloat("", &fSlowMotionSpeed, 0.1);

		if (fSlowMotionSpeed > 2.0f) fSlowMotionSpeed = 2.0f;
		if (fSlowMotionSpeed < 0.0f) fSlowMotionSpeed = 0.0f;
		ImGui::Checkbox("Enable", &bSlowMotionEnabled);

		ImGui::Separator();
	}
	if (iCurrentTab == TAB_CAMERA)
	{
		ImGui::Checkbox("Custom Camera Position", &bCustomCamera);
		ImGui::InputFloat3("X | Y | Z", &camPos.X);
		ImGui::Checkbox("Custom Camera Rotation", &bCustomCameraRot);
		ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);
		if (SettingsMgr->bGlobalCameraHook)
		{
			ImGui::Checkbox("Custom FOV", &bCustomFOV);
			ImGui::InputFloat("FOV", &camFov);
		}
		ImGui::Separator();
		ImGui::Checkbox("Enable Freecam", &bFreeCameraMovement);
		ImGui::SameLine(); ShowHelpMarker("Requires both toggles enabled!\n You can configure keys in .ini file.");
		ImGui::InputFloat("Freecam Speed", &fFreeCameraSpeed);
		ImGui::InputInt("Freecam Rotation Speed", &iFreeCameraRotSpeed);

		if (bFreeCameraMovement)
		{
			ImGui::Separator();
			ImGui::Checkbox("Mouse Control", &bEnableMouseControl);

			if (bEnableMouseControl)
			{
				ImGui::Checkbox("Invert Y", &bInvertMouseY);
				ImGui::SliderInt("Mouse Smoothness", &mouseSens, 1, 15);
			}
		}


		ImGui::Separator();
		if (MK11::GetCharacterObject(PLAYER1) && MK11::GetCharacterObject(PLAYER2))
		{
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
			if (iCurrentCustomCamera == CAMERA_1STPERSON || iCurrentCustomCamera == CAMERA_1STPERSON_MID)
			{
				ImGui::InputFloat("FPS Camera Offset", &fAdjustCam);
				ImGui::InputFloat("FPS Up/Down Offset", &fAdjustCamZ);
				ImGui::InputFloat("FPS Left/Right Offset", &fAdjustCamX);
			}
			else if (iCurrentCustomCamera == CAMERA_3RDPERSON)
			{
				ImGui::InputFloat("TPP Camera Offset", &fAdjustCam3);
				ImGui::InputFloat("TPP Up/Down Offset", &fAdjustCamZ3);
				ImGui::InputFloat("TPP Left/Right Offset", &fAdjustCamX3);
			}
		}
		else
			ImGui::Text("Custom cameras will appear once ingame!");
		
	}
	if (iCurrentTab == TAB_PLAYER_CONTROL)
	{
		ImGui::Checkbox("Change Player Speed", &bChangePlayerSpeed);
		ImGui::SliderFloat("Player 1", &fPlayer1Speed, 0.0, 10.0f);
		ImGui::SliderFloat("Player 2", &fPlayer2Speed, 0.0, 10.0f);

		bool reset = ImGui::Button("Reset Speed");
		if (reset)
		{
			fPlayer1Speed = 1.0f;
			fPlayer2Speed = 1.0f;
		}
		ImGui::Separator();
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
	if (iCurrentTab == TAB_MISC)
	{
		if (ImGui::Button("Hide FightHUD"))
			MK11::HideHUD();
		ImGui::SameLine();
		if (ImGui::Button("Show FightHUD"))
			MK11::ShowHUD();
		ImGui::SameLine();

	}
	if (iCurrentTab == TAB_CHEATS)
	{
		ImGui::Text("Player 1");
		ImGui::Separator();
		ImGui::Checkbox("Infinite Health", &bInfiniteHealthPlayer1);
		ImGui::Separator();

		ImGui::Text("Player 2");
		ImGui::Separator();
		ImGui::Checkbox("Infinite Health ", &bInfiniteHealthPlayer2);
		ImGui::Separator();
		//ImGui::Checkbox("Infinite Timer", &bStopTimer);
	}



}

void MK11Menu::Process()
{
	UpdateControls();
	if (bFocused && bEnableMouseControl)
	UpdateMouse();
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
	}

	if (bSlowMotionEnabled)
	{
		if (GetAsyncKeyState(VK_F6))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			fSlowMotionSpeed += 0.1f;
		}
		if (GetAsyncKeyState(VK_F7))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			fSlowMotionSpeed -= 0.1f;
		}
	}

}

void MK11Menu::UpdateMouse()
{
	if (bIsActive) return;

	GetCursorPos(&curMouse);
	mouseSpeedX = curMouse.x - orgMouse.x;
	mouseSpeedY = curMouse.y - orgMouse.y;


	if (bFocused)
	{
		if (TheMenu->bFreeCameraMovement)
		{
			float newVal = TheMenu->camRot.Yaw;
			newVal += mouseSpeedX / mouseSens;
			TheMenu->camRot.Yaw = newVal;


			float newValY = TheMenu->camRot.Pitch;

			if (bInvertMouseY) mouseSpeedY *= -1;

			newValY += mouseSpeedY / mouseSens;
			TheMenu->camRot.Pitch = newValY;
		}
	}

}

bool MK11Menu::GetActiveState()
{
	return bIsActive;
}

char * GetMK11HookVersion()
{
	char buffer[512];
	sprintf(buffer, "MK11Hook by ermaccer (%s)", MK11HOOK_VERSION);
	return buffer;
}
