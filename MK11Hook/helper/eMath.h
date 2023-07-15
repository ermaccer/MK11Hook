#pragma once
#include "..\unreal\FVector.h"
#include "..\unreal\FQuat.h"

#include <math.h>
#define M_PI           3.14159265358979323846f

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0 / M_PI)

class eMath {
public:
	static FVector quat2vec(FQuat q);
	static bool	   areVecsEqual(FVector v1, FVector v2);
};