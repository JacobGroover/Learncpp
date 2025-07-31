/*
If our desire is to specialize the print() function so that it prints doubles in scientific notation.
Using class template specialization, we could define a specialized class for Storage<double>:
 */

// #include <iostream>
//
// template <typename T>
// class Storage
// {
// private:
// 	T m_value {};
// public:
// 	Storage(T value)
// 	  : m_value { value }
// 	{
// 	}
//
// 	void print()
// 	{
// 		std::cout << m_value << '\n';
// 	}
// };
//
// // Explicit class template specialization for Storage<double>
// // Note how redundant this is
// template <>
// class Storage<double>
// {
// private:
// 	double m_value {};
// public:
// 	Storage(double value)
// 	  : m_value { value }
// 	{
// 	}
//
// 	void print();
// };
//
// // We're going to define this outside the class for reasons that will become obvious shortly
// // This is a normal (non-specialized) member function definition (for member function print of specialized class Storage<double>)
// void Storage<double>::print()
// {
// 	std::cout << std::scientific << m_value << '\n';
// }
//
// int main()
// {
// 	// Define some storage units
// 	Storage i { 5 };
// 	Storage d { 6.7 }; // uses explicit specialization Storage<double>
//
// 	// Print out some values
// 	i.print(); // calls Storage<int>::print (instantiated from Storage<T>)
// 	d.print(); // calls Storage<double>::print (called from explicit specialization of Storage<double>)
// }

/*
However, note how much redundancy there is here. We’ve duplicated an entire class definition just so
that we can change one member function!

Fortunately, we can do better. C++ does not require us to explicitly specialize Storage<double> to explicitly
specialize Storage<double>::print(). Instead, we can let the compiler implicitly specialize Storage<double> from
Storage<T>, and provide an explicit specialization of just Storage<double>::print()! Here’s what that looks like:
 */

#include <iostream>

template <typename T>
class Storage
{
private:
 T m_value {};
public:
 Storage(T value)
   : m_value { value }
 {
 }

 void print()
 {
  std::cout << m_value << '\n';
 }
};

// This is a specialized member function definition
// Explicit function specializations are not implicitly inline, so make this inline if put in header file
template<>
void Storage<double>::print()
{
 std::cout << std::scientific << m_value << '\n';
}

int main()
{
 // Define some storage units
 Storage i { 5 };
 Storage d { 6.7 }; // will cause Storage<double> to be implicitly instantiated

 // Print out some values
 i.print(); // calls Storage<int>::print (instantiated from Storage<T>)
 d.print(); // calls Storage<double>::print (called from explicit specialization of Storage<double>::print())
}

/*
That’s it!

As noted in the prior lesson (26.3 -- Function template specialization), explicit function specializations are not
implicitly inline, so we should mark our specialization of Storage<double>::print() as inline if it is defined it in
a header file.
 */

/*
Where to define class template specializations:

In order to use a specialization, the compiler must be able to see the full definition of both the non-specialized
class and the specialized class. If the compiler can only see the definition of the non-specialized class, it will
use that instead of the specialization.

For this reason, specialized classes and functions are often defined in a header file just below the definition of
the non-specialized class, so that including a single header includes both the non-specialized class and any
specializations. This ensures the specialization can always be seen whenever the non-specialized class can also be seen.

If a specialization is only required in a single translation unit, it can be defined in the source file for that
translation unit. Because other translation units will not be able to see the definition of the specialization,
they will continue to use the non-specialized version.

Be wary of putting a specialization in its own separate header file, with the intent of including the specialization’s
header in any translation unit where the specialization is desired. It’s a bad idea to design code that transparently
changes behavior based on the presence or absence of a header file. For example, if you intend to use the
specialization but forget to include the header of the specialization, you may end up using the non-specialized
version instead. If you intend to use the non-specialization, you may end up using the specialization anyway if
some other header includes the specialization as a transitive include.
 */