#pragma once
#include "mk11.h"
#include <Windows.h>
// as usual, based on mh2 debug menu


enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_3RDPERSON2,
	CAMERA_1STPERSON,
	CAMERA_1STPERSON_MID,
	CAMERA_INJUSTICE_2,
	TOTAL_CUSTOM_CAMERAS
};


enum eCHRModifierModes {
	MODIFIER_SCREEN,
	MODIFIER_FIGHT,
	TOTAL_MODES
};


class MK11Menu {
public:
	bool	 m_bIsActive;
	bool	 m_bSlowMotion;
	bool     m_bFreezeWorld;
	bool	 m_bIsFocused;
	bool	 m_bHookDispatch;
	bool	 m_bForceCameraUpdate;
	bool	 m_bCustomCameraPos;
	bool	 m_bCustomCameraRot;
	bool	 m_bCustomCameraFOV;
	bool	 m_bFreeCamMouseControl;
	bool	 m_bFreeCamMouseInvertY;
	bool	 m_bFreeCam;
	bool	 m_bCustomCameras;
	bool	 m_bYObtained;
	bool	 m_bStageModifier;
	bool	 m_bDisableHUD;
	bool	 m_bAutoHideHUD;
	// cheats
	bool	m_bInfiniteHealthP1;
	bool	m_bInfiniteHealthP2;
	bool	m_bNoHealthP1;
	bool	m_bNoHealthP2;
	bool	m_bZeroMeterP1;
	bool	m_bZeroMeterP2;
	bool	m_bInfiniteAttackP1;
	bool	m_bInfiniteAttackP2;
	bool	m_bInfiniteDefendP1;
	bool	m_bInfiniteDefendP2;
	bool	m_bOneHealthP1;
	bool	m_bOneHealthP2;

	bool	m_bChangePlayerSpeed;
	bool	m_bChangePlayerScale;
	bool	m_bPlayer1Modifier;
	bool	m_bPlayer2Modifier;

	bool	m_bKryptModifier;
	bool	m_bTagAssist;
	bool	m_bTagAssistP2;
	bool	m_bDisableGearLoadouts;

	float	 m_fSlowMotionSpeed;
	float	 m_fP1Speed;
	float	 m_fP2Speed;
	float	 m_fAdjustCustomCameraX;
	float	 m_fAdjustCustomCameraY;
	float	 m_fAdjustCustomCameraZ;
	float	 m_fAdjustCustomCameraCrouch;
	float	 m_fAdjustCustomCameraThirdPersonX;
	float	 m_fAdjustCustomCameraThirdPersonY;
	float	 m_fAdjustCustomCameraThirdPersonZ;
	float	 m_fFreeCameraSpeed;

	int  m_nFreeCameraRotationSpeed;
	int  m_nCurrentCustomCamera;
	int  m_nCurrentCharModifier;


	FVector	 m_vP1Scale;
	FVector	 m_vP2Scale;


	char szCurrentModifier[128] = {};
	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szCurrentCameraOption[128];
	char szStageModifierStage[128] = {};
	char szCurrentKryptCharacter[128];
	char szCurrentKryptCharacterClass[128];
	char szPlayer1TagAssistCharacter[128] = {};
	char szPlayer2TagAssistCharacter[128] = {};

	// camera

	FVector  camPos;
	FRotator camRot;
	float	 camFov;

	// player 
	FVector plrPos;
	FVector plrPos2;

	// cam mouse

	POINT	orgMouse;
	POINT	curMouse;
	int     mouseSpeedX;
	int     mouseSpeedY;
	int     mouseSens;

	void Initialize();
	void Draw();
	void Process();
	void UpdateControls();
	void UpdateMouse();
	bool GetActiveState();
};

char* GetMK11HookVersion();
extern MK11Menu* TheMenu;

