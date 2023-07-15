#pragma once
#include "..\utils.h"

class CharacterDefinition {
public:
	void Set(const char* name, int64 loadout, int64 unk);
	void SetLevel(int level);
	void SetAlternatePalette(bool set);
	void SetLoadout(int64 loadout);
};