/*
* Write the following program: The user is asked to enter 2 floating point numbers (use doubles). The user is
* then asked to enter one of the following mathematical symbols: +, -, *, or /. The program computes the answer
* on the two numbers the user entered and prints the results. If the user enters an invalid symbol, the program
* should print nothing.
*
* Example of program:
*
* Enter a double value: 6.2
* Enter a double value: 5
* Enter +, -, *, or /: *
* 6.2 * 5 is 31
*/

#include "CalcDoubles.h"

#include <iostream>

double enterNumber() {
    std::cout << "Enter a double value: ";
    double x{};
    std::cin >> x;
    return x;
}

char enterOperator() {
    char op{};
    std::cout << "Enter +, -, *, or /: ";
    std::cin >> op;
    return op;
}

void computeAnswer(double x, double y, char op) {
    double answer{};
    if (op == '+') {
        answer = x + y;
    } else if (op == '-') {
        answer = x - y;
    } else if (op == '*') {
        answer = x * y;
    } else if (op == '/') {
        answer = x / y;
    } else {
        return;
    }
    std::cout << x << " " << op << " " << y << " is: " << answer << '\n';
}