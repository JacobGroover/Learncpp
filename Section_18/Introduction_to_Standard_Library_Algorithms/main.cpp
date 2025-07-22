// Let’s use std::sort to sort an array in reverse order using a custom comparison function named greater:

#include <algorithm>
#include <array>
#include <iostream>

bool greater(int a, int b)
{
	// Order @a before @b if @a is greater than @b.
	return (a > b);
}

int main()
{
	std::array arr{ 13, 90, 99, 5, 40, 80 };

	// Pass greater to std::sort
	std::sort(arr.begin(), arr.end(), greater);

	for (int i : arr)
	{
		std::cout << i << ' ';
	}

	std::cout << '\n';

	return 0;
}

/*
Our greater function needs 2 arguments, but we’re not passing it any, so where do they come from? When we use a
function without parentheses (), it’s only a function pointer, not a call. You might remember this from when we
tried to print a function without parentheses and std::cout printed “1”. std::sort uses this pointer and calls the
actual greater function with any 2 elements of the array. We don’t know which elements greater will be called with,
because it’s not defined which sorting algorithm std::sort is using under the hood. We talk more about function
pointers in a later chapter.

Because sorting in descending order is so common, C++ provides a custom type (named std::greater) for that too (which is part of the functional header). In the above example, we can replace:

std::sort(arr.begin(), arr.end(), greater); // call our custom greater function
with:

std::sort(arr.begin(), arr.end(), std::greater{}); // use the standard library greater comparison

// Before C++17, we had to specify the element type when we create std::greater
std::sort(arr.begin(), arr.end(), std::greater<int>{}); // use the standard library greater comparison
Note that the std::greater{} needs the curly braces because it is not a callable function. It’s a type,
and in order to use it, we need to instantiate an object of that type. The curly braces instantiate an
anonymous object of that type (which then gets passed as an argument to std::sort).
 */