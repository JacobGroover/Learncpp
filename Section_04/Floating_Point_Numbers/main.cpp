#include <iostream>
#include <limits>
#include <iomanip> // for output manipulator std::setprecision()

// You can see if your floating point types are IEEE 754 compatible with the following code:

int main()
{
    std::cout << std::boolalpha; // print bool as true or false rather than 1 or 0
    std::cout << "float: " << std::numeric_limits<float>::is_iec559 << '\n';
    std::cout << "double: " << std::numeric_limits<double>::is_iec559 << '\n';
    std::cout << "long double: " << std::numeric_limits<long double>::is_iec559 << '\n';

    // IEEE 754 single-precision (4 bytes)	±1.18 x 10-38 to ±3.4 x 1038 and 0.0	        6-9 significant digits, typically 7
    // IEEE 754 double-precision (8 bytes)	±2.23 x 10-308 to ±1.80 x 10308 and 0.0	        15-18 significant digits, typically 16
    // x87 extended-precision (80 bits)	±3.36 x 10-4932 to ±1.18 x 104932 and 0.0	        18-21 significant digits
    // IEEE 754 quadruple-precision (16 bytes)	±3.36 x 10-4932 to ±1.18 x 104932 and 0.0	33-36 significant digits


    std::cout << std::setprecision(17); // show 17 digits of precision
    std::cout << 3.33333333333333333333333333333333333333f <<'\n'; // f suffix means float
    std::cout << 3.33333333333333333333333333333333333333 << '\n'; // no suffix means double

    // Precision issues don’t just impact fractional numbers, they impact any number with too many significant digits:
    float f { 123456789.0f }; // f has 10 significant digits
    std::cout << std::setprecision(9); // to show 9 digits in f
    std::cout << f << '\n';


    /*
     * Floating point numbers are tricky to work with due to non-obvious differences between binary
     * (how data is stored) and decimal (how we think) numbers. Consider the fraction 1/10. In decimal,
     * this is easily represented as 0.1, and we are used to thinking of 0.1 as an easily representable
     * number with 1 significant digit. However, in binary, decimal value 0.1 is represented by the infinite
     * sequence: 0.00011001100110011… Because of this, when we assign 0.1 to a floating point number, we’ll
     * run into precision problems.
     */
    double d{0.1};
    std::cout << d << '\n'; // use default cout precision of 6
    std::cout << std::setprecision(17);
    std::cout << d << '\n';


    // Rounding errors can have unexpected consequences:
    std::cout << std::setprecision(17);

    double d1{ 1.0 };
    std::cout << d1 << '\n';

    double d2{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 }; // should equal 1.0
    std::cout << d2 << '\n';


    // IEEE 754 compatible formats additionally support some special values:

    // Inf, which represents infinity. Inf is signed, and can be positive (+Inf) or negative (-Inf).
    // NaN, which stands for “Not a Number”. There are several different kinds of NaN (which we won’t discuss here).
    // Signed zero, meaning there are separate representations for “positive zero” (+0.0) and “negative zero” (-0.0).
    // Formats that are not compatible with IEEE 754 may not support some (or any) of these values. In such cases, code that uses or generates these special values will produce implementation-defined behavior.

    // Here’s a program showing all three:

    double zero{0.0};

    double posinf{5.0 / zero}; // positive infinity
    std::cout << posinf << '\n';

    double neginf{-5.0 / zero}; // negative infinity
    std::cout << neginf << '\n';

    double z1{0.0 / posinf}; // positive zero
    std::cout << z1 << '\n';

    double z2{-0.0 / posinf}; // negative zero
    std::cout << z2 << '\n';

    double nan{zero / zero}; // not a number (mathematically invalid)
    std::cout << nan << '\n';

    return 0;
}
