/*
 * it is a best practice for code files to #include their paired header file (if one exists).
 * This allows the compiler to catch certain kinds of errors at compile time instead of link time,
 * which can save time, especially on large projects where compile and link times can be long.
 */
#include "io.h"

#include <iostream>

// Get and return a single integer from the user
int readNumber() {
	std::cout << "Enter a number: ";
	int num{};
	std::cin >> num;
	return num;
}

// Output the answer
void writeAnswer(int answer) {
	std::cout << "Answer: " << answer << '\n';
}