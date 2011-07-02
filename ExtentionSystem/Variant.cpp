#include "Variant.h"

using namespace std;

#define CheckAndFreeComplex()\
	if (isComplexType())\
	{\
		freeComplexType();\
	}


Variant::Variant(void)
{
	m_type = Invalid;
}

Variant::Variant( const int & i )
{
	m_type = Invalid;
	this->operator =(i);
}

Variant::Variant( const char& c )
{
	m_type=Invalid;
	this->operator =(c);
}

Variant::Variant( const short& s )
{
	m_type=Invalid;
	this->operator =(s);
}

Variant::Variant( const long& l )
{
	m_type=Invalid;
	this->operator =(l);
}

Variant::Variant( const long long & ll )
{
	m_type=Invalid;
	this->operator =(ll);
}

Variant::Variant( const float & f )
{
	m_type=Invalid;
	this->operator =(f);
}

Variant::Variant( const double& d )
{
	m_type=Invalid;
	this->operator =(d);
}

Variant::Variant( const std::string& str )
{
	m_type=Invalid;
	this->operator =(str);
}

Variant::Variant( const std::vector<Variant>& vec )
{
	m_type=Invalid;
	this->operator =(vec);
}

Variant::Variant( const std::list<Variant>& li )
{
	m_type=Invalid;
	this->operator =(li);
}

Variant::Variant( const std::map<std::string,Variant>& mp )
{
	m_type=Invalid;
	this->operator =(mp);
}

Variant::Variant( const bool& b )
{
	m_type=Invalid;
	this->operator =(b);
}

Variant::Variant( const char* str )
{
	m_type=Invalid;
	this->operator =(string(str));
}

Variant::Variant( const Variant& other )
{
	m_type=Invalid;
	this->operator =(other);
}

Variant::~Variant(void)
{
	CheckAndFreeComplex();
}

Variant& Variant::operator=( const int & i )
{
	CheckAndFreeComplex();
	m_data.i=i;
	m_type = Int;
	return *this;
}

Variant& Variant::operator=( const char& c )
{
	CheckAndFreeComplex();
	m_data.c = c;
	m_type = Char;
	return *this;
}

Variant& Variant::operator=( const short& s )
{
	CheckAndFreeComplex();
	m_data.s = s;
	m_type = Short;
	return *this;
}

Variant& Variant::operator=( const long& l )
{
	CheckAndFreeComplex();
	m_data.l = l;
	m_type = Long;
	return *this;
}

Variant& Variant::operator=( const long long & ll )
{
	CheckAndFreeComplex();
	m_data.ll=ll;
	m_type = LongLong;
	return *this;
}

Variant& Variant::operator=( const float & f )
{
	CheckAndFreeComplex();
	m_data.f = f;
	m_type = Float;
	return *this;
}

Variant& Variant::operator=( const double& d )
{
	CheckAndFreeComplex();
	m_data.d = d;
	m_type = Double;
	return *this;
}

Variant& Variant::operator=( const std::string& str )
{
	CheckAndFreeComplex();
	m_data.ptr = new string(str);
	m_type = String;
	return *this;
}

Variant& Variant::operator=( const std::vector<Variant>& vec )
{
	CheckAndFreeComplex();
	m_data.ptr = new vector<Variant>(vec);
	m_type = Vector;
	return *this;
}

Variant& Variant::operator=( const std::list<Variant>& li )
{
	CheckAndFreeComplex();
	m_data.ptr = new list<Variant>(li);
	m_type = List;
	return *this;
}

Variant& Variant::operator=( const std::map<std::string,Variant>& mp )
{
	CheckAndFreeComplex();
	m_data.ptr = new map<string,Variant>(mp);
	m_type = Map;
	return *this;
}

Variant& Variant::operator=( const bool& b )
{
	CheckAndFreeComplex();
	m_data.b = b;
	m_type = Bool;
	return *this;
}

