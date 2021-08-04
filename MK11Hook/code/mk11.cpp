#include "mk11.h"
#include <iostream>
#include <Windows.h>
#include "mk11menu.h"
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include "MKCharacter.h"
#include "MKModifier.h"
#include "mkcamera.h"

int64 hud_property = 0;

void __fastcall MK11Hooks::HookProcessStuff()
{
	TheMenu->Process();
	Notifications->Update();

	if (TheMenu->bSlowMotionEnabled)
		MK11::SlowGameTimeForXTicks(TheMenu->fSlowMotionSpeed, 10);

	if (TheMenu->bChangePlayerSpeed)
	{
		if (MK11::GetCharacterObject(PLAYER1))
			MK11::GetCharacterObject(PLAYER1)->SetSpeed(TheMenu->fPlayer1Speed);
		if (MK11::GetCharacterObject(PLAYER2))
			MK11::GetCharacterObject(PLAYER2)->SetSpeed(TheMenu->fPlayer2Speed);
	}
	if (TheMenu->bChangePlayerScale)
	{
		if (MK11::GetCharacterObject(PLAYER1))
			MK11::GetCharacterObject(PLAYER1)->SetScale(&TheMenu->fPlayer1Scale);
		if (MK11::GetCharacterObject(PLAYER2))
			MK11::GetCharacterObject(PLAYER2)->SetScale(&TheMenu->fPlayer2Scale);
	}


	if (MK11::GetCharacterObject(PLAYER1))
	{
		if (TheMenu->bInfiniteHealthPlayer1)
			MK11::GetCharacterObject(PLAYER1)->SetLife(1000.0f);

		if (TheMenu->bNoHealthPlayer1)
			MK11::GetCharacterObject(PLAYER1)->SetLife(0.0f);
		if (TheMenu->b1HealthPlayer1)
			MK11::GetCharacterObject(PLAYER1)->SetLife(0.01f);

		if (TheMenu->bInfiniteAttackBarPlayer1)
		{
			if (MK11::GetCharacterInfo(PLAYER1))
				MK11::SetCharacterEnergy(MK11::GetCharacterInfo(PLAYER1), BAR_Offensive, 1000.0f);
		}

		if (TheMenu->bInfiniteDefendBarPlayer1)
		{
			if (MK11::GetCharacterInfo(PLAYER1))
				MK11::SetCharacterEnergy(MK11::GetCharacterInfo(PLAYER1), BAR_Defensive, 1000.0f);
		}

		if (TheMenu->bAutoHideHUD)
			MK11::HideHUD();
	}


	if (MK11::GetCharacterObject(PLAYER2))
	{
		if (TheMenu->bInfiniteHealthPlayer2)
			MK11::GetCharacterObject(PLAYER2)->SetLife(1000.0f);

		if (TheMenu->bNoHealthPlayer2)
			MK11::GetCharacterObject(PLAYER2)->SetLife(0.0f);
		if (TheMenu->b1HealthPlayer2)
			MK11::GetCharacterObject(PLAYER2)->SetLife(0.01f);

		if (TheMenu->bInfiniteAttackBarPlayer2)
		{
			if (MK11::GetCharacterInfo(PLAYER2))
				MK11::SetCharacterEnergy(MK11::GetCharacterInfo(PLAYER2), BAR_Offensive, 1000.0f);
		}

		if (TheMenu->bInfiniteDefendBarPlayer2)
		{
			if (MK11::GetCharacterInfo(PLAYER2))
				MK11::SetCharacterEnergy(MK11::GetCharacterInfo(PLAYER2), BAR_Defensive, 1000.0f);
		}
	}
	

	if (!(MK11::GetCharacterObject(PLAYER1)) || !(MK11::GetCharacterObject(PLAYER2)))
	{
		if (TheMenu->bEnableCustomCameras)
			TheMenu->bEnableCustomCameras = false;
	}

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

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			TheMenu->camFov -= 1.0f;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			TheMenu->camFov += 1.0f;
	}


	if (TheMenu->bForceMoveCamera)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			TheCamera->SetFOV(TheMenu->camFov);
		}

	}

	((void(__fastcall*)())_addr(0x141153C50))();
}

