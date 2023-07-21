#pragma once

#include <functional>
#include <iostream>

#include "Object.h"

//implemented as an object, as it 
class Behavior : public Object
{
private:
	function<void ()> func;
public:
	Behavior(const string& str, function<void ()> func)
		:Object(str)
		,func(func)
	{}

	CLONE(Behavior)

	ObjectH eval()
	{
		func();
		return Object::eval(); //returns itself
	}

	virtual string evalAsString()
	{
		eval();
		return ""; //allows behaviors to be embdedded in prints
	}

	virtual int evalAsInt()
	{
		eval();
		throw EvalException("Tried to eval Behavior as int", name(), 0);
	}

	virtual bool evalAsBool()
	{
		eval();
		return true;
	}
};

#define Pause Behavior("Pause", [](){int x; x = cin.get();})