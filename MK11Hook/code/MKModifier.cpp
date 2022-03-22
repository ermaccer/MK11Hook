#include "MKModifier.h"
#include "mk10utils.h"

TagAssistModifier::TagAssistModifier(const char * character)
{
	((void(__fastcall*)(BaseModifier*,const char*, int))_addr(0x140545F90))(this, character, 0);
}

void TagAssistModifier::Activate(PlayerInfo* info)
{
	//140558320
	((void(__fastcall*)(BaseModifier*, PlayerInfo*))_addr(0x140558AE0))(this, info);
}

TagAssistModifierObject * TagAssistModifier::CreateObject()
{
	return 	((TagAssistModifierObject*(__fastcall*)(BaseModifier*))_addr(0x140560BE0))(this);
}

void MKModifier::ActivateModifier(BaseModifier * modifier, MKCharacter * obj)
{
	((void(__fastcall*)(MKModifier*, BaseModifier*, MKCharacter*))_addr(0x140B85ED0))(this, modifier, obj);
}

void TagAssistModifierObject::Activate(MKCharacter* obj)
{
	((void(__fastcall*)(TagAssistModifierObject*, MKCharacter*))_addr(0x140558960))(this, obj);
}
