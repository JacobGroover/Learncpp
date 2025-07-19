#include "pair.h"
#include <iostream>

void foo(); // forward declaration for function foo()

int main()
{
	Pair<double> p2 { 3.4, 5.6 };
	std::cout << max(p2) << " is larger\n";

	foo();

	return 0;
}

/*
Separate from the multi-file class templates in this project, below is a simple program with a deduction guide
for helping Class Template Argument Deduction (CTAD) identify proper class type deductions:
*/

// template <typename T, typename U>
// struct PairCTAD
// {
// 	T first{};
// 	U second{};
// };
//
// // Here's a deduction guide for our Pair (needed in C++17 only)
// // Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
// template <typename T, typename U>
// PairCTAD(T, U) -> PairCTAD<T, U>;
//
// int main() {
// 	PairCTAD<int, int> pCtad1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
// 	PairCTAD pCtad2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)
//
// 	// C++20 added the ability for the compiler to automatically generate deduction guides for aggregates,
// 	// so deduction guides should only need to be provided for C++17 compatibility.
//
// 	return 0;
// }