#include "PluginSpec.h"
#include "PluginSpecLoader.h"
PluginSpec::~PluginSpec(void)
{
}

PluginSpec::PluginSpec( const std::string filename )
:m_enabled(false)
{
	PluginSpecLoader::Load(this,filename);
}
