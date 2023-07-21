#pragma once

#include <stack>

#include "BindBackend.h"
#include "Evaluator.h"


class LambdaObject : public Evaluator
{
private:
	vector<ObjectH> bindings;
	ObjectH obj;

	//Creation details
	friend class LambdaDeclarator;
	LambdaObject(int numArgs, int id) : Evaluator("LambdaObject", numArgs, numArgs), id(id)
	{} //only LambdaDeclarators can create new Lambdas

	//Scoping details
	const int id;
	static stack<int> lambdaStack;
	
public:
	EVAL_BODY(LambdaObject)
	{
		while(true)
		{
			bind::StackFrame thisFrame;
			for(unsigned i = 0; i < bindings.size(); ++i)
			{
				thisFrame.bind(bindings[i], getParameter(i));
			}

			return obj->eval();
		}
	}
};

class LambdaDeclarator : public Evaluator
{
private:
	static int numDistinctLambdas;
	const int id;
public:
	LambdaDeclarator() : Evaluator("Lambda"), id(++numDistinctLambdas)
	{}
	EVAL_BODY(LambdaDeclarator)
	{
		LambdaObject lambda(numVals() - 1, id);
		for(int i = 0; i < numVals() - 1; ++i)
		{
			lambda.bindings.push_back(getParameter(i));
		}
		lambda.obj = getParameter(numVals() - 1);
		
		return lambda.getHandle();
	}
};

#define Lambda LambdaDeclarator()

/*
Invoker allows for inplace lambda invocations.
It prevenets ((Lambda, tok(x), (Add, tok(x), 5)), 5) from
being parsed to (Lambda, tok(x), (Add, tok(x), 5), 5) by
providing an explicit function call: (Call, (Lambda, tok(x), (Add, tok(x), 5)), 5)
*/

class Invoker : public Evaluator
{
public:
	Invoker() : Evaluator("Call")
	{}
	EVAL_BODY(Invoker)
	{
		auto func = castTo<Evaluator>(getParameter(0));
		for(int i = 1; i < numVals(); ++i)
			func->addArgument(getParameter(i));

		ObjectH result = func->eval();
		func->clearArguments();
		return result;
	}
};

#define Call Invoker()
