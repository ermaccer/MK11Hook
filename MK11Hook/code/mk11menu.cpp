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
#include "helper/eAbilityNames.h"
#include "helper/eKeyboardMan.h"
#include "..\eDirectX11Hook.h"
#include "GameInfo.h"
#include "Krypt.h"
#include "MKObject.h"
#include "helper/eMouse.h"
#include "AnimationTool.h"
#include "../utils/MemoryMgr.h"

using namespace Memory::VP;
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
	"Injustice 2",
	"Head Perspective"
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

const char* szBones[] = {
	"Head",
	"Hips",
	"Jaw",
	"LeftArm",
	"LeftEye",
	"LeftFoot",
	"LeftForeArm",
	"LeftHand",
	"LeftLeg",
	"Neck",
	"Neck1",
	"Reference",
	"RightArm",
	"RightEye",
	"RightFoot",
	"RightHand",
	"RightLeg",
	"Spine",
	"Spine1",
	"Spine2",
	"Spine3",
};


const char* szAI[] = {
	"AI_ATFatalitySoaker.mko",
	"AI_ButtonMasher.mko",
	"AI_DebugBrutality.mko",
	"AI_DebugInteractable.mko",
	"AI_DebugKrushingBlow.mko",
	"AI_DebugOnlineButtonMasher.mko",
	"AI_Dummy.mko",
	"AI_Fighter.mko",
	"AI_Flying.mko",
	"AI_Normal.mko",
	"AI_PlayerSelectArena.mko",
	//"AI_Practice.mko",
	"AI_SingleMove.mko",
	"AI_Test.mko",
	"AI_Tutorial.mko",
	"AI_Verifier.mko",
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
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szCurrentModifier, szModifierModes[0]);
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	sprintf(szCurrentKryptCharacter, szCharacters[0]);
	sprintf(szCurrentKryptCharacterClass, szCharClasses[0]);
	sprintf(szPlayer1TagAssistCharacter, szKryptCharacters[0]);
	sprintf(szPlayer2TagAssistCharacter, szKryptCharacters[0]);
	sprintf(szAbilityReferenceChararacter, szKryptCharacters[0]);
	sprintf(szPlayer1Bone, szBones[0]);
	sprintf(szPlayer2Bone, szBones[0]);
	sprintf(szPlayer1AI, szAI[0]);
	sprintf(szPlayer2AI, szAI[0]);
}

