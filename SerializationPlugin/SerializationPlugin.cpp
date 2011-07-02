#include "SerializationPlugin.h"
#include <iostream>
#include "tinyxml.h"
using namespace std;

SerializationPlugin::SerializationPlugin(void)
{
}

SerializationPlugin::~SerializationPlugin(void)
{
}

void SerializationPlugin::invoke( std::map<std::string,Variant>* inout)
{
	map<string,Variant>& retv = *inout;
	bool ok = false;
	if (retv.find("serialize")!=retv.end()&&retv.find("serializePath")!=retv.end())
	{
		Variant& temp = retv["serialize"];
		string path = retv["serializePath"].toString(&ok);
		if (ok)
		{
			ok=serialize(path,temp);
		}
	}
}

bool SerializationPlugin::initialize( int argc,char** argv )
{
	cout<<"Initialize SerializationPlugin"<<endl;
	return true;
}

static TiXmlElement* getXmlElement(const Variant& input){
	TiXmlElement* retv = new TiXmlElement("Invalid");
	switch(input.getType()){
		case Variant::Int:
			retv->SetValue("Int");
			retv->SetAttribute("Value",input.toInt());
			break;
		case Variant::Char:
			retv->SetValue("Char");
			retv->SetAttribute("Value",input.toChar());
			break;
		case Variant::Short:
			retv->SetValue("Short");
			retv->SetAttribute("Value",input.toShort());
			break;
		case Variant::Long:
			retv->SetValue("Long");
			retv->SetAttribute("Value",input.toLong());
			break;
		case Variant::LongLong:
			retv->SetValue("LongLong");
			retv->SetAttribute("Value",input.toLongLong());
			break;
		case Variant::Float:
			retv->SetValue("Float");
			retv->SetDoubleAttribute("Value",input.toFloat());
			break;
		case Variant::Double:
			retv->SetValue("Double");
			retv->SetDoubleAttribute("Value",input.toDouble());
			break;
	}
	return retv;
}

bool SerializationPlugin::serialize( const std::string& path,const Variant& input )
{
	//cout<<"Invoke Serialize"<<endl;
	TiXmlDocument doc (path.c_str());
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0","","");
	doc.LinkEndChild(decl);
	doc.LinkEndChild(getXmlElement(input));
	doc.SaveFile(path.c_str());
	return true;
}

DECLARE_PLUGIN(SerializationPlugin);
