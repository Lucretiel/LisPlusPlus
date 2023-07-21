#pragma once

#include "Evaluator.h"

class Construct : public Evaluator
{
public:
	Construct(): Evaluator("Cons", 2, 2) {}
	EVAL_BODY(Construct)
	{
		ObjectH car = getParameter(0)->eval();
		ObjectH cdr = getParameter(1)->eval();
		return Pair(car, cdr).getHandle();
	}
};

#define Cons Construct()

template<int which>
class Getter : public Evaluator
{
public:
	Getter(const string& str): Evaluator(str, 1, 1) {}
	EVAL_BODY(Getter)
	{
		//TODO: investigate if there needs to be a second eval() call here
		return castTo<Pair>(getParameter(0)->eval())->get<which>();
	}
};

#define Car Getter<0>("Car")
#define Cdr Getter<1>("Cdr")