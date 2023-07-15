#include "LadderInfo.h"

LadderInfo* GetLadderInfo()
{
	static uintptr_t pat = _pattern(PATID_GetLadderInfo);
	if (pat)
	{
		uintptr_t offset = *(unsigned int*)(pat);
		return ((LadderInfo * (__fastcall*)())(pat + offset + 5))();
	}

	return nullptr;
}