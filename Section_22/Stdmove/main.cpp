/*
std::move can be used whenever we want to treat an l-value like an r-value
to invoke move semantics instead of copy semantics.
 */

// #include <iostream>
// #include <string>
// #include <utility> // for std::move
//
// template <typename T>
// void mySwapMove(T& a, T& b)
// {
// 	T tmp { std::move(a) }; // invokes move constructor
// 	a = std::move(b); // invokes move assignment
// 	b = std::move(tmp); // invokes move assignment
// }
//
// int main()
// {
// 	std::string x{ "abc" };
// 	std::string y{ "de" };
//
// 	std::cout << "x: " << x << '\n';
// 	std::cout << "y: " << y << '\n';
//
// 	mySwapMove(x, y);
//
// 	std::cout << "x: " << x << '\n';
// 	std::cout << "y: " << y << '\n';
//
// 	return 0;
// }

// =====================================================================================

#include <iostream>
#include <string>
#include <utility> // for std::move
#include <vector>

int main()
{
	std::vector<std::string> v;

	// We use std::string because it is movable (std::string_view is not)
	std::string str { "Knock" };

	std::cout << "Copying str\n";
	v.push_back(str); // calls l-value version of push_back, which copies str into the array element

	std::cout << "str: " << str << '\n';
	std::cout << "vector: " << v[0] << '\n';

	std::cout << "\nMoving str\n";

	v.push_back(std::move(str)); // calls r-value version of push_back, which moves str into the array element

	std::cout << "str: " << str << '\n'; // The result of this is indeterminate
	std::cout << "vector:" << v[0] << ' ' << v[1] << '\n';

	return 0;
}

/*
std::move() gives a hint to the compiler that the programmer doesn’t need the value of an object any more. Only use
std::move() on persistent objects whose value you want to move, and do not make any assumptions about the value of
the object beyond that point. It is okay to give a moved-from object a new value (e.g. using operator=) after the
current value has been moved.
 */

/*
std::move can also be useful when sorting an array of elements. Many sorting algorithms (such as selection
sort and bubble sort) work by swapping pairs of elements. In previous lessons, we’ve had to resort to
copy-semantics to do the swapping. Now we can use move semantics, which is more efficient.

It can also be useful if we want to move the contents managed by one smart pointer to another.
 */

/*
There is a useful variant of std::move() called std::move_if_noexcept() that returns a movable r-value if the object
has a noexcept move constructor, otherwise it returns a copyable l-value.
We cover this in lesson 27.10 -- std::move_if_noexcept.
 */