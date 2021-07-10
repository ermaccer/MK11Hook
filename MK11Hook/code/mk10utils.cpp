#include "..\pch.h"
#include "mk10utils.h"

int64 GetMKXEntryPoint()
{
	static __int64 addr = reinterpret_cast<__int64>(GetModuleHandle(nullptr));
	return addr;
}

int64 _addr(__int64 addr)
{
	return GetMKXEntryPoint() - 0x140000000 + addr;
}
