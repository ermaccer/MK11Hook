#pragma once
#include <string>
#include <vector>
#include "..\utils.h"
#include "..\mk\GameInfo.h"

struct eAbilityNameEntry {
	std::string chr;
	const char* abNames[TOTAL_ABILITIES] = {};

	eAbilityNameEntry();
};

class eAbiltityNames {
public:
	static std::vector<eAbilityNameEntry> m_aAbilityNames;
	static void Init();
	static eAbilityNameEntry* Get(const char* chrName);
	static int GetAmount(eAbilityNameEntry* ability);

};