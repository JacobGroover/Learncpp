/*
 NOTE: The implicit move constructor and move assignment will copy pointers, not move them. If you want to move a
 pointer member, you will need to define the move constructor and move assignment yourself.
 */

/*
The rule of five says that if the copy constructor, copy assignment, move constructor, move assignment,
or destructor are defined or deleted, then each of those functions should be defined or deleted.

If you delete the copy constructor, the compiler will not generate an implicit move constructor (making your
objects neither copyable nor movable). Therefore, when deleting the copy constructor, it is useful to be explicit
about what behavior you want from your move constructors. Either explicitly delete them (making it clear this is
the desired behavior), or default them (making the class move-only).
 */

/*
Automatic l-values returned by value may be moved instead of copied

In the generateResource() function of the Auto_ptr4 example above, when variable res is returned by value, it is
moved instead of copied, even though res is an l-value. The C++ specification has a special rule that says automatic
objects returned from a function by value can be moved even if they are l-values. This makes sense, since res was
going to be destroyed at the end of the function anyway! We might as well steal its resources instead of making an
expensive and unnecessary copy.

Although the compiler can move l-value return values, in some cases it may be able to do even better by simply
eliding the copy altogether (which avoids the need to make a copy or do a move at all). In such a case, neither
the copy constructor nor move constructor would be called.
 */

/*
Disabling copying

In move-enabled classes, it is sometimes desirable to delete the copy constructor and copy assignment functions
to ensure copies aren’t made. In the case of our Auto_ptr class, we don’t want to copy our templated object T -- both
because it’s expensive, and whatever class T is may not even support copying!

Here’s a version of Auto_ptr that supports move semantics but not copy semantics:
 */

#include <iostream>

// template<typename T>
// class Auto_ptr5
// {
//  T* m_ptr {};
// public:
//  Auto_ptr5(T* ptr = nullptr)
//   : m_ptr { ptr }
//  {
//  }
//
//  ~Auto_ptr5()
//  {
//   delete m_ptr;
//  }
//
//  // Copy constructor -- no copying allowed!
//  Auto_ptr5(const Auto_ptr5& a) = delete;
//
//  // Move constructor
//  // Transfer ownership of a.m_ptr to m_ptr
//  Auto_ptr5(Auto_ptr5&& a) noexcept
//   : m_ptr { a.m_ptr }
//  {
//   a.m_ptr = nullptr;
//  }
//
//  // Copy assignment -- no copying allowed!
//  Auto_ptr5& operator=(const Auto_ptr5& a) = delete;
//
//  // Move assignment
//  // Transfer ownership of a.m_ptr to m_ptr
//  Auto_ptr5& operator=(Auto_ptr5&& a) noexcept
//  {
//   // Self-assignment detection
//   if (&a == this)
//    return *this;
//
//   // Release any resource we're holding
//   delete m_ptr;
//
//   // Transfer ownership of a.m_ptr to m_ptr
//   m_ptr = a.m_ptr;
//   a.m_ptr = nullptr;
//
//   return *this;
//  }
//
//  T& operator*() const { return *m_ptr; }
//  T* operator->() const { return m_ptr; }
//  bool isNull() const { return m_ptr == nullptr; }
// };

/*
If you were to try to pass an Auto_ptr5 l-value to a function by value, the compiler would complain that the copy
constructor required to initialize the function parameter has been deleted. This is good, because we should probably
be passing Auto_ptr5 by const l-value reference anyway!
 */

// =========================================================================================

/*
To show how the below class performs when we allocate a million integers on the heap, we’re going to leverage the
Timer class we developed in lesson 18.4 -- Timing your code. We’ll use the Timer class to time how fast our code runs,
and show you the performance difference between copying and moving.
 */

// #include <algorithm> // for std::copy_n
// #include <chrono> // for std::chrono functions
// #include <iostream>
//
// #include <cstddef> // for std::size_t
//
// template <typename T>
// class DynamicArray
// {
// private:
//  T* m_array {};
//  int m_length {};
//
//  void alloc(int length)
//  {
//   m_array = new T[static_cast<std::size_t>(length)];
//   m_length = length;
//  }
// public:
//  DynamicArray(int length)
//  {
//   alloc(length);
//  }
//
//  ~DynamicArray()
//  {
//   delete[] m_array;
//  }
//
//  // Copy constructor
//  DynamicArray(const DynamicArray &arr)
//  {
//   alloc(arr.m_length);
//   std::copy_n(arr.m_array, m_length, m_array); // copy m_length elements from arr to m_array
//  }
//
//  // Copy assignment
//  DynamicArray& operator=(const DynamicArray &arr)
//  {
//   if (&arr == this)
//    return *this;
//
//   delete[] m_array;
//
//   alloc(arr.m_length);
//
//   std::copy_n(arr.m_array, m_length, m_array); // copy m_length elements from arr to m_array
//
//   return *this;
//  }
//
//  int getLength() const { return m_length; }
//  T& operator[](int index) { return m_array[index]; }
//  const T& operator[](int index) const { return m_array[index]; }
// };
//
// class Timer
// {
// private:
//  // Type aliases to make accessing nested type easier
//  using Clock = std::chrono::high_resolution_clock;
//  using Second = std::chrono::duration<double, std::ratio<1> >;
//
//  std::chrono::time_point<Clock> m_beg { Clock::now() };
//
// public:
//  void reset()
//  {
//   m_beg = Clock::now();
//  }
//
//  double elapsed() const
//  {
//   return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
//  }
// };
//
// // Return a copy of arr with all of the values doubled
// DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr)
// {
//  DynamicArray<int> dbl(arr.getLength());
//  for (int i = 0; i < arr.getLength(); ++i)
//   dbl[i] = arr[i] * 2;
//
//  return dbl;
// }
//
// int main()
// {
//  Timer t;
//
//  DynamicArray<int> arr(1000000);
//
//  for (int i = 0; i < arr.getLength(); i++)
//   arr[i] = i;
//
//  arr = cloneArrayAndDouble(arr);
//
//  std::cout << t.elapsed();
// }

