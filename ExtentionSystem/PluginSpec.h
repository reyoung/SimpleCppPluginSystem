#pragma once
#include "global.h"
#include "IPlugin.h"
#include <string>
#include <vector>
/**
*	\abstract Plugin的描述类，存有依赖关系，作者，等等
*	\note
*/
struct DLL_EXPORT PluginSpecDependency{
	std::string name;
	std::string version;
};
class DLL_EXPORT PluginSpec : public Castable
{
public:

	enum State {Invalid,Read};
	
	//! 初始化描述，传入一个配置文件名，ini文件，带扩展名
	//! \method   PluginSpec
	//! \return   
	//! \param    const std::string filename
	PluginSpec(const std::string filename);
	virtual ~PluginSpec(void);

	//! 获得Plugin
	//! \method   getPlugin
	//! \return   IPlugin*
	IPlugin* getPlugin()const;

	//! 插件名
	//! \method   name
	//! \return   std::string
	inline std::string name()const{
		return m_name;
	}

	//! 插件版本号
	//! \method   version
	//! \return   std::string
	inline std::string version()const{
		return m_version;
	}

	//! 插件作者/公司
	//! \method   vender
	//! \return   std::string
	inline std::string vender()const{
		return m_vendor;
	}

	//! 插件的依赖
	//! \method   dependency
	//! \return   std::vector<Dependency>  一个数组，每一项均是以来的插件名和版本号
	inline std::vector<PluginSpecDependency> dependency()const{
		return m_dependency;
	}

	//! 插件的授权协议（免费/收费/开源）
	//! \method   license
	//! \return   std::string
	inline std::string license()const{
		return m_license;
	}

	//! 插件的类别(算法/界面)
	//! \method   category
	//! \return   std::string
	inline std::string category()const{
		return m_category;
	}
	
	//! 是否启动插件
	//! \method   isEnabled
	//! \return   bool
	inline bool isEnabled()const{
		return m_enabled;
	}

private:
	std::string m_filename;
	std::string m_name;
	std::string m_version;
	std::string m_vendor;
	std::string m_license;
	std::string m_category;
	bool			m_enabled;
	std::vector<PluginSpecDependency> m_dependency;
	friend class PluginSpecLoader;
};
