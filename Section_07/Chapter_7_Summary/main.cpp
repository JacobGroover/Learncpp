#include "constants.h"
#include <iostream>

int accumulate(int amount) {
	static int sum = 0;
	sum += amount;
	return sum;
}

int main() {

	// 1) Fix the following:

	std::cout << "Enter a positive number: ";
	int num{};
	std::cin >> num;


	// if (num < 0)
	// 	std::cout << "Negative number entered.  Making positive.\n";
	// num = -num;
	if (num < 0) {
		std::cout << "Negative number entered.  Making positive.\n";
		num = -num;
	}

	std::cout << "You entered: " << num << '\n' << '\n';

	// 2) Write a file named constants.h that makes the following program run.
	// If your compiler is C++17 capable, use an inline constexpr variable.
	// Otherwise, use a normal constexpr variable. maxClassSize should have value 35.

	std::cout << "How many students are in your class? ";
	int students{};
	std::cin >> students;


	if (students > Constants::maxClassSize)
		std::cout << "There are too many students in this class";
	else
		std::cout << "This class isn't too large";
	std::cout << '\n' << '\n';

	// 3) Write a function int accumulate(int x). This function should return the sum of all of the values of x
	// that have been passed to this function.
	// The following program should run and produce the output noted in comments:
	std::cout << accumulate(4) << '\n'; // prints 4
	std::cout << accumulate(3) << '\n'; // prints 7
	std::cout << accumulate(2) << '\n'; // prints 9
	std::cout << accumulate(1) << '\n'; // prints 10

	// 3b) Extra credit: What are two shortcomings of the accumulate() function above?
	// 1. There is no conventional way to reset the accumulation without restarting the program.
	// 2. There is no conventional way to have multiple accumulators running.

	return 0;
}