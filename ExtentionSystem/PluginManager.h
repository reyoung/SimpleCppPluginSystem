#pragma once
#include "global.h"
#include <string>
#include <map>
#include <vector>
#include "Castable.h"
class IPlugin;
class PluginSpec;

/**
*	\abstract	Plugin管理者，理论上对客户端的唯一接口
*	\note
*/
class ExtentionSystem_DLL_API PluginManager:public Castable
{
private:
	PluginManager(void);
public:

	//! 初始化
	//! \method   Initialize
	//! \return   void
	//! \param    int argc	 传入命令行参数
	//! \param    char * * argv
	//! \param    const std::string & plugin_path plugin的目录
	static void Initialize(int argc,char** argv,const std::string& plugin_path);
	virtual ~PluginManager(void);

	static inline PluginManager* Instance(){
		return m_manager;
	}

	inline PluginSpec* findSpec(const IPlugin* plugin){
		IPlugin* p = const_cast<IPlugin*>(plugin);
		if (m_plugins.find(p)!=m_plugins.end())
		{
			return 0;
		}else{
			return m_plugins[p];
		}
	}

	void addExitReleaseObject(Castable* obj);

private:
	static PluginManager* m_manager;
	std::map<IPlugin* ,PluginSpec* > m_plugins;
	std::vector<Castable* > m_exitReleaseObjs;

	static void atexitCallBack();

//public://! For Test Only

	//! 获得一个目录下所有的PluginSpec，包括子目录
	//! \method   getAllPluginSpec
	//! \return   std::vector<PluginSpec*>
	//! \param    const std::string & plugin_path
	static std::vector<PluginSpec*> getAllPluginSpec(const std::string& plugin_path);


	//! 根据PluginSpec的依赖关系，对PluginSpec进行排序，排序后的顺序，从0到N可以依此载入，无依赖。
	//! \method   resolve
	//! \return   void
	//! \param    std::vector<PluginSpec * > * toResove
	static void resolve(std::vector<PluginSpec* > * toResove);
};
