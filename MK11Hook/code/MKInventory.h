#pragma once
#include "mk11.h"

class ItemDefinition {
private:
public:
	unsigned int guid[4] = {};
	ItemDefinition();
	ItemDefinition(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4);
};

class GearItem {
private:
	char pad[24];
	ItemDefinition def;
	char data[650] = {};
public:
	GearItem(int64 guid1, int64 guid2, int unk);
	bool Valid();
	int64 GetCharacterKey();
	char* GetName();

	ItemDefinition GetGUID();
};


void EquipItem(PLAYER_NUM plr, GearItem* item);