// =========================================================================================

/*
Now let’s update DynamicArray by replacing the copy constructor and copy assignment with a move constructor
and move assignment, and then run the program again:
 */

// #include <cstddef> // for std::size_t
//
// template <typename T>
// class DynamicArray
// {
// private:
//  T* m_array {};
//  int m_length {};
//
//  void alloc(int length)
//  {
//   m_array = new T[static_cast<std::size_t>(length)];
//   m_length = length;
//  }
// public:
//  DynamicArray(int length)
//  {
//   alloc(length);
//  }
//
//  ~DynamicArray()
//  {
//   delete[] m_array;
//  }
//
//  // Copy constructor
//  DynamicArray(const DynamicArray &arr) = delete;
//
//  // Copy assignment
//  DynamicArray& operator=(const DynamicArray &arr) = delete;
//
//  // Move constructor
//  DynamicArray(DynamicArray &&arr) noexcept
//   :  m_array { arr.m_array }, m_length { arr.m_length }
//  {
//   arr.m_length = 0;
//   arr.m_array = nullptr;
//  }
//
//  // Move assignment
//  DynamicArray& operator=(DynamicArray &&arr) noexcept
//  {
//   if (&arr == this)
//    return *this;
//
//   delete[] m_array;
//
//   m_length = arr.m_length;
//   m_array = arr.m_array;
//   arr.m_length = 0;
//   arr.m_array = nullptr;
//
//   return *this;
//  }
//
//  int getLength() const { return m_length; }
//  T& operator[](int index) { return m_array[index]; }
//  const T& operator[](int index) const { return m_array[index]; }
// };
//
// #include <iostream>
// #include <chrono> // for std::chrono functions
//
// class Timer
// {
// private:
//  // Type aliases to make accessing nested type easier
//  using Clock = std::chrono::high_resolution_clock;
//  using Second = std::chrono::duration<double, std::ratio<1> >;
//
//  std::chrono::time_point<Clock> m_beg { Clock::now() };
//
// public:
//  void reset()
//  {
//   m_beg = Clock::now();
//  }
//
//  double elapsed() const
//  {
//   return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
//  }
// };
//
// // Return a copy of arr with all of the values doubled
// DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int> &arr)
// {
//  DynamicArray<int> dbl(arr.getLength());
//  for (int i = 0; i < arr.getLength(); ++i)
//   dbl[i] = arr[i] * 2;
//
//  return dbl;
// }
//
// int main()
// {
//  Timer t;
//
//  DynamicArray<int> arr(1000000);
//
//  for (int i = 0; i < arr.getLength(); i++)
//   arr[i] = i;
//
//  arr = cloneArrayAndDouble(arr);
//
//  std::cout << t.elapsed();
// }

// ===================================================================================

/*
While deleting only the move constructor and move assignment may seem like a good idea if you want a copyable but
not movable object, this has the unfortunate consequence of making the class not returnable by value in cases where
mandatory copy elision does not apply. This happens because a deleted move constructor is still a declared function,
and thus is eligible for overload resolution. And return by value will favor a deleted move constructor over a
non-deleted copy constructor. This is illustrated by the following program:
 */

// #include <iostream>
// #include <string>
// #include <string_view>
//
// class Name
// {
// private:
//  std::string m_name {};
//
// public:
//  Name(std::string_view name) : m_name{ name }
//  {
//  }
//
//  Name(const Name& name) = default;
//  Name& operator=(const Name& name) = default;
//
//  Name(Name&& name) = delete;
//  Name& operator=(Name&& name) = delete;
//
//  const std::string& get() const { return m_name; }
// };
//
// Name getJoe()
// {
//  Name joe{ "Joe" };
//  return joe; // error: Move constructor was deleted
// }
//
// int main()
// {
//  Name n{ getJoe() };
//
//  std::cout << n.get() << '\n';
//
//  return 0;
// }

/*
 We can create our own friend function to swap each member of a class for move semantics, since directly using
 std::swap on the class objects will cause infinite recursion:
 */

#include <iostream>
#include <string>
#include <string_view>

class Name
{
private:
 std::string m_name {};

public:
 Name(std::string_view name) : m_name{ name }
 {
 }

 Name(const Name& name) = delete;
 Name& operator=(const Name& name) = delete;

 // Create our own swap friend function to swap the members of Name
 friend void swap(Name& a, Name& b) noexcept
 {
  // We avoid recursive calls by invoking std::swap on the std::string member,
  // not on Name
  std::swap(a.m_name, b.m_name);
 }

 Name(Name&& name) noexcept
 {
  std::cout << "Move ctor\n";

  swap(*this, name); // Now calling our swap, not std::swap
 }

 Name& operator=(Name&& name) noexcept
 {
  std::cout << "Move assign\n";

  swap(*this, name); // Now calling our swap, not std::swap

  return *this;
 }

 const std::string& get() const { return m_name; }
};

int main()
{
 Name n1{ "Alex" };
 n1 = Name{"Joe"}; // invokes move assignment

 std::cout << n1.get() << '\n';

 return 0;
}