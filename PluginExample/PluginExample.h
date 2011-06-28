#pragma once
#include <string>
#include "global.h"
#include <ExtentionSystem/IPlugin.h>
class PluginExample_DLL_API PluginExample:public IPlugin
{
public:
	PluginExample(void);
	virtual ~PluginExample(void);
	virtual bool initialize(int argc,char** argv);
	void printHello(const std::string& str)const;
};
