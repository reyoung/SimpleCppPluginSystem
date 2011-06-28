#pragma once
#include "Castable.h"
#include <string>
class PluginSpec;
class ExtentionSystem_DLL_API IPlugin:public Castable
{
public:
	IPlugin(void);
	virtual bool initialize(int argc,char** argv)=0;
	virtual void initialized(){
	}
	inline PluginSpec* getSpec()const{
		return 0;
	}
	virtual ~IPlugin(void);
private:
};
