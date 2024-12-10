#pragma once
#include "..\utils.h"
#include "GameInfo.h"
#include "MKCharacter.h"
#include "PlayerInfo.h"
#include "MKStructs.h"

void MKProcDispatch();
void Dispatch(int64 ptr, int a2);
void RecordEvent(int64 eventID, int64 a2, int64 a3, int64 a4);

MKCharacter* GetObj(PLAYER_NUM plr);
PlayerInfo*  GetInfo(PLAYER_NUM plr);

void HideHUD();
void ShowHUD();

void SlowGameTimeForXTicks(float speed, int ticks);

unsigned int _hash(const char* input);

// wrappers

void GetCharacterPosition(FVector* vec, PLAYER_NUM plr);
char* GetCharacterName(PLAYER_NUM plr);

void SetCharacterMKX(PLAYER_NUM plr, char* name);
void SetCharacterAI(PLAYER_NUM plr, char* script, int level);