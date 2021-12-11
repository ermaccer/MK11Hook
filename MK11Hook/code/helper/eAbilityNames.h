#pragma once
#include <string>
#include <vector>
#include "..\mk11.h"

struct eAbilityNameEntry {
	std::string chr;
	const char* abNames[TOTAL_ABILITIES] = {};

	eAbilityNameEntry();
};

class eAbiltityNames {
public:
	static std::vector<eAbilityNameEntry> m_aAbilityNames;
	static void Init();
	static eAbilityNameEntry Get(const char* chrName);

};