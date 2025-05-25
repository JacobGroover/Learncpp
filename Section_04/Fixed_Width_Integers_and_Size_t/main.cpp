// Use a fixed-width integer type when you need an integral type that has a guaranteed range across many devices

// std::int8_t	1 byte signed	-128 to 127	            Treated like a signed char on many systems.
// std::uint8_t	1 byte unsigned	0 to 255	            Treated like an unsigned char on many systems.
// std::int16_t	2 byte signed	-32,768 to 32,767
// std::uint16_t	2 byte unsigned	0 to 65,535
// std::int32_t	4 byte signed	-2,147,483,648 to 2,147,483,647
// std::uint32_t	4 byte unsigned	0 to 4,294,967,295
// std::int64_t	8 byte signed	-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
// std::uint64_t	8 byte unsigned	0 to 18,446,744,073,709,551,615

#include <cstdint> // for fixed-width integers
#include <iostream>
#include <cstddef>  // for std::size_t

int main()
{
    std::int32_t x { 32767 }; // x is always a 32-bit integer
    x = x + 1;                // so 32768 will always fit
    std::cout << x << '\n';

    /*
     * Due to an oversight in the C++ specification, modern compilers typically treat std::int8_t
     * and std::uint8_t (and the corresponding fast and least fixed-width types) the same as signed
     * char and unsigned char respectively. Thus on most modern systems, the 8-bit fixed-width
     * integral types will behave like char types.
     */

    std::int8_t x2 { 65 };   // initialize 8-bit integral type with value 65
    std::cout << x2 << '\n'; // You're probably expecting this to print 65


    /*
    * The fast types (std::int_fast#_t and std::uint_fast#_t) provide the fastest signed/unsigned integer type
    * with a width of at least # bits (where # = 8, 16, 32, or 64). For example, std::int_fast32_t will give you
    * the fastest signed integer type that’s at least 32-bits. By fastest, we mean the integral type that can be
    * processed most quickly by the CPU.
    *
    * The least types (std::int_least#_t and std::uint_least#_t) provide the smallest signed/unsigned integer type
    * with a width of at least # bits (where # = 8, 16, 32, or 64). For example, std::uint_least32_t will give you
    * the smallest unsigned integer type that’s at least 32-bits.
     */

    std::cout << "least 8:  " << sizeof(std::int_least8_t)  * 8 << " bits\n";
    std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
    std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
    std::cout << '\n';
    std::cout << "fast 8:  "  << sizeof(std::int_fast8_t)   * 8 << " bits\n";
    std::cout << "fast 16: "  << sizeof(std::int_fast16_t)  * 8 << " bits\n";
    std::cout << "fast 32: "  << sizeof(std::int_fast32_t)  * 8 << " bits\n";

    /*
    * these fast and least integers have their own downsides. First, not many programmers actually use them, and a
    * lack of familiarity can lead to errors. Then the fast types can also lead to memory wastage, as their actual
    * size may be significantly larger than indicated by their name.
    *
    * Most seriously, because the size of the fast/least integers is implementation-defined, your program may exhibit
    * different behaviors on architectures where they resolve to different sizes. For example:
     */

     std::uint_fast16_t sometype { 0 };
     sometype = sometype - 1; // intentionally overflow to invoke wraparound behavior

     std::cout << sometype << '\n';

     // This code will produce different results depending on whether std::uint_fast16_t is 16, 32, or 64 bits!
     // This is exactly what we were trying to avoid by using fixed-width integers in the first place!


     // std::size_t is an alias for an implementation-defined unsigned integral type.
     // It is used within the standard library to represent the byte-size or length of objects.
     // In other words, the compiler decides if std::size_t is an unsigned int, an unsigned long,
     // an unsigned long long, etc…
     std::cout << sizeof(int) << '\n';

     int x3 { 5 };
     std::size_t s { sizeof(x3) }; // sizeof returns a value of type std::size_t, so that should be the type of s
     std::cout << s << '\n';

    return 0;
}