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
	if (retv.find("deserialize")!=retv.end())
	{
		string path = retv["deserialize"].toString(&ok);
		if (ok)
		{
			ok = deserialize(path,retv["deserialize"]);
		}
	}
	retv["ok"]=ok;
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
static Variant getVarient(TiXmlElement* el){
	if (strcmp(el->Value(),"Int")==0)
	{
		return Variant(int(el->FirstAttribute()->IntValue()));
	}else if (strcmp(el->Value(),"Char")==0)
	{
		return Variant(char(el->FirstAttribute()->IntValue()));
	}else if (strcmp(el->Value(),"Short")==0)
	{
		return Variant(short(el->FirstAttribute()->IntValue()));
	}else if (strcmp(el->Value(),"Long")==0)
	{
		return Variant(long(el->FirstAttribute()->IntValue()));
	}else if (strcmp(el->Value(),"LongLong")==0)
	{
		return Variant(long long(el->FirstAttribute()->IntValue()));
	}else if (strcmp(el->Value(),"Float")==0)
	{
		return Variant(float(el->FirstAttribute()->DoubleValue()));
	}else if (strcmp(el->Value(),"Double")==0)
	{
		return Variant(double(el->FirstAttribute()->DoubleValue()));
	}else if(strcmp(el->Value(),"String")==0){
		TiXmlText* node = el->FirstChild()->ToText();
		return Variant(string(node->Value()));
	}else if(strcmp(el->Value(),"Vector")==0){
		TiXmlElement* sub = el->FirstChildElement();
		vector<Variant> ret ;
		while (sub!=0)
		{
			ret.push_back(getVarient(sub));
			sub=sub->NextSiblingElement();
		}
		return ret;
	}else if (strcmp(el->Value(),"List")==0)
	{
		TiXmlElement* sub = el->FirstChildElement();
		list<Variant> ret ;
		while (sub!=0)
		{
			ret.push_back(getVarient(sub));
			sub=sub->NextSiblingElement();
		}
		return ret;
	}else if(strcmp(el->Value(),"Map")==0){
		map<string,Variant> ret;
		TiXmlElement* sub = el->FirstChildElement();
		while (sub!=0)
		{
			string lab(sub->Value());
			ret[lab]=getVarient(sub->FirstChildElement());
			sub=sub->NextSiblingElement();
		}
		return ret;
	}else{
		return Variant();
	}
}

bool SerializationPlugin::deserialize( const std::string& path,Variant& v )
{
	//cout<<"deserialize "<<path<<endl;
	TiXmlDocument doc(path.c_str());
	bool ok = doc.LoadFile(path.c_str());
	if (ok)
	{
		TiXmlElement* el = doc.FirstChildElement();
		v = getVarient(el);
		return true;
	}else{
		return false;
	}
}

DECLARE_PLUGIN(SerializationPlugin);
