#include "MKCharacter.h"
#include "mk10utils.h"
#include "mk11.h"
#include <iostream>
#include <Windows.h>
#include "unreal/FName.h"

void MKCharacter::SetLife(float life)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1404CC300))(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	((void(__fastcall*)(MKCharacter*, FVector*))_addr(0x14117AC20))(this, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1404C7FE0))(this, speed);
}


void MKCharacter::SetEasyKrushingBlows(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404CB440))(this, enable, 1);
}

void MKCharacter::SetInfiniteKrushingBlows(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404CE6A0))(this, enable, 1);
}

void MKCharacter::SetFastUppercutRecovery(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404CD240))(this, enable, 1);
}

void MKCharacter::SetKrushingBlowsDisabled(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404CC250))(this, enable, 1);
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
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404CADD0))(this, enable, 1);
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
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140DD9030))(this, 0.5);
}

void MKCharacter::KillHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140DD9000))(this, 0.5);
}

void MKCharacter::SetBoneSize(const char * name, float size)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(int64, FName*, float))_addr(0x141A39B30))(*(int64*)((int64)this + 0x250), &fname,  size);
}

void MKCharacter::GetBonePos(const char * name, FVector * pos)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName, FVector*))_addr(0x140DD2660))(this, fname, pos);
}

void MKCharacter::GetBoneRot(const char * name, FRotator * rot)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName, FRotator*))_addr(0x1404A9220))(this, fname, rot);
}

void MKCharacter::ExecuteScript(MKScript* script, int function)
{
	((void(__thiscall*)(MKCharacter*, MKScript*, int, int))_addr(0x1404D5790))(this, script, function, 1);
}

MKScript* MKCharacter::GetMyScript()
{
	return *(MKScript**)(this + 0xA7D8);
}

VMProc* MKCharacter::GetMyProc()
{
	return *(VMProc**)(this + 0x10E0);
}

USkeletalMeshComponent* MKCharacter::GetSkeleton()
{
	return *(USkeletalMeshComponent**)((int64)this + 0x250);
}
