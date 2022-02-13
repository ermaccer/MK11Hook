#pragma once
#include "unreal/FName.h"
#include "MKStructs.h"
enum eMeterValues {
	BAR_Offensive,
	BAR_Defensive
};

class PlayerInfo {
public:
	void SetMeter(eMeterValues type, float value);
	void SetDamageMult(float value);
	void SetColor(FName color, FVector* value);
};