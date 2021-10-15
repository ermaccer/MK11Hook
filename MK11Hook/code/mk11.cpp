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

	if (TheMenu->m_bSlowMotion)
		SlowGameTimeForXTicks(TheMenu->m_fSlowMotionSpeed, 10);

	if (TheMenu->m_bChangePlayerSpeed)
	{
		if (GetObj(PLAYER1))
			GetObj(PLAYER1)->SetSpeed(TheMenu->m_fP1Speed);
		if (GetObj(PLAYER2))
			GetObj(PLAYER2)->SetSpeed(TheMenu->m_fP2Speed);
	}
	if (TheMenu->m_bChangePlayerScale)
	{
		if (GetObj(PLAYER1))
			GetObj(PLAYER1)->SetScale(&TheMenu->m_vP1Scale);
		if (GetObj(PLAYER2))
			GetObj(PLAYER2)->SetScale(&TheMenu->m_vP2Scale);
	}


	if (GetObj(PLAYER1))
	{
		if (TheMenu->m_bInfiniteHealthP1)
			GetObj(PLAYER1)->SetLife(1000.0f);

		if (TheMenu->m_bNoHealthP1)
			GetObj(PLAYER1)->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP1)
			GetObj(PLAYER1)->SetLife(0.01f);

		if (TheMenu->m_bInfiniteAttackP1)
		{
			if (GetInfo(PLAYER1))
				SetCharacterEnergy(GetInfo(PLAYER1), BAR_Offensive, 1000.0f);
		}

		if (TheMenu->m_bInfiniteDefendP1)
		{
			if (GetInfo(PLAYER1))
				SetCharacterEnergy(GetInfo(PLAYER1), BAR_Defensive, 1000.0f);
		}

		if (TheMenu->m_bAutoHideHUD)
			HideHUD();
		if (TheMenu->m_bP1CustomAbilities)
		{
			TheMenu->m_nP1Abilities = 0;
			for (int i = 0; i < sizeof(TheMenu->m_P1Abilities) / sizeof(TheMenu->m_P1Abilities[0]); i++)
			{
				if (TheMenu->m_P1Abilities[i])
				{
					TheMenu->m_nP1Abilities += pow(2, i);
				}
			}
			GetObj(PLAYER1)->SetAbility(TheMenu->m_nP1Abilities);
		}


	}


	if (GetObj(PLAYER2))
	{
		if (TheMenu->m_bInfiniteHealthP2)
			GetObj(PLAYER2)->SetLife(1000.0f);

		if (TheMenu->m_bNoHealthP1)
			GetObj(PLAYER2)->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP2)
			GetObj(PLAYER2)->SetLife(0.01f);

		if (TheMenu->m_bInfiniteAttackP2)
		{
			if (GetInfo(PLAYER2))
				SetCharacterEnergy(GetInfo(PLAYER2), BAR_Offensive, 1000.0f);
		}

		if (TheMenu->m_bInfiniteDefendP2)
		{
			if (GetInfo(PLAYER2))
				SetCharacterEnergy(GetInfo(PLAYER2), BAR_Defensive, 1000.0f);
		}

		if (TheMenu->m_bP1CustomAbilities)
		{
			TheMenu->m_nP2Abilities = 0;
			for (int i = 0; i < sizeof(TheMenu->m_P2Abilities) / sizeof(TheMenu->m_P2Abilities[0]); i++)
			{
				if (TheMenu->m_P2Abilities[i])
				{
					TheMenu->m_nP2Abilities += pow(2, i);
				}
			}
			GetObj(PLAYER2)->SetAbility(TheMenu->m_nP2Abilities);
		}
	}


	if (!(GetObj(PLAYER1)) || !(GetObj(PLAYER2)))
	{
		if (TheMenu->m_bCustomCameras)
			TheMenu->m_bCustomCameras = false;
	}

	if (TheMenu->m_bFreeCam)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->m_fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			TheMenu->camFov -= 1.0f;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			TheMenu->camFov += 1.0f;
	}


	if (TheMenu->m_bForceCameraUpdate)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			TheCamera->SetFOV(TheMenu->camFov);
		}

	}

	((void(__fastcall*)())_addr(0x141153D20))();
}

void MK11Hooks::PreLoadHook(int64 a1, int64 a2, int a3)
{
	((void(__fastcall*)(int64, int64, int))_addr(0x1408FCDB0))(a1, a2, a3);
}

