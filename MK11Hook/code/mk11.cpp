#include "mk11.h"
#include <iostream>
#include <Windows.h>
#include "mk11menu.h"
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include "MKCharacter.h"
#include "MKModifier.h"
#include "mkcamera.h"
#include "PlayerInfo.h"
#include "unreal/FName.h"
#include "MKObject.h"
#include "Krypt.h"
#include "MKCommand.h"
#include "helper/eMouse.h"

int64 hud_property = 0;

void __fastcall MK11Hooks::HookProcessStuff()
{
	TheMenu->Process();
	Notifications->Update();
	eMouse::UpdateMouse();

	MKCharacter* p1 = GetObj(PLAYER1);
	MKCharacter* p2 = GetObj(PLAYER2);
	PlayerInfo* p1_info = GetInfo(PLAYER1);
	PlayerInfo* p2_info = GetInfo(PLAYER2);

	if (TheMenu->m_bSlowMotion)
		SlowGameTimeForXTicks(TheMenu->m_fSlowMotionSpeed, 10);

	if (TheMenu->m_bChangePlayerSpeed)
	{
		if (p1)	p1->SetSpeed(TheMenu->m_fP1Speed);
		if (p2)	p2->SetSpeed(TheMenu->m_fP2Speed);
	}
	if (TheMenu->m_bChangePlayerScale)
	{
		if (p1)
		{
			if (TheMenu->m_bSmoothScaleChange)
			{
				FVector src = p1->GetScale();
				FVector scale = TheMenu->m_vP1Scale;

				if (!(fabs(TheMenu->m_vP1Scale.X - src.X) < 0.01f))
				{
					if (src.X < scale.X)
						src.X += TheMenu->m_fSmoothScalingUpdate;
					else
						src.X -= TheMenu->m_fSmoothScalingUpdate;
				}

				if (!(fabs(TheMenu->m_vP1Scale.Y - src.Y) < 0.01f))
				{
					if (src.Y < scale.Y)
						src.Y += TheMenu->m_fSmoothScalingUpdate;
					else
						src.Y -= TheMenu->m_fSmoothScalingUpdate;
				}

				if (!(fabs(TheMenu->m_vP1Scale.Z - src.Z) < 0.01f))
				{
					if (src.Z < scale.Z)
						src.Z += TheMenu->m_fSmoothScalingUpdate;
					else
						src.Z -= TheMenu->m_fSmoothScalingUpdate;
				}
			
				p1->SetScale(&src);
			}
			else
				p1->SetScale(&TheMenu->m_vP1Scale);
		}

		if (p2)
		{
			if (TheMenu->m_bSmoothScaleChange)
			{
				FVector src = p2->GetScale();
				FVector scale = TheMenu->m_vP2Scale;

				if (!(fabs(TheMenu->m_vP2Scale.X - src.X) < 0.01f))
				{
					if (src.X < scale.X)
						src.X += TheMenu->m_fSmoothScalingUpdate;
					else
						src.X -= TheMenu->m_fSmoothScalingUpdate;
				}

				if (!(fabs(TheMenu->m_vP2Scale.Y - src.Y) < 0.01f))
				{
					if (src.Y < scale.Y)
						src.Y += TheMenu->m_fSmoothScalingUpdate;
					else
						src.Y -= TheMenu->m_fSmoothScalingUpdate;
				}

				if (!(fabs(TheMenu->m_vP2Scale.Z - src.Z) < 0.01f))
				{
					if (src.Z < scale.Z)
						src.Z += TheMenu->m_fSmoothScalingUpdate;
					else
						src.Z -= TheMenu->m_fSmoothScalingUpdate;
				}

				p2->SetScale(&src);
			}
			else
				p2->SetScale(&TheMenu->m_vP2Scale);
		}
	}

	if (p1)
	{
		if (TheMenu->m_bInfiniteHealthP1)	p1->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP1)		p1->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP1)	p1->SetLife(0.01f);


		if (TheMenu->m_bEasyKBsP1)
			p1->SetEasyKrushingBlows(true);

		if (TheMenu->m_bInfKBsP1)
			p1->SetInfiniteKrushingBlows(true);

		if (TheMenu->m_bFastUppercutsP1)
			p1->SetFastUppercutRecovery(true);

		if (TheMenu->m_bDisableComboScaling)
		{
			if (p1_info)
				p1_info->SetDamageMult(1.0f);
		}

		if (TheMenu->m_bInfiniteAttackP1)
		{
			if (p1_info)
				p1_info->SetMeter(BAR_Offensive, 1000.0f);
		}

		if (TheMenu->m_bInfiniteDefendP1)
		{
			if (p1_info)
				p1_info->SetMeter(BAR_Defensive, 1000.0f);
		}

		if (TheMenu->m_bAutoHideHUD)
			HideHUD();
		if (TheMenu->m_bP1CustomAbilities)
		{
			TheMenu->m_nP1Abilities = 0;
			for (int i = 0; i < sizeof(TheMenu->m_P1Abilities) / sizeof(TheMenu->m_P1Abilities[0]); i++)
			{
				if (TheMenu->m_P1Abilities[i])
					TheMenu->m_nP1Abilities += (int)pow(2, i);
			}
			p1->SetAbility(TheMenu->m_nP1Abilities);
		}

		if (TheMenu->m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING && TheMenu->m_bCustomCameras)
		{
			if (TheMenu->m_bUsePlayerTwoAsTracker)
				p2->SetBoneSize("Head", 0.1f);
			else
				p1->SetBoneSize("Head", 0.1f);

			TheMenu->m_bDisableHeadTracking = true;
		}

		if (TheMenu->m_bDisableHeadTracking)
		{
			if (TheMenu->m_bUsePlayerTwoAsTracker)
				p2->KillHeadTracking();
			else
				p1->KillHeadTracking();

		}
	}


	if (p2)
	{
		if (TheMenu->m_bInfiniteHealthP2)	p2->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP2)	p2->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP2)	p2->SetLife(0.01f);

		if (TheMenu->m_bEasyKBsP2)
			p2->SetEasyKrushingBlows(true);

		if (TheMenu->m_bInfKBsP2)
			p2->SetInfiniteKrushingBlows(true);

		if (TheMenu->m_bFastUppercutsP2)
			p2->SetFastUppercutRecovery(true);

		if (TheMenu->m_bDisableComboScaling)
		{
			if (p2_info)
				p2_info->SetDamageMult(1.0f);
		}

		if (TheMenu->m_bInfiniteAttackP2)
		{
			if (p2_info)
				p2_info->SetMeter(BAR_Offensive, 1000.0f);
		}

		if (TheMenu->m_bInfiniteDefendP2)
		{
			if (p2_info)
				p2_info->SetMeter(BAR_Defensive, 1000.0f);
		}

		if (TheMenu->m_bP2CustomAbilities)
		{
			TheMenu->m_nP2Abilities = 0;
			for (int i = 0; i < sizeof(TheMenu->m_P2Abilities) / sizeof(TheMenu->m_P2Abilities[0]); i++)
			{
				if (TheMenu->m_P2Abilities[i])
					TheMenu->m_nP2Abilities += (int)pow(2, i);
			}
			p2->SetAbility(TheMenu->m_nP2Abilities);
		}
	}

	TheMenu->UpdateFreecam();

	if (TheMenu->m_bForceCameraUpdate)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			TheCamera->SetFOV(TheMenu->camFov);
		}

	}

	if (p1 && p2)
	{
		if (TheMenu->m_bBrutalityWatcher)
			TheMenu->RunBrutalityWatcher();
	}

	((void(__fastcall*)())_addr(0x141152BE0))();
}

