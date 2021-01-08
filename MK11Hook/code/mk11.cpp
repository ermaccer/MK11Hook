#include "mk11.h"
#include <iostream>
#include <Windows.h>
#include "mk11menu.h"
#include "eSettingsManager.h"

void __fastcall MK11Hooks::HookProcessStuff()
{
	TheMenu->Process();

	if (TheMenu->bSlowMotionEnabled)
		((void(__fastcall*)(float, int, int))_mk11addr(0x1405BEDD0))(TheMenu->fSlowMotionSpeed, 10, 0);

	if (TheMenu->bFreeCameraMovement)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->iFreeCameraRotSpeed;
	}

	((void(__fastcall*)())_mk11addr(0x1411518C0))();
}

void __fastcall MK11Hooks::HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	printf("MK11Hook::Info() | Starting a new fight!\n");
	TheMenu->bEnableCustomCameras = false;
	TheMenu->bCustomCamera = false;
	TheMenu->bCustomCameraRot = false;
	TheMenu->bYObtained = false;



	//((int64(__fastcall*)(int64, int64))_mk11addr(0x1405F8550))(MK11::GetCharacterInfo(PLAYER1), (int64)&name);

	//MK11::SetCharacter(PLAYER1, "char_spawn");
	((void(__fastcall*)(int64,int64,int64,int64))_mk11addr(0x141157850))(eventID,a2,a3,a4);

}

void __fastcall MK11Hooks::HookCamSetPos(int64 ptr, FVector * pos)
{
	float oneTime = 0.0f;
	if (!TheMenu->bYObtained)
	{
		oneTime = pos->Y;
		TheMenu->bYObtained = true;
	}
	if (TheMenu->bEnableCustomCameras)
	{
		FVector plrPos;
		FVector p2;
		MK11::GetCharacterPosition(&plrPos, PLAYER1);
		MK11::GetCharacterPosition(&p2, PLAYER2);
		switch (TheMenu->iCurrentCustomCamera)
		{
		case CAMERA_3RDPERSON:
			pos->X = 5;
			pos->Y = oneTime - 330.0f;
			pos->Y += plrPos.Y * 0.85f;
			pos->Z = 210.0f + plrPos.Z;

			if (p2.Y < plrPos.Y)
			{
				pos->Y += 600.0f;
				pos->Z = 210.0f;

			}


			TheMenu->camPos = *pos;
			break;
		case CAMERA_3RDPERSON2:
			pos->X = 5;
			pos->Y = oneTime - 230.0f;
			pos->Y += plrPos.Y * 0.85f;
			pos->Z = 260.0f + plrPos.Z;;

			if (p2.Y < plrPos.Y)
			{
				pos->Y += 600.0f;
				pos->Z = 260.0f;
			}


			TheMenu->camPos = *pos;
			break;
		case CAMERA_1STPERSON:
			pos->X = TheMenu->fAdjustCamX;
			pos->Y = -230;
			pos->Y += plrPos.Y - pos->Y;
			if (p2.Y < plrPos.Y)
				pos->Y += TheMenu->fAdjustCam * -1;
			else
				pos->Y += TheMenu->fAdjustCam;
			pos->Z = TheMenu->fAdjustCamZ + plrPos.Z;


			TheMenu->camPos = *pos;
			break;
		case CAMERA_1STPERSON_MID:
			pos->X = 16.0f;
			pos->Y = -230;
			pos->Y += plrPos.Y - pos->Y;
			if (p2.Y < plrPos.Y)
				pos->Y += 23.0f * -1;
			else
				pos->Y += 23.0f;
			pos->Z = 124.0f + plrPos.Z;


			TheMenu->camPos = *pos;
			break;
		}
		MK11::CamSetPos(ptr, pos);
	}
	else
	{

		if (!TheMenu->bCustomCamera)
		{
			TheMenu->camPos = *pos;
			MK11::CamSetPos(ptr, pos);
		}
		else
			MK11::CamSetPos(ptr, &TheMenu->camPos);
	}

}

void __fastcall MK11Hooks::HookCamSetRot(int64 ptr, FRotator * rot)
{
	if (TheMenu->bEnableCustomCameras)
	{
		FVector p1, p2;
		switch (TheMenu->iCurrentCustomCamera)
		{
		case CAMERA_3RDPERSON:
			rot->Pitch = -900;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK11::GetCharacterPosition(&p1, PLAYER1);
			MK11::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
				rot->Pitch = -900;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_3RDPERSON2:
			rot->Pitch = -4000;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK11::GetCharacterPosition(&p1, PLAYER1);
			MK11::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
				rot->Pitch = -4000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_1STPERSON:
			rot->Pitch = 0;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK11::GetCharacterPosition(&p1, PLAYER1);
			MK11::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_1STPERSON_MID:
			rot->Pitch = 0;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK11::GetCharacterPosition(&p1, PLAYER1);
			MK11::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
			}

			TheMenu->camRot = *rot;
			break;
		}

		MK11::CamSetRot(ptr, rot);
	}
	else 
	{
		if (!TheMenu->bCustomCameraRot)
		{
			TheMenu->camRot = *rot;
			MK11::CamSetRot(ptr, rot);
		}
		else
			MK11::CamSetRot(ptr, &TheMenu->camRot);
	}



}



