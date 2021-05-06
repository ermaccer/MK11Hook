#include "eSettingsManager.h"
#include "..\IniReader.h"
#include <Windows.h>
eSettingsManager* SettingsMgr = new eSettingsManager;

void eSettingsManager::Init()
{
	CIniReader ini("");
	bEnableConsoleWindow = ini.ReadBoolean("Settings", "bEnableConsoleWindow", true);
	bGlobalCameraHook = ini.ReadBoolean("Settings", "bGlobalCameraHook", true);

	iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);

	bUseLegacyCharacterModifier = ini.ReadBoolean("Settings", "bUseLegacyCharacterModifier", false);

	iFreeCameraKeyXPlus = ini.ReadInteger("Settings", "iFreeCameraKeyXPlus", 0);
	iFreeCameraKeyXMinus = ini.ReadInteger("Settings", "iFreeCameraKeyXMinus", 0);


	iFreeCameraKeyYPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYPlus", 0);
	iFreeCameraKeyYMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYMinus", 0);

	iFreeCameraKeyZPlus = ini.ReadInteger("Settings", "iFreeCameraKeyZPlus", 0);
	iFreeCameraKeyZMinus = ini.ReadInteger("Settings", "iFreeCameraKeyZMinus", 0);


	iFreeCameraKeyYawPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYawPlus", 0);
	iFreeCameraKeyYawMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYawMinus", 0);

	iFreeCameraKeyRollPlus = ini.ReadInteger("Settings", "iFreeCameraKeyRollPlus", 0);
	iFreeCameraKeyRollMinus = ini.ReadInteger("Settings", "iFreeCameraKeyRollMinus", 0);

	iFreeCameraKeyPitchPlus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchPlus", 0);
	iFreeCameraKeyPitchMinus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchMinus", 0);

	iFreeCameraKeyFOVPlus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0);
	iFreeCameraKeyFOVMinus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0);
}
