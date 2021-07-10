#include "MKCharacter.h"
#include "mk10utils.h"
#include "mk11.h"
#include <iostream>
#include <Windows.h>

void MKCharacter::SetLife(float life)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1404C8070))(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	((void(__fastcall*)(MKCharacter*, FVector*))_addr(0x141161920))(this, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1404C3D50))(this, speed);
}

void MKCharacter::SetMeter(eMeterValues meter, float value)
{
	((void(__fastcall*)(MKCharacter*, eMeterValues, float))_addr(0x1405FA670))(this, meter, value);
}

void MKCharacter::SetEasyKrushingBlows(bool enable)
{
	((void(__fastcall*)(MKCharacter*, int, int))_addr(0x1404C71B0))(this, enable, 1);
}

void MKCharacter::SetItem(int64 ptr, char * slot)
{
	((void(__fastcall*)(MKCharacter*, int64, char*))_addr(0x140818380))(this, ptr, slot);
}

CharacterInfo * MKCharacter::GetCharacterData(int unk)
{
	CharacterInfo* inf = ((CharacterInfo*(__fastcall*)(MKCharacter*,int))_addr(0x140C0DE60))(this, unk);

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


bool MKCharacter::IsCrouching()
{
	return ((bool(__fastcall*)(MKCharacter*))_addr(0x14047ADB0))(this);
}
