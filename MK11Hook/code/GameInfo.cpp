#include "GameInfo.h"
#include "mk11.h"
#include "mk10utils.h"

FGGameInfo* GetGameInfo()
{
	return *(FGGameInfo**)_addr(GFG_GAME_INFO);
}

void FGGameInfo::SetStage(const char* stage)
{
	((void(__thiscall*)(FGGameInfo*, const char*))_addr(0x140599CD0))(this, stage);
}

void FGGameInfo::ResetStageInteractables()
{
	int64 bgnd_info = *(int64*)(this + 80);

	((void(__fastcall*)(int64))_addr(0x14045BE30))(bgnd_info);
	((void(__fastcall*)(int64))_addr(0x14045C370))(bgnd_info);
	((void(__fastcall*)(int64))_addr(0x14045BDA0))(bgnd_info);
}
