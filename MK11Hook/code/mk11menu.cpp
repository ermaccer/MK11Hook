#include "mk11menu.h"
#include <Windows.h>
#include "mk10utils.h"
#include "mk11.h"
#include <iostream>
#include "..\imgui\imgui.h"
#include "eSettingsManager.h"
#include "..\utils\MemoryMgr.h"

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
	bPlayer1ModifierEnabled = false;
	bPlayer2ModifierEnabled = false;

	iCharacterModifierMode = MODIFIER_SCREEN;

	bCustomCamera = false;
	bCustomCameraRot = false;
	bCustomFOV = false;
	iCurrentTab = 0;
	bSlowMotionEnabled = 0;
	fSlowMotionSpeed = 0.5f;

	bYObtained = false;
	fFreeCameraSpeed = 5.25f;
	iFreeCameraRotSpeed = 120;
	bEnableCustomCameras = false;
	iCurrentCustomCamera = -1;
	fAdjustCamZ = 161.0f;
	fAdjustCamX = -10.0f;
	fAdjustCam3 = 0;
	fAdjustCamX3 = 0;
	fAdjustCamZ3 = 0;
	camFov = 0;
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szCurrentModifier, szModifierModes[0]);
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	orgMouse.x = GetSystemMetrics(SM_CXSCREEN) / 2;
	orgMouse.y = GetSystemMetrics(SM_CYSCREEN) / 2;
	mouseSpeedX = 0;
	mouseSpeedY = 0;
	mouseScroll = 0;
	mouseSens = 5;
	bInvertMouseY = true;
	bFreezeWorld = false;
	bFocused = false;
	bAboutWindow = false;

	bChangePlayerSpeed = false;
	fPlayer1Speed = 1.0f;
	fPlayer2Speed = 1.0f;


	bChangePlayerScale = false;
	fPlayer1Scale = { 1.0f,1.0f,1.0f };
	fPlayer2Scale = { 1.0f,1.0f,1.0f };

	bInfiniteHealthPlayer1 = false;
	bInfiniteHealthPlayer2 = false;
	bInfiniteAttackBarPlayer1 = false;
	bInfiniteDefendBarPlayer1 = false;
	bInfiniteAttackBarPlayer2 = false;
	bInfiniteDefendBarPlayer2 = false;

	bNoHealthPlayer1 = false;
	bNoHealthPlayer2 = false;
	b1HealthPlayer1 = false;
	b1HealthPlayer2 = false;


	bChangeKryptCharacter = false;
	sprintf(szCurrentKryptCharacter, szCharacters[0]);
	sprintf(szCurrentKryptCharacterClass, szCharClasses[0]);
}

