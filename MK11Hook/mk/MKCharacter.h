#pragma once
#include "VMProc.h"
#include "PlayerInfo.h"
#include "CharacterDefinition.h"
#include "GameInfo.h"
#include "MKScript.h"
#include "MKObject.h"

#include "..\unreal\SkeletalMesh.h"
#include "..\unreal\FRotator.h"
#include "..\unreal\FVector.h"
#include "..\utils.h"

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



class MKCharacter : public MKObject {
public:
	void SetLife(float life);
	void SetScale(FVector* scale);
	void SetSpeed(float speed);
	void SetEasyKrushingBlows(bool enable);
	void SetInfiniteKrushingBlows(bool enable);
	void SetFastUppercutRecovery(bool enable);
	void SetKrushingBlowsDisabled(bool enable);
	void SetAbility(unsigned int id);
	void SetCombos(bool enable);
	void SetXRayInfinite(bool enable);
	void SetXRayNoRequirement(bool enable);

	void Rotate(float x, float y, float z);

	float GetLife();

	int GetAbility();
	FVector GetScale();

	void ClearAbilities();


	void ActivateHeadTracking();
	void KillHeadTracking();

	void SetBoneSize(const char* name, float size);

	void GetBonePos(const char* name, FVector* pos);
	void GetBoneRot(const char* name, FRotator* rot);


	void ExecuteScript(MKScript* script, int function);

	MKScript* GetMyScript();
	VMProc* GetMyProc();

	USkeletalMeshComponent* GetSkeleton();
};


