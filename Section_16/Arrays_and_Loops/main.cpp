/*
Arrays provide a way to store multiple objects without having to name each element.

Loops provide a way to traverse an array without having to explicitly list each element.

Templates provide a way to parameterize the element type.

Together, templates, arrays, and loops allow us to write code that can operate on a container of elements,
regardless of the element type or number of elements in the container:
 */

#include <iostream>
#include <vector>

// Function template to calculate the average of the values in a std::vector
template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
	std::size_t length { arr.size() };

	T average { 0 };                                      // if our array has elements of type T, our average should have type T too
	for (std::size_t index{ 0 }; index < length; ++index) // iterate through all the elements
		average += arr[index];                            // sum up all the elements
	average /= static_cast<int>(length);                  // divide by count of items (integral in nature)

	return average;
}

int main()
{
	std::vector class1 { 84, 92, 76, 81, 56 };
	std::cout << "The class 1 average is: " << calculateAverage(class1) << '\n'; // calc average of 5 ints

	std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
	std::cout << "The class 2 average is: " << calculateAverage(class2) << '\n'; // calc average of 4 doubles

	return 0;
}

/*
When we calculate the average, we divide the sum by the count of items. The count of items is an integral value.
Therefore, semantically, it makes more sense to divide by an int.
 */