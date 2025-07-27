/*
L-value reference				Can be initialized with			Can modify
Modifiable l-values				Yes								Yes
Non-modifiable l-values			No								No
R-values						No								No


L-value reference to const		Can be initialized with			Can modify
Modifiable l-values				Yes								No
Non-modifiable l-values			Yes								No
R-values						Yes								No

R-value reference				Can be initialized with			Can modify
Modifiable l-values				No								No
Non-modifiable l-values			No								No
R-values						Yes								Yes

R-value reference to const		Can be initialized with			Can modify
Modifiable l-values				No								No
Non-modifiable l-values			No								No
R-values						Yes								No


R-value references have two properties that are useful.

1. First, r-value references extend the lifespan of the object they are initialized with to the lifespan of the
r-value reference (l-value references to const objects can do this too).
NOTE: LESSON TAUGHT THIS BUT... I DO NOT THINK THIS IS CORRECT:
End of lesson states:
"You should almost never return an r-value reference, for the same reason you should almost never return an
l-value reference. In most cases, you’ll end up returning a hanging reference when the referenced object goes
out of scope at the end of the function."

2. Second, non-const r-value references allow you to modify the r-value.
 */


// R-value references are more often used as function parameters.
// This is most useful for function overloads when you want to have different behavior for l-value and r-value arguments.
#include <iostream>

void fun(const int& lref) // l-value arguments will select this function
{
	std::cout << "l-value reference to const: " << lref << '\n';
}

void fun(int&& rref) // r-value arguments will select this function
{
	std::cout << "r-value reference: " << rref << '\n';
}

int main()
{
	int x{ 5 };
	fun(x); // l-value argument calls l-value version of function
	fun(5); // r-value argument calls r-value version of function

	return 0;
}

/*
Rvalue reference variables are lvalues

Consider the following snippet:

int&& ref{ 5 };
fun(ref);
Which version of fun would you expect the above to call: fun(const int&) or fun(int&&)?

The answer might surprise you. This calls fun(const int&).

Although variable ref has type int&&, when used in an expression it is an lvalue (as are all named variables). The type of an object and its value category are independent.

You already know that literal 5 is an rvalue of type int, and int x is an lvalue of type int. Similarly, int&& ref is an lvalue of type int&&.

So not only does fun(ref) call fun(const int&), it does not even match fun(int&&), as rvalue references can’t bind to lvalues.
 */

/*
You should almost never return an r-value reference, for the same reason you should almost never return an
l-value reference. In most cases, you’ll end up returning a hanging reference when the referenced object goes
out of scope at the end of the function.
 */