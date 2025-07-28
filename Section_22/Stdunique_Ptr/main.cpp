/*
 NOTE: Favor std::array, std::vector, or std::string over a smart pointer
 managing a fixed array, dynamic array, or C-style string.
 */

// #include <iostream>
// #include <memory> // for std::unique_ptr
// #include <utility> // for std::move
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// int main()
// {
// 	std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
// 	std::unique_ptr<Resource> res2{}; // Start as nullptr
//
// 	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
// 	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");
//
// 	// res2 = res1; // Won't compile: copy assignment is disabled
// 	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null
//
// 	std::cout << "Ownership transferred\n";
//
// 	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
// 	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");
//
// 	return 0;
// } // Resource destroyed here when res2 goes out of scope

/*
std::unique_ptr has an overloaded operator* and operator-> that can be used to return the resource being managed.
Operator* returns a reference to the managed resource, and operator-> returns a pointer.

Remember that std::unique_ptr may not always be managing an object -- either because it was created empty
(using the default constructor or passing in a nullptr as the parameter), or because the resource it was
managing got moved to another std::unique_ptr. So before we use either of these operators, we should check
whether the std::unique_ptr actually has a resource. Fortunately, this is easy: std::unique_ptr has a cast to
bool that returns true if the std::unique_ptr is managing a resource.

Here’s an example of this:
 */

// #include <iostream>
// #include <memory> // for std::unique_ptr
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// std::ostream& operator<<(std::ostream& out, const Resource&)
// {
// 	out << "I am a resource";
// 	return out;
// }
//
// int main()
// {
// 	std::unique_ptr<Resource> res{ new Resource{} };
//
// 	if (res) // use implicit cast to bool to ensure res contains a Resource
// 		std::cout << *res << '\n'; // print the Resource that res is owning
//
// 	return 0;
// }

/*
Use std::make_unique() instead of creating std::unique_ptr and using new yourself:
 */

// #include <memory> // for std::unique_ptr and std::make_unique
// #include <iostream>
//
// class Fraction
// {
// private:
//  int m_numerator{ 0 };
//  int m_denominator{ 1 };
//
// public:
//  Fraction(int numerator = 0, int denominator = 1) :
//   m_numerator{ numerator }, m_denominator{ denominator }
//  {
//  }
//
//  friend std::ostream& operator<<(std::ostream& out, const Fraction &f1)
//  {
//   out << f1.m_numerator << '/' << f1.m_denominator;
//   return out;
//  }
// };
//
//
// int main()
// {
//  // Create a single dynamically allocated Fraction with numerator 3 and denominator 5
//  // We can also use automatic type deduction to good effect here
//  auto f1{ std::make_unique<Fraction>(3, 5) };
//  std::cout << *f1 << '\n';
//
//  // Create a dynamically allocated array of Fractions of length 4
//  auto f2{ std::make_unique<Fraction[]>(4) };
//  std::cout << f2[0] << '\n';
//
//  return 0;
// }

// ===================================================================

// In general, you should not return std::unique_ptr by pointer (ever) or reference
// (unless you have a specific compelling reason to).
// std::unique_ptr can be safely returned from a function by value:

// #include <iostream>
// #include <memory> // for std::unique_ptr
//
// class Resource
// {
// public:
//  Resource() { std::cout << "Resource acquired\n"; }
//  ~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// std::unique_ptr<Resource> createResource()
// {
//  return std::make_unique<Resource>();
// }
//
// int main()
// {
//  auto ptr{ createResource() };
//
//  // do whatever
//
//  return 0;
// }


// ===================================================================

/*
If you want the function to take ownership of the contents of the pointer, pass the std::unique_ptr by value.
Note that because copy semantics have been disabled, you’ll need to use std::move to actually pass the variable in.

Although you can pass a std::unique_ptr by const reference (which will allow the function to use the object without
assuming ownership), it’s better to just pass the resource itself (by pointer or reference, depending on whether null
is a valid argument). This allows the function to remain agnostic of how the caller is managing its resources.
 */

// To get a raw pointer from a std::unique_ptr, you can use the get() member function:

#include <memory> // for std::unique_ptr
#include <iostream>

class Resource
{
public:
 Resource() { std::cout << "Resource acquired\n"; }
 ~Resource() { std::cout << "Resource destroyed\n"; }
};

std::ostream& operator<<(std::ostream& out, const Resource&)
{
 out << "I am a resource";
 return out;
}

// The function only uses the resource, so we'll accept a pointer to the resource, not a reference to the whole std::unique_ptr<Resource>
void useResource(const Resource* res)
{
 if (res)
  std::cout << *res << '\n';
 else
  std::cout << "No resource\n";
}

int main()
{
 auto ptr{ std::make_unique<Resource>() };

 useResource(ptr.get()); // note: get() used here to get a pointer to the Resource

 std::cout << "Ending program\n";

 return 0;
} // The Resource is destroyed here

/*
You can, of course, use std::unique_ptr as a composition member of your class. This way, you don’t have to worry
about ensuring your class destructor deletes the dynamic memory, as the std::unique_ptr will be automatically
destroyed when the class object is destroyed.

However, if the class object is not destroyed properly (e.g. it is dynamically allocated and not deallocated properly),
then the std::unique_ptr member will not be destroyed either, and the object being managed by the std::unique_ptr will
not be deallocated.
 */

/*
There are two easy ways to misuse std::unique_ptrs, both of which are easily avoided.
First, don’t let multiple objects manage the same resource.
Second, don’t manually delete the resource out from underneath the std::unique_ptr.

Note that std::make_unique() prevents both of the above cases from happening inadvertently.
 */