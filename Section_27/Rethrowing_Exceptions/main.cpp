// When rethrowing the same exception, use the throw keyword by itself

/*
Rethrowing an exception (the right way)

Fortunately, C++ provides a way to rethrow the exact same exception as the one that was just caught.
To do so, simply use the throw keyword from within the catch block (with no associated variable), like so:
 */

#include <iostream>
class Base
{
public:
	Base() {}
	virtual void print() { std::cout << "Base"; }
};

class Derived: public Base
{
public:
	Derived() {}
	void print() override { std::cout << "Derived"; }
};

int main()
{
	try
	{
		try
		{
			throw Derived{};
		}
		catch (Base& b)
		{
			std::cout << "Caught Base b, which is actually a ";
			b.print();
			std::cout << '\n';
			throw; // note: We're now rethrowing the object here
		}
	}
	catch (Base& b)
	{
		std::cout << "Caught Base b, which is actually a ";
		b.print();
		std::cout << '\n';
	}

	return 0;
}