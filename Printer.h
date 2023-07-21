#pragma once

#include <iostream>

#include "Evaluator.h"

template<bool evalFirst>
class Printer : public Evaluator
{
public:
	Printer(const string& name): Evaluator(name) {}
	EVAL_BODY(Printer)
	{
		ObjectH ret;
		//the optimizer should optimize away this if, since it's based on a compile-time bool
		if(evalFirst)
		{
			string result;
			//evaluate first
			for(int i = 0; i < numVals() - 1; ++i)
				result += getParameter(i)->evalAsString();
			//store the last eval to be returned later
			ret = getParameter(numVals() - 1)->eval();
			result += ret->evalAsString();

			cout << result;

			return ret;
		}
		else
		{
			for(int i = 0; i < numVals() - 1; ++i)
			{
				cout << getParameter(i)->evalAsString();
			}
			ret = getParameter(numVals() - 1)->eval();
			cout << ret->evalAsString();
		}
		cout << endl;
		return ret;
	}
};

#define Print Printer<false>("Print")
#define EvalThenPrint Printer<true>("EvalThenPrint")