#include "MKModifier.h"
#include "mk10utils.h"

TagAssistModifier::TagAssistModifier(const char * character)
{
	((void(__fastcall*)(BaseModifier*,const char*, int))_addr(0x140545800))(this, character, 0);
}

void TagAssistModifier::Activate(int64 info)
{
	//140558320
	((void(__fastcall*)(BaseModifier*, int64))_addr(0x140558350))(this, info);
}

TagAssistModifierObject * TagAssistModifier::CreateObject()
{
	return 	((TagAssistModifierObject*(__fastcall*)(BaseModifier*))_addr(0x140560450))(this);
}

void MKModifier::ActivateModifier(BaseModifier * modifier, MKCharacter * obj)
{
	((void(__fastcall*)(MKModifier*, BaseModifier*, MKCharacter*))_addr(0x140B85BD0))(this, modifier, obj);
}

void TagAssistModifierObject::Activate(MKCharacter* obj)
{
	((void(__fastcall*)(TagAssistModifierObject*, MKCharacter*))_addr(0x1405581D0))(this, obj);
}

void TagAssistModifierObject::AddHUDModifier(int plr, int unk, int unk2)
{
	((void(__fastcall*)(TagAssistModifierObject*,int, int, int))_addr(0x14055A4A0))(this, plr, unk, unk2);
}
