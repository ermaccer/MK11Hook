#pragma once
enum eMeterValues {
	BAR_Offensive,
	BAR_Defensive
};

class PlayerInfo {
public:
	void SetMeter(eMeterValues type, float value);
	void SetDamageMult(float value);
};