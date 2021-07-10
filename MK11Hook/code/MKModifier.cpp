#include "MKModifier.h"
#include "mk10utils.h"

TagModifier::TagModifier(const char * character)
{
	((void(__fastcall*)(BaseModifier*,const char*, int))_addr(0x1405457D0))(this, character, 0);
}

void TagModifier::Activate(int64 info)
{
	//140558320
	((void(__fastcall*)(BaseModifier*, int64))_addr(0x140558320))(this, info);
}

void MKModifier::ActivateModifier(BaseModifier * modifier, MKCharacter * obj)
{
	((void(__fastcall*)(MKModifier*, BaseModifier*, MKCharacter*))_addr(0x140B85960))(this, modifier, obj);
}
