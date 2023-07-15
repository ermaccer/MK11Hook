#pragma once
#include "../utils.h"
#include "../unreal/FMatrix.h"
#include "Engine.h"

class MKCamera {
private:
	char pad[0x6BC];
	FVector  camPos;
	FRotator camRot;
	float	 camFov;
public:
	void SetPosition(FVector* pos);
	void SetRotation(FRotator* rot);
	void SetFOV(float FOV);
	float GetFOV();

	void HookedSetPosition(FVector* pos);
	void HookedSetRotation(FRotator* rot);
	FMatrix GetMatrix();
};

extern MKCamera* TheCamera;