#include <bitset>
#include <cstdint>
#include <iostream>

/*
	SUMMARY

	Summarizing how to set, clear, toggle, and query bit flags:
	To query bit states, we use bitwise AND:

	if (flags & option4) ... // if option4 is set, do something

	To set bits (turn on), we use bitwise OR:
	flags |= option4; // turn option 4 on.
	flags |= (option4 | option5); // turn options 4 and 5 on.

	To clear bits (turn off), we use bitwise AND with bitwise NOT:
	flags &= ~option4; // turn option 4 off
	flags &= ~(option4 | option5); // turn options 4 and 5 off

	To flip bit states, we use bitwise XOR:
	flags ^= option4; // flip option4 from on to off, or vice versa
	flags ^= (option4 | option5); // flip options 4 and 5
*/

int main() {
	// Defining bit masks in C++14:
	// constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
	// constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
	// constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
	// constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
	// constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
	// constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
	// constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
	// constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

	// Defining bit masks in C++11 or earlier:
	// Using Hexadecimal:
	// constexpr std::uint8_t mask0{ 0x01 }; // hex for 0000 0001
	// constexpr std::uint8_t mask1{ 0x02 }; // hex for 0000 0010
	// constexpr std::uint8_t mask2{ 0x04 }; // hex for 0000 0100
	// constexpr std::uint8_t mask3{ 0x08 }; // hex for 0000 1000
	// constexpr std::uint8_t mask4{ 0x10 }; // hex for 0001 0000
	// constexpr std::uint8_t mask5{ 0x20 }; // hex for 0010 0000
	// constexpr std::uint8_t mask6{ 0x40 }; // hex for 0100 0000
	// constexpr std::uint8_t mask7{ 0x80 }; // hex for 1000 0000

	// Using left-shift operator (simpler):
	// constexpr std::uint8_t mask0{ 1 << 0 }; // 0000 0001
	// constexpr std::uint8_t mask1{ 1 << 1 }; // 0000 0010
	// constexpr std::uint8_t mask2{ 1 << 2 }; // 0000 0100
	// constexpr std::uint8_t mask3{ 1 << 3 }; // 0000 1000
	// constexpr std::uint8_t mask4{ 1 << 4 }; // 0001 0000
	// constexpr std::uint8_t mask5{ 1 << 5 }; // 0010 0000
	// constexpr std::uint8_t mask6{ 1 << 6 }; // 0100 0000
	// constexpr std::uint8_t mask7{ 1 << 7 }; // 1000 0000

	// Testing a bit to see if it's on or off:
	[[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
	[[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
	[[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
	[[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
	[[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
	[[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
	[[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
	[[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

	std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

	std::cout << "Testing a bit for on/off:\n";
	std::cout << "bit 0 is " << (static_cast<bool>(flags & mask0) ? "on\n" : "off\n");
	std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

	// Setting a bit:
	std::cout << "\nSetting a bit:\n";
	std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

	flags |= mask1; // turn on bit 1

	std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

	std::cout << "\nSetting/Turning on multiple bits simultaneously:\n";
	// flags |= (mask4 | mask5); // turn bits 4 and 5 on at the same time

	// Resetting a bit:
	std::cout << "\nResetting a bit:\n";
	std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

	flags &= ~mask2; // turn off bit 2

	std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

	// flags &= ~(mask4 | mask5); // turn bits 4 and 5 off at the same time
	// flags &= static_cast<std::uint8_t>(~mask2); // use this if compiler complains and integral promotion

	// Flipping a bit (on to off, or off to on) using bitwise XOR:
	std::cout << "\nFlipping a bit:\n";
	std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
	flags ^= mask2; // flip bit 2
	std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
	flags ^= mask2; // flip bit 2
	std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

	// flags ^= (mask4 | mask5); // flip bits 4 and 5 at the same time

	// std::bitset supports bitwise operators as well as its own functions:
	std::cout << "\nstd::bitset supports bitwise operators as well as its own functions:\n";
	std::bitset<8> flags2{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
	std::cout << "bit 1 is " << (flags2.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags2.test(2) ? "on\n" : "off\n");

	flags2 ^= (mask1 | mask2); // flip bits 1 and 2
	std::cout << "bit 1 is " << (flags2.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags2.test(2) ? "on\n" : "off\n");

	flags2 |= (mask1 | mask2); // turn bits 1 and 2 on
	std::cout << "bit 1 is " << (flags2.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags2.test(2) ? "on\n" : "off\n");

	flags2 &= ~(mask1 | mask2); // turn bits 1 and 2 off
	std::cout << "bit 1 is " << (flags2.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags2.test(2) ? "on\n" : "off\n");

	// Making bit masks meaningful with better naming conventions:
	std::cout << "\nMaking bit masks meaningful with better naming conventions:\n";

	// Define a bunch of physical/emotional states
	[[maybe_unused]] constexpr std::uint8_t isHungry   { 1 << 0 }; // 0000 0001
	[[maybe_unused]] constexpr std::uint8_t isSad      { 1 << 1 }; // 0000 0010
	[[maybe_unused]] constexpr std::uint8_t isMad      { 1 << 2 }; // 0000 0100
	[[maybe_unused]] constexpr std::uint8_t isHappy    { 1 << 3 }; // 0000 1000
	[[maybe_unused]] constexpr std::uint8_t isLaughing { 1 << 4 }; // 0001 0000
	[[maybe_unused]] constexpr std::uint8_t isAsleep   { 1 << 5 }; // 0010 0000
	[[maybe_unused]] constexpr std::uint8_t isDead     { 1 << 6 }; // 0100 0000
	[[maybe_unused]] constexpr std::uint8_t isCrying   { 1 << 7 }; // 1000 0000

	std::uint8_t me{}; // all flags/options turned off to start
	me |= (isHappy | isLaughing); // I am happy and laughing
	me &= ~isLaughing; // I am no longer laughing

	// Query a few states
	// (we'll use static_cast<bool> to interpret the results as a boolean value)
	std::cout << std::boolalpha; // print true or false instead of 1 or 0
	std::cout << "I am happy? " << static_cast<bool>(me & isHappy) << '\n';
	std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n';

	std::cout << "\nHere is the same example implemented using std::bitset:\n";
	[[maybe_unused]] constexpr std::bitset<8> isHungry2   { 1 << 0 }; // 0000 0001
	[[maybe_unused]] constexpr std::bitset<8> isSad2      { 1 << 1 }; // 0000 0010
	[[maybe_unused]] constexpr std::bitset<8> isMad2      { 1 << 2 }; // 0000 0100
	[[maybe_unused]] constexpr std::bitset<8> isHappy2    { 1 << 3 }; // 0000 1000
	[[maybe_unused]] constexpr std::bitset<8> isLaughing2 { 1 << 4 }; // 0001 0000
	[[maybe_unused]] constexpr std::bitset<8> isAsleep2   { 1 << 5 }; // 0010 0000
	[[maybe_unused]] constexpr std::bitset<8> isDead2     { 1 << 6 }; // 0100 0000
	[[maybe_unused]] constexpr std::bitset<8> isCrying2   { 1 << 7 }; // 1000 0000

	std::bitset<8> me2{}; // all flags/options turned off to start
	me2 |= (isHappy2 | isLaughing2); // I am happy and laughing
	me2 &= ~isLaughing2; // I am no longer laughing

	// Query a few states (we use the any() function to see if any bits remain set)
	std::cout << std::boolalpha; // print true or false instead of 1 or 0
	std::cout << "I am happy? " << (me2 & isHappy2).any() << '\n';
	std::cout << "I am laughing? " << (me2 & isLaughing2).any() << '\n';


	/*
	 Astute readers may note that the above examples don’t actually save any memory. 8 separate booleans values would
	 normally take 8 bytes. But the examples above (using std::uint8_t) use 9 bytes -- 8 bytes to define the bit masks,
	 and 1 byte for the flag variable!

	 Bit flags make the most sense when you have many identical flag variables. For example, in the example above,
	 imagine that instead of having one person (me), you had 100. If you used 8 Booleans per person (one for each
	 possible state), you’d use 800 bytes of memory. With bit flags, you’d use 8 bytes for the bit masks, and 100
	 bytes for the bit flag variables, for a total of 108 bytes of memory -- approximately 8 times less memory.

	 For most programs, the amount of memory saved using bit flags is not worth the added complexity. But in programs
	 where there are tens of thousands or even millions of similar objects, using bit flags can reduce memory use
	 substantially. It’s a useful optimization to have in your toolkit if you need it.

	 There’s another case where bit flags and bit masks can make sense. Imagine you had a function that could take any
	 combination of 32 different options. One way to write that function would be to use 32 individual Boolean parameters:

	 void someFunction(bool option1, bool option2, bool option3, bool option4, bool option5, bool option6,
	 bool option7, bool option8, bool option9, bool option10, bool option11, bool option12, bool option13,
	 bool option14, bool option15, bool option16, bool option17, bool option18, bool option19, bool option20,
	 bool option21, bool option22, bool option23, bool option24, bool option25, bool option26, bool option27,
	 bool option28, bool option29, bool option30, bool option31, bool option32);

	 Hopefully you’d give your parameters more descriptive names, but the point here is to show you how obnoxiously
	 long the parameter list is.

	 Then when you wanted to call the function with options 10 and 32 set to true, you’d have to do so like this:

	 someFunction(false, false, false, false, false, false, false, false, false, true, false, false, false, false,
	 false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false,
	 false, true);

	 This is ridiculously difficult to read (is that option 9, 10, or 11 that’s set to true?), and also means
	 you have to remember which argument corresponds to which option (is setting the “edit flag” the 9th, 10th,
	 or 11th parameter?).

	 Instead, if you defined the function using bit flags like this:
	 void someFunction(std::bitset<32> options);

	 Then you could use bit flags to pass in only the options you wanted:
	 someFunction(option10 | option32);
	 */


	// Bit masks involving multiple bits:

	// The following program asks the user to enter a 32-bit hexadecimal value,
	// and then extracts the 8-bit color values for R, G, B, and A:
	constexpr std::uint32_t redBits{ 0xFF000000 };
	constexpr std::uint32_t greenBits{ 0x00FF0000 };
	constexpr std::uint32_t blueBits{ 0x0000FF00 };
	constexpr std::uint32_t alphaBits{ 0x000000FF };

	std::cout << "Enter a 32-bit RGBA color value in hexadecimal (e.g. FF7F3300): ";
	std::uint32_t pixel{};
	// std::cin >> std::hex >> pixel; // std::hex allows us to read in a hex value

	// use Bitwise AND to isolate the pixels for our given color,
	// then right shift the value into the lower 8 bits
	const std::uint8_t red{ static_cast<std::uint8_t>((pixel & redBits) >> 24) };
	const std::uint8_t green{ static_cast<std::uint8_t>((pixel & greenBits) >> 16) };
	const std::uint8_t blue{ static_cast<std::uint8_t>((pixel & blueBits) >> 8) };
	const std::uint8_t alpha{ static_cast<std::uint8_t>(pixel & alphaBits) };

	std::cout << "Your color contains:\n";
	std::cout << std::hex; // print the following values in hex

	// reminder: std::uint8_t will likely print as a char
	// we static_cast to int to ensure it prints as an integer
	std::cout << static_cast<int>(red)   << " red\n";
	std::cout << static_cast<int>(green) << " green\n";
	std::cout << static_cast<int>(blue)  << " blue\n";
	std::cout << static_cast<int>(alpha) << " alpha\n";

	// In the above program, we use a bitwise AND to query the set of 8 bits we’re interested in, and then we
	// right shift them into an 8-bit value so we can print them back as hex values.


	// QUIZ:

	[[maybe_unused]] constexpr std::uint8_t option_viewed{ 0x01 };
	[[maybe_unused]] constexpr std::uint8_t option_edited{ 0x02 };
	[[maybe_unused]] constexpr std::uint8_t option_favorited{ 0x04 };
	[[maybe_unused]] constexpr std::uint8_t option_shared{ 0x08 };
	[[maybe_unused]] constexpr std::uint8_t option_deleted{ 0x10 };

	std::uint8_t myArticleFlags{ option_favorited };
	// std::uint8_t myArticleFlags{ option_favorited | option_deleted};

	// Place all lines of code for the following quiz here
		// a) Add a line of code to set the article as viewed. (expected output: 00000101)
	myArticleFlags |= option_viewed;
	std::cout << static_cast<std::bitset<8>>(myArticleFlags) << '\n';

		// b) Add a line of code to check if the article was deleted.
	if (myArticleFlags & option_deleted) {
		std::cout << "Item was deleted." << '\n';
	}

		// c) Add a line of code to clear the article as a favorite. (expected output assuming part a) is correct: 00000001)
	// myArticleFlags &= ~option_favorited; // This is bad practice, because it fails to make explicit the type promotion from std::uint8_t to int before applying the bitwise operation. Some compilers may not catch this.
	myArticleFlags &= static_cast<std::uint8_t>(~option_favorited); // This is a more robust solution than the line above due to type promotion characteristics.
	std::cout << static_cast<std::bitset<8>>(myArticleFlags) << '\n';

	// d) Extra credit: why are the following two lines identical?
	// myflags &= ~(option4 | option5); // turn options 4 and 5 off
	// myflags &= ~option4 & ~option5; // turn options 4 and 5 off
	// ANSWER: De Morgan’s laws says that if we distribute a NOT, we need to flip ORs and ANDs to the other. So ~(option4 | option5) becomes ~option4 & ~option5.

	return 0;
}
