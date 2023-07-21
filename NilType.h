#pragma once

#include "Object.h"

class NilType : public Object
{
public:
	static ObjectH nilHandle; //all nils are the same
	virtual ObjectH eval()
	{
		return nilHandle;
	}

	virtual ObjectH clone() const
	{
		return nilHandle;
	}

	virtual string evalAsString()
	{
		return "nil";
	}

	virtual int evalAsInt()
	{
		throw EvalException("Tried to eval nil as int");
	}

	virtual bool evalAsBool()
	{
		return false;
	}

	static bool isNil(ObjectH obj)
	{
		return obj == nilHandle;
	}

};

#define nil NilType()