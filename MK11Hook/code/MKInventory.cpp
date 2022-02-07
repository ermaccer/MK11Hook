#include "MKInventory.h"
#include "mk10utils.h"

GearItem::GearItem(unsigned char version, ItemDefinition* item, unsigned short unk, unsigned char unk2, int level, short unk3)
{
	((void(__fastcall*)(GearItem*, unsigned char,ItemDefinition*, unsigned short, unsigned char,int, short))_addr(0x1406A39C0))(this,version,item,unk,unk2,level,unk3);
}


bool GearItem::Valid()
{
	return 	((bool(__fastcall*)(GearItem*))_addr(0x140810FD0))(this);
}

int64 GearItem::GetCharacterKey()
{
	return ((int64(__fastcall*)(GearItem*))_addr(0x1406D5A90))(this);
}

char * GearItem::GetName()
{
	static char buff[256] = { };
	((void(__fastcall*)(GearItem*, char*))_addr(0x14071C650))(this, buff);
	return buff;
}

ItemDefinition GearItem::GetGUID()
{
	return *(ItemDefinition*)(this + 36);
}


void EquipItem(PLAYER_NUM plr, GearItem * item)
{
	int64 ptr = GetInfo(plr);
	int64 chr = (ptr + 216);
	int64 loadout = (chr + 96);
	((void(__fastcall*)(int64, GearItem*))_addr(0x1406CD1F0))(loadout, item);
}

ItemDefinition::ItemDefinition()
{
}

ItemDefinition::ItemDefinition(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
	((void(__fastcall*)(ItemDefinition*, unsigned int, unsigned int, unsigned int, unsigned int))_addr(0x1406A1910))(this, a1,a2,a3,a4);
}
