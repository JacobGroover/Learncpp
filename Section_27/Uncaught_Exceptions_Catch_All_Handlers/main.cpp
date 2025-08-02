// #include <iostream>
//
// struct GameSession
// {
// 	// Game session data here
// };
//
// void runGame(GameSession&)
// {
// 	throw 1;
// }
//
// void saveGame(GameSession&)
// {
// 	// Save user's game here
// }
//
// int main()
// {
// 	GameSession session{};
//
// 	try
// 	{
// 		runGame(session);
// 	}
// 	catch(...)
// 	{
// 		std::cerr << "Abnormal termination\n";
// 	}
//
// 	saveGame(session); // save the user's game (even if catch-all handler was hit)
//
// 	return 0;
// }

/*
If your program uses exceptions, consider using a catch-all handler in main, to help ensure orderly behavior if
an unhandled exception occurs.

If an exception is caught by the catch-all handler, you should assume the program is now in some indeterminate state,
perform cleanup immediately, and then terminate.
 */

/*
Unhandled exceptions are an indication that something unexpected has happened, and we probably want to diagnose
why an unhandled exception was thrown in the first place. Many debuggers will (or can be configured to) break on
unhandled exceptions, allowing us to view the stack at the point where the unhandled exception was thrown. However,
if we have a catch-all handler, then all exceptions are handled, and (because the stack is unwound) we lose useful
diagnostic information.

Therefore, in debug builds, it can be useful to disable the catch-all handler. We can do this via conditional
compilation directives.

Here’s one way to do that:
 */

#include <iostream>

struct GameSession
{
	// Game session data here
};

void runGame(GameSession&)
{
	throw 1;
}

void saveGame(GameSession&)
{
	// Save user's game here
}

class DummyException // a dummy class that can't be instantiated
{
	DummyException() = delete;
};

int main()
{
	GameSession session {};

	try
	{
		runGame(session);
	}
#ifndef NDEBUG // if we're in release node
	catch(...) // compile in the catch-all handler
	{
		std::cerr << "Abnormal termination\n";
	}
#else // in debug mode, compile in a catch that will never be hit (for syntactic reasons)
	catch(DummyException)
	{
	}
#endif

	saveGame(session); // save the user's game (even if catch-all handler was hit)

	return 0;
}