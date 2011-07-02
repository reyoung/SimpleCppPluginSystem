#include "ICommand.h"
using namespace std;
ICommand::ICommand(void)
{
} 

ICommand::~ICommand(void)
{
}

bool ICommand::perform() const
{
	map<string,Variant> param = getParam();
	PluginManager::Invoke("ActionPlugin",&param);
	return param["ok"].toBool();
}
