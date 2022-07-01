#include "FMath.h"
#include <math.h>

FMath GMath;

FMath::FMath()
{
    for (int i = 0; i < 16384; ++i)
    {
        float value = i * 2.0 * 3.141592653589793 / 16384.0;
        this->TrigFLOAT[i] = sinf(value);
    }
}
