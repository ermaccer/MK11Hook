#include "ePluginInterface.h"
#include <iostream>

ePlugin::ePlugin()
{
	sprintf(m_szPluginName, "Unknown");
	m_nProjectID = PROJECT_UNKNOWN;
	m_bIsValid = false;
	m_pPluginFunc = nullptr;
	m_pHMod = 0;
}

void ePlugin::Shutdown()
{
	m_pPluginFunc = nullptr;
	m_bIsValid = false;
	FreeModule(m_pHMod);
}

void ePluginInterface::LoadPlugins()
{
}

void ePluginInterface::UnloadPlugins()
{
}
