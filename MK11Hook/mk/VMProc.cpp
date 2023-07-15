#include "VMProc.h"

unsigned int VMProc::GetCurrentFunction()
{
    return *(unsigned int*)(this + 360);
}
