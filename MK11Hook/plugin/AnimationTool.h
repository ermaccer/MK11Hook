#pragma once
#include <vector>
#include <math.h>

#include "../utils.h"
#include "../unreal/SkeletalMesh.h"
#include "../unreal/FVector.h"
#include "../mk/MKCharacter.h"
#include "Menu.h"

#define M_PI           3.14159265358979323846f

#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0f)
#define radToDeg(angleInRadians) ((angleInRadians) * 180.0f / M_PI)

struct PoseEntry {
	FBoneAtom atom;
	char boneName[256];
};

struct AnimFrame {
	std::vector<PoseEntry> frame;
};


struct EPoseHeader {
	int hdr;
	int numBones;
	char charName[32] = {};
	int reserved;
	int game;
};


struct EPoseEntry {
	char boneName[64] = {};
	FBoneAtom atom;
};


class AnimationTool {
public:
	static bool ms_bActive;
	static bool ms_bSkipFaceBones;
	static bool ms_bDrawEditBox;
	static bool ms_bDrawFileBox;
	static bool ms_bSave;
	static bool ms_bLoad;
	static bool ms_bTargetP2;
	static bool ms_bEditP2;

	static std::vector<PoseEntry> plr2_pose;
	static std::vector<PoseEntry> plr1_pose;

	static void Draw();
	static void StorePose();
	static void StoreP2Pose();
	static void UseP2Pose();
	static void ClearPose();


	static void ProcessPosing();

	static void DrawEditBox();
	static void DrawFileBox();

	static int GetBoneID(char* name);
	static int GetBoneIDP2(char* name);
	static bool IsFaceBone(char* name);

	static void SavePose(char* path);
	static void LoadPose(char* path);
};


FQuat		vec2quat(FVector v);
FVector		quat2vec(FQuat q);