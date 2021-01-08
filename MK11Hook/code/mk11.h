#pragma once
#include "mk10utils.h"

#define GFG_GAME_INFO  0x14348BC40
#define PLAYER_STRUCTS 0x14348B488

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

struct FVector
{
	float X;
	float Y;
	float Z;
};

struct FRotator {
	int Pitch;
	int Yaw;
	int Roll;
};


namespace MK11 {

	int64 GetCharacterObject(PLAYER_NUM plr);
	int64 GetCharacterInfo(PLAYER_NUM plr);


	int64 GetPlayerData(PLAYER_NUM plr);
	PLAYER_NUM GetPlayerIDFromData(int64 data);


	void GetCharacterDefinition(PLAYER_NUM plr);
	void GetCharacterPosition(FVector* vec, PLAYER_NUM plr);

	

	void LoadAsset(const char* name);

	void __fastcall CamSetPos(int64 ptr, FVector* pos);
	void __fastcall CamSetRot(int64 ptr, FRotator* rot);

	bool IsDLC(const char* name);
}

namespace MK11Hooks {
	// hooks
	void __fastcall HookProcessStuff();
	void __fastcall HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4);

	void __fastcall HookCamSetPos(int64 ptr, FVector* pos);
	void __fastcall HookCamSetRot(int64 ptr, FRotator* rot);

	int64 __fastcall HookLoadCharacter(int64 ptr, char* name);
}