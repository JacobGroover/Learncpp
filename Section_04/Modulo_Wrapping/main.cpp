#include <iostream>

int main()
{
    unsigned short x{ 65535 }; // largest 16-bit unsigned value possible
    std::cout << "x was: " << x << '\n';

    x = 65536; // 65536 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = 65537; // 65537 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    unsigned short x2{ 0 }; // smallest 2-byte unsigned value possible
    std::cout << "x2 was: " << x2 << '\n';

    x2 = -1; // -1 is out of our range, so we get modulo wrap-around
    std::cout << "x2 is now: " << x2 << '\n';

    x2 = -2; // -2 is out of our range, so we get modulo wrap-around
    std::cout << "x2 is now: " << x2 << '\n';

    /*
     * In C++, if a mathematical operation (e.g. arithmetic or comparison) has one signed integer and
     * one unsigned integer, the signed integer will usually be converted to an unsigned integer.
     * And the result will thus be unsigned. For example:
     */
    unsigned int u{ 2 };
    signed int s{ 3 };

    std::cout << u - s << '\n'; // 2 - 3 = 4294967295

    signed int s2 { -1 };
    unsigned int u2 { 1 };

    if (s2 < u2) // -1 is implicitly converted to 4294967295, and 4294967295 < 1 is false
        std::cout << "-1 is less than 1\n";
    else
        std::cout << "1 is less than -1\n"; // this statement executes

    return 0;
}