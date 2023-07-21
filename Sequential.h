#pragma once

#include "Evaluator.h"

class Sequential : public Evaluator
{
public:
	Sequential(): Evaluator("Do") {}
	EVAL_BODY(Sequential)
	{
		for(int i = 0; i < numVals() - 1; ++i)
		{
			getParameter(i)->eval();
		}
		return getParameter(numVals() - 1);
	}
};

#define Do Sequential();
