/*
 * When a function is called, all the parameters of the function are created as variables, and the value
 * of each argument is copied into the matching parameter (using copy initialization). This process is
 * called pass by value. Function parameters that use pass by value are called value parameters.
 *
 * (Omitting pass by reference and constants here for simplicity)
 */

#include <iostream>

int getValueFromUser()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input;
}

void printDouble(int value)
{
    std::cout << value << " doubled is: " << value * 2 << '\n';
}

// add() takes two integers as parameters, and returns the result of their sum
// The values of x and y are determined by the function that calls add()
int add(int x, int y)
{
    return x + y;
}

int multiply(int z, int w)
{
    return z * w;
}

// Ok: unnamed parameter will not generate warning. The Google C++ style guide recommends using a
// comment to document what the unnamed parameter was
void doSomething(int)
{
}

// Write a function called doubleNumber() that takes one integer parameter.
// The function should return double the value of the parameter.
int doubleNumber(int value) {
    return value * 2;
}

// main takes no parameters
int main()
{
    printDouble(getValueFromUser());

    // Expected output from the following is:
    // 9, 15, 10, 7, 6, each on separate lines

    std::cout << add(4, 5) << '\n'; // within add() x=4, y=5, so x+y=9
    std::cout << add(1 + 2, 3 * 4) << '\n'; // within add() x=3, y=12, so x+y=15

    int a{ 5 };
    std::cout << add(a, a) << '\n'; // evaluates (5 + 5)

    std::cout << add(1, multiply(2, 3)) << '\n'; // evaluates 1 + (2 * 3)
    std::cout << add(1, add(2, 3)) << '\n'; // evaluates 1 + (2 + 3)

    // Write a complete program that reads an integer from the user, doubles it using the doubleNumber() function
    // you wrote in the previous quiz question, and then prints the doubled value out to the console.
    std::cout << doubleNumber(getValueFromUser()) << '\n';


    return 0;
}