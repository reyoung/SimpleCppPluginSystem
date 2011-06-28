#pragma once
#include "Castable.h"
#include <string>
class PluginSpec;

/**
*	\abstract 所有Plugin的基类
*	\note
*/
class ExtentionSystem_DLL_API IPlugin:public Castable
{
public:
	IPlugin(void);
	
	//! 初始化Plugin
	//! \method   initialize
	//! \return   bool	是否成功
	//! \param    int argc		命令行参数
	//! \param    char * * argv	命令行参数
	virtual bool initialize(int argc,char** argv)=0;	
	
	//! 初始化结束后回调
	//! \method   initialized
	//! \return   void
	virtual void initialized(){
	}

	//! 获得Plugin的描述
	//! \method   getSpec
	//! \return   PluginSpec*
	inline PluginSpec* getSpec()const{
		return 0;
	}
	virtual ~IPlugin(void);
private:
};
