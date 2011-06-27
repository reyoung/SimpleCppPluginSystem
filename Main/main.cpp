#include <iostream>
#include <ExtentionSystem/PluginLoader.h>
#include <PluginExample/PluginExample.h>
#include <cassert>
using namespace std;
int main(){
	PluginLoader ploader;	// ����Loader
	ploader.setFileName("PluginExample");	//�����ļ���
	bool ok = ploader.load();	//Load
	assert(ok);
	Castable* plugin = ploader.newInstance();	//�����µ�Plugin��
	assert(plugin);
	PluginExample* pe = dynamic_cast<PluginExample* >(plugin); //ת�͵��û��Զ�������
	assert(pe);
	pe->printHello("Hello world from plugin");			//�����û��Զ��庯��
	delete plugin;			// �ͷ�new ������Plugin
	system("pause");
	return 0;
}
