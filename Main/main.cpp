#include <iostream>
#include <ExtentionSystem/PluginLoader.h>
#include <PluginExample/PluginExample.h>
#include <cassert>
using namespace std;
int main(){
	PluginLoader ploader;	// 建立Loader
	ploader.setFileName("PluginExample");	//设置文件名
	bool ok = ploader.load();	//Load
	assert(ok);
	Castable* plugin = ploader.newInstance();	//创建新的Plugin类
	assert(plugin);
	PluginExample* pe = dynamic_cast<PluginExample* >(plugin); //转型到用户自定义类型
	assert(pe);
	pe->printHello("Hello world from plugin");			//调用用户自定义函数
	delete plugin;			// 释放new 出来的Plugin
	system("pause");
	return 0;
}
