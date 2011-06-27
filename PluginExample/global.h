#include <Windows.h>

#ifdef PLUGINEXAMPLE_EXPORTS
#define PluginExample_DLL_API	__declspec(dllexport)
#else
#define PluginExample_DLL_API  __declspec(dllimport)
#endif