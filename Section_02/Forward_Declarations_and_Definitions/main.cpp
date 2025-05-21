// Code files compile sequentially in C++, so defining the add function after main will result in a compiler error.
// This can be resolved by re-ordering the function so it is defined before the main function, but this is not always
// possible. Let’s say we’re writing a program that has two functions A and B. If function A calls function B, and
// function B calls function A, then there’s no way to order the functions in a way that will make the compiler happy.

// Another way of resolving this is to use a forward declaration, which allows us to tell the compiler about the
// existence of an identifier before actually defining the identifier.

// Most often, forward declarations are used to tell the compiler about the existence of some function that has been
// defined in a different code file. Reordering isn’t possible in this scenario because the caller and the callee are
// in completely different files.

#include <iostream>

// To write a forward declaration for a function, we use a function declaration (a.k.a. a function prototype).
// Function declaration includes return type, name, parameters, and semicolon.  No function body!
// Can be written without the parameter names, though this is discouraged since it can make their use less clear.
// These will traditionally be written in the header file later:
int add(int x, int y);
int subtract(int x, int y); // Forward declaration for a function in a different file

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    std::cout << "The difference of 3 and 4 is: " << subtract(3, 4) << '\n';
    return 0;
}

int add(int x, int y)
{
    return x + y;
}