#include "PlayerInfo.h"
#include <iostream>

void PlayerInfo::SetMeter(eMeterValues type, float value)
{
	static uintptr_t pat = _pattern(PATID_PlayerInfo_SetMeter);
	if (pat)
		((void(__fastcall*)(PlayerInfo*, int, float))pat)(this, type, value);
}

void PlayerInfo::SetDamageMult(float value)
{
	*(float*)((int64)this + 1000) = value;
	*(float*)((int64)this + 1004) = value;
	*(float*)((int64)this + 1008) = value;
}

void PlayerInfo::RefreshMeter(bool value)
{
	static uintptr_t pat = _pattern(PATID_PlayerInfo_RefreshMeter);
	if (pat)
		((void(__fastcall*)(PlayerInfo*, bool))pat)(this,value);
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

AIDrone* PlayerInfo::GetDrone()
{
	static uintptr_t pat = _pattern(PATID_PlayerInfo_GetDrone);
	if (pat)
		return	((AIDrone*(__fastcall*)(PlayerInfo*))pat)(this);
	return nullptr;
}

void AIDrone::Set(const char* script, int unk)
{
	static uintptr_t pat = _pattern(PATID_AIDrone_Set);
	if (pat)
		((void(__fastcall*)(AIDrone*, const char*, int))pat)(this, script, unk);
}
