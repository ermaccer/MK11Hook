#pragma once
#include "FRotator.h"
#include "FVector.h"

class FMatrix {
public:
	float M[4][4] = {};

	FMatrix();
	FMatrix(FRotator*);

	FVector GetRight();
	FVector GetForward();
	FVector GetUp();
};