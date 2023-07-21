#pragma once

#include <string>
#include <vector>

#include "Object.h"

using namespace std;

namespace bind
{
	class StackFrame
	{
	private:
		vector<string> bindings;
	public:
		~StackFrame();
		void bind(ObjectH tok, ObjectH obj);
		void bind(const string& name, ObjectH obj);
	};

	ObjectH get(const string& str);
}