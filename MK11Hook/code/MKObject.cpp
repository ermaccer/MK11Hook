#include "MKObject.h"
#include "mk10utils.h"
#include "mk11menu.h"
#include <iostream>

void MKObject::SetPos(FVector* pos)
{
	((void(__fastcall*)(MKObject*, FVector*))_addr(0x14115FA50))(this, pos);
}

void MKObject::GetPos(FVector* dest)
{
	((void(__fastcall*)(MKObject*, FVector*))_addr(0x1411509E0))(this, dest);
}

void MKObject::SetPosHooked(FVector* pos)
{
	printf("%x\n", this);
	if (TheMenu->m_bKryptAirbreak)
		SetPos(&TheMenu->kryptPos);
	else
	{
		TheMenu->kryptPos = *pos;
		SetPos(pos);
	}

	
}
