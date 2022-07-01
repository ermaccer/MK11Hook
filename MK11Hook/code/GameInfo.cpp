#include "GameInfo.h"
#include "mk11.h"
#include "mk10utils.h"

MKScript* GetScript(const char* name)
{
	int64 package = ((int64(__fastcall*)(const char*))_addr(0x140941B20))("MainlineManaged.SystemPackages.FightingArt");
	if (package)
	{
		MKScript* script = ((MKScript*(__fastcall*)(int64, const char*, int,int,int))_addr(0x140EA8830))(package,name,1,1,0);
		return script;

	}
	return nullptr;
}

int64 GetScriptVar(MKScript* script, const char* name)
{
	return ((int64(__fastcall*)(MKScript*, const char*, int))_addr(0x14114F750))(script, name, 1);
}

FGGameInfo* GetGameInfo()
{
	return *(FGGameInfo**)_addr(GFG_GAME_INFO);
}

int GetGameState()
{
	return *(int*)((*(int64*)_addr(GFG_GAME_INFO)) + 1944);
}

void FGGameInfo::SetStage(const char* stage)
{
	((void(__thiscall*)(FGGameInfo*, const char*))_addr(0x14059A460))(this, stage);
}

void FGGameInfo::ResetStageInteractables()
{
	int64 bgnd_info = *(int64*)(this + 80);

	((void(__fastcall*)(int64))_addr(0x14045C5C0))(bgnd_info);
	((void(__fastcall*)(int64))_addr(0x14045CB00))(bgnd_info);
	((void(__fastcall*)(int64))_addr(0x14045C530))(bgnd_info);
}

PlayerInfo* FGGameInfo::GetInfo(PLAYER_NUM plr)
{
	return ((PlayerInfo*(__fastcall*)(FGGameInfo*, PLAYER_NUM))_addr(0x14056F8F0))(this, plr);
}

int MKScript::GetFunctionID(int hash)
{
	return ((int(__thiscall*)(MKScript*, int, int))_addr(0x14114C5F0))(this, hash, 0);
}

int64 MKScript::GetVar(const char* name)
{
	return ((int64(__fastcall*)(MKScript*, const char*, int))_addr(0x14114F750))(this, name, 1);
}

unsigned int MKScript::GetCurrentFunc()
{
	return *(unsigned int*)(this + 360);
}
