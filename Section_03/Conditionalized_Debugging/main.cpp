/*
 *
 * We can enable debugging simply by commenting / uncommenting #define ENABLE_DEBUG.
 * This allows us to reuse previously added debug statements and then just disable them when we’re done with them,
 * rather than having to actually remove them from the code. If this were a multi-file program,
 * the #define ENABLE_DEBUG would go in a header file that’s included into all code files so we can
 * comment / uncomment the #define in a single location and have it propagate to all code files.
 *
 * This addresses the issue with having to remove debug statements and the risk in doing so, but at the
 * cost of even more code clutter. Another downside of this approach is that if you make a typo
 * (e.g. misspell “DEBUG”) or forget to include the header into a code file, some or all of the debugging
 * for that file may not be enabled. So although this is better than the unconditionalized version, there’s
 * still room to improve.
 */

#include <iostream>

#define ENABLE_DEBUG // comment out to disable debugging

int getUserInput()
{
#ifdef ENABLE_DEBUG
	std::cerr << "getUserInput() called\n";
#endif
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
#ifdef ENABLE_DEBUG
	std::cerr << "main() called\n";
#endif
	int x{ getUserInput() };
	std::cout << "You entered: " << x << '\n';

	return 0;
}