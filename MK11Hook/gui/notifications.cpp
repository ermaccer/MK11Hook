#include "notifications.h"
#include <iostream>
#include <Windows.h>
#include "imgui\imgui.h"
#include "gui_impl.h"
#include "dx11hook.h"
#include "..\plugin\Settings.h"

eNotificationManager* Notifications = new eNotificationManager();

void eNotificationManager::Init()
{
	m_bIsNotificationActive = false;
	m_fNotifAlpha = 1.0;
}

void eNotificationManager::Update()
{
	UpdateAlpha();
}

void eNotificationManager::UpdateAlpha()
{
	float delta = 1.0f / 60.0f;

	if (GUIImplementation::ms_bInit)
		delta = 1.0f / ImGui::GetIO().Framerate;


	float alphaSpeed = 1.8f;

	m_fNotifAlpha = max(m_fNotifAlpha - delta * alphaSpeed, 0.0f);


	if (m_fNotifAlpha <= 0)
		m_bIsNotificationActive = false;

}

void eNotificationManager::Draw()
{
	if (m_bIsNotificationActive)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, m_fNotifAlpha);
		ImGui::SetNextWindowPos(ImVec2(5, 10));
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x - 15.0f, 0.0f));
		ImGui::Begin("notif", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs
			| ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing);
		ImGui::TextUnformatted(szMessageBuffer);
		ImGui::End();
		ImGui::PopStyleVar(1);
	}
}

void eNotificationManager::SetNotificationTime(int time)
{
	m_fNotifAlpha = time / 1000.0f;
}

void eNotificationManager::PushNotification(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(szMessageBuffer, format, args);
	va_end(args);
	m_bIsNotificationActive = true;
	//if (SettingsMgr->bEnableConsoleWindow)
	//{
	//	printf("Notification | %s\n", szMessageBuffer);
	//}
}
