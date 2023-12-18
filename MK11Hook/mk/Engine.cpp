#include "Engine.h"

void MKProcDispatch()
{
	static uintptr_t pat = _pattern(PATID_MKProcDispatch);
	if (pat)
		((void(__fastcall*)())pat)();
}

void Dispatch(int64 ptr, int a2)
{
	static uintptr_t pat = _pattern(PATID_Dispatch);
	if (pat)
		((void(__fastcall*)(int64, int))pat)(ptr, a2);
}

void RecordEvent(int64 eventID, int64 a2, int64 a3, int64 a4)
{
	static uintptr_t pat = _pattern(PATID_RecordEvent);
	if (pat)
		((void(__fastcall*)(int64, int64, int64, int64))pat)(eventID, a2, a3, a4);
}

MKCharacter* GetObj(PLAYER_NUM plr)
{
	static uintptr_t pat = _pattern(PATID_GetObj);
	if (pat)
		return ((MKCharacter * (__fastcall*)(PLAYER_NUM))pat)(plr);
	return nullptr;
	
}

PlayerInfo* GetInfo(PLAYER_NUM plr)
{
	return GetGameInfo()->GetInfo(plr);
}

void HideHUD()
{
	static uintptr_t pat = _pattern(PATID_HideHUD);
	if (pat)
		((void(__fastcall*)(int, int))pat)(8, 8);

}

void ShowHUD()
{
	static uintptr_t pat = _pattern(PATID_ShowHUD);
	if (pat)
		((void(__fastcall*)(int, int))pat)(8, 8);
}


void SlowGameTimeForXTicks(float speed, int ticks)
{
	static uintptr_t pat = _pattern(PATID_SlowGameTimeForXTicks);
	if (pat)
		((void(__fastcall*)(float, int, int))pat)(speed, ticks, 0);
}

unsigned int _hash(const char* input)
{
	unsigned int result;
	int stringLength;
	int character;

	if (!input)
		return 0;
	stringLength = -1;

	do
		++stringLength;
	while (input[stringLength]);

	for (result = 0x811C9DC5; stringLength; --stringLength)
	{
		character = *(unsigned char*)input++;
		result = character ^ (unsigned int)(0x1000193 * result);
	}
	return result;
}


void GetCharacterPosition(FVector* vec, PLAYER_NUM plr)
{
	MKCharacter* obj = GetObj(plr);
	if (obj)
		obj->GetPos(vec);
}


char* GetCharacterName(PLAYER_NUM plr)
{
	int64 info = (int64)GetInfo(plr);
	character_info* chr = *(character_info**)(info + 216);
	if (chr)
		return chr->name;
	else
		return "null";
}

void SetCharacterMKX(PLAYER_NUM plr, char* name)
{
	int64 ptr = (int64)GetInfo(plr);
	CharacterDefinition* chr = (CharacterDefinition*)(ptr + 216);
	chr->Set(name, 0, 0);
}
