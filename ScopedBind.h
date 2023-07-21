#pragma once

#include <vector>

#include "BindBackend.h"
#include "Evaluator.h"

class ScopedBind : public Evaluator
{
public:
	ScopedBind(): Evaluator("Let")
	{}
	EVAL_BODY(ScopedBind)
	{
		bind::StackFrame thisFrame;
		for(int i = 0; i < numVals() - 1; i += 2)
		{
			thisFrame.bind(getParameter(i), getParameter(i+1));
		}

		return getParameter(numVals()-1)->eval();
	}
};

#define Let ScopedBind()