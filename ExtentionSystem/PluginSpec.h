#pragma once
#include "global.h"
#include "Castable.h"
#include <string>
#include <vector>

class DLL_EXPORT PluginSpec : public Castable
{
public:
	struct DLL_EXPORT Dependency{
		std::string name;
		std::string version;
	};
	enum State {Invalid,Read};
	PluginSpec(const std::string filename);
	virtual ~PluginSpec(void);
	inline std::string name()const{
		return m_name;
	}
	inline std::string version()const{
		return m_version;
	}
	inline std::string vender()const{
		return m_vendor;
	}
	inline std::vector<Dependency> dependency()const{
		return m_dependency;
	}
	inline std::string license()const{
		return m_license;
	}
	inline std::string category()const{
		return m_category;
	}
	
	inline bool isEnabled()const{
		return m_enabled;
	}

private:
	std::string m_name;
	std::string m_version;
	std::string m_vendor;
	std::string m_license;
	std::string m_category;
	bool			m_enabled;
	std::vector<Dependency> m_dependency;
	friend class PluginSpecLoader;
};
