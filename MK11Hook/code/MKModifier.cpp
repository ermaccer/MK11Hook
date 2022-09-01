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

Modifier::Modifier(const char* character,int a3, int a4, char* a5)
{
	((void(__fastcall*)(BaseModifier*, const char*, int, int, char*))_addr(0x140542610))(this, character, a3, a4, a5);
}

void Modifier::Activate(MKCharacter* who)
{
	((void(__fastcall*)(BaseModifier*, MKCharacter*))_addr(0x1405586E0))(this, who);
}

ModifierAssist::ModifierAssist(const char* name, int a3, int a4, char* a5)
{
	((void(__fastcall*)(ModifierAssist*, const char*, int, int, char*))_addr(0x140542230))(this, name, a3, a4, a5);
}

ModifierAssistObject* ModifierAssist::CreateObject()
{
	return 	((ModifierAssistObject* (__fastcall*)(BaseModifier*))_addr(0x1405608F0))(this);
}

void ModifierAssistObject::Activate(MKCharacter* obj)
{
	((void(__fastcall*)(ModifierAssistObject*,MKCharacter*))_addr(0x1405581A0))(this, obj);
}
