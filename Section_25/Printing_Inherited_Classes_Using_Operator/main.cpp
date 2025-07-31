/*
First, we set up operator<< as a friend in our base class as usual. But rather than have operator<< determine what
to print, we will instead have it call a normal member function that can be virtualized! This virtual function will
do the work of determining what to print for each class.

In this first solution, our virtual member function (which we call identify()) returns a std::string, which is
printed by Base::operator<<:
 */

// #include <iostream>
//
// class Base
// {
// public:
// 	// Here's our overloaded operator<<
// 	friend std::ostream& operator<<(std::ostream& out, const Base& b)
// 	{
// 		// Call virtual function identify() to get the string to be printed
// 		out << b.identify();
// 		return out;
// 	}
//
// 	// We'll rely on member function identify() to return the string to be printed
// 	// Because identify() is a normal member function, it can be virtualized
// 	virtual std::string identify() const
// 	{
// 		return "Base";
// 	}
// };
//
// class Derived : public Base
// {
// public:
// 	// Here's our override identify() function to handle the Derived case
// 	std::string identify() const override
// 	{
// 		return "Derived";
// 	}
// };
//
// int main()
// {
// 	Base b{};
// 	std::cout << b << '\n';
//
// 	Derived d{};
// 	std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects
//
// 	Base& bref{ d };
// 	std::cout << bref << '\n';
//
// 	return 0;
// }

/*
The above solution works great, but has two potential shortcomings:

It makes the assumption that the desired output can be represented as a single std::string.
Our identify() member function does not have access to the stream object.
The latter is problematic in cases where we need a stream object, such as when we want to print the
value of a member variable that has an overloaded operator<<.

Fortunately, it’s straightforward to modify the above example to resolve both of these issues. In the
previous version, virtual function identify() returned a string to be printed by Base::operator<<. In
this version, we’ll instead define virtual member function print() and delegate responsibility for printing
directly to that function.

Here’s an example that illustrates the idea:
 */

#include <iostream>

class Base
{
public:
 // Here's our overloaded operator<<
 friend std::ostream& operator<<(std::ostream& out, const Base& b)
 {
  // Delegate printing responsibility for printing to virtual member function print()
  return b.print(out);
 }

 // We'll rely on member function print() to do the actual printing
 // Because print() is a normal member function, it can be virtualized
 virtual std::ostream& print(std::ostream& out) const
 {
  out << "Base";
  return out;
 }
};

// Some class or struct with an overloaded operator<<
struct Employee
{
 std::string name{};
 int id{};

 friend std::ostream& operator<<(std::ostream& out, const Employee& e)
 {
  out << "Employee(" << e.name << ", " << e.id << ")";
  return out;
 }
};

class Derived : public Base
{
private:
 Employee m_e{}; // Derived now has an Employee member

public:
 Derived(const Employee& e)
  : m_e{ e }
 {
 }

 // Here's our override print() function to handle the Derived case
 std::ostream& print(std::ostream& out) const override
 {
  out << "Derived: ";

  // Print the Employee member using the stream object
  out << m_e;

  return out;
 }
};

int main()
{
 Base b{};
 std::cout << b << '\n';

 Derived d{ Employee{"Jim", 4}};
 std::cout << d << '\n'; // note that this works even with no operator<< that explicitly handles Derived objects

 Base& bref{ d };
 std::cout << bref << '\n';

 return 0;
}