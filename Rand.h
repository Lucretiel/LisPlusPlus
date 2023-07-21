#pragma once
#include <random>

#include "Evaluator.h"

class RandInt : public Evaluator
{
	//TODO: make static, possibly
private:
	mt19937 engine;
public:
	RandInt(): Evaluator("Rand", 2, 2) {}
	EVAL_BODY(RandInt)
	{
		static uniform_int_distribution<int> dist(getParameter(0)->evalAsInt(), getParameter(1)->evalAsInt());
		return Value(dist(engine)).getHandle();
	}
};

#define Rand RandInt()
