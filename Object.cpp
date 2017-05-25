#include "Object.hpp"

#include <string.h>

Object::Type Object::type() const
{
	return mType;
}

void Object::setNone()
{
	mType = TypeNone;
}

void Object::setBool(bool value)
{
	mType = TypeBool;
	mData.boolValue = value;
}

void Object::setInt(int value)
{
	mType = TypeInt;
	mData.intValue = value;
}

void Object::setString(const std::string &value)
{
	mType = TypeString;
	mData.stringValue = new std::string(value);
}

void Object::setAtom(const std::string &value)
{
	mType = TypeAtom;
	mData.stringValue = new std::string(value);
}

void Object::setCons(Object *car, Object *cdr)
{
	mType = TypeCons;
	mData.consValue.car = car;
	mData.consValue.cdr = cdr;
}

void Object::setLambda(std::vector<std::string> &&variables, Object *body)
{
	mType = TypeLambda;
	
	Lambda *lambda = new Lambda;
	lambda->variables = std::move(variables);
	lambda->body = body;

	mData.lambdaValue = lambda;
}

void Object::setNativeFunction(NativeFunction nativeFunction)
{
	mType = TypeNativeFunction;
	mData.nativeFunctionValue = nativeFunction;
}

int Object::intValue() const
{
	return mData.intValue;
}

bool Object::boolValue() const
{
	return mData.boolValue;
}

const std::string &Object::stringValue() const
{
	return *mData.stringValue;
}

const Object::Cons &Object::consValue() const
{
	return mData.consValue;
}

const Object::Lambda &Object::lambdaValue() const
{
	return *mData.lambdaValue;
}

Object::NativeFunction Object::nativeFunctionValue() const
{
	return mData.nativeFunctionValue;
}

void Object::dispose()
{
	switch (mType) {
	case TypeString:
	case TypeAtom:
		delete mData.stringValue;
		break;

	case TypeLambda:
		delete mData.lambdaValue;
		break;

	default:
		break;
	}
}