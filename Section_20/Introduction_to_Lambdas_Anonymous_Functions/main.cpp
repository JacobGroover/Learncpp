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

int main()
{
	constexpr std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

	// Define the function right where we use it.
	auto found{ std::find_if(arr.begin(), arr.end(),
							 [](std::string_view str) // here's our lambda, no capture clause
							 {
							   return str.find("nut") != std::string_view::npos;
							 }) };

	if (found == arr.end())
	{
		std::cout << "No nuts\n";
	}
	else
	{
		std::cout << "Found " << *found << '\n';
	}

	return 0;
}

/*
Best practice

Following the best practice of defining things in the smallest scope and closest to first use, lambdas are preferred
over normal functions when we need a trivial, one-off function to pass as an argument to some other function.
 */