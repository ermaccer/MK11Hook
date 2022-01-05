#pragma once

struct FVector
{
	float X;
	float Y;
	float Z;
};

struct FRotator 
{
	int Pitch;
	int Yaw;
	int Roll;
};

struct FLinearColor
{
	float R;
	float G;
	float B;
	float A;
};


struct character_info {
	char	name[16];
};
