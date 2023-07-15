#include "API.h"
#include "Menu.h"
#include "..\gui\imgui\imgui.h"
#include "..\mk\PlayerInfo.h"

bool MK11HOOK_GetMenuActive()
{
    return TheMenu->m_bIsActive;
}

MKCharacter* MK11HOOK_GetCharacterObject(PLAYER_NUM id)
{
    return GetObj(id);
}

PlayerInfo* MK11HOOK_GetPlayerInfo(PLAYER_NUM id)
{
    return GetInfo(id);
}

FGGameInfo* MK11HOOK_GetGameInfo()
{
    return GetGameInfo();
}

void MK11HOOK_ImGui_Text(const char* text)
{
    ImGui::TextWrapped(text);
}

bool MK11HOOK_ImGui_Checkbox(const char* text, bool* value)
{
    return ImGui::Checkbox(text, value);
}

bool MK11HOOK_ImGui_Button(const char* text)
{
    return ImGui::Button(text);
}

bool MK11HOOK_ImGui_InputInt(const char* text, int* value)
{
    return ImGui::InputInt(text, value);
}

bool MK11HOOK_ImGui_InputFloat(const char* text, float* value)
{
    return ImGui::InputFloat(text, value);
}

bool MK11HOOK_ImGui_InputText(const char* label, char* buff, size_t size)
{
    return ImGui::InputText(label, buff, size);
}

bool MK11HOOK_ImGui_BeginCombo(const char* label, const char* previewValue)
{
    return ImGui::BeginCombo(label, previewValue);
}

void MK11HOOK_ImGui_EndCombo()
{
    ImGui::EndCombo();
}

bool MK11HOOK_ImGui_Selectable(const char* label, bool selected)
{
    return ImGui::Selectable(label, selected);
}

void MK11HOOK_ImGui_SetItemDefaultFocus()
{
    ImGui::SetItemDefaultFocus();
}

void MK11HOOK_ImGui_Separator()
{
    ImGui::Separator();
}

bool MK11HOOK_ImGui_CollapsingHeader(const char* label)
{
    return ImGui::CollapsingHeader(label);
}

