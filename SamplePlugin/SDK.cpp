#include "pch.h"
#include "SDK.h"
#include <Windows.h>
bool MK11HOOKSDK::ms_bIsInitialized = true;
bool (*MK11HOOKSDK::IsMenuActive)(void) = nullptr;
MKCharacter* (*MK11HOOKSDK::GetCharacterObject)(PLAYER_NUM) = nullptr;
PlayerInfo* (*MK11HOOKSDK::GetPlayerInfo)(PLAYER_NUM) = nullptr;
FGGameInfo* (*MK11HOOKSDK::GetGameInfo)(void) = nullptr;

bool (*MK11HOOKSDK::ImGui_Checkbox)(const char*, bool*) = nullptr;
void (*MK11HOOKSDK::ImGui_Text)(const char*) = nullptr;
bool (*MK11HOOKSDK::ImGui_Button)(const char*) = nullptr;
bool (*MK11HOOKSDK::ImGui_InputInt)(const char*, int*) = nullptr;
bool (*MK11HOOKSDK::ImGui_InputFloat)(const char*, float*) = nullptr;
bool (*MK11HOOKSDK::ImGui_InputText)(const char*, char*, size_t) = nullptr;
bool (*MK11HOOKSDK::ImGui_BeginCombo)(const char*, const char*) = nullptr;
void (*MK11HOOKSDK::ImGui_EndCombo)() = nullptr;
bool (*MK11HOOKSDK::ImGui_Selectable)(const char*, bool) = nullptr;
void (*MK11HOOKSDK::ImGui_SetItemDefaultFocus)() = nullptr;
void (*MK11HOOKSDK::ImGui_Separator)() = nullptr;
bool (*MK11HOOKSDK::ImGui_CollapsingHeader)(const char*) = nullptr;

void MK11HOOKSDK::Initialize()
{
	HMODULE hook = GetModuleHandle(L"mk11hook.asi");
	if (!hook)
	{
		ms_bIsInitialized = false;
		return;
	}

	IsMenuActive = (bool(*)())GetProcAddress(hook, "MK11HOOK_GetMenuActive");
	if (!IsMenuActive)
	{
		ms_bIsInitialized = false;
		return;
	}

	GetCharacterObject = (MKCharacter * (*)(PLAYER_NUM))GetProcAddress(hook, "MK11HOOK_GetCharacterObject");
	if (!GetCharacterObject)
	{
		ms_bIsInitialized = false;
		return;
	}

	GetPlayerInfo = (PlayerInfo * (*)(PLAYER_NUM))GetProcAddress(hook, "MK11HOOK_GetPlayerInfo");
	if (!GetPlayerInfo)
	{
		ms_bIsInitialized = false;
		return;
	}

	GetGameInfo = (FGGameInfo* (*)())GetProcAddress(hook, "MK11HOOK_GetGameInfo");
	if (!GetGameInfo)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_Checkbox = (bool(*)(const char*, bool*))GetProcAddress(hook, "MK11HOOK_ImGui_Checkbox");
	if (!ImGui_Checkbox)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_Text = (void(*)(const char*))GetProcAddress(hook, "MK11HOOK_ImGui_Text");
	if (!ImGui_Text)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_Button = (bool(*)(const char*))GetProcAddress(hook, "MK11HOOK_ImGui_Button");
	if (!ImGui_Button)
	{
		ms_bIsInitialized = false;
		return;
	}


	ImGui_InputInt = (bool(*)(const char*, int*))GetProcAddress(hook, "MK11HOOK_ImGui_InputInt");
	if (!ImGui_InputInt)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_InputFloat = (bool(*)(const char*, float*))GetProcAddress(hook, "MK11HOOK_ImGui_InputFloat");
	if (!ImGui_InputFloat)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_InputText = (bool(*)(const char*, char*, size_t))GetProcAddress(hook, "MK11HOOK_ImGui_InputText");
	if (!ImGui_InputText)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_BeginCombo = (bool(*)(const char*, const char*))GetProcAddress(hook, "MK11HOOK_ImGui_BeginCombo");
	if (!ImGui_BeginCombo)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_EndCombo = (void(*)())GetProcAddress(hook, "MK11HOOK_ImGui_EndCombo");
	if (!ImGui_EndCombo)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_Selectable = (bool(*)(const char*, bool))GetProcAddress(hook, "MK11HOOK_ImGui_Selectable");
	if (!ImGui_Selectable)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_SetItemDefaultFocus = (void(*)())GetProcAddress(hook, "MK11HOOK_ImGui_SetItemDefaultFocus");
	if (!ImGui_SetItemDefaultFocus)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_Separator = (void(*)())GetProcAddress(hook, "MK11HOOK_ImGui_Separator");
	if (!ImGui_Separator)
	{
		ms_bIsInitialized = false;
		return;
	}

	ImGui_CollapsingHeader = (bool(*)(const char*))GetProcAddress(hook, "MK11HOOK_ImGui_CollapsingHeader");
	if (!ImGui_CollapsingHeader)
	{
		ms_bIsInitialized = false;
		return;
	}
}

bool MK11HOOKSDK::IsOK()
{
	return ms_bIsInitialized;
}
