#pragma once
#include "global.h"
#include "IPlugin.h"
#include <string>
#include <vector>
/**
*	\abstract Plugin�������࣬����������ϵ�����ߣ��ȵ�
*	\note
*/
class DLL_EXPORT PluginSpec : public Castable
{
public:
	struct DLL_EXPORT Dependency{
		std::string name;
		std::string version;
	};
	enum State {Invalid,Read};
	
	//! ��ʼ������������һ�������ļ�����ini�ļ�������չ��
	//! \method   PluginSpec
	//! \return   
	//! \param    const std::string filename
	PluginSpec(const std::string filename);
	virtual ~PluginSpec(void);

	//! ���Plugin
	//! \method   getPlugin
	//! \return   IPlugin*
	IPlugin* getPlugin()const;

	//! �����
	//! \method   name
	//! \return   std::string
	inline std::string name()const{
		return m_name;
	}

	//! ����汾��
	//! \method   version
	//! \return   std::string
	inline std::string version()const{
		return m_version;
	}

	//! �������/��˾
	//! \method   vender
	//! \return   std::string
	inline std::string vender()const{
		return m_vendor;
	}

	//! ���������
	//! \method   dependency
	//! \return   std::vector<Dependency>  һ�����飬ÿһ����������Ĳ�����Ͱ汾��
	inline std::vector<Dependency> dependency()const{
		return m_dependency;
	}

	//! �������ȨЭ�飨���/�շ�/��Դ��
	//! \method   license
	//! \return   std::string
	inline std::string license()const{
		return m_license;
	}

	//! ��������(�㷨/����)
	//! \method   category
	//! \return   std::string
	inline std::string category()const{
		return m_category;
	}
	
	//! �Ƿ��������
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
	std::vector<Dependency> m_dependency;
	friend class PluginSpecLoader;
};
