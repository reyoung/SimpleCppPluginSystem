#pragma  once
#include <string>
#include <map>
#include <Windows.h>
#include "Castable.h"
using namespace std;


class PluginLoaderPrivate
{
public:
    HINSTANCE pHnd;		//! ���
    string   filename;		//! �ļ���


    //!  ���ش���PluginLoaderPrivate��������plugin֮ǰload��
    //! ��ֱ�ӷ��أ����򴴽��µ�
    //! \method   findOrCreate
    //! \return   PluginLoaderPrivate*
    //! \param    const string & fn
    static PluginLoaderPrivate* findOrCreate(const string& fn);

    PluginLoaderPrivate();
    ~PluginLoaderPrivate();

    //! ж��һ��Plugin��������������Plugin��Loader��ж���ˣ�Free�����
    //! \method   unuse
    //! \return   bool
    bool unuse();

    //!  ����һ��Plugin
    //! \method   load
    //! \return   bool
    bool  load();


    //!  Plugin�Ƿ��Ѿ�����
    //! \method   isLoaded
    //! \return   bool
    bool isLoaded()const;


    //!  ���һ���µ�Plugin�����ࡣ
    //! \method   getInstance
    //! \return   Castable*
    Castable*  getInstance()const;
};