void __fastcall MK11Hooks::HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	printf("MK11Hook::Info() | Starting a new fight!\n");
	TheMenu->m_bCustomCameraPos = false;
	TheMenu->m_bCustomCameraRot = false;
	TheMenu->m_bYObtained = false;



	if (TheMenu->m_bStageModifier)
		GetGameInfo()->SetStage(TheMenu->szStageModifierStage);

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

	((void(__fastcall*)(int64, int64, int64, int64))_addr(0x141158B70))(eventID, a2, a3, a4);

}

void MK11Hooks::HookPreFightStart()
{
	((void(__fastcall*)())_addr(0x140CFBAB0))();
}


int64 MK11Hooks::HookSetProperty(int64 ptr, char * name, int64 unk)
{
	hud_property = ptr;
	return ((int64(__fastcall*)(int64, char*, int64))_addr(0x141A6B2D0))(ptr, name, unk);
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
		((int64(__fastcall*)(int64, int))_addr(0x141171F80))(ptr, a2);

}

void MK11Hooks::HookSetSelectScreen(int64 ptr, PLAYER_NUM  plr, int teamNo, char * name, int level, int64 loadout, bool altPalette)
{
	if (plr <= 1 && teamNo <= 3)
	{
		CharacterDefinition* chr = (CharacterDefinition*)((120 * (teamNo + 4 * plr)) + ptr + 448);

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

		chr->Set(name, 0, 0);
		chr->SetLevel(level);
		chr->SetAlternatePalette(altPalette);

		if (loadout)
			chr->SetLoadout(loadout);

	}

}

