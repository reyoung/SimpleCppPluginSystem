#include "CommandPlugin.h"
#include <iostream>
#include "CommandPool.h"
using namespace std;
CommandPlugin::CommandPlugin(void)
{
}

CommandPlugin::~CommandPlugin(void)
{
}

bool CommandPlugin::initialize( int argc,char** argv )
{
	m_file = "Command.xml";
	return true;
}

void CommandPlugin::invoke( std::map<std::string,Variant>* inout)
{
	std::map<std::string,Variant>& retv = *inout;
	if (retv.find("CMDConfigFilename")!=retv.end())
	{
		retv["CMDConfigFilename"]=getCMDConfigFileName();
	}
}

void CommandPlugin::initialized()
{
	map<string,Variant> param;
	param["deserialize"] = m_file;
	PluginManager::Invoke("SerializationPlugin",&param);
	CommandPool::cmdset = new CommandPool();
	CommandPool::Instance()->m_data = param["deserialize"];
	CommandPool::Instance()->pack();
}

std::string CommandPlugin::getCMDConfigFileName() const
{
	return m_file;
}

DECLARE_PLUGIN(CommandPlugin);