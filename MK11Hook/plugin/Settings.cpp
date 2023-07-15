#include "Settings.h"
#include "../utils/IniReader.h"
#include <Windows.h>
eSettingsManager* SettingsMgr = new eSettingsManager;

eSettingsManager::eSettingsManager()
{
	CIniReader ini("");
	CIniReader user("mk11hook_user.ini");


	// user first
	iToggleCustomCamKey = user.ReadInteger("Settings", "iToggleCustomCamKey", 0);

	bEnableConsoleWindow = ini.ReadBoolean("Settings", "bEnableConsoleWindow", true);
	bEnableGamepadSupport = ini.ReadBoolean("Settings", "bEnableGamepadSupport", true);
	bDisableAnimationTool = ini.ReadBoolean("Settings", "bDisableAnimationTool", false);
	bUseLegacyCharacterModifier = ini.ReadBoolean("Settings", "bUseLegacyCharacterModifier", false);
	bMakeAllAbilities1Slot = ini.ReadBoolean("Settings", "bMakeAllAbilities1Slot", false);

	iHookMenuOpenKey = user.ReadInteger("Settings", "iHookMenuOpenKey", -1);
	if (iHookMenuOpenKey == -1) iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);

	iToggleFreezeWorldKey = user.ReadInteger("Settings", "iToggleFreezeWorldKey", -1);
	if (iToggleFreezeWorldKey == -1) iToggleFreezeWorldKey = VK_F2;

	iToggleSlowMoKey = user.ReadInteger("Settings", "iToggleSlowMoKey", -1);
	if (iToggleSlowMoKey == -1) iToggleSlowMoKey = VK_F5;

	iResetStageInteractablesKey = user.ReadInteger("Settings", "iResetStageInteractablesKey", -1);
	if (iResetStageInteractablesKey == -1) iResetStageInteractablesKey = -1;

	iToggleFreeCameraKey = user.ReadInteger("Settings", "iToggleFreeCameraKey", -1);
	if (iToggleFreeCameraKey == -1) iToggleFreeCameraKey = -1;

	iFreeCameraKeyFOVPlus = user.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", -1);
	if (iFreeCameraKeyFOVPlus == -1) iFreeCameraKeyFOVPlus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0);

	iFreeCameraKeyFOVMinus = user.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", -1);
	if (iFreeCameraKeyFOVMinus == -1) iFreeCameraKeyFOVMinus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0);

	iFreeCameraKeyXPlus = user.ReadInteger("Settings", "iFreeCameraKeyXPlus", -1);
	if (iFreeCameraKeyXPlus == -1) iFreeCameraKeyXPlus = ini.ReadInteger("Settings", "iFreeCameraKeyXPlus", 0);

	iFreeCameraKeyXMinus = user.ReadInteger("Settings", "iFreeCameraKeyXMinus", -1);
	if (iFreeCameraKeyXMinus == -1) iFreeCameraKeyXMinus = ini.ReadInteger("Settings", "iFreeCameraKeyXMinus", 0);

	iFreeCameraKeyYPlus = user.ReadInteger("Settings", "iFreeCameraKeyYPlus", -1);
	if (iFreeCameraKeyYPlus == -1) iFreeCameraKeyYPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYPlus", 0);

	iFreeCameraKeyYMinus = user.ReadInteger("Settings", "iFreeCameraKeyYMinus", -1);
	if (iFreeCameraKeyYMinus == -1) iFreeCameraKeyYMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYMinus", 0);

	iFreeCameraKeyZPlus = user.ReadInteger("Settings", "iFreeCameraKeyZPlus", -1);
	if (iFreeCameraKeyZPlus == -1) iFreeCameraKeyZPlus = ini.ReadInteger("Settings", "iFreeCameraKeyZPlus", 0);

	iFreeCameraKeyZMinus = user.ReadInteger("Settings", "iFreeCameraKeyZMinus", -1);
	if (iFreeCameraKeyZMinus == -1) iFreeCameraKeyZMinus = ini.ReadInteger("Settings", "iFreeCameraKeyZMinus", 0);

	iFreeCameraKeyYawPlus = user.ReadInteger("Settings", "iFreeCameraKeyYawPlus", -1);
	if (iFreeCameraKeyYawPlus == -1) iFreeCameraKeyYawPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYawPlus", 0);

	iFreeCameraKeyYawMinus = user.ReadInteger("Settings", "iFreeCameraKeyYawMinus", -1);
	if (iFreeCameraKeyYawMinus == -1) iFreeCameraKeyYawMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYawMinus", 0);

	iFreeCameraKeyRollPlus = user.ReadInteger("Settings", "iFreeCameraKeyRollPlus", -1);
	if (iFreeCameraKeyRollPlus == -1) iFreeCameraKeyRollPlus = ini.ReadInteger("Settings", "iFreeCameraKeyRollPlus", 0);

	iFreeCameraKeyRollMinus = user.ReadInteger("Settings", "iFreeCameraKeyRollMinus", -1);
	if (iFreeCameraKeyRollMinus == -1) iFreeCameraKeyRollMinus = ini.ReadInteger("Settings", "iFreeCameraKeyRollMinus", 0);


	iFreeCameraKeyPitchPlus = user.ReadInteger("Settings", "iFreeCameraKeyPitchPlus", -1);
	if (iFreeCameraKeyPitchPlus == -1) iFreeCameraKeyPitchPlus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchPlus", 0);

	iFreeCameraKeyPitchMinus = user.ReadInteger("Settings", "iFreeCameraKeyPitchMinus", -1);
	if (iFreeCameraKeyPitchMinus == -1) iFreeCameraKeyPitchMinus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchMinus", 0);

	fMenuScale = user.ReadFloat("MenuSettings", "fMenuScale", 1.0f);

	if (fMenuScale < 1.0f)
		fMenuScale = 1.0f;

	mouse.sens = user.ReadInteger("Mouse", "Sensitivity", 10);
	mouse.invert_y = user.ReadBoolean("Mouse", "InvertY", false);
	mouse.invert_x = user.ReadBoolean("Mouse", "InvertX", false);

}

