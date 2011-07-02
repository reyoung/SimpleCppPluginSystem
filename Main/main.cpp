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
	map<string,Variant> m;
	list<Variant> vec;
	vec.push_back(1);
	vec.push_back(string("2"));
	vec.push_back(3.3);
	m["Array"]=vec;
	m["T2"]=10;
	data =m;
	map<string,Variant> param;
	param["serialize"]=data;
	param["serializePath"]=string("out.xml");
	PluginManager::Invoke("SerializationPlugin",&param);
	param.clear();
	param["deserialize"]=string("out.xml");
	PluginManager::Invoke("SerializationPlugin",&param);
	cout<<param["deserialize"].toMap().size()<<endl;
	system("pause");
	return 0;
}