void MK11Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetMK11HookVersion(), &m_bIsActive, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SUBMENU_SETTINGS] = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Ability Reference"))
				m_bSubmenuActive[SUBMENU_ABILITY_REFERENCE] = true;
			if (ImGui::MenuItem("Script Reference"))
				m_bSubmenuActive[SUBMENU_SCRIPT] = true;
			ImGui::EndMenu();
		}
		if (!SettingsMgr->bDisableAnimationTool)
		{
			if (ImGui::BeginMenu("Posing"))
			{
				m_bSubmenuActive[SUBMENU_ANIMATIONTOOL] = true;
				ImGui::EndMenu();
			}
		}
	}
	ImGui::EndMenuBar();

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character"))
		{
			DrawCharacterTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage"))
		{
			DrawStageTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Modifiers"))
		{
			DrawModifiersTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player"))
		{
			DrawPlayerTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Speed"))
		{
			DrawSpeedTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera"))
		{
			DrawCameraTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			DrawCheatsTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Script"))
		{
			DrawScriptTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Krypt"))
		{
			DrawKryptTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("AI"))
		{
			DrawAITab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			DrawMiscTab();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();


	if (m_bSubmenuActive[SUBMENU_ABILITY_REFERENCE])
		DrawAbilityReference();

	if (m_bSubmenuActive[SUBMENU_SCRIPT])
		DrawScriptReference();

	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();

	if (m_bSubmenuActive[SUBMENU_ANIMATIONTOOL])
		DrawAnimationTool();

}

void MK11Menu::Process()
{
	m_bIsFocused = IsWindowFocused();
	UpdateControls();
	if (!SettingsMgr->bDisableAnimationTool)
	{
		if (AnimationTool::ms_bActive)
		{
			Nop(_addr(0x140E4EB90), 3);
		}
		else
		{
			Patch<char>(_addr(0x140E4EB90), 0x48);
			Patch<char>(_addr(0x140E4EB90) + 1, 0x8B);
			Patch<char>(_addr(0x140E4EB90) + 2, 0x08);
		}
		AnimationTool::ProcessPosing();

		if (!GetObj(PLAYER1))
		{
			Patch<char>(_addr(0x140E4EB90), 0x48);
			Patch<char>(_addr(0x140E4EB90) + 1, 0x8B);
			Patch<char>(_addr(0x140E4EB90) + 2, 0x08);
		}
	}

}

void MK11Menu::UpdateControls()
{

	if (GetAsyncKeyState(SettingsMgr->iHookMenuOpenKey))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		m_bIsActive ^= 1;
	}

	if (!m_bIsActive)
	{
		if (GetAsyncKeyState(SettingsMgr->iToggleCustomCamKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
				m_bCustomCameras ^= 1;
			else
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Custom cameras can only be activated in game!");
			}
		}
		if (GetAsyncKeyState(SettingsMgr->iResetStageInteractablesKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
				GetGameInfo()->ResetStageInteractables();
			else
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Stage objects can only be reset in game!");
			}
		}

		if (GetAsyncKeyState(SettingsMgr->iToggleSlowMoKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			m_bSlowMotion ^= 1;
		}

		if (GetAsyncKeyState(SettingsMgr->iToggleFreezeWorldKey))
		{
			if (m_bHookDispatch)
			{
				if (GetTickCount64() - timer <= 150) return;
				timer = GetTickCount64();
				m_bFreezeWorld ^= 1;
			}

		}
		ProcessScriptHotkeys();
	}

}

void MK11Menu::UpdateFreecam()
{
	if (TheMenu->m_bFreeCam)
	{
		if (TheCamera)
		{
			FVector fwd = TheCamera->GetMatrix().GetForward();
			FVector strafe = TheCamera->GetMatrix().GetRight();
			FVector up = TheCamera->GetMatrix().GetUp();

			// forward

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
				TheMenu->camPos += fwd * TheMenu->m_fFreeCameraSpeed * 1;


			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
				TheMenu->camPos += fwd * TheMenu->m_fFreeCameraSpeed * -1;

			// strafe

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
				TheMenu->camPos += strafe * TheMenu->m_fFreeCameraSpeed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
				TheMenu->camPos += strafe * TheMenu->m_fFreeCameraSpeed * -1;

			// up

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
				TheMenu->camPos += up * TheMenu->m_fFreeCameraSpeed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
				TheMenu->camPos += up * TheMenu->m_fFreeCameraSpeed * -1;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
				TheMenu->camRot.Yaw -= TheMenu->m_nFreeCameraRotationSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
				TheMenu->camRot.Yaw += TheMenu->m_nFreeCameraRotationSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
				TheMenu->camRot.Roll -= TheMenu->m_nFreeCameraRotationSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
				TheMenu->camRot.Roll += TheMenu->m_nFreeCameraRotationSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
				TheMenu->camRot.Pitch -= TheMenu->m_nFreeCameraRotationSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
				TheMenu->camRot.Pitch += TheMenu->m_nFreeCameraRotationSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
				TheMenu->camFov -= 1.0f;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
				TheMenu->camFov += 1.0f;

			// mouse
			{
				if (!TheMenu->m_bIsActive && TheMenu->m_bMouseControl)
				{
					TheMenu->camRot.Pitch += eMouse::GetDeltaY();
					TheMenu->camRot.Yaw += eMouse::GetDeltaX();
				}
			}
		}
	}

}

void MK11Menu::DrawCharacterTab()
{
	ImGui::TextWrapped("Select a method for replacing characters.\nSelect Screen - replaces character during selection, works with normal gamemodes.\n"
		"Fight Init - Replaces character during game loading, allows to change characters in story mode, attract, practice.");

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

}

void MK11Menu::DrawStageTab()
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

	if (ImGui::Button("Reset Stage Objects"))
		GetGameInfo()->ResetStageInteractables();
}

void MK11Menu::DrawModifiersTab()
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
				int val = (int)pow(2, i);
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
						int id = (int)pow(2, i);
						m_P1Abilities[i] = abilities & id;
					}
				}

			}
			ImGui::Separator();
			ImGui::Checkbox("Player 2 Custom Abilities", &m_bP2CustomAbilities);
			ImGui::Separator();

			for (int i = 0; i < sizeof(m_P2Abilities) / sizeof(m_P2Abilities[0]); i++)
			{
				int val = (int)pow(2, i);
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
						int id = (int)pow(2, i);
						m_P2Abilities[i] = abilities & id;
					}
				}

			}

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Skeleton"))
		{
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
			{
				ImGui::TextWrapped("Player 1");
				ImGui::Separator();
				if (ImGui::BeginCombo("Bone##p1", szPlayer1Bone))
				{
					for (int n = 0; n < IM_ARRAYSIZE(szBones); n++)
					{
						bool is_selected = (szPlayer1Bone == szBones[n]);
						if (ImGui::Selectable(szBones[n], is_selected))
							sprintf(szPlayer1Bone, szBones[n]);
						if (is_selected)
							ImGui::SetItemDefaultFocus();
				
					}
					ImGui::EndCombo();
				}
				static float boneSizeP1 = 0.0f;
				ImGui::InputFloat("Size##p1", &boneSizeP1);


				if (ImGui::Button("Change Bone", { -FLT_MIN, 0 }))
				{
					Notifications->SetNotificationTime(2500);
					Notifications->PushNotification("Changed %s", szPlayer1Bone);
					GetObj(PLAYER1)->SetBoneSize(szPlayer1Bone, boneSizeP1);
				}

				ImGui::TextWrapped("Player 2");
				ImGui::Separator();

				if (ImGui::BeginCombo("Bone##p2", szPlayer2Bone))
				{
					for (int n = 0; n < IM_ARRAYSIZE(szBones); n++)
					{
						bool is_selected = (szPlayer2Bone == szBones[n]);
						if (ImGui::Selectable(szBones[n], is_selected))
							sprintf(szPlayer2Bone, szBones[n]);
						if (is_selected)
							ImGui::SetItemDefaultFocus();

					}
					ImGui::EndCombo();
				}
				static float boneSizeP2 = 0.0f;
				ImGui::InputFloat("Size##p2", &boneSizeP2);


				if (ImGui::Button("Change Bone##p2", { -FLT_MIN, 0 }))
				{
					Notifications->SetNotificationTime(2500);
					Notifications->PushNotification("Changed %s", szPlayer1Bone);
					GetObj(PLAYER2)->SetBoneSize(szPlayer2Bone, boneSizeP2);
				}

				ImGui::Separator();
				ImGui::TextWrapped("Presets");
				if (ImGui::Button("Big Heads", { -FLT_MIN, 0 }))
				{
					Notifications->SetNotificationTime(2500);
					GetObj(PLAYER1)->SetBoneSize("Head", 1.5f);
					GetObj(PLAYER2)->SetBoneSize("Head", 1.5f);
					GetObj(PLAYER1)->SetBoneSize("Neck", 1.5f);
					GetObj(PLAYER2)->SetBoneSize("Neck", 1.5f);
				}
				if (ImGui::Button("Big Fists", { -FLT_MIN, 0 }))
				{
					GetObj(PLAYER1)->SetBoneSize("LeftHand", 3.0f);
					GetObj(PLAYER1)->SetBoneSize("RightHand", 3.0f);
					GetObj(PLAYER2)->SetBoneSize("LeftHand", 3.0f);
					GetObj(PLAYER2)->SetBoneSize("RightHand", 3.0f);
				}
				if (ImGui::Button("Googly Eyes", { -FLT_MIN, 0 }))
				{
					GetObj(PLAYER1)->SetBoneSize("LeftEye", 2.0f);
					GetObj(PLAYER1)->SetBoneSize("RightEye", 2.0f);
					GetObj(PLAYER2)->SetBoneSize("LeftEye", 2.0f);
					GetObj(PLAYER2)->SetBoneSize("RightEye", 2.0f);
				}
				if (ImGui::Button("Large Feet", { -FLT_MIN, 0 }))
				{
					GetObj(PLAYER1)->SetBoneSize("LeftFoot", 2.0f);
					GetObj(PLAYER1)->SetBoneSize("RightFoot", 2.0f);
					GetObj(PLAYER2)->SetBoneSize("LeftFoot", 2.0f);
					GetObj(PLAYER2)->SetBoneSize("RightFoot", 2.0f);
				}
				if (ImGui::Button("Reset All", { -FLT_MIN, 0 }))
				{
					for (int i = 0; i < sizeof(szBones) / sizeof(szBones[0]); i++)
					{
						GetObj(PLAYER1)->SetBoneSize(szBones[i], 1.0f);
						GetObj(PLAYER2)->SetBoneSize(szBones[i], 1.0f);
					}
				}
				ImGui::Separator();
			}
			else
				ImGui::TextWrapped("Skeleton options are only available in-game!");

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Custom Brutalities"))
		{
			ImGui::Checkbox("Custom Brutalities", &m_bBrutalityWatcher);
			ImGui::Separator();

			ImGui::InputFloat("Min. Health Required", &m_fBrutalityWatcherHealth);

			ImGui::Separator();
			ImGui::InputText("P1 Source", szPlayer1BrutalityCharacter, sizeof(szPlayer1BrutalityCharacter));
			ImGui::InputText("P1 Function", szPlayer1BrutalityFunc, sizeof(szPlayer1BrutalityFunc));
			ImGui::Separator();

			ImGui::Separator();
			ImGui::InputText("P2 Source", szPlayer2BrutalityCharacter, sizeof(szPlayer2BrutalityCharacter));
			ImGui::InputText("P2 Function", szPlayer2BrutalityFunc, sizeof(szPlayer2BrutalityFunc));
			ImGui::Separator();

			if (GetObj(PLAYER1) && GetObj(PLAYER2))
				ImGui::Text("P1 Life: %f P2 Life: %f\n", GetObj(PLAYER1)->GetLife(), GetObj(PLAYER2)->GetLife());
			

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

void MK11Menu::DrawPlayerTab()
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
		ImGui::Text("Position");
		ImGui::SameLine(); ShowHelpMarker("Read only!");
		GetCharacterPosition(&plrPos, PLAYER1);
		ImGui::InputFloat3("X | Y | Z", &plrPos.X);
		GetCharacterPosition(&plrPos2, PLAYER2);
		ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
	
	}
	else
		ImGui::Text("Player options are only available in-game!");

}

void MK11Menu::DrawSpeedTab()
{
	ImGui::Text("Gamespeed Control");
	ImGui::InputFloat("", &m_fSlowMotionSpeed, 0.1f);

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
}

void MK11Menu::DrawCameraTab()
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
		ImGui::Checkbox("Mouse Control", &m_bMouseControl);
	}




	ImGui::Separator();
	ImGui::Checkbox("Force Camera To Move", &m_bForceCameraUpdate);
	ImGui::SameLine(); ShowHelpMarker("Check this option if you can't move camera anymore in win poses and some cinematics.");

	ImGui::Separator();

	ImGui::Checkbox("Custom Cameras", &m_bCustomCameras);

	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{

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
		}
		else if (m_nCurrentCustomCamera == CAMERA_3RDPERSON)
		{
			ImGui::InputFloat("TPP Camera Offset", &m_fAdjustCustomCameraThirdPersonY);
			ImGui::InputFloat("TPP Up/Down Offset", &m_fAdjustCustomCameraThirdPersonZ);
			ImGui::InputFloat("TPP Left/Right Offset", &m_fAdjustCustomCameraThirdPersonX);
		}
		else if (m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING)
		{
			ImGui::InputFloat("Up/Down Angle Offset", &m_fAdjustCustomHeadCameraY);
			ImGui::InputFloat("Up/Down Offset", &m_fAdjustCustomHeadCameraZ);
			ImGui::InputFloat("Left/Right Offset", &m_fAdjustCustomHeadCameraX);

			ImGui::Checkbox("Don't Flip Camera", &m_bDontFlipCamera);
			ImGui::SameLine(); ShowHelpMarker("Use this option for head tracked cinematics.");
			ImGui::Checkbox("Use Player Two As Source", &m_bUsePlayerTwoAsTracker);

			ImGui::TextWrapped("Recommended to set FOV value to at least 110 to make this mode look right!");
		}
	}
	else
		ImGui::Text("Custom cameras will appear once in-game!");

}

