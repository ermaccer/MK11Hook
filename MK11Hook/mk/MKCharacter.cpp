#include "MKCharacter.h"
#include <iostream>
#include <Windows.h>
#include "../unreal/FName.h"
#include "Engine.h"

void MKCharacter::SetLife(float life)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetLife);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float))pat)(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	int64 obj = *(int64*)(this + 32);

	static uintptr_t pat = _pattern(PATID_MKCharacter_SetScale);
	if (pat)
		((void(__fastcall*)(int64, FVector*))pat)(obj, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetSpeed);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float))pat)(this, speed);
}


void MKCharacter::SetEasyKrushingBlows(bool enable)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetEasyKrushingBlows);
	if (pat)
		((void(__fastcall*)(MKCharacter*, int, int))pat)(this, enable, 1);
}

void MKCharacter::SetInfiniteKrushingBlows(bool enable)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetInfiniteKrushingBlows);
	if (pat)
		((void(__fastcall*)(MKCharacter*, int, int))pat)(this, enable, 1);
}

void MKCharacter::SetFastUppercutRecovery(bool enable)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetFastUppercutRecovery);
	if (pat)
		((void(__fastcall*)(MKCharacter*, int, int))pat)(this, enable, 1);
}

void MKCharacter::SetKrushingBlowsDisabled(bool enable)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetKrushingBlowsDisabled);
	if (pat)
		((void(__fastcall*)(MKCharacter*, int, int))pat)(this, enable, 1);
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
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetCombos);
	if (pat)
		((void(__fastcall*)(MKCharacter*, int, int))pat)(this, enable, 1);
}

void MKCharacter::SetXRayInfinite(bool enable)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetInfiniteXrays);
	if (pat)
		((void(__fastcall*)(MKCharacter*, int, int))pat)(this, enable, 1);
}

void MKCharacter::SetXRayNoRequirement(bool enable)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetXrayNoRequirement);
	if (pat)
		((void(__fastcall*)(MKCharacter*, int, int))pat)(this, enable, 1);
}

void MKCharacter::Rotate(float x, float y, float z)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_Rotate);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float, float, float))pat)(this, x, y, z);
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
	static uintptr_t pat = _pattern(PATID_MKCharacter_ActivateHeadTracking);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float))pat)(this, 0.5);
}

void MKCharacter::KillHeadTracking()
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_KillHeadTracking);
	if (pat)
		((void(__fastcall*)(MKCharacter*, float))pat)(this, 0.5);
}

void MKCharacter::SetBoneSize(const char * name, float size)
{
	FName fname(name, FNAME_Add, 1);
	static uintptr_t pat = _pattern(PATID_MKCharacter_SetBoneSize);
	if (pat)
		((void(__fastcall*)(int64, FName*, float))pat)(*(int64*)((int64)this + 0x250), &fname,  size);
}

void MKCharacter::GetBonePos(const char * name, FVector * pos)
{
	FName fname(name, FNAME_Add, 1);
	static uintptr_t pat = _pattern(PATID_MKCharacter_GetBonePos);
	if (pat)
		((void(__fastcall*)(MKCharacter*, FName, FVector*))pat)(this, fname, pos);
}

void MKCharacter::GetBoneRot(const char * name, FRotator * rot)
{
	FName fname(name, FNAME_Add, 1);
	static uintptr_t pat = _pattern(PATID_MKCharacter_GetBoneRot);
	if (pat)
		((void(__fastcall*)(MKCharacter*, FName, FRotator*))pat)(this, fname, rot);
}

void MKCharacter::ExecuteScript(MKScript* script, int function)
{
	static uintptr_t pat = _pattern(PATID_MKCharacter_ExecuteScript);
	if (pat)
		((void(__thiscall*)(MKCharacter*, MKScript*, int, int))pat)(this, script, function, 1);
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
