#include "Krypt.h"
Krypt* Krypt::pKrypt = nullptr;
void Krypt::FindKrypt()
{
	static uintptr_t pat = _pattern(PATID_Krypt_FindKrypt);
	if (pat)
	{
		unsigned int offset = *(unsigned int*)(pat);
		Krypt::pKrypt = (Krypt*)(pat + offset + 7);
	}
}

MKObject* Krypt::GetKryptPlayer(int value)
{
	static uintptr_t pat = _pattern(PATID_Krypt_GetKryptPlayer);
	if (pat)
		return ((MKObject * (__fastcall*)(Krypt*, int))pat)(this, value);
	return nullptr;
}

Krypt* GetKrypt()
{
	return Krypt::pKrypt;
}