void __fastcall MK11Hooks::HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	printf("MK11Hook::Info() | Starting a new fight!\n");
	TheMenu->m_bCustomCameras = false;
	TheMenu->m_bCustomCameraPos = false;
	TheMenu->m_bCustomCameraRot = false;
	TheMenu->m_bYObtained = false;

	if (TheMenu->m_bStageModifier)
		SetStage(TheMenu->szStageModifierStage);

	if (TheMenu->m_nCurrentCharModifier == MODIFIER_FIGHT)
	{
		if (TheMenu->m_bPlayer1Modifier)
			SetCharacterMKX(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
		if (TheMenu->m_bPlayer2Modifier)
			SetCharacterMKX(PLAYER2, TheMenu->szPlayer2ModifierCharacter);
	}


	if (TheMenu->m_bTagAssist)
	{
		TagAssistModifier tag(TheMenu->szPlayer1TagAssistCharacter);
		tag.Activate(GetInfo(PLAYER1));

		TagAssistModifierObject* obj = tag.CreateObject();

		if (obj)
			obj->Activate(GetObj(PLAYER1));

		GetModifierManager()->ActivateModifier(&tag, GetObj(PLAYER1));
		LoadModifierAssets();
		printf("MK11Hook::Info() | P1 Tag Assist: %s\n", TheMenu->szPlayer1TagAssistCharacter);
	}
	if (TheMenu->m_bTagAssistP2)
	{
		TagAssistModifier tag(TheMenu->szPlayer2TagAssistCharacter);
		tag.Activate(GetInfo(PLAYER2));

		TagAssistModifierObject* obj = tag.CreateObject();

		if (obj)
			obj->Activate(GetObj(PLAYER2));

		GetModifierManager()->ActivateModifier(&tag, GetObj(PLAYER2));
		LoadModifierAssets();
		printf("MK11Hook::Info() | P2 Tag Assist: %s\n", TheMenu->szPlayer2TagAssistCharacter);
	}

	printf("MK11Hook::Info() | %s VS %s\n", GetCharacterName(PLAYER1), GetCharacterName(PLAYER2));





	((void(__fastcall*)(int64, int64, int64, int64))_addr(0x141159CB0))(eventID, a2, a3, a4);

}

void MK11Hooks::PostLoadHook()
{


	((int64(__fastcall*)())_addr(0x14090F7A0))();
}

int64 __fastcall MK11Hooks::HookLoadCharacter(int64 ptr, char * name)
{
	printf("%x\n", (int64)&name[0]);
	if (TheMenu->m_nCurrentCharModifier == MODIFIER_SCREEN)
	{
		if (name)
		{
			if (!IsDLC(name))
			{
				if (TheMenu->m_bPlayer1Modifier)
				{
					if (ptr == GetInfo(PLAYER1))
					{

						char* original_name = name;
						printf("MK11Hook::Info() | Setting Player %s\n", TheMenu->szPlayer1ModifierCharacter);
						strcpy((char*)(int64)&original_name[0], TheMenu->szPlayer1ModifierCharacter);
						strcpy((char*)(int64)&original_name[0], original_name);

						// crash fix
						TheMenu->m_bPlayer1Modifier = false;
					}
				}
				if (TheMenu->m_bPlayer2Modifier)
				{
					if (ptr == GetInfo(PLAYER2))
					{
						char* original_name = name;
						printf("MK11Hook::Info() | Setting Player %s\n", TheMenu->szPlayer2ModifierCharacter);
						strcpy((char*)(int64)&original_name[0], TheMenu->szPlayer2ModifierCharacter);
						strcpy((char*)(int64)&original_name[0], original_name);
						TheMenu->m_bPlayer2Modifier = false;
					}
				}
			}
		}

	}
	return ((int64(__fastcall*)(int64, char*))_addr(0x1408F8500))(ptr, name);

}

int64 MK11Hooks::HookSetProperty(int64 ptr, char * name, int64 unk)
{
	hud_property = ptr;
	return ((int64(__fastcall*)(int64, char*, int64))_addr(0x141A6BE90))(ptr, name, unk);
}

void MK11Hooks::HookReadPropertyValue(int64 ptr, int* unk, int* value)
{
	int input = *value;
	if (ptr == hud_property)
	{
		if (TheMenu->m_bDisableHUD)
			input ^= 1;
	}


	*unk = *(int*)(ptr + 408) & input | *unk & ~*(int*)(ptr + 408);
}

int64 MK11Hooks::HookLoadouts(int64 ptr)
{
	if (TheMenu->m_bDisableGearLoadouts)
		return true;
	else
		return ((int64(__fastcall*)(int64))_addr(0x14086F670))(ptr);
}

void MK11Hooks::HookDispatch(int64 ptr, int a2)
{
	if (TheMenu->m_bHookDispatch)
	{
		int64 arg = *(int64*)(ptr);

		if (!TheMenu->m_bFreezeWorld)
			a2 = *(uint32_t*)(ptr + 0x18);

		if (*(uint32_t*)(ptr + 0x14) == a2)
			return;

		*(int*)(ptr + 0x14) = a2;
		((void(*)(int64, int))*(int64*)(arg + 0xD8))(ptr, a2);
	}
	else
		((int64(__fastcall*)(int64, int))_addr(0x141172FF0))(ptr, a2);

}

