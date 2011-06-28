#include "PluginSpec.h"
#include "PluginSpecLoader.h"
#include "PluginLoader.h"
#include <string>
using namespace std;
PluginSpec::~PluginSpec(void)
{
}

PluginSpec::PluginSpec( const std::string filename )
:m_enabled(false)
{
	PluginSpecLoader::Load(this,filename);
	m_filename = filename;
}

IPlugin* PluginSpec::getPlugin() const
{
	string path = m_filename;
	size_t pos=0;
	for (size_t i=0;i<path.size();++i)
	{
		if (path[i]=='\\')
		{
			pos = i;
		}
	}
	path.erase(path.begin()+pos,path.end());
	if (!path.empty())
	{
		path.push_back('\\');
	}
	path+=m_name;
	PluginLoader loader;
	loader.setFileName(path);
	loader.load();
	Castable* result = loader.newInstance();
	IPlugin* retv =  dynamic_cast<IPlugin* >(result);
	return retv;
}
