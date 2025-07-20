/*
Like constructors, destructors have specific naming rules:

1. The destructor must have the same name as the class, preceded by a tilde (~).
2. The destructor can not take arguments.
3. The destructor has no return type.

A class can only have a single destructor.

Generally you should not call a destructor explicitly (as it will be called automatically when the object is destroyed),
since there are rarely cases where you’d want to clean up an object more than once.

Destructors may safely call other member functions since the object isn’t destroyed until after the destructor executes.


In lesson 8.12 -- Halts (exiting your program early), we discussed the std::exit() function, can be used to terminate
your program immediately. When the program is terminated immediately, the program just ends. Local variables are not
destroyed first, and because of this, no destructors will be called. Be wary if you’re relying on your destructors to
do necessary cleanup work in such a case.

Unhandled exceptions will also cause the program to terminate, and may not unwind the stack before doing so. If stack
unwinding does not happen, destructors will not be called prior to the termination of the program.
 */

#include <iostream>

class Simple
{
private:
	int m_id {};

public:
	Simple(int id)
		: m_id { id }
	{
		std::cout << "Constructing Simple " << m_id << '\n';
	}

	~Simple() // here's our destructor
	{
		std::cout << "Destructing Simple " << m_id << '\n';
	}

	int getID() const { return m_id; }
};

int main()
{
	// Allocate a Simple
	Simple simple1{ 1 };
	{
		Simple simple2{ 2 };
	} // simple2 dies here

	return 0;
} // simple1 dies here