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
	char data[150] = {};
public:
	GearItem(unsigned char version, ItemDefinition* item ,unsigned short  unk, unsigned char unk2, int level, short unk3);

	bool Valid();
	int64 GetCharacterKey();
	char* GetName();

	ItemDefinition GetGUID();
};


void EquipItem(PLAYER_NUM plr, GearItem* item);