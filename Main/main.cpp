#include <iostream>
#include <ExtentionSystem/all.h>
#include <CommandPlugin/CommandSet.h>
#include <cassert>
using namespace std;


int main(int argc,char** argv){
	PluginManager::Initialize(argc,argv,"plugins");	//! 初始化管理器
	map<string,Variant> param;
	param["exec"]=0;
	PluginManager::Invoke("PluginMain",&param);
	system("pause");
	return 0;
}
