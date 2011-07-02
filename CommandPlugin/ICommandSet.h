#pragma once
#include "global.h"
#include <ExtentionSystem/all.h>
class COMMANDPLUGIN_API ICommandSet:public Castable
{
public:
	ICommandSet(void);
	virtual ~ICommandSet(void);
};
