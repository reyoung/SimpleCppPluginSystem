#include "PluginManager.h"
#include <io.h>
#include "PluginSpec.h"
using namespace  std;
PluginManager* PluginManager::m_manager=0;

PluginManager::PluginManager(void)
{
}

PluginManager::~PluginManager(void)
{
}

std::vector<PluginSpec*> PluginManager::getAllPluginSpec( const std::string& plugin_path )
{
	int handle;
	struct _finddata_t fileInfo;
	std::vector<PluginSpec*> retv;
	string pattern = plugin_path+"\\*.ini";
	system("cd");
	if ((handle=_findfirst(pattern.c_str(),&fileInfo))!=-1);
	{
		do
		{
			string path = plugin_path+"\\"+fileInfo.name;
			retv.push_back(new PluginSpec(path));
		}while (_findnext(handle,&fileInfo)==0);
		_findclose(handle);
	}
	return retv;
}

void PluginManager::Initialize( int argc,char** argv,const std::string& plugin_path )
{
	m_manager = new PluginManager();
	vector<PluginSpec*> specs = m_manager->getAllPluginSpec(plugin_path);
}

static bool isNotIn(const vector<PluginSpec*>& vec,const PluginSpecDependency& dep ){
	for(int i=0;i<vec.size();++i){
		if (vec[i]->name()==dep.name&&vec[i]->version()==dep.version)
		{
			return false;
		}
	}
	return true;
}


void PluginManager::resolve( std::vector<PluginSpec* > * toResove )
{
	vector<PluginSpec* >& specs = *toResove;
	vector <PluginSpec* > retv ;
	while (retv.size()!=specs.size())
	{
		bool breakFlag= true;
		for (int i = 0;i<specs.size();++i)
		{
			PluginSpecDependency depen;
			depen.name = specs[i]->name();
			depen.version = specs[i]->version();
			bool notIn = isNotIn(retv,depen);
			if(!notIn){
				continue;
			}
			vector<PluginSpecDependency> deps = specs[i]->dependency();
			bool flag = true;
			for (int j=0;j<deps.size();++j)
			{
				if (isNotIn(retv,deps[j]))
				{
					flag=false;
					break;
				}
			}
			if (flag)
			{
				breakFlag = false;
				retv.push_back(specs[i]);
			}
		}
		if (breakFlag)
		{
			break;
		}
	}
	specs = retv;
}
