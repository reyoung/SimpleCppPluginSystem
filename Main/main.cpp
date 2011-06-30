#include <iostream>
#include <ExtentionSystem/IPlugin.h>
#include <ExtentionSystem/PluginSpec.h>
#include <ExtentionSystem/PluginManager.h>
#include <ExtentionSystem/Variant.h>
#include <cassert>
using namespace std;
void testSpec(int argc,char** argv){
	PluginSpec spec("plugins\\PluginExample.ini");
	cout<<spec.name()<<endl;
	cout<<spec.version()<<endl;
	cout<<spec.vender()<<endl;
	cout<<spec.license()<<endl;
	vector<PluginSpecDependency> dep = spec.dependency();
	for (int i=0;i<dep.size();++i)
	{
		cout<<dep[i].name<<" "<<dep[i].version<<endl;
	}
	cout<<spec.isEnabled()<<endl;

	IPlugin* plugin = spec.getPlugin();
	if (plugin)
	{
		plugin->initialize(argc,argv);
	}
	delete plugin;
	system("pause");
}


int main(int argc,char** argv){
	PluginManager::Initialize(argc,argv,"plugins");
	Variant v;
	v="Hello world";
	cout<<v.toString()<<endl;
	v=12;
	cout<<v.toInt()<<endl;
	system("pause");
	return 0;
}
