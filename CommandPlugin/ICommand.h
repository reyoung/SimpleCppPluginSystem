#pragma once
#include "global.h"
#include <ExtentionSystem/all.h>
class COMMANDPLUGIN_API ICommand:public Castable
{
public:
	ICommand(void);
	virtual ~ICommand(void);
	virtual bool perform()const;
	virtual std::map<std::string,Variant> getParam()const=0;
};
