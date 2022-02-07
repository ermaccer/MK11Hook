#include "eSettingsManager.h"
#include "..\IniReader.h"
#include <Windows.h>
eSettingsManager* SettingsMgr = new eSettingsManager;

void eSettingsManager::Init()
{
	CIniReader ini("");
	CIniReader user("mk11hook_user.ini");
	

	// user first
	iToggleCustomCamKey = user.ReadInteger("Settings", "iToggleCustomCamKey", 0);
	
	iHookMenuOpenKey = user.ReadInteger("Settings", "iHookMenuOpenKey", 0xFF);

	if (iHookMenuOpenKey == 0xFF)
		iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);


	iToggleFreezeWorldKey = user.ReadInteger("Settings", "iToggleFreezeWorldKey", 0xFF);
	if (iToggleFreezeWorldKey == 0xFF)
		iToggleFreezeWorldKey = VK_F2;

	iToggleSlowMoKey = user.ReadInteger("Settings", "iToggleSlowMoKey", 0xFF);
	if (iToggleSlowMoKey == 0xFF)
		iToggleSlowMoKey = VK_F5;

	iResetStageInteractablesKey = user.ReadInteger("Settings", "iResetStageInteractablesKey", 0xFF);
	if (iResetStageInteractablesKey == 0xFF)
		iResetStageInteractablesKey = 0xFF;

	iFreeCameraKeyFOVPlus = user.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0xFF);
	if (iFreeCameraKeyFOVPlus == 0xFF)
		iFreeCameraKeyFOVPlus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0);

	iFreeCameraKeyFOVMinus = user.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0xFF);
	if (iFreeCameraKeyFOVMinus == 0xFF)
		iFreeCameraKeyFOVMinus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0);

	iFreeCameraKeyXPlus = user.ReadInteger("Settings", "iFreeCameraKeyXPlus", 0xFF);
	if (iFreeCameraKeyXPlus == 0xFF)
		iFreeCameraKeyXPlus = ini.ReadInteger("Settings", "iFreeCameraKeyXPlus", 0);

	iFreeCameraKeyXMinus = user.ReadInteger("Settings", "iFreeCameraKeyXMinus", 0xFF);
	if (iFreeCameraKeyXMinus == 0xFF)
		iFreeCameraKeyXMinus = ini.ReadInteger("Settings", "iFreeCameraKeyXMinus", 0);


	iFreeCameraKeyYPlus = user.ReadInteger("Settings", "iFreeCameraKeyYPlus", 0xFF);
	if (iFreeCameraKeyYPlus == 0xFF)
		iFreeCameraKeyYPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYPlus", 0);

	iFreeCameraKeyYMinus = user.ReadInteger("Settings", "iFreeCameraKeyYMinus", 0xFF);
	if (iFreeCameraKeyYMinus == 0xFF)
		iFreeCameraKeyYMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYMinus", 0);

	iFreeCameraKeyZPlus = user.ReadInteger("Settings", "iFreeCameraKeyZPlus", 0xFF);
	if (iFreeCameraKeyZPlus == 0xFF)
		iFreeCameraKeyZPlus = ini.ReadInteger("Settings", "iFreeCameraKeyZPlus", 0);

	iFreeCameraKeyZMinus = user.ReadInteger("Settings", "iFreeCameraKeyZMinus", 0xFF);
	if (iFreeCameraKeyZMinus == 0xFF)
		iFreeCameraKeyZMinus = ini.ReadInteger("Settings", "iFreeCameraKeyZMinus", 0);

	iFreeCameraKeyYawPlus = user.ReadInteger("Settings", "iFreeCameraKeyYawPlus", 0xFF);
	if (iFreeCameraKeyYawPlus == 0xFF)
		iFreeCameraKeyYawPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYawPlus", 0);

	iFreeCameraKeyYawMinus = user.ReadInteger("Settings", "iFreeCameraKeyYawMinus", 0xFF);
	if (iFreeCameraKeyYawMinus == 0xFF)
		iFreeCameraKeyYawMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYawMinus", 0);

	iFreeCameraKeyRollPlus = user.ReadInteger("Settings", "iFreeCameraKeyRollPlus", 0xFF);
	if (iFreeCameraKeyRollPlus == 0xFF)
		iFreeCameraKeyRollPlus = ini.ReadInteger("Settings", "iFreeCameraKeyRollPlus", 0);

	iFreeCameraKeyRollMinus = user.ReadInteger("Settings", "iFreeCameraKeyRollMinus", 0xFF);
	if (iFreeCameraKeyRollMinus == 0xFF)
		iFreeCameraKeyRollMinus = ini.ReadInteger("Settings", "iFreeCameraKeyRollMinus", 0);


	iFreeCameraKeyPitchPlus = user.ReadInteger("Settings", "iFreeCameraKeyPitchPlus", 0xFF);
	if (iFreeCameraKeyPitchPlus == 0xFF)
		iFreeCameraKeyPitchPlus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchPlus", 0);

	iFreeCameraKeyPitchMinus = user.ReadInteger("Settings", "iFreeCameraKeyPitchMinus", 0xFF);
	if (iFreeCameraKeyPitchMinus == 0xFF)
		iFreeCameraKeyPitchMinus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchMinus", 0);

	fMenuScale = user.ReadFloat("MenuSettings", "fMenuScale", 1.0f);

	if (fMenuScale < 1.0f)
		fMenuScale = 1.0f;

	bEnableConsoleWindow = ini.ReadBoolean("Settings", "bEnableConsoleWindow", true);
	bEnableGamepadSupport = ini.ReadBoolean("Settings", "bEnableGamepadSupport", true);
	bUseLegacyCharacterModifier = ini.ReadBoolean("Settings", "bUseLegacyCharacterModifier", false);
	bMakeAllAbilities1Slot = ini.ReadBoolean("Settings", "bMakeAllAbilities1Slot", false);

}



void eSettingsManager::SaveSettings()
{
	CIniReader user("mk11hook_user.ini");
	user.WriteFloat("MenuSettings", "fMenuScale", fMenuScale);

	user.WriteInteger("Settings", "iHookMenuOpenKey", iHookMenuOpenKey);
	user.WriteInteger("Settings", "iToggleFreezeWorldKey", iToggleFreezeWorldKey);
	user.WriteInteger("Settings", "iToggleCustomCamKey", iToggleCustomCamKey);
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

	CIniReader ini("");
	ini.WriteBoolean("Settings", "bEnableGamepadSupport", bEnableGamepadSupport);
	ini.WriteBoolean("Settings", "bEnableConsoleWindow", bEnableConsoleWindow);
}
