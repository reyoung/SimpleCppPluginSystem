#pragma once
#include "global.h"
#include <string>
#include <map>
#include <vector>
#include "Castable.h"
class IPlugin;
class PluginSpec;

/**
*	\abstract	Plugin�����ߣ������϶Կͻ��˵�Ψһ�ӿ�
*	\note
*/
class ExtentionSystem_DLL_API PluginManager:public Castable
{
private:
	PluginManager(void);
public:

	//! ��ʼ��
	//! \method   Initialize
	//! \return   void
	//! \param    int argc	 ���������в���
	//! \param    char * * argv
	//! \param    const std::string & plugin_path plugin��Ŀ¼
	static void Initialize(int argc,char** argv,const std::string& plugin_path);
	virtual ~PluginManager(void);


private:
	static PluginManager* m_manager;
	std::map<IPlugin* ,PluginSpec* > m_plugins;
public://! For Test Only

	//! ���һ��Ŀ¼�����е�PluginSpec��������Ŀ¼
	//! \method   getAllPluginSpec
	//! \return   std::vector<PluginSpec*>
	//! \param    const std::string & plugin_path
	static std::vector<PluginSpec*> getAllPluginSpec(const std::string& plugin_path);


	//! ����PluginSpec��������ϵ����PluginSpec��������������˳�򣬴�0��N�����������룬��������
	//! \method   resolve
	//! \return   void
	//! \param    std::vector<PluginSpec * > * toResove
	static void resolve(std::vector<PluginSpec* > * toResove);
};