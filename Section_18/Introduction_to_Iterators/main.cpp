/*
NOTE: Generally you'll use begin() when working with standard library algorithms, and data() when working with
 functions that expect C-style arrays or when you need direct access to the underlying array data.

int* end{ arr.data() + std::size(arr) }; // data() returns a pointer to the first element
 */

/*
Iterating through an array (or other structure) of data is quite a common thing to do in programming.
And so far, we’ve covered many different ways to do so: with loops and an index (for-loops and while loops),
with pointers and pointer arithmetic, and with range-based for-loops:
 */

// #include <array>
// #include <cstddef>
// #include <iostream>
//
// int main()
// {
// 	// In C++17, the type of variable arr is deduced to std::array<int, 7>
// 	// If you get an error compiling this example, see the warning below
// 	std::array arr{ 0, 1, 2, 3, 4, 5, 6 };
// 	std::size_t length{ std::size(arr) };
//
// 	// while-loop with explicit index
// 	std::size_t index{ 0 };
// 	while (index < length)
// 	{
// 		std::cout << arr[index] << ' ';
// 		++index;
// 	}
// 	std::cout << '\n';
//
// 	// for-loop with explicit index
// 	for (index = 0; index < length; ++index)
// 	{
// 		std::cout << arr[index] << ' ';
// 	}
// 	std::cout << '\n';
//
// 	// for-loop with pointer (Note: ptr can't be const, because we increment it)
// 	for (auto ptr{ &arr[0] }; ptr != (&arr[0] + length); ++ptr)
// 	{
// 		std::cout << *ptr << ' ';
// 	}
// 	std::cout << '\n';
//
// 	// range-based for loop
// 	for (int i : arr)
// 	{
// 		std::cout << i << ' ';
// 	}
// 	std::cout << '\n';
//
// 	return 0;
// }

/*
 WARNING: he examples in this lesson use a C++17 feature called class template argument deduction to deduce the
 template arguments for a template variable from its initializer. In the example above, when the compiler sees
 std::array arr{ 0, 1, 2, 3, 4, 5, 6 };, it will deduce that we want std::array<int, 7> arr { 0, 1, 2, 3, 4, 5, 6 };
 */


/*
 Pointers as an iterator:
 */
// #include <array>
// #include <iostream>
//
// int main()
// {
//  std::array arr{ 0, 1, 2, 3, 4, 5, 6 };
//
//  auto begin{ &arr[0] };
//  // note that this points to one spot beyond the last element
//  auto end{ begin + std::size(arr) };
//
//  // for-loop with pointer
//  for (auto ptr{ begin }; ptr != end; ++ptr) // ++ to move to next element
//  {
//   std::cout << *ptr << ' '; // Indirection to get value of current element
//  }
//  std::cout << '\n';
//
//  return 0;
// }


/*
The erase() function returns an iterator to the element one past the
erased element (or end() if the last element was removed):
 */

#include <iostream>
#include <vector>

int main()
{
 std::vector v{ 1, 2, 3, 4, 5, 6, 7 };

 auto it{ v.begin() };

 ++it; // move to second element
 std::cout << *it << '\n';

 it = v.erase(it); // erase the element currently being iterated over, set `it` to next element

 std::cout << *it << '\n'; // now ok, prints 3

 return 0;
}