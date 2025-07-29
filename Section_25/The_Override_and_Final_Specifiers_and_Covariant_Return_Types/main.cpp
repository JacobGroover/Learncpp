/*
Covariant return types

There is one special case in which a derived class virtual function override can have a different return type
than the base class and still be considered a matching override. If the return type of a virtual function is a
pointer or a reference to some class, override functions can return a pointer or a reference to a derived class.
These are called covariant return types. Here is an example:
 */

#include <iostream>
#include <string_view>

class Base
{
public:
	// This version of getThis() returns a pointer to a Base class
	virtual Base* getThis() { std::cout << "called Base::getThis()\n"; return this; }
	void printType() { std::cout << "returned a Base\n"; }
};

class Derived : public Base
{
public:
	// Normally override functions have to return objects of the same type as the base function
	// However, because Derived is derived from Base, it's okay to return Derived* instead of Base*
	Derived* getThis() override { std::cout << "called Derived::getThis()\n";  return this; }
	void printType() { std::cout << "returned a Derived\n"; }
};

int main()
{
	Derived d{};
	Base* b{ &d };
	d.getThis()->printType(); // calls Derived::getThis(), returns a Derived*, calls Derived::printType
	b->getThis()->printType(); // calls Derived::getThis(), returns a Base*, calls Base::printType

	return 0;
}

/*
One interesting note about covariant return types: C++ can’t dynamically select types, so you’ll always get the type
that matches the actual version of the function being called.

In the above example, we first call d.getThis(). Since d is a Derived, this calls Derived::getThis(), which returns a
Derived*. This Derived* is then used to call non-virtual function Derived::printType().

Now the interesting case. We then call b->getThis(). Variable b is a Base pointer to a Derived object. Base::getThis()
is a virtual function, so this calls Derived::getThis(). Although Derived::getThis() returns a Derived*, because Base
version of the function returns a Base*, the returned Derived* is upcast to a Base*. Because Base::printType() is
non-virtual, Base::printType() is called.

In other words, in the above example, you only get a Derived* if you call getThis() with an object that is typed as
a Derived object in the first place.

Note that if printType() were virtual instead of non-virtual, the result of b->getThis() (an object of type Base*)
would have undergone virtual function resolution, and Derived::printType() would have been called.

Covariant return types are often used in cases where a virtual member function returns a pointer or reference to the
class containing the member function (e.g. Base::getThis() returns a Base*, and Derived::getThis() returns a Derived*).
However, this isn’t strictly necessary. Covariant return types can be used in any case where the return type of the
override member function is derived from the return type of the base virtual member function.
 */