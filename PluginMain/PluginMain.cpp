#include "PluginMain.h"
#include <iostream>
#include <CommandPlugin/CommandPool.h>
#include <CommandPlugin/KeyCommandSet.h>
using namespace std;


PluginMain::PluginMain(void)
{
}

PluginMain::~PluginMain(void)
{
}

void PluginMain::invoke( std::map<std::string,Variant>* inout)
{
	map<string,Variant>& retv = *inout;
	if (retv.find("exec")!=retv.end())
	{
		cout<<"--------Plugin Main Exec------------"<<endl;
		exec();
		cout<<"--------Plugin Main Exec------------"<<endl;
	}
}

bool PluginMain::initialize( int argc,char** argv )
{
	cout<<"Initialize PluginMain"<<endl;
	return true;
}

void PluginMain::exec()
{
	cout<<"Command Type Count: "<<CommandPool::Instance()->typeCount()<<endl;
	KeyCommandSet kset = CommandPool::Instance()->getKeyCommandSet();
	cout<<"Key Set Size: "<<kset.size()<<endl;
	kset.newExeCommand("ie","C:\\Program Files\\Internet Explorer\\iexplore.exe");
	KeyCommand kcmd = kset.findCommand("ie");
	kcmd.perform();
}

DECLARE_PLUGIN(PluginMain);