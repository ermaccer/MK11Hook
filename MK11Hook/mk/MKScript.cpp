#include "MKScript.h"

MKScript* GetScript(const char* name)
{
	static uintptr_t pat = _pattern(PATID_GetScript0);
	if (pat)
	{
		int64 package = ((int64(__fastcall*)(const char*))pat)("MainlineManaged.SystemPackages.FightingArt");
		if (package)
		{
			static uintptr_t pat1 = _pattern(PATID_GetScript1);
			MKScript* script = ((MKScript * (__fastcall*)(int64, const char*, int, int, int))pat1)(package, name, 1, 1, 0);
			return script;

		}
	}

	return nullptr;
}

int MKScript::GetFunctionID(int hash)
{
	static uintptr_t pat = _pattern(PATID_MKScript_GetFunctionID);
	if (pat)
		return ((int(__thiscall*)(MKScript*, int, int))pat)(this, hash, 0);

	return 0;
}

int64 MKScript::GetVar(const char* name)
{
	static uintptr_t pat = _pattern(PATID_MKScript_GetVar);
	if (pat)
		return ((int64(__fastcall*)(MKScript*, const char*, int))pat)(this, name, 1);

	return 0;
}

