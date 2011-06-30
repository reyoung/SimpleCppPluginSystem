#pragma once
#include "Castable.h"
#include <string>
#include <vector>
#include <list>
#include <map>

class ExtentionSystem_DLL_API Variant:public Castable
{
public:
	enum Type{
		ComplexType=(1<<31),
		Invalid=0,
		Char = 1,
		Int = 2,
		Short=3,
		Long = 4,
		LongLong = 5,
		Float = 6,
		Double = 7,
//! Complex Type (STD)
		String = 8|ComplexType,
		Vector = 9 |ComplexType,
		List = 10|ComplexType,
		Map = 11|ComplexType,
	};

	Variant(void);
	virtual ~Variant(void);
	
	Variant(const int & i);
	Variant& operator = (const int & i);
	int toInt(bool* ok=0,int default_value =0)const;

	Variant(const char& c);
	Variant& operator = (const char& c);
	char toChar(bool* ok=0,char default_char = 0)const;

	Variant(const short& s);
	Variant& operator = (const short& s);
	short toShort(bool* ok=0,short default_short = 0)const;

	Variant(const long& l);
	Variant& operator = (const long& l);
	long toLong(bool* ok=0,long default_long = 0)const ;

	Variant(const long long & ll);
	Variant& operator = (const long long & ll);
	long long toLongLong(bool* ok=0,long long default_longlong=0)const;

	Variant(const float & f);
	Variant& operator = (const float & f);
	float toFloat(bool* ok=0,float default_float = 0)const;

	Variant(const double& d);
	Variant& operator = (const double& d);
	double toDouble(bool* ok=0,double default_double = 0)const;

	Variant(const std::string& str);
	Variant& operator = (const std::string& str);
	std::string toString(bool* ok=0,const std::string& default_str="")const;

	Variant(const std::vector<Variant>& vec);
	Variant& operator = (const std::vector<Variant>& vec);
	std::vector<Variant> toVector(bool* ok=0)const;

	Variant(const std::list<Variant>& li);
	Variant& operator = (const std::list<Variant>& li);
	std::list<Variant> toList(bool* ok=0)const;

	Variant(const std::map<std::string,Variant>& mp);
	Variant& operator = (const std::map<std::string,Variant>& mp);
	std::map<std::string,Variant> toMap(bool* ok)const;

	inline Type getType()const{
		return m_type;
	}

	inline bool isComplexType()const{
		return m_type&ComplexType;
	}

	inline bool isValid()const{
		return m_type!=Invalid;
	}

private:
	union __PrivateUnoin{
		char c;
		int i;
		short s;
		long l;
		long long ll;
		float f;
		double d;
		void* ptr;
	};
	Type m_type;
	__PrivateUnoin m_data;

	void freeComplexType();
};
