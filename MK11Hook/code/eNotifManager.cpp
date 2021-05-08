#include "eNotifManager.h"
#include <iostream>
#include <Windows.h>
#include "..\imgui\imgui.h"

eNotificationManager* Notifications = new eNotificationManager();

void eNotificationManager::Init()
{
	m_bIsNotificationActive = false;
	m_tTimer = GetTickCount64();
}

void eNotificationManager::Update()
{
	if (GetTickCount64() - m_tTimer <= m_nNotificationTime) return;
	m_tTimer = GetTickCount64();

	m_bIsNotificationActive = false;
}

void eNotificationManager::Draw()
{
	if (m_bIsNotificationActive)
	{
		ImGui::SetNextWindowPos(ImVec2(5, 10));
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x / 3, 0.0f));
		ImGui::Begin("setup", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs
			| ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing);
		ImGui::TextUnformatted(szMessageBuffer);
	}
}

void eNotificationManager::SetNotificationTime(int time)
{
	m_nNotificationTime = time;
}

void eNotificationManager::PushNotification(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(szMessageBuffer, format, args);
	va_end(args);
	m_bIsNotificationActive = true;
}
