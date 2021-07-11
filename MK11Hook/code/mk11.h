#pragma once
#include "mk10utils.h"
#include "MKStructs.h"
#include "MKCharacter.h"
#include "MKModifier.h"
#define GFG_GAME_INFO  0x14348ED10


#define MK11HOOK_VERSION "0.4.2"

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


namespace MK11 {
	MKCharacter* GetCharacterObject(PLAYER_NUM plr);
	int64 GetCharacterInfo(PLAYER_NUM plr);


	int64 GetPlayerData(PLAYER_NUM plr);
	PLAYER_NUM GetPlayerIDFromData(int64 data);

	void GetCharacterPosition(FVector* vec, PLAYER_NUM plr);

	void HideHUD();
	void ShowHUD();



	// mkx recreation
	void SetCharacterMKX(PLAYER_NUM plr, char* name);
	void SetStage(const char* stage);
	void SetCharacter(int64 chr, char* name, int64 ptr, int64 unk);

	char* GetCharacterName(PLAYER_NUM plr);
		

	void SlowGameTimeForXTicks(float speed, int ticks);
	void SetSpeed(float speed);



	void  SetCharacterEnergy(int64 obj,int type, float energy);


	bool IsDLC(const char* name);

	void SetKryptCharacter(int64 ptr, char* name);
	void SetKryptCharacterL(int64 ptr, char* name, int unk);
	void SetKryptCharacterClass(int64 ptr, char* name, int unk);


	MKModifier* GetModifierManager();

}

namespace MK11Hooks {
	// hooks
	void  HookProcessStuff();
	void  HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4);
	int64 PostLoadHook();

	int64 HookLoadCharacter(int64 ptr, char* name);

	int64  HookSetProperty(int64 ptr, char* name, int64 unk);
	void   HookReadPropertyValue(int64 ptr, int* unk, int* value);

	int64  HookLoadouts(int64 ptr);

	void   HookDispatch(int64 ptr, int a2);


}