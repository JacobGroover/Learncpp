#include <iostream>

// https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/

int main()
{

    int a;         // default-initialization (no initializer)

    // Traditional initialization forms:
    int b = 5;     // copy-initialization (initial value after equals sign)
    int c ( 6 );   // direct-initialization (initial value in parentheses)

    // Modern initialization forms (preferred):
    int d { 7 };   // direct-list-initialization (initial value in braces)
    int e {};      // value-initialization (empty braces) / zero-initialization to value 0

    // An integer can only hold non-fractional values.
    // Initializing an int with fractional value 4.5 requires the compiler to convert 4.5 to a value an int can hold.
    // Such a conversion is a narrowing conversion, since the fractional part of the value will be lost.

    // int w1 { 4.5 }; // compile error: list-init does not allow narrowing conversion

    int w2 = 4.5;   // compiles: w2 copy-initialized to value 4
    int w3 (4.5);   // compiles: w3 direct-initialized to value 4

    // w1 = 4.5;       // okay: copy-assignment allows narrowing conversion of 4.5 to 4

    // Use direct-list-initialization when you’re actually using the initial value:
    int x { 0 };    // direct-list-initialization with initial value 0
    std::cout << x; // we're using that 0 value here

    // Use value-initialization when the object’s value is temporary and will be replaced:
    int y {};      // value initialization
    std::cin >> y; // we're immediately replacing that value so an explicit 0 would be meaningless

    int f = 4, g = 5; // correct: f and g both have initializers
    int h, i = 5;     // wrong: h doesn't have its own initializer

    [[maybe_unused]] double pi { 3.14159 };  // Don't complain if pi is unused
    [[maybe_unused]] double gravity { 9.8 }; // Don't complain if gravity is unused
    [[maybe_unused]] double phi { 1.61803 }; // Don't complain if phi is unused

    std::cout << pi << '\n';
    std::cout << phi << '\n';

    // In the case that the compiler is set to treat warnings as errors, the compiler
    // will no longer warn about gravity not being used

    return 0;

    return 0;
}
