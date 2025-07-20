// In this lesson, we’ll combine elements of both function templates and class templates as we take a
// closer look at class templates that have member functions.

// Type template parameters defined as part of a class template parameter declaration can be used both as the
// type of data members and as the type of member function parameters.



#include <ios>       // for std::boolalpha
#include <iostream>

template <typename T>
class Pair
{
private:
	T m_first{};
	T m_second{};

public:
	// When we define a member function inside the class definition,
	// the template parameter declaration belonging to the class applies
	Pair(const T& first, const T& second)
		: m_first{ first }
	, m_second{ second }
	{
	}

	bool isEqual(const Pair<T>& pair);
};

// When we define a member function outside the class definition,
// we need to resupply a template parameter declaration
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
	return m_first == pair.m_first && m_second == pair.m_second;
}

int main()
{
	Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
	std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
	std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

	return 0;
}

/*
The above should be pretty straightforward, but there are a few things worth noting.

First, because our class has private members, it is not an aggregate, and therefore can’t use aggregate initialization.
Instead, we have to initialize our class objects using a constructor.

Since our class data members are of type T, we make the parameters of our constructor type const T&, so the user can
supply initialization values of the same type. Because T might be expensive to copy, it’s safer to pass by const
reference than by value.

Note that when we define a member function inside the class template definition, we don’t need to provide a template
parameter declaration for the member function. Such member functions implicitly use the class template parameter
declaration.

Second, we don’t need deduction guides for CTAD to work with non-aggregate classes. A matching constructor provides
the compiler with the information it needs to deduce the template parameters from the initializers.

________________________________________

Third, when looking closely at the case where we define a member function for a class template outside the
class template definition:

Since this member function definition is separate from the class template definition, we need to resupply a template
parameter declaration (template <typename T>) so the compiler knows what T is.

Also, when we define a member function outside the class, we need to qualify the member function name with the fully
templated name of the class template (Pair<T>::isEqual, not Pair::isEqual).

________________________________________

In a prior lesson, we noted that the name of a constructor must match the name of the class. But in our class
template for Pair<T> above, we named our constructor Pair, not Pair<T>. Somehow this still works, even though
the names don’t match.

Within the scope of a class, the unqualified name of the class is called an injected class name. In a class template,
the injected class name serves as shorthand for the fully templated name.

________________________________________

In lesson 13.14 -- Class template argument deduction (CTAD) and deduction guides, we noted that CTAD doesn’t work
with function parameters (as it is argument deduction, not parameter deduction). However, using an injected class
name as a function parameter is okay, as it is shorthand for the fully templated name, not a use of CTAD.

________________________________________

In lesson 11.7 -- Function template instantiation, we noted that functions implicitly instantiated from templates are
implicitly inline. This includes both non-member and member function templates. Therefore, there is no issue including
member function templates defined in header files into multiple code files, as the functions instantiated from those
templates will be implicitly inline (and the linker will de-duplicate them).

Any member function templates defined outside the class definition should be defined just below the class
definition (in the same file).
 */