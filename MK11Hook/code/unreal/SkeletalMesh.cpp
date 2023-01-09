#include "SkeletalMesh.h"
#include "..\mk11.h"

void USkeletalMeshComponent::GetBoneName(FName& name, int BoneIndex)
{
	((void(__fastcall*)(USkeletalMeshComponent*,FName&, int))_addr(0x141A30C40))(this, name, BoneIndex);
}
