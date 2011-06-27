#include "PluginLoader_Win32.h"

PluginLoaderPrivate* PluginLoaderPrivate::findOrCreate( const string& fn )
{
    return 0;
}

PluginLoaderPrivate::PluginLoaderPrivate()
    :pHnd(0)
{
}

PluginLoaderPrivate::~PluginLoaderPrivate()
{

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
    return false;
}