void MK11Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetMK11HookVersion());
	if (ImGui::BeginTabBar("##tabs"))
	{

		if (ImGui::BeginTabItem("Character Modifier"))
		{

			ImGui::Text("Select a method for replacing characters.\nSelect Screen - replaces character during selection, works with normal gamemodes\n"
				"Fight Init - Replaces character during game loading, allows to change characters\nin story mode, attract, practice.\n"
				"NOTE: Game modes with intros crash!\n");
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
			iCharacterModifierMode = GetModifierMode(szCurrentModifier);


			ImGui::Separator();


			ImGui::Checkbox("Enable Player 1 Modifier", &bPlayer1ModifierEnabled);
		
			if (iCharacterModifierMode == MODIFIER_SCREEN)
			{
				ImGui::SameLine();
				ShowHelpMarker("Should work in all game modes, to reset character cell (in case it gets stuck) please exit and enter game mode again, or just select original character from modifier list. You'll most likely need a gamepad for tower modes. NB: Doesn't work with DLC characters!");
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
			ImGui::Checkbox("Enable Player 2 Modifier", &bPlayer2ModifierEnabled);

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


			ImGui::Checkbox("Enable Stage Modifier", &bStageModifier);

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
		if (ImGui::BeginTabItem("Player Control"))
		{
			ImGui::Checkbox("Change Player Speed", &bChangePlayerSpeed);
			ImGui::SliderFloat("Player 1", &fPlayer1Speed, 0.0, 10.0f);
			ImGui::SliderFloat("Player 2", &fPlayer2Speed, 0.0, 10.0f);

			bool reset = ImGui::Button("Reset Speed");
			if (reset)
			{
				fPlayer1Speed = 1.0f;
				fPlayer2Speed = 1.0f;
			}

			ImGui::Separator();
			ImGui::Checkbox("Change Player Scale", &bChangePlayerScale);
			ImGui::InputFloat3("Player 1 ", &fPlayer1Scale.X);
			ImGui::InputFloat3("Player 2 ", &fPlayer2Scale.X);

			bool scale_reset = ImGui::Button("Reset Scale");
			if (scale_reset)
			{
				fPlayer1Scale = { 1.0f,1.0f,1.0f };
				fPlayer2Scale = { 1.0f,1.0f,1.0f };
			}

			ImGui::Separator();
			ImGui::Text("Position");
			ImGui::SameLine(); ShowHelpMarker("Preview only!");
			if (MK11::GetCharacterObject(PLAYER1))
			{
				MK11::GetCharacterPosition(&plrPos, PLAYER1);
				ImGui::InputFloat3("X | Y | Z", &plrPos.X);
			}
			if (MK11::GetCharacterObject(PLAYER2))
			{
				MK11::GetCharacterPosition(&plrPos2, PLAYER2);
				ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Speed Modifier"))
		{
			ImGui::Text("Gamespeed Control");
			ImGui::InputFloat("", &fSlowMotionSpeed, 0.1);

			if (fSlowMotionSpeed > 2.0f) fSlowMotionSpeed = 2.0f;
			if (fSlowMotionSpeed < 0.0f) fSlowMotionSpeed = 0.0f;
			ImGui::Checkbox("Enable", &bSlowMotionEnabled);

			ImGui::Separator();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Control"))
		{
			ImGui::Checkbox("Custom Camera Position", &bCustomCamera);
			ImGui::InputFloat3("X | Y | Z", &camPos.X);
			ImGui::Checkbox("Custom Camera Rotation", &bCustomCameraRot);
			ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);
			if (SettingsMgr->bGlobalCameraHook)
			{
				ImGui::Checkbox("Custom FOV", &bCustomFOV);
				ImGui::InputFloat("FOV", &camFov);
			}
			ImGui::Separator();
			ImGui::Checkbox("Enable Freecam", &bFreeCameraMovement);
			ImGui::SameLine(); ShowHelpMarker("Requires both toggles enabled!\n You can configure keys in .ini file.");
			ImGui::InputFloat("Freecam Speed", &fFreeCameraSpeed);
			ImGui::InputInt("Freecam Rotation Speed", &iFreeCameraRotSpeed);

			if (bFreeCameraMovement)
			{
				ImGui::Separator();
				ImGui::Checkbox("Mouse Control", &bEnableMouseControl);

				if (bEnableMouseControl)
				{
					ImGui::Checkbox("Invert Y", &bInvertMouseY);
					ImGui::SliderInt("Mouse Smoothness", &mouseSens, 1, 15);
				}
			}


			ImGui::Separator();
			if (MK11::GetCharacterObject(PLAYER1) && MK11::GetCharacterObject(PLAYER2))
			{
				ImGui::Checkbox("Custom Cameras", &bEnableCustomCameras);

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
				iCurrentCustomCamera = GetCamMode(szCurrentCameraOption);
				if (iCurrentCustomCamera == CAMERA_1STPERSON || iCurrentCustomCamera == CAMERA_1STPERSON_MID)
				{
					ImGui::InputFloat("FPS Camera Offset", &fAdjustCam);
					ImGui::InputFloat("FPS Up/Down Offset", &fAdjustCamZ);
					ImGui::InputFloat("FPS Left/Right Offset", &fAdjustCamX);
				}
				else if (iCurrentCustomCamera == CAMERA_3RDPERSON)
				{
					ImGui::InputFloat("TPP Camera Offset", &fAdjustCam3);
					ImGui::InputFloat("TPP Up/Down Offset", &fAdjustCamZ3);
					ImGui::InputFloat("TPP Left/Right Offset", &fAdjustCamX3);
				}
			}
			else
				ImGui::Text("Custom cameras will appear once ingame!");

			ImGui::EndTabItem();

		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			ImGui::Text("Player 1");
			ImGui::Separator();
			ImGui::Checkbox("Infinite Health", &bInfiniteHealthPlayer1);
			ImGui::Checkbox("Infinite Offensive Bar", &bInfiniteAttackBarPlayer1);
			ImGui::Checkbox("Infinite Defensive Bar", &bInfiniteDefendBarPlayer1);
			ImGui::Checkbox("Zero Health", &bNoHealthPlayer1);
			ImGui::Checkbox("1 Health", &b1HealthPlayer1);
			if (MK11::GetCharacterObject(PLAYER1))
			{
				if (ImGui::Button("Enable Easy Krushing Blows"))
					MK11::SetCharacterEasyKB(MK11::GetCharacterObject(PLAYER1), 1);
				if (ImGui::Button("Disable Easy Krushing Blows"))
					MK11::SetCharacterEasyKB(MK11::GetCharacterObject(PLAYER1), 0);
			}
			ImGui::Separator();

			ImGui::Text("Player 2");
			ImGui::Separator();
			ImGui::Checkbox("Infinite Health ", &bInfiniteHealthPlayer2);
			ImGui::Checkbox("Infinite Offensive Bar ", &bInfiniteAttackBarPlayer2);
			ImGui::Checkbox("Infinite Defensive Bar ", &bInfiniteDefendBarPlayer2);
			ImGui::Checkbox("Zero Health ", &bNoHealthPlayer2);
			ImGui::Checkbox("1 Health ", &b1HealthPlayer2);
			if (MK11::GetCharacterObject(PLAYER2))
			{
				if (ImGui::Button("Enable Easy Krushing Blows "))
					MK11::SetCharacterEasyKB(MK11::GetCharacterObject(PLAYER2), 1);
				if (ImGui::Button("Disable Easy Krushing Blows "))
					MK11::SetCharacterEasyKB(MK11::GetCharacterObject(PLAYER2), 0);
			}
			ImGui::Separator();

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Krypt Modifier"))
		{

			ImGui::Text("Make sure you match the character class! It's trial & error if a character doesn't work.");
			ImGui::Text("Normal characters use Base class, while Sektor/Cyrax use NPCs. Some might not work at all.");
			ImGui::Separator();
			ImGui::Checkbox("Change Krypt Character",&bChangeKryptCharacter);

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
				MK11::HideHUD();
			ImGui::SameLine();
			if (ImGui::Button("Show FightHUD"))
				MK11::ShowHUD();
			ImGui::EndTabItem();

		}

		ImGui::End();
	}










}

void MK11Menu::Process()
{
	UpdateControls();
	if (bFocused && bEnableMouseControl)
	UpdateMouse();
}

void MK11Menu::UpdateControls()
{

	if (GetAsyncKeyState(VK_F5))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		bSlowMotionEnabled ^= 1;
	}

	if (bSlowMotionEnabled)
	{
		if (GetAsyncKeyState(VK_F6))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			fSlowMotionSpeed += 0.1f;
		}
		if (GetAsyncKeyState(VK_F7))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			fSlowMotionSpeed -= 0.1f;
		}
	}

}

void MK11Menu::UpdateMouse()
{
	if (bIsActive) return;

	GetCursorPos(&curMouse);
	mouseSpeedX = curMouse.x - orgMouse.x;
	mouseSpeedY = curMouse.y - orgMouse.y;


	if (bFocused)
	{
		if (TheMenu->bFreeCameraMovement)
		{
			float newVal = TheMenu->camRot.Yaw;
			newVal += mouseSpeedX / mouseSens;
			TheMenu->camRot.Yaw = newVal;


			float newValY = TheMenu->camRot.Pitch;

			if (bInvertMouseY) mouseSpeedY *= -1;

			newValY += mouseSpeedY / mouseSens;
			TheMenu->camRot.Pitch = newValY;
		}
	}

}

bool MK11Menu::GetActiveState()
{
	return bIsActive;
}

char * GetMK11HookVersion()
{
	char buffer[512];
	sprintf(buffer, "MK11Hook by ermaccer (%s)", MK11HOOK_VERSION);
	return buffer;
}

void PushNotification()
{
}
