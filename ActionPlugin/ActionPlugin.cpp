#include "ActionPlugin.h"
#include <iostream>
using namespace std;
ActionPlugin::ActionPlugin(void)
{
}

ActionPlugin::~ActionPlugin(void)
{
}

bool ActionPlugin::initialize( int argc,char** argv )
{
	cout<<"Initialize ActionPlugin"<<endl;
	return true;
}

void ActionPlugin::invoke( std::map<std::string,Variant>* inout)
{

}

DECLARE_PLUGIN(ActionPlugin);