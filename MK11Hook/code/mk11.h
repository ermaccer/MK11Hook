#pragma once
#include "GameInfo.h"
#include "mk10utils.h"
#include "MKStructs.h"
#include "MKCharacter.h"
#include "MKModifier.h"
#include "PlayerInfo.h"
#include "CharacterDefinition.h"

#define GFG_GAME_INFO  0x1434BA060 


#define MK11HOOK_VERSION "0.5.5"

#define TOTAL_ABILITIES 20


enum eCharacterClass {
	Base,
	TestCharacters,
	Generated,
	NPCs,
	TOTAL_CHARACTER_CLASSES
};



MKCharacter* GetObj(PLAYER_NUM plr);
PlayerInfo* GetInfo(PLAYER_NUM plr);


void GetCharacterPosition(FVector* vec, PLAYER_NUM plr);

void HideHUD();
void ShowHUD();



// mkx recreation
void SetCharacterMKX(PLAYER_NUM plr, char* name);
char* GetCharacterName(PLAYER_NUM plr);
	

void SlowGameTimeForXTicks(float speed, int ticks);
void SetKryptCharacter(int64 ptr, char* name);
void SetKryptCharacterL(int64 ptr, char* name, int unk);
void SetKryptCharacterClass(int64 ptr, char* name, int unk);


MKModifier* GetModifierManager();
void		LoadModifierAssets();


unsigned int HashString(const char* input);


namespace MK11Hooks {
	// hooks
	void  HookProcessStuff();
	void  HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4);

	void   HookReadPropertyValue(int64 ptr, int* unk, int* value);
	int64  HookSetProperty(int64 ptr, char* name, int64 unk);

	void   HookDispatch(int64 ptr, int a2);

	void   HookSetSelectScreen(int64 ptr, PLAYER_NUM plr, int teamNo, char *name, int level, int64 loadout, bool altPalette);
	void   HookSetLadderScreen(CharacterDefinition* chr, char* name, int64 ptr, int64 unk);
}