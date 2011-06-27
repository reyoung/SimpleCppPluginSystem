#include "PluginLoader.h"

#ifdef _WIN32
#include "PluginLoader_Win32.h" //! Win32 下PluginLoader的实现
#endif

PluginLoader::PluginLoader( const std::string& fn )
{
    this->setFileName(fn);
}

PluginLoader::PluginLoader()
    :member(0)
{

}

PluginLoader::~PluginLoader(void)
{
    if(member)
        member->unuse();
}

bool PluginLoader::isLoaded() const
{
    return member&&member->isLoaded();
}

bool PluginLoader::load()
{
    return member&&member->load();
}

Castable* PluginLoader::newInstance()
{
    return member?member->getInstance():0;
}

void PluginLoader::setFileName( const std::string& fn/*=""*/ )
{
    member = PluginLoaderPrivate::findOrCreate(fn);
}

bool PluginLoader::unload()
{
    if (member)
    {
        bool retv = member->unuse();
        member = 0;
        return retv;
    }
    else
        return false;
}
