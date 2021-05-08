#pragma once
#include "mk10utils.h"

class eNotificationManager {
public:
	char szMessageBuffer[2048] = {};
	bool m_bIsNotificationActive;
	int  m_nNotificationTime;
	int64 m_tTimer;


	void Init();

	void Update();
	void Draw();
	void SetNotificationTime(int time);
	void PushNotification(const char* format, ...);
};

extern eNotificationManager* Notifications;