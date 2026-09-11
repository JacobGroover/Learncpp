# Learn C++

A structured, hands-on pass through [learncpp.com](https://www.learncpp.com/), from the fundamentals through move semantics, templates, and exceptions, as groundwork for C++ graphics and systems work.

Every lesson and exercise is its own small CMake project, compiled as C++23 with strict warnings enabled.

## At a glance

- **115** standalone lesson projects across **28** sections
- **~14,500** lines of C++ (138 source files, 18 headers)
- **C++23**, GCC 13.1, CMake
- Warnings: `-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Weffc++`
- May – December 2025

## What's covered

| Sections | Topics |
| --- | --- |
| 01 – 04 | Basics, functions and multi-file programs, debugging, fundamental types (booleans, fixed-width integers, floating point, `sizeof`) |
| 05 – 09 | `std::string`, operators, scope, control flow, random numbers with Mersenne Twister, `assert` / `static_assert`, validating `std::cin` input |
| 12 – 13 | References and pointers, `std::optional`, enumerations, alias and class templates, overloading the I/O operators |
| 14 – 15 | Classes: member initializer lists, destructors, the `this` pointer and member-function chaining, static members, friends, nested types, ref qualifiers, classes in header files |
| 16 – 18 | `std::vector`, `std::array`, iterators, standard library algorithms, selection sort, timing code |
| 19 – 20 | Dynamic allocation with `new` / `delete`, dynamic arrays, pointers to pointers, void pointers, function pointers, lambdas and captures, recursion, command-line arguments |
| 21 – 23 | Operator overloading, move semantics and smart pointers, object relationships (composition, aggregation, association, dependencies, container classes, `std::initializer_list`) |
| 24 – 26 | Inheritance and multiple inheritance, virtual functions, abstract base and interface classes, `override` / `final`, virtual base classes, class templates, non-type template parameters, full and partial template specialization |
| 27 – 28 | Exceptions (`noexcept`, function try blocks, rethrowing, `std::move_if_noexcept`), stream I/O, file I/O, random file access, stream states and input validation |
| F, O | `constexpr` and `consteval` functions; bit manipulation with bitwise operators, bit masks, and `std::bitset` |

## Highlights

- **Blackjack** (`Section_17/Blackjack`): a console game that models cards and a deck with enums and structs, shuffles with `std::shuffle`, and plays out player and dealer turns.
- **Smart pointers and move semantics** (`Section_22`): `std::unique_ptr`, `std::shared_ptr`, move constructors and assignment, and breaking a `std::shared_ptr` reference cycle with `std::weak_ptr`.
- **Template specialization** (`Section_26`): full and partial specialization, including partial specialization for pointers.
- **Chapter summaries** (`Chapter_XX_Summary`): end-of-chapter programs that combine each chapter's concepts.

## Building a lesson

Each folder with a `CMakeLists.txt` builds on its own. You'll need a C++23 compiler (developed with GCC 13.1) and CMake 3.31 or newer.

```bash
cd Section_17/Blackjack
cmake -S . -B build
cmake --build build
```

The executable is written to `build/`.

New lessons start from `CMake Template.txt`: C++23, compiler extensions off, strict warnings, and a commented-out `-Werror` variant.

## Layout

```
Section_NN/
  Lesson_Name/
    CMakeLists.txt
    main.cpp          # plus headers for multi-file lessons
Section_A_Miscellaneous_Subjects/
Section_B_Cpp_Updates/
```

## Credit

The lessons and exercises follow [learncpp.com](https://www.learncpp.com/). `Random.h`, used in the random-number and Blackjack lessons, is the helper header the course provides.