void MK11Hooks::PreLoadHook(int64 a1, int64 a2, int a3)
{
	((void(__fastcall*)(int64, int64, int))_addr(0x1408FCDB0))(a1,a2,a3);
}

void __fastcall MK11Hooks::HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	printf("MK11Hook::Info() | Starting a new fight!\n");
	TheMenu->bEnableCustomCameras = false;
	TheMenu->bCustomCamera = false;
	TheMenu->bCustomCameraRot = false;
	TheMenu->bYObtained = false;

	if (TheMenu->bStageModifier)
		MK11::SetStage(TheMenu->szStageModifierStage);

	if (TheMenu->iCharacterModifierMode == MODIFIER_FIGHT)
	{
		if (TheMenu->bPlayer1ModifierEnabled)
			MK11::SetCharacterMKX(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
		if (TheMenu->bPlayer2ModifierEnabled)
			MK11::SetCharacterMKX(PLAYER2, TheMenu->szPlayer2ModifierCharacter);
	}


	if (TheMenu->bEnableTagAssistModifier)
	{
		TagAssistModifier tag(TheMenu->szPlayer1TagAssistCharacter);
		tag.Activate(MK11::GetCharacterInfo(PLAYER1));

		TagAssistModifierObject* obj = tag.CreateObject();

		if (obj)
			obj->Activate(MK11::GetCharacterObject(PLAYER1));

		MK11::GetModifierManager()->ActivateModifier(&tag, MK11::GetCharacterObject(PLAYER1));
		MK11::LoadModifierAssets();
		printf("MK11Hook::Info() | P1 Tag Assist: %s\n", TheMenu->szPlayer1TagAssistCharacter);
	}
	if (TheMenu->bEnableTagAssistModifierPlayer2)
	{
		TagAssistModifier tag(TheMenu->szPlayer2TagAssistCharacter);
		tag.Activate(MK11::GetCharacterInfo(PLAYER2));

		TagAssistModifierObject* obj = tag.CreateObject();

		if (obj)
			obj->Activate(MK11::GetCharacterObject(PLAYER2));

		MK11::GetModifierManager()->ActivateModifier(&tag, MK11::GetCharacterObject(PLAYER2));
		MK11::LoadModifierAssets();
		printf("MK11Hook::Info() | P2 Tag Assist: %s\n", TheMenu->szPlayer2TagAssistCharacter);
	}

	printf("MK11Hook::Info() | %s VS %s\n", MK11::GetCharacterName(PLAYER1), MK11::GetCharacterName(PLAYER2));




	((void(__fastcall*)(int64,int64,int64,int64))_addr(0x141159BE0))(eventID,a2,a3,a4);

}

void MK11Hooks::PostLoadHook()
{

	((int64(__fastcall*)())_addr(0x14090F7A0))();
}

int64 __fastcall MK11Hooks::HookLoadCharacter(int64 ptr, char * name)
{
	printf("%x\n", (int64)&name[0]);
	if (TheMenu->iCharacterModifierMode == MODIFIER_SCREEN)
	{
		if (name)
		{
			if (!MK11::IsDLC(name))
			{
				if (TheMenu->bPlayer1ModifierEnabled)
				{
					if (ptr == MK11::GetCharacterInfo(PLAYER1))
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
					if (ptr == MK11::GetCharacterInfo(PLAYER2))
					{
						char* original_name = name;
						printf("MK11Hook::Info() | Setting Player %d as %s\n", MK11::GetPlayerIDFromData(ptr), TheMenu->szPlayer2ModifierCharacter);
						strcpy((char*)(int64)&original_name[0], TheMenu->szPlayer2ModifierCharacter);
						strcpy((char*)(int64)&original_name[0], original_name);
						TheMenu->bPlayer2ModifierEnabled = false;
					}
				}
			}
		}

	}
	return ((int64(__fastcall*)(int64, char*))_addr(0x1408F8830))(ptr, name);

}

