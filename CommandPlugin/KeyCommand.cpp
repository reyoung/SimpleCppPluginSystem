#include "KeyCommand.h"
#include <cassert>
using namespace std;

KeyCommand::KeyCommand( const std::string* key,const Variant* va )
:m_key(key),m_param(va)
{

}

KeyCommand::~KeyCommand(void)
{
}


std::string KeyCommand::getKey() const
{
	return *m_key;
}

std::map<std::string,Variant> KeyCommand::getParam() const
{
	assert(m_param->getType()==Variant::Map);
	return m_param->toMap();
}

bool KeyCommand::isValid() const
{
	return m_key!=0 && m_param!=0;
}
