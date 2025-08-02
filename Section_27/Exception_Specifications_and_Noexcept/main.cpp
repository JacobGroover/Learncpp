// The following program illustrates the behavior of noexcept functions and exceptions in various cases:

// h/t to reader yellowEmu for the first draft of this program
#include <iostream>

class Doomed
{
public:
	~Doomed()
	{
		std::cout << "Doomed destructed\n";
	}
};

void thrower()
{
	std::cout << "Throwing exception\n";
	throw 1;
}

void pt()
{
	std::cout << "pt (potentally throwing) called\n";
	//This object will be destroyed during stack unwinding (if it occurs)
	Doomed doomed{};
	thrower();
	std::cout << "This never prints\n";
}

void nt() noexcept
{
	std::cout << "nt (noexcept) called\n";
	//This object will be destroyed during stack unwinding (if it occurs)
	Doomed doomed{};
	thrower();
	std::cout << "this never prints\n";
}

void tester(int c) noexcept
{
	std::cout << "tester (noexcept) case " << c << " called\n";
	try
	{
		(c == 1) ? pt() : nt();
	}
	catch (...)
	{
		std::cout << "tester caught exception\n";
	}
}

int main()
{
	std::cout << std::unitbuf; // flush buffer after each insertion
	std::cout << std::boolalpha; // print boolean as true/false
	tester(1);
	std::cout << "Test successful\n\n";
	tester(2);
	std::cout << "Test successful\n";

	return 0;
}

/*
The noexcept operator can also be used inside expressions. It takes an expression as an argument, and returns true or
false if the compiler thinks it will throw an exception or not. The noexcept operator is checked statically at
compile-time, and doesn’t actually evaluate the input expression.
 */

void foo() {throw -1;}
void boo() {};
void goo() noexcept {};
struct S{};

constexpr bool b1{ noexcept(5 + 3) }; // true; ints are non-throwing
constexpr bool b2{ noexcept(foo()) }; // false; foo() throws an exception
constexpr bool b3{ noexcept(boo()) }; // false; boo() is implicitly noexcept(false)
constexpr bool b4{ noexcept(goo()) }; // true; goo() is explicitly noexcept(true)
constexpr bool b5{ noexcept(S{}) };   // true; a struct's default constructor is noexcept by default

/*
The noexcept operator can be used to conditionally execute code depending on whether it is potentially throwing or not.
This is required to fulfill certain exception safety guarantees, which we’ll talk about in the next section.


An exception safety guarantee is a contractual guideline about how functions or classes will behave in the event an
exception occurs. There are four levels of exception safety guarantees:

- No guarantee -- There are no guarantees about what will happen if an exception is thrown (e.g. a class may be left in
an unusable state)

- Basic guarantee -- If an exception is thrown, no memory will be leaked and the object is still usable, but the program
may be left in a modified state.

- Strong guarantee -- If an exception is thrown, no memory will be leaked and the program state will not be changed.
This means the function must either completely succeed or have no side effects if it fails. This is easy if the failure
happens before anything is modified in the first place, but can also be achieved by rolling back any changes so the
program is returned to the pre-failure state.

- No throw / No fail guarantee -- The function will always succeed (no-fail) or fail without throwing an exception
that is exposed to the caller (no-throw). Exceptions may be thrown internally if not exposed. The noexcept specifier
maps to this level of exception safety guarantee.


There are a few good reasons to mark functions a non-throwing:

- Non-throwing functions can be safely called from functions that are not exception-safe, such as destructors

- Functions that are noexcept can enable the compiler to perform some optimizations that would not otherwise be
available. Because a noexcept function cannot throw an exception outside the function, the compiler doesn’t have
to worry about keeping the runtime stack in an unwindable state, which can allow it to produce faster code.

- There are significant cases where knowing a function is noexcept allows us to produce more efficient implementations
in our own code: the standard library containers (such as std::vector) are noexcept aware and will use the noexcept
operator to determine whether to use move semantics (faster) or copy semantics (slower) in some places. We cover move
semantics in chapter 22, and this optimization in lesson 27.10 -- std::move_if_noexcept.


The standard library’s policy is to use noexcept only on functions that must not throw or fail. Functions that are
potentially throwing but do not actually throw exceptions (due to implementation) typically are not marked as noexcept.

For your own code, always mark the following as noexcept:

- Move constructors

- Move assignment operators

- Swap functions

For your code, consider marking the following as noexcept:

- Functions for which you want to express a no-throw or no-fail guarantee (e.g. to document that they can be safely
called from destructors or other noexcept functions)

- Copy constructors and copy assignment operators that are no-throw (to take advantage of optimizations).

- Destructors. Destructors are implicitly noexcept so long as all members have noexcept destructors
 */