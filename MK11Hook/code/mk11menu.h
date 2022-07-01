#pragma once
#include "mk11.h"
#include <Windows.h>
#include "helper/eKeyboardMan.h"
#include "GameInfo.h"
#include <vector>
// as usual, based on mh2 debug menu


enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_3RDPERSON2,
	CAMERA_1STPERSON,
	CAMERA_1STPERSON_MID,
	CAMERA_INJUSTICE_2,
	CAMERA_HEAD_TRACKING,
	TOTAL_CUSTOM_CAMERAS
};


enum eCHRModifierModes {
	MODIFIER_SCREEN,
	MODIFIER_FIGHT,
	TOTAL_MODES
};

enum eMenuSubMenus {
	SUBMENU_ABILITY_REFERENCE,
	SUBMENU_NPC_MOVELIST,
	SUBMENU_SETTINGS,
	SUBMENU_SCRIPT,
	TOTAL_SUBMENUS
};

enum eScriptExecuteType {
	SCRIPT_P1,
	SCRIPT_P2,
	SCRIPT_GLOBAL
};

struct eScriptKeyBind {
	eScriptExecuteType type;
	eVKKeyCode key;
	char scriptName[128] = {};
	unsigned int functionHash;
};

class MK11Menu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool     m_bPressingKey = false;
	bool	 m_bSlowMotion = false;
	bool     m_bFreezeWorld = false;
	bool	 m_bIsFocused = false;
	bool	 m_bHookDispatch = false;
	bool	 m_bForceCameraUpdate = false;
	bool	 m_bCustomCameraPos = false;
	bool	 m_bCustomCameraRot = false;
	bool	 m_bCustomCameraFOV = false;
	bool	 m_bFreeCam = false;
	bool	 m_bCustomCameras = false;
	bool	 m_bDontFlipCamera = false;
	bool	 m_bDisableHeadTracking = false;
	bool	 m_bUsePlayerTwoAsTracker = false;
	bool	 m_bYObtained = false;
	bool	 m_bStageModifier = false;
	bool	 m_bDisableHUD = false;
	bool	 m_bAutoHideHUD = false;
	bool	 m_bMouseControl = false;

	// cheats
	bool	m_bInfiniteHealthP1 = false;
	bool	m_bInfiniteHealthP2 = false;
	bool	m_bNoHealthP1 = false;
	bool	m_bNoHealthP2 = false;
	bool	m_bZeroMeterP1 = false;
	bool	m_bZeroMeterP2 = false;
	bool	m_bInfiniteAttackP1 = false;
	bool	m_bInfiniteAttackP2 = false;
	bool	m_bInfiniteDefendP1 = false;
	bool	m_bInfiniteDefendP2 = false;
	bool	m_bOneHealthP1 = false;
	bool	m_bOneHealthP2 = false;
	bool    m_bEasyKBsP1 = false;
	bool	m_bEasyKBsP2 = false;
	bool    m_bInfKBsP1 = false;
	bool	m_bInfKBsP2 = false;
	bool    m_bFastUppercutsP1 = false;
	bool    m_bFastUppercutsP2 = false;

	bool	m_bChangePlayerSpeed = false;
	bool	m_bChangePlayerScale = false;
	bool    m_bSmoothScaleChange = false;
	bool	m_bPlayer1Modifier = false;
	bool	m_bPlayer2Modifier = false;

	bool	m_bKryptModifier = false;
	bool	m_bTagAssist = false;
	bool	m_bTagAssistP2 = false;
	bool	m_bDisableGearLoadouts = false;
	bool    m_bDisableComboScaling = false;
	bool	m_bKryptAirbreak = false;
	bool	m_bBrutalityWatcher = false;
	bool	m_bBrutalityDoneP1 = false;
	bool	m_bBrutalityDoneP2 = false;

	float	 m_fSlowMotionSpeed = 0.5f;
	float	 m_fP1Speed = 1.0f;
	float	 m_fP2Speed = 1.0f;
	float	 m_fAdjustCustomCameraX = -10.0f;
	float	 m_fAdjustCustomCameraY = 0.0f;
	float	 m_fAdjustCustomCameraZ = 161.0f;
	float	 m_fAdjustCustomCameraCrouch = 120.0f;
	float	 m_fAdjustCustomCameraThirdPersonX = 0.0f;
	float	 m_fAdjustCustomCameraThirdPersonY = 0.0f;
	float	 m_fAdjustCustomCameraThirdPersonZ = 0.0f;
	float	 m_fAdjustCustomHeadCameraX = 0.0f;
	float	 m_fAdjustCustomHeadCameraY = 1600.0f;
	float	 m_fAdjustCustomHeadCameraZ = 0.0f;
	float	 m_fFreeCameraSpeed = 5.25f;
	float    m_fSmoothScalingUpdate = 0.01f;

	float	 m_fBrutalityWatcherHealth = 0.5f;

	int  m_nFreeCameraRotationSpeed = 120;
	int  m_nCurrentCustomCamera = CAMERA_3RDPERSON;
	int  m_nCurrentCharModifier = MODIFIER_SCREEN;
	int  m_nP1Abilities = 0;
	int  m_nP2Abilities = 0;

	int* m_pCurrentVarToChange = nullptr;

	bool m_bP1CustomAbilities = false;
	bool m_P1Abilities[20] = {};
	bool m_bP2CustomAbilities = false ;
	bool m_P2Abilities[20] = {};

	int  m_nScriptExecuteType = 0;
	unsigned int m_nHash = 0;
	MKScript* m_pScript;

	FVector	 m_vP1Scale = { 1.0f, 1.0f, 1.0f };
	FVector	 m_vP2Scale = { 1.0f, 1.0f, 1.0f };


	char szCurrentModifier[128] = {};
	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szCurrentCameraOption[128];
	char szStageModifierStage[128] = {};
	char szCurrentKryptCharacter[128];
	char szCurrentKryptCharacterClass[128];
	char szPlayer1TagAssistCharacter[128] = {};
	char szPlayer2TagAssistCharacter[128] = {};
	char szAbilityReferenceChararacter[128] = {};

	char szPlayer1BrutalityCharacter[128] = {};
	char szPlayer2BrutalityCharacter[128] = {};

	char szPlayer1BrutalityFunc[128] = {};
	char szPlayer2BrutalityFunc[128] = {};

	char szPlayer1Bone[128] = {};
	char szPlayer2Bone[128] = {};
	// camera

	FVector  camPos = {};
	FRotator camRot = {};
	float	 camFov = 0;

	// player 
	FVector plrPos;
	FVector plrPos2;

	FVector kryptPos;

	std::vector<eScriptKeyBind> m_vKeyBinds;

	void Initialize();
	void Draw();
	void Process();
	void UpdateControls();
	void UpdateFreecam();

	void DrawCharacterTab();
	void DrawStageTab();
	void DrawModifiersTab();
	void DrawPlayerTab();
	void DrawSpeedTab();
	void DrawCameraTab();
	void DrawCheatsTab();
	void DrawKryptTab();
	void DrawMiscTab();
	void DrawScriptTab();

	void DrawSettings();
	void DrawAbilityReference();
	void DrawScriptReference();

	void DrawKeyBind(char* name, int* var);

#ifdef _DEBUG
	static void DrawDebug();
#endif

	void KeyBind(int* var, char* bindName, char* name);
	bool GetActiveState();

	void RunLastScript();

	void RunBrutalityWatcher();

	void ProcessScriptHotkeys();
};

char* GetMK11HookVersion();
extern MK11Menu* TheMenu;


bool IsWindowFocused();

