#include "GameInfo.h"

uintptr_t FGGameInfo::pGameInfo = 0;

FGGameInfo* GetGameInfo()
{
	return *(FGGameInfo**)FGGameInfo::pGameInfo;
}

int GetGameState()
{
	return *(int*)((*(int64*)FGGameInfo::pGameInfo) + 1944);
}

void FGGameInfo::FindGameInfo()
{
	static uintptr_t pat = _pattern(PATID_FGGameInfo_FindGameInfo);
	if (pat)
	{
		unsigned int offset = *(unsigned int*)(pat);
		FGGameInfo::pGameInfo =(pat + offset + 4);
	}
}

void FGGameInfo::SetStage(const char* stage)
{
	static uintptr_t pat = _pattern(PATID_FGGameInfo_SetStage);
	if (pat)
		((void(__thiscall*)(FGGameInfo*, const char*))pat)(this, stage);
}

void FGGameInfo::ResetStageInteractables()
{
	int64 bgnd_info = *(int64*)(this + 80);

	static uintptr_t pat = _pattern(PATID_FGGameInfo_ResetStageInteractables0);
	if (pat)
		((void(__fastcall*)(int64))pat)(bgnd_info);

	static uintptr_t pat1 = _pattern(PATID_FGGameInfo_ResetStageInteractables1);
	if (pat1)
		((void(__fastcall*)(int64))pat1)(bgnd_info);

	static uintptr_t pat2 = _pattern(PATID_FGGameInfo_ResetStageInteractables2);
	if (pat2)
		((void(__fastcall*)(int64))pat2)(bgnd_info);
}

PlayerInfo* FGGameInfo::GetInfo(PLAYER_NUM plr)
{
	static uintptr_t pat = _pattern(PATID_FGGameInfo_GetInfo);
	if (pat)
		return ((PlayerInfo*(__fastcall*)(FGGameInfo*, PLAYER_NUM))pat)(this, plr);
	return nullptr;
}