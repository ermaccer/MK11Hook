#include "GameInfo.h"
#include "mk11.h"
#include "mk10utils.h"

MKScript* GetScript(const char* name)
{
	int64 package = ((int64(__fastcall*)(const char*))_addr(0x1409413B0))("MainlineManaged.SystemPackages.FightingArt");
	if (package)
	{
		MKScript* script = ((MKScript*(__fastcall*)(int64, const char*, int,int,int))_addr(0x140EA84C0))(package,name,1,1,0);
		return script;

	}
	return nullptr;
}

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

PlayerInfo* FGGameInfo::GetInfo(PLAYER_NUM plr)
{
	return ((PlayerInfo*(__fastcall*)(FGGameInfo*, PLAYER_NUM))_addr(0x14056F160))(this, plr);
}

MKScript* FGGameInfo::GetFightScript()
{
	return ((MKScript * (__thiscall*)(FGGameInfo*))_addr(0x14056F1D0))(this);
}

MKScript* FGGameInfo::GetGenericScript()
{
	return ((MKScript * (__thiscall*)(FGGameInfo*, int))_addr(0x1405700E0))(this, 1);
}

int MKScript::GetFunctionID(int hash)
{
	return ((int(__thiscall*)(MKScript*, int, int))_addr(0x14114D730))(this, hash, 0);
}

MKScriptVM::MKScriptVM(int val)
{
	((void(__fastcall*)(MKScriptVM*, int))_addr(0x14113D210))(this,val);
}


void MKScriptVM::Set(MKScript* script, unsigned int funcHash)
{
	((void(__fastcall*)(MKScriptVM*, MKScript*, unsigned int))_addr(0x14115CF30))(this, script, funcHash);

}

void MKScriptVM::Run()
{
	((void(__fastcall*)(MKScriptVM*))_addr(0x14114AE00))(this);
}

void MKScriptVM::BeginVar()
{
	((void(__fastcall*)())_addr(0x1411434E0))();

}

void MKScriptVM::PushVar(void* var)
{
	((void(__fastcall*)(void*))_addr(0x141159650))(var);
}
