#pragma once
#include "Castable.h"
#include <string>
#include "PluginManager.h"

/**
*	\abstract ����Plugin�Ļ���
*	\note
*/
class ExtentionSystem_DLL_API IPlugin:public Castable
{
public:
	IPlugin(void);
	
	//! ��ʼ��Plugin
	//! \method   initialize
	//! \return   bool	�Ƿ�ɹ�
	//! \param    int argc		�����в���
	//! \param    char * * argv	�����в���
	virtual bool initialize(int argc,char** argv)=0;	
	
	//! ��ʼ��������ص�
	//! \method   initialized
	//! \return   void
	virtual void initialized(){
	}

	//! ���Plugin������
	//! \method   getSpec
	//! \return   PluginSpec*
	inline PluginSpec* getSpec()const{
		return m_pm->findSpec(this);
	}
	virtual ~IPlugin(void);
private:
	PluginManager* m_pm;
	friend class PluginManager;
};
