// To allocate an array dynamically, we use the array form of new and delete (often called new[] and delete[]):

#include <cstddef>
#include <iostream>

int main()
{
	std::cout << "Enter a positive integer: ";
	std::size_t length{};
	std::cin >> length;

	int* array{ new int[length]{} }; // use array new.  Note that length does not need to be constant!

	std::cout << "I just allocated an array of integers of length " << length << '\n';

	array[0] = 5; // set element 0 to value 5

	delete[] array; // use array delete to deallocate array

	// we don't need to set array to nullptr/0 here because it's going out of scope immediately after this anyway

	// The length of dynamically allocated arrays has type std::size_t. If you are using a non-constexpr int,
	// you’ll need to static_cast to std::size_t since that is considered a narrowing conversion and your
	// compiler will warn otherwise.


	// starting with C++11, it’s now possible to initialize dynamic arrays using initializer lists:

	// int fixedArray[5] = { 9, 7, 5, 3, 1 }; // initialize a fixed array before C++11
	// int* array{ new int[5]{ 9, 7, 5, 3, 1 } }; // initialize a dynamic array since C++11
	// // To prevent writing the type twice, we can use auto. This is often done for types with long names.
	// auto* array{ new int[5]{ 9, 7, 5, 3, 1 } };

	// Note that this syntax has no operator= between the array length and the initializer list.
	// For consistency, fixed arrays can also be initialized using uniform initialization:

	// int fixedArray[]{ 9, 7, 5, 3, 1 }; // initialize a fixed array in C++11
	// char fixedArray[]{ "Hello, world!" }; // initialize a fixed array in C++11

	return 0;
}

/*
Resizing arrays:

Dynamically allocating an array allows you to set the array length at the time of allocation. However, C++ does not
provide a built-in way to resize an array that has already been allocated. It is possible to work around this
limitation by dynamically allocating a new array, copying the elements over, and deleting the old array. However,
this is error prone, especially when the element type is a class (which have special rules governing how they are created).

Consequently, we recommend avoiding doing this yourself. Use std::vector instead.
 */