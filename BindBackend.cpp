#include "BindBackend.h"

#include <unordered_map>
#include <list>
#include <utility>
#include <algorithm>

#include "Token.h"

using namespace std;

namespace bind
{
	typedef unordered_map<string, ObjectH> bindTable;
	bindTable activeBindings;
	list<bindTable::value_type> bindStack;

	const string& bind(const string& str, ObjectH obj)
	{
		auto item = activeBindings.find(str);
		if(item != activeBindings.end())
			bindStack.push_front(*item);
		activeBindings[str] = obj->eval();
		return str;
	}

	void unbind(const string& str)
	{
  		activeBindings.erase(str);
		auto item = find_if(bindStack.begin(), bindStack.end(), [&str](bindTable::value_type& item)
		{
			return item.first == str;
		});

		if(item != bindStack.end())
		{
			activeBindings.insert(*item);
			bindStack.erase(item);
		}
	}

	ObjectH get(const string& str)
	{
		try
		{
			return activeBindings.at(str);
		}
		catch(out_of_range&)
		{
			throw TokenException(str);
		}

	}

	StackFrame::~StackFrame()
	{
		for(auto& name : bindings)
			unbind(name);
	}

	void StackFrame::bind(ObjectH token, ObjectH object)
	{
		auto tok = castTo<Token>(token);
		bind(tok->name(), object);
	}

	void StackFrame::bind(const string& name, ObjectH object)
	{
		bindings.push_back(bind::bind(name, object));
	}


}
