#include "PlayerInfo.h"
#include "mk10utils.h"
#include "mk11.h"
#include "eSettingsManager.h"
#include <iostream>

void PlayerInfo::SetMeter(eMeterValues type, float value)
{
	((void(__fastcall*)(PlayerInfo*, int, float))_addr(0x1405FA450))(this, type, value);
}

void PlayerInfo::SetDamageMult(float value)
{
	*(float*)(this + 1000) = value;
	*(float*)(this + 1004) = value;
	*(float*)(this + 1008) = value;
}

void PlayerInfo::SetColor(FName color, FVector* value)
{
	//PlayerInfo* info = (PlayerInfo*)((int64)this - 1056);
	if (GetGameInfo())
	{
		PlayerInfo* p1 = GetInfo(PLAYER1);
		PlayerInfo* p2 = GetInfo(PLAYER2);
		if (p1 || p2)
		{
			printf("THIS - %x P1: %x P2: %x\n", this, (int64)GetInfo(PLAYER1) + 1056, (int64)GetInfo(PLAYER2) + 1056);
		}
	}


	//character_info* chr = *(character_info**)((int64)this - 1056 + 216);
	//if (chr)
	//	printf("Blood for %s\n", chr->name);


	*value = { 0.5,0.5,0 };
	((void(__fastcall*)(PlayerInfo*, FName, FVector*))_addr(0x140E4E240))(this, color, value);
}