void MK11Menu::DrawCheatsTab()
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

	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{
		ImGui::Text("Easy Krushing Blows\n");
		ImGui::NextColumn();
		if (ImGui::Checkbox("P1##kbs", &m_bEasyKBsP1))
		{
			if (m_bEasyKBsP1)
				GetObj(PLAYER1)->SetEasyKrushingBlows(true);
			else
				GetObj(PLAYER1)->SetEasyKrushingBlows(false);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("P2##kbs", &m_bEasyKBsP2))
		{
			if (m_bEasyKBsP2)
				GetObj(PLAYER2)->SetEasyKrushingBlows(true);
			else
				GetObj(PLAYER2)->SetEasyKrushingBlows(false);
		}
		ImGui::NextColumn();

		ImGui::Text("Infinite Krushing Blows\n");
		ImGui::NextColumn();
		if (ImGui::Checkbox("P1##ikbs", &m_bInfKBsP1))
		{
			if (m_bInfKBsP1)
				GetObj(PLAYER1)->SetInfiniteKrushingBlows(true);
			else
				GetObj(PLAYER1)->SetInfiniteKrushingBlows(false);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("P2##ikbs", &m_bInfKBsP2))
		{
			if (m_bInfKBsP2)
				GetObj(PLAYER2)->SetInfiniteKrushingBlows(true);
			else
				GetObj(PLAYER2)->SetInfiniteKrushingBlows(false);
		}
		ImGui::NextColumn();

		ImGui::Text("Quick Uppercut Recovery\n");
		ImGui::NextColumn();
		if (ImGui::Checkbox("P1##ups", &m_bFastUppercutsP1))
		{
			if (m_bFastUppercutsP1)
				GetObj(PLAYER1)->SetFastUppercutRecovery(true);
			else
				GetObj(PLAYER1)->SetFastUppercutRecovery(false);
		}
		ImGui::SameLine();
		if (ImGui::Checkbox("P2##ups", &m_bFastUppercutsP2))
		{
			if (m_bFastUppercutsP2)
				GetObj(PLAYER2)->SetFastUppercutRecovery(true);
			else
				GetObj(PLAYER2)->SetFastUppercutRecovery(false);
		}
		ImGui::NextColumn();
	}




	ImGui::Columns(1);
	ImGui::Separator();

}

