#include "MKObject.h"
#include "mk10utils.h"
#include "mk11menu.h"
#include <iostream>

void MKObject::SetPos(FVector* pos)
{
	((void(__fastcall*)(MKObject*, FVector*))_addr(0x141178C80))(this, pos);
}

void MKObject::GetPos(FVector* dest)
{
	((void(__fastcall*)(MKObject*, FVector*))_addr(0x141169C10))(this, dest);
}
