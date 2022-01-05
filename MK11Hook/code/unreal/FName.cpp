#include "FName.h"
#include "..\mk11.h"

FName::FName(const char * Name, EFindName FindType, int formal)
{
	((void(__fastcall*)(FName*, const char*, EFindName, int))_addr(0x141A6A2A0))(this, Name, FindType, formal);
}
