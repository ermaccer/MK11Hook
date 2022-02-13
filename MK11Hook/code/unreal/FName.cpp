#include "FName.h"
#include "..\mk11.h"

FName::FName(const char * Name, EFindName FindType, int formal)
{
	((void(__fastcall*)(FName*, const char*, EFindName, int))_addr(0x141A6A2A0))(this, Name, FindType, formal);
}

int64 FName::ToString()
{
	static char idk[566];
	return ((__int64(__fastcall*)(FName*, char*))_addr(0x141AFC4A0))(this, idk);
}
