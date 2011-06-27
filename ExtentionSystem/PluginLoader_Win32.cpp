#include "PluginLoader_Win32.h"
#include "Castable.h"
#include <map>
#include <sstream>
#include <climits>
using namespace std;
#ifndef  PATH_MAX
#define PATH_MAX 512
#endif

#define VERSION_GETTER	"__get__plugin__version"
#define INSTANCE_GETTER "__get__plugin__instance"



//! ������һ���ṹ�壬����Loader��ָ������ô���
struct AUX_STRUCT{
	int	refcount;
	PluginLoaderPrivate*	 data;
	AUX_STRUCT()
		:refcount(0),data(0)
	{
	}
};
//! �ļ�����AUX_STRUCT��ӳ��
static map<string,AUX_STRUCT> LoaderPool;
//! �����˳�ʱ��������е�LoaderPool;
static void CleanLoaderPool(){
	for (map<string,AUX_STRUCT>::iterator it = LoaderPool.begin();it!=LoaderPool.end();++it)
	{
		if(it->second.data)
			delete it->second.data;
	}
}
//! ע������˳�ʱ�Ļص�����
static int RegestExitFunc(){
	atexit(CleanLoaderPool);
	return 0;
}
//! ִ��ע��
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
#ifdef UNICODE
	string& orig = this->filename;
	size_t origsize = strlen(orig.c_str()) + 1;
	size_t convertedChars = 0;
	wchar_t* wcstring= new wchar_t[PATH_MAX];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
	pHnd = LoadLibrary(wcstring);
	delete [] wcstring;
#else
	pHnd = LoadLibrary(this->filename.c_str());
#endif

	return pHnd!=NULL;
}

bool PluginLoaderPrivate::isLoaded() const
{
    return pHnd!=NULL;
}

Castable* PluginLoaderPrivate::getInstance() 
{
	typedef int (*VersionFunc)();
	if(!isLoaded()||!load()){
		//! Failed to load
		return 0;
	}
	VersionFunc vf = (VersionFunc) GetProcAddress(this->pHnd,VERSION_GETTER);
	if(vf){
		int version = vf();
		switch(version){
		case 0:
			{
				typedef Castable*  (*InstanceFunc)();
				InstanceFunc func = (InstanceFunc )GetProcAddress(pHnd,INSTANCE_GETTER);
				if(func){
					return func();
				}else{
					//! Fail to load
					return 0;
				}
			}
		default:
			//! Fail to load
			return 0;
		}
	}else{
		//! Failed to load. Cannot Find VERSION_GETTER
		return 0;
	}
}

bool PluginLoaderPrivate::unuse()
{
	if(LoaderPool.find(this->filename)==LoaderPool.end()){ // û�ҵ�
		return false;
	}else{
		AUX_STRUCT& temp = LoaderPool[this->filename];
		--temp.refcount;
		// ��ʹLoaderû�������ˣ����е����ݽṹ��������Ȼ�ᱻ���ã����ԣ�����Ҫɾ��
		// �����˳���һ����ȫɾ����
		//if(!temp.refcount){	//! û������������
		//	LoaderPool.erase(LoaderPool.find(this->filename));  // �������е�����ɾ��
		//	delete this; // ɾ���Լ�
		//}
		return true;
	}
}
