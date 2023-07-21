#pragma once

#include <memory>
#include <string>
#include <sstream>

#include "Exception.h"

using namespace std;

class Object;
typedef shared_ptr<Object> ObjectH;

class Object
{
private:
	weak_ptr<Object> self;
	string _name;
protected:
	template<class Derived>
	ObjectH cloneTemplate() const
	{
		ObjectH x(new Derived(*static_cast<const Derived* const>(this)));
		x->self = x;
		return x;
	}

public:
	Object(const string& name = ""):_name(name) {}

	virtual ~Object() {}

	virtual ObjectH eval()
	{
		return self.lock();
	}

	virtual ObjectH clone() const =0;
	ObjectH getHandle() const
	{
		ObjectH x = self.lock();
		if(x) return x;
		return clone();
	}

	virtual string evalAsString()
	{
		stringstream s;
		s << evalAsInt();
		return s.str();
	}

	virtual int evalAsInt() =0;

	virtual bool evalAsBool()
	{
		return static_cast<bool>(evalAsInt());
	}

	string name() const {return _name;}
};

#define CLONE(TYPE) \
	virtual ObjectH clone() const { return cloneTemplate<TYPE>(); } 

template<class T>
ObjectH castToObject(shared_ptr<T> obj) {return static_pointer_cast<Object>(obj);}

template<class A, class B>
shared_ptr<A> castTo(shared_ptr<B> obj) {return dynamic_pointer_cast<A>(obj);}