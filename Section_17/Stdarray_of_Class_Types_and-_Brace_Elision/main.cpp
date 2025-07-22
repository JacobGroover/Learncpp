/*
When initializing a std::array with a struct, class, or array and not providing the element type with each initializer,
you’ll need an extra pair of braces so that the compiler will properly interpret what to initialize.

This is an artifact of aggregate initialization, and other standard library container types (that use list
constructors) do not require the double braces in these cases.
 */

#include <array>
#include <iostream>
#include <string_view>

// Each student has an id and a name
struct Student
{
	int id{};
	std::string_view name{};
};

// Our array of 3 students (single braced since we mention Student with each initializer)
constexpr std::array students{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } };

const Student* findStudentById(int id)
{
	// Look through all the students
	for (auto& s : students)
	{
		// Return student with matching id
		if (s.id == id) return &s;
	}

	// No matching id found
	return nullptr;
}

int main()
{
	constexpr std::string_view nobody { "nobody" };

	const Student* s1 { findStudentById(1) };
	std::cout << "You found: " << (s1 ? s1->name : nobody) << '\n';

	const Student* s2 { findStudentById(3) };
	std::cout << "You found: " << (s2 ? s2->name : nobody) << '\n';

	return 0;
}

/*
Note that because std::array students is constexpr, our findStudentById() function must
return a const pointer, which means our Student pointers in main() must also be const.
 */

/*
In modern C++, C-style arrays are typically used in two cases:

To store constexpr global (or constexpr static local) program data. Because such arrays can be accessed directly from
anywhere in the program, we do not need to pass the array, which avoids decay-related issues. The syntax for defining
C-style arrays can be a little less wonky than std::array. More importantly, indexing such arrays does not have sign
conversion issues like the standard library container classes do.

As parameters to functions or classes that want to handle non-constexpr C-style string arguments directly
(rather than requiring a conversion to std::string_view). There are two possible reasons for this: First, converting
a non-constexpr C-style string to a std::string_view requires traversing the C-style string to determine its length.
If the function is in a performance critical section of code and the length isn’t needed (e.g. because the function
is going to traverse the string anyway) then avoiding the conversion may be useful. Second, if the function (or class)
calls other functions that expect C-style strings, converting to a std::string_view just to convert back may be
suboptimal (unless you have other reasons for wanting a std::string_view).
 */