#pragma once
#include <ExtentionSystem/all.h>
#include "global.h"
class SERIALIZATIONPLUGIN_API SerializationPlugin:public IPlugin
{
public:
	SerializationPlugin(void);
	virtual void invoke(std::map<std::string,Variant>* );
	virtual bool initialize(int argc,char** argv);

	bool serialize(const std::string& path,const Variant& input);

	virtual ~SerializationPlugin(void);
};
