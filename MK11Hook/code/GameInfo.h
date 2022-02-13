#pragma once
#include "PlayerInfo.h"

enum  PLAYER_NUM
{
	INVALID_PLAYER_NUM = -1,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
	CPU_PLAYER,
	NOT_CPU_PLAYER,
	BACKGROUND_PLAYER
};


class MKScript {
public:
	int GetFunctionID(int hash);
};


class MKScriptVM {
private:
	char data[14 * 4];
public:
	MKScriptVM(int val);
	void Set(MKScript*, unsigned int funcHash);
	void Run();
	
	static void BeginVar();
	static void PushVar(void* var);
};

class FGGameInfo {
public:
	void SetStage(const char* stage);
	void ResetStageInteractables();
	PlayerInfo* GetInfo(PLAYER_NUM plr);


	MKScript* GetFightScript();
	MKScript* GetGenericScript();
};

MKScript* GetScript(const char* name);

FGGameInfo* GetGameInfo();