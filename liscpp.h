#pragma once

#include "Evaluators.h"

void ReadEvalPrint(Object& eval)
{
	try
	{
		cout << "==>" << eval.evalAsString() << endl;
	}
	catch(EvalException& e)
	{
		cout << "\nError:\n" << e.error << "\nCall Stack:\n";
		for(auto& frame : e.callStack)
		{
			cout << frame.first << ", argument " << frame.second << '\n';
		}

	}
	int x;
	x = cin.get();
}

void Evaluate(Object& eval)
{
	eval.eval();
}

int EvaluateInt(Object& eval)
{
	return eval.evalAsInt();
}

string EvaluateString(Object& eval)
{
	return eval.evalAsString();
}

vector<ObjectH> evaluateVec(Object& eval)
{
	ObjectH list = eval.eval();

	vector<ObjectH> ret;
	while(!NilType::isNil(list))
	{
		shared_ptr<Pair> p = castTo<Pair>(list);
		ret.push_back(p->get<0>());
		list = p->get<1>();
	}

	return ret;
}

vector<int> convertToInt(const vector<ObjectH>& vec)
{
	vector<int> ret(vec.size());

	transform(vec.begin(), vec.end(), ret.begin(), [](ObjectH obj){ return obj->evalAsInt();});
	return ret;
}

vector<string> convertToString(const vector<ObjectH>& vec)
{
	vector<string> ret(vec.size());

	transform(vec.begin(), vec.end(), ret.begin(), [](ObjectH obj){ return obj->evalAsString();});
	return ret;
}