#pragma once
#include <ExtentionSystem/Castable.h>
#include <string>
#include "global.h"

class PluginExample_DLL_API PluginExample:public Castable
{
public:
	PluginExample(void);
	virtual ~PluginExample(void);
	void printHello(const std::string& str)const;
};
