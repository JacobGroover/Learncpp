// An object of type T is cheap to copy if sizeof(T) <= 2 * sizeof(void*) and has no additional setup costs.

// The following program defines a function-like macro that can be used to determine if a type (or object) is cheap to copy accordingly:

// However, it can be hard to know whether a class type object has setup costs or not. It’s best to assume that most
// standard library classes have setup costs, unless you know otherwise that they don’t.

#include <iostream>

// Function-like macro that evaluates to true if the type (or object) is equal to or smaller than
// the size of two memory addresses
#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))

struct S
{
	double a;
	double b;
	double c;
};

int main()
{
	std::cout << std::boolalpha; // print true or false rather than 1 or 0
	std::cout << isSmall(int) << '\n'; // true

	double d {};
	std::cout << isSmall(d) << '\n'; // true
	std::cout << isSmall(S) << '\n'; // false

	return 0;
}