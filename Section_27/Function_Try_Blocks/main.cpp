/*
The syntax for function try blocks:
 */

// #include <iostream>
//
// class A
// {
// private:
// 	int m_x;
// public:
// 	A(int x) : m_x{x}
// 	{
// 		if (x <= 0)
// 			throw 1; // Exception thrown here
// 	}
// };
//
// class B : public A
// {
// public:
// 	B(int x) try : A{x} // note addition of try keyword here
// 	{
// 	}
// 	catch (...) // note this is at same level of indentation as the function itself
// 	{
// 		// Exceptions from member initializer list or
// 		// from constructor body are caught here
//
// 		std::cerr << "Exception caught\n";
//
// 		throw; // rethrow the existing exception
// 	}
// };
//
// int main()
// {
// 	try
// 	{
// 		B b{0};
// 	}
// 	catch (int)
// 	{
// 		std::cout << "Oops\n";
// 	}
// }

/*
Limitations on function catch blocks

With a regular catch block (inside a function), we have three options: We can throw a new exception, rethrow the
current exception, or resolve the exception (by either a return statement, or by letting control reach the end of
the catch block).

A function-level catch block for a constructor must either throw a new exception or rethrow the existing
exception -- they are not allowed to resolve exceptions! Return statements are also not allowed, and reaching
the end of the catch block will implicitly rethrow.

A function-level catch block for a destructor can throw, rethrow, or resolve the current exception via a return
statement. Reaching the end of the catch block will implicitly rethrow.

A function-level catch block for other functions can throw, rethrow, or resolve the current exception via a return
statement. Reaching the end of the catch block will implicitly resolve the exception for non-value (void) returning
functions and produce undefined behavior for value-returning functions!

The following table summarizes the limitations and behavior of function-level catch blocks:

Function type					Can resolve exceptions via return statement					Behavior at end of catch block
Constructor						No, must throw or rethrow									Implicit rethrow
Destructor						Yes															Implicit rethrow
Non-value returning function	Yes															Resolve exception
Value-returning function		Yes															Undefined behavior

Because such behavior at the end of the catch block varies dramatically depending on the type of function
(and includes undefined behavior in the case of value-returning functions), we recommend never letting control
reach the end of the catch block, and always explicitly throwing, rethrowing, or returning.

n the program above, if we had not explicitly rethrow the exception in the function-level catch block of the
constructor, control would have reached the end of the function-level catch, and because this was a constructor,
an implicit rethrow would have happened instead. The result would have been the same.

Although function level try blocks can be used with non-member functions as well, they typically aren’t because
there’s rarely a case where this would be needed. They are almost exclusively used with constructors!

In the above example, if either A or B’s constructor throws an exception, it will be caught by the try block around B’s constructor.

We can see that in the following example, where we’re throwing an exception from class B instead of class A:
 */

#include <iostream>

// class A
// {
// private:
// 	int m_x;
// public:
// 	A(int x) : m_x{x}
// 	{
// 	}
// };
//
// class B : public A
// {
// public:
// 	B(int x) try : A{x} // note addition of try keyword here
// 	{
// 		if (x <= 0) // moved this from A to B
// 			throw 1; // and this too
// 	}
// 	catch (...)
// 	{
// 		std::cerr << "Exception caught\n";
//
// 		// If an exception isn't explicitly thrown here,
// 		// the current exception will be implicitly rethrown
// 	}
// };
//
// int main()
// {
// 	try
// 	{
// 		B b{0};
// 	}
// 	catch (int)
// 	{
// 		std::cout << "Oops\n";
// 	}
// }

/*
Function try is useful primarily for either logging failures before passing the exception up the stack,
or for changing the type of exception thrown.

Don’t use function try to clean up resources:

When construction of an object fails, the destructor of the class is not called. Consequently, you may be tempted to
use a function try block as a way to clean up a class that had partially allocated resources before failing. However,
referring to members of the failed object is considered undefined behavior since the object is “dead” before the catch
block executes. This means that you can’t use function try to clean up after a class. If you want to clean up after a
class, follow the standard rules for cleaning up classes that throw exceptions:

Taking advantage of the fact that class members are destructed even if the constructor fails, if you do the
resource allocations inside the members of the class (rather than in the constructor itself), then those members
can clean up after themselves when they are destructed.

Here’s an example:
 */

#include <iostream>

class Member
{
public:
	Member()
	{
		std::cerr << "Member allocated some resources\n";
	}

	~Member()
	{
		std::cerr << "Member cleaned up\n";
	}
};

class A
{
private:
	int m_x {};
	Member m_member;

public:
	A(int x) : m_x{x}
	{
		if (x <= 0)
			throw 1;
	}

	~A()
	{
		std::cerr << "~A\n"; // should not be called
	}
};


int main()
{
	try
	{
		A a{0};
	}
	catch (int)
	{
		std::cerr << "Oops\n";
	}

	return 0;
}

/*
In the above program, when class A throws an exception, all of the members of A are destructed. m_member’s destructor
is called, providing an opportunity to clean up any resources that it allocated.

This is part of the reason that RAII (covered in lesson 19.3 -- Destructors) is advocated so highly -- even in
exceptional circumstances, classes that implement RAII are able to clean up after themselves.

However, creating a custom class like Member to manage a resource allocation isn’t efficient. Fortunately, the
C++ standard library comes with RAII-compliant classes to manage common resource types, such as files (std::fstream,
covered in lesson 28.6 -- Basic file I/O) and dynamic memory (std::unique_ptr and the other smart pointers, covered
in 22.1 -- Introduction to smart pointers and move semantics).

For example, instead of this:

class Foo
private:
	int* ptr; // Foo will handle allocation/deallocation


Do this:

class Foo
private:
	std::unique_ptr<int> ptr; // std::unique_ptr will handle allocation/deallocation

In the former case, if Foo’s constructor were to fail after ptr had allocated its dynamic memory, Foo would be
responsible for cleanup, which can be challenging. In the latter case, if Foo’s constructor were to fail after ptr
has allocated its dynamic memory, ptr’s destructor would execute and return that memory to the system. Foo doesn’t
have to do any explicit cleanup when resource handling is delegated to RAII-compliant members!
 */