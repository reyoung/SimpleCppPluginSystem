#pragma once
#include "global.h"
#include <ExtentionSystem/all.h>
class COMMANDPLUGIN_API CommandSet:public Castable
{

	CommandSet(void);
public:
	static CommandSet* Instance();
	size_t typeCount()const;

	virtual ~CommandSet(void);
private:
	Variant m_data;
	static CommandSet* cmdset;
	friend class CommandPlugin;
	void pack();
private:
	static void atexit_callback();
};
