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
	((void(__fastcall*)(PlayerInfo*, FName, FVector*))_addr(0x140E4E240))(this, color, value);
}

