#pragma once
#include "global.h"
#include <string>
#include <map>
#include <vector>
#include "Castable.h"
class IPlugin;
class PluginSpec;
class ExtentionSystem_DLL_API PluginManager:public Castable
{
private:
	PluginManager(void);
public:
	static void Initialize(int argc,char** argv,const std::string& plugin_path);
	virtual ~PluginManager(void);


private:
	static PluginManager* m_manager;
	std::map<IPlugin* ,PluginSpec* > m_plugins;
public://! For Test Only
	static std::vector<PluginSpec*> getAllPluginSpec(const std::string& plugin_path);
	static void resolve(std::vector<PluginSpec* > * toResove);
};
