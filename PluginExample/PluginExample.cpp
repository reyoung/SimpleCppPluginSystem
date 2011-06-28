#include "PluginExample.h"
#include <string>
#include <iostream>
#include <ExtentionSystem/Plugin.h>
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

DECLARE_PLUGIN(PluginExample)