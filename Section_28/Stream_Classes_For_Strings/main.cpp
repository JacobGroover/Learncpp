/*
There are six stream classes for strings: istringstream (derived from istream), ostringstream
(derived from ostream), and stringstream (derived from iostream) are used for reading and writing normal
characters width strings. wistringstream, wostringstream, and wstringstream are used for reading and writing wide
character strings. To use the stringstreams, you need to #include the sstream header.

There are two ways to get data into a stringstream, and
two ways to get data out of a stringstream:

1. Using insertion (<<) or extraction operator (>>), respectively.
2. Using the str(string) function to set or get the value of the buffer.
 */

#include <iostream>
#include <sstream>

// int main() {
//  // std::stringstream os {};
//  // os.str("en garde!"); // set the stringstream buffer to "en garde!"
//
//  // std::stringstream os {};
//  // os << "12345 67.89\n";
//  // std::cout << os.str();
//
//  std::stringstream os {};
//  os << "12345 67.89"; // insert a string of numbers into the stream
//
//  std::string strValue {};
//  os >> strValue;
//
//  std::string strValue2 {};
//  os >> strValue2;
//
//  // print the numbers separated by a dash
//  std::cout << strValue << " - " << strValue2 << '\n';
//
//  return 0;
// }

/*
Conversion between strings and numbers

Because the insertion and extraction operators know how to work with all of the basic data types, we can use them
in order to convert strings to numbers or vice versa.

First, let’s take a look at converting numbers into a string:
 */

// std::stringstream os {};
//
// constexpr int nValue { 12345 };
// constexpr double dValue { 67.89 };
// os << nValue << ' ' << dValue;
//
// std::string strValue1, strValue2;
// os >> strValue1 >> strValue2;
//
// std::cout << strValue1 << ' ' << strValue2 << '\n';


/*
 Now let’s convert a numerical string to a number:
 */

// std::stringstream os {};
// os << "12345 67.89"; // insert a string of numbers into the stream
// int nValue {};
// double dValue {};
//
// os >> nValue >> dValue;
//
// std::cout << nValue << ' ' << dValue << '\n';


/*
Clearing a stringstream for reuse

There are several ways to empty a stringstream’s buffer.
 */

int main() {
 // 1. Set it to the empty string using str() with a blank C-style string:
 std::stringstream os {};
 os << "Hello ";

 os.str(""); // erase the buffer

 os << "World!";
 std::cout << os.str();

 std::cout << '\n';
 // 2. Set it to the empty string using str() with a blank std::string object:
 std::stringstream os2 {};
 os2 << "Hello ";

 os2.str(std::string{}); // erase the buffer

 os2 << "World!";
 std::cout << os2.str();

 std::cout << '\n';

 /*
 When clearing out a stringstream, it is also generally a good idea to call the clear() function:
  */
 std::stringstream os3 {};
 os3 << "Hello ";

 os3.str(""); // erase the buffer
 os3.clear(); // reset error flags

 os3 << "World!";
 std::cout << os3.str();

 /*
 clear() resets any error flags that may have been set and returns the stream back to the ok state.
 We will talk more about the stream state and error flags in the lesson on Stream States and Input Validation.
  */

 return 0;
}