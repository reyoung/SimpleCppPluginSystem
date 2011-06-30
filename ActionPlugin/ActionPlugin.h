#pragma once
#include "global.h"
#include <ExtentionSystem/all.h>
class ActionPlugin:public IPlugin
{
public:
	ActionPlugin(void);
	~ActionPlugin(void);
	virtual void invoke(std::map<std::string,Variant>* inout);
	virtual bool initialize(int argc,char** argv);	

	bool exec(const std::string& path)const;
	bool browse(const std::string& url)const;
};
