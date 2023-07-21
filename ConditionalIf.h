#pragma once

#include "Evaluator.h"

class ConditionalIf : public Evaluator
{
public:
	ConditionalIf(): Evaluator("If", 3, 3) {}
	EVAL_BODY(ConditionalIf)
	{
		if(getParameter(0)->evalAsBool())
			return getParameter(1)->eval();
		return getParameter(2)->eval();
	}
};

#define If ConditionalIf()