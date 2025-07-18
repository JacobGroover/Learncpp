/*
Prefer std::optional for optional return types.

Prefer function overloading for optional function parameters (when possible). Otherwise, use std::optional<T>
for optional arguments when T would normally be passed by value. Favor const T* when T is expensive to copy.
 */

#include <iostream>
#include <optional> // for std::optional (C++17)

// Our function now optionally returns an int value
std::optional<int> doIntDivision(int x, int y)
{
	if (y == 0)
		return {}; // or return std::nullopt
	return x / y;
}

int main()
{
	std::optional<int> result1 { doIntDivision(20, 5) };
	if (result1) // if the function returned a value
		std::cout << "Result 1: " << *result1 << '\n'; // get the value
	else
		std::cout << "Result 1: failed\n";

	std::optional<int> result2 { doIntDivision(5, 0) };

	if (result2)
		std::cout << "Result 2: " << *result2 << '\n';
	else
		std::cout << "Result 2: failed\n";

	return 0;
}

/*
Using std::optional is quite easy. We can construct a std::optional<T> either with or without a value:

std::optional<int> o1 { 5 };            // initialize with a value
std::optional<int> o2 {};               // initialize with no value
std::optional<int> o3 { std::nullopt }; // initialize with no value
 */

/*
To see if a std::optional has a value, we can choose one of the following:

if (o1.has_value()) // call has_value() to check if o1 has a value
if (o2)             // use implicit conversion to bool to check if o2 has a value
 */

/*
To get the value from a std::optional, we can choose one of the following:

std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)
 */

/*
Note that std::optional has a usage syntax that is essentially identical to a pointer:

Behavior				Pointer										std::optional
Hold no value			initialize/assign {} or std::nullptr		initialize/assign {} or std::nullopt
Hold a value			initialize/assign an address				initialize/assign a value
Check if has value		implicit conversion to bool					implicit conversion to bool or has_value()
Get value				dereference									dereference or value()


However, semantically, a pointer and a std::optional are quite different.

A pointer has reference semantics, meaning it references some other object, and assignment copies the pointer,
not the object. If we return a pointer by address, the pointer is copied back to the caller, not the object being
pointed to. This means we can’t return a local object by address, as we’ll copy that object’s address back to the
caller, and then the object will be destroyed, leaving the returned pointer dangling.

A std::optional has value semantics, meaning it actually contains its value, and assignment copies the value.
If we return a std::optional by value, the std::optional (including the contained value) is copied back to the caller.
This means we can return a value from the function back to the caller using std::optional.

With this in mind, let’s look at how our example works. Our doIntDivision() now returns a std::optional<int> instead
of an int. Inside the function body, if we detect an error, we return {}, which implicitly returns a std::optional
containing no value. If we have a value, we return that value, which implicit returns a std::optional containing
that value.

Within main(), we use an implicit conversion to bool to check if our returned std::optional has a value or not. If it
does, we dereference the std::optional object to get the value. If it doesn’t, then we execute our error condition.
That’s it!
 */

/*
std::expected (introduced in C++23) is designed to handle the case where a function can return either an expected
value or an unexpected error code. See the std::expected reference for more information:
https://en.cppreference.com/w/cpp/utility/expected.html

Example below:

#include <iostream>
#include <expected>
#include <string>

enum class Math_Error
{
	DIVISION_BY_ZERO,
	OVERFLOW
};

std::expected<int, Math_Error> safe_divide(int x, int y)
{
	if (y == 0)
		return std::unexpected(Math_Error::DIVISION_BY_ZERO);

	if (x > 1000 && y == 1) // example 2nd fail condition
		return std::unexpected(Math_Error::OVERFLOW);

	return x / y;
}

void test(int x, int y)
{
	std::cout << x << " / " << y << " = ";

	auto result = safe_divide(x, y);

	if (result) {
		std::cout << *result << '\n';
	} else {
		switch (result.error()) {
			case Math_Error::DIVISION_BY_ZERO:
				std::cout << "Error: Cannot divide by zero\n";
				break;
			case Math_Error::OVERFLOW:
				std::cout << "Error: Result too large\n";
				break;
		}
	}
}

 */