// Fibonacci basic recursion:

// #include <iostream>
//
// int fibonacci(int count)
// {
// 	if (count == 0)
// 		return 0; // base case (termination condition)
// 	if (count == 1)
// 		return 1; // base case (termination condition)
// 	return fibonacci(count-1) + fibonacci(count-2);
// }
//
// // And a main program to display the first 13 Fibonacci numbers
// int main()
// {
// 	for (int count { 0 }; count < 13; ++count)
// 		std::cout << fibonacci(count) << ' ';
//
// 	return 0;
// }

// Memoization caches the results of expensive function calls so the result can be returned when the same input occurs again.
// Memoization version of the recursive Fibonacci algorithm:
#include <iostream>
#include <vector>

// count is now a std::size_t to make indexing the std::vector easier
int fibonacci(std::size_t count)
{
	// We'll use a static std::vector to cache calculated results
	static std::vector results{ 0, 1 };

	// If we've already seen this count, then use the cache'd result
	if (count < std::size(results))
		return results[count];

	// Otherwise calculate the new result and add it
	results.push_back(fibonacci(count - 1) + fibonacci(count - 2));
	return results[count];
}

// And a main program to display the first 13 Fibonacci numbers
int main()
{
	for (int count { 0 }; count < 13; ++count)
		std::cout << fibonacci(static_cast<std::size_t>(count)) << ' ';

	return 0;
}