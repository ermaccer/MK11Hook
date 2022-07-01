#include "MKCharacter.h"
#include "mk10utils.h"
#include "mk11.h"
#include <iostream>
#include <Windows.h>
#include "unreal/FName.h"

void MKCharacter::SetLife(float life)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1404C8830))(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	((void(__fastcall*)(MKCharacter*, FVector*))_addr(0x1411608B0))(this, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1404C4510))(this, speed);
}


void MKCharacter::SetEasyKrushingBlows(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404C7970))(this, enable, 1);
}

void MKCharacter::SetInfiniteKrushingBlows(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404CABD0))(this, enable, 1);
}

void MKCharacter::SetFastUppercutRecovery(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404C9770))(this, enable, 1);
}

int MKCharacter::GetAbility()
{
	return *(int*)(this + 64304);
}

FVector MKCharacter::GetScale()
{
	int64 obj = *(int64*)(this + 32);
	return *(FVector*)(obj + 0x134);
}

void MKCharacter::SetAbility(unsigned int id)
{
	*(int*)(this + 64304) = id;
}

void MKCharacter::SetCombos(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404C7300))(this, enable, 1);
}

float MKCharacter::GetLife()
{
	return 	*(float*)(this + 3104);
}

void MKCharacter::ClearAbilities()
{
	*(int*)(this + 64304) = 0;
}

void MKCharacter::ActivateHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140DC05C0))(this, 0.5);
}

void MKCharacter::KillHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140DC0590))(this, 0.5);
}

void MKCharacter::SetBoneSize(const char * name, float size)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(int64, FName*, float))_addr(0x141A30590))(*(int64*)((int64)this + 0x250), &fname,  size);
}

void MKCharacter::GetBonePos(const char * name, FVector * pos)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName, FVector*))_addr(0x140DB9BF0))(this, fname, pos);
}

void MKCharacter::GetBoneRot(const char * name, FRotator * rot)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName, FRotator*))_addr(0x1404A5550))(this, fname, rot);
}

void MKCharacter::ExecuteScript(MKScript* script, int function)
{
	((void(__thiscall*)(MKCharacter*, MKScript*, int, int))_addr(0x1404D1CC0))(this, script, function, 1);
}

MKScript* MKCharacter::GetMyScript()
{
	return *(MKScript**)(this + 0xA7D8);
}

VMProc* MKCharacter::GetMyProc()
{
	return *(VMProc**)(this + 0x10E0);
}


