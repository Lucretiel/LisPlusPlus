#pragma once

#include <functional>

#include "Evaluator.h"

class Accumulator : public Evaluator
{
	function<ObjectH (ObjectH, ObjectH)> func;
public:
	Accumulator(function<ObjectH (ObjectH, ObjectH)> x, string name): Evaluator(name), func(x) {}

	EVAL_BODY(Accumulator)
	{
		ObjectH obj = getParameter(0);
		for(int i = 1; i < numVals(); ++i)
			obj = func(obj, getParameter(i));

		return obj;
	}

	static ObjectH add(ObjectH lhs, ObjectH rhs)
	{
		return Value(lhs->evalAsInt() + rhs->evalAsInt()).getHandle();
	}
	static ObjectH sub(ObjectH lhs, ObjectH rhs)
	{
		return Value(lhs->evalAsInt() - rhs->evalAsInt()).getHandle();
	}
	static ObjectH mult(ObjectH lhs, ObjectH rhs)
	{
		return Value(lhs->evalAsInt() * rhs->evalAsInt()).getHandle();
	}
	static ObjectH div(ObjectH lhs, ObjectH rhs)
	{
		return Value(lhs->evalAsInt() / rhs->evalAsInt()).getHandle();
	}

	static ObjectH and(ObjectH lhs, ObjectH rhs)
	{
		return Value(lhs->evalAsBool() && rhs->evalAsBool()).getHandle();
	}
	static ObjectH or(ObjectH lhs, ObjectH rhs)
	{
		return Value(lhs->evalAsBool() || rhs->evalAsBool()).getHandle();
	}
};

#define Add Accumulator(&Accumulator::add, "Add")
#define Sub Accumulator(&Accumulator::sub, "Sub")
#define Mult Accumulator(&Accumulator::mult, "Mult")
#define Div Accumulator(&Accumulator::div, "Div")
#define And Accumulator(&Accumulator::and, "And")
#define Or Accumulator(&Accumulator::or, "Or")