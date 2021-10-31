#include "mk11menu.h"
#include <Windows.h>
#include "mk10utils.h"
#include "mk11.h"
#include <iostream>
#include "..\imgui\imgui.h"
#include "eSettingsManager.h"
#include "..\utils\MemoryMgr.h"
#include "eNotifManager.h"
#include "MKCamera.h"
#include <math.h>


static int64 timer = GetTickCount64();
static int64 func_timer = GetTickCount64();
char textBuffer[260] = {};
const char* szCharacters[] = {
	// place npcs first for easy access
	"CHAR_Cyrax",
	"CHAR_Sektor",
	"CHAR_FireGod",
	"CHAR_Kronika",

	// rest of the cast
	"CHAR_Baraka",
	"CHAR_Cage",
	"CHAR_Cassie",
	"CHAR_Cetrion",
	"CHAR_DVorah",
	"CHAR_ErronBlack",
	"CHAR_Jacqui",
	"CHAR_Jade",
	"CHAR_Jax",
	"CHAR_Kabal",
	"CHAR_Kano",
	"CHAR_Kitana",
	"CHAR_Kollector",
	"CHAR_Kotal",
	"CHAR_KungLao",
	"CHAR_LiuKang",
	"CHAR_Noob",
	"CHAR_Raiden",
	"CHAR_Scorpion",
	"CHAR_Skarlet",
	"CHAR_Sonya",
	"CHAR_SubZero",
	"CHAR_Terminas",
	// story (512 in total) fun ones in front
	"SEK_Story_Upgraded",
	"KRO_Story_Crown",
	"FRO_Story_Robe",
	"BARpr_Story",
	"BAR_A",
	"BAR_B",
	"BAR_C",
	"BAR_D",
	"BAR_E",
	"BAR_F",
	"BAR_F1",
	"BAR_G",
	"BAR_H",
	"CAS_A",
	"CAS_A1",
	"CAS_B",
	"CAS_C",
	"CAS_D",
	"CAS_E",
	"CAS_F",
	"CAS_G",
	"CAS_H",
	"CAS_H1",
	"CAS_I",
	"CAS_NoGlasses",
	"CAS_Story",
	"CAS_Story_SF",
	"CAS_Story_SF_NoHelmet",
	"CET_A",
	"CET_B",
	"CET_C",
	"CET_D",
	"CET_E",
	"CET_F",
	"CET_G",
	"CET_Story",
	"CET_Story_Dark",
	"FRO_A",
	"FRO_A1",
	"FRO_B",
	"FRO_C",
	"FRO_D",
	"FRO_E",
	"FRO_F",
	"FRO_G",
	"FRO_NoMask",
	"FRO_Story",
	"DVO_A",
	"DVO_A1_KL",
	"DVO_B",
	"DVO_B1",
	"DVO_C",
	"DVO_D",
	"DVO_E",
	"DVO_F",
	"DVO_G",
	"DVO_Story",
	"ERRpa_Story",
	"ERRpa_Story_Fight",
	"ERRpr_Story",
	"ERRpr_Story_Fight",
	"ERRpr_Story_Mask",
	"ERRpr_Story_Mask_Fight",
	"ERR_A",
	"ERR_B",
	"ERR_C",
	"ERR_C1",
	"ERR_D",
	"ERR_E",
	"ERR_F",
	"ERR_G",
	"ERR_H",
	"JAC_A",
	"JAC_A1",
	"JAC_B",
	"JAC_C",
	"JAC_D",
	"JAC_E",
	"JAC_F",
	"JAC_G",
	"JAC_H",
	"JAC_Story",
	"JAC_Story_Crown",
	"JAC_Story_SF",
	"JAC_Story_SF_NoMic",
	"JADpa_Story",
	"JADpa_Story_NoHood",
	"JADpa_Story_NoStaff",
	"JADrv_Story",
	"JADrv_Story_KronikaUpgraded",
	"JADrv_Story_KronikaUpgraded_NoMask",
	"JADrv_Story_NoMask",
	"JADrv_Story_NoStaff",
	"JAD_A",
	"JAD_B",
	"JAD_B1",
	"JAD_C",
	"JAD_D",
	"JAD_DefaultPreset_02",
	"JAD_DefaultPreset_03",
	"JAD_E",
	"JAD_E1",
	"JAD_F",
	"JAD_G",
	"JAD_H",
	"JAD_I",
	"JAD_WitchNoMask",
	"JAXpa_Story",
	"JAXpa_Story_Crown",
	"JAXpr_KronikaUpgraded",
	"JAXpr_Story",
	"JAX_A",
	"JAX_B",
	"JAX_C",
	"JAX_D",
	"JAX_E",
	"JAX_F",
	"JOHpa_Story",
	"JOHpa_Story_Collar",
	"JOHpa_Story_Fight",
	"JOHpa_Story_NoGlasses",
	"JOHpa_Story_NoJacket",
	"JOHpa_Story_Scar",
	"JOHpr_Story",
	"JOHpr_Story_Glasses",
	"JOHpr_Story_Scar",
	"JOH_A",
	"JOH_B",
	"JOH_B1",
	"JOH_C",
	"JOH_D",
	"JOH_DefaultPreset_02",
	"JOH_DefaultPreset_03",
	"JOH_E",
	"JOH_F",
	"JOH_H",
	"JOH_I",
	"JOH_J1",
	"JOH_J2",
	"JOH_Mime",
	"JOH_Movie",
	"JOH_NoGlasses",
	"KABpa_Story",
	"KABrv_Story",
	"KAB_A",
	"KAB_B",
	"KAB_C",
	"KAB_D",
	"KAB_DefaultPreset_02",
	"KAB_DefaultPreset_03",
	"KAB_D_Test",
	"KAB_E",
	"KAB_F",
	"KAB_G",
	"KAB_G1",
	"KANpa_Story",
	"KANpa_Story_Fight",
	"KANpr_Story",
	"KANpr_Story_Fight",
	"KAN_A",
	"KAN_A1",
	"KAN_B",
	"KAN_C",
	"KAN_D",
	"KAN_E",
	"KAN_F",
	"KAN_G",
	"KAN_H",
	"KAN_I",
	"KITpa_Story",
	"KITpa_Story_Goddess",
	"KITpa_Story_NoMask",
	"KITrv_Story",
	"KITrv_Story_KronikaUpgraded",
	"KITrv_Story_KronikaUpgraded_NoMask",
	"KITrv_Story_Mask",
	"KITrv_Story_NoEyeMask",
	"KIT_A",
	"KIT_B",
	"KIT_B1",
	"KIT_C",
	"KIT_D",
	"KIT_E",
	"KIT_F",
	"KIT_H",
	"KIT_I",
	"KIT_J",
	"KIT_K",
	"KOT_A",
	"KOT_A1",
	"KOT_B",
	"KOT_C",
	"KOT_E",
	"KOT_F",
	"KOT_G",
	"KOT_GearTest",
	"KOT_SKIN_D",
	"KOT_Story",
	"KOT_Story_NoHelmet",
	"KOL_A",
	"KOL_B",
	"KOL_C",
	"KOL_D",
	"KOL_D1",
	"KOL_E",
	"KOL_F",
	"KOL_Story",
	"KOL_Story_Fight",
	"KOL_Story_noBackpack",
	"KUNpa_Story",
	"KUNpa_Story_Disguise",
	"KUNpa_Story_NoHat",
	"KUNrv_Story",
	"KUNrv_Story_KronikaUpgraded",
	"KUNrv_Story_NoHat",
	"KUN_C1",
	"KUN_A",
	"KUN_A_SetB",
	"KUN_B",
	"KUN_C",
	"KUN_D",
	"KUN_E",
	"KUN_F",
	"KUN_G",
	"KUN_H",
	"KUN_I",
	"LIUpa_Story",
	"LIUpa_Story_Disguise",
	"LIUpa_Story_Shirtless",
	"LIUrv_Story",
	"LIU_A",
	"LIU_B",
	"LIU_C",
	"LIU_D",
	"LIU_D2",
	"LIU_E",
	"LIU_F",
	"LIU_G",
	"LIU_H",
	"LIU_I",
	"LIU_J",
	"LIU_Story_SoulDrain",
	"LIU_Story_Montage_A",
	"LIU_Story_Montage_B",
	"LIU_Story_Montage_C",
	"LIU_Story_Montage_D",
	"LIU_Story_Montage_E",
	"LIU_Story_Montage_F",
	"LIU_Story_Montage_G",
	"LIU_Story_Montage_H",
	"LIU_Story_Montage_I",
	"LIU_Story_Montage_J",
	"LIU_Story_Montage_K",
	"LIU_Story_Montage_L",
	"LIU_Story_Montage_M",
	"LIU_Story_Montage_N",
	"LIU_Story_Montage_O",
	"LIU_Story_Montage_P",
	"LIU_Story_Montage_Q",
	"LIU_Story_Montage_R",
	"NOO_NoMask",
	"NOO_SKIN_A",
	"NOO_SKIN_A1",
	"NOO_SKIN_A2",
	"NOO_SKIN_B",
	"NOO_SKIN_B1",
	"NOO_SKIN_C",
	"NOO_SKIN_D",
	"NOO_SKIN_E",
	"NOO_SKIN_F",
	"NOO_SKIN_G",
	"NOO_SKIN_H",
	"NOO_SKIN_I",
	"NOO_Story",
	"NOO_Story_NoSickle",
	"RAIpa_Story",
	"RAIpa_Story_Fight",
	"RAIpa_Story_Mortal",
	"RAIpa_Story_Mortal_WithHat",
	"RAIpa_Story_Red_Fight",
	"RAIpr_Story",
	"RAIpr_Story_Fight",
	"RAIpr_Story_NoAmulet",
	"RAI_A",
	"RAI_A1",
	"RAI_B",
	"RAI_C",
	"RAI_D",
	"RAI_DefaultPreset_02",
	"RAI_DefaultPreset_03",
	"RAI_E",
	"RAI_F",
	"RAI_G",
	"RAI_H1",
	"RAI_Movie",
	"RAIpa_Story_Montage_A",
	"RAIpa_Story_Montage_B",
	"RAIpa_Story_Montage_C",
	"RAIpa_Story_Montage_D",
	"RAIpa_Story_Montage_E",
	"RAIpa_Story_Montage_F",
	"RAIpa_Story_Montage_G",
	"RAIpa_Story_Montage_H",
	"RAIpa_Story_Montage_I",
	"RAIpa_Story_Montage_J",
	"RAIpa_Story_Montage_K",
	"RAIpa_Story_Montage_L",
	"RAIpa_Story_Montage_M",
	"RAIpa_Story_Montage_N",
	"RAIpa_Story_Montage_O",
	"RAIpa_Story_Montage_P",
	"RAIpa_Story_Montage_Q",
	"RAIpa_Story_Montage_R",
	"RAIpa_Story_SoulDrain",
	"RAIpa_Story_SoulDrain_NoHat",
	"SCOpa_Story",
	"SCOpa_Story_NoSwords",
	"SCOpr_Story",
	"SCOpr_Story_NoSwords",
	"SCO_A",
	"SCO_A1",
	"SCO_A_NoMask",
	"SCO_B",
	"SCO_C",
	"SCO_D",
	"SCO_E",
	"SCO_F",
	"SCO_H",
	"SCO_H1",
	"SCO_I",
	"SHA_A",
	"SHA_B",
	"SHA_C",
	"SHA_D",
	"SHA_E",
	"SHA_F",
	"SHA_GearTest",
	"SHA_Story",
	"SHA_Story_EyeCut",
	"SHA_Story_NoHelmet",
	"SHA_Story_SoulDrain",
	"SHA_test",
	"SKApa_Story",
	"SKA_A",
	"SKA_B",
	"SKA_B_NoMask",
	"SKA_C",
	"SKA_D",
	"SKA_D2",
	"SKA_E",
	"SKA_F",
	"SKA_G",
	"SKA_H",
	"SKA_I",
	"SKA_J",
	"SKA_No_Mask",
	"SKA_SKIN_B_Blue",
	"SONpa_Story",
	"SONpa_Story_NoGloves",
	"SONpr_Story",
	"SONpr_Story_Fight",
	"SONpr_Story_SF",
	"SONpr_Story_SF_NoHat",
	"SON_A",
	"SON_B",
	"SON_C",
	"SON_D",
	"SON_E",
	"SON_F",
	"SON_FACE_C_TEST",
	"SON_H",
	"SON_I",
	"SON_I1",
	"SON_I2",
	"SON_J",
	"SON_Movie",
	"SUB_A",
	"SUB_A1",
	"SUB_A2",
	"SUB_A_60Hz",
	"SUB_B",
	"SUB_B1",
	"SUB_C",
	"SUB_D",
	"SUB_E",
	"SUB_EU",
	"SUB_F",
	"SUB_F1",
	"SUB_G",
	"SUB_H",
	"SUB_I",
	"SUB_Masked_DefaultPreset",
	"SUB_Story",
	"TER_A",
	"TER_B",
	"TER_C",
	"TER_C1",
	"TER_D",
	"TER_E",
	"TER_F",
	"TER_G",
	"TER_H",
	"TER_Story",
	"TER_Story_Axe",
	"TER_Story_Fight",
	"TER_Story_Hammer",
	"TER_Story_Upgraded",
	"TER_Story_Upgraded_Fight",
	"TER_Story_Upgraded_NoHelmet",
	"CYR_Story",
	"KRO_Story",
	"SEK_Story",
	"PL1_Story_NoMask",
	"SHTpa_Story",
	"SHTpa_Story_Burnt",
	"SHTpa_Story_NoProp",
	"SHTpr_Story",
	"SHTpr_Story_NoCrown",
	"SHTpr_Story_NoProp",
	"SHT_A",
	"SHT_B",
	"SHT_C",
	"SHT_D",
	"SHT_DefaultPreset_02",
	"SHT_E",
	"SHT_F",
	"SHT_G",
	"SHT_H",
	"SHT_I",
	"SHT_J",
	"NITpa_Story",
	"NITpa_Story_NoProp",
	"NITrv_Story",
	"NITrv_Story_NoProp",
	"NITrv_Story_NoProp_SoulDrain",
	"NIT_A",
	"NIT_B",
	"NIT_D",
	"NIT_DefaultPreset_02",
	"NIT_E",
	"NIT_GEARTest",
	"TRM_defaultpreset_02",
	"TRM_NoGlasses",
	"TRM_SKIN_A",
	"TRM_SKIN_B",
	"TRM_SKIN_D",
	"TRM_SKIN_E1",
	"TRM_SKIN_E2",
	"TRM_SKIN_E3",
	"TRM_SKIN_E4",
	"TRM_SKIN_E5",
	"SINpa_Story",
	"SINpa_Story_SoulDrain",
	"SINrv_Story",
	"SIN_A",
	"SIN_B",
	"SIN_D",
	"SIN_DefaultPreset_02",
	"SIN_E",
	"SIN_E1",
	"JOK_A",
	"JOK_B",
	"JOK_D",
	"JOK_DefaultPreset_02",
	"JOK_E",
	"SPA_A",
	"SPA_B",
	"SPA_B_02",
	"SPA_C",
	"SPA_D",
	"SPA_DefaultPreset_02",
	"SPA_E",
	"SHE_A",
	"SHE_B",
	"SHE_D",
	"SHE_DefaultPreset_02",
	"SHE_E",
	"SHE_Story",
	"FUJdk_Story",
	"FUJdk_Story_NoProps",
	"FUJ_A",
	"FUJ_B",
	"FUJ_C",
	"FUJ_D",
	"FUJ_DefaultPreset_02",
	"FUJ_E",
	"FUJ_Story",
	"FUJ_Story_NoProps",
	"FUJ_Story_SoulDrain",
	"ROB_D",
	"ROB_D1",
	"ROB_DefaultPreset_02",
	"ROB_Maskless",
	"ROB_SKIN_A",
	"ROB_SKIN_A1",
	"ROB_SKIN_B",
	"ROB_SKIN_B1",
	"ROB_SKIN_C",
	"MIL_A",
	"MIL_B",
	"MIL_C",
	"MIL_D",
	"MIL_DefaultPreset_02",
	"MIL_G",
	"MIL_H",
	"MIL_NoMask",
	"RAM_A",
	"RAM_A1",
	"RAM_B",
	"RAM_B1",
	"RAM_C",
	"RAM_D",
	"RAM_DefaultPreset_02",
	"RAM_E",
	"RAN_A",
	"RAN_B",
	"RAN_C",
	"RAN_D",
	"RAN_DefaultPreset_02",
	"RAN_E",
	"RAN_NoMask",
	// more weird stuff
	"LIU_Story_FireGod",
	"LIU_Tower_FireGod",

};
const char* szStageNames[]{
	"BGND_BlackMarketAlley",
	"BGND_CyberLinKueiAssembly",
	"BGND_GorosLair",
	"BGND_KharonsShip",
	"BGND_KoliseumBeastiary",
	"BGND_KotalsKoliseum",
	"BGND_KronikaHourGlass",
	"BGND_KronikaHourGlassNT",
	"BGND_KronikaHourGlassPrehistoric",
	"BGND_KronikaHourGlassChoatian",
	"BGND_KytinnLostHive",
	"BGND_MainMenuBackground",
	"BGND_SeaOfBlood",
	"BGND_ShangTsungsIslandRuins",
	"BGND_ShaolinTrapDungeon",
	"BGND_ShinnoksBoneSepulcher",
	"BGND_ShiRaiRyuFireGarden",
	"BGND_SpecialForcesDesertCommand",
	"BGND_TankGarageBunker",
	"BGND_TarkatanWarCamp",
	"BGND_TournamentLevel",
	"BGND_TournamentLVCMB",
	"BGND_TournamentLVNRS",
	"BGND_TournamentLVCEO",
	"BGND_TournamentLVEVO",
	"BGND_TournamentLVVNY",
	"BGND_TournamentLVDRM",
	"BGND_TournamentLVCTD",
	"BGND_TournamentLVBGS",
	"BGND_TournamentLVNEC",
	"BGND_TournamentLVECT",
	"BGND_TournamentLVFKT",
	"BGND_WuShiDragonGrotto",

};
const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Third Person",
	"Third Person #2",
	"First Person",
	"First Person Mid",
	"Injustice 2"
};
const char* szModifierModes[TOTAL_MODES] = {
	"Select Screen Swap",
	"Fight Init",
};
const char* szCharClasses[TOTAL_CHARACTER_CLASSES] = {
	"Base",
	"TestCharacters",
	"Generated",
	"NPCs",
};
const char* szKryptCharacters[] = {
	// place npcs first for easy access
	"CHAR_Cyrax",
	"CHAR_Sektor",
	"CHAR_FireGod",
	"CHAR_Kronika",
	// rest of the cast
	"CHAR_Baraka",
	"CHAR_Cage",
	"CHAR_Cassie",
	"CHAR_Cetrion",
	"CHAR_DVorah",
	"CHAR_ErronBlack",
	"CHAR_Jacqui",
	"CHAR_Jade",
	"CHAR_Jax",
	"CHAR_Kabal",
	"CHAR_Kano",
	"CHAR_Kitana",
	"CHAR_Kollector",
	"CHAR_Kotal",
	"CHAR_KungLao",
	"CHAR_LiuKang",
	"CHAR_Noob",
	"CHAR_Raiden",
	"CHAR_Scorpion",
	"CHAR_Skarlet",
	"CHAR_Sonya",
	"CHAR_SubZero",
	"CHAR_Terminas",
	"CHAR_Terminator",
	"CHAR_Spawn",
	"CHAR_Sindel",
	"CHAR_ShaoKahn",
	"CHAR_Rambo",
	"CHAR_Robocop",
	"CHAR_Rain",
	"CHAR_ShangTsung",
	"CHAR_Joker",
	"CHAR_Fujin",
	"CHAR_Sheeva",
	"CHAR_CyberFrost",
	"CHAR_Nightwolf",
	"CHAR_Mileena",
};


