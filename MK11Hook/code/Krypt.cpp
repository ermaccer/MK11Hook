#include "Krypt.h"
#include "mk10utils.h"

MKObject* Krypt::GetKryptPlayer(int value)
{
	return ((MKObject*(__fastcall*)(Krypt*, int))_addr(0x14098DA20))(this, value);
}

Krypt* GetKrypt()
{
	return ((Krypt*(__fastcall*)(int))_addr(0x14098D8C0))(1);
}
