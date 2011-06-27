#pragma once
#include "global.h"

/**
*	\abstract	 所有可转型类的基类，插件的基类。同时也是所有插件的基类
*	\note
*/
class ExtentionSystem_DLL_API Castable
{
public:
    Castable(void);
    virtual ~Castable(void);
};
