#include <bitset>
#include <iostream>

// Define a new unscoped enumeration named Color
enum Color
{
	// Here are the enumerators
	// These symbolic constants define all the possible values this type can hold
	// Each enumerator is separated by a comma, not a semicolon
	red,
	green,
	blue, // trailing comma optional but recommended
}; // the enum definition must end with a semicolon

namespace Flags
{
	enum State
	{
		isHungry,
		isSad,
		isMad,
		isHappy,
		isLaughing,
		isAsleep,
		isDead,
		isCrying,
	};
}

int main()
{
	// Define a few variables of enumerated type Color
	Color apple { red };   // my apple is red
	Color shirt { green }; // my shirt is green
	Color cup { blue };    // my cup is blue

	// Color socks { white }; // error: white is not an enumerator of Color
	// Color hat { 2 };       // error: 2 is not an enumerator of Color



// In lesson O.1 -- Bit flags and bit manipulation via std::bitset, we discussed bit flags. Enums can also be used to
// define a collection of related bit flag positions for use with std::bitset:

	std::bitset<8> me{};
	me.set(Flags::isHappy);
	me.set(Flags::isLaughing);

	std::cout << std::boolalpha; // print bool as true/false

	// Query a few states (we use the any() function to see if any bits remain set)
	std::cout << "I am happy? " << me.test(Flags::isHappy) << '\n';
	std::cout << "I am laughing? " << me.test(Flags::isLaughing) << '\n';

	return 0;
}