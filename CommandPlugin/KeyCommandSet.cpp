#include "KeyCommandSet.h"
#include <cassert>
using namespace std;
KeyCommandSet::KeyCommandSet(void)
{
}

KeyCommandSet::~KeyCommandSet(void)
{
}

KeyCommand KeyCommandSet::findCommand( const std::string& key ) const
{
	map<string,Variant>::const_iterator it = data->mapPtr()->find(key);
	if (it!=data->mapPtr()->end())
	{
		KeyCommand kcmd(&it->first,&it->second);
	}else{
		return KeyCommand(0,0);
	}
}

size_t KeyCommandSet::size() const
{
	assert(data->getType()==Variant::Map);
	return data->mapPtr()->size();
}

KeyCommand KeyCommandSet::newCommand( const std::string& key,const std::map<std::string,Variant>& param )
{
	assert(data->getType()==Variant::Map);
	(*data->mapPtr())[key] = param;
	map<string,Variant>::iterator it = data->mapPtr()->find(key);
	assert(it!=data->mapPtr()->end());
	KeyCommand kcmd(&it->first,&it->second);
	return kcmd;
}

KeyCommand KeyCommandSet::newExeCommand( const std::string& key,const std::string& path )
{
	map<string,Variant> param;
	param["exec"]=path;
	return newCommand(key,param);
}
