#include "CharacterDefinition.h"

//CharacterLoadout* CharacterDefinition::GetLoadout()
//{
	//return (CharacterLoadout*)(this + 96);
//}

void CharacterDefinition::Set(const char* name, int64 loadout, int64 unk)
{
	((void(__fastcall*)(CharacterDefinition*, const char*, int64, int64))_addr(0x140598AB0))(this, name, loadout, unk);
}

void CharacterDefinition::SetLevel(int level)
{
	((void(__fastcall*)(CharacterDefinition*, int))_addr(0x140599F80))(this, level);
}

void CharacterDefinition::SetAlternatePalette(bool set)
{
	((void(__fastcall*)(CharacterDefinition*, int))_addr(0x14059E5E0))(this, set);
}

void CharacterDefinition::SetLoadout(int64 loadout)
{
	((void(__fastcall*)(CharacterDefinition*, int64))_addr(0x14059A0B0))(this, loadout);
}

//void CharacterLoadout::EquipItem(GearItem* item)
//{
//	((void(__fastcall*)(CharacterLoadout*, GearItem*))_addr(0x1406CD1F0))(this, item);
//}
