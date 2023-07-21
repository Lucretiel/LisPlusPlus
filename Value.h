#pragma once

#include "Object.h"

class Value : public Object
{
private:
	int val;
public:
	typedef int valueType;
	Value(int x): val(x) {}

	int evalAsInt() {return val;}

	CLONE(Value)
};