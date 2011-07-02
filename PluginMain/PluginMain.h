#pragma once
#include <ExtentionSystem/all.h>
#include "global.h"
class PLUGINMAIN_API PluginMain :public IPlugin
{
public:
	PluginMain(void);
	~PluginMain(void);
	virtual void invoke(std::map<std::string,Variant>* );
	virtual bool initialize(int argc,char** argv);
	
	void exec();
};
