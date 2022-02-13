#pragma once
#include "MKStructs.h"

class MKObject {
public:
	void SetPos(FVector* pos);
	void GetPos(FVector* dest);


	void SetPosHooked(FVector* pos);
};