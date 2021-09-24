#pragma once
#include "MKStructs.h"
#include "mk10utils.h"
enum eMeterValues {
	BAR_Offensive,
	BAR_Defensive
};

struct CharacterCAP {
	char* Name;
	int  unk1;
	int unk2;
};

struct CharacterCAPData {
	CharacterCAP cap[5];// dunno how many
};
struct CharacterInfo {
	char* Name;
	char pad[128];
	char* CharacterClass;
	char _pad[8];
	char* AssetDefinition;
	char __pad[40];
	char* ScriptName;
	char ___pad[8];
	char* ScriptAssets;
	char ____pad[24];
	char* CommonScriptAssets;
	char _____pad[8];
	char* CharacterAssetPath;
	char ______pad[24];
	char* CAPPath;
	char _______pad[8];
	char* RootPath;
	char ________pad[48];
	CharacterCAPData* CAPs;
	char _________pad[8];
	char* Package;
	char __________pad[8];
	void* AudioTable;
};


// wrapper for old functions
class MKCharacter {
public:
	void SetLife(float life);
	void SetScale(FVector* scale);
	void SetSpeed(float speed);
	void SetMeter(eMeterValues meter, float value);
	void SetEasyKrushingBlows(bool enable);
	void SetItem(int64 ptr, char* slot);
	void SetBreakersActive(bool enable);
	void SetBreakers(int amount);

	CharacterInfo* GetCharacterData(int unk);

	bool IsCrouching();
};

