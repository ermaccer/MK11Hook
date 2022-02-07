#include "MKCharacter.h"
#include "mk10utils.h"
#include "mk11.h"
#include <iostream>
#include <Windows.h>
#include "unreal/FName.h"

void MKCharacter::SetLife(float life)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1404C80A0))(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	((void(__fastcall*)(MKCharacter*, FVector*))_addr(0x1411619F0))(this, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1404C3D80))(this, speed);
}


void MKCharacter::SetEasyKrushingBlows(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404C71E0))(this, enable, 1);
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

void MKCharacter::ClearAbilities()
{
	((void(__fastcall*)(MKCharacter*))_addr(0x14048D8A0))(this);
}

CharacterInfo * MKCharacter::GetCharacterData(int unk)
{
	CharacterInfo* inf = ((CharacterInfo*(__fastcall*)(MKCharacter*,int))_addr(0x140C0E130))(this, unk);

	printf("========\n");
	printf("PTR: %x\n", inf);
	printf("Character: %s\n", inf->Name);
	printf("Class: %s\n", inf->CharacterClass);
	printf("CAP: %s %d %d 2: %s %d %d\n", inf->CAPs->cap[0].Name, inf->CAPs->cap[0].unk1, inf->CAPs->cap[0].unk2,
		inf->CAPs->cap[1].Name, inf->CAPs->cap[1].unk1, inf->CAPs->cap[1].unk2);
	printf("Model: %s\n", inf->CAPPath);
	printf("Asset: %s\n", inf->CharacterAssetPath);
	printf("Script: %s\n", inf->ScriptName);
	printf("ScriptAssets: %s\n", inf->CommonScriptAssets);
	printf("Root: %s\n", inf->RootPath);
	printf("============\n");


	return inf;

}

void MKCharacter::ActivateHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140DC01F0))(this, 0.5);
}

void MKCharacter::KillHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140DC01C0))(this, 0.5);
}

void MKCharacter::SetBoneSize(const char * name, float size)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(int64, FName*, float))_addr(0x1453EBB40))(*(int64*)((int64)this + 0x250), &fname,  size);
}

void MKCharacter::GetBonePos(const char * name, FVector * pos)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName, FVector*))_addr(0x140DB9820))(this, fname, pos);
}

void MKCharacter::GetBoneRot(const char * name, FRotator * rot)
{
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName, FRotator*))_addr(0x1404A4DC0))(this, fname, rot);
}

int64 MKCharacter::GetSkeleton()
{
	return *(int64*)(this + 592);
}

