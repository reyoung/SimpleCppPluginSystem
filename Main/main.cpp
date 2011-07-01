#include <iostream>
#include <ExtentionSystem/IPlugin.h>
#include <ExtentionSystem/PluginSpec.h>
#include <ExtentionSystem/PluginManager.h>
#include <ExtentionSystem/Variant.h>
#include <cassert>
using namespace std;

int main(int argc,char** argv){
	PluginManager::Initialize(argc,argv,"plugins");	//! ��ʼ��������
	
	map<string,Variant> param;//! ���ú���
	param["browse"]=string("www.baidu.com");
	param["exec"]=string("C:\\Program Files\\Windows Media Player\\wmplayer.exe");
	map<string,Variant> subparam;
	subparam["prefix"]=string("google");
	subparam["keyword"]=string("tjureyoung");
	param["netsearch"]=subparam;
	param["explorer"]=string("C:\\");

	PluginManager::Instance()->invoke("ActionPlugin",&param);

	cout<<"Invoke Result "<<param["ok"].toBool()<<endl; //! �����Ƿ�ɹ�
	cout<<"Success Invoke Count = "<<param["okcount"].toInt()<<endl;
	system("pause");
	return 0;
}
