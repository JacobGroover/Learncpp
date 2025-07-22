/*
Selection sort performs the following steps to sort an array from smallest to largest:

1. Starting at array index 0, search the entire array to find the smallest value
2. Swap the smallest value found in the array with the value at index 0
3. Repeat steps 1 & 2 starting from the next index
 */

#include <iostream>
#include <iterator>
#include <utility>

int main()
{
	int array[]{ 30, 50, 20, 10, 40 };
	constexpr int length{ static_cast<int>(std::size(array)) };

	// Step through each element of the array
	// (except the last one, which will already be sorted by the time we get there)
	for (int startIndex{ 0 }; startIndex < length - 1; ++startIndex)
	{
		// smallestIndex is the index of the smallest element we’ve encountered this iteration
		// Start by assuming the smallest element is the first element of this iteration
		int smallestIndex{ startIndex };

		// Then look for a smaller element in the rest of the array
		for (int currentIndex{ startIndex + 1 }; currentIndex < length; ++currentIndex)
		{
			// If we've found an element that is smaller than our previously found smallest
			if (array[currentIndex] < array[smallestIndex])
				// then keep track of it
					smallestIndex = currentIndex;
		}

		// smallestIndex is now the index of the smallest element in the remaining array
		// swap our start element with our smallest element (this sorts it into the correct place)
		std::swap(array[startIndex], array[smallestIndex]);
	}

	// Now that the whole array is sorted, print our sorted array as proof it works
	for (int index{ 0 }; index < length; ++index)
		std::cout << array[index] << ' ';

	std::cout << '\n';

	return 0;
}


/*
Because sorting arrays is so common, the C++ standard library includes a sorting function
named std::sort. std::sort lives in the <algorithm> header, and can be invoked on an array like so:
 */

// #include <algorithm> // for std::sort
// #include <iostream>
// #include <iterator> // for std::size
//
// int main()
// {
// 	int array[]{ 30, 50, 20, 10, 40 };
//
// 	std::sort(std::begin(array), std::end(array));
//
// 	for (int i{ 0 }; i < static_cast<int>(std::size(array)); ++i)
// 		std::cout << array[i] << ' ';
//
// 	std::cout << '\n';
//
// 	return 0;
// }


/*
 Bubble Sort below:
 */

// #include <iostream>
// #include <iterator> // for std::size
// #include <utility>
//
// int main()
// {
// 	int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
// 	constexpr int length{ static_cast<int>(std::size(array)) }; // C++17
// 	//  constexpr int length{ sizeof(array) / sizeof(array[0]) }; // use instead if not C++17 capable
//
// 	// Step through each element of the array (except the last, which will already be sorted by the time we get to it)
// 	for (int iteration{ 0 }; iteration < length-1; ++iteration)
// 	{
// 		// Search through all elements up to the end of the array - 1
// 		// The last element has no pair to compare against
// 		for (int currentIndex{ 0 }; currentIndex < length - 1; ++currentIndex)
// 		{
// 			// If the current element is larger than the element after it, swap them
// 			if (array[currentIndex] > array[currentIndex+1])
// 				std::swap(array[currentIndex], array[currentIndex + 1]);
// 		}
// 	}
//
// 	// Now print our sorted array as proof it works
// 	for (int index{ 0 }; index < length; ++index)
// 		std::cout << array[index] << ' ';
//
// 	std::cout << '\n';
//
// 	return 0;
// }


/*
Add two optimizations to the bubble sort algorithm you wrote in the bubble sort:

Notice how with each iteration of bubble sort, the biggest number remaining gets bubbled to the end of the array.
After the first iteration, the last array element is sorted. After the second iteration, the second to last array
element is sorted too. And so on… With each iteration, we don’t need to recheck elements that we know are already
sorted. Change your loop to not re-check elements that are already sorted.

If we go through an entire iteration without doing a swap, then we know the array must already be sorted.
Implement a check to determine whether any swaps were made this iteration, and if not, terminate the loop early.
If the loop was terminated early, print on which iteration the sort ended early.

Your output should match this:

Early termination on iteration 6
1 2 3 4 5 6 7 8 9
 */

// #include <iostream>
// #include <iterator> // for std::size
// #include <utility>
//
// int main()
// {
// 	int array[]{ 6, 3, 2, 9, 7, 1, 5, 4, 8 };
// 	constexpr int length{ static_cast<int>(std::size(array)) }; // C++17
// 	//  constexpr int length{ sizeof(array) / sizeof(array[0]) }; // use instead if not C++17 capable
//
// 	// Step through each element of the array except the last
// 	for (int iteration{ 0 }; iteration < length-1; ++iteration)
// 	{
// 		// Account for the fact that the last element is already sorted with each subsequent iteration
// 		// so our array "ends" one element sooner
// 		int endOfArrayIndex{ length - iteration };
//
// 		bool swapped{ false }; // Keep track of whether any elements were swapped this iteration
//
// 		// Search through all elements up to the end of the array - 1
// 		// The last element has no pair to compare against
// 		for (int currentIndex{ 0 }; currentIndex < endOfArrayIndex - 1; ++currentIndex)
// 		{
// 			// If the current element is larger than the element after it
// 			if (array[currentIndex] > array[currentIndex + 1])
// 			{
// 				// Swap them
// 				std::swap(array[currentIndex], array[currentIndex + 1]);
// 				swapped = true;
// 			}
// 		}
//
// 		// If we haven't swapped any elements this iteration, we're done early
// 		if (!swapped)
// 		{
// 			// iteration is 0 based, but counting iterations is 1-based.  So add 1 here to adjust.
// 			std::cout << "Early termination on iteration: " << iteration+1 << '\n';
// 			break;
// 		}
// 	}
//
// 	// Now print our sorted array as proof it works
// 	for (int index{ 0 }; index < length; ++index)
// 		std::cout << array[index] << ' ';
//
// 	std::cout << '\n';
//
// 	return 0;
// }