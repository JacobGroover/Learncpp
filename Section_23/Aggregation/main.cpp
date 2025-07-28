/*
In an aggregation, we also add parts as member variables. However, these member variables are typically either
references or pointers that are used to point at objects that have been created outside the scope of the class.
Consequently, an aggregation usually either takes the objects it is going to point to as constructor parameters,
or it begins empty and the subobjects are added later via access functions or operators.

Because these parts exist outside of the scope of the class, when the class is destroyed, the pointer or reference
member variable will be destroyed (but not deleted). Consequently, the parts themselves will still exist.

Let’s take a look at a Teacher and Department example in more detail. In this example, we’re going to make a couple
of simplifications: First, the department will only hold one teacher. Second, the teacher will be unaware of what
department they’re part of.
 */

// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Teacher
// {
// private:
// 	std::string m_name{};
//
// public:
// 	Teacher(std::string_view name)
// 		: m_name{ name }
// 	{
// 	}
//
// 	const std::string& getName() const { return m_name; }
// };
//
// class Department
// {
// private:
// 	const Teacher& m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers
//
// public:
// 	Department(const Teacher& teacher)
// 		: m_teacher{ teacher }
// 	{
// 	}
// };
//
// int main()
// {
// 	// Create a teacher outside the scope of the Department
// 	Teacher bob{ "Bob" }; // create a teacher
//
// 	{
// 		// Create a department and use the constructor parameter to pass
// 		// the teacher to it.
// 		Department department{ bob };
//
// 	} // department goes out of scope here and is destroyed
//
// 	// bob still exists here, but the department doesn't
//
// 	std::cout << bob.getName() << " still exists!\n";
//
// 	return 0;
// }

/*
Although it might seem a little silly in the above example that the Teachers don’t know what Department they’re
working for, that may be totally fine in the context of a given program. When you’re determining what kind of
relationship to implement, implement the simplest relationship that meets your needs, not the one that seems
like it would fit best in a real-life context.

For example, if you’re writing a body shop simulator, you may want to implement a car and engine as an aggregation,
so the engine can be removed and put on a shelf somewhere for later. However, if you’re writing a racing simulation,
you may want to implement a car and an engine as a composition, since the engine will never exist outside of the car
in that context.
 */

/*
Instead of references, we could use pointers, but that would open the possibility to store or pass null pointers.
In the Department/Teacher example, we don’t want to allow null pointers. To solve this, there’s std::reference_wrapper.

Essentially, std::reference_wrapper is a class that acts like a reference, but also allows assignment and copying,
so it’s compatible with lists like std::vector.

The good news is that you don’t really need to understand how it works to use it. All you need to know are three things:

1. std::reference_wrapper lives in the <functional> header.

2. When you create your std::reference_wrapper wrapped object, the object can’t be an anonymous object
(since anonymous objects have expression scope, and this would leave the reference dangling).

3. When you want to get your object back out of std::reference_wrapper, you use the get() member function.

Here’s an example using std::reference_wrapper in a std::vector:
 */

// #include <functional> // std::reference_wrapper
// #include <iostream>
// #include <vector>
// #include <string>
//
// int main()
// {
// 	std::string tom{ "Tom" };
// 	std::string berta{ "Berta" };
//
// 	std::vector<std::reference_wrapper<std::string>> names{ tom, berta }; // these strings are stored by reference, not value
//
// 	std::string jim{ "Jim" };
//
// 	names.emplace_back(jim);
//
// 	for (auto name : names)
// 	{
// 		// Use the get() member function to get the referenced string.
// 		name.get() += " Beam";
// 	}
//
// 	std::cout << jim << '\n'; // prints Jim Beam
//
// 	return 0;
// }

/*
To create a vector of const references, we’d have to add const before the std::string like so:

// Vector of const references to std::string
std::vector<std::reference_wrapper<const std::string>> names{ tom, berta };
 */

// Below is the original code updated so support multiple teachers:

#include <functional> // std::reference_wrapper
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Teacher
{
private:
 std::string m_name{};

public:
 Teacher(std::string_view name)
     : m_name{ name }
 {
 }

 const std::string& getName() const { return m_name; }
};

class Department
{
private:
 std::vector<std::reference_wrapper<const Teacher>> m_teachers{};

public:
 Department() = default;

 // Pass by regular reference. The user of the Department class shouldn't care
 // about how it's implemented.
 void add(const Teacher& teacher)
 {
  m_teachers.emplace_back(teacher);
 }

 friend std::ostream& operator<<(std::ostream& out, const Department& department)
 {
  out << "Department: ";

  for (const auto& teacher : department.m_teachers)
  {
   out << teacher.get().getName() << ' ';
  }

  out << '\n';

  return out;
 }
};

int main()
{
 // Create a teacher outside the scope of the Department
 Teacher t1{ "Bob" };
 Teacher t2{ "Frank" };
 Teacher t3{ "Beth" };

 {
  // Create a department and add some Teachers to it
  Department department{}; // create an empty Department

  department.add(t1);
  department.add(t2);
  department.add(t3);

  std::cout << department;

 } // department goes out of scope here and is destroyed

 std::cout << t1.getName() << " still exists!\n";
 std::cout << t2.getName() << " still exists!\n";
 std::cout << t3.getName() << " still exists!\n";

 return 0;
}