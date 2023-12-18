#include "Scaleform.h"
#include "..\utils.h"

bool* Scaleform::ms_bActive = nullptr;

void Scaleform::FindData()
{
	static uintptr_t pat = _pattern(PATID_GetScaleform);
	if (pat)
	{
		unsigned int offset = *(unsigned int*)(pat);
		Scaleform::ms_bActive = (bool*)(pat + offset + 5);
	}
}

void Scaleform::SetActive(bool value)
{
	if (ms_bActive)
		*ms_bActive = value;
}
