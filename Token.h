#pragma once

#include "Evaluator.h"
#include "BindBackend.h"

class Token : public Evaluator
{
public:
	Token(const string& x): Evaluator(x) {}

	virtual ~Token() {}

	CLONE(Token);

	ObjectH eval() override
	{
		if(numVals() == 0)
			return bind::get(name());

		EvaluatorH func = castTo<Evaluator>(bind::get(name())->clone());
		for(int i = 0; i < numVals(); ++i)
			func->addArgument(getParameter(i));

		try
		{
			return func->eval();
		}
		catch(EvalException& e)
		{
			e.addToStack(name(), 0);
			throw;
		}

	}
};

//TODO: user-defined literal implementation
#define tok(a) Token(#a)
