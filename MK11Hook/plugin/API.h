#pragma once
#include "..\mk\Engine.h"

extern "C"  {
	__declspec(dllexport) bool MK11HOOK_GetMenuActive();
	__declspec(dllexport) MKCharacter* MK11HOOK_GetCharacterObject(PLAYER_NUM id);
	__declspec(dllexport) PlayerInfo* MK11HOOK_GetPlayerInfo(PLAYER_NUM id);
	__declspec(dllexport) FGGameInfo* MK11HOOK_GetGameInfo();
	__declspec(dllexport) void MK11HOOK_ImGui_Text(const char* text);
	__declspec(dllexport) bool MK11HOOK_ImGui_Checkbox(const char* text, bool* value);
	__declspec(dllexport) bool MK11HOOK_ImGui_Button(const char* text);
	__declspec(dllexport) bool MK11HOOK_ImGui_InputInt(const char* text, int* value);
	__declspec(dllexport) bool MK11HOOK_ImGui_InputFloat(const char* text, float* value);
	__declspec(dllexport) bool MK11HOOK_ImGui_InputText(const char* label, char* buff, size_t size);
	__declspec(dllexport) bool MK11HOOK_ImGui_BeginCombo(const char* label, const char* previewValue);
	__declspec(dllexport) void MK11HOOK_ImGui_EndCombo();
	__declspec(dllexport) bool MK11HOOK_ImGui_Selectable(const char* label, bool selected);
	__declspec(dllexport) void MK11HOOK_ImGui_SetItemDefaultFocus();
	__declspec(dllexport) void MK11HOOK_ImGui_Separator();
	__declspec(dllexport) bool MK11HOOK_ImGui_CollapsingHeader(const char* label);
}