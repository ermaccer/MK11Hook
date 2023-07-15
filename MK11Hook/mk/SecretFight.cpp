#include "SecretFight.h"
#include <iostream>

bool SecretFightData::IsSet()
{
    return ((bool(__thiscall*)(SecretFightData*))_addr(0x1405F3070))(this);
}

bool SecretFightData::IsSet_Hooked()
{
    bool result = IsSet();
    printf("Original challenge set: %d Challenge status set: %d", result, challengeSet);
    return result;
}

bool SecretFightData::IsChallengeMet()
{
    return ((bool(__thiscall*)(SecretFightData*))_addr(0x1405F2240))(this);
}

bool SecretFightData::IsChallengeMet_Hooked()
{
    bool org_challenge = IsChallengeMet();
    printf("Original challenge met: %d Challenge status set: %d", org_challenge, challengeSet);
    
    return true;
}
