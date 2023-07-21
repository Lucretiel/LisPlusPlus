#pragma once

#include "Evaluator.h"

class ListBuilder : public Evaluator
{
private:
	ObjectH buildListFrom(int index)
	{
		if(index == numVals())
			return NilType::nilHandle;
		ObjectH car = getParameter(index)->eval();
		ObjectH cdr = buildListFrom(index + 1);

		return Pair(car, cdr).getHandle();
	}

public:
	ListBuilder(): Evaluator("List") {}
	EVAL_BODY(ListBuilder)
	{
		return buildListFrom(0);
	}
};

#define List ListBuilder()