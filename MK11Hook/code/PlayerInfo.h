#pragma once
#include "unreal/FName.h"
#include "MKStructs.h"
enum eMeterValues {
	BAR_Offensive,
	BAR_Defensive
};

enum eButton : int {
	BUTTON_UP = 1,
	BUTTON_DOWN = 2,
	BUTTON_LEFT = 4,
	BUTTON_RIGHT = 8,
	BUTTON_BP = 16,
	BUTTON_FK = 32,
	BUTTON_FP = 64,
	BUTTON_BK = 128,
	BUTTON_UNK = 256,
	BUTTON_RESET = 512,
	BUTTON_ASSIST = 2048,
	BUTTON_THROW = 4096,
	BUTTON_INTERACT = 8192,
	BUTTON_FLIP_STANCE = 16384,
	BUTTON_BLOCK = 32768
};

struct ButtonInfo {
	eButton id;
	int pad[3];
};


struct HitCounter {
	int hits;
	int airHits;
	int combo;
};

struct Gamepad {
	char pad[0x1C];
	ButtonInfo buttons;
	ButtonInfo oldButtons;
};


class AIDrone {
public:
	void Set(const char* script, int unk);
};

class PlayerInfo {
public:
	char _pad[48];
	Gamepad* pad;

	void SetMeter(eMeterValues type, float value);
	void SetDamageMult(float value);
	void RefreshMeter(bool value);
	float GetMeter(eMeterValues type);

	HitCounter GetHits();

	AIDrone* GetDrone();
};