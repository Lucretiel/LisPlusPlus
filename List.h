#pragma once

#include <exception>
#include <array>

#include "Object.h"
#include "NilType.h"

class Pair : public Object
{
	array<ObjectH, 2> items;

	string noParenthesis()
	{
		string str = get<0>()->evalAsString();
		if(NilType::isNil(get<1>()))
			return str;

		try
		{
			Pair* try_cdr = cdrList();
			str += ',' + try_cdr->noParenthesis();
		}
		catch(bad_cast&)
		{
			str += '.' + get<1>()->evalAsString();
		}
		return str;
	}

	Pair* cdrList() {return dynamic_cast<Pair*>(get<1>().get());}
public:
	Pair(ObjectH car, ObjectH cdr)
	{
		items[0] = car;
		items[1] = cdr;
	}

	template<unsigned which>
	ObjectH get() {return items.at(which);}

	template<>
	ObjectH get<0>() {return items[0];}

	template<>
	ObjectH get<1>() {return items[1];}

	CLONE(Pair);

	virtual string evalAsString()
	{
		return '(' + noParenthesis() + ')';
	}

	virtual int evalAsInt()
	{
		throw EvalException("Tried to eval Pair as int");
	}

	virtual bool evalAsBool()
	{
		return true;
	}

	static ObjectH makePair(ObjectH car, ObjectH cdr)
	{

	}

};
