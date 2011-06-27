#include "PluginLoader_Win32.h"

#include <map>

using namespace std;

struct AUX_STRUCT{
	int	refcount;
	PluginLoaderPrivate*	 data;
	AUX_STRUCT()
		:refcount(0),data(0)
	{
	}
};
static map<string,AUX_STRUCT> LoaderPool;

static void CleanLoaderPool(){
	for (map<string,AUX_STRUCT>::iterator it = LoaderPool.begin();it!=LoaderPool.end();++it)
	{
		delete it->second.data;
	}
}
static int RegestExitFunc(){
	atexit(CleanLoaderPool);
	return 0;
}
static int __InitValue = RegestExitFunc();

PluginLoaderPrivate* PluginLoaderPrivate::findOrCreate( const string& fn )
{
	if(LoaderPool.find(fn)==LoaderPool.end()){  //! δ���ع�
		AUX_STRUCT temp;
		temp.data = new PluginLoaderPrivate();
		temp.data->filename = fn;
		++temp.refcount;
		LoaderPool[fn]=temp;
		return temp.data;
	}else{
		AUX_STRUCT& temp = LoaderPool[fn];
		++temp.refcount;
		return temp.data;
	}
}

PluginLoaderPrivate::PluginLoaderPrivate()
    :pHnd(0)
{
}

PluginLoaderPrivate::~PluginLoaderPrivate()
{
	if (pHnd)
	{
		FreeLibrary(this->pHnd);
	}
}

bool PluginLoaderPrivate::load()
{
    return false;
}

bool PluginLoaderPrivate::isLoaded() const
{
    return false;
}

Castable* PluginLoaderPrivate::getInstance() const
{
    return 0;
}

bool PluginLoaderPrivate::unuse()
{
	if(LoaderPool.find(this->filename)==LoaderPool.end()){ // û�ҵ�
		return false;
	}else{
		AUX_STRUCT& temp = LoaderPool[this->filename];
		--temp.refcount;
		if(!temp.refcount){	//! û������������
			LoaderPool.erase(LoaderPool.find(this->filename));  // �������е�����ɾ��
			delete this; // ɾ���Լ�
		}
		return true;
	}
}
