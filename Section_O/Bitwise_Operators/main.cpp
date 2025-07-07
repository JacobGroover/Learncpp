#include <bitset>
#include <cstdint>
#include <iostream>

/*
NOTE: SEE LINE 149 FOR RELATED CODE/CONCEPT
A bitwise rotation is like a bitwise shift, except that any bits shifted off one end are added back to
the other end. For example 0b1001 << 1 would be 0b0010, but a left rotate by 1 would result in 0b0011 instead.
Implement a function that does a left rotate on a std::bitset<4>. For this one, it’s okay to use test() and set().
*/
// "rotl" stands for "rotate left"
std::bitset<4> rotl(std::bitset<4> bits)
{
	// Your code here:
	const bool leftBit { bits.test(bits.size() - 1) };

	bits <<= 1;

	if (leftBit) {
		bits.set(0);
	}
	return bits;
}

// Extra credit: Redo the above method but don’t use the test and set functions (use bitwise operators).
std::bitset<4> rotlEC(std::bitset<4> bits) {
	return (bits << 1) | (bits >> bits.size() - 1);
}

int main() {
	std::bitset<4> x{0b1100};

	std::cout << x << '\n';
	std::cout << (x >> 1) << '\n'; // shift right by 1, yielding 0110
	std::cout << (x << 1) << '\n'; // shift left by 1, yielding 1000

	/*
	 Note that if you’re using operator<< for both output and left shift, parenthesization is required to use for left-shifting:
	 */
	std::bitset<4> x2{0b0110};

	std::cout << x2 << 1 << '\n'; // print value of x (0110), then 1
	std::cout << (x2 << 1) << '\n' << '\n'; // print x left shifted by 1 (1100)

	/*
	 When interpreted as an integer, the number of bits in the result of a bitwise NOT affects the value produced.
	 The following example illustrates this:
	*/
	std::bitset<4> b4{0b100}; // b4 is 0100
	std::bitset<8> b8{0b100}; // b8 is 0000 0100

	std::cout << "Initial values:\n";
	std::cout << "Bits: " << b4 << ' ' << b8 << '\n';
	std::cout << "Values: " << b4.to_ulong() << ' ' << b8.to_ulong() << "\n\n";

	b4 = ~b4; // flip b4 to 1011
	b8 = ~b8; // flip b8 to 1111 1011

	std::cout << "After bitwise NOT:\n";
	std::cout << "Bits: " << b4 << ' ' << b8 << '\n';
	std::cout << "Values: " << b4.to_ulong() << ' ' << b8.to_ulong() << '\n' << '\n';

	/*
	Bitwise OR (|) works much like its logical OR counterpart. If you remember, logical OR evaluates to true (1) if either of the operands are true, otherwise it evaluates to false (0).
	However, whereas logical OR is applied to the entire operand (to produce a single true or false result),
	bitwise OR is applied to each pair of bits in the operands (to produce a single true or false result for each bit).

	Let’s illustrate this with an example. Consider the expression 0b0101 | 0b0110:
	 */
	std::cout << "Bitwise OR Result: " << (std::bitset<4>{0b0101} | std::bitset<4>{0b0110}) << '\n' << '\n';

	/*
	Bitwise AND (&) works similarly to the above, except it uses AND logic instead of OR logic. That is, for each pair of bits in the operands, Bitwise AND sets the resulting bit to true (1) if both paired bits are 1, and false (0) otherwise.

	Consider the expression 0b0101 & 0b0110. Lining each of the bits up and applying bitwise AND to each column of bits:
	 */
	std::cout << "Bitwise AND Result: " << (std::bitset<4>{0b0101} & std::bitset<4>{0b0110}) << '\n' << '\n';

	/*
	 Similarly, we can do the same thing to compound bitwise AND expressions, such as 0b0001 & 0b0011 & 0b0111.
	 If all the bits in a column are 1, the result of that column is 1.
	 */
	std::cout << "Compound Bitwise AND Result: " << (std::bitset<4>{0b0001} & std::bitset<4>{0b0011} & std::bitset<4>{
		                                                 0b0111
	                                                 }) << '\n' << '\n';

	/*
	 For each pair of bits in the operands, Bitwise XOR sets the resulting bit to true (1) when exactly one of the paired bits is 1, and false (0) otherwise. Put another way, Bitwise XOR sets the resulting bit to true when the paired bits are different (one is a 0 and the other a 1).

	 Consider the expression 0b0110 ^ 0b0011:
	 */

	std::cout << "Bitwise XOR Result: " << (std::bitset<4>{0b0110} ^ std::bitset<4>{0b0011}) << '\n' << '\n';
	// This also works for compound expressions for bitwise XOR.

	/*
	 Similar to the arithmetic assignment operators, C++ provides bitwise assignment operators. These do modify the left operand.

	left shift		<<	x <<= n		the bits in x are shifted left by n positions, new bits are 0.
	right shift		>>	x >>= n		the bits in x are shifted right by n positions, new bits are 0.
	bitwise AND		&	x &= y		each bit is set when both corresponding bits in x and y are 1.
	bitwise OR		|	x |= y		each bit is set when either corresponding bit in x and y is 1.
	bitwise XOR		^	x ^= y		each bit is set when the corresponding bits in x and y are different.

	For example, instead of writing x = x >> 1; you can write x >>= 1;
	 */

	std::bitset<4> bits { 0b0100 };
	bits >>= 1;
	std::cout << "Bitwise Right Shift Result: " << bits << '\n' << '\n';

	/*
	 There is no bitwise NOT assignment operator. This is because the other bitwise operators are binary,
	 but bitwise NOT is unary (so what would go on the right-hand side of a ~= operator?). If you want to
	 flip all the bits of an object, you can use normal assignment: x = ~x;
	 */

	/*
	When using bitwise operators on integral types narrower than int or unsigned int, there are two cases to watch out for:

	1) operator~ and operator<< are width-sensitive and may produce different results depending on the width of the operand.

	2) Initializing or assigning the result to a variable of the smaller integral type is a narrowing conversion
	(since converting an int or unsigned int to a smaller integral type may result in data loss). This is disallowed
	in list initialization, and your compiler may or may not complain about a narrowing assignment.

	The following example exhibits these issues (assuming 32-bit ints):
	 */

	std::uint8_t c { 0b00001111 };

	std::cout << "Narrowing Conversions cases to watch out for: " << '\n';
	std::cout << std::bitset<32>(~c) << '\n';			// incorrect: prints 11111111111111111111111111110000
	std::cout << std::bitset<32>(c << 6) << '\n';	// incorrect: prints 0000000000000000001111000000
	//std::uint8_t cneg { ~c };							// error: narrowing conversion from unsigned int to std::uint8_t
	c = ~c;												// possible warning: narrowing conversion from unsigned int to std::uint8_t

	// These issues can be addressed by using static_cast to convert the result of your bitwise operation back
	// to the narrower integral type. The following program produces the correct results:
	std::cout << '\n' << "Correct handling of Narrowing Conversions: " << '\n';
	std::uint8_t c2 { 0b00001111 };

	std::cout << std::bitset<32>(static_cast<std::uint8_t>(~c2)) << '\n';     // correct: prints 00000000000000000000000011110000
	std::cout << std::bitset<32>(static_cast<std::uint8_t>(c2 << 6)) << '\n' << '\n'; // correct: prints 0000000000000000000011000000
	std::uint8_t cneg { static_cast<std::uint8_t>(~c) };                     // compiles
	c2 = static_cast<std::uint8_t>(~c);                                       // no warning

	/*
	 A bitwise rotation is like a bitwise shift, except that any bits shifted off one end are added back to
	 the other end. For example 0b1001 << 1 would be 0b0010, but a left rotate by 1 would result in 0b0011 instead.
	 Implement a function that does a left rotate on a std::bitset<4>. For this one, it’s okay to use test() and set().
	 (for compile ordering, the function has been moved to the top of this file)
	 */

	std::bitset<4> bits1{ 0b0001 };
	std::cout << rotl(bits1) << '\n';

	std::bitset<4> bits2{ 0b1001 };
	std::cout << rotl(bits2) << '\n' << '\n';

	std::cout << "Extra Credit version: " << '\n';
	std::cout << rotlEC(bits1) << '\n';
	std::cout << rotlEC(bits2) << '\n' << '\n';
	// std::cout << rotlEC(std::bitset<4> { 0b1000 }) << '\n';
	// std::cout << rotlEC(std::bitset<4> { 0b0100 }) << '\n';
	// std::cout << rotlEC(std::bitset<4> { 0b0010 }) << '\n';
	// std::cout << rotlEC(std::bitset<4> { 0b1110 }) << '\n';

	return 0;
}
