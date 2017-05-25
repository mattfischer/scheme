#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <string>
#include <vector>

class ObjectPool;

class Object {
public:
	enum Type {
		TypeNone,
		TypeBool,
		TypeInt,
		TypeString,
		TypeSymbol,
		TypeCons,
		TypeLambda,
		TypeNativeFunction
	};

	struct Cons {
		Object *car;
		Object *cdr;
	};

	struct Lambda {
		std::vector<std::string> variables;
		Object *body;
	};

	typedef Object *(*NativeFunction)(Object*, ObjectPool*);

	Type type() const;

	void setNone();
	void setBool(bool value);
	void setInt(int value);
	void setString(const std::string &value);
	void setSymbol(const std::string &value);
	void setCons(Object *car, Object *cdr);
	void setLambda(std::vector<std::string> &&variables, Object *body);
	void setNativeFunction(NativeFunction nativeFunction);

	int intValue() const;
	bool boolValue() const;
	const std::string &stringValue() const;
	const Cons &consValue() const;
	const Lambda &lambdaValue() const;
	NativeFunction nativeFunctionValue() const;

	void dispose();

private:
	Type mType;

	union {
		int intValue;
		bool boolValue;
		std::string *stringValue;
		Cons consValue;
		Lambda *lambdaValue;
		NativeFunction nativeFunctionValue;
	} mData;
};

#endif