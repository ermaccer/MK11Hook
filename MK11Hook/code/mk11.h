#pragma once
#include "mk10utils.h"

#define GFG_GAME_INFO  0x14348ED10
#define PLAYER_STRUCTS 0x14348E558


#define MK11HOOK_VERSION "0.3.5"

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


struct FLinearColor
{
	float A;
	float B;
	float G;
	float R;
};


struct FRotator {
	int Pitch;
	int Yaw;
	int Roll;
};

struct MKCameraObj {
	char pad[0x6BC];
	FVector pos;
	FRotator rot;
	float   FOV;
};


struct character_info {
	char	name[16];
};


namespace MK11 {

	int64 GetCharacterObject(PLAYER_NUM plr);
	int64 GetCharacterInfo(PLAYER_NUM plr);


	int64 GetPlayerData(PLAYER_NUM plr);
	PLAYER_NUM GetPlayerIDFromData(int64 data);

	void GetCharacterPosition(FVector* vec, PLAYER_NUM plr);

	void HideHUD();
	void ShowHUD();
	void PauseGame(bool enable);



	// mkx recreation
	void SetCharacterMKX(PLAYER_NUM plr, char* name);

	void SetCharacter(int64 chr, char* name, int64 ptr, int64 unk);

	PLAYER_NUM GetIDFromData(int64 data);
	char* GetCharacterName(PLAYER_NUM plr);
		
	// todo
	void SetControlScheme(int64 obj, int preset);

	void SlowGameTimeForXTicks(float speed, int ticks);
	void SetSpeed(float speed);


	void SetStage(const char* stage);


	void  SetCharacterSpeed(PLAYER_NUM plr, float speed);
	void  SetCharacterScale(PLAYER_NUM plr, FVector* scale);
	void  SetCharacterLife(int64 obj, float life);
	void  SetCharacterMeter(int64 obj, float meter);
	void  SetCharacterEnergy(int64 obj,int type, float energy);
	void  SetCharacterEasyKB(int64 obj, int value);

	int64 GetCharacterMovie(int64 chr, int unk, char* buffer, int id);
	int64 GetCinemaByName(char* a1, char* a2, char* a3, int id);


	void __fastcall CamSetPos(int64 ptr, FVector* pos);
	void __fastcall CamSetRot(int64 ptr, FRotator* rot);

	void __fastcall ActorCamSetPos(int64 ptr, FVector* pos);
	void __fastcall ActorCamSetRot(int64 ptr, FRotator* rot);
	bool IsDLC(const char* name);
}

namespace MK11Hooks {
	// hooks
	void __fastcall HookProcessStuff();
	void __fastcall HookStartupFightRecording(int64 eventID, int64 a2, int64 a3, int64 a4);

	void __fastcall HookCamSetPos(int64 ptr, FVector* pos);
	void __fastcall HookCamSetRot(int64 ptr, FRotator* rot);

	void __fastcall HookActorCamSetPos(int64 ptr, FVector* pos);
	void __fastcall HookActorCamSetRot(int64 ptr, FRotator* rot);

	int64 __fastcall HookLoadCharacter(int64 ptr, char* name);
	void			 HookSetCharacter(int64 chr, char* name, int64 ptr, int64 unk);
	void __fastcall  UpdatePauseState(int64 ptr);


}