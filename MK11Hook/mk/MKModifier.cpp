#include "MKModifier.h"


TagAssistModifier::TagAssistModifier(const char * character)
{
	static uintptr_t pat = _pattern(PATID_TagAssistModifier_TagAssistModifier);
	if (pat)
		((void(__fastcall*)(BaseModifier*,const char*, int))pat)(this, character, 0);
}

void TagAssistModifier::Activate(PlayerInfo* info)
{
	static uintptr_t pat = _pattern(PATID_TagAssistModifier_Activate);
	if (pat)
		((void(__fastcall*)(BaseModifier*, PlayerInfo*))pat)(this, info);
}

TagAssistModifierObject * TagAssistModifier::CreateObject()
{
	static uintptr_t pat = _pattern(PATID_TagAssistModifier_CreateObject);
	if (pat)
		return 	((TagAssistModifierObject*(__fastcall*)(BaseModifier*))pat)(this);
	return nullptr;
}

void MKModifier::ActivateModifier(BaseModifier * modifier, MKCharacter * obj)
{
	static uintptr_t pat = _pattern(PATID_MKModifier_ActivateModifier);
	if (pat)
		((void(__fastcall*)(MKModifier*, BaseModifier*, MKCharacter*))pat)(this, modifier, obj);
}

void TagAssistModifierObject::Activate(MKCharacter* obj)
{
	static uintptr_t pat = _pattern(PATID_TagAssistModifierObject_Activate);
	if (pat)
		((void(__fastcall*)(TagAssistModifierObject*, MKCharacter*))pat)(this, obj);
}

MKModifier* GetModifierManager()
{
	static uintptr_t pat = _pattern(PATID_GetModifierManager);
	int64 info = 0;

	if (pat)
	{
		info = ((int64(__fastcall*)())(pat + *(int*)(pat) + 4))();
	}

	if (info)
		return (MKModifier*)*(int64*)(info + 32);

	return nullptr;
}

void LoadModifierAssets()
{
	static uintptr_t pat = _pattern(PATID_LoadModifierAssets);
	if (pat)
		((void(__fastcall*)(FGGameInfo*, bool))pat)(GetGameInfo(), 1);
}