#include "CalcDoubles.h"
#include "BallDrop.h"

#include <iostream>

int main() {

    double num1{enterNumber()};
    double num2{enterNumber()};
    char op{enterOperator()};
    computeAnswer(num1, num2, op);

    std::cout << '\n';

    double towerHeight{getTowerHeight()};
    for (int i{0}; i < 6; ++i) {
        printBallHeight(towerHeight, i);
    }

    return 0;
}