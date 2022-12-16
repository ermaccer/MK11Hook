#include "MKModifier.h"
#include "mk10utils.h"

TagAssistModifier::TagAssistModifier(const char * character)
{
	((void(__fastcall*)(BaseModifier*,const char*, int))_addr(0x140549D20))(this, character, 0);
}

void TagAssistModifier::Activate(PlayerInfo* info)
{
	((void(__fastcall*)(BaseModifier*, PlayerInfo*))_addr(0x14055C8B0))(this, info);
}

TagAssistModifierObject * TagAssistModifier::CreateObject()
{
	return 	((TagAssistModifierObject*(__fastcall*)(BaseModifier*))_addr(0x1405649B0))(this);
}

void MKModifier::ActivateModifier(BaseModifier * modifier, MKCharacter * obj)
{
	((void(__fastcall*)(MKModifier*, BaseModifier*, MKCharacter*))_addr(0x140B9C5B0))(this, modifier, obj);
}

void TagAssistModifierObject::Activate(MKCharacter* obj)
{
	((void(__fastcall*)(TagAssistModifierObject*, MKCharacter*))_addr(0x14055C730))(this, obj);
}