// Assertions should be used to document cases that should be logically impossible.
// Error handling should be used to handle cases that are possible.

// the std::abort() function terminates the program immediately, without a chance to do any further cleanup
// (e.g. close a file or database). Because of this, asserts should be used only in cases where corruption
// isn’t likely to occur if the program terminates unexpectedly.

#undef NDEBUG // enables asserts
#define NDEBUG // disable asserts (must be placed before any #includes)
#include <cassert>
#include <iostream>

// static_assert(sizeof(long) == 8, "long must be 8 bytes");
// static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

double getInverse(double x)
{
	assert(x != 0.0);
	if (x == 0.0)
		// handle error somehow (e.g. throw an exception)

			return 1.0 / x;
}

int main()
{
	assert(false && "This is a string message"); // won't trigger since asserts have been disabled in this translation unit
	std::cout << "Hello, world!\n";

	return 0;
}