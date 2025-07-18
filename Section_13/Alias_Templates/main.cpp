/*
There are a couple of things worth noting about this example.

First, unlike normal type aliases (which can be defined inside a block), alias templates must be defined
in the global scope (as all templates must).

Second, prior to C++20, we must explicitly specify the template arguments when we instantiate an object
using an alias template. As of C++20, we can use alias template deduction, which will deduce the type of
the template arguments from an initializer in cases where the aliased type would work with CTAD.

Third, because CTAD doesn’t work on function parameters, when we use an alias template as a function
parameter, we must explicitly define the template arguments used by the alias template.
 */

#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's our alias template
// Alias templates must be defined in global scope
template <typename T>
using Coord = Pair<T>; // Coord is an alias for Pair<T>

// Our print function template needs to know that Coord's template parameter T is a type template parameter
template <typename T>
void print(const Coord<T>& c)
{
    std::cout << c.first << ' ' << c.second << '\n';
}

int main()
{
    Coord<int> p1 { 1, 2 }; // Pre C++-20: We must explicitly specify all type template argument
    Coord p2 { 1, 2 };      // In C++20, we can use alias template deduction to deduce the template arguments in cases where CTAD works

    std::cout << p1.first << ' ' << p1.second << '\n';
    print(p2);

    return 0;
}