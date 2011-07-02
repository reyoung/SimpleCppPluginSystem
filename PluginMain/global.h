#pragma once
#ifdef PLUGINMAIN_EXPORTS
#define PLUGINMAIN_API __declspec(dllexport)
#else
#define PLUGINMAIN_API __declspec(dllimport)
#endif