void MK11Menu::DrawKryptTab()
{
	ImGui::TextWrapped("Make sure you match the character class! It's trial & error if a character doesn't work.");
	ImGui::TextWrapped("Normal characters use Base class, while Sektor/Cyrax use NPCs. Some might not work at all.");
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

}

void MK11Menu::DrawMiscTab()
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

	ImGui::Checkbox("Disable Head Tracking", &m_bDisableHeadTracking);
	ImGui::SameLine();
	ShowHelpMarker("Disables P1 head looking at P2. Automatically enabled with 'Head Perspective' custom camera.");

	ImGui::Checkbox("Disable Combo Scaling", &m_bDisableComboScaling);
}

void MK11Menu::DrawScriptTab()
{
	ImGui::RadioButton("On Player1", &m_nScriptExecuteType, SCRIPT_P1); ImGui::SameLine();
	ImGui::RadioButton("On Player2", &m_nScriptExecuteType, SCRIPT_P2);

	static char szScriptSource[256] = {};
	ImGui::InputText("Script Source", szScriptSource, sizeof(szScriptSource));
	ImGui::Separator();

	m_pScript = GetScript(szScriptSource);
	if (m_pScript)
	{
		static int functionIndex = 0;
		static char szFunction[256] = {};

		static int hash = 0;
		ImGui::TextWrapped("Functions with params are not supported!");

		ImGui::InputText("Function Name", szFunction, sizeof(szFunction));
		ImGui::InputInt("Function Index", &functionIndex,1,100, ImGuiInputTextFlags_ReadOnly); 
		ImGui::SameLine(); ShowHelpMarker("Read only.");

		static eScriptKeyBind bind;
		if (ImGui::Button("Add Hotkey"))
		{
			m_nHash = HashString(szFunction);
			functionIndex = m_pScript->GetFunctionID(m_nHash);

			bind.functionHash = m_nHash;
			sprintf(bind.scriptName,"%s", szScriptSource);
			bind.type = (eScriptExecuteType)m_nScriptExecuteType;
			
			m_bPressingKey = true;
		}

		if (m_bPressingKey)
		{
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				bind.key = result;
				m_vKeyBinds.push_back(bind);
				m_bPressingKey = false;
			}

		}
		ImGui::SameLine();
		if (ImGui::Button("Run"))
		{
			m_nHash = HashString(szFunction);
			functionIndex = m_pScript->GetFunctionID(m_nHash);
			
			RunLastScript();
		}

#ifdef _DEBUG
		static char szScriptVariable[256] = {};
		static int64 test;
		ImGui::InputText("Script Variable", szScriptVariable, sizeof(szScriptVariable));
		if (ImGui::Button("Get Var Ptr"))
		{
			test = GetScriptVar(m_pScript, szScriptVariable);
			std::cout << std::hex << test << std::endl;
		}
#endif
	}
	else
	{
		if (strlen(szScriptSource) > 0)
		ImGui::TextWrapped("%s not available!", szScriptSource);
	}
		

	ImGui::Separator();
	ImGui::TextWrapped("Registered hotkeys:");
	for (unsigned int i = 0; i < m_vKeyBinds.size(); i++)
	{
		ImGui::TextWrapped("%s - Run [0x%X] from %s", eKeyboardMan::KeyToString(m_vKeyBinds[i].key), m_vKeyBinds[i].functionHash, m_vKeyBinds[i].scriptName);
	}

	if (ImGui::Button("Clear All"))
		m_vKeyBinds.clear();

}

