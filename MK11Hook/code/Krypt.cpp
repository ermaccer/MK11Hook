#include "Krypt.h"
#include "mk10utils.h"

MKObject* Krypt::GetKryptPlayer(int value)
{
	return ((MKObject*(__fastcall*)(Krypt*, int))_addr(0x140984C20))(this, value);
}

void Krypt::BuildPlayer()
{
	((void(__fastcall*)(Krypt*))_addr(0x140976AA0))(this);
}

Krypt* GetKrypt()
{
	return ((Krypt*(__fastcall*)(int))_addr(0x140984AC0))(1);
}
