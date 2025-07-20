// Access static members using the class name and the scope resolution operator (::).

// Make your static members inline or constexpr so they can be initialized inside the class definition.

// Why use static variables inside classes? One use is to assign a unique ID to every instance of the class.
// Here’s an example:

#include <iostream>

class Something
{
private:
	static inline int s_idGenerator { 1 };
	int m_id {};

public:
	// grab the next value from the id generator
	Something() : m_id { s_idGenerator++ }
	{
	}

	int getID() const { return m_id; }
};

int main()
{
	Something first{};
	Something second{};
	Something third{};

	std::cout << first.getID() << '\n';
	std::cout << second.getID() << '\n';
	std::cout << third.getID() << '\n';
	return 0;
}

/*
Static member variables are also useful when the class needs to utilize a lookup table
(e.g. an array used to store a set of pre-calculated values). By making the lookup table static,
only one copy exists for all objects, rather than making a copy for each object instantiated.
This can save substantial amounts of memory.
 */

/*
Note that this static member definition is not subject to access controls: you can define and initialize the value
even if it’s declared as private (or protected) in the class (as definitions are not considered to be a form of access).

For non-template classes, if the class is defined in a header (.h) file, the static member definition is usually
placed in the associated code file for the class (e.g. Something.cpp). Alternatively, the member can also be defined
as inline and placed below the class definition in the header (this is useful for header-only libraries). If the class
is defined in a source (.cpp) file, the static member definition is usually placed directly underneath the class. Do
not put the static member definition in a header file (much like a global variable, if that header file gets included
more than once, you’ll end up with multiple definitions, which will cause a linker error).

For template classes, the (templated) static member definition is typically placed directly underneath the template
class definition in the header file (this doesn’t violate the ODR because such definitions are implicitly inline).


There are a few shortcuts to the above. First, when the static member is a constant integral type
(which includes char and bool) or a const enum, the static member can be initialized inside the class definition:

class Whatever
{
public:
	static const int s_value{ 4 }; // a static const int can be defined and initialized directly
};

In the above example, because the static member variable is a const int, no explicit definition line is needed.
This shortcut is allowed because these specific const types are compile-time constants.

In lesson 7.10 -- Sharing global constants across multiple files (using inline variables), we introduced inline
variables, which are variables that are allowed to have multiple definitions. C++17 allows static members to be
inline variables:

class Whatever
{
public:
	static inline int s_value{ 4 }; // a static inline variable can be defined and initialized directly
};

Such variables can be initialized inside the class definition regardless of whether they are constant or not.
This is the preferred method of defining and initializing static members.

Because constexpr members are implicitly inline (as of C++17), static constexpr members can also be initialized
inside the class definition without explicit use of the inline keyword:

#include <string_view>

class Whatever
{
public:
	static constexpr double s_value{ 2.2 }; // ok
	static constexpr std::string_view s_view{ "Hello" }; // this even works for classes that support constexpr initialization
};

THEREFORE: Make your static members inline or constexpr so they can be initialized inside the class definition.

_________________________________________________________________________________________

A static member may use auto to deduce its type from the initializer, or Class Template Argument Deduction (CTAD)
to deduce template type arguments from the initializer.

Non-static members may not use auto or CTAD.

The reasons for this distinction being made are quite complicated, but boil down to there being certain cases that
can occur with non-static members that lead to ambiguity or non-intuitive results. This does not occur for static
members. Thus non-static members are restricted from using these features, whereas static members are not.

#include <utility> // for std::pair<T, U>

class Foo
{
private:
	auto m_x { 5 };           // auto not allowed for non-static members
	std::pair m_v { 1, 2.3 }; // CTAD not allowed for non-static members

	static inline auto s_x { 5 };           // auto allowed for static members
	static inline std::pair s_v { 1, 2.3 }; // CTAD allowed for static members

public:
	Foo() {};
};

int main()
{
	Foo foo{};

	return 0;
}

 */