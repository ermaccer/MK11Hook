#pragma once
#include "mk11.h"
// as usual, based on mh2 debug menu

enum eTabs {
	TAB_CHARACTER_MODIFIER,
	TAB_SPEED,
	TAB_CAMERA,
	TAB_PLAYER_CONTROL,
};

enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_3RDPERSON2,
	CAMERA_1STPERSON,
	CAMERA_1STPERSON_MID,
	TOTAL_CUSTOM_CAMERAS
};

class MK11Menu {
private:
	bool bIsActive;
	int  iCurrentTab;
public:
	bool	 bSlowMotionEnabled;
	float	 fSlowMotionSpeed;

	// characters
	bool bPlayer1ModifierEnabled;
	bool bPlayer2ModifierEnabled;
	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};


	// camera
	bool bCustomCamera;
	bool bCustomCameraRot;
	FVector camPos;
	FRotator camRot;
	bool bFreeCameraMovement;
	float fFreeCameraSpeed;
	int  iFreeCameraRotSpeed;
	bool bEnableCustomCameras;
	int  iCurrentCustomCamera;
	char szCurrentCameraOption[128];
	bool bYObtained;

	float fAdjustCam;
	float fAdjustCamZ;
	float fAdjustCamX;
	// player
	FVector plrPos;
	FVector plrPos2;

	void Initialize();
	void Draw();
	void Process();
	void UpdateControls();
	bool GetActiveState();
};


extern MK11Menu* TheMenu;