#include "Hooks.h"

int64 hud_property = 0;

void(__fastcall* pProcessDOFSettings)(int64, int64, int64, int64) = 0;


void ProcessDOFSettings(int64 settings, int64 a2, int64 newSettings, int64 a4)
{
	if (pProcessDOFSettings)
		pProcessDOFSettings(settings, a2, newSettings, a4);

	if (TheMenu->m_bDisableDOF)
		*(int*)(settings + 36) = 0;
}

void MKProcDispatch_Hook()
{
	PluginDispatch();
	MKProcDispatch();
}

void Dispatch_Hook(int64 ptr, int a2)
{
	if (TheMenu->m_bHookDispatch)
	{
		int64 arg = *(int64*)(ptr);

		if (!TheMenu->m_bFreezeWorld)
			a2 = *(uint32_t*)(ptr + 0x18);

		if (*(uint32_t*)(ptr + 0x14) == a2)
			return;

		*(int*)(ptr + 0x14) = a2;
		((void(*)(int64, int)) * (int64*)(arg + 0xD8))(ptr, a2);
	}
	else
		Dispatch(ptr, a2);
}

void RecordEvent_Hook(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	PluginFightStartup();
	RecordEvent(eventID, a2, a3, a4);
}

void SetSelectScreen_Hook(int64 ptr, PLAYER_NUM plr, int teamNo, char* name, int level, int64 loadout, bool altPalette)
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

void SetCharacterLadder_Hook(CharacterDefinition* chr, char* name, int64 ptr, int64 unk)
{
	if (TheMenu->m_bPlayer1Modifier)
		name = TheMenu->szPlayer1ModifierCharacter;
	chr->Set(name, ptr, unk);
}

void ReadPropertyValue_Hook(int64 ptr, int* unk, int* value)
{
	int input = *value;
	if (ptr == hud_property)
	{
		if (TheMenu->m_bHideHUD)
			input ^= 1;
	}

	*unk = *(int*)(ptr + 408) & input | *unk & ~*(int*)(ptr + 408);
}

int64 SetProperty(int64 ptr, char* name, int64 unk)
{
	hud_property = ptr;
	static uintptr_t pat = _pattern(PATID_SetProperty);
	if (pat)
		return ((int64(__fastcall*)(int64, char*, int64))pat)(ptr, name, unk);
	return 0;
}


void SetKryptCharacter(int64 ptr, char* name)
{
	if (TheMenu->m_bKryptModifier)
		name = TheMenu->szCurrentKryptCharacter;

	printf("MK11Hook::SetKryptCharacter() | Loading character %s\n", name);
	static uintptr_t pat = _pattern(PATID_SetKryptCharacter);
	if (pat)
		((void(__fastcall*)(int64, char*))pat)(ptr, name);
}

void SetKryptCharacterL(int64 ptr, char* name, int unk)
{
	static uintptr_t pat = _pattern(PATID_SetKryptCharacterL);
	if (pat)
		((void(__fastcall*)(int64, char*, int))pat)(ptr, name, unk);
}

void SetKryptCharacterClass(int64 ptr, char* name, int unk)
{
	if (TheMenu->m_bKryptModifier)
		name = TheMenu->szCurrentKryptCharacterClass;
	memcpy((void*)ptr, name, unk);
}

void PluginDispatch()
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
		if (p1) p1->SetScale(&TheMenu->m_vP1Scale);
		if (p2) p2->SetScale(&TheMenu->m_vP2Scale);
	}

	if (p1)
	{
		if (TheMenu->m_bInfiniteHealthP1)	p1->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP1)		p1->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP1)	p1->SetLife(0.01f);

		if (TheMenu->m_bAIDroneModifierP1)
		{
			if (AIDrone* drone = p1_info->GetDrone())
				drone->Set(TheMenu->szPlayer1AI, 0);
		}

		if (TheMenu->m_bEasyKBsP1)
			p1->SetEasyKrushingBlows(true);

		if (TheMenu->m_bInfKBsP1)
			p1->SetInfiniteKrushingBlows(true);

		if (TheMenu->m_bFastUppercutsP1)
			p1->SetFastUppercutRecovery(true);

		if (TheMenu->m_bNoKBsP1)
			p1->SetKrushingBlowsDisabled(true);

		if (TheMenu->m_bInfiniteXraysP1)
			p1->SetXRayInfinite(true);

		if (TheMenu->m_bXrayAlwaysP1)
			p1->SetXRayNoRequirement(true);

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

		if (TheMenu->m_bAIDroneModifierP2)
		{
			if (AIDrone* drone = p2_info->GetDrone())
				drone->Set(TheMenu->szPlayer2AI, 0);
		}


		if (TheMenu->m_bEasyKBsP2)
			p2->SetEasyKrushingBlows(true);

		if (TheMenu->m_bInfKBsP2)
			p2->SetInfiniteKrushingBlows(true);

		if (TheMenu->m_bFastUppercutsP2)
			p2->SetFastUppercutRecovery(true);

		if (TheMenu->m_bNoKBsP2)
			p2->SetKrushingBlowsDisabled(true);

		if (TheMenu->m_bInfiniteXraysP2)
			p2->SetXRayInfinite(true);

		if (TheMenu->m_bXrayAlwaysP2)
			p2->SetXRayNoRequirement(true);

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

	PluginInterface::OnFrameTick();

}

void PluginFightStartup()
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


	if (GetModifierManager())
	{
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

	}
	


	printf("MK11Hook::Info() | %s VS %s\n", GetCharacterName(PLAYER1), GetCharacterName(PLAYER2));
	PluginInterface::OnFightStartup();
}