void eSettingsManager::SaveSettings()
{
	CIniReader user("mk11hook_user.ini");
	user.WriteFloat("MenuSettings", "fMenuScale", fMenuScale);

	user.WriteInteger("Settings", "iHookMenuOpenKey", iHookMenuOpenKey);
	user.WriteInteger("Settings", "iToggleFreezeWorldKey", iToggleFreezeWorldKey);
	user.WriteInteger("Settings", "iToggleCustomCamKey", iToggleCustomCamKey);
	user.WriteInteger("Settings", "iToggleSlowMoKey", iToggleSlowMoKey);
	user.WriteInteger("Settings", "iFreeCameraKeyXPlus", iFreeCameraKeyXPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyXMinus", iFreeCameraKeyXMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyYPlus", iFreeCameraKeyYPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyYMinus", iFreeCameraKeyYMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyZPlus", iFreeCameraKeyZPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyZMinus", iFreeCameraKeyZMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyYawPlus", iFreeCameraKeyYawPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyYawMinus", iFreeCameraKeyYawMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyRollPlus", iFreeCameraKeyRollPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyRollMinus", iFreeCameraKeyRollMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyPitchPlus", iFreeCameraKeyPitchPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyPitchMinus", iFreeCameraKeyPitchMinus);
	user.WriteInteger("Settings", "iFreeCameraKeyFOVPlus", iFreeCameraKeyFOVPlus);
	user.WriteInteger("Settings", "iFreeCameraKeyFOVMinus", iFreeCameraKeyFOVMinus);
	user.WriteInteger("Settings", "iResetStageInteractablesKey", iResetStageInteractablesKey);
	user.WriteInteger("Settings", "iToggleFreeCameraKey", iToggleFreeCameraKey);
	user.WriteInteger("Mouse", "Sensitivity", mouse.sens);
	user.WriteBoolean("Mouse", "InvertY", mouse.invert_y);
	user.WriteBoolean("Mouse", "InvertX", mouse.invert_x);

	CIniReader ini("");
	ini.WriteBoolean("Settings", "bEnableGamepadSupport", bEnableGamepadSupport);
	ini.WriteBoolean("Settings", "bEnableConsoleWindow", bEnableConsoleWindow);
}

void eSettingsManager::ResetKeys()
{
	iHookMenuOpenKey = VK_F1;
	iToggleCustomCamKey = 0;
	iToggleSlowMoKey = VK_F5;
	iToggleFreezeWorldKey = VK_F2;
	iResetStageInteractablesKey = 0;
	iToggleFreeCameraKey = 0;
	iFreeCameraKeyXPlus = 104;
	iFreeCameraKeyXMinus = 98;
	iFreeCameraKeyYPlus = 102;
	iFreeCameraKeyYMinus = 100;
	iFreeCameraKeyZPlus = 103;
	iFreeCameraKeyZMinus = 97;
	iFreeCameraKeyYawPlus = 39;
	iFreeCameraKeyYawMinus = 37;
	iFreeCameraKeyPitchPlus = 38;
	iFreeCameraKeyPitchMinus = 40;
	iFreeCameraKeyRollMinus = 99;
	iFreeCameraKeyRollPlus = 105;
	iFreeCameraKeyFOVPlus = 107;
	iFreeCameraKeyFOVMinus = 109;
}
