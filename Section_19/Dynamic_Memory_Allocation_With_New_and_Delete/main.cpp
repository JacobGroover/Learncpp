#include <iostream>

void doSomething()
{
	int* ptr{ new int{} };
}	// ptr goes out of scope here without delete being called, resulting in a memory leak

int main() {
	// When you dynamically allocate a variable, you can also initialize it via direct initialization or uniform initialization:
	int* ptr1{ new int (5) }; // use direct initialization
	int* ptr2{ new int { 6 } }; // use uniform initialization

	int* ptr {new int {2} };
	// assuming ptr has previously been allocated with operator new
	delete ptr; // return the memory pointed to by ptr to the operating system
	ptr = nullptr; // set ptr to be a null pointer
	// Set deleted pointers to nullptr unless they are going out of scope immediately afterward.

	// int* value { new (std::nothrow) int }; // value will be set to a null pointer if the integer allocation fails

	// Note that if you then attempt to dereference this pointer, undefined behavior will result (most likely,
	// your program will crash). Consequently, the best practice is to check all memory requests to ensure they
	// actually succeeded before using the allocated memory:
	int* value { new (std::nothrow) int{} }; // ask for an integer's worth of memory
	if (!value) // handle case where new returned null
	{
		// Do error handling here
		std::cerr << "Could not allocate memory\n";
	}


	/*
	Although memory leaks can result from a pointer going out of scope, there are other ways that memory leaks
	can result. For example, a memory leak can occur if a pointer holding the address of the dynamically allocated
	memory is assigned another value:
	 */
	int value2 = 5;
	int* ptrLeak{ new int{} }; // allocate memory
	ptrLeak = &value2; // old address lost, memory leak results

	// This can be fixed by deleting the pointer before reassigning it:

	int value3{ 5 };
	int* ptrNoLeak{ new int{} }; // allocate memory
	delete ptrNoLeak; // return memory back to operating system
	ptrNoLeak = &value3; // reassign pointer to address of value


	// Relatedly, it is also possible to get a memory leak via double-allocation:
	int* ptrDoubleAlloc{ new int{} };
	ptrDoubleAlloc = new int{}; // old address lost, memory leak results

	/*
	The address returned from the second allocation overwrites the address of the first allocation.
	Consequently, the first allocation becomes a memory leak!

	Similarly, this can be avoided by ensuring you delete the pointer before reassigning.
	 */

	return 0;
}