#include "PluginMain.h"
#include <iostream>
#include <CommandPlugin/CommandSet.h>
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
	cout<<"Command Type Count: "<<CommandSet::Instance()->typeCount()<<endl;
}

DECLARE_PLUGIN(PluginMain);