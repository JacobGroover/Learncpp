/*
Implementing a constructor that takes a std::initializer_list parameter allows us to use list initialization with
our custom classes. We can also use std::initializer_list to implement other functions that need to use an
initializer list, such as an assignment operator.
 */

/*
Warning:

Adding a list constructor to an existing class that did not have one may break existing programs.
 */

// #include <algorithm> // for std::copy
// #include <cassert> // for assert()
// #include <initializer_list> // for std::initializer_list
// #include <iostream>
//
// class IntArray
// {
// private:
// 	int m_length {};
// 	int* m_data{};
//
// public:
// 	IntArray() = default;
//
// 	IntArray(int length)
// 		: m_length{ length }
// 	, m_data{ new int[static_cast<std::size_t>(length)] {} }
// 	{
//
// 	}
//
// 	IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
// 		: IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
// 	{
// 		// Now initialize our array from the list
// 		std::copy(list.begin(), list.end(), m_data);
// 	}
//
// 	~IntArray()
// 	{
// 		delete[] m_data;
// 		// we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
// 	}
//
// 	IntArray(const IntArray&) = delete; // to avoid shallow copies
// 	IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies
//
// 	int& operator[](int index)
// 	{
// 		assert(index >= 0 && index < m_length);
// 		return m_data[index];
// 	}
//
// 	int getLength() const { return m_length; }
// };
//
// int main()
// {
// 	IntArray array{ 5, 4, 3, 2, 1 }; // initializer list
// 	for (int count{ 0 }; count < array.getLength(); ++count)
// 		std::cout << array[count] << ' ';
//
// 	return 0;
// }

/*
Here’s our IntArray constructor that takes a std::initializer_list<int>.

IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
	: IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
{
	// Now initialize our array from the list
	std::copy(list.begin(), list.end(), m_data);
}
On line 1: As noted above, we have to use angled brackets to denote what type of element we expect inside the list.
In this case, because this is an IntArray, we’d expect the list to be filled with int. Note that we don’t pass the
list by const reference. Much like std::string_view, std::initializer_list is very lightweight and copies tend to be
cheaper than an indirection.

On line 2: We delegate allocating memory for the IntArray to the other constructor via a delegating constructor
(to reduce redundant code). This other constructor needs to know the length of the array, so we pass it list.size(),
which contains the number of elements in the list. Note that list.size() returns a size_t (which is unsigned) so we
need to cast to a signed int here.

The body of the constructor is reserved for copying the elements from the list into our IntArray class. The easiest
way to do this is to use std::copy(), which lives in the <algorithm> header.
 */

/*
Best practice:

When initializing a container that has a list constructor:

- Use brace initialization when intending to call the list constructor (e.g. because your initializers are element values)

- Use direct initialization when intending to call a non-list constructor (e.g. because your initializers are not element values).
 */

/*
Note that if you implement a constructor that takes a std::initializer_list, you should ensure you do at least one of the following:

1. Provide an overloaded list assignment operator
2. Provide a proper deep-copying copy assignment operator
3. Delete the copy assignment operator

Here’s why: consider the following class (which doesn’t have any of these things), along with a list assignment statement:
 */

// #include <algorithm> // for std::copy()
// #include <cassert>   // for assert()
// #include <initializer_list> // for std::initializer_list
// #include <iostream>
//
// class IntArray
// {
// private:
// 	int m_length{};
// 	int* m_data{};
//
// public:
// 	IntArray() = default;
//
// 	IntArray(int length)
// 		: m_length{ length }
// 	, m_data{ new int[static_cast<std::size_t>(length)] {} }
// 	{
//
// 	}
//
// 	IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
// 		: IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
// 	{
// 		// Now initialize our array from the list
// 		std::copy(list.begin(), list.end(), m_data);
// 	}
//
// 	~IntArray()
// 	{
// 		delete[] m_data;
// 	}
//
// 	//	IntArray(const IntArray&) = delete; // to avoid shallow copies
// 	//	IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies
//
// 	int& operator[](int index)
// 	{
// 		assert(index >= 0 && index < m_length);
// 		return m_data[index];
// 	}
//
// 	int getLength() const { return m_length; }
// };
//
// int main()
// {
// 	IntArray array{};
// 	array = { 1, 3, 5, 7, 9, 11 }; // Here's our list assignment statement
//
// 	for (int count{ 0 }; count < array.getLength(); ++count)
// 		std::cout << array[count] << ' '; // undefined behavior
//
// 	return 0;
// }

/*
Using the IntArray class above, implement an overloaded assignment operator that takes an initializer list:
 */

#include <algorithm> // for std::copy()
#include <cassert>   // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>

class IntArray
{
private:
 int m_length {};
 int* m_data {};

public:
 IntArray() = default;

 IntArray(int length)
  : m_length{ length }
 , m_data{ new int[static_cast<std::size_t>(length)] {} }
 {

 }

 IntArray(std::initializer_list<int> list) : // allow IntArray to be initialized via list initialization
  IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
 {
  // Now initialize our array from the list
  std::copy(list.begin(), list.end(), m_data);
 }

 ~IntArray()
 {
  delete[] m_data;
  // we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
 }

 IntArray(const IntArray&) = delete; // to avoid shallow copies
 IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies

 IntArray& operator=(std::initializer_list<int> list)
 {
  // If the new list is a different size, reallocate it
  int length { static_cast<int>(list.size()) };
  if (length != m_length)
  {
   delete[] m_data;
   m_length = length;
   m_data = new int[list.size()]{};
  }

  // Now initialize our array from the list
  std::copy(list.begin(), list.end(), m_data);

  return *this;
 }

 int& operator[](int index)
 {
  assert(index >= 0 && index < m_length);
  return m_data[index];
 }

 int getLength() const { return m_length; }
};

int main()
{
 IntArray array { 5, 4, 3, 2, 1 }; // initializer list
 for (int count{ 0 }; count < array.getLength(); ++count)
  std::cout << array[count] << ' ';

 std::cout << '\n';

 array = { 1, 3, 5, 7, 9, 11 };

 for (int count{ 0 }; count < array.getLength(); ++count)
  std::cout << array[count] << ' ';

 std::cout << '\n';

 return 0;
}