void MK11Hooks::HookSetSelectScreen(int64 ptr, PLAYER_NUM  plr, int teamNo, char * name, int level, int64 loadout, bool altPalette)
{
	if (plr <= 1 && teamNo <= 3)
	{
		int64 chr = 120 * ((int)teamNo + 4 * (int)plr) + ptr + 448;

		if (TheMenu->m_nCurrentCharModifier == MODIFIER_SCREEN && (TheMenu->m_bPlayer1Modifier || TheMenu->m_bPlayer2Modifier))
		{
			if (name)
			{

				switch (plr)
				{
				case PLAYER1:
					if (TheMenu->m_bPlayer1Modifier)
						name = TheMenu->szPlayer1ModifierCharacter;
					break;
				case PLAYER2:
					if (TheMenu->m_bPlayer2Modifier)
						name = TheMenu->szPlayer2ModifierCharacter;
					break;
				default:
					break;
				}
			}
		}


		SetCharacter(chr, name, 0, 0);

		SetCharacterLevel(chr, level);
		SetCharacterAltPal(chr, altPalette);
		if (loadout)
			SetCharacterLoadout(chr, loadout);
	}

}

void MK11Hooks::HookSetLadderScreen(int64 chr, char * name, int64 ptr, int64 unk)
{
	if (TheMenu->m_bPlayer1Modifier)
		name = TheMenu->szPlayer1ModifierCharacter;
	SetCharacter(chr, name, ptr, unk);
}

MKCharacter* GetObj(PLAYER_NUM plr)
{
	return ((MKCharacter*(__fastcall*)(PLAYER_NUM))_addr(0x1408F87D0))(plr);
}

int64 GetInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	return ((int64(__fastcall*)(int64, PLAYER_NUM))_addr(0x14056F160))(gameinfo, plr);
}




void GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = GetInfo(plr);
	int64 ptr = *(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector*))_addr(0x1411509E0))(ptr, vec);
}

void HideHUD()
{
	((void(__fastcall*)(int, int))_addr(0x1408F5220))(8, 8);
}

void ShowHUD()
{
	((void(__fastcall*)(int, int))_addr(0x1408F5B60))(8, 8);
}

void SetCharacterMKX(PLAYER_NUM plr, char * name)
{
	int64 ptr = GetInfo(plr);
	int64 chr = (ptr + 216);
	SetCharacter(chr, name, 0, 0);
}

void SetCharacter(int64 chr, char * name, int64 ptr, int64 unk)
{
	((void(__fastcall*)(int64, const char*, int64, int64))_addr(0x140598320))(chr, name, ptr, unk);

}

void SetCharacterLevel(int64 chr, int level)
{
	((void(__fastcall*)(int64, int))_addr(0x1405997F0))(chr, level);
}

void SetCharacterAltPal(int64 chr, int value)
{
	((void(__fastcall*)(int64, int))_addr(0x14059DE50))(chr, value);
}

void SetCharacterLoadout(int64 chr, int64 loadout)
{
	((void(__fastcall*)(int64, int64))_addr(0x140599920))(chr, loadout);
}


char * GetCharacterName(PLAYER_NUM plr)
{
	int64 info = GetInfo(plr);
	character_info* chr = *(character_info**)(info + 216);

	return chr->name;
}



void SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, int, int))_addr(0x1405C0280))(speed, ticks, 0);
}

void SetCharacterEnergy(int64 obj, int type, float energy)
{
	((void(__fastcall*)(int64, int, float))_addr(0x1405FA450))(obj, type, energy);
}

void SetStage(const char * stage)
{
	__int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, const char*))_addr(0x140599CD0))(gameinfo, stage);
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

bool IsDLC(const char * name)
{
	if (name)
	{
		for (int i = 0; i < sizeof(szCharactersDLC) / sizeof(szCharactersDLC[0]); i++)
		{
			if (strcmp(name, szCharactersDLC[i]) == 0)
			{
				if (TheMenu->m_bPlayer1Modifier)
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

void SetKryptCharacter(int64 ptr, char * name)
{
	if (TheMenu->m_bKryptModifier)
		name = TheMenu->szCurrentKryptCharacter;

	printf("MK11Hook::SetKryptCharacter() | Loading character %s\n", name);

	((void(__fastcall*)(int64, char*))_addr(0x140821A50))(ptr, name);
}

void SetKryptCharacterL(int64 ptr, char * name, int unk)
{
	((void(__fastcall*)(int64, char*, int))_addr(0x141A6A2A0))(ptr, name, unk);
}

void SetKryptCharacterClass(int64 ptr, char * name, int unk)
{
	if (TheMenu->m_bKryptModifier)
		name = TheMenu->szCurrentKryptCharacterClass;
	((void(__fastcall*)(int64, char*, int))_addr(0x142396240))(ptr, name, unk);
}

MKModifier* GetModifierManager()
{
	int64 info = ((int64(__fastcall*)())_addr(0x140679430))();
	return ((MKModifier*(__fastcall*)(int64))_addr(0x14067B000))(info);
}

void LoadModifierAssets()
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	((void(__fastcall*)(int64, bool))_addr(0x14057D5C0))(gameinfo, 1);

}