int GetCamMode(const char* mode)
{
	for (int i = 0; i < TOTAL_CUSTOM_CAMERAS; i++)
	{
		if (strcmp(mode, szCameraModes[i]) == 0)
		{
			return i;
			break;
		}
	}
	return -1;
}

int GetModifierMode(const char* mode)
{
	for (int i = 0; i < TOTAL_MODES; i++)
	{
		if (strcmp(mode, szModifierModes[i]) == 0)
		{
			return i;
			break;
		}
	}
	return -1;
}

MK11Menu* TheMenu = new MK11Menu();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}

}

void MK11Menu::Initialize()
{
	m_bIsActive = false;
	m_bPlayer1Modifier = false;
	m_bPlayer2Modifier = false;
	m_bNoHealthP1 = false;
	m_bNoHealthP1 = false;
	m_bOneHealthP1 = false;
	m_bOneHealthP2 = false;
	m_bCustomCameraPos = false;
	m_bCustomCameraRot = false;
	m_bCustomCameraFOV = false;
	m_bYObtained = false;
	m_bCustomCameras = false;
	m_bFreeCamMouseInvertY = true;
	m_bFreezeWorld = false;
	m_bIsFocused = false;
	m_bChangePlayerSpeed = false;
	m_bChangePlayerScale = false;
	m_bInfiniteHealthP1 = false;
	m_bInfiniteHealthP2 = false;
	m_bInfiniteAttackP1 = false;
	m_bInfiniteDefendP1 = false;
	m_bInfiniteAttackP2 = false;
	m_bInfiniteDefendP2 = false;
	m_bKryptModifier = false;
	m_bAutoHideHUD = false;
	m_bDisableGearLoadouts = false;
	m_bDisableHUD = false;
	m_bHookDispatch = false;
	m_bForceCameraUpdate = false;
	m_bTagAssist = false;
	m_bTagAssistP2 = false;
	m_bSlowMotion = false;
	m_bP1CustomAbilities = false;
	m_bP2CustomAbilities = false;
	m_bSmoothScaleChange = false;


	m_nCurrentCharModifier = MODIFIER_SCREEN;
	m_nFreeCameraRotationSpeed = 120;
	m_nCurrentCustomCamera = -1;
	m_nP1Abilities = 0;
	m_nP2Abilities = 0;
	mouseSpeedX = 0;
	mouseSpeedY = 0;
	mouseSens = 5;
	orgMouse.x = GetSystemMetrics(SM_CXSCREEN) / 2;
	orgMouse.y = GetSystemMetrics(SM_CYSCREEN) / 2;

	m_fSlowMotionSpeed = 0.5f;
	m_fFreeCameraSpeed = 5.25f;
	m_fAdjustCustomCameraZ = 161.0f;
	m_fAdjustCustomCameraX = -10.0f;
	m_fAdjustCustomCameraThirdPersonY = 0;
	m_fAdjustCustomCameraThirdPersonX = 0;
	m_fAdjustCustomCameraThirdPersonZ = 0;
	m_fAdjustCustomCameraCrouch = 120.0f;
	m_fP1Speed = 1.0f;
	m_fP2Speed = 1.0f;
	m_vP1Scale = { 1.0f,1.0f,1.0f };
	m_vP2Scale = { 1.0f,1.0f,1.0f };
	m_fSmoothScalingUpdate = 0.01f;
	camFov = 0;




	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szCurrentModifier, szModifierModes[0]);
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	sprintf(szCurrentKryptCharacter, szCharacters[0]);
	sprintf(szCurrentKryptCharacterClass, szCharClasses[0]);
	sprintf(szPlayer1TagAssistCharacter, szKryptCharacters[0]);
	sprintf(szPlayer2TagAssistCharacter, szKryptCharacters[0]);

}

