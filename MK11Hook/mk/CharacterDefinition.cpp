#include "CharacterDefinition.h"

void CharacterDefinition::Set(const char* name, int64 loadout, int64 unk)
{
	static uintptr_t pat = _pattern(PATID_CharacterDefinition_Set);
	if (pat)
		((void(__fastcall*)(CharacterDefinition*, const char*, int64, int64))pat)(this, name, loadout, unk);
}

void CharacterDefinition::SetLevel(int level)
{
	*(int*)((int64)this + 84) = level;
}

void CharacterDefinition::SetAlternatePalette(bool set)
{
	static uintptr_t pat = _pattern(PATID_CharacterDefinition_SetAlternatePalette);
	if (pat)
		((void(__fastcall*)(CharacterDefinition*, int))pat)(this, set);
}

void CharacterDefinition::SetLoadout(int64 loadout)
{
	static uintptr_t pat = _pattern(PATID_CharacterDefinition_SetLoadout);
	if (pat)
		((void(__fastcall*)(CharacterDefinition*, int64))pat)(this, loadout);
}
