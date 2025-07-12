#include <iostream>
#include "Random.h" // defines Random::mt, Random::get(), and Random::generate()
#include <cstddef> // for std::size_t

// Generating random numbers using Random.h is as simple as following these three steps:

/*
1. Copy/paste the Random.h code into a file named Random.h in your project directory and save it. Optionally add Random.h to your project.
2. #include "Random.h" from any .cpp file in your project that needs to generate random numbers.
3. Call Random::get(min, max) to generate a random number between min and max (inclusive). No initialization or setup is required.
*/

// Here is a sample program demonstrating different uses of Random.h:

int main() {
	// We can call Random::get() to generate random integral values
	// If the two arguments have the same type, the returned value will have that same type.
	std::cout << Random::get(1, 6) << '\n';   // returns int between 1 and 6
	std::cout << Random::get(1u, 6u) << '\n'; // returns unsigned int between 1 and 6

	// In cases where we have two arguments with different types
	// and/or if we want the return type to be different than the argument types
	// We must specify the return type using a template type argument (between the angled brackets)
	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	std::cout << Random::get<std::size_t>(1, 6u) << '\n'; // returns std::size_t between 1 and 6

	// If we have our own distribution, we can access Random::mt directly

	// Let's create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
	for (int count{ 1 }; count <= 10; ++count)
	{
		std::cout << die6(Random::mt) << '\t'; // generate a roll of the die here
	}

	std::cout << '\n';

	return 0;
}