Variant& Variant::operator=( const Variant& other )
{
	m_type=Invalid;
	if (other.isComplexType())
	{
		switch(other.m_type){
			case String:
				this->operator =(other.toString());
				break;
			case Vector:
				this->operator =(other.toVector());
				break;
			case Map:
				this->operator =(other.toMap());
				break;
			case List:
				this->operator =(other.toList());
				break;
		}
	}else{
			m_data = other.m_data;
	}
	m_type  = other.m_type;
	return *this;
}

void Variant::freeComplexType()
{
	switch (getType())
	{
	case String:
		delete (string*) m_data.ptr;
		break;
	case Vector:
		delete (vector<Variant>* )m_data.ptr;
		break;
	case List:
		delete (list<Variant>* )m_data.ptr;
		break;
	case Map:
		delete (map<string,Variant>* )m_data.ptr;
		break;
	}
}

int Variant::toInt( bool* ok/*=0*/,int default_value /*=0*/ ) const
{
	if (getType()==Int)
	{
		if (ok)
		{
			*ok=true;
		}
		return m_data.i;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return default_value;
	}
}

char Variant::toChar( bool* ok/*=0*/,char default_char /*= 0*/ ) const
{
	if (getType()==Char)
	{
		if (ok)
		{
			*ok=true;
		}
		return m_data.c;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return default_char;
	}
}

short Variant::toShort( bool* ok/*=0*/,short default_short /*= 0*/ ) const
{
	if (getType()==Short)
	{
		if (ok)
		{
			*ok=true;
		}
		return m_data.s;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return default_short;
	}
}

long Variant::toLong( bool* ok/*=0*/,long default_long /*= 0*/ ) const
{
	if (getType()==Long)
	{
		if (ok)
		{
			*ok=true;
		}
		return m_data.l;
	}else{
		if (ok)
		{
			ok=false;
		}
		return default_long;
	}
}

long long Variant::toLongLong( bool* ok/*=0*/,long long default_longlong/*=0*/ ) const
{
	if (getType()==LongLong)
	{
		if (ok)
		{
			*ok=true;
		}
		return m_data.ll;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return default_longlong;
	}
}

float Variant::toFloat( bool* ok/*=0*/,float default_float /*= 0*/ ) const
{
	if (getType()==Float)
	{
		if (ok)
		{
			*ok=true;
		}
		return m_data.f;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return default_float;
	}
}

double Variant::toDouble( bool* ok/*=0*/,double default_double /*= 0*/ ) const
{
	if (getType()==Double)
	{
		if (ok)
		{
			*ok=true;
		}
		return m_data.d;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return default_double;
	}
}

std::string Variant::toString( bool* ok/*=0*/,const std::string& default_str/*=""*/ ) const
{
	if (getType()==String)
	{
		if (ok)
		{
			*ok=true;
		}
		return *(string *)m_data.ptr;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return default_str;
	}
}

std::vector<Variant> Variant::toVector( bool* ok/*=0*/ ) const
{
	if (getType()==Vector)
	{
		if (ok)
		{
			*ok=true;
		}
		return *(vector<Variant>* )(m_data.ptr);
	}else{
		if (ok)
		{
			*ok=false;
		}
		return vector<Variant>();
	}
}

std::list<Variant> Variant::toList( bool* ok/*=0*/ ) const
{
	if (getType()==List){
		if (ok)
		{
			*ok=true;
		}
		return *(list<Variant>*)m_data.ptr;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return list<Variant>();
	}
}

std::map<std::string,Variant> Variant::toMap( bool* ok ) const
{
	if (getType()==Map)
	{
		if (ok)
		{
			*ok=true;
		}
		return *(map<string,Variant>*)(m_data.ptr);
	}else
	{
		if (ok)
		{
			*ok=false;
		}
		return map<string,Variant>();
	}
}

bool Variant::toBool( bool* ok/*=0*/,bool default_bool/*= false*/ )const
{
	if (getType()==Bool)
	{
		if (ok)
		{
			*ok=true;
		}
		return m_data.b;
	}else{
		if (ok)
		{
			*ok=false;
		}
		return default_bool;
	}
}

std::map<std::string,Variant>* Variant::mapPtr() const
{
	if (getType()==Variant::Map)
	{
		return (std::map<std::string,Variant>*)m_data.ptr;
	}else{
		return 0;
	}
}

