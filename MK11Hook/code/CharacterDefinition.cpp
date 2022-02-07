#include "CharacterDefinition.h"

void CharacterDefinition::Set(const char* name, int64 loadout, int64 unk)
{
	((void(__fastcall*)(CharacterDefinition*, const char*, int64, int64))_addr(0x140598320))(this, name, loadout, unk);
}

void CharacterDefinition::SetLevel(int level)
{
	((void(__fastcall*)(CharacterDefinition*, int))_addr(0x1405997F0))(this, level);
}

void CharacterDefinition::SetAlternatePalette(bool set)
{
	((void(__fastcall*)(CharacterDefinition*, int))_addr(0x14059DE50))(this, set);
}

void CharacterDefinition::SetLoadout(int64 loadout)
{
	((void(__fastcall*)(CharacterDefinition*, int64))_addr(0x140599920))(this, loadout);
}