int64 MK11Hooks::HookSetProperty(int64 ptr, char * name, int64 unk)
{
	hud_property = ptr;
	return ((int64(__fastcall*)(int64, char*, int64))_addr(0x141A6B8B0))(ptr,name,unk);
}

void MK11Hooks::HookReadPropertyValue(int64 ptr, int* unk, int* value)
{
	int input = *value;
	if (ptr == hud_property)
	{
		if (TheMenu->bForceDisableHUD)
			input ^= 1;
	}


	*unk = *(int*)(ptr + 408) & input | *unk & ~*(int*)(ptr + 408);
}

int64 MK11Hooks::HookLoadouts(int64 ptr)
{
	if (TheMenu->bDisableGearLoadouts)
		return true;
	else
		return ((int64(__fastcall*)(int64))_addr(0x14086F930))(ptr);
}

void MK11Hooks::HookDispatch(int64 ptr, int a2)
{
	if (TheMenu->bHookDispatch)
	{
		int64 arg = *(int64*)(ptr);

		if (!TheMenu->bFreezeWorld)
			a2 = *(uint32_t*)(ptr + 0x18);

		if (*(uint32_t*)(ptr + 0x14) == a2)
			return;

		*(int*)(ptr + 0x14) = a2;
		((void(*)(int64, int))*(int64*)(arg + 0xD8))(ptr, a2);
	}
	else	
		((int64(__fastcall*)(int64,int))_addr(0x141172F20))(ptr,a2);

}

void MK11Hooks::HookSetSelectScreen(int64 ptr, PLAYER_NUM  plr, int teamNo, char * name, int level, int64 loadout, bool altPalette)
{
	if (plr <= 1 && teamNo <= 3)
	{
		int64 chr = 120 * ((int)teamNo + 4i64 * (int)plr) + ptr + 448;

		if (TheMenu->iCharacterModifierMode == MODIFIER_SCREEN && (TheMenu->bPlayer1ModifierEnabled || TheMenu->bPlayer2ModifierEnabled))
		{
			if (name)
			{

				switch (plr)
				{
				case PLAYER1:
					if (TheMenu->bPlayer1ModifierEnabled)
						name = TheMenu->szPlayer1ModifierCharacter;
					break;
				case PLAYER2:
					if (TheMenu->bPlayer2ModifierEnabled)
						name = TheMenu->szPlayer2ModifierCharacter;
					break;
				default:
					break;
				}
			}
		}


		MK11::SetCharacter(chr, name, 0, 0);

		MK11::SetCharacterLevel(chr, level);
		MK11::SetCharacterAltPal(chr, altPalette);
		if (loadout)
			MK11::SetCharacterLoadout(chr, loadout);
	}

}

void MK11Hooks::HookSetLadderScreen(int64 chr, char * name, int64 ptr, int64 unk)
{
	if (TheMenu->bPlayer1ModifierEnabled)
		name = TheMenu->szPlayer1ModifierCharacter;
	MK11::SetCharacter(chr, name, ptr, unk);
}

MKCharacter* MK11::GetCharacterObject(PLAYER_NUM plr)
{
	return ((MKCharacter*(__fastcall*)(PLAYER_NUM))_addr(0x1408F8B00))(plr);
}

int64 MK11::GetCharacterInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	return ((int64(__fastcall*)(int64, PLAYER_NUM))_addr(0x14056F130))(gameinfo, plr);
}

int64 MK11::GetPlayerData(PLAYER_NUM plr)
{
	return GetCharacterInfo(plr);
}

PLAYER_NUM MK11::GetPlayerIDFromData(int64 data)
{
	if (data == GetCharacterInfo(PLAYER2))
		return PLAYER2;
	else
		return PLAYER1;
}


