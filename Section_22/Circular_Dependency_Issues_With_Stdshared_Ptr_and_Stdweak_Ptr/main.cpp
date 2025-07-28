/*
std::shared_ptr can be used when you need multiple smart pointers that can co-own a resource.
The resource will be deallocated when the last std::shared_ptr goes out of scope. std::weak_ptr can
be used when you want a smart pointer that can see and use a shared resource, but does not participate
in the ownership of that resource.
 */

// This example overcomes cyclical dependency issues associated with only using std::shared_ptr in this instance:

// #include <iostream>
// #include <memory> // for std::shared_ptr and std::weak_ptr
// #include <string>
//
// class Person
// {
// 	std::string m_name;
// 	std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr
//
// public:
//
// 	Person(const std::string &name): m_name(name)
// 	{
// 		std::cout << m_name << " created\n";
// 	}
// 	~Person()
// 	{
// 		std::cout << m_name << " destroyed\n";
// 	}
//
// 	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
// 	{
// 		if (!p1 || !p2)
// 			return false;
//
// 		p1->m_partner = p2;
// 		p2->m_partner = p1;
//
// 		std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';
//
// 		return true;
// 	}
// };
//
// int main()
// {
// 	auto lucy { std::make_shared<Person>("Lucy") };
// 	auto ricky { std::make_shared<Person>("Ricky") };
//
// 	partnerUp(lucy, ricky);
//
// 	return 0;
// }

/*
One downside of std::weak_ptr is that std::weak_ptr are not directly usable (they have no operator->).
To use a std::weak_ptr, you must first convert it into a std::shared_ptr. Then you can use the std::shared_ptr.
To convert a std::weak_ptr into a std::shared_ptr, you can use the lock() member function. Here’s the above
example, updated to show this off:
 */

// #include <iostream>
// #include <memory> // for std::shared_ptr and std::weak_ptr
// #include <string>
//
// class Person
// {
// 	std::string m_name;
// 	std::weak_ptr<Person> m_partner; // note: This is now a std::weak_ptr
//
// public:
//
// 	Person(const std::string &name) : m_name(name)
// 	{
// 		std::cout << m_name << " created\n";
// 	}
// 	~Person()
// 	{
// 		std::cout << m_name << " destroyed\n";
// 	}
//
// 	friend bool partnerUp(std::shared_ptr<Person> &p1, std::shared_ptr<Person> &p2)
// 	{
// 		if (!p1 || !p2)
// 			return false;
//
// 		p1->m_partner = p2;
// 		p2->m_partner = p1;
//
// 		std::cout << p1->m_name << " is now partnered with " << p2->m_name << '\n';
//
// 		return true;
// 	}
//
// 	std::shared_ptr<Person> getPartner() const { return m_partner.lock(); } // use lock() to convert weak_ptr to shared_ptr
// 	const std::string& getName() const { return m_name; }
// };
//
// int main()
// {
// 	auto lucy { std::make_shared<Person>("Lucy") };
// 	auto ricky { std::make_shared<Person>("Ricky") };
//
// 	partnerUp(lucy, ricky);
//
// 	auto partner = ricky->getPartner(); // get shared_ptr to Ricky's partner
// 	std::cout << ricky->getName() << "'s partner is: " << partner->getName() << '\n';
//
// 	return 0;
// }

/*
Avoiding dangling pointers with std::weak_ptr:

Consider the case where a normal “dumb” pointer is holding the address of some object, and then that object is
destroyed. Such a pointer is dangling, and dereferencing the pointer will lead to undefined behavior. And
unfortunately, there is no way for us to determine whether a pointer holding a non-null address is dangling or not.
This is a large part of the reason dumb pointers are dangerous.

Because std::weak_ptr won’t keep an owned resource alive, it’s similarly possible for a std::weak_ptr to be left
pointing to a resource that has been deallocated by a std::shared_ptr. However, std::weak_ptr has a neat trick up
its sleeve -- because it has access to the reference count for an object, it can determine if it is pointing to a
valid object or not! If the reference count is non-zero, the resource is still valid. If the reference count is zero,
then the resource has been destroyed.

The easiest way to test whether a std::weak_ptr is valid is to use the expired() member function, which returns true
if the std::weak_ptr is pointing to an invalid object, and false otherwise.

Here’s a simple example showing this difference in behavior:
 */

// h/t to reader Waldo for an early version of this example
#include <iostream>
#include <memory>

class Resource
{
public:
 // Resource() { std::cerr << "Resource acquired\n"; }
 Resource() { std::cout << "Resource acquired\n"; }
 // ~Resource() { std::cerr << "Resource destroyed\n"; }
 ~Resource() { std::cout << "Resource destroyed\n"; }
};

// Returns a std::weak_ptr to an invalid object
std::weak_ptr<Resource> getWeakPtr()
{
 auto ptr{ std::make_shared<Resource>() };
 return std::weak_ptr<Resource>{ ptr };
} // ptr goes out of scope, Resource destroyed

// Returns a dumb pointer to an invalid object
Resource* getDumbPtr()
{
 auto ptr{ std::make_unique<Resource>() };
 return ptr.get();
} // ptr goes out of scope, Resource destroyed

int main()
{
 auto dumb{ getDumbPtr() };
 std::cout << "Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");

 auto weak{ getWeakPtr() };
 std::cout << "Our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

 return 0;
}

/*
Both getDumbPtr() and getWeakPtr() use a smart pointer to allocate a Resource -- this smart pointer ensures that the
allocated Resource will be destroyed at the end of the function. When getDumbPtr() returns a Resource*, it returns a
dangling pointer (because std::unique_ptr destroyed the Resource at the end of the function). When getWeakPtr() returns
a std::weak_ptr, that std::weak_ptr is similarly pointing to an invalid object (because std::shared_ptr destroyed the
Resource at the end of the function).

Inside main(), we first test whether the returned dumb pointer is nullptr. Because the dumb pointer is still holding
the address of the deallocated resource, this test fails. There is no way for main() to tell whether this pointer is
dangling or not. In this case, because it is a dangling pointer, if we were to dereference this pointer, undefined
behavior would result.

Next, we test whether weak.expired() is true. Because the reference count for the object being pointed to by weak is 0
(because the object being pointed to was already destroyed), this resolves to true. The code in main() can thus tell
that weak is pointing to an invalid object, and we can conditionalize our code as appropriate!

Note that if a std::weak_ptr is expired, then we shouldn’t call lock() on it, because the object being pointed to has
already been destroyed, so there is no object to share. If you do call lock() on an expired std::weak_ptr, it will
return a std::shared_ptr to nullptr.
 */