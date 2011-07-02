#pragma  once

#ifdef SERIALIZATIONPLUGIN_EXPORTS
#define SERIALIZATIONPLUGIN_API __declspec(dllexport)
#else
#define SERIALIZATIONPLUGIN_API __declspec(dllimport)
#endif