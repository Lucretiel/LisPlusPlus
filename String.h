#pragma once

#include "Object.h"

class String : public Object
{
private:
	string val;
public:
	typedef string valueType;
	String(const string& x): val(x) {}
	string evalAsString()
	{
		return val;
	}

	int evalAsInt()
	{
		throw EvalException("Tried to eval string as int");
	}

	bool evalAsBool()
	{
		return true;
	}

	CLONE(String)
};
