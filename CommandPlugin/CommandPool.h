#pragma once
#include "global.h"
#include <ExtentionSystem/all.h>
class KeyCommandSet;
class COMMANDPLUGIN_API CommandPool:public Castable
{

	CommandPool(void);
public:
	static CommandPool* Instance();
	size_t typeCount()const;
	KeyCommandSet getKeyCommandSet();
	virtual ~CommandPool(void);
private:
	Variant m_data;
	static CommandPool* cmdset;
	friend class CommandPlugin;
	void pack();
private:
	static void atexit_callback();
};
