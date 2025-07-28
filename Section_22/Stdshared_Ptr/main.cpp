/*
Always make a copy of an existing std::shared_ptr if you need more than one std::shared_ptr pointing to the same resource.

Just like with std::unique_ptr, std::shared_ptr can be a null pointer, so check to make sure it is valid before using it.
 */

// #include <iostream>
// #include <memory> // for std::shared_ptr
//
// class Resource
// {
// public:
// 	Resource() { std::cout << "Resource acquired\n"; }
// 	~Resource() { std::cout << "Resource destroyed\n"; }
// };
//
// int main()
// {
// 	// allocate a Resource object and have it owned by std::shared_ptr
// 	Resource* res { new Resource };
// 	std::shared_ptr<Resource> ptr1{ res };
// 	{
// 		std::shared_ptr<Resource> ptr2 { ptr1 }; // make another std::shared_ptr pointing to the same thing
//
// 		std::cout << "Killing one shared pointer\n";
// 	} // ptr2 goes out of scope here, but nothing happens
//
// 	std::cout << "Killing another shared pointer\n";
//
// 	return 0;
// } // ptr1 goes out of scope here, and the allocated Resource is destroyed

/*
Much like std::make_unique() can be used to create a std::unique_ptr in C++14, std::make_shared()
can (and should) be used to make a std::shared_ptr. std::make_shared() is available in C++11.

Here’s our original example, using std::make_shared():
 */

#include <iostream>
#include <memory> // for std::shared_ptr

class Resource
{
public:
 Resource() { std::cout << "Resource acquired\n"; }
 ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
 // allocate a Resource object and have it owned by std::shared_ptr
 auto ptr1 { std::make_shared<Resource>() };
 {
  auto ptr2 { ptr1 }; // create ptr2 using copy of ptr1

  std::cout << "Killing one shared pointer\n";
 } // ptr2 goes out of scope here, but nothing happens

 std::cout << "Killing another shared pointer\n";

 return 0;
} // ptr1 goes out of scope here, and the allocated Resource is destroyed

/*
The reasons for using std::make_shared() are the same as std::make_unique() -- std::make_shared() is simpler and
safer (there’s no way to create two independent std::shared_ptr pointing to the same resource but unaware of each
other using this method). However, std::make_shared() is also more performant than not using it. The reasons for
this lie in the way that std::shared_ptr keeps track of how many pointers are pointing at a given resource.
 */

/*
Unlike std::unique_ptr, which uses a single pointer internally, std::shared_ptr uses two pointers internally.
One pointer points at the resource being managed. The other points at a “control block”, which is a dynamically
allocated object that tracks of a bunch of stuff, including how many std::shared_ptr are pointing at the resource.
When a std::shared_ptr is created via a std::shared_ptr constructor, the memory for the managed object (which is
usually passed in) and control block (which the constructor creates) are allocated separately. However, when using
std::make_shared(), this can be optimized into a single memory allocation, which leads to better performance.

This also explains why independently creating two std::shared_ptr pointed to the same resource gets us into trouble.
Each std::shared_ptr will have one pointer pointing at the resource. However, each std::shared_ptr will independently
allocate its own control block, which will indicate that it is the only pointer owning that resource. Thus, when that
std::shared_ptr goes out of scope, it will deallocate the resource, not realizing there are other std::shared_ptr also
trying to manage that resource.

However, when a std::shared_ptr is cloned using copy assignment, the data in the control block can be appropriately
updated to indicate that there are now additional std::shared_ptr co-managing the resource.
 */

/*
A std::unique_ptr can be converted into a std::shared_ptr via a special std::shared_ptr constructor that accepts a
std::unique_ptr r-value. The contents of the std::unique_ptr will be moved to the std::shared_ptr.

However, std::shared_ptr can not be safely converted to a std::unique_ptr. This means that if you’re creating a
function that is going to return a smart pointer, you’re better off returning a std::unique_ptr and assigning it
to a std::shared_ptr if and when that’s appropriate.
 */

/*
std::shared_ptr has some of the same challenges as std::unique_ptr -- if the std::shared_ptr is not properly disposed
of (either because it was dynamically allocated and never deleted, or it was part of an object that was dynamically
allocated and never deleted) then the resource it is managing won’t be deallocated either. With std::unique_ptr, you
only have to worry about one smart pointer being properly disposed of. With std::shared_ptr, you have to worry about
them all. If any of the std::shared_ptr managing a resource are not properly destroyed, the resource will not be
deallocated properly.
 */

/*
In C++17 and earlier, std::shared_ptr does not have proper support for managing arrays,
and should not be used to manage a C-style array. As of C++20, std::shared_ptr does have support for arrays.
 */