#pragma once
#include <Windows.h>

// as usual, pluginmh/mugenhook

class eSettingsManager {
public:
	void Init();

	bool bEnableConsoleWindow;
	bool bDisableComboDamageScaling;
	
	bool bUseLegacyCharacterModifier;
	bool bMakeAllAbilities1Slot;

	bool bEnableGamepadSupport;

	// generic
	int iHookMenuOpenKey;
	int iToggleCustomCamKey;
	int iToggleSlowMoKey = VK_F5;
	int iToggleFreezeWorldKey = VK_F2;
	int iResetStageInteractablesKey;
	// free camera keys
	int iFreeCameraKeyXPlus;
	int iFreeCameraKeyXMinus;
	int iFreeCameraKeyYPlus;
	int iFreeCameraKeyYMinus;
	int iFreeCameraKeyZPlus;
	int iFreeCameraKeyZMinus;

	
	int iFreeCameraKeyYawPlus;
	int iFreeCameraKeyYawMinus;

	int iFreeCameraKeyPitchPlus;
	int iFreeCameraKeyPitchMinus;

	int iFreeCameraKeyRollMinus;
	int iFreeCameraKeyRollPlus;



	int iFreeCameraKeyFOVPlus;
	int iFreeCameraKeyFOVMinus;

	float fMenuScale;

	void SaveSettings();
	void ResetKeys();
};

extern eSettingsManager* SettingsMgr;