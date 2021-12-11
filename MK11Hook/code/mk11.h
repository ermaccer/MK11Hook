#pragma once
#include "mk10utils.h"
#include "MKStructs.h"
#include "MKCharacter.h"
#include "MKModifier.h"
#define GFG_GAME_INFO  0x1434990A0


#define MK11HOOK_VERSION "0.4.7"

#define TOTAL_ABILITIES 20

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


enum eCharacterClass {
	Base,
	TestCharacters,
	Generated,
	NPCs,
	TOTAL_CHARACTER_CLASSES
};



MKCharacter* GetObj(PLAYER_NUM plr);
int64 GetInfo(PLAYER_NUM plr);


void GetCharacterPosition(FVector* vec, PLAYER_NUM plr);

void HideHUD();
void ShowHUD();



// mkx recreation
void SetCharacterMKX(PLAYER_NUM plr, char* name);
void SetStage(const char* stage);


// definition functions
void SetCharacter(int64 chr, char* name, int64 ptr, int64 unk);
void SetCharacterLevel(int64 chr, int level);
void SetCharacterAltPal(int64 chr, int value);
void SetCharacterLoadout(int64 chr, int64 loadout);

char* GetCharacterName(PLAYER_NUM plr);
	

void SlowGameTimeForXTicks(float speed, int ticks);



void  SetCharacterEnergy(int64 obj,int type, float energy);


bool IsDLC(const char* name);

void SetKryptCharacter(int64 ptr, char* name);
void SetKryptCharacterL(int64 ptr, char* name, int unk);
void SetKryptCharacterClass(int64 ptr, char* name, int unk);


MKModifier* GetModifierManager();
void		LoadModifierAssets();


namespace MK11Hooks {
	// hooks
	void  HookProcessStuff();
	void  PreLoadHook(int64 a1, int64 a2, int a3);
	void  HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4);
	void  PostLoadHook();

	int64 HookLoadCharacter(int64 ptr, char* name);

	int64  HookSetProperty(int64 ptr, char* name, int64 unk);
	void   HookReadPropertyValue(int64 ptr, int* unk, int* value);

	int64  HookLoadouts(int64 ptr);

	void   HookDispatch(int64 ptr, int a2);

	void   HookSetSelectScreen(int64 ptr, PLAYER_NUM plr, int teamNo, char *name, int level, int64 loadout, bool altPalette);
	void   HookSetLadderScreen(int64 chr, char* name, int64 ptr, int64 unk);


}