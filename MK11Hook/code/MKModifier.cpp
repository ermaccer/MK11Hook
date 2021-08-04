#include "MKModifier.h"
#include "mk10utils.h"

TagAssistModifier::TagAssistModifier(const char * character)
{
	((void(__fastcall*)(BaseModifier*,const char*, int))_addr(0x1405457D0))(this, character, 0);
}

void TagAssistModifier::Activate(int64 info)
{
	//140558320
	((void(__fastcall*)(BaseModifier*, int64))_addr(0x140558320))(this, info);
}

TagAssistModifierObject * TagAssistModifier::CreateObject()
{
	return 	((TagAssistModifierObject*(__fastcall*)(BaseModifier*))_addr(0x140560420))(this);
}

void MKModifier::ActivateModifier(BaseModifier * modifier, MKCharacter * obj)
{
	((void(__fastcall*)(MKModifier*, BaseModifier*, MKCharacter*))_addr(0x140B85960))(this, modifier, obj);
}

void TagAssistModifierObject::Activate(MKCharacter* obj)
{
	((void(__fastcall*)(TagAssistModifierObject*, MKCharacter*))_addr(0x1405581A0))(this, obj);
}
