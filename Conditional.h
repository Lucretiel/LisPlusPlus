#pragma once

#include <functional>

#include "Evaluator.h"

class Conditional : public Evaluator
{
	function<bool (ObjectH, ObjectH)> func;
public:
	Conditional(function<bool (ObjectH, ObjectH)> x, string name): Evaluator(name), func(x) {}

	EVAL_BODY(Conditional)
	{
		//TODO: implement short-circuits
		bool val = true;
		ObjectH prev = getParameter(0)->eval();
		for(int i = 1; i < numVals(); ++i)
		{
			ObjectH next = getParameter(i)->eval();
			val = val && func(prev, next);
			prev = next;
		}

		return Value(val).getHandle();
	}

	static bool less(ObjectH lhs, ObjectH rhs)
	{
		return lhs->evalAsInt() < rhs->evalAsInt();
	}
	static bool greater(ObjectH lhs, ObjectH rhs)
	{
		return lhs->evalAsInt() > rhs->evalAsInt();
	}
	static bool equal(ObjectH lhs, ObjectH rhs)
	{
		return lhs->evalAsInt() == rhs->evalAsInt();
	}
	static bool notEqual(ObjectH lhs, ObjectH rhs)
	{
		return lhs->evalAsInt() != rhs->evalAsInt();
	}
	static bool lessEqual(ObjectH lhs, ObjectH rhs)
	{
		return lhs->evalAsInt() <= rhs->evalAsInt();
	}
	static bool greaterEqual(ObjectH lhs, ObjectH rhs)
	{
		return lhs->evalAsInt() >= rhs->evalAsInt();
	}
};

#define Less Conditional(&Conditional::less, "Less")
#define Greater Conditional(&Conditional::greater, "Greater")
#define Equal Conditional(&Conditional::equal, "Equal")
#define NotEqual Conditional(&Conditional::notEqual, "NotEqual")
#define LessEqual Conditional(&Conditional::lessEqual, "LessEqual")
#define GreaterEqual Conditional(&Conditional::greaterEqual, "GreaterEqual")