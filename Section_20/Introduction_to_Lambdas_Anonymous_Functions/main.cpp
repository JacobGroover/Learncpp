/*
The syntax for lambdas is one of the weirder things in C++, and takes a bit of getting used to. Lambdas take the form:

[ captureClause ] ( parameters ) -> returnType
{
	statements;
}
The capture clause can be empty if no captures are needed.
The parameter list can be empty if no parameters are required. It can also be omitted entirely unless a return type
is specified.
The return type is optional, and if omitted, auto will be assumed (thus using type deduction used to determine the
return type). While we previously noted that type deduction for function return types should be avoided, in this
context, it’s fine to use (because these functions are typically so trivial).
Also note that lambdas (being anonymous) have no name, so we don’t need to provide one.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

/*
Storing a lambda in a variable provides a way for us to give the lambda a useful name,
which can help make our code more readable.

Storing a lambda in a variable also provides us with a way to use that lambda more than once.
 */
// bool checkEvens(std::array<int, 5>& array) {
// 	// Good: Instead, we can store the lambda in a named variable and pass it to the function.
// 	auto isEven{
// 		[](int i)
// 		{
// 			return (i % 2) == 0;
// 		}
// 	};
//
// 	return std::all_of(array.begin(), array.end(), isEven);
// }
//
// int main()
// {
// 	constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };
//
// 	// Define the function right where we use it.
// 	auto found{ std::find_if(arr.begin(), arr.end(),
// 							 [](std::string_view str) // here's our lambda, no capture clause
// 							 {
// 							   return str.find("nut") != std::string_view::npos;
// 							 }) };
//
// 	if (found == arr.end())
// 	{
// 		std::cout << "No nuts\n";
// 	}
// 	else
// 	{
// 		std::cout << "Found " << *found << '\n';
// 	}
//
// 	return 0;
// }

/*
Best practice

Following the best practice of defining things in the smallest scope and closest to first use, lambdas are preferred
over normal functions when we need a trivial, one-off function to pass as an argument to some other function.
 */

/*
 Lambdas are Functors (objects that contain an overloaded operator() that make them callable like a function), not
 actual functions. The compiler generates a unique type just for the lambda that is not exposed to us.
 */

/*
Although we don’t know the type of a lambda, there are several ways of storing a lambda for use post-definition.
If the lambda has an empty capture clause (nothing between the hard brackets []), we can use a regular
function pointer. std::function or type deduction via the auto keyword will also work (even if the lambda
has a non-empty capture clause).
 */

// #include <functional>
//
// int main()
// {
// 	// A regular function pointer. Only works with an empty capture clause (empty []).
// 	double (*addNumbers1)(double, double){
// 		[](double a, double b) {
// 			return a + b;
// 		}
// 	};
//
// 	addNumbers1(1, 2);
//
// 	// Using std::function. The lambda could have a non-empty capture clause (discussed next lesson).
// 	std::function<double(double, double)> addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead (also compile errored in C++23 until added)
// 		[](double a, double b) {
// 			return a + b;
// 		}
// 	};
//
// 	addNumbers2(3, 4);
//
// 	// Using auto. Stores the lambda with its real type.
// 	// The only way of using the lambda’s actual type is by means of auto. auto also has the benefit of having no overhead compared to std::function.
// 	auto addNumbers3{
// 		[](double a, double b) {
// 			return a + b;
// 		}
// 	};
//
// 	addNumbers3(5, 6);
//
// 	return 0;
// }

/*
To pass a lambda to a function, there are 4 options:
 */
// #include <functional>
// #include <iostream>
//
// // Case 1: use a `std::function` parameter. Has more overhead than following options, allows for header separation.
// void repeat1(int repetitions, const std::function<void(int)>& fn)
// {
// 	for (int i{ 0 }; i < repetitions; ++i)
// 		fn(i);
// }
//
// // Case 2: use a function template with a type template parameter
// template <typename T>
// void repeat2(int repetitions, const T& fn)
// {
// 	for (int i{ 0 }; i < repetitions; ++i)
// 		fn(i);
// }
//
// // Case 3: use the abbreviated function template syntax (C++20)
// void repeat3(int repetitions, const auto& fn)
// {
// 	for (int i{ 0 }; i < repetitions; ++i)
// 		fn(i);
// }
//
// // Case 4: use function pointer (only for lambda with no captures)
// void repeat4(int repetitions, void (*fn)(int))
// {
// 	for (int i{ 0 }; i < repetitions; ++i)
// 		fn(i);
// }
//
// int main()
// {
// 	auto lambda = [](int i)
// 	{
// 		std::cout << i << '\n';
// 	};
//
// 	repeat1(3, lambda);
// 	repeat2(3, lambda);
// 	repeat3(3, lambda);
// 	repeat4(3, lambda);
//
// 	return 0;
// }

/*
BEST PRACTICE:

When storing a lambda in a variable, use auto as the variable’s type.

When passing a lambda to a function:

If C++20 capable, use auto as the parameter’s type.
Otherwise, use a function with a type template parameter or std::function parameter (or a function pointer if the lambda has no captures).
 */

