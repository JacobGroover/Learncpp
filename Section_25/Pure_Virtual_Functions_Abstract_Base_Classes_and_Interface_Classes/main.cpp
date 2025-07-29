/*
 NOTE:
For consistency, abstract classes still have virtual tables. A constructor or destructor of an abstract class can
call a virtual function, and it needs to resolve to the proper function (in the same class, since the derived classes
either haven’t been constructed yet or have already been destroyed).

The virtual table entry for a class with a pure virtual function will generally either contain a null pointer, or
point to a generic function that prints an error (sometimes this function is named __purecall).
 */

/*
It turns out that we can create pure virtual functions that have definitions.

This paradigm can be useful when you want your base class to provide a default implementation for a function,
but still force any derived classes to provide their own implementation. However, if the derived class is happy
with the default implementation provided by the base class, it can simply call the base class implementation
directly. For example:
 */

#include <iostream>
#include <string>
#include <string_view>

class Animal // This Animal is an abstract base class
{
protected:
	std::string m_name {};

public:
	Animal(std::string_view name)
		: m_name(name)
	{
	}

	const std::string& getName() const { return m_name; }
	virtual std::string_view speak() const = 0; // note that speak is a pure virtual function

	virtual ~Animal() = default;
};

std::string_view Animal::speak() const
{
	return "buzz"; // some default implementation
}

class Dragonfly: public Animal
{

public:
	Dragonfly(std::string_view name)
		: Animal{name}
	{
	}

	std::string_view speak() const override// this class is no longer abstract because we defined this function
	{
		return Animal::speak(); // use Animal's default implementation
	}
};

int main()
{
	Dragonfly dfly{"Sally"};
	std::cout << dfly.getName() << " says " << dfly.speak() << '\n';

	return 0;
}

// A destructor can be made pure virtual, but must be given a definition so that it can be called when a derived object is destructed.

/*
An interface class is a class that has no member variables, and where all of the functions are pure virtual!
Interfaces are useful when you want to define the functionality that derived classes must implement, but leave
the details of how the derived class implements that functionality entirely up to the derived class.

Interface classes are often named beginning with an I. Here’s a sample interface class:
 */

#include <string_view>

class IErrorLog
{
public:
	virtual bool openLog(std::string_view filename) = 0;
	virtual bool closeLog() = 0;

	virtual bool writeError(std::string_view errorMessage) = 0;

	virtual ~IErrorLog() {} // make a virtual destructor in case we delete an IErrorLog pointer, so the proper derived destructor is called
};