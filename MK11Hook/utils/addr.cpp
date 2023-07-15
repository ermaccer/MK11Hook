#include "..\pch.h"
#include "addr.h"

int64 GetEntryPoint()
{
	static int64 addr = reinterpret_cast<int64>(GetModuleHandle(nullptr));
	return addr;
}

int64 _addr(int64 addr)
{
	static int64 ImageBase = 0x140000000;
	return GetEntryPoint() - ImageBase + addr;
}
