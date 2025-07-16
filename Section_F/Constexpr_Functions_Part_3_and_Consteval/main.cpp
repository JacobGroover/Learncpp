/*
For best results, we’d advise the following:

1. Avoid calling non-constexpr functions from within a constexpr function if possible.

2. If your constexpr function requires different behavior for constant and non-constant contexts,
conditionalize the behavior with if (std::is_constant_evaluated()) (in C++20) or if consteval (C++23 onward).

3. Always test your constexpr functions in a constant context, as they may work when called in a non-constant
context but fail in a constant context.
*/

/*
Using consteval to make constexpr execute at compile-time C++20

The downside of consteval functions is that such functions can’t evaluate at runtime, making them less flexible
than constexpr functions, which can do either. Therefore, it would still be useful to have a convenient way to
force constexpr functions to evaluate at compile-time (even when the return value is being used where a constant
expression is not required), so that we can explicitly force compile-time evaluation when possible, and runtime
evaluation when we can’t.

Here’s an example that shows how this is possible:

This uses a variadic preprocessor macro (the #define, ..., and __VA_ARGS__) to define an consteval lambda that is immediately invoked (by the trailing parentheses).
You can find information on variadic macros at https://en.cppreference.com/w/cpp/preprocessor/replace.
We cover lambdas in lesson 20.6 -- Introduction to lambdas (anonymous functions).
*/

// #include <iostream>
//
// #define CONSTEVAL(...) [] consteval { return __VA_ARGS__; }()               // C++20 version per Jan Scultke (https://stackoverflow.com/a/77107431/460250)
// #define CONSTEVAL11(...) [] { constexpr auto _ = __VA_ARGS__; return _; }() // C++11 version per Justin (https://stackoverflow.com/a/63637573/460250)
//
// // This function returns the greater of the two numbers if executing in a constant context
// // and the lesser of the two numbers otherwise
// constexpr int compare(int x, int y) // function is constexpr
// {
// 	if (std::is_constant_evaluated())
// 		return (x > y ? x : y);
// 	else
// 		return (x < y ? x : y);
// }
//
// int main()
// {
// 	int x { 5 };
// 	std::cout << compare(x, 6) << '\n';                  // will execute at runtime and return 5
//
// 	std::cout << compare(5, 6) << '\n';                  // may or may not execute at compile-time, but will always return 5
// 	std::cout << CONSTEVAL(compare(5, 6)) << '\n';       // will always execute at compile-time and return 6
//
//
// 	return 0;
// }

// The following should also work (and is a bit cleaner since it doesn’t use preprocessor macros):

#include <iostream>

// Uses abbreviated function template (C++20) and `auto` return type to make this function work with any type of value
// See 'related content' box below for more info (you don't need to know how these work to use this function)
// We've opted to use an uppercase name here for consistency with the prior example, but it also makes it easier to see the call
consteval auto CONSTEVAL(auto value)
{
	return value;
}

// This function returns the greater of the two numbers if executing in a constant context
// and the lesser of the two numbers otherwise
constexpr int compare(int x, int y) // function is constexpr
{
	if (std::is_constant_evaluated())
		return (x > y ? x : y);
	else
		return (x < y ? x : y);
}

int main()
{
	std::cout << CONSTEVAL(compare(5, 6)) << '\n';       // will execute at compile-time

	return 0;
}

/*
Why not constexpr every function?

There are a few reasons you may not want to constexpr a function:

1. constexpr signals that a function can be used in a constant expression. If your function cannot be evaluated as
part of a constant expression, it should not be marked as constexpr.

2. constexpr is part of the interface of a function. Once a function is made constexpr, it can be called by other
constexpr functions or used in contexts that require constant expressions. Removing the constexpr later will break
such code.

3. constexpr functions can be harder to debug since you can’t breakpoint or step through them in a debugger.
*/


/*
Why constexpr a function when it is not actually evaluated at compile-time?

New programmers sometimes ask, “why should I constexpr a function when it is only evaluated at runtime in my program
(e.g. because the arguments in the function call are non-const)”?

There are a few reasons:

1. There’s little downside to using constexpr, and it may help the compiler optimize your program to be
smaller and faster.

2. Just because you’re not calling the function in a compile-time evaluatable context right now doesn’t
mean you won’t call it in such a context when you modify or extend your program. And if you haven’t constexpr’d
the function already, you may not think to when you do start to call it in such a context, and then you’ll miss
out on the performance benefits. Or you may be forced to constexpr it later when you need to use the return value
in a context that requires a constant expression somewhere.

3. Repetition helps ingrain best practices.

On a non-trivial project, it’s a good idea to implement your functions with the mindset that they may be reused
(or extended) in the future. Any time you modify an existing function, you risk breaking it, and that means it
needs to be retested, which takes time and energy. It’s often worth spending an extra minute or two “doing it
right the first time” so you don’t have to redo (and retest) it again later.
 */