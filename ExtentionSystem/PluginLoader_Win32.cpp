#include "PluginLoader_Win32.h"

#include <map>

using namespace std;
//! 辅助的一个结构体，保存Loader的指针和引用次数
struct AUX_STRUCT{
	int	refcount;
	PluginLoaderPrivate*	 data;
	AUX_STRUCT()
		:refcount(0),data(0)
	{
	}
};
//! 文件名和AUX_STRUCT的映射
static map<string,AUX_STRUCT> LoaderPool;
//! 程序退出时，清空所有的LoaderPool;
static void CleanLoaderPool(){
	for (map<string,AUX_STRUCT>::iterator it = LoaderPool.begin();it!=LoaderPool.end();++it)
	{
		if(it->second.data)
			delete it->second.data;
	}
}
//! 注册程序退出时的回调函数
static int RegestExitFunc(){
	atexit(CleanLoaderPool);
	return 0;
}
//! 执行注册
static int __InitValue = RegestExitFunc();

PluginLoaderPrivate* PluginLoaderPrivate::findOrCreate( const string& fn )
{
	if(LoaderPool.find(fn)==LoaderPool.end()){  //! 未加载过
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
	if(LoaderPool.find(this->filename)==LoaderPool.end()){ // 没找到
		return false;
	}else{
		AUX_STRUCT& temp = LoaderPool[this->filename];
		--temp.refcount;
		if(!temp.refcount){	//! 没有人在引用了
			LoaderPool.erase(LoaderPool.find(this->filename));  // 将容器中的引用删除
			delete this; // 删除自己
		}
		return true;
	}
}
