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


class FGGameInfo {
public:
	void SetStage(const char* stage);
	void ResetStageInteractables();
	PlayerInfo* GetInfo(PLAYER_NUM plr);
};

FGGameInfo* GetGameInfo();