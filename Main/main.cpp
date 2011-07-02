#include <iostream>
#include <ExtentionSystem/IPlugin.h>
#include <ExtentionSystem/PluginSpec.h>
#include <ExtentionSystem/PluginManager.h>
#include <ExtentionSystem/Variant.h>
#include <cassert>
using namespace std;


int main(int argc,char** argv){
	PluginManager::Initialize(argc,argv,"plugins");	//! 初始化管理器
	Variant data;
	double a = 1.2;
	data = a;
	map<string,Variant> param;
	param["serialize"]=data;
	param["serializePath"]=string("out.xml");
	PluginManager::Invoke("SerializationPlugin",&param);
	system("pause");
	return 0;
}
