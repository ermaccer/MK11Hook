#include "PatternSolver.h"
#include "..\utils\Patterns.h"
#include "..\gui\log.h"
#include <chrono>

uintptr_t PatternSolver::ms_patterns[PATID_Total_Patterns];


uintptr_t PatternSolver::GetPattern(const char* szPattern, int offset)
{
    uintptr_t addr = 0;
    try {
        addr = (uintptr_t)hook::txn::get_pattern(szPattern, offset);
    }
    TXN_CATCH();

    return addr;
}

void PatternSolver::Initialize()
{
    eLog::Message(__FUNCTION__, "Starting pattern search");

    for (int i = 0; i < PATID_Total_Patterns; i++)
        ms_patterns[i] = 0;

    auto begin = std::chrono::high_resolution_clock::now();

    ms_patterns[PATID_MKProcDispatch_Hook] = GetPattern("E8 ? ? ? ? 48 8B 1D ? ? ? ? 48 8D 54 24 40 48 8B CB E8 ? ? ? ?", 0);
    ms_patterns[PATID_RecordEvent_Hook] = GetPattern("E8 ? ? ? ? 48 8B 45 77 48 8B D8 48 B9 60 00 FE 00 70 80 01 00 48 23 D9", 0);
    ms_patterns[PATID_CameraPositionNOP] = GetPattern("8B 87 00 07 00 00 0F 11 87 BC 06 00 00", 6);
    ms_patterns[PATID_CameraRotationNOP] = GetPattern("48 8B CF F2 0F 11 8F CC 06 00 00", 3);
    ms_patterns[PATID_CameraPositionHook] = GetPattern("89 87 D4 06 00 00 E8 ? ? ? ? 48 8D 54 24 3C", 6);
    ms_patterns[PATID_CameraRotationHook] = GetPattern("48 8D 54 24 3C 48 8B CF E8 ? ? ? ? 48 8B 9C 24 90 00 00 00", 8);
    ms_patterns[PATID_SetSelectScreen_Hook] = GetPattern("48 83 EC 28 4D 8B D1 83 FA 01 77 6D 41 83 F8 03", 0);
    ms_patterns[PATID_SetCharacterLadder_Hook] = GetPattern("45 33 C9 45 33 C0 48 8B D5 48 8B 8E E0 01 00 00 E8 ? ? ? ? 48 8B 8E E0 01 00 00", 16);
    ms_patterns[PATID_ReadPropertyValue_Hook] = GetPattern("44 8B 89 98 01 00 00 41 8B C9 41 8B 00", 0);
    ms_patterns[PATID_SetProperty_Hook] = GetPattern("48 8D 15 ? ? ? ? 48 8B C8 E8 ? ? ? ? EB 03 49 8B C6 48 81 88 90 00 00 00 00 40 00 00", 10);
    ms_patterns[PATID_SetProperty] = GetPattern("40 53 48 83 EC 20 48 8B D9 E8 ? ? ? ? 48 8D 05 ? ? ? ? C7 83 98 01 00 00 01 00 00 00", 0);
    ms_patterns[PATID_Dispatch_Hook] = GetPattern("48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ?", 7);
    ms_patterns[PATID_1SlotAbilitiesHook] = GetPattern("48 83 EC 38 0F 10 41 24 48 8D 4C 24 20 0F 29 44 24 20 E8 ? ? ? ? 48 85 C0 74 29 48 8D 88 D0 01 00 00 48 8D 54 24 20 E8 ? ? ? ? 48 85 C0 74 13 48 8B 00 48 85 C0 74 0B 8B 80 DC 00 00 00", 0);
    ms_patterns[PATID_SetKryptCharacter_Hook] = GetPattern("48 8D 15 ? ? ? ? 48 8D 4D 90 E8 ? ? ? ? 41 B8 01 00 00 00", 11);
    ms_patterns[PATID_SetKryptCharacterL_Hook] = GetPattern("48 8D 15 ? ? ? ? 48 8D 4C 24 40 E8 ? ? ? ? 48 8B 08 48 89 4D E8", 12);
    ms_patterns[PATID_SetKryptCharacterClass_Hook] = GetPattern("4C 8B C1 48 8D 15 ? ? ? ? 48 8B C8 E8 ? ? ? ? 90 48 8D 44 24 48", 13);

    ms_patterns[PATID_CharacterDefinition_Set] = GetPattern("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 E1 48 81 EC F8 00 00 00 48 C7 45 97 FE FF FF FF", 0);
    ms_patterns[PATID_CharacterDefinition_SetAlternatePalette] = GetPattern("44 8B 41 50 41 8B C0 83 E0 FE 41 83 C8 01", 0);
    ms_patterns[PATID_CharacterDefinition_SetLoadout] = GetPattern("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B 59 60", 0);

    ms_patterns[PATID_MKProcDispatch] = GetPattern("48 8B C4 57 41 54 41 55 41 56 41 57 48 83 EC 40 48 C7 40 B8 FE FF FF FF 48 89 58 10 48 89 68 18 48 89 70 20 48 8D 0D ? ? ? ? E8", 0);
    ms_patterns[PATID_Dispatch] = GetPattern("8B 51 18 39 51 14 74 0D 48 8B 01 89 51 14 48 FF A0 E0 00 00 00", 0);
    ms_patterns[PATID_RecordEvent] = GetPattern("48 83 EC 38 44 8B D1 48 8B 0D ? ? ? ? 48 85 C9 74 14", 0);
    ms_patterns[PATID_GetObj] = GetPattern("40 53 48 83 EC 20 0F B6 DA 45 33 C0 8B D1 48 8B 0D ? ? ? ?", 0);
    ms_patterns[PATID_HideHUD] = GetPattern("48 89 5C 24 08 57 48 83 EC 20 8B F9 8B DA 48 8B 0D ? ? ? ? F6 81 BC 00 00 00 10", 0);
    ms_patterns[PATID_ShowHUD] = GetPattern("48 89 5C 24 08 57 48 83 EC 20 48 8B 05 ? ? ? ? 8B DA 8B F9", 0);
    ms_patterns[PATID_SlowGameTimeForXTicks] = GetPattern("40 57 48 83 EC 50 48 C7 44 24 30 FE FF FF FF 48 89 5C 24 60 0F 29 74 24 40 8B FA F3 0F 10 ? ? ? ? ? F3 0F 5F F0", 0);

    ms_patterns[PATID_FGGameInfo_FindGameInfo] = GetPattern("40 53 48 83 EC 20 0F B6 DA 45 33 C0 8B D1 48 8B 0D ? ? ? ?", 17);
    ms_patterns[PATID_FGGameInfo_SetStage] = GetPattern("40 57 48 83 EC 40 48 C7 44 24 20 FE FF FF FF 48 89 5C 24 50 48 89 74 24 58 48 8B F1 E8 ? ? ? ? 33 D2", 0);
    ms_patterns[PATID_FGGameInfo_ResetStageInteractables0] = GetPattern("40 53 57 41 54 41 55 48 83 EC 78 8B 91 B8 4E 00 00", 0);
    ms_patterns[PATID_FGGameInfo_ResetStageInteractables1] = GetPattern("48 83 EC 28 48 81 C1 E8 4E 00 00 C6 44 24 30 00", 0);
    ms_patterns[PATID_FGGameInfo_ResetStageInteractables2] = GetPattern("48 89 5C 24 08 57 48 83 EC 20 48 8B F9 B9 B6 00 00 00", 0);
    ms_patterns[PATID_FGGameInfo_GetInfo] = GetPattern("83 FA 03 77 0C 48 63 C2 48 8B 84 C1 78 07 00 00 C3", 0);

    ms_patterns[PATID_Krypt_FindKrypt] = GetPattern("48 8D 6C 24 D0 48 81 EC 30 01 00 00 4C 8B 05 ? ? ? ?", 15);
    ms_patterns[PATID_Krypt_GetKryptPlayer] = GetPattern("40 53 48 83 EC 20 48 8B 99 88 0C 00 00 4C 8B C9", 0);

    ms_patterns[PATID_GetLadderInfo] = GetPattern("48 8B 98 C0 01 00 00 48 85 DB 74 15 E8 ? ? ? ?", 13);

    ms_patterns[PATID_MKCamera_SetPosition] = GetPattern("40 53 48 83 EC 20 F2 0F 10 02 48 8B D9 F2 0F 11 81 18 01 00 00 8B 42 08 BA 01 00 00 00 89 81 20 01 00 00 E8 ? ? ? ? 48 8D 8B 68 03 00 00", 0);
    ms_patterns[PATID_MKCamera_SetRotation] = GetPattern("40 53 48 83 EC 20 F2 0F 10 02 48 8B D9 F2 0F 11 81 24 01 00 00 8B 42 08", 0);

    ms_patterns[PATID_MKCharacter_SetLife] = GetPattern("40 53 48 83 EC 70 48 C7 44 24 30 FE FF FF FF 0F 29 74 24 60 0F 28 F1", 0);
    ms_patterns[PATID_MKCharacter_SetScale] = GetPattern("F2 0F 10 02 F2 0F 11 81 ? ? 00 00 8B 42 08 BA 01 00 00 00", 0);
    ms_patterns[PATID_MKCharacter_SetSpeed] = GetPattern("40 53 48 83 EC 30 0F 29 74 24 20 48 8B D9 0F 28 F1 E8 ? ? ? ? 0F 28 CE 48 8B CB 0F 28 74 24 20 48 83 C4 30 5B E9 ? ? ? ?", 0);
    ms_patterns[PATID_MKCharacter_SetEasyKrushingBlows] = GetPattern("33 C0 49 B9 FF FF FF FF FF FF FF FB 41 83 F8 03", 0);
    ms_patterns[PATID_MKCharacter_SetInfiniteKrushingBlows] = GetPattern("33 C0 49 B9 FF FF FF FF FF FF DF FF 41 83 F8 03", 0);
    ms_patterns[PATID_MKCharacter_SetFastUppercutRecovery] = GetPattern("33 C0 41 83 F8 03 44 0F 47 C0 49 63 C0 4C 8D 04 C1 49 8B 88 F0 0D 00 00 48 8B C1 48 0F BA E9 1C", 0);
    ms_patterns[PATID_MKCharacter_SetKrushingBlowsDisabled] = GetPattern("33 C0 49 B9 FF FF FF FF FF FF EF FF 41 83 F8 03", 0);
    ms_patterns[PATID_MKCharacter_SetCombos] = GetPattern("33 C0 41 83 F8 03 44 0F 47 C0 49 63 C0 4C 8D 04 C1 49 8B 88 F0 0D 00 00 48 8B C1 48 0F BA E9 1A", 0);
    ms_patterns[PATID_MKCharacter_SetInfiniteXrays] = GetPattern("40 53 48 83 EC 20 48 8B 81 ? ? ? ? 48 8B D9 48 85 C0 74 5B 80 F2 01 48 89 74 24 ? 48 89 7C 24 ? 0F B6 FA 89 B8", 0);
    ms_patterns[PATID_MKCharacter_SetXrayNoRequirement] = GetPattern("48 89 5C 24 ? 57 48 83 EC 20 33 C0 8B FA 41 83 F8 03 48 BA ? ? ? ? ? ? ? ? 44 0F 47 C0 49 63 C0 4C 8D 0C C1 4D 8B 81 ? ? ? ? 49 8B C0 48 0B C2", 0);
    ms_patterns[PATID_MKCharacter_ActivateHeadTracking] = GetPattern("48 83 EC 38 0F 29 74 24 20 0F 28 F1 E8 ? ? ? ? 48 85 C0 74 0F 48 8B 10 0F 28 CE 48 8B C8 FF 92 88 00 00 00 0F 28 74 24 20", 0);
    ms_patterns[PATID_MKCharacter_KillHeadTracking] = GetPattern("48 83 EC 38 0F 29 74 24 20 0F 28 F1 E8 ? ? ? ? 48 85 C0 74 0F 48 8B 10 0F 28 CE 48 8B C8 FF 92 90 00 00 00 0F 28 74 24 20", 0);
    ms_patterns[PATID_MKCharacter_SetBoneSize] = GetPattern("48 89 5C 24 08 57 48 83 EC 50 48 8B F9 0F 29 74 24 40 48 8B 89 ? ? 00 00 0F 28 F2 48 8B DA", 0);
    ms_patterns[PATID_MKCharacter_GetBonePos] = GetPattern("40 53 48 83 EC 70 33 C0 49 8B D8 48 89 84 24 88 00 00 00", 0);
    ms_patterns[PATID_MKCharacter_GetBoneRot] = GetPattern("4D 85 C0 74 4C 53 48 81 EC 80 00 00 00 48 8B 01", 0);
    ms_patterns[PATID_MKCharacter_ExecuteScript] = GetPattern("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 48 89 7C 24 20 41 56 48 83 EC 30 48 8B F9 45 8B F1 33 C9", 0);
    ms_patterns[PATID_MKCharacter_Rotate] = GetPattern("48 83 EC 38 48 83 79 20 00 74 4A F3 0F 10", 0);

    ms_patterns[PATID_TagAssistModifier_TagAssistModifier] = GetPattern("48 89 4C 24 08 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC 60 48 C7 45 C0 FE FF FF FF 48 89 9C 24 A8 00 00 00 49 8B D8", 0);
    ms_patterns[PATID_TagAssistModifier_Activate] = GetPattern("48 85 D2 0F 84 A7 01 00 00 48 8B C4 57 41 56 41 57 48 83 EC 70 48 C7 40 A8 FE FF FF FF", 0);
    ms_patterns[PATID_TagAssistModifier_CreateObject] = GetPattern("40 57 48 83 EC 30 48 C7 44 24 20 FE FF FF FF 48 89 5C 24 40 48 8B F9 BA 01 00 00 00 B9 20 01 00 00", 0);
    ms_patterns[PATID_MKModifier_ActivateModifier] = GetPattern("48 89 5C 24 18 48 89 6C 24 20 56 48 83 EC 20 48 8B 02 48 8B E9 48 8B CA", 0);
    ms_patterns[PATID_TagAssistModifierObject_Activate] = GetPattern("48 89 5C 24 08 57 48 83 EC 20 48 8B DA 48 8B F9 48 85 D2 0F 84 89 00 00 00", 0);
    ms_patterns[PATID_GetModifierManager] = GetPattern("B9 03 00 00 00 E8 ? ? ? ? E8 ? ? ? ? 48 85 C0 74 11 BA 40 00 00 00", 11);
    ms_patterns[PATID_LoadModifierAssets] = GetPattern("48 89 5C 24 10 55 48 83 EC 30 48 8D 2D ? ? ? ?", 0);

    ms_patterns[PATID_MKObject_SetPos] = GetPattern("48 89 5C 24 10 57 48 83 EC 30 48 8B D9 48 8B FA 48 8B 49 20 48 85 C9 0F 84 86 00 00 00 48 89 74 24 40 E8 ? ? ? ? 48 8B F0", 0);
    ms_patterns[PATID_MKObject_GetPos] = GetPattern("40 53 48 83 EC 30 4C 8B 49 20 48 8B DA 4D 85 C9 74 65", 0);

    ms_patterns[PATID_GetScript0] = GetPattern("40 57 48 83 EC 60 48 C7 44 24 20 FE FF FF FF 48 89 5C 24 70 48 8B D9 48 8B D1 33 C9 E8 ? ? ? ? 48 85 C0", 0);
    ms_patterns[PATID_GetScript1] = GetPattern("48 8B C4 41 56 48 83 EC 60 48 C7 40 D8 FE FF FF FF 48 89 58 08 48 89 68 10 48 89 70 18 48 89 78 20 41 8B F1 41 0F B6 E8", 0);
    ms_patterns[PATID_MKScript_GetFunctionID] = GetPattern("48 83 EC 28 48 81 C1 50 01 00 00 E8 ? ? ? ? 48 85 C0", 0);
    ms_patterns[PATID_MKScript_GetVar] = GetPattern("45 33 C0 4C 8B CA 4C 8B D9 48 85 D2 75 05", 0);

    ms_patterns[PATID_PlayerInfo_SetMeter] = GetPattern("40 53 48 83 EC 30 0F 29 74 24 20 0F 57 F6 8B DA", 0);
    ms_patterns[PATID_PlayerInfo_RefreshMeter] = GetPattern("48 89 5C 24 10 56 48 81 EC 80 00 00 00 48 8B D9", 0);
    ms_patterns[PATID_PlayerInfo_GetDrone] = GetPattern("48 8B 81 50 04 00 00 48 85 C0 74 21", 0);
    ms_patterns[PATID_AIDrone_Set] = GetPattern("48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 20 48 8B F9 48 8B F2 48 8B 0D ? ? ? ? BA 00 00 00 10", 0);

    ms_patterns[PATID_SetKryptCharacter] = GetPattern("40 57 48 83 EC 40 48 C7 44 24 20 FE FF FF FF 48 89 5C 24 50 48 89 74 24 60 48 8B DA 48 8B F9 33 F6", 0);
    ms_patterns[PATID_SetKryptCharacterL] = GetPattern("40 53 48 83 EC 40 48 8B D9 48 85 D2 74 48 80 3A 00", 0);
    ms_patterns[PATID_AnimationToolCode] = GetPattern("0F 10 44 24 48 45 0F C6 C9 C6", 10);

    ms_patterns[PATID_FName_FName] = GetPattern("40 53 48 83 EC 40 48 8B D9 48 85 D2 74 48 80 3A 00", 0);
    ms_patterns[PATID_GetNames] = GetPattern("8B 0C FE 48 8B 05 ? ? ? ? 48 8B 0C C8 48 83 C1 10 E8 ? ? ? ? 41 3B C5", 6);
    ms_patterns[PATID_USkeletalMeshComponent_GetBoneName] = GetPattern("48 89 5C 24 08 57 48 83 EC 20 48 8B 89 ? ? 00 00 41 8B D8", 0);

    ms_patterns[PATID_XInputGetState_Hook] = GetPattern("48 8D 55 17 8B CB E8 ? ? ? ? 85 C0", 7);

    ms_patterns[PATID_GetScaleform] = GetPattern("83 3D ? ? ? ? ? 74 72 45 8B C4 8B 15", 2);

    ms_patterns[PATID_ProcessDOFSettings] = GetPattern("48 8D 4B 44 E8 ? ? ? ? 48 8D 44 24", 4);

    auto end = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    auto timeSeconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin);
    eLog::Message(__FUNCTION__, "Checked %d patterns in %dms (%ds)", PATID_Total_Patterns, time.count(), timeSeconds.count());

}

