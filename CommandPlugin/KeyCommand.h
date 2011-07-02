#pragma once
#include "global.h"
#include "ICommand.h"
class COMMANDPLUGIN_API KeyCommand:public ICommand
{
	KeyCommand(const std::string& key,const Variant* va);
public:
	virtual ~KeyCommand(void);
	bool isValid()const;
	std::string getKey()const;
	virtual std::map<std::string,Variant> getParam()const;
private:
	const Variant* m_param;
	const std::string m_key;
	friend class KeyCommandSet;
};
