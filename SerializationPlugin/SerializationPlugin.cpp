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
		case Variant::Bool:
			retv->SetValue("Bool");
			retv->SetDoubleAttribute("Value",input.toBool());
			break;
		case Variant::String:
			retv->SetValue("String");
			{
				TiXmlText* text = new TiXmlText(input.toString().c_str());
				retv->LinkEndChild(text);
			}
			break;
		case Variant::Vector:
			retv->SetValue("Vector");
			{
				vector<Variant> temp = input.toVector();
				for (size_t i=0;i<temp.size();++i)
				{
					retv->LinkEndChild(getXmlElement(temp[i]));
				}
			}
			break;
		case Variant::List:
			retv->SetValue("List");
			{
				list<Variant> temp = input.toList();
				for (list<Variant>::iterator it = temp.begin();it!=temp.end();++it)
				{
					retv->LinkEndChild(getXmlElement(*it));
				}
			}
			break;
		case Variant::Map:
			retv->SetValue("Map");
			{
				map<string,Variant> temp = input.toMap();
				for(map<string,Variant>::iterator it = temp.begin();it!=temp.end();++it){
					TiXmlElement* el = new TiXmlElement(it->first.c_str());
					el->LinkEndChild(getXmlElement(it->second));
					retv->LinkEndChild(el);
				}
			}
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
