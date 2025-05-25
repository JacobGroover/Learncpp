#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>
#include <climits> // for CHAR_BIT

// NOTE:
// sizeof does not include dynamically allocated memory used by an object

// NOTE:
// You might assume that types that use less memory would be faster than types that use more memory.
// This is not always true. CPUs are often optimized to process data of a certain size (e.g. 32 bits),
// and types that match that size may be processed quicker. On such a machine, a 32-bit int could be faster
// than a 16-bit short or an 8-bit char.

int main()
{
    std::cout << "A byte is " << CHAR_BIT << " bits\n\n";

    std::cout << std::left; // left justify output

    std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
    std::cout << std::setw(16) << "char:" << sizeof(char) << " bytes\n";
    std::cout << std::setw(16) << "short:" << sizeof(short) << " bytes\n";
    std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
    std::cout << std::setw(16) << "long:" << sizeof(long) << " bytes\n";
    std::cout << std::setw(16) << "long long:" << sizeof(long long) << " bytes\n";
    std::cout << std::setw(16) << "float:" << sizeof(float) << " bytes\n";
    std::cout << std::setw(16) << "double:" << sizeof(double) << " bytes\n";
    std::cout << std::setw(16) << "long double:" << sizeof(long double) << " bytes\n";

    // You can also use the sizeof operator on a variable name:

    int x{};
    std::cout << "x is " << sizeof(x) << " bytes\n";

    return 0;
}
