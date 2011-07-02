#include "CommandSet.h"
using namespace std;
CommandSet* CommandSet::cmdset = 0;
CommandSet::CommandSet(void)
{
	atexit(atexit_callback);
}

CommandSet::~CommandSet(void)
{
}

CommandSet* CommandSet::Instance()
{
	return cmdset;
}

void CommandSet::atexit_callback()
{
	map<string,Variant> param;
	map<string,Variant> param2;
	param["serialize"]=cmdset->m_data;
	param2["CMDConfigFilename"]=Variant();
	PluginManager::Invoke("CommandPlugin",&param2);
	param["serializePath"]=param2["CMDConfigFilename"];
	PluginManager::Invoke("SerializationPlugin",&param);
	if (cmdset)
	{
		delete cmdset;
	}
}

void CommandSet::pack()
{
	if (m_data.getType()!=Variant::Map)
	{
		map<string,Variant> init;
		init["ExeCommand"]=map<string,Variant>();
		init["KeyCommand"]=map<string,Variant>();
		m_data = init;
	}
}

size_t CommandSet::typeCount() const
{
	return m_data.toMap().size();
}
