#pragma once
#include "..\utils.h"
#include "..\unreal\FVector.h"

class MKObject {
public:
	void SetPos(FVector* pos);
	void GetPos(FVector* dest);
};