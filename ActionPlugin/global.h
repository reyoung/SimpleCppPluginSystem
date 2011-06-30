#pragma  once

#ifdef ACTIONPLUGIN_EXPORTS
#define ACTIONPLUGIN_DLL __declspec(dllexport)
#else
#define  ACTIONPLUGIN_DLL __declspec(dllimport)
#endif