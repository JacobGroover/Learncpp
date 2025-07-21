#include <iostream>
#include <vector>
#include "SignedArrayView.h"

/*
 Both of the following approaches to indexing arrays should be equally performant on modern compilers.

 The first one is more boilerplate, slightly better for readability and reusability.

 The second one is less boilerplate, and has a small chance of being more performant if
 the compiler doesn't inline the SignedArrayView wrapper.
 */

int main()
{
	std::vector arr{ 9, 7, 5, 3, 1 };
	SignedArrayView sarr{ arr }; // Create a signed view of our std::vector

	for (auto index{ sarr.ssize() - 1 }; index >= 0; --index)
		std::cout << sarr[index] << ' '; // index using a signed type

	return 0;


	// Or index the underlying C-style array instead:

	// std::vector arr{ 9, 7, 5, 3, 1 };
	//
	// using Index = std::ptrdiff_t; // in C++20, prefer std::ssize(), and therefore omit this line
	// auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
	// for (auto index{ length - 1 }; index >= 0; --index)
	// 	std::cout << arr.data()[index] << ' ';       // use data() to avoid sign conversion warning
	//
	// return 0;

	/*
	 Advantages of this approach:
	1. We can use signed loop variables and indices.
	2. We don’t have to define any custom types or type aliases.
	3. The hit to readability from using data() isn’t very big.
	4. There should be no performance hit in optimized code.
	 */
}