#include "PluginInterface.h"
#include "..\gui\log.h"
#include "..\gui\imgui\imgui.h"

std::vector<PluginInfo> PluginInterface::plugins;

void PluginInterface::LoadPlugins()
{
	plugins.clear();

	WIN32_FIND_DATAW ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	hFind = FindFirstFileW(L"Retail\\*.ehp", &ffd);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		return;
	}

	if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		PluginInfo plugin;
		ZeroMemory(&plugin, sizeof(PluginInfo));
		if (plugin.Load(ffd.cFileName))
			plugins.push_back(plugin);
	}

	while (FindNextFileW(hFind, &ffd) != 0)
	{
		if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			PluginInfo plugin;
			ZeroMemory(&plugin, sizeof(PluginInfo));
			if (plugin.Load(ffd.cFileName))
				plugins.push_back(plugin);
		}
	}
}

void PluginInterface::UnloadPlugins()
{
	for (unsigned int i = 0; i < plugins.size(); i++)
	{
		plugins[i].Unload();
	}
}

void PluginInterface::OnFrameTick()
{
	for (unsigned int i = 0; i < plugins.size(); i++)
	{
		plugins[i].pluginOnFrameTick();
	}
}

void PluginInterface::OnFightStartup()
{
	for (unsigned int i = 0; i < plugins.size(); i++)
	{
		plugins[i].pluginOnFightStartup();
	}
}

void PluginInterface::ProcessPluginTabs()
{
	if (plugins.size() > 0)
	{
		if (ImGui::BeginTabItem("Plugins"))
		{
			if (ImGui::BeginTabBar("##plugintabs"))
			{
				for (unsigned int i = 0; i < plugins.size(); i++)
				{	
					if (plugins[i].pluginTabFunction)
					{
						static char labelName[128] = {};
						sprintf_s(labelName, "%s##%d", plugins[i].GetPluginTabName(), i);
						if (ImGui::BeginTabItem(labelName))
						{
							plugins[i].pluginTabFunction();
							ImGui::EndTabItem();
						}
					}

				}
				
				ImGui::EndTabBar();
			}
			ImGui::EndTabItem();
		}
	}

}

int PluginInterface::GetNumPlugins()
{
	return (int)plugins.size();
}


const char* PluginInfo::GetPluginName()
{
	return szPluginName;
}

const char* PluginInfo::GetPluginTabName()
{
	return szPluginTabName;
}

const char* PluginInfo::GetPluginProject()
{
	return szPluginProject;
}

bool PluginInfo::Load(wchar_t* path)
{
	hModule = LoadLibraryW(path);

	if (hModule)
	{
		pluginGetPluginName = (const char*(*)())GetProcAddress(hModule, "GetPluginName");
		if (!pluginGetPluginName)
		{
			eLog::Message(__FUNCTION__, "ERROR: Could not find GetPluginName for %ws!", path);
			return false;
		}
		pluginGetPluginProject = (const char* (*)())GetProcAddress(hModule, "GetPluginProject");
		if (!pluginGetPluginProject)
		{
			eLog::Message(__FUNCTION__, "ERROR: Could not find GetPluginProject for %ws!", path);
			return false;
		}
		pluginGetPluginTabName = (const char* (*)())GetProcAddress(hModule, "GetPluginTabName");
		if (!pluginGetPluginTabName)
		{
			eLog::Message(__FUNCTION__, "ERROR: Could not find GetPluginTabName for %ws!", path);
			return false;
		}
		pluginOnFrameTick = (void(*)())GetProcAddress(hModule, "OnFrameTick");
		if (!pluginOnFrameTick)
		{
			eLog::Message(__FUNCTION__, "ERROR: Could not find OnFrameTick for %ws!", path);
			return false;
		}
		pluginOnFightStartup = (void(*)())GetProcAddress(hModule, "OnFightStartup");
		if (!pluginOnFightStartup)
		{
			eLog::Message(__FUNCTION__, "ERROR: Could not find OnFightStartup for %ws!", path);
			return false;
		}
		pluginOnInitialize = (void(*)())GetProcAddress(hModule, "OnInitialize");
		if (!pluginOnInitialize)
		{
			eLog::Message(__FUNCTION__, "ERROR: Could not find OnInitialize for %ws!", path);
			return false;
		}
		pluginOnShutdown = (void(*)())GetProcAddress(hModule, "OnShutdown");
		if (!pluginOnShutdown)
		{
			eLog::Message(__FUNCTION__, "ERROR: Could not find OnShutdown for %ws!", path);
			return false;
		}
		pluginTabFunction = (void(*)())GetProcAddress(hModule, "TabFunction");

		sprintf_s(szPluginName, pluginGetPluginName());
		sprintf_s(szPluginProject, pluginGetPluginProject());
		sprintf_s(szPluginTabName, pluginGetPluginTabName());


		if (!(strcmp(szPluginProject, PROJECT_NAME) == 0))
		{
			eLog::Message(__FUNCTION__, "ERROR: Plugin %ws is not built for this project!", path);
			return false;
		}

		eLog::Message(__FUNCTION__, "INFO: Loaded %s (%ws)!", szPluginName, path);

		pluginOnInitialize();

		return true;
	}

	return false;
}

void PluginInfo::Unload()
{
	if (pluginOnShutdown)
		pluginOnShutdown();

	if (hModule)
	{
		FreeLibrary(hModule);
		hModule = 0;
	}
}
