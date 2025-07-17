#include <iostream>
#include <typeinfo>

int main() {

	// a case where a pointer is changed to point at a different object:

	int x{ 5 };
	int* ptr{ &x }; // ptr initialized to point at x

	std::cout << *ptr << '\n'; // print the value at the address being pointed to (x's address)

	int y{ 6 };
	ptr = &y; // // change ptr to point at y

	std::cout << *ptr << '\n'; // print the value at the address being pointed to (y's address)


	std::cout << '\n';
	// a case where we can also use a pointer to change the value being pointed at:

	int x2{ 5 };
	int* ptr2{ &x2 }; // initialize ptr with address of variable x

	std::cout << x2 << '\n';    // print x's value
	std::cout << *ptr2 << '\n'; // print the value at the address that ptr is holding (x's address)

	*ptr2 = 6; // The object at the address held by ptr (x) assigned value 6 (note that ptr is dereferenced here)

	std::cout << x2 << '\n';
	std::cout << *ptr2 << '\n'; // print the value at the address that ptr is holding (x's address)

	std::cout << '\n';
	// Pointers and lvalue references behave similarly. Consider the following program:

	int x3{ 5 };
	int& ref { x3 };  // get a reference to x
	int* ptr3 { &x3 }; // get a pointer to x

	std::cout << x3;
	std::cout << ref;  // use the reference to print x's value (5)
	std::cout << *ptr3 << '\n'; // use the pointer to print x's value (5)

	ref = 6; // use the reference to change the value of x
	std::cout << x3;
	std::cout << ref;  // use the reference to print x's value (6)
	std::cout << *ptr3 << '\n'; // use the pointer to print x's value (6)

	*ptr3 = 7; // use the pointer to change the value of x
	std::cout << x3;
	std::cout << ref;  // use the reference to print x's value (7)
	std::cout << *ptr3 << '\n'; // use the pointer to print x's value (7)

	std::cout << '\n';
	/*
	It’s worth noting that the address-of operator (&) doesn’t return the address of its operand as a literal
	(as C++ doesn’t support address literals). Instead, it returns a pointer to the operand (whose value is the
	address of the operand). In other words, given variable int x, &x returns an int* holding the address of x.

	We can see this in the following example:
	 */
	int x4{ 4 };
	std::cout << typeid(x4).name() << '\n';  // print the type of x
	std::cout << typeid(&x4).name() << '\n'; // print the type of &x

	return 0;
}