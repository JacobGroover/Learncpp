/*
#include <iostream>

class Something
{
private:
	static inline int s_value { 1 };

public:
	static int getValue() { return s_value; } // static member function
};

int main()
{
	std::cout << Something::getValue() << '\n';
}
 */

// Static member functions can also be defined outside of the class declaration. This works the same way as for normal member functions.

#include <iostream>

class IDGenerator
{
private:
	static inline int s_nextID { 1 };

public:
	static int getNextID(); // Here's the declaration for a static function
};

// Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
int IDGenerator::getNextID() { return s_nextID++; }

int main()
{
	for (int count{ 0 }; count < 5; ++count)
		std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';

	return 0;
}

/*
A word of warning about classes with all static members

Be careful when writing classes with all static members. Although such “pure static classes” (also called “monostates”)
can be useful, they also come with some potential downsides.

First, because all static members are instantiated only once, there is no way to have multiple copies of a pure static
class (without cloning the class and renaming it). For example, if you needed two independent IDGenerator, this
would not be possible with a pure static class.

Second, in the lesson on global variables, you learned that global variables are dangerous because any piece of code
can change the value of the global variable and end up breaking another piece of seemingly unrelated code. The same
holds true for pure static classes. Because all of the members belong to the class (instead of object of the class),
and class declarations usually have global scope, a pure static class is essentially the equivalent of declaring
functions and global variables in a globally accessible namespace, with all the requisite downsides that global
variables have.

Instead of writing a class with all static members, consider writing a normal class and instantiating a global
instance of it (global variables have static duration). That way the global instance can be used when appropriate,
but local instances can still be instantiated if and when that is useful.

____________________________________________________________

Pure static classes have a lot of overlap with namespaces. Both allow you to define variables with static duration
and functions within their scope region. However, one significant difference is that classes have access controls while
namespaces do not.

In general, a static class is preferable when you have static data members and/or need access controls. Otherwise,
prefer a namespace.

____________________________________________________________

If you can initialize normal member variables via a constructor, then by extension it makes sense that you should be
able to initialize static member variables via a static constructor. And while some modern languages do support static
constructors for precisely this purpose, C++ is unfortunately not one of them.

If your static variable can be directly initialized, no constructor is needed: you can initialize the static member
variable at the point of definition (even if it is private). We do this in the IDGenerator example above.
Here’s another example:

#include <iostream>

struct Chars
{
	char first{};
	char second{};
	char third{};
	char fourth{};
	char fifth{};
};

struct MyClass
{
	static inline Chars s_mychars { 'a', 'e', 'i', 'o', 'u' }; // initialize static variable at point of definition
};

int main()
{
	std::cout << MyClass::s_mychars.third; // print i

	return 0;
}

If initializing your static member variable requires executing code (e.g. a loop), there are many different, somewhat
obtuse ways of doing this. One way that works with all variables, static or not, is to use a function to create an
object, fill it with data, and return it to the caller. This returned value can be copied into the object being
initialized. A lambda can also be used for this:

#include <iostream>

struct Chars
{
	char first{};
	char second{};
	char third{};
	char fourth{};
	char fifth{};
};

class MyClass
{
private:
	static Chars generate()
	{
		Chars c{}; // create an object
		c.first = 'a'; // fill it with values however you like
		c.second = 'e';
		c.third = 'i';
		c.fourth = 'o';
		c.fifth = 'u';

		return c; // return the object
	}

public:
	static inline Chars s_mychars { generate() }; // copy the returned object into s_mychars
};

int main()
{
	std::cout << MyClass::s_mychars.third; // print i

	return 0;
}

We show a practical example of this methodology in lesson 8.15 -- Global random numbers (Random.h)
(though we do it with a namespace rather than a static class, it works the same way)
 */