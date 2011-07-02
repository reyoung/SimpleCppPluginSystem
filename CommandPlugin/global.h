#pragma  once

#ifdef COMMANDPLUGIN_EXPORTS
#define COMMANDPLUGIN_API	__declspec(dllexport)
#else
#define COMMANDPLUGIN_API   __declspec(dllimport)
#endif