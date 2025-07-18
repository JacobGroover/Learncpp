#include <bitset>
#include <iostream>
#include <cstdint>  // for std::int8_t

// Define a new unscoped enumeration named Color

// It is possible to explicitly specify an underlying type for an enumeration. The underlying type must be an
// integral type. For example, if you are working in some bandwidth-sensitive context (e.g. sending data over a
// network) you may want to specify a smaller type for your enumeration:
// Use an 8-bit integer as the enum underlying type
enum Color : std::int8_t
{
	// Here are the enumerators
	// These symbolic constants define all the possible values this type can hold
	// Each enumerator is separated by a comma, not a semicolon
	black,
	red,
	blue,
	green, // trailing comma optional but recommended
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

	Color c{ black };
	std::cout << sizeof(c) << '\n'; // prints 1 (byte)

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