#include <iostream>

// returns true if x and y are equal, false otherwise
bool isEqual(int x, int y)
{
    return x == y; // operator== returns true if x equals y, and false otherwise
}

int main()
{
    std::cout << true << '\n'; // true evaluates to 1
    std::cout << !true << '\n'; // !true evaluates to 0

    bool b {false};
    std::cout << b << '\n'; // b is false, which evaluates to 0
    std::cout << !b << '\n'; // !b is true, which evaluates to 1

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << true << '\n'; // true evaluates to 1
    std::cout << !true << '\n'; // !true evaluates to 0

    bool b2 {false};
    std::cout << b2 << '\n'; // b is false, which evaluates to 0
    std::cout << !b2 << '\n'; // !b is true, which evaluates to 1

    std::cout << std::noboolalpha; // print bools as true or false

    std::cout << true << '\n'; // true evaluates to 1
    std::cout << !true << '\n'; // !true evaluates to 0

    bool b3 {false};
    std::cout << b3 << '\n'; // b is false, which evaluates to 0
    std::cout << !b3 << '\n'; // !b is true, which evaluates to 1


    // When using uniform initialization, you can initialize a variable using integer
    // literals 0 (for false) and 1 (for true) (but you really should be using false and
    // true instead). Other integer literals cause compilation errors:
    bool bFalse { 0 }; // okay: initialized to false
    bool bTrue  { 1 }; // okay: initialized to true
    //bool bNo    { 2 }; // error: narrowing conversions disallowed

    //std::cout << bFalse << bTrue << bNo << '\n';


    // in any context where an integer can be converted to a Boolean,
    // the integer 0 is converted to false, and any other integer is converted to true:
    std::cout << std::boolalpha; // print bools as true or false

    bool b4 = 4 ; // copy initialization allows implicit conversion from int to bool
    std::cout << b4 << '\n';

    bool b5 = 0 ; // copy initialization allows implicit conversion from int to bool
    std::cout << b5 << '\n';

    // By default, std::cin only accepts numeric input for Boolean variables: 0 is false, and 1 is true.
    // Any other numeric value will be interpreted as true, and will cause std::cin to enter failure mode.
    // Any non-numeric value will be interpreted as false and will cause std::cin to enter failure mode.

    // To allow std::cin to accept the words false and true as inputs, you must first input to std::boolalpha

    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y{};
    std::cin >> y;

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << x << " and " << y << " are equal? ";
    std::cout << isEqual(x, y) << '\n'; // will return true or false


    // if your conditional is an expression that does not evaluate to a Boolean value,
    //  the result of the conditional expression is converted to a Boolean value: non-zero values
    //  get converted to Boolean true, and zero-values get converted to Boolean false:
    int x2 { 4 };
    if (x2) // nonsensical, but for the sake of example... “if x is non-zero/non-empty”
        std::cout << "hi\n";
    else
        std::cout << "bye\n";

    return 0;
}