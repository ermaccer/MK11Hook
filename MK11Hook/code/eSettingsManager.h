#pragma once
#pragma once


// as usual, pluginmh/mugenhook

class eSettingsManager {
public:
	void Init();

	bool bEnableConsoleWindow;


	int iHookMenuOpenKey;
	// free camera keys
	int iFreeCameraKeyXPlus;
	int iFreeCameraKeyXMinus;
	int iFreeCameraKeyYPlus;
	int iFreeCameraKeyYMinus;
	int iFreeCameraKeyYawPlus;
	int iFreeCameraKeyYawMinus;
	int iFreeCameraKeyZPlus;
	int iFreeCameraKeyZMinus;




};

extern eSettingsManager* SettingsMgr;