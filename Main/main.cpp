#include <iostream>
#include <ExtentionSystem/PluginLoader.h>
using namespace std;
int main(){
	PluginLoader ploader;
	ploader.setFileName("PluginExample");
	cout<<ploader.unload()<<endl;
	return 0;
}
