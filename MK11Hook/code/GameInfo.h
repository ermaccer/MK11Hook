#pragma once
#include "PlayerInfo.h"
#include "mk10utils.h"

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

class FGGameInfo {
public:
	void SetStage(const char* stage);
	void ResetStageInteractables();
	PlayerInfo* GetInfo(PLAYER_NUM plr);
};

MKScript* GetScript(const char* name);

int64 GetScriptVar(MKScript* script, const char* name);

FGGameInfo* GetGameInfo();