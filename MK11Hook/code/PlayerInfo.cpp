#include "PlayerInfo.h"
#include "mk10utils.h"
#include "mk11.h"
#include "eSettingsManager.h"
#include <iostream>

void PlayerInfo::SetMeter(eMeterValues type, float value)
{
	((void(__fastcall*)(PlayerInfo*, int, float))_addr(0x1405FABE0))(this, type, value);
}

void PlayerInfo::SetDamageMult(float value)
{
	*(float*)((int64)this + 1000) = value;
	*(float*)((int64)this + 1004) = value;
	*(float*)((int64)this + 1008) = value;
}

void PlayerInfo::RefreshMeter(bool value)
{
	((void(__fastcall*)(PlayerInfo*, bool))_addr(0x140602930))(this,value);
}

float PlayerInfo::GetMeter(eMeterValues type)
{
	int64 meter_ptr = ((int64)this + 16 * (type + 24));
	return *(float*)(meter_ptr + 4);
}

HitCounter PlayerInfo::GetHits()
{
	return *(HitCounter*)((int64)this + 0x430);
}
