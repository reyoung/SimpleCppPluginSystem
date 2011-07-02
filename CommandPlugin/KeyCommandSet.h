#pragma once
#include "ICommandSet.h"
#include "KeyCommand.h"
class COMMANDPLUGIN_API KeyCommandSet :public ICommandSet
{
public:
	KeyCommandSet(void);
	virtual ~KeyCommandSet(void);
	KeyCommand findCommand(const std::string& key)const;
	size_t  size()const;
	KeyCommand newCommand(const std::string& key,const std::map<std::string,Variant>& param);
	KeyCommand newExeCommand(const std::string& key,const std::string& path);
	KeyCommand newBrowseCommand(const std::string& key,const std::string& url);
	KeyCommand newNetsearchCommand(const std::string& key,const std::string& prefix,const std::string& keyword);
private:
	Variant*	data;
	friend class CommandPool;
};