void MK11Hooks::HookSetLadderScreen(CharacterDefinition* chr, char * name, int64 ptr, int64 unk)
{
	if (TheMenu->m_bPlayer1Modifier)
		name = TheMenu->szPlayer1ModifierCharacter;
	chr->Set(name, ptr, unk);
}

MKCharacter* GetObj(PLAYER_NUM plr)
{
	return ((MKCharacter*(__fastcall*)(PLAYER_NUM))_addr(0x1408F8F60))(plr);
}

PlayerInfo* GetInfo(PLAYER_NUM plr)
{
	return GetGameInfo()->GetInfo(plr);
}

void GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = (int64)GetObj(plr);
	if (object)
		((int64(__fastcall*)(int64, FVector*))_addr(0x14114F8A0))(object, vec);
}

void HideHUD()
{
	((void(__fastcall*)(int, int))_addr(0x1408F59B0))(8, 8);
}

void ShowHUD()
{
	((void(__fastcall*)(int, int))_addr(0x1408F62F0))(8, 8);
}

void SetCharacterMKX(PLAYER_NUM plr, char * name)
{
	int64 ptr = (int64)GetInfo(plr);
	CharacterDefinition* chr = (CharacterDefinition * )(ptr + 216);
	chr->Set(name, 0, 0);
}

char * GetCharacterName(PLAYER_NUM plr)
{
	int64 info = (int64)GetInfo(plr);
	character_info* chr = *(character_info**)(info + 216);
	if (chr)
		return chr->name;
	else
		return "null";
}

void SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, int, int))_addr(0x1405C0A10))(speed, ticks, 0);
}


void SetKryptCharacter(int64 ptr, char * name)
{
	if (TheMenu->m_bKryptModifier)
		name = TheMenu->szCurrentKryptCharacter;

	printf("MK11Hook::SetKryptCharacter() | Loading character %s\n", name);

	((void(__fastcall*)(int64, char*))_addr(0x1408221E0))(ptr, name);
}

void SetKryptCharacterL(int64 ptr, char * name, int unk)
{
	((void(__fastcall*)(int64, char*, int))_addr(0x141A696E0))(ptr, name, unk);
}

void SetKryptCharacterClass(int64 ptr, char * name, int unk)
{
	if (TheMenu->m_bKryptModifier)
		name = TheMenu->szCurrentKryptCharacterClass;
	((void(__fastcall*)(int64, char*, int))_addr(0x142395AD0))(ptr, name, unk);
}

MKModifier* GetModifierManager()
{
	int64 info = ((int64(__fastcall*)())_addr(0x140679BC0))();
	return ((MKModifier*(__fastcall*)(int64))_addr(0x14067B790))(info);
}

void LoadModifierAssets()
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	((void(__fastcall*)(int64, bool))_addr(0x14057DD50))(gameinfo, 1);

}

unsigned int HashString(const char* input)
{
	unsigned int result; 
	int stringLength; 
	int character; 

	if (!input)
		return 0;
	stringLength = -1;

	do
		++stringLength;
	while (input[stringLength]);

	for (result = 0x811C9DC5; stringLength; --stringLength)
	{
		character = *(unsigned char*)input++;
		result = character ^ (unsigned int)(0x1000193 * result);
	}
	return result;
}