void MK11::GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = GetCharacterInfo(plr);
	int64 ptr = *(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector*))_addr(0x141150910))(ptr, vec);
}

void MK11::HideHUD()
{
	((void(__fastcall*)(int, int))_addr(0x1408F5550))(8, 8);
}

void MK11::ShowHUD()
{
	((void(__fastcall*)(int, int))_addr(0x1408F5E90))(8, 8);
}

void MK11::SetCharacterMKX(PLAYER_NUM plr,char * name)
{
	int64 ptr = GetCharacterInfo(plr);
	int64 chr = (ptr + 216);
	MK11::SetCharacter(chr, name, 0,0);
}

void MK11::SetCharacter(int64 chr, char * name, int64 ptr, int64 unk)
{
	((void(__fastcall*)(int64, const char*, int64, int64))_addr(0x1405982F0))(chr, name, ptr, unk);

}

void MK11::SetCharacterLevel(int64 chr, int level)
{
	((void(__fastcall*)(int64, int))_addr(0x1405997C0))(chr, level);
}

void MK11::SetCharacterAltPal(int64 chr, int value)
{

	((void(__fastcall*)(int64, int))_addr(0x14059DE20))(chr, value);
}

void MK11::SetCharacterLoadout(int64 chr, int64 loadout)
{
	((void(__fastcall*)(int64, int64))_addr(0x1405998F0))(chr, loadout);
}


char * MK11::GetCharacterName(PLAYER_NUM plr)
{
	int64 info = GetCharacterInfo(plr);
	character_info* chr = *(character_info**)(info + 216);

	return chr->name;
}



void MK11::SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, int, int))_addr(0x1405C04A0))(speed, ticks, 0);
}

void MK11::SetSpeed(float speed)
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	((void(__fastcall*)(int64, float))_addr(0x140599510))(gameinfo, speed);
}

void MK11::SetCharacterEnergy(int64 obj, int type, float energy)
{
	((void(__fastcall*)(int64, int, float))_addr(0x1405FA670))(obj, type, energy);
}

void MK11::SetStage(const char * stage)
{
	__int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, const char*))_addr(0x140599CA0))(gameinfo, stage);
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
				if (TheMenu->bPlayer1ModifierEnabled)
				{
					printf("MK11Hook::Info() | Cannot swap DLC characters!\n");
					Notifications->SetNotificationTime(5500);
					Notifications->PushNotification("Cannot swap DLC characters!");
				}

				return true;
			}
		}
	}

	return false;
}

void MK11::SetKryptCharacter(int64 ptr, char * name)
{
	if (TheMenu->bChangeKryptCharacter)
		name = TheMenu->szCurrentKryptCharacter;

	printf("MK11Hook::SetKryptCharacter() | Loading character %s\n", name);

	((void(__fastcall*)(int64, char*))_addr(0x140821CD0))(ptr, name);
}

void MK11::SetKryptCharacterL(int64 ptr, char * name, int unk)
{
	//if (TheMenu->bChangeKryptCharacter)
	//	name = 0;
	((void(__fastcall*)(int64, char*, int))_addr(0x141A69CC0))(ptr, name, unk);
}

void MK11::SetKryptCharacterClass(int64 ptr, char * name, int unk)
{
	if (TheMenu->bChangeKryptCharacter)
		name = TheMenu->szCurrentKryptCharacterClass;
	((void(__fastcall*)(int64, char*, int))_addr(0x142395E20))(ptr, name, unk);
}

MKModifier* MK11::GetModifierManager()
{
	int64 info = ((int64(__fastcall*)())_addr(0x140679670))();
	return ((MKModifier*(__fastcall*)(int64))_addr(0x14067B240))(info);
}

void MK11::LoadModifierAssets()
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	((void(__fastcall*)(int64, bool))_addr(0x14057D590))(gameinfo, 1);

}

void MK11::mk_sleep(int64 duration)
{
	((void(__fastcall*)(int64))_addr(0x1411544D0))(duration);
}
