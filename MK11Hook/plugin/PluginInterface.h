#pragma once
#include <Windows.h>
#include <vector>
#include <string>

#define PROJECT_NAME "MK11HOOK"

class PluginInfo {
private:
	HMODULE hModule;
	char szPluginName[128];
	char szPluginProject[128];
	char szPluginTabName[128];

public:
	const char* (*pluginGetPluginName)(void) = nullptr;
	const char* (*pluginGetPluginProject)(void) = nullptr;
	const char* (*pluginGetPluginTabName)(void) = nullptr;
	void (*pluginOnFrameTick)(void) = nullptr;
	void (*pluginOnInitialize)(void) = nullptr;
	void (*pluginOnFightStartup)(void) = nullptr;
	void (*pluginOnShutdown)(void) = nullptr;
	void (*pluginTabFunction)(void) = nullptr;


	const char* GetPluginName();
	const char* GetPluginTabName();
	const char* GetPluginProject();

	bool Load(wchar_t* path);
	void Unload();
};



class PluginInterface {
public:
	static std::vector<PluginInfo> plugins;

	static void LoadPlugins();
	static void UnloadPlugins();

	static void OnFrameTick();
	static void OnFightStartup();

	static void ProcessPluginTabs();

	static int  GetNumPlugins();
};