#pragma once

class eNotificationManager {
public:
	char szMessageBuffer[2048] = {};
	bool m_bIsNotificationActive;
	float m_fNotifAlpha;

	void Init();

	void Update();
	void UpdateAlpha();
	void Draw();
	void SetNotificationTime(int time);
	void PushNotification(const char* format, ...);
};

extern eNotificationManager* Notifications;