#pragma once
#include <vector>
#include <Windows.h>

enum eProjectID {
	PROJECT_UNKNOWN = -1,
	PROJECT_MK9HOOK,
	PROJECT_MKXHOOK,
	PROJECT_MK11HOOK,
	PROJECT_INJHOOK,
	PROJECT_I2HOOK
};


class ePlugin {
	char m_szPluginName[128];
	int  m_nProjectID;

	bool m_bIsValid;

	void (*m_pPluginFunc)();

	HMODULE	m_pHMod;

	ePlugin();
	void Shutdown();
};


class ePluginInterface {
public:
	static std::vector<ePlugin*> m_pPlugins;

	static void LoadPlugins();
	static void UnloadPlugins();
};