#pragma once

#include <iostream>
#include "Evaluator.h"

template<class ObjectType>
class Reader : public Evaluator
{
public:
	Reader(const string& name): Evaluator(name, 1, 1) {}
	EVAL_BODY(Reader)
	{
		cout << getParameter(0)->evalAsString();
		ObjectType::valueType val;
		cin >> val;
		return ObjectType(val).getHandle();
	}
};


#define ReadInt Reader<Value>("ReadInt")
#define ReadString Reader<String>("ReadString")