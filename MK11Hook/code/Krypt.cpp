#include "Krypt.h"
#include "mk10utils.h"

MKObject* Krypt::GetKryptPlayer(int value)
{
	return ((MKObject*(__fastcall*)(Krypt*, int))_addr(0x140985370))(this, value);
}

Krypt* GetKrypt()
{
	return ((Krypt*(__fastcall*)(int))_addr(0x140985210))(1);
}
