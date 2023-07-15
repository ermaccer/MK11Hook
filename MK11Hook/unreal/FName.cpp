#include "FName.h"

FName::FName()
{
	Index = -1;
	Number = 0;
}

FName::FName(const char * Name, EFindName FindType, int formal)
{
	static uintptr_t pat = _pattern(PATID_FName_FName);
	if (pat)
		((void(__fastcall*)(FName*, const char*, EFindName, int))pat)(this, Name, FindType, formal);
}

TArray<FNameEntry*>* GetNames()
{
	static uintptr_t pat = _pattern(PATID_GetNames);
	static uintptr_t namesPtr = 0;
	if (pat)
	{
		unsigned int offset = *(unsigned int*)(pat);
		namesPtr = pat + offset + 4;
	}
	if (namesPtr)
		return (TArray< FNameEntry* >*)namesPtr;

	return nullptr;
}

char* GetName(int index)
{
	if (GetNames())
	{
		if (GetNames()->Data[index])
			return GetNames()->Data[index]->name;
	}
		return "n/a";
}
