#pragma once

#include <functional>

#include "Evaluator.h"

class Tester : public Evaluator
{
private:
	function<ObjectH (ObjectH)> func;
public:
	Tester(function<ObjectH (ObjectH)> func, const string& name)
		:Evaluator(name, 1, 1)
		,func(func)
	{}
	EVAL_BODY(Tester)
	{
		return func(getParameter(0));
	}

	static ObjectH nilTest(ObjectH obj)
	{
		return Value(static_cast<int>(obj->eval() == NilType::nilHandle)).getHandle();
	}
};

#define IsNil Tester(&Tester::nilTest, "isNil")