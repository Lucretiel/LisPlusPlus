#pragma once

#include "Evaluator.h"

class ConditionalSwitch : public Evaluator
{
public:
	ConditionalSwitch() : Evaluator("Cond") {}
	EVAL_BODY(ConditionalSwitch)
	{
		for(int i = 0; i < numVals() - 1; i += 2)
		{
			if(getParameter(i)->evalAsBool())
				return getParameter(i + 1)->eval();
		}
		return getParameter(numVals() - 1)->eval();
	}

};

#define Cond ConditionalSwitch()