#include "ICommandSet.h"
#include "CommandPool.h"
#include "KeyCommandSet.h"
using namespace std;
ICommandSet::ICommandSet(void)
{
}

ICommandSet::~ICommandSet(void)
{
}

void ICommandSet::newCommandWithType( const std::string& type,const std::string& key,const map<std::string,Variant>& param )
{
	if (type=="Key")
	{
		CommandPool::Instance()->getKeyCommandSet().newCommand(key,param);
	}
}
