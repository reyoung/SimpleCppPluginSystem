#pragma once
#include "global.h"
#include <ExtentionSystem/all.h>
class COMMANDPLUGIN_API ICommandSet:public Castable
{
public:
	ICommandSet(void);
	virtual ~ICommandSet(void);
	void newCommandWithType(const std::string& type,const std::string& key,const std::map<std::string,Variant>& param);
};
