#pragma once
#include "..\pch.h"

enum EPatternID {
	PATID_MKProcDispatch_Hook,
	PATID_RecordEvent_Hook,
	PATID_CameraPositionNOP,
	PATID_CameraRotationNOP,
	PATID_CameraPositionHook,
	PATID_CameraRotationHook,
	PATID_SetSelectScreen_Hook,
	PATID_SetCharacterLadder_Hook,
	PATID_ReadPropertyValue_Hook,
	PATID_SetProperty_Hook,
	PATID_SetProperty,
	PATID_Dispatch_Hook,
	PATID_1SlotAbilitiesHook,
	PATID_SetKryptCharacter_Hook,
	PATID_SetKryptCharacterL_Hook,
	PATID_SetKryptCharacterClass_Hook,

	PATID_CharacterDefinition_Set,
	PATID_CharacterDefinition_SetAlternatePalette,
	PATID_CharacterDefinition_SetLoadout,

	PATID_MKProcDispatch,
	PATID_Dispatch,
	PATID_RecordEvent,
	PATID_GetObj,
	PATID_HideHUD,
	PATID_ShowHUD,
	PATID_SlowGameTimeForXTicks,

	PATID_FGGameInfo_FindGameInfo,
	PATID_FGGameInfo_SetStage,
	PATID_FGGameInfo_ResetStageInteractables0,
	PATID_FGGameInfo_ResetStageInteractables1,
	PATID_FGGameInfo_ResetStageInteractables2,
	PATID_FGGameInfo_GetInfo, 
	
	PATID_Krypt_FindKrypt,
	PATID_Krypt_GetKryptPlayer,

	PATID_GetLadderInfo,

	PATID_MKCamera_SetPosition,
	PATID_MKCamera_SetRotation,

	PATID_MKCharacter_SetLife,
	PATID_MKCharacter_SetScale,
	PATID_MKCharacter_SetSpeed,
	PATID_MKCharacter_SetEasyKrushingBlows,
	PATID_MKCharacter_SetInfiniteKrushingBlows,
	PATID_MKCharacter_SetFastUppercutRecovery,
	PATID_MKCharacter_SetKrushingBlowsDisabled,
	PATID_MKCharacter_SetCombos,
	PATID_MKCharacter_SetInfiniteXrays,
	PATID_MKCharacter_SetXrayNoRequirement,
	PATID_MKCharacter_ActivateHeadTracking,
	PATID_MKCharacter_KillHeadTracking,
	PATID_MKCharacter_SetBoneSize,
	PATID_MKCharacter_GetBonePos,
	PATID_MKCharacter_GetBoneRot,
	PATID_MKCharacter_ExecuteScript,
	PATID_MKCharacter_Rotate,

	PATID_TagAssistModifier_TagAssistModifier,
	PATID_TagAssistModifier_Activate,
	PATID_TagAssistModifier_CreateObject,
	PATID_MKModifier_ActivateModifier,
	PATID_TagAssistModifierObject_Activate,
	PATID_GetModifierManager,
	PATID_LoadModifierAssets,

	PATID_MKObject_SetPos,
	PATID_MKObject_GetPos,

	PATID_GetScript0,
	PATID_GetScript1,
	PATID_MKScript_GetFunctionID,
	PATID_MKScript_GetVar,

	PATID_PlayerInfo_SetMeter,
	PATID_PlayerInfo_RefreshMeter,
	PATID_PlayerInfo_GetDrone,
	PATID_AIDrone_Set,

	PATID_SetKryptCharacter,
	PATID_SetKryptCharacterL,
	PATID_AnimationToolCode,

	PATID_FName_FName,
	PATID_GetNames,
	PATID_USkeletalMeshComponent_GetBoneName,

	PATID_XInputGetState_Hook,
	PATID_GetScaleform,

	PATID_Total_Patterns
};


class PatternSolver {
public:
	static uintptr_t ms_patterns[PATID_Total_Patterns];

	static uintptr_t GetPattern(const char* szPattern, int offset);

	static void			Initialize();
	static int			GetNumPatternsOK();
	static bool			CheckMissingPatterns();
	static const char*	GetPatternName(int id);

};


uintptr_t _pattern(EPatternID id);