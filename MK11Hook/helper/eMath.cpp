#include "eMath.h"

FVector eMath::quat2vec(FQuat q)
{
	FVector result;

	float ysqr = q.Y * q.Y;

	float t0 = +2.0f * (q.W * q.X + q.Y * q.Z);
	float t1 = +1.0f - 2.0f * (q.X * q.X + ysqr);
	float roll = (float)atan2(t0, t1);

	float t2 = +2.0f * (q.W * q.Y - q.Z * q.X);
	t2 = ((t2 > 1.0f) ? 1.0f : t2);
	t2 = ((t2 < -1.0f) ? -1.0f : t2);

	float pitch = (float)asin(t2);
	float t3 = +2.0f * (q.W * q.Z + q.X * q.Y);
	float t4 = +1.0f - 2.0f * (ysqr + q.Z * q.Z);
	float yaw = (float)atan2(t3, t4);

	result.X = roll / M_PI * 180;
	result.Y = pitch / M_PI * 180;
	result.Z = yaw / M_PI * 180;
	return result;
}

bool eMath::areVecsEqual(FVector v1, FVector v2)
{
	if (fabs(v1.X - v2.X) < 0.1f &&
		(fabs(v1.Y - v2.Y) < 0.1f) &&
		(fabs(v1.Z - v2.Z) < 0.1f))
		return true;
	else
		return false;
}
