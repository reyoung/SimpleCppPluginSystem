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
	for (size_t i=0;i<m_exitReleaseObjs.size();++i)
	{
		delete m_exitReleaseObjs[i];
	}
}


std::vector<PluginSpec*> PluginManager::getAllPluginSpec( const std::string& plugin_path )
{
	int handle;
	struct _finddata_t fileInfo;
	std::vector<PluginSpec*> retv;
	string pattern = plugin_path+"\\*.ini";
	system("cd");
	if ((handle=_findfirst(pattern.c_str(),&fileInfo))!=-1)
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
	for (size_t i=0;i<specs.size();++i)
	{
		m_manager->addExitReleaseObject(specs[i]);
	}
	resolve(&specs);
	for (size_t i=0;i<specs.size();++i)
	{
		IPlugin* plugin = specs[i]->getPlugin();
		if (plugin==NULL)
		{
			continue;
		}
		plugin->m_pm = m_manager;
		m_manager->addExitReleaseObject(plugin);
		plugin->initialize(argc,argv);
		m_manager->m_plugins[plugin] = specs[i];
	}
	for (map<IPlugin* ,PluginSpec* >::iterator it = m_manager->m_plugins.begin();
		it!=m_manager->m_plugins.end();++it)
	{
		it->first->initialized();
	}
	atexit(atexitCallBack);
}

static bool isNotIn(const vector<PluginSpec*>& vec,const PluginSpecDependency& dep ){
	for(size_t i=0;i<vec.size();++i){
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
		for (size_t i = 0;i<specs.size();++i)
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
			for (size_t j=0;j<deps.size();++j)
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

void PluginManager::atexitCallBack()
{
	delete m_manager;
}

void PluginManager::addExitReleaseObject( Castable* obj )
{
	this->m_exitReleaseObjs.push_back(obj);
}

void PluginManager::invoke( const std::string& name,std::map<std::string,Variant>* inout )
{
	IPlugin* plugin = getPlugin(name);
	if (plugin)
	{
		plugin->invoke(inout);
	}else{
		(*inout)["ok"]=false;
	}
}

IPlugin* PluginManager::getPlugin( const std::string& name )
{
	for (map<IPlugin*,PluginSpec*>::iterator it = this->m_plugins.begin();
		it!=this->m_plugins.end();++it)
	{
		if (it->second->name()==name)
		{
			return it->first;
		}
	}
	return 0;
}

void PluginManager::emitSignal( const std::map<std::string,Variant>& sig )
{
	for (map<IPlugin*,PluginSpec*>::iterator it = this->m_plugins.begin();
		it!=this->m_plugins.end();++it)
	{
		std::map<std::string,Variant> temp = sig;
		it->first->invoke(&temp);
	}
}
