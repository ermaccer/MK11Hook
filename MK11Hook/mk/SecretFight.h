#pragma once
#include "..\utils.h"

class SecretFightData {
public:
	char pad[328];
	const char* challengeName;
	int	 challengeSet;


	bool IsSet();
	bool IsSet_Hooked();
	bool IsChallengeMet();
	bool IsChallengeMet_Hooked();
};