#include "IPlugin.h"

IPlugin::IPlugin(void)
{
}

IPlugin::~IPlugin(void)
{
}

void IPlugin::emitSignal( const std::map<std::string,Variant>& sig )
{
	PluginManager::Instance()->emitSignal(sig);
}
