#pragma once
#include "PluginSpec.h"
class PluginSpecLoader
{
public:
	static bool Load(PluginSpec * self, const std::string& fn);
private:
	static int handler(void* user, const char* section, const char* name, const char* value);
	static void ParseDependency(PluginSpec * self, const char* desc);
};
