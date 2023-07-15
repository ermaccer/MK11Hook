#pragma once
#include "TArray.h"
#include "FVector.h"
#include "FQuat.h"
#include "FName.h"
#include "..\utils.h"

struct FBoneAtom {
	FQuat Rotation;
	FVector Translation;
	float JointRadius;
	FVector Scale;
};


struct FSkeletonPose {
	char pad[16];
	TArray<FBoneAtom> BoneAtoms;
};


class USkeleton {
public:
	void GetBoneName(FName& name, int BoneIndex);
};


class USkeletalMeshComponent {
public:
	char pad[0x700];
	FSkeletonPose pose;

	USkeleton* GetSkeleton();
	void GetBoneName(FName& name, int BoneIndex);
};