void MK11Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetMK11HookVersion(),&m_bIsActive);
	if (ImGui::BeginTabBar("##tabs"))
	{

		if (ImGui::BeginTabItem("Character Modifier"))
		{

			ImGui::Text("Select a method for replacing characters.\nSelect Screen - replaces character during selection, works with normal gamemodes\n"
				"Fight Init - Replaces character during game loading, allows to change characters\nin story mode, attract, practice.\n");

			if (m_nCurrentCharModifier == MODIFIER_FIGHT)
				ImGui::Text("NOTE: Game modes with intros crash in fight init modifier!\n");
			if (ImGui::BeginCombo("Modifier Mode", szCurrentModifier))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szModifierModes); n++)
				{
					bool is_selected = (szCurrentModifier == szModifierModes[n]);
					if (ImGui::Selectable(szModifierModes[n], is_selected))
						sprintf(szCurrentModifier, szModifierModes[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			m_nCurrentCharModifier = GetModifierMode(szCurrentModifier);


			ImGui::Separator();


			ImGui::Checkbox("Enable Player 1 Modifier", &m_bPlayer1Modifier);

			if (m_nCurrentCharModifier == MODIFIER_SCREEN)
			{
				ImGui::SameLine();
				ShowHelpMarker("Should work in all game modes. You'll most likely need a gamepad for tower modes when playing as NPCs.");
			}


			if (ImGui::BeginCombo("Player 1 Character", szPlayer1ModifierCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
				{
					bool is_selected = (szPlayer1ModifierCharacter == szCharacters[n]);
					if (ImGui::Selectable(szCharacters[n], is_selected))
						sprintf(szPlayer1ModifierCharacter, szCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::Separator();
			ImGui::Checkbox("Enable Player 2 Modifier", &m_bPlayer2Modifier);

			if (ImGui::BeginCombo("Player 2 Character", szPlayer2ModifierCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
				{
					bool is_selected = (szPlayer2ModifierCharacter == szCharacters[n]);
					if (ImGui::Selectable(szCharacters[n], is_selected))
						sprintf(szPlayer2ModifierCharacter, szCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::Separator();

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage Modifier"))
		{


			ImGui::Checkbox("Enable Stage Modifier", &m_bStageModifier);

			if (ImGui::BeginCombo("Stage", szStageModifierStage))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szStageNames); n++)
				{
					bool is_selected = (szStageModifierStage == szCameraModes[n]);
					if (ImGui::Selectable(szStageNames[n], is_selected))
						sprintf(szStageModifierStage, szStageNames[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Modifiers"))
		{
			if (ImGui::BeginTabBar("##modifiers"))
			{
				if (ImGui::BeginTabItem("Tag Assists"))
				{
					ImGui::Checkbox("Player 1 Tag Assist Modifier", &m_bTagAssist);


					if (ImGui::BeginCombo("Player 1 Tag Assist Character", szPlayer1TagAssistCharacter))
					{
						for (int n = 0; n < IM_ARRAYSIZE(szKryptCharacters); n++)
						{
							bool is_selected = (szPlayer1TagAssistCharacter == szKryptCharacters[n]);
							if (ImGui::Selectable(szKryptCharacters[n], is_selected))
								sprintf(szPlayer1TagAssistCharacter, szKryptCharacters[n]);
							if (is_selected)
								ImGui::SetItemDefaultFocus();

						}
						ImGui::EndCombo();
					}
					ImGui::Separator();
					ImGui::Checkbox("Player 2 Tag Assist Modifier", &m_bTagAssistP2);


					if (ImGui::BeginCombo("Player 2 Tag Assist Character", szPlayer2TagAssistCharacter))
					{
						for (int n = 0; n < IM_ARRAYSIZE(szKryptCharacters); n++)
						{
							bool is_selected = (szPlayer2TagAssistCharacter == szKryptCharacters[n]);
							if (ImGui::Selectable(szKryptCharacters[n], is_selected))
								sprintf(szPlayer2TagAssistCharacter, szKryptCharacters[n]);
							if (is_selected)
								ImGui::SetItemDefaultFocus();

						}
						ImGui::EndCombo();
					}
					ImGui::Separator();

					ImGui::Text("NOTE: Scorpion will not work unless previously loaded (eg. P2).\nIf you get load crashes enable modifier in-game then restart or rematch (when online).");
					ImGui::Text("Restart match when you toggle these in game!");
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Abilities"))
				{

					ImGui::Checkbox("Player 1 Custom Abilities", &m_bP1CustomAbilities);
					ImGui::SameLine(); ShowHelpMarker("Set these on select screen! Changing these in game might make moves locked. Hold L SHIFT to view numeric value.");
					ImGui::Separator();
					
					for (int i = 0; i < sizeof(m_P1Abilities) / sizeof(m_P1Abilities[0]); i++)
					{
						int val = pow(2, i);
						if (GetAsyncKeyState(VK_LSHIFT))
							sprintf(textBuffer, "Ability %d (%d)", i + 1, val);
						else
							sprintf(textBuffer, "Ability %d", i + 1);

						ImGui::Checkbox(textBuffer, &m_P1Abilities[i]);

						if (i % 2 == 0)
							ImGui::SameLine();
					}


					if (GetObj(PLAYER1))
					{
						if (ImGui::Button("Get##p1"))
						{
							int abilities = GetObj(PLAYER1)->GetAbility();

							for (int i = 0; i < sizeof(m_P1Abilities) / sizeof(m_P1Abilities[0]); i++)
							{
								int id = pow(2, i);
								m_P1Abilities[i] = abilities & id;
							}
						}

					}
					ImGui::Separator();
					ImGui::Checkbox("Player 2 Custom Abilities", &m_bP2CustomAbilities);
					ImGui::Separator();

					for (int i = 0; i < sizeof(m_P2Abilities) / sizeof(m_P2Abilities[0]); i++)
					{
						int val = pow(2, i);
						if (GetAsyncKeyState(VK_LSHIFT))
							sprintf(textBuffer, "Ability %d (%d)##p2", i + 1, val);
						else
							sprintf(textBuffer, "Ability %d##p2", i + 1);

						ImGui::Checkbox(textBuffer, &m_P2Abilities[i]);

						if (i % 2 == 0)
							ImGui::SameLine();
					}


					if (GetObj(PLAYER2))
					{
						if (ImGui::Button("Get##p2"))
						{
							int abilities = GetObj(PLAYER2)->GetAbility();

							for (int i = 0; i < sizeof(m_P2Abilities) / sizeof(m_P2Abilities[0]); i++)
							{
								int id = pow(2, i);
								m_P2Abilities[i] = abilities & id;
							}
						}

					}

					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player Control"))
		{
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			{
				ImGui::Checkbox("Change Player Speed", &m_bChangePlayerSpeed);
				ImGui::SliderFloat("Player 1", &m_fP1Speed, 0.0, 10.0f);
				ImGui::SliderFloat("Player 2", &m_fP2Speed, 0.0, 10.0f);
				if (ImGui::Button("Reset Speed"))
				{
					m_fP1Speed = 1.0f;
					m_fP2Speed = 1.0f;
					if (GetObj(PLAYER1))
						GetObj(PLAYER1)->SetSpeed(m_fP1Speed);
					if (GetObj(PLAYER2))
						GetObj(PLAYER2)->SetSpeed(m_fP1Speed);
				}
				ImGui::Separator();
				ImGui::Checkbox("Change Player Scale", &m_bChangePlayerScale);
				ImGui::InputFloat3("Player 1 ", &m_vP1Scale.X);
				ImGui::InputFloat3("Player 2 ", &m_vP2Scale.X);

				ImGui::Checkbox("Smooth Player Scale", &m_bSmoothScaleChange);
				ImGui::InputFloat("Smooth Scale Value", &m_fSmoothScalingUpdate);


				if (ImGui::Button("Reset Scale"))
				{
					m_vP1Scale = { 1.0f,1.0f,1.0f };
					m_vP2Scale = { 1.0f,1.0f,1.0f };
					if (GetObj(PLAYER1))
						GetObj(PLAYER1)->SetScale(&m_vP1Scale);
					if (GetObj(PLAYER2))
						GetObj(PLAYER2)->SetScale(&m_vP2Scale);
				}


				ImGui::Separator();





				if (GetObj(PLAYER1) && GetObj(PLAYER2))
				{

					ImGui::Text("Position");
					ImGui::SameLine(); ShowHelpMarker("Read only!");
					GetCharacterPosition(&plrPos, PLAYER1);
					ImGui::InputFloat3("X | Y | Z", &plrPos.X);
					GetCharacterPosition(&plrPos2, PLAYER2);
					ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
				}




			}
			else
				ImGui::Text("Player options are only available in-game!");

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Speed Modifier"))
		{
			ImGui::Text("Gamespeed Control");
			ImGui::InputFloat("", &m_fSlowMotionSpeed, 0.1);

			if (m_fSlowMotionSpeed > 2.0f) m_fSlowMotionSpeed = 2.0f;
			if (m_fSlowMotionSpeed < 0.0f) m_fSlowMotionSpeed = 0.0f;
			ImGui::Checkbox("Enable", &m_bSlowMotion);
			ImGui::SameLine();
			ShowHelpMarker("Hotkey - F5");


			ImGui::Separator();
			ImGui::Text("Tick this checkbox if you want to freeze game with a button, this might cause\nissues with pause menus and stuff so enable only when needed!");
			ImGui::Checkbox("Hook Freeze World", &m_bHookDispatch);

			if (m_bHookDispatch)
			{
				ImGui::Checkbox("Freeze World", &m_bFreezeWorld);
				ImGui::SameLine();
				ShowHelpMarker("Hotkey - F2");
			}


			ImGui::Separator();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Control"))
		{
			ImGui::Checkbox("Set Camera Position", &m_bCustomCameraPos);
			ImGui::InputFloat3("X | Y | Z", &camPos.X);
			ImGui::Checkbox("Set Camera Rotation", &m_bCustomCameraRot);
			ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);

			ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);
			ImGui::InputFloat("FOV", &camFov);

			ImGui::Separator();
			ImGui::Checkbox("Enable Freecam", &m_bFreeCam);
			ImGui::SameLine(); ShowHelpMarker("Allows to move camera with certain keys.\nRequires all toggles enabled!\nYou can configure keys in .ini file.");

			if (m_bFreeCam)
			{
				if (!m_bCustomCameraPos || !m_bCustomCameraRot || !m_bCustomCameraFOV)
					ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Check rest of the Set Camera options!");

				ImGui::InputFloat("Freecam Speed", &m_fFreeCameraSpeed);
				ImGui::InputInt("Freecam Rotation Speed", &m_nFreeCameraRotationSpeed);

				ImGui::Separator();
				ImGui::Checkbox("Mouse Control", &m_bFreeCamMouseControl);

				if (m_bFreeCamMouseControl)
				{
					ImGui::SameLine();  ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "This feature is not yet finished!");
					ImGui::Checkbox("Invert Y", &m_bFreeCamMouseInvertY);
					ImGui::SliderInt("Mouse Smoothness", &mouseSens, 1, 15);
				}
			}




			ImGui::Separator();
			ImGui::Checkbox("Force Camera To Move", &m_bForceCameraUpdate);
			ImGui::SameLine(); ShowHelpMarker("Check this option if the game you can't move camera anymore in win poses and some cinematics.");

			ImGui::Separator();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			{
				ImGui::Checkbox("Custom Cameras", &m_bCustomCameras);

				if (ImGui::BeginCombo("Mode", szCurrentCameraOption))
				{
					for (int n = 0; n < IM_ARRAYSIZE(szCameraModes); n++)
					{
						bool is_selected = (szCurrentCameraOption == szCameraModes[n]);
						if (ImGui::Selectable(szCameraModes[n], is_selected))
							sprintf(szCurrentCameraOption, szCameraModes[n]);
						if (is_selected)
							ImGui::SetItemDefaultFocus();

					}
					ImGui::EndCombo();
				}
				m_nCurrentCustomCamera = GetCamMode(szCurrentCameraOption);
				if (m_nCurrentCustomCamera == CAMERA_1STPERSON || m_nCurrentCustomCamera == CAMERA_1STPERSON_MID)
				{
					ImGui::InputFloat("FPS Camera Offset", &m_fAdjustCustomCameraY);
					ImGui::InputFloat("FPS Up/Down Offset", &m_fAdjustCustomCameraZ);
					ImGui::InputFloat("FPS Left/Right Offset", &m_fAdjustCustomCameraX);
					ImGui::InputFloat("FPS Crouch Offset", &m_fAdjustCustomCameraCrouch);
				}
				else if (m_nCurrentCustomCamera == CAMERA_3RDPERSON)
				{
					ImGui::InputFloat("TPP Camera Offset", &m_fAdjustCustomCameraThirdPersonY);
					ImGui::InputFloat("TPP Up/Down Offset", &m_fAdjustCustomCameraThirdPersonZ);
					ImGui::InputFloat("TPP Left/Right Offset", &m_fAdjustCustomCameraThirdPersonX);
				}
			}
			else
				ImGui::Text("Custom cameras will appear once in-game!");

			ImGui::EndTabItem();

		}
		if (ImGui::BeginTabItem("Cheats"))
		{

			ImGui::Separator();
			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, 220);

			ImGui::Text("Infinite Health");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##infhealth", &m_bInfiniteHealthP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##infhealth", &m_bInfiniteHealthP2);
			ImGui::NextColumn();


			ImGui::Text("Zero Health\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##0health", &m_bNoHealthP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##0health", &m_bNoHealthP2);
			ImGui::NextColumn();


			ImGui::Text("1 Health\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##1health", &m_bOneHealthP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##1health", &m_bOneHealthP2);
			ImGui::NextColumn();


			ImGui::Text("Infinite Offensive Bar\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##atk", &m_bInfiniteAttackP1);
			ImGui::SameLine();
			ImGui::Checkbox("P2##atk", &m_bInfiniteAttackP2);
			ImGui::NextColumn();

			ImGui::Text("Infinite Defensive Bar\n");
			ImGui::NextColumn();
			ImGui::Checkbox("P1##def", &m_bInfiniteDefendP1);
			ImGui::SameLine();					  
			ImGui::Checkbox("P2##def", &m_bInfiniteDefendP2);
			ImGui::NextColumn();


			ImGui::Columns(1);
			ImGui::Separator();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			ImGui::Text("Easy Krushing Blows");

			if (GetObj(PLAYER1))
			{
				if (ImGui::Button("Enable  P1"))
					GetObj(PLAYER1)->SetEasyKrushingBlows(true);
				ImGui::SameLine();
				if (ImGui::Button("Disable P1"))
					GetObj(PLAYER1)->SetEasyKrushingBlows(false);
			}
			if (GetObj(PLAYER1))
			{
				if (ImGui::Button("Enable  P2"))
					GetObj(PLAYER1)->SetEasyKrushingBlows(true);
				ImGui::SameLine();
				if (ImGui::Button("Disable P2"))
					GetObj(PLAYER1)->SetEasyKrushingBlows(false);
			}
			ImGui::Separator();

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Krypt Modifier"))
		{

			ImGui::Text("Make sure you match the character class! It's trial & error if a character doesn't work.");
			ImGui::Text("Normal characters use Base class, while Sektor/Cyrax use NPCs. Some might not work at all.");
			ImGui::Separator();
			ImGui::Checkbox("Change Krypt Character", &m_bKryptModifier);

			if (ImGui::BeginCombo("Character Class", szCurrentKryptCharacterClass))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharClasses); n++)
				{
					bool is_selected = (szCurrentKryptCharacterClass == szCharClasses[n]);
					if (ImGui::Selectable(szCharClasses[n], is_selected))
						sprintf(szCurrentKryptCharacterClass, szCharClasses[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}


			if (ImGui::BeginCombo("Krypt Character", szCurrentKryptCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szKryptCharacters); n++)
				{
					bool is_selected = (szCurrentKryptCharacter == szKryptCharacters[n]);
					if (ImGui::Selectable(szKryptCharacters[n], is_selected))
						sprintf(szCurrentKryptCharacter, szKryptCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}


			ImGui::Separator();
			ImGui::Text("NOTE: This only changes character during krypt load!");

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			if (ImGui::Button("Hide FightHUD"))
				HideHUD();
			ImGui::SameLine();
			if (ImGui::Button("Show FightHUD"))
				ShowHUD();

			ImGui::Checkbox("Hide FightHUD In Game", &m_bAutoHideHUD);
			ImGui::Checkbox("Disable HUD Completely", &m_bDisableHUD);
			ImGui::SameLine();
			ShowHelpMarker("You'll need to go in-game/back to menu for this option to take effect.");

			ImGui::Checkbox("Disable Nondefault Gear Loadouts", &m_bDisableGearLoadouts);
			ImGui::SameLine();
			ShowHelpMarker("Only default loadouts will be used. Do not toggle this option when models are on screen.");
			ImGui::EndTabItem();


		}
		ImGui::EndTabBar();
	}
	ImGui::End();


}

void MK11Menu::Process()
{
	UpdateControls();
	if (m_bIsFocused && m_bFreeCamMouseControl)
		UpdateMouse();

}

void MK11Menu::UpdateControls()
{
	if (GetAsyncKeyState(SettingsMgr->iHookMenuOpenKey))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		m_bIsActive ^= 1;
	}


	if (GetAsyncKeyState(VK_F5))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		m_bSlowMotion ^= 1;
	}

	if (GetAsyncKeyState(VK_F2))
	{
		if (m_bHookDispatch)
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			m_bFreezeWorld ^= 1;
		}

	}

	if (m_bSlowMotion)
	{
		if (GetAsyncKeyState(VK_F6))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			m_fSlowMotionSpeed += 0.1f;
		}
		if (GetAsyncKeyState(VK_F7))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			m_fSlowMotionSpeed -= 0.1f;
		}
	}

}

void MK11Menu::UpdateMouse()
{
	if (m_bIsActive) return;

	GetCursorPos(&curMouse);
	mouseSpeedX = curMouse.x - orgMouse.x;
	mouseSpeedY = curMouse.y - orgMouse.y;


	if (m_bIsFocused)
	{
		if (TheMenu->m_bFreeCam)
		{
			int newVal = TheMenu->camRot.Yaw;
			newVal += mouseSpeedX / mouseSens;
			TheMenu->camRot.Yaw = newVal;


			int newValY = TheMenu->camRot.Pitch;

			if (m_bFreeCamMouseInvertY) mouseSpeedY *= -1;

			newValY += mouseSpeedY / mouseSens;
			TheMenu->camRot.Pitch = newValY;
		}
	}

}

bool MK11Menu::GetActiveState()
{
	return m_bIsActive;
}

char * GetMK11HookVersion()
{
	static char buffer[512] = {};
	sprintf(buffer, "MK11Hook by ermaccer (%s)", MK11HOOK_VERSION);
	return buffer;
}

void PushNotification()
{
}
