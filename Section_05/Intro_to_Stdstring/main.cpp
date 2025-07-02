#include <iostream>

int main() {
	std::cout << "Enter your full name: " << "\n";
	std::string name{};
	std::getline(std::cin >> std::ws, name);

	std::cout << "Enter your age: " << "\n";
	int age{};
	std::cin >> age;

	// age is signed, and name.length() is unsigned. The two shouldn't be mixed so convert name.length() to a signed value

	// int nameLength {static_cast<int>(name.length())}; // get number of chars in name (including spaces). Best option before C++ 20
	// int nameLength {std::ssize(name)}; // Disallowed because brace initialization disallows narrowing conversions
	// int nameLength = std::ssize(name); // OK in C++ but not recommended: narrowing allowed, assumed you know what you're doing, compiler doesn't check
	int nameLength {static_cast<int>(std::ssize(name))}; // Best practice, tells compiler you're aware of the narrowing and that it's okay

	/*
	 * name.length() returns type std::size_t, an unsigned type.
	 * std::size_t is implementation-defined, but usually 32-bit for 32-bit systems, and 64-bit for 64-bit systems.
	 *
	 * std::ssize(name) returns std::ptrdiff_t, a signed type. Holds the result of subtracting one pointer from another.
	 * std::ptrdiff_t is guaranteed to be able to represent the difference between any two pointers into the same array/object.
	 * On modern 64-bit systems, it is usually a 64-bit signed integer, while int is typically 32-bit.
	 * This makes it safer and more portable when dealing with pointer math or large containers.
	 *
	 * C++20 introduced std::ssize specifically because converting unsigned sizes to signed types (especially for
	 * loops) was common and error-prone, so using std::ssize follows modern, recommended C++ style.
	 */


	std::cout << "Your age + the length of your name is: " << age + nameLength << "\n";

	return 0;
}