#include <iostream>
#include <string>
#include <string_view>

class Employee {
private:
	std::string m_name{};

public:
	Employee(std::string_view name): m_name{name} {
	}

	const std::string &getName() const & { return m_name; }
	//  & qualifier overloads function to match only lvalue implicit objects
	std::string getName() const && { return m_name; }
	// && qualifier overloads function to match only rvalue implicit objects
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name) {
	Employee e{name};
	return e;
}

int main() {
	Employee joe{"Joe"};
	std::cout << joe.getName() << '\n';
	// Joe is an lvalue, so this calls std::string& getName() & (returns a reference)

	std::cout << createEmployee("Frank").getName() << '\n';
	// Frank is an rvalue, so this calls std::string getName() && (makes a copy)

	return 0;
}

// This allows us to do the performant thing when our implicit object is an lvalue, and the safe thing when
// our implicit object is an rvalue.

/*
The above rvalue overload of getName() above is potentially suboptimal from a performance perspective when the
implicit object is a non-const temporary. In such cases, the implicit object is going to die at the end of the
expression anyway. So instead of having the rvalue getter return a (possibly expensive) copy of the member, we
can have it try to move the member (using std::move).

This can be facilitated by adding the following overloaded getter for non-const rvalues:

// If the implicit object is a non-const rvalue, use std::move to try to move m_name
std::string getName() && { return std::move(m_name); }

This can either coexist with the const rvalue getter, or you can just use this
instead (since const rvalues are fairly uncommon).

We cover std::move in lesson 22.4 -- std::move.
 */

/*
Some notes about ref-qualified member functions

First, for a given function, non-ref-qualified overloads and ref-qualified overloads cannot coexist.
Use one or the other.

Second, similar to how a const lvalue reference can bind to an rvalue, if only a const lvalue-qualified
function exists, it will accept either lvalue or rvalue implicit objects.

Third, either qualified overload can be explicitly deleted (using = delete), which prevents calls to that function.
For example, deleting the rvalue-qualified version prevents use of the function with rvalue implicit objects.
 */

/*
So why don’t we recommend using ref-qualifiers?

While ref-qualifiers are neat, there are some downsides to using them in this way.

Adding rvalue overloads to every getter that returns a reference adds clutter to the class, to mitigate against a case
that isn’t that common and is easily avoidable with good habits.

Having an rvalue overload return by value means we have to pay for the cost of a copy (or move) even in cases where
we could have used a reference safely (e.g. in case 1 of the example at the top of the lesson).
Additionally:

Most C++ developers are not aware of this feature (which can lead to errors or inefficiencies in use).

The standard library typically does not make use of this feature.

Based on all of the above, we are not recommending the use of ref-qualifiers as a best practice. Instead, we recommend
always using the result of an access function immediately and not saving returned references for use later.
 */