int64 __fastcall MK11Hooks::HookLoadCharacter(int64 ptr, char * name)
{
	if (name)
	{
		if (!MK11::IsDLC(name))
		{
			if (TheMenu->bPlayer1ModifierEnabled)
			{
				if (ptr == MK11::GetPlayerData(PLAYER1))
				{
					char* original_name = name;
					printf("MK11Hook::Info() | Setting Player %d as %s\n", MK11::GetPlayerIDFromData(ptr), TheMenu->szPlayer1ModifierCharacter);
					strcpy((char*)(int64)&original_name[0], TheMenu->szPlayer1ModifierCharacter);
					strcpy((char*)(int64)&original_name[0], original_name);
					// crash fix
					TheMenu->bPlayer1ModifierEnabled = false;
				}
			}
			if (TheMenu->bPlayer2ModifierEnabled)
			{
				if (ptr == MK11::GetPlayerData(PLAYER2))
				{
					char* original_name = name;
					printf("MK11Hook::Info() | Setting Player %d as %s\n", MK11::GetPlayerIDFromData(ptr), TheMenu->szPlayer2ModifierCharacter);
					strcpy((char*)(int64)&original_name[0], TheMenu->szPlayer2ModifierCharacter);
					strcpy((char*)(int64)&original_name[0], original_name);
				}
			}
		}
	}
	
	

	return ((int64(__fastcall*)(int64, char*))_mk11addr(0x1408F7200))(ptr, name);

}

int64 MK11::GetCharacterObject(PLAYER_NUM plr)
{
	return ((int64(__fastcall*)(PLAYER_NUM))_mk11addr(0x1408F74D0))(plr);
}

int64 MK11::GetCharacterInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)_mk11addr(GFG_GAME_INFO);

	return ((int64(__fastcall*)(int64, PLAYER_NUM, int))_mk11addr(0x140568640))(gameinfo, plr, 0);
}

int64 MK11::GetPlayerData(PLAYER_NUM plr)
{
	int64 ptr = 0;
	int offset = 0;

	switch (plr)
	{
	case PLAYER1:
		offset = 0;
		break;
	case PLAYER2:
		offset = 8;
		break;
	default:
		break;
	}

	__int64 p_gameinfo = *(__int64*)_mk11addr(PLAYER_STRUCTS + offset);

	ptr = p_gameinfo;

	return ptr;
}

PLAYER_NUM MK11::GetPlayerIDFromData(int64 data)
{
	if (data == *(__int64*)_mk11addr(PLAYER_STRUCTS + 8))
		return PLAYER2;
	else
		return PLAYER1;
}

void MK11::GetCharacterDefinition(PLAYER_NUM plr)
{
	int64 object = GetCharacterObject(plr);
	int64 ptr = *(int64*)(object + 216);



}

void MK11::GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = GetCharacterInfo(plr);
	int64 ptr = *(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector*))_mk11addr(0x14114E580))(ptr, vec);
}

void MK11::LoadAsset(const char * name)
{
	printf("%s | %s [addr %x]\n", __FUNCTION__, name,(int64)&name[0]);
	((int64(__fastcall*)(char*))_mk11addr(0x14056F6C0))((char*)name);
}

void __fastcall MK11::CamSetPos(int64 ptr, FVector * pos)
{
	((void(__fastcall*)(int64, FVector*))_mk11addr(0x140E47FC0))(ptr, pos);
}

void __fastcall MK11::CamSetRot(int64 ptr, FRotator * rot)
{
	((void(__fastcall*)(int64, FRotator*))_mk11addr(0x140E48890))(ptr, rot);
}



const char* szCharactersDLC[] = {
	"CHAR_Terminator",
	"CHAR_Spawn",
	"CHAR_Sindel",
	"CHAR_ShaoKahn",
	"CHAR_Rambo",
	"CHAR_Robocop",
	"CHAR_Rain",
	"CHAR_ShangTsung",
	"CHAR_Joker",
	"CHAR_Fujin",
	"CHAR_Sheeva",
	"CHAR_CyberFrost",
	"CHAR_Nightwolf",
	"CHAR_Mileena",
};

bool MK11::IsDLC(const char * name)
{
	if (name)
	{
			for (int i = 0; i < sizeof(szCharactersDLC) / sizeof(szCharactersDLC[0]); i++)
	{
		if (strcmp(name, szCharactersDLC[i]) == 0)
		{
			printf("MKXHook::Info() | Cannot swap DLC characters!\n");
			return true;
		}
	}
	}

	return false;
}