/*
When used in the context of a lambda, auto is just a shorthand for a template parameter. This is known as a
generic lambda:
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

// int main()
// {
// 	constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
// 		"January",
// 		"February",
// 		"March",
// 		"April",
// 		"May",
// 		"June",
// 		"July",
// 		"August",
// 		"September",
// 		"October",
// 		"November",
// 		"December"
// 	  };
//
// 	// Search for two consecutive months that start with the same letter.
// 	const auto sameLetter{ std::adjacent_find(months.begin(), months.end(),
// 										[](const auto& a, const auto& b) {
// 										  return a[0] == b[0];
// 										}) };
//
// 	// Make sure that two months were found.
// 	if (sameLetter != months.end())
// 	{
// 		// std::next returns the next iterator after sameLetter
// 		std::cout << *sameLetter << " and " << *std::next(sameLetter)
// 				  << " start with the same letter\n";
// 	}
//
// 	return 0;
// }

/*
In the above example, we use auto parameters to capture our strings by const reference. Because all string types
allow access to their individual characters via operator[], we don’t need to care whether the user is passing in
a std::string, C-style string, or something else. This allows us to write a lambda that could accept any of these,
meaning if we change the type of months later, we won’t have to rewrite the lambda.

However, auto isn’t always the best choice. Consider:
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

// int main()
// {
// 	constexpr std::array months{ // pre-C++17 use std::array<const char*, 12>
// 		"January",
// 		"February",
// 		"March",
// 		"April",
// 		"May",
// 		"June",
// 		"July",
// 		"August",
// 		"September",
// 		"October",
// 		"November",
// 		"December"
// 	  };
//
// 	// Count how many months consist of 5 letters
// 	const auto fiveLetterMonths{ std::count_if(months.begin(), months.end(),
// 										 [](std::string_view str) {
// 										   return str.length() == 5;
// 										 }) };
//
// 	std::cout << "There are " << fiveLetterMonths << " months with 5 letters\n";
//
// 	return 0;
// }
/*
In this example, using auto would infer a type of const char*. C-style strings aren’t easy to work with
(apart from using operator[]). In this case, we prefer to explicitly define the parameter as a std::string_view,
which allows us to work with the underlying data much more easily (e.g. we can ask the string view for its length,
even if the user passed in a C-style array).
 */

/*
In lesson 11.7 -- Function template instantiation, we discussed that when a function template contains a static
local variable, each function instantiated from that template will receive its own independent static local variable.
This may cause issues if that is not expected.

Generic lambdas work the same way: a unique lambda will be generated for each different type that auto resolves to.

The following example shows how one generic lambda turns into two distinct lambdas:
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>

// int main()
// {
// 	// Print a value and count how many times @print has been called.
// 	auto print{
// 		[](auto value) {
// 			static int callCount{ 0 };
// 			std::cout << callCount++ << ": " << value << '\n';
// 		}
// 	};
//
// 	print("hello"); // 0: hello
// 	print("world"); // 1: world
//
// 	print(1); // 0: 1
// 	print(2); // 1: 2
//
// 	print("ding dong"); // 2: ding dong
//
// 	return 0;
// }

/*
If return type deduction is used, a lambda’s return type is deduced from the return-statements inside the lambda,
and all return statements in the lambda must return the same type (otherwise the compiler won’t know which one to prefer).

For example:
 */
#include <iostream>

// int main()
// {
// 	auto divide{ [](int x, int y, bool intDivision) { // note: no specified return type
// 		if (intDivision)
// 			return x / y; // return type is int
// 		else
// 			return static_cast<double>(x) / y; // ERROR: return type doesn't match previous return type
// 	} };
//
// 	std::cout << divide(3, 2, true) << '\n';
// 	std::cout << divide(3, 2, false) << '\n';
//
// 	return 0;
// }

/*
This produces a compile error because the return type of the first return statement (int) doesn’t match the
return type of the second return statement (double).

In the case where we’re returning different types, we have two options:

1. Do explicit casts to make all the return types match, or
2. explicitly specify a return type for the lambda, and let the compiler do implicit conversions.

The second case is usually the better choice:
 */
#include <iostream>

// int main()
// {
// 	// note: explicitly specifying this returns a double
// 	auto divide{ [](int x, int y, bool intDivision) -> double {
// 		if (intDivision)
// 			return x / y; // will do an implicit conversion of result to double
// 		else
// 			return static_cast<double>(x) / y;
// 	} };
//
// 	std::cout << divide(3, 2, true) << '\n';
// 	std::cout << divide(3, 2, false) << '\n';
//
// 	return 0;
// }

/*
That way, if you ever decide to change the return type, you (usually) only need to change the
lambda’s return type, and not touch the lambda body.
 */


// QUIZ:

/*
Create a struct Student that stores the name and points of a student. Create an array of students and use
std::max_element to find the student with the most points, then print that student’s name. std::max_element
takes the begin and end of a list, and a function that takes 2 parameters and returns true if the first argument
is less than the second.
 */
struct Student {
	std::string_view name{};
	int points{};
};

int main() {
	constexpr std::array<Student, 8> arr{
	  { { "Albert", 3 },
		{ "Ben", 5 },
		{ "Christine", 2 },
		{ "Dan", 8 }, // Dan has the most points (8).
		{ "Enchilada", 4 },
		{ "Francis", 1 },
		{ "Greg", 3 },
		{ "Hagrid", 5 } }
	};

	const auto best{
		std::max_element(std::begin(arr), std::end(arr), [](const auto& a, const auto& b) -> bool {
			return a.points < b.points;
		}
			)};

	std::cout << best->name << " is the best student"; // must dereference iterator ( using operator-> ) to get element
}