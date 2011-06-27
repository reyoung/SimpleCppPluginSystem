#pragma once
#include "global.h"
#include <string>
#include "Castable.h"

/**
*	\abstract ��������ʵ����
*	\note
*/
class PluginLoaderPrivate;

/**
*	\abstract ����������Ľӿ�
*	\note
*/
class ExtentionSystem_DLL_API PluginLoader
{
	DISABLE_COPY(PluginLoader)
public:
	PluginLoader();
	PluginLoader(const std::string& fn);
	~PluginLoader(void);
	
	//! ���ò�����ļ���
	//! \method   setFileName
	//! \return   void
	//! \param    const std::string & fn	������ļ���(����չ��)
	void setFileName(const std::string& fn="");

	//! ж�ز��
	//! \method   unload
	//! \return   bool
	bool unload();

	//! ����Ƿ�����
	//! \method   isLoaded
	//! \return   bool
	bool isLoaded()const;

	//! ������
	//! \method   load
	//! \return   bool
	bool load();


	//! �Ӳ���У���ȡ���������
	//! \method   newInstance
	//! \return   Castable*	��������࣬����̳���Castable
	Castable* newInstance();
	

private:
	PluginLoaderPrivate* member;
};
