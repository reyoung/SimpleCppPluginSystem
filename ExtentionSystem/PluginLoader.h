#pragma once
#include "global.h"
#include <string>
#include "Castable.h"

/**
*	\abstract 插件载入的实现类
*	\note
*/
class PluginLoaderPrivate;

/**
*	\abstract 插件载入对外的接口
*	\note
*/
class ExtentionSystem_DLL_API PluginLoader
{
	DISABLE_COPY(PluginLoader)
public:
	PluginLoader();
	PluginLoader(const std::string& fn);
	~PluginLoader(void);
	
	//! 设置插件的文件名
	//! \method   setFileName
	//! \return   void
	//! \param    const std::string & fn	插件的文件名(无扩展名)
	void setFileName(const std::string& fn="");

	//! 卸载插件
	//! \method   unload
	//! \return   bool
	bool unload();

	//! 插件是否载入
	//! \method   isLoaded
	//! \return   bool
	bool isLoaded()const;

	//! 载入插件
	//! \method   load
	//! \return   bool
	bool load();


	//! 从插件中，获取插件的主类
	//! \method   newInstance
	//! \return   Castable*	插件的主类，必须继承自Castable
	Castable* newInstance();
	

private:
	PluginLoaderPrivate* member;
};
