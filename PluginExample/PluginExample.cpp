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
DECLARE_PLUGIN(PluginExample)