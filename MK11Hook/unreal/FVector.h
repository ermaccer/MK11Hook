#pragma once
#include <math.h>

class FVector
{
public:
	float X,Y,Z;
	FVector(void) {}
	FVector(float a, float b, float c)
	{
		X = a;
		Y = b;
		Z = c;
	}
	
	const FVector &operator+=(FVector const &right) {
		X += right.X;
		Y += right.Y;
		Z += right.Z;
		return *this;
	}

	const FVector &operator+=(float const &right) {
		X += right;
		Y += right;
		Z += right;
		return *this;
	}

	const FVector &operator-=(FVector const &right) {
		X -= right.X;
		Y -= right.Y;
		Z -= right.Z;
		return *this;
	}

	const FVector &operator*=(float right) {
		X *= right;
		Y *= right;
		Z *= right;
		return *this;
	}

	const FVector &operator/=(float right) {
		X /= right;
		Y /= right;
		Z /= right;
		return *this;
	}

	FVector operator-() const {
		return FVector(-X, -Y, -Z);
	}
};

inline FVector operator+(const FVector &left, const FVector &right)
{
	return FVector(left.X + right.X, left.Y + right.Y, left.Z + right.Z);
}

inline FVector operator-(const FVector &left, const FVector &right)
{
	return FVector(left.X - right.X, left.Y - right.Y, left.Z - right.Z);
}

inline FVector operator*(const FVector &left, float right)
{
	return FVector(left.X * right, left.Y * right, left.Z * right);
}

inline FVector operator*(float left, const FVector &right)
{
	return FVector(left * right.X, left * right.Y, left * right.Z);
}

inline FVector operator/(const FVector &left, float right)
{
	return FVector(left.X / right, left.Y / right, left.Z / right);
}
