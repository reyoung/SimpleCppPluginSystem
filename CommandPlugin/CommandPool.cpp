#include "CommandPool.h"
#include "KeyCommandSet.h"
using namespace std;
CommandPool* CommandPool::cmdset = 0;
CommandPool::CommandPool(void)
{
	atexit(atexit_callback);
}

CommandPool::~CommandPool(void)
{
}

CommandPool* CommandPool::Instance()
{
	return cmdset;
}

void CommandPool::atexit_callback()
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

void CommandPool::pack()
{
	if (m_data.getType()!=Variant::Map)
	{
		map<string,Variant> init;
		init["ExeCommand"]=map<string,Variant>();
		init["KeyCommand"]=map<string,Variant>();
		m_data = init;
	}
}

size_t CommandPool::typeCount() const
{
	return m_data.toMap().size();
}

KeyCommandSet CommandPool::getKeyCommandSet()
{
	KeyCommandSet set;
	set.data = &(*m_data.mapPtr())["KeyCommand"];
	return set;
}
