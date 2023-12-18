#pragma once
#include "PlayerInfo.h"
#include "../utils.h"

#define TOTAL_ABILITIES 20


enum PLAYER_NUM
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
};


enum eCharacterClass {
	Base,
	TestCharacters,
	Generated,
	NPCs,
	TOTAL_CHARACTER_CLASSES
};

class FGGameInfo {
public:
	static void FindGameInfo();
	static uintptr_t pGameInfo;
	void SetStage(const char* stage);
	void ResetStageInteractables();
	PlayerInfo* GetInfo(PLAYER_NUM plr);
};

FGGameInfo* GetGameInfo();
int GetGameState();