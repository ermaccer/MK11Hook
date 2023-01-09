#include "FName.h"
#include "..\mk11.h"

FName::FName()
{
	Index = -1;
	Number = 0;
}

FName::FName(const char * Name, EFindName FindType, int formal)
{
	((void(__fastcall*)(FName*, const char*, EFindName, int))_addr(0x141A75200))(this, Name, FindType, formal);
}

TArray<FNameEntry*>* GetNames()
{
	return (TArray< FNameEntry* >*)_addr(0x143643BD8);
}

char* GetName(int index)
{
	if (GetNames()->Data[index])
		return GetNames()->Data[index]->name;
	else
		return "n/a";
}
