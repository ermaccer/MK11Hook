#pragma once
#include "mk11.h"
#include <Windows.h>
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
//	CAMERA_INJUSTICE_2,
	TOTAL_CUSTOM_CAMERAS
};

class MK11Menu {
private:
	bool bIsActive;
	int  iCurrentTab;
public:
	bool	 bSlowMotionEnabled;
	float	 fSlowMotionSpeed;
	// window data

	bool bFocused;

	// characters
	bool bPlayer1ModifierEnabled;
	bool bPlayer2ModifierEnabled;
	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};


	// camera

	bool bCustomCamera;
	bool bCustomFOV;
	bool bCustomCameraRot;
	FVector camPos;
	FRotator camRot;
	float camFov;

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

	float fAdjustCam3;
	float fAdjustCamZ3;
	float fAdjustCamX3;

	// cam mouse
	bool bEnableMouseControl;
	bool bInvertMouseY;
	POINT orgMouse;
	POINT curMouse;
	int     mouseSpeedX;
	int     mouseSpeedY;
	int     mouseScroll;
	int     mouseSens;

	// player
	FVector plrPos;
	FVector plrPos2;

	void Initialize();
	void Draw();
	void Process();
	void UpdateControls();
	void UpdateMouse();
	bool GetActiveState();
};


extern MK11Menu* TheMenu;