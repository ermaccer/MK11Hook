#include "MKModifier.h"
#include "Engine.h"


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

Modifier* MKModifier::CreateModifier(const char* name)
{
	return new Modifier(name);
}

void MKModifier::ActivateModifier(Modifier* mod, int playerFlags)
{
	ModifierObject obj(mod, playerFlags);

	MKCharacter* p1 = GetObj(PLAYER1);

	if (!p1)
		return;

	MKCharacter* p2 = GetObj(PLAYER2);

	if (!p2)
		return;

	obj.Activate(p1, p2);
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

Modifier::Modifier(const char* name)
{
	static uintptr_t pat = _pattern(PATID_MKModifier_Constructor);
	if (pat)
		((void(__fastcall*)(BaseModifier*, const char*, int, int64, int64))pat)(this, name, 1, 0, 0);
}

void Modifier::GetAssetPath(TArray<char>& path)
{
	static uintptr_t pat = _pattern(PATID_MKModifier_GetAssetPath);
	if (pat)
		((void(__fastcall*)(Modifier*, TArray<char>&))pat)(this, path);
}

ModifierObject::ModifierObject(Modifier* modifier, int flags)
{
	static uintptr_t pat = _pattern(PATID_MKModifierObject_Constructor);
	if (pat)
		((void(__fastcall*)(ModifierObject*, BaseModifier*, int))pat)(this, modifier, flags);
}

void ModifierObject::Activate(MKCharacter* p1, MKCharacter* p2)
{
	static uintptr_t pat = _pattern(PATID_MKModifierObject_Activate);
	if (pat)
		((void(__fastcall*)(ModifierObject*, MKCharacter*, MKCharacter*))pat)(this, p1, p2);
}
