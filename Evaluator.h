#pragma once

#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "Objects.h"

//TODO: add explicit # of arguments, and associated exception
class Evaluator : public Object
{
private:
	vector<ObjectH> vals;

	int minArguments;
	int maxArguments;
protected:
	//TODO: make private. Consider refactoring eval and evalSpecific
	int mostRecentlyAccessedArgument;

	ObjectH getParameter(int index)
	{
		try
		{
			mostRecentlyAccessedArgument = index;
			return vals.at(index);
		}
		catch(out_of_range)
		{
			throw IndexException(index);
		}
	}
	int numVals() {return vals.size();}

	void checkNumVals()
	{
		if((minArguments ? numVals() >= minArguments : true) && (maxArguments ? numVals() <= maxArguments : true))
			return;
		throw NumArgumentsException(minArguments, maxArguments, numVals());
	}


public:
	Evaluator(const string& name, int minArguments = 1, int maxArguments = 0)
		:Object(name)
		,minArguments(minArguments)
		,maxArguments(maxArguments)
		,mostRecentlyAccessedArgument(0)
	{}

	virtual ~Evaluator(void)
	{}

	void addArgument(ObjectH next)
	{
		vals.push_back(next);
	}

	void clearArguments()
	{
		vals.clear();
	}

	Evaluator& operator,(const Object& next)
	{
		addArgument(next.getHandle());
		return *this;
	}

	Evaluator& operator,(int next)
	{
		addArgument(Value(next).getHandle());
		return *this;
	}

	Evaluator& operator,(const string& next)
	{
		addArgument(String(next).getHandle());
		return *this;
	}

	virtual int evalAsInt() override
	{
		return this->eval()->evalAsInt();
	}

	virtual string evalAsString() override
	{
		return this->eval()->evalAsString();
	}

};

#define EVAL_BODY(TYPE) \
	virtual ~##TYPE() {}\
	CLONE(TYPE) \
	virtual ObjectH eval() override \
	{\
		if(numVals() == 0)\
			return getHandle(); \
		try \
		{ \
			checkNumVals(); \
			return evalSpecific();\
		} \
		catch(EvalException& e) \
		{\
			e.addToStack(name(), mostRecentlyAccessedArgument);\
			throw;\
		}\
	}\
	ObjectH evalSpecific()

typedef shared_ptr<Evaluator> EvaluatorH;