#pragma once

// as usual, pluginmh/mugenhook

class eSettingsManager {
public:
	void Init();

	bool bEnableConsoleWindow;
	int iHookMenuOpenKey;
	
	bool bUseLegacyCharacterModifier;
	bool bMakeAllAbilities1Slot;

	bool bEnableGamepadSupport;
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
	int iFreeCameraKeyRollPlus;
	int iFreeCameraKeyRollMinus;

	int iFreeCameraKeyFOVPlus;
	int iFreeCameraKeyFOVMinus;

	float fMenuScale;

	void SaveSettings();
};

extern eSettingsManager* SettingsMgr;