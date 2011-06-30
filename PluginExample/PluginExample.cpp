#include "PluginExample.h"
#include <string>
#include <iostream>
#include <ExtentionSystem/Plugin.h>
#include <map>
using namespace std;

PluginExample::PluginExample(void)
{
}

PluginExample::~PluginExample(void)
{
}

void PluginExample::printHello( const std::string& str ) const
{
	using namespace std;
	cout<<str<<endl;
}

bool PluginExample::initialize( int argc,char** argv )
{
	using namespace std;
	cout<<"Initialize"<<endl;
	return true;
}

void PluginExample::invoke( std::map<std::string,Variant>* inout )
{
	map<string,Variant>& retv = *inout;
	bool ok=false;
	if(retv.find("printHello")!=retv.end()){
		string param = retv["printHello"].toString(&ok);
		if (ok)
		{
			this->printHello(param);
		}
	}
	retv["ok"]=ok;
}

DECLARE_PLUGIN(PluginExample)