void MK11Menu::DrawAITab()
{
	ImGui::Checkbox("Change Player 1 AI", &m_bAIDroneModifierP1);

	if (ImGui::BeginCombo("Player 1 AI", szPlayer1AI))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szAI); n++)
		{
			bool is_selected = (szPlayer1AI == szAI[n]);
			if (ImGui::Selectable(szAI[n], is_selected))
				sprintf(szPlayer1AI, szAI[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}

	ImGui::Separator();
	ImGui::Checkbox("Change Player 2 AI", &m_bAIDroneModifierP2);

	if (ImGui::BeginCombo("Player 2 AI", szPlayer2AI))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szAI); n++)
		{
			bool is_selected = (szPlayer2AI == szAI[n]);
			if (ImGui::Selectable(szAI[n], is_selected))
				sprintf(szPlayer2AI, szAI[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}
	ImGui::Separator();

}

void MK11Menu::DrawSettings()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 54 * ImGui::GetFontSize(), 54 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI",
		"Keys",
		"Mouse"
	};

	enum eSettings {
		MENU,
		INI,
		KEYS,
		MOUSE
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to mk11hook_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat("", &SettingsMgr->fMenuScale);
		ImGui::PopItemWidth();
		break;
	case INI:            
		ImGui::TextWrapped("These settings control MK11Hook.ini options. Any changes require game restart to take effect.");
		ImGui::Checkbox("Debug Console", &SettingsMgr->bEnableConsoleWindow);
		ImGui::Checkbox("Gamepad Support", &SettingsMgr->bEnableGamepadSupport);
		break;
	case KEYS:
		if (m_bPressingKey)
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");

		if (ImGui::Button("Reset Keys", { -FLT_MIN, 0 }))
		{
			SettingsMgr->ResetKeys();
			Notifications->SetNotificationTime(2500);
			Notifications->PushNotification("Keys reset! Remember to save.");

		}
		ImGui::Separator();
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iHookMenuOpenKey, "Open/Close Menu", "menu");
		KeyBind(&SettingsMgr->iToggleSlowMoKey, "Toggle Gamespeed/Slow Motion", "slomo");
		KeyBind(&SettingsMgr->iToggleFreezeWorldKey, "Freeze World", "freeze");
		ImGui::Separator();
		ImGui::LabelText("","Camera");
		ImGui::Separator();

		KeyBind(&SettingsMgr->iFreeCameraKeyFOVPlus, "FOV+", "fov_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyFOVMinus, "FOV-", "fov_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyYawPlus, "Yaw+", "ya_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYawMinus, "Yaw-", "ya_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchPlus, "Pitch+", "pi_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchMinus, "Pitch-", "pi_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollPlus, "Roll+", "r_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollMinus, "Roll-", "r_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyXPlus, "X+", "x_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyXMinus, "X-", "x_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYPlus, "Y+", "y_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYMinus, "Y-", "y_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyZPlus, "Z+", "z_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyZMinus, "Z-", "z_minus");


		ImGui::Separator();
		ImGui::LabelText("", "Misc");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iToggleCustomCamKey, "Toggle Custom Cameras", "ccam");
		KeyBind(&SettingsMgr->iResetStageInteractablesKey, "Reset Stage Objects", "r_stage");
		ImGui::Separator();

		if (m_bPressingKey)
		{
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				*m_pCurrentVarToChange = result;
				m_bPressingKey = false;
			}

		}
		break;
	case MOUSE:
		ImGui::TextWrapped("All user settings are saved to mk11hook_user.ini.");
		ImGui::Text("Sensitivity");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::SliderInt("", &SettingsMgr->mouse.sens, 1, 50);
		ImGui::PopItemWidth();
		ImGui::Checkbox("Invert X", &SettingsMgr->mouse.invert_x);
		ImGui::Checkbox("Invert Y", &SettingsMgr->mouse.invert_y);
		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Settings saved to MK11Hook.ini and mk11hook_user.ini!");
		eDirectX11Hook::ms_bShouldReloadFonts = true;
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

