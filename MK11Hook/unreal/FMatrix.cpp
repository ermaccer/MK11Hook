#include "FMatrix.h"
#include "FMath.h"

FMatrix::FMatrix()
{
}

FMatrix::FMatrix(FRotator* Rot)
{
	float v2;
	float v3;
	float v4;
	float v5;
	float v6;
	float v7;
	float v8;
	float v9;
	float CR;
	float v12;
	float SY;
	float CY;
	float CP;
	float SR;

	SR = GMath.TrigFLOAT[(Rot->Roll >> 2) & 0x3FFF];
	v12 = GMath.TrigFLOAT[(Rot->Pitch >> 2) & 0x3FFF];
	SY = GMath.TrigFLOAT[(Rot->Yaw >> 2) & 0x3FFF];
	CR = GMath.TrigFLOAT[((Rot->Roll + 0x4000) >> 2) & 0x3FFF];
	CP = GMath.TrigFLOAT[((Rot->Pitch + 0x4000) >> 2) & 0x3FFF];
	CY = GMath.TrigFLOAT[((Rot->Yaw + 0x4000) >> 2) & 0x3FFF];
	v2 = CP * CY;
	this->M[0][0] = v2;
	v3 = CP * SY;
	this->M[0][1] = v3;
	this->M[0][2] = v12;
	this->M[0][3] = 0.0f;
	v4 = SR * v12 * CY - CR * SY;
	this->M[1][0] = v4;
	v5 = SR * v12 * SY + CR * CY;
	this->M[1][1] = v5;
	v6 = (-0.0f - SR) * CP;
	this->M[1][2] = v6;
	this->M[1][3] = 0.0f;
	v7 = -0.0f - (CR * v12 * CY + SR * SY);
	this->M[2][0] = v7;
	v8 = CY * SR - CR * v12 * SY;
	this->M[2][1] = v8;
	v9 = CR * CP;
	this->M[2][2] = v9;
	this->M[2][3] = 0.0f;
	this->M[3][0] = 0.0f;
	this->M[3][1] = 0.0f;
	this->M[3][2] = 0.0f;
	this->M[3][3] = 1.0f;
}

FVector FMatrix::GetRight()
{
	return { M[1][0], M[1][1],M[1][2] };
}

FVector FMatrix::GetForward()
{
	return { M[0][0], M[0][1],M[0][2] };
}

FVector FMatrix::GetUp()
{
	return { M[2][0], M[2][1],M[2][2] };
}