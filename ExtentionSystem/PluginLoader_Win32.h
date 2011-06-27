#pragma  once
#include <string>
#include <map>
#include <Windows.h>
#include "Castable.h"
using namespace std;


class PluginLoaderPrivate
{
public:
    HINSTANCE pHnd;		//! 句柄
    string   filename;		//! 文件名


    //!  本地存有PluginLoaderPrivate表，如果这个plugin之前load过
    //! ，直接返回，否则创建新的
    //! \method   findOrCreate
    //! \return   PluginLoaderPrivate*
    //! \param    const string & fn
    static PluginLoaderPrivate* findOrCreate(const string& fn);

    PluginLoaderPrivate();
    ~PluginLoaderPrivate();

    //! 卸载一个Plugin，如果所有用这个Plugin的Loader都卸载了，Free掉句柄
    //! \method   unuse
    //! \return   bool
    bool unuse();

    //!  载入一个Plugin
    //! \method   load
    //! \return   bool
    bool  load();


    //!  Plugin是否已经载入
    //! \method   isLoaded
    //! \return   bool
    bool isLoaded()const;


    //!  获得一个新的Plugin的主类。
    //! \method   getInstance
    //! \return   Castable*
    Castable*  getInstance()const;
};
