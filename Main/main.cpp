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
	subparam["prefix"]=string("http://www.baidu.com/s?wd=");
	subparam["keyword"]=string("tjureyoung");
	param["netsearch"]=subparam;

	PluginManager::Instance()->invoke("ActionPlugin",&param);

	cout<<"Invoke Result "<<param["ok"].toBool()<<endl; //! �����Ƿ�ɹ�
	cout<<"Success Invoke Count = "<<param["okcount"].toInt()<<endl;

	system("pause");
	return 0;
}
