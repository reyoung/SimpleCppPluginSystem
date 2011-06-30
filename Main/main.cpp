#include <iostream>
#include <ExtentionSystem/IPlugin.h>
#include <ExtentionSystem/PluginSpec.h>
#include <ExtentionSystem/PluginManager.h>
#include <ExtentionSystem/Variant.h>
#include <cassert>
using namespace std;

int main(int argc,char** argv){
	PluginManager::Initialize(argc,argv,"plugins");	//! 初始化管理器
	
	map<string,Variant> param;//! 调用函数
	param["printHello"]="Hello world\nThis param is from outsize\n";
	PluginManager::Instance()->invoke("PluginExample",&param);

	cout<<"Invoke Result "<<param["ok"].toBool()<<endl; //! 调用是否成功

	system("pause");
	return 0;
}
