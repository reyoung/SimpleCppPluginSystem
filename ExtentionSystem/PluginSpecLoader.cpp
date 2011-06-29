#include "PluginSpecLoader.h"
#include "ini.h"

bool PluginSpecLoader::Load( PluginSpec * self, const std::string& fn )
{
	if(ini_parse(fn.c_str(),handler,self)<0){
		return false;
	}
	return true;
}

int PluginSpecLoader::handler( void* user, const char* section, const char* name, const char* value )
{
	PluginSpec* pconfig = (PluginSpec*)user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	if (MATCH("PluginInfo","Name"))
	{
		pconfig->m_name = strdup(value);
	}else if (MATCH("PluginInfo","Version"))
	{
		pconfig->m_version = strdup(value);
	}else if(MATCH("PluginInfo","Vendor")){
		pconfig->m_vendor = strdup(value);
	}else if(MATCH("PluginInfo","Dependency")){
		ParseDependency(pconfig,value);
	}else if(MATCH("PluginInfo","License")){
		pconfig->m_license = strdup(value);
	}else if(MATCH("PluginInfo","Category")){
		pconfig->m_category = strdup(value);
	}else if(MATCH("PluginInfo","Enabled")){
		pconfig->m_enabled= value[0]=='1';
	}
	return 0;
}


void PluginSpecLoader::ParseDependency( PluginSpec * self, const char* desc )
{
	PluginSpecDependency dep;
	int flag= 0;
	for (size_t i=0;i<strlen(desc);++i)
	{
		if(desc[i]=='('){
			++flag;
			continue;
		}else if (desc[i]==')')
		{
			++flag;
			self->m_dependency.push_back(dep);
			dep.name.clear();
			dep.version.clear();
			continue;
		}else if(desc[i]==':'){
			flag = 0;
			continue;
		}else{
			if(flag==0){
				dep.name.push_back(desc[i]);
			}else{
				dep.version.push_back(desc[i]);
			}
		}
	}
}
