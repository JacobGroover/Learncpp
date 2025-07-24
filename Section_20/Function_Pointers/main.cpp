/*
 SUMMARY:
Function pointers are useful primarily when you want to store functions in an array (or other structure),
or when you need to pass a function to another function. Because the native syntax to declare function pointers
is ugly and error prone, we recommend using std::function. In places where a function pointer type is only used
once (e.g. a single parameter or return value), std::function can be used directly. In places where a function
pointer type is used multiple times, a type alias to a std::function is a better choice (to prevent repeating yourself).
 */

/*
 Because the resolution happens at runtime, default arguments are not resolved when a
 function is called through a function pointer.

This means that we can use a function pointer to disambiguate a function call that would
otherwise be ambiguous due to default arguments. In the following example, we show two ways to do this:
*/

// #include <iostream>
//
// void print(int x)
// {
// 	std::cout << "print(int)\n";
// }
//
// void print(int x, int y = 10)
// {
// 	std::cout << "print(int, int)\n";
// }
//
// int main()
// {
// 	//    print(1); // ambiguous function call
//
// 	// Deconstructed method
// 	using vnptr = void(*)(int); // define a type alias for a function pointer to a void(int) function
// 	vnptr pi { print }; // initialize our function pointer with function print
// 	pi(1); // call the print(int) function through the function pointer
//
// 	// Concise method
// 	static_cast<void(*)(int)>(print)(1); // call void(int) version of print with argument 1
//
// 	return 0;
// }

/*
== CALLBACK FUNCTIONS ==

Here’s a full example of a selection sort that uses a function pointer parameter to do a user-defined comparison,
along with an example of how to call it:
 */
#include <utility> // for std::swap
#include <iostream>

// Here is a comparison function that sorts in ascending order
// (Note: it's exactly the same as the previous ascending() function)
bool ascending(int x, int y)
{
    return x > y; // swap if the first element is greater than the second
}

// Here is a comparison function that sorts in descending order
bool descending(int x, int y)
{
    return x < y; // swap if the second element is greater than the first
}

// Note our user-defined comparison is the third parameter
void selectionSort(int* array, int size, bool comparisonFcn(int, int) = ascending) // This line also works, see notes below
// void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))
{
    if (!array || !comparisonFcn)
        return;

    // Step through each element of the array
    for (int startIndex{ 0 }; startIndex < (size - 1); ++startIndex)
    {
        // bestIndex is the index of the smallest/largest element we've encountered so far.
        int bestIndex{ startIndex };

        // Look for smallest/largest element remaining in the array (starting at startIndex+1)
        for (int currentIndex{ startIndex + 1 }; currentIndex < size; ++currentIndex)
        {
            // If the current element is smaller/larger than our previously found smallest
            if (comparisonFcn(array[bestIndex], array[currentIndex])) // COMPARISON DONE HERE
            {
                // This is the new smallest/largest number for this iteration
                bestIndex = currentIndex;
            }
        }

        // Swap our start element with our smallest/largest element
        std::swap(array[startIndex], array[bestIndex]);
    }
}

// This function prints out the values in the array
void printArray(int* array, int size)
{
    if (!array)
        return;

    for (int index{ 0 }; index < size; ++index)
    {
        std::cout << array[index] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    int array[9]{ 3, 7, 9, 5, 6, 1, 8, 2, 4 };

    // Sort the array in descending order using the descending() function
    selectionSort(array, 9, descending);
    printArray(array, 9);

    // Sort the array in ascending order using the ascending() function
    selectionSort(array, 9, ascending);
    printArray(array, 9);

    // Sort using default function parameter
    selectionSort(array, 9);
    printArray(array, 9);

    return 0;
}

/*
NOTE: If a function parameter is of a function type, it will be converted to a pointer to the function type. This means:

void selectionSort(int* array, int size, bool (*comparisonFcn)(int, int))

can be equivalently written as:

void selectionSort(int* array, int size, bool comparisonFcn(int, int))

This only works for function parameters, and so is of somewhat limited use.
On a non-function parameter, the latter is interpreted as a forward declaration:

bool (*ptr)(int, int); // definition of function pointer ptr
bool fcn(int, int);    // forward declaration of function fcn

NOTE: Can also allow for default parameters.
In this case, as long as the user calls selectionSort normally (not through a function pointer), the
comparisonFcn parameter will call the default parameter. You will need to ensure the function assigned as the default
parameter is declared prior to this point, otherwise the compiler will complain it doesn't recognize the function.
 */

/*
 NOTE:
type aliases can be used to make pointers to functions look more like regular variables:

using ValidateFunction = bool(*)(int, int);
This defines a type alias called “ValidateFunction” that is a pointer to a function that takes two ints and returns a bool.

Now instead of doing this:
bool validate(int x, int y, bool (*fcnPtr)(int, int)); // ugly

You can do this:
bool validate(int x, int y, ValidateFunction pfcn) // clean
 */

/*
Using std::function

An alternate method of defining and storing function pointers is to use std::function, which is part of the standard
library <functional> header. To define a function pointer using this method, declare a std::function object like so:

#include <functional>
bool validate(int x, int y, std::function<bool(int, int)> fcn); // std::function method that returns a bool and
takes two int parameters

As you see, both the return type and parameters go inside angled brackets, with the parameters inside parentheses.
If there are no parameters, the parentheses can be left empty.

Updating our earlier example with std::function:
 */

// #include <functional>
// #include <iostream>
//
// int foo()
// {
//     return 5;
// }
//
// int goo()
// {
//     return 6;
// }
//
// int main()
// {
//     std::function<int()> fcnPtr{ &foo }; // declare function pointer that returns an int and takes no parameters
//     fcnPtr = &goo; // fcnPtr now points to function goo
//     std::cout << fcnPtr() << '\n'; // call the function just like normal
//
//     std::function fcnPtr2{ &foo }; // can also use CTAD to infer template arguments
//
//     return 0;
// }

/*
Type aliasing std::function can be helpful for readability:

using ValidateFunctionRaw = bool(*)(int, int); // type alias to raw function pointer
using ValidateFunction = std::function<bool(int, int)>; // type alias to std::function
Also note that std::function only allows calling the function via implicit dereference
(e.g. fcnPtr()), not explicit dereference (e.g. (*fcnPtr)()).

When defining a type alias, we must explicitly specify any template arguments. We can’t use CTAD in
this case since there is no initializer to deduce the template arguments from.
 */

/*
Much like the auto keyword can be used to infer the type of normal variables, the auto keyword
can also infer the type of a function pointer.

This works exactly like you’d expect, and the syntax is very clean. The downside is, of course, that all the
details about the function’s parameters types and return type are hidden, so it’s easier to make a mistake when
making a call with the function, or using its return value.
 */