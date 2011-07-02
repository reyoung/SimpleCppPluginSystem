#pragma once
#include <ExtentionSystem/all.h>
#include "global.h"
class COMMANDPLUGIN_API CommandPlugin:public IPlugin
{
public:
	CommandPlugin(void);
	~CommandPlugin(void);
	virtual bool initialize(int argc,char** argv);
	virtual void invoke(std::map<std::string,Variant>* );
	virtual void initialized();
	std::string getCMDConfigFileName()const;
private:
	std::string m_file;
};
