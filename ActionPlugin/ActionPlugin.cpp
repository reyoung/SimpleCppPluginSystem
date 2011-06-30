#include "ActionPlugin.h"
#include <iostream>

using namespace std;
ActionPlugin::ActionPlugin(void)
{
}

ActionPlugin::~ActionPlugin(void)
{
}

bool ActionPlugin::initialize( int argc,char** argv )
{
	cout<<"Initialize ActionPlugin"<<endl;
	return true;
}

void ActionPlugin::invoke( std::map<std::string,Variant>* inout)
{
	std::map<std::string,Variant>& retv = *inout;
	bool ok = false;
	int okcount=0;
	if (retv.find("exec")!=retv.end())
	{
		string path = retv["exec"].toString(&ok);
		if (ok)
		{
			ok = exec(path);
			if (ok)
			{
				++okcount;
			}
		}
	}
	if (retv.find("browse")!=retv.end())
	{
		string url = retv["browse"].toString(&ok);
		if (ok)
		{
			ok = browse(url);
			if (ok)
			{
				++okcount;
			}
		}
	}

	retv["ok"]=ok;
	retv["okcount"]=okcount;
}

bool ActionPlugin::exec( const std::string& path )const
{
	//cout<<"Invoke Exec with path:"<<path<<endl;
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof( si ) );
	si.cb = sizeof( si );
	ZeroMemory( &pi, sizeof( pi ) );

	if( !CreateProcessA(path.c_str(),
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi ) )
	{
		return false;
	}else{
		return true;
	}
}

bool ActionPlugin::browse( const std::string& url ) const
{
	//cout<<"Browse Url:"<<url<<endl;
	HKEY hkRoot,hSubKey; 
	char ValueName[256];
	unsigned char DataValue[256];
	unsigned long cbValueName=256;
	unsigned long cbDataValue=256;
	char ShellChar[256]; 
	DWORD dwType;
	string u= " "+url;
	if(RegOpenKeyA(HKEY_CLASSES_ROOT,NULL,&hkRoot)==ERROR_SUCCESS)
	{
		if(RegOpenKeyExA(hkRoot,
			"htmlfile\\shell\\open\\command",
			0,
			KEY_ALL_ACCESS,
			&hSubKey)==ERROR_SUCCESS)
		{
			RegEnumValueA(hSubKey, 
				0,
				ValueName,
				&cbValueName,
				NULL,
				&dwType,
				DataValue,
				&cbDataValue);
			strcpy(ShellChar,(char *)DataValue);
			strcat(ShellChar,u.c_str());
			WinExec(ShellChar,SW_SHOW);
		}
		else
			return false;
	}
	else
		return false;
	RegCloseKey(hSubKey);
	RegCloseKey(hkRoot);
	return true;
}


DECLARE_PLUGIN(ActionPlugin);