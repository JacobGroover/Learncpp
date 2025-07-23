// a simple class that uses a destructor:

#include <iostream>
#include <cassert>
#include <cstddef>

class IntArray
{
private:
	int* m_array{};
	int m_length{};

public:
	IntArray(int length) // constructor
	{
		assert(length > 0);

		m_array = new int[static_cast<std::size_t>(length)]{};
		m_length = length;
	}

	~IntArray() // destructor
	{
		// Dynamically delete the array we allocated earlier
		delete[] m_array;
	}

	void setValue(int index, int value) { m_array[index] = value; }
	int getValue(int index) { return m_array[index]; }

	int getLength() { return m_length; }
};

int main()
{
	IntArray ar ( 10 ); // allocate 10 integers
	for (int count{ 0 }; count < ar.getLength(); ++count)
		ar.setValue(count, count+1);

	std::cout << "The value of element 5 is: " << ar.getValue(5) << '\n';

	return 0;
} // ar is destroyed here, so the ~IntArray() destructor function is called here

/*
RAII

RAII (Resource Acquisition Is Initialization) is a programming technique whereby resource use is tied to the lifetime
of objects with automatic duration (e.g. non-dynamically allocated objects). In C++, RAII is implemented via classes
with constructors and destructors. A resource (such as memory, a file or database handle, etc…) is typically acquired
in the object’s constructor (though it can be acquired after the object is created if that makes sense). That resource
can then be used while the object is alive. The resource is released in the destructor, when the object is destroyed.
The primary advantage of RAII is that it helps prevent resource leaks (e.g. memory not being deallocated) as all
resource-holding objects are cleaned up automatically.

The IntArray class at the top of this lesson is an example of a class that implements RAII -- allocation in the
constructor, deallocation in the destructor. std::string and std::vector are examples of classes in the standard
library that follow RAII -- dynamic memory is acquired on initialization, and cleaned up automatically on destruction.
 */