/*
Container classes typically implement a fairly standardized minimal set of functionality.
Most well-defined containers will include functions that:

Create an empty container (via a constructor)
Insert a new object into the container
Remove an object from the container
Report the number of objects currently in the container
Empty the container of all objects
Provide access to the stored objects
Sort the elements (optional)
*/

/*
In this example, we are going to write an integer array class from scratch that implements most of the common
functionality that containers should have. This array class is going to be a value container, which will hold
copies of the elements it’s organizing. As the name suggests, the container will hold an array of integers,
similar to std::vector<int>.
 */

#include <iostream>
#include "IntArray.h"

int main()
{
	// Declare an array with 10 elements
	IntArray array(10);

	// Fill the array with numbers 1 through 10
	for (int i{ 0 }; i<10; ++i)
		array[i] = i+1;

	// Resize the array to 8 elements
	array.resize(8);

	// Insert the number 20 before element with index 5
	array.insertBefore(20, 5);

	// Remove the element with index 3
	array.remove(3);

	// Add 30 and 40 to the end and beginning
	array.insertAtEnd(30);
	array.insertAtBeginning(40);

	// A few more tests to ensure copy constructing / assigning arrays
	// doesn't break things
	{
		IntArray b{ array };
		b = array;
		b = b;
		array = array;
	}

	// Print out all the numbers
	for (int i{ 0 }; i<array.getLength(); ++i)
		std::cout << array[i] << ' ';

	std::cout << '\n';

	return 0;
}

/*
Although writing container classes can be pretty complex, the good news is that you only have to write them once.
Once the container class is working, you can use and reuse it as often as you like without any additional
programming effort required.

A few additional improvements that could/should be made:

We could have made this a template class, so that it would work with any copyable type rather than just int.
We should add const overloads of various member functions to properly support const IntArrays.
We should add support for move semantics (via adding a move constructor and move assignment).
When performing resize or insertion operations, we can move elements instead of copying them.
 */

/*
Some advanced improvements related to exception handling:

- When performing resize or insertion operations, move elements only if their move constructor is noexcept,
otherwise copy them (27.10 -- std::move_if_noexcept).

- Provide a strong exception safety guarantee for resize or insertion operations
(27.9 -- Exception specifications and noexcept).
 */

/*
One more thing: If a class in the standard library meets your needs, use that instead of creating your own.
For example, instead of using IntArray, you’re better off using std::vector<int>. It’s battle tested, efficient,
and plays nicely with the other classes in the standard library. But sometimes you need a specialized container
class that doesn’t exist in the standard library, so it’s good to know how to create your own when you need to.
 */