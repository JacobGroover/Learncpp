// A friend class is a class that can access the private and protected members of another class.

// NOTE: Put each class definition in a separate header file, with the member function definitions in
// corresponding .cpp files. That way, all the class definitions are available in the .cpp files,
// and no rearranging of classes or functions is necessary to make member function friendship work.

#include <iostream>

class Storage
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
	   : m_nValue { nValue }, m_dValue { dValue }
	{ }

	// Make the Display class a friend of Storage
	friend class Display;
};

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		 : m_displayIntFirst { displayIntFirst }
	{
	}

	// Because Display is a friend of Storage, Display members can access the private members of Storage
	void displayStorage(const Storage& storage)
	{
		if (m_displayIntFirst)
			std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
		else // display double first
			std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
	}

	void setDisplayIntFirst(bool b)
	{
		m_displayIntFirst = b;
	}
};

int main()
{
	Storage storage { 5, 6.7 };
	Display display { false };

	display.displayStorage(storage);

	display.setDisplayIntFirst(true);
	display.displayStorage(storage);

	return 0;
}

/*
A few additional notes on friend classes.

First, even though Display is a friend of Storage, Display has no access to the *this pointer of Storage objects
(because *this is actually a function parameter).

Second, friendship is not reciprocal. Just because Display is a friend of Storage does not mean Storage is also a
friend of Display. If you want two classes to be friends of each other, both must declare the other as a friend.

Class friendship is also not transitive. If class A is a friend of B, and B is a friend of C,
that does not mean A is a friend of C.

Nor is friendship inherited. If class A makes B a friend, classes derived from B are not friends of A.
 */