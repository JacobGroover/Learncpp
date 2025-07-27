/*
What are the limitations on operator overloading?

First, almost any existing operator in C++ can be overloaded.
The exceptions are: conditional (?:), sizeof, scope (::), member selector (.), pointer member selector (.*), typeid,
and the casting operators.

Second, you can only overload the operators that exist. You can not create new operators or rename existing operators.
For example, you could not create an operator** to do exponents.

Third, at least one of the operands in an overloaded operator must be a user-defined type.
This means you could overload operator+(int, Mystring), but not operator+(int, double).
(Best Practice: An overloaded operator should operate on at least one program-defined type (either as a parameter
of the function, or the implicit object).)

Fourth, it is not possible to change the number of operands an operator supports.

Finally, all operators keep their default precedence and associativity
(regardless of what they’re used for) and this can not be changed.
 */

/*
Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value.

Operators that modify their leftmost operand (e.g. pre-increment, any of the assignment operators) should generally return the leftmost operand by reference.
 */

/*
Operator overloading is a variant of function overloading that lets you overload operators for your classes.
When operators are overloaded, the intent of the operators should be kept as close to the original intent of
the operators as possible. If the meaning of an operator when applied to a custom class is not clear and intuitive,
use a named function instead.

Operators can be overloaded as a normal function, a friend function, or a member function. The following rules of
thumb can help you determine which form is best for a given situation:

- If you’re overloading assignment (=), subscript ([]), function call (()), or member selection (->), do so as a member function.
- If you’re overloading a unary operator, do so as a member function.
- If you’re overloading a binary operator that modifies its left operand (e.g. operator+=), do so as a member function if you can.
- If you’re overloading a binary operator that does not modify its left operand (e.g. operator+), do so as a normal function or friend function.

Best Practice:
- Prefer overloading operators as normal functions instead of friends if it’s possible to do so without adding additional functions.
 */

// https://www.learncpp.com/cpp-tutorial/overloading-typecasts/
// Typecasts can be overloaded to provide conversion functions, which can be used to explicitly or implicitly convert your class into another type.

// Just like single-parameter converting constructors should be marked as explicit, typecasts should be marked as
// explicit, except in cases where the type to be converted to is essentially synonymous with the destination type.

/*
A copy constructor is a special type of constructor used to initialize an object from another object of the same type.
Copy constructors are used for direct/uniform initialization from an object of the same type, copy initialization
(Fraction f = Fraction(5,3)), and when passing or returning a parameter by value.

If you do not supply a copy constructor, the compiler will create one for you. Compiler-provided copy constructors
will use memberwise initialization, meaning each member of the copy is initialized from the original member. The copy
constructor may be elided for optimization purposes, even if it has side-effects, so do not rely on your copy
constructor actually executing.
 */

/*
Constructors are considered converting constructors by default, meaning that the compiler will use them to implicitly
convert objects of other types into objects of your class. You can avoid this by using the explicit keyword in front
of your constructor. You can also delete functions within your class, including the copy constructor and overloaded
assignment operator if desired. This will cause a compiler error if a deleted function would be called.
 */

/*
The assignment operator can be overloaded to allow assignment to your class. If you do not provide an overloaded
assignment operator, the compiler will create one for you. Overloaded assignment operators should always include a
self-assignment check (unless it’s handled naturally, or you’re using the copy and swap idiom).
 */

/*
New programmers often mix up when the assignment operator vs copy constructor are used, but it’s fairly straightforward:

- If a new object has to be created before the copying can occur, the copy constructor is used (note: this includes passing or returning objects by value).
- If a new object does not have to be created before the copying can occur, the assignment operator is used.
 */

/*
By default, the copy constructor and assignment operators provided by the compiler do a memberwise initialization or
assignment, which is a shallow copy. If your class dynamically allocates memory, this will likely lead to problems,
as multiple objects will end up pointing to the same allocated memory. In this case, you’ll need to explicitly define
these in order to do a deep copy. Even better, avoid doing your own memory management if you can and use classes from
the standard library.
 */

/*
Tip:

Transactional operations can be implemented using a number of different strategies. For example:

- Alter on success: Store the result of each sub-operation. If all sub-operations succeed, replace the relevant
data with the stored results. This is the strategy we use in the Point example above.

- Restore on failure: Copy any data that can be altered. If any sub-operation fails, the changes made by prior
sub-operations can be reverted using the data from copy.

- Rollback on failure: If any sub-operation fails, each prior sub-operation is reversed
(using an opposite sub-operation). This strategy is often used in databases, where the data
is too large to back up, and the result of sub-operations can’t be stored.
 */


/*
 Move Sematnics Example:
 */

#include <iostream>

template <typename T>
class Auto_ptr2
{
 T* m_ptr {};
public:
 Auto_ptr2(T* ptr=nullptr)
  :m_ptr(ptr)
 {
 }

 ~Auto_ptr2()
 {
  delete m_ptr;
 }

 // A copy constructor that implements move semantics
 Auto_ptr2(Auto_ptr2& a) // note: not const
 {
  // We don't need to delete m_ptr here.  This constructor is only called when we're creating a new object, and m_ptr can't be set prior to this.
  m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
  a.m_ptr = nullptr; // make sure the source no longer owns the pointer
 }

 // An assignment operator that implements move semantics
 Auto_ptr2& operator=(Auto_ptr2& a) // note: not const
 {
  if (&a == this)
   return *this;

  delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
  m_ptr = a.m_ptr; // then transfer our dumb pointer from the source to the local object
  a.m_ptr = nullptr; // make sure the source no longer owns the pointer
  return *this;
 }

 T& operator*() const { return *m_ptr; }
 T* operator->() const { return m_ptr; }
 bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
 Resource() { std::cout << "Resource acquired\n"; }
 ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
 Auto_ptr2<Resource> res1(new Resource());
 Auto_ptr2<Resource> res2; // Start as nullptr

 std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
 std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

 res2 = res1; // res2 assumes ownership, res1 is set to null

 std::cout << "Ownership transferred\n";

 std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
 std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

 return 0;
}