#include "SkeletalMesh.h"

void USkeletalMeshComponent::GetBoneName(FName& name, int BoneIndex)
{
	static uintptr_t pat = _pattern(PATID_USkeletalMeshComponent_GetBoneName);
	if (pat)
		((void(__fastcall*)(USkeletalMeshComponent*,FName&, int))pat)(this, name, BoneIndex);
}
