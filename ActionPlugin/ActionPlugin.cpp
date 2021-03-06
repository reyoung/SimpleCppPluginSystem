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
	if (retv.find("netsearch")!=retv.end())
	{
		map<string,Variant> p = retv["netsearch"].toMap(&ok);
		if (ok)
		{
			if (p.find("keyword")!=p.end()&&p.find("prefix")!=p.end())
			{
				string keyword = p["keyword"].toString(&ok);
				if (ok)
				{
					string prefix = p["prefix"].toString(&ok);
					if (ok)
					{
						if (prefix == "baidu")
						{
							ok =netsearch("http://www.baidu.com/s?wd=",keyword);
						}else if (prefix=="google")
						{
							ok = netsearch("http://www.google.com.hk/#q=",keyword);
						}
						else{
							ok = netsearch(prefix,keyword);
						}
						if (ok)
						{
							++okcount;
						}
					}
				}
			}
			else{
				ok=false;
			}
		}
	}
	if (retv.find("explorer")!=retv.end())
	{
		string path = retv["explorer"].toString(&ok);
		if (ok)
		{
			ok=explorer(path);
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

bool ActionPlugin::netsearch( const std::string& urlprefix,const std::string& keyword )
{
	return browse(urlprefix+keyword);
}

bool ActionPlugin::explorer( const std::string& path ) const
{
	string cmd = "explorer ";
	int retv = system((cmd+path).c_str());
	return retv==1;
}


DECLARE_PLUGIN(ActionPlugin);