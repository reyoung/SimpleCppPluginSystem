#include <iostream>
#include <ExtentionSystem/IPlugin.h>
#include <ExtentionSystem/PluginSpec.h>
#include <cassert>
using namespace std;
int main(int argc,char** argv){
	PluginSpec spec("plugins\\PluginExample.ini");
	cout<<spec.name()<<endl;
	cout<<spec.version()<<endl;
	cout<<spec.vender()<<endl;
	cout<<spec.license()<<endl;
	vector<PluginSpec::Dependency> dep = spec.dependency();
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
	return 0;
}