void MK11Menu::DrawAbilityReference()
{
	ImGui::Begin("Ability Reference", &m_bSubmenuActive[SUBMENU_ABILITY_REFERENCE]);

	static int charID = 0;
	ImGui::BeginChild("##chars", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(szKryptCharacters); n++)
	{
		bool is_selected = (charID == n);
		if (ImGui::Selectable(szKryptCharacters[n], is_selected))
			charID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();

	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##movelist", { 0, -ImGui::GetFrameHeightWithSpacing() });

	eAbilityNameEntry ab;
	ab = eAbiltityNames::Get(szKryptCharacters[charID]);

	ImGui::LabelText("ID", "Name");
	ImGui::Separator();

	for (unsigned int i = 0; i < TOTAL_ABILITIES; i++)
	{
		if (strlen(ab.abNames[i]) > 0)
		{
			sprintf(textBuffer, "%d", i + 1);
			ImGui::LabelText(textBuffer, ab.abNames[i]);
		}

	}

	ImGui::EndChild();
	ImGui::End();
}

void MK11Menu::DrawScriptReference()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 54 * ImGui::GetFontSize(), 54 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Script Reference", &m_bSubmenuActive[SUBMENU_SCRIPT]);

	static int secID = 0;
	static const char* scriptSections[] = {
		"General",
		"Usage",
	};

	enum eScriptRef {
		GEN,
		USG,
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(scriptSections); n++)
	{
		bool is_selected = (secID == n);
		if (ImGui::Selectable(scriptSections[n], is_selected))
			secID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (secID)
	{
	case GEN:
		ImGui::TextWrapped("You can find script functions in the MKScript folder. Open .mko file of interest with notepad or"
			" any hex editor. To find functions that can be executed look for strings starting with 'Rx', 'pFunc','p'.");
		break;
	case USG:
		ImGui::BulletText("On Player1 - selected function will execute on Player 1 object.\nUse with character scripts or FightEngine");
		ImGui::BulletText("On Player2 - selected function will execute on Player 2 object.\nUse with character scripts or FightEngine");

		ImGui::TextWrapped("Some common player functions:");
		ImGui::BulletText("BrutalityVictory1");
		ImGui::BulletText("BrutalityVictory2");
		ImGui::BulletText("EndOfRound_Winner_Taunt_1/2/3/4/5");
		ImGui::BulletText("RxMotherBug (CHAR_DVorah)");
		ImGui::BulletText("RxT800 (CHAR_Terminator)");

		ImGui::TextWrapped("Some common FightEngine.mko functions:");
		ImGui::BulletText("RxBrutalitySharedUppercut");
		ImGui::BulletText("RxIceBall");
		break;
	default:
		break;
	}

	ImGui::EndChild();

	ImGui::End();
}

void MK11Menu::DrawAnimationTool()
{
	AnimationTool::Draw();
}

void MK11Menu::DrawKeyBind(char* name, int* var)
{
	ImGui::SameLine();

	static char butName[256] = {};
	sprintf(butName, "%s##key%s", eKeyboardMan::KeyToString(*var), name);
	if (ImGui::Button(butName))
	{
		m_bPressingKey = true;
		m_pCurrentVarToChange = var;
	}

}

#ifdef _DEBUG
void MK11Menu::DrawDebug()
{
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.95f);
	ImGui::SetNextWindowPos(ImVec2(10, 5));
	ImGui::Begin("devtext", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoInputs |ImGuiWindowFlags_NoSavedSettings |ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::PopStyleVar(1);
	ImGui::Text("MK11Hook %s Debug (%.2f FPS)", MK11HOOK_VERSION, ImGui::GetIO().Framerate);
	ImGui::Text("");
	ImGui::Text("Player 1 Object: 0x%p Info: 0x%p",GetObj(PLAYER1), GetInfo(PLAYER1));
	ImGui::Text("Player 2 Object: 0x%p Info: 0x%p", GetObj(PLAYER2), GetInfo(PLAYER2));
	if (GetInfo(PLAYER1)->pad)
	ImGui::Text("P1: %s Hits: %d %d Button: %d", GetCharacterName(PLAYER1), GetInfo(PLAYER1)->GetHits().hits, GetInfo(PLAYER1)->GetHits().airHits, GetInfo(PLAYER1)->pad->buttons.id);
	if (GetInfo(PLAYER2)->pad)
	ImGui::Text("P2: %s Hits: %d %d Button: %d", GetCharacterName(PLAYER2), GetInfo(PLAYER2)->GetHits().hits, GetInfo(PLAYER2)->GetHits().airHits, GetInfo(PLAYER2)->pad->buttons.id);
	ImGui::End();
}
#endif

void MK11Menu::KeyBind(int* var, char * bindName, char * name)
{
	ImGui::LabelText("", bindName);
	DrawKeyBind(name, var);
}

bool MK11Menu::GetActiveState()
{
	return m_bIsActive;
}

void MK11Menu::RunLastScript()
{
	if (m_pScript->GetFunctionID(m_nHash))
	{
		switch (m_nScriptExecuteType)
		{
		case SCRIPT_P1:
			GetObj(PLAYER1)->ExecuteScript(m_pScript, m_nHash);
			break;
		case SCRIPT_P2:
			GetObj(PLAYER2)->ExecuteScript(m_pScript, m_nHash);
			break;
		default:
			break;
		}
	}
	else
	{
		Notifications->SetNotificationTime(3500);
		Notifications->PushNotification("Function %x does not exist!", m_nHash);
	}
}

void MK11Menu::RunBrutalityWatcher()
{
	MKCharacter* p1 = GetObj(PLAYER1);
	MKCharacter* p2 = GetObj(PLAYER2);

	MKScript* genericCommands = GetScript("GenericCommands.mko");

	if (!genericCommands)
		return;

	if (p2)
	{
		float life = p2->GetLife();

		if (life <= m_fBrutalityWatcherHealth)
		{
			if (!m_bBrutalityDoneP1)
			{
				MKScript* script = GetScript(szPlayer1BrutalityCharacter);
				if (script)
				{
					p2->ExecuteScript(genericCommands, HashString("ForceBackToStance"));
					p2->ExecuteScript(script, HashString(szPlayer1BrutalityFunc));
				}
				
				m_bBrutalityDoneP1 = true;
			}

		}
		else
		{
			m_bBrutalityDoneP1 = false;
		}
	}

	if (p1)
	{
		float life = p1->GetLife();

		if (life <= m_fBrutalityWatcherHealth)
		{
			if (!m_bBrutalityDoneP2)
			{
				MKScript* script = GetScript(szPlayer2BrutalityCharacter);
				if (script)
				{
					p1->ExecuteScript(genericCommands, HashString("ForceBackToStance"));
					p1->ExecuteScript(script, HashString(szPlayer2BrutalityFunc));
				}
				m_bBrutalityDoneP2 = true;
			}
		}
		else
		{
			m_bBrutalityDoneP2 = false;
		}
	}
}

void MK11Menu::ProcessScriptHotkeys()
{
	for (int i = 0; i < m_vKeyBinds.size(); i++)
	{
		if (GetAsyncKeyState(m_vKeyBinds[i].key) & 0x1)
		{
			MKScript* script = GetScript(m_vKeyBinds[i].scriptName);
			if (script->GetFunctionID(m_vKeyBinds[i].functionHash))
			{
				switch (m_vKeyBinds[i].type)
				{
				case SCRIPT_P1:
					GetObj(PLAYER1)->ExecuteScript(script, m_vKeyBinds[i].functionHash);
					break;
				case SCRIPT_P2:
					GetObj(PLAYER2)->ExecuteScript(script, m_vKeyBinds[i].functionHash);
					break;
				default:
					break;
				}
			}
			else
			{
				Notifications->SetNotificationTime(3500);
				Notifications->PushNotification("Function %x does not exist!", m_vKeyBinds[i].functionHash);
			}
		}
	}
}

char * GetMK11HookVersion()
{
	static char buffer[512] = {};
	sprintf(buffer, "MK11Hook by ermaccer (%s)", MK11HOOK_VERSION);
	return buffer;
}

bool IsWindowFocused()
{
	if (eDirectX11Hook::ms_bInit)
		return GetForegroundWindow() == eDirectX11Hook::ms_hWindow;

	return false;
}
