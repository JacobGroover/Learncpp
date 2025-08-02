/*
 NOTE: Exception objects should not keep pointers or references to stack-allocated objects. If a thrown exception
 results in stack unwinding (causing the destruction of stack-allocated objects), these pointers or references
 may be left dangling.
 */

/*
Since it’s possible to throw classes as exceptions, and classes can be derived from other classes, we need to consider
what happens when we use inherited classes as exceptions. As it turns out, exception handlers will not only match
classes of a specific type, they’ll also match classes derived from that specific type as well! Consider the
following example:
 */

// #include <iostream>
//
// class Base
// {
// public:
// 	Base() {}
// };
//
// class Derived: public Base
// {
// public:
// 	Derived() {}
// };
//
// int main()
// {
// 	try
// 	{
// 		throw Derived();
// 	}
// 	catch (const Derived& derived)
// 	{
// 		std::cerr << "caught Derived";
// 	}
// 	catch (const Base& base)
// 	{
// 		std::cerr << "caught Base";
// 	}
//
// 	return 0;
// }

/*
Much of the time, when an exception is thrown by the standard library, we won’t care whether it’s a bad allocation,
a bad cast, or something else. We just care that something catastrophic went wrong and now our program is exploding.
Thanks to std::exception, we can set up an exception handler to catch exceptions of type std::exception, and we’ll end
up catching std::exception and all of the derived exceptions together in one place. Easy!
 */

// #include <cstddef> // for std::size_t
// #include <exception> // for std::exception
// #include <iostream>
// #include <limits>
// #include <string> // for this example
//
// int main()
// {
//  try
//  {
//   // Your code using standard library goes here
//   // We'll trigger one of these exceptions intentionally for the sake of the example
//   std::string s;
//   s.resize(std::numeric_limits<std::size_t>::max()); // will trigger a std::length_error or allocation exception
//  }
//  // This handler will catch std::exception and all the derived exceptions too
//  catch (const std::exception& exception)
//  {
//   std::cerr << "Standard exception: " << exception.what() << '\n';
//  }
//
//  return 0;
// }

/*
Sometimes we’ll want to handle a specific type of exception differently. In this case, we can add a handler for that
specific type, and let all the others “fall through” to the base handler. Consider:
 */

// try
// {
//  // code using standard library goes here
// }
// // This handler will catch std::length_error (and any exceptions derived from it) here
// catch (const std::length_error& exception)
// {
//  std::cerr << "You ran out of memory!" << '\n';
// }
// // This handler will catch std::exception (and any exception derived from it) that fall
// // through here
// catch (const std::exception& exception)
// {
//  std::cerr << "Standard exception: " << exception.what() << '\n';
// }

/*
Using the standard exceptions directly

Nothing throws a std::exception directly, and neither should you. However, you should feel free to throw the other
standard exception classes in the standard library if they adequately represent your needs. You can find a list of
all the standard exceptions on cppreference.

std::runtime_error (included as part of the stdexcept header) is a popular choice, because it has a generic name,
and its constructor takes a customizable message:
 */

// #include <exception> // for std::exception
// #include <iostream>
// #include <stdexcept> // for std::runtime_error
//
// int main()
// {
//  try
//  {
//   throw std::runtime_error("Bad things happened");
//  }
//  // This handler will catch std::exception and all the derived exceptions too
//  catch (const std::exception& exception)
//  {
//   std::cerr << "Standard exception: " << exception.what() << '\n';
//  }
//
//  return 0;
// }

/*
You can, of course, derive your own classes from std::exception, and override the virtual what() const member function.
Here’s the same program as above, with ArrayException derived from std::exception:
 */

// #include <exception> // for std::exception
// #include <iostream>
// #include <string>
// #include <string_view>
//
// class ArrayException : public std::exception
// {
// private:
//  std::string m_error{}; // handle our own string
//
// public:
//  ArrayException(std::string_view error)
//   : m_error{error}
//  {
//  }
//
//  // std::exception::what() returns a const char*, so we must as well
//  const char* what() const noexcept override { return m_error.c_str(); }
// };
//
// class IntArray
// {
// private:
//  int m_data[3] {}; // assume array is length 3 for simplicity
//
// public:
//  IntArray() {}
//
//  int getLength() const { return 3; }
//
//  int& operator[](const int index)
//  {
//   if (index < 0 || index >= getLength())
//    throw ArrayException("Invalid index");
//
//   return m_data[index];
//  }
//
// };
//
// int main()
// {
//  IntArray array;
//
//  try
//  {
//   int value{ array[5] };
//  }
//  catch (const ArrayException& exception) // derived catch blocks go first
//  {
//   std::cerr << "An array exception occurred (" << exception.what() << ")\n";
//  }
//  catch (const std::exception& exception)
//  {
//   std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
//  }
// }

/*
Note that virtual function what() has specifier noexcept (which means the function promises not to throw exceptions
itself). Therefore, our override should also have specifier noexcept.

Because std::runtime_error already has string handling capabilities, it’s also a popular base class for derived
exception classes. std::runtime_error can take a C-style string parameter, or a const std::string& parameter.

Here’s the same example derived from std::runtime_error instead:
 */

#include <exception> // for std::exception
#include <iostream>
#include <stdexcept> // for std::runtime_error
#include <string>

class ArrayException : public std::runtime_error
{
public:
 // std::runtime_error takes either a null-terminated const char* or a const std::string&.
 // We will follow their lead and take a const std::string&
 ArrayException(const std::string& error)
  : std::runtime_error{ error } // std::runtime_error will handle the string
 {
 }


 // no need to override what() since we can just use std::runtime_error::what()
};

class IntArray
{
private:
 int m_data[3]{}; // assume array is length 3 for simplicity

public:
 IntArray() {}

 int getLength() const { return 3; }

 int& operator[](const int index)
 {
  if (index < 0 || index >= getLength())
   throw ArrayException("Invalid index");

  return m_data[index];
 }

};

int main()
{
 IntArray array;

 try
 {
  int value{ array[5] };
 }
 catch (const ArrayException& exception) // derived catch blocks go first
 {
  std::cerr << "An array exception occurred (" << exception.what() << ")\n";
 }
 catch (const std::exception& exception)
 {
  std::cerr << "Some other std::exception occurred (" << exception.what() << ")\n";
 }
}