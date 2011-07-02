#include "KeyCommand.h"
#include <cassert>
#include "CommandPool.h"
#include "KeyCommandSet.h"
using namespace std;

KeyCommand::KeyCommand( const std::string& key,const Variant* va )
:m_key(key),m_param(va)
{

}

KeyCommand::~KeyCommand(void)
{
}


std::string KeyCommand::getKey() const
{
	return m_key;
}

std::map<std::string,Variant> KeyCommand::getParam() const
{
	assert(m_param->getType()==Variant::Map);
	CommandPool::Instance()->getKeyCommandSet().newCommand("$lastCMD",m_param->toMap());
	return m_param->toMap();
}

bool KeyCommand::isValid() const
{
	return m_param!=0;
}
