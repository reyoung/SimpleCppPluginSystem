#include "PluginManager.h"
using namespace  std;
PluginManager* PluginManager::m_manager=0;

PluginManager::PluginManager(void)
{
}

PluginManager::~PluginManager(void)
{
}

std::vector<PluginSpec*> PluginManager::getAllPluginSpec( const std::string& plugin_path )
{
	return std::vector<PluginSpec*> ();
}

void PluginManager::Initialize( int argc,char** argv,const std::string& plugin_path )
{
	m_manager = new PluginManager();
	vector<PluginSpec*> specs = m_manager->getAllPluginSpec(plugin_path);
}

void PluginManager::resolve( std::vector<PluginSpec* > * toResove )
{

}