int PatternSolver::GetNumPatternsOK()
{
    int patternNum = 0;

    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i]) patternNum++;
    return patternNum;
}

bool PatternSolver::CheckMissingPatterns()
{
    int missingPatterns = 0;
    for (int i = 0; i < PATID_Total_Patterns; i++)
        if (ms_patterns[i] == 0)
        {
            missingPatterns++;
            eLog::Message(__FUNCTION__, "ERROR: Could not find %s!", GetPatternName(i));
        }
    return missingPatterns > 0;
}

const char* PatternSolver::GetPatternName(int id)
{
    if (id >= PATID_Total_Patterns)
        return "UNKNOWN";

    static const char* szPatternNames[PATID_Total_Patterns] = {
        "MKProcDispatch_Hook",
        "RecordEvent_Hook",
        "CameraPositionNOP",
        "CameraRotationNOP",
        "CameraPositionHook",
        "CameraRotationHook",
        "SetSelectScreen_Hook",
        "SetCharacterLadder_Hook",
        "ReadPropertyValue_Hook",
        "SetProperty_Hook",
        "SetProperty",
        "Dispatch_Hook",
        "1SlotAbilitiesHook",
        "SetKryptCharacter_Hook",
        "SetKryptCharacterL_Hook",
        "SetKryptCharacterClass_Hook",
        "CharacterDefinition_Set",
        "CharacterDefinition_SetAlternatePalette",
        "CharacterDefinition_SetLoadout",
        "MKProcDispatch",
        "Dispatch",
        "RecordEvent",
        "GetObj",
        "HideHUD",
        "ShowHUD",
        "SlowGameTimeForXTicks",
        "FGGameInfo_FindGameInfo",
        "FGGameInfo_SetStage",
        "FGGameInfo_ResetStageInteractables0",
        "FGGameInfo_ResetStageInteractables1",
        "FGGameInfo_ResetStageInteractables2",
        "FGGameInfo_GetInfo",
        "Krypt_FindKrypt",
        "Krypt_GetKryptPlayer",
        "GetLadderInfo",
        "MKCamera_SetPosition",
        "MKCamera_SetRotation",
        "MKCharacter_SetLife",
        "MKCharacter_SetScale",
        "MKCharacter_SetSpeed",
        "MKCharacter_SetEasyKrushingBlows",
        "MKCharacter_SetInfiniteKrushingBlows",
        "MKCharacter_SetFastUppercutRecovery",
        "MKCharacter_SetKrushingBlowsDisabled",
        "MKCharacter_SetCombos",
        "MKCharacter_SetInfiniteXrays",
        "MKCharacter_SetXrayNoRequirement",
        "MKCharacter_ActivateHeadTracking",
        "MKCharacter_KillHeadTracking",
        "MKCharacter_SetBoneSize",
        "MKCharacter_GetBonePos",
        "MKCharacter_GetBoneRot",
        "MKCharacter_ExecuteScript",
        "MKCharacter_Rotate",
        "TagAssistModifier_TagAssistModifier",
        "TagAssistModifier_Activate",
        "TagAssistModifier_CreateObject",
        "MKModifier_ActivateModifier",
        "TagAssistModifierObject_Activate",
        "GetModifierManager",
        "LoadModifierAssets",
        "MKObject_SetPos",
        "MKObject_GetPos",
        "GetScript0",
        "GetScript1",
        "MKScript_GetFunctionID",
        "MKScript_GetVar",
        "PlayerInfo_SetMeter",
        "PlayerInfo_RefreshMeter",
        "PlayerInfo_GetDrone",
        "AIDrone_Set",
        "SetKryptCharacter",
        "SetKryptCharacterL",
        "AnimationToolCode",
        "FName_FName",
        "GetNames",
        "USkeletalMeshComponent_GetBoneName",
        "XInputGetState_Hook",
        "GetScaleform",
        "ProcessDOFSettings"
    };

    return szPatternNames[id];
}

uintptr_t _pattern(EPatternID id)
{
    if (id >= PATID_Total_Patterns)
        return 0;

    return PatternSolver::ms_patterns[id];
}
