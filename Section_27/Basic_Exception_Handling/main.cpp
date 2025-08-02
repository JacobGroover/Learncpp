// Here’s a full program that uses throw, try, and multiple catch blocks:

// #include <iostream>
// #include <string>
//
// int main()
// {
// 	try
// 	{
// 		// Statements that may throw exceptions you want to handle go here
// 		throw -1; // here's a trivial example
// 	}
// 	catch (double) // no variable name since we don't use the exception itself in the catch block below
// 	{
// 		// Any exceptions of type double thrown within the above try block get sent here
// 		std::cerr << "We caught an exception of type double\n";
// 	}
// 	catch (int x)
// 	{
// 		// Any exceptions of type int thrown within the above try block get sent here
// 		std::cerr << "We caught an int exception with value: " << x << '\n';
// 	}
// 	catch (const std::string&) // catch classes by const reference
// 	{
// 		// Any exceptions of type std::string thrown within the above try block get sent here
// 		std::cerr << "We caught an exception of type std::string\n";
// 	}
//
// 	// Execution continues here after the exception has been handled by any of the above catch blocks
// 	std::cout << "Continuing on our merry way\n";
//
// 	return 0;
// }

// Let’s take a look at an example that’s not quite so academic:

#include <cmath> // for sqrt() function
#include <iostream>

// A modular square root function
double mySqrt(double x)
{
	// If the user entered a negative number, this is an error condition
	if (x < 0.0)
		throw "Can not take sqrt of negative number"; // throw exception of type const char*

	return std::sqrt(x);
}

int main()
{
	std::cout << "Enter a number: ";
	double x {};
	std::cin >> x;

	try // Look for exceptions that occur within try block and route to attached catch block(s)
	{
		double d = mySqrt(x);
		std::cout << "The sqrt of " << x << " is " << d << '\n';
	}
	catch (const char* exception) // catch exceptions of type const char*
	{
		std::cerr << "Error: " << exception << std::endl;
	}

	return 0;
}

/*
There are four common things that catch blocks do when they catch an exception:

First, catch blocks may print an error (either to the console, or a log file) and then allow the function to proceed.

Second, catch blocks may return a value or error code back to the caller.

Third, a catch block may throw another exception. Because the catch block is outside of the try block, the newly
thrown exception in this case is not handled by the preceding try block -- it’s handled by the next enclosing try block.

Fourth, a catch block in main() may be used to catch fatal errors and terminate the program in a clean way.
 */