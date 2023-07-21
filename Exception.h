#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <utility>
using namespace std;

class EvalException
{
public:
	vector<pair<string, int>> callStack;
	string error;
public:
	explicit EvalException(const string& error, const string& startStack, int startArg)
		:error(error)
		,callStack(1, make_pair(startStack, startArg))
	{}

	explicit EvalException(const string& error = "")
		:error(error)
	{}

	void addToStack(const string& name, int startArg)
	{
		callStack.emplace_back(name, startArg);
	}
};

class IndexException : public EvalException
{
public:
	explicit IndexException(int index)
	{
		stringstream x;
		x << "Index error: index " << index;
		error = x.str();
	}
};

class TokenException : public EvalException
{
public:
	explicit TokenException(const string& token)
		:EvalException("Attempted to retrieve unbound token: " + token)
	{}
};

class NumArgumentsException : public EvalException
{
public:
	explicit NumArgumentsException(int min, int max, int got)
	{
		stringstream x;
		x << "Argument Error: Need ";
		if(min && max)
		{
			if(min == max)
				x << "exactly " << min;
			else
				x << "between " << min << " and " << max;
		}
		else if(min)
			x << "at least " << min;
		else if(max)
			x << "up to " << max;

		x << " arguments. Got " << got << " arguments\n";
		error = x.str();
	}

};
