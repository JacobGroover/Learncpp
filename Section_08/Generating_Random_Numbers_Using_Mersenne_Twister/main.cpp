#include <iostream>
#include <random> // for std::mt19937
#include <chrono> // for std::chrono

int main()
{

	// SEEDING WITH THE SYSTEM CLOCK

	/*
	To minimize the chance of two time values being identical if the program is run quickly in succession, we want
	to use some time measure that changes as quickly as possible. For this, we’ll ask the clock how much time has
	passed since the earliest time it can measure. This time is measured in “ticks”, which is a very small unit of
	time (usually nanoseconds, but could be milliseconds).

	The downside of this approach is that if the program is run several times in quick succession, the seeds
	generated for each run won’t be that different, which can impact the quality of the random results from a
	statistical standpoint. For normal programs, this doesn’t matter, but for programs that require high quality,
	independent results, this method of seeding may be insufficient.

	std::chrono::high_resolution_clock is a popular choice instead of std::chrono::steady_clock.
	std::chrono::high_resolution_clock is the clock that uses the most granular unit of time, but
	it may use the system clock for the current time, which can be changed or rolled back by users.
	std::chrono::steady_clock may have a less granular tick time, but is the only clock with a
	guarantee that users cannot adjust it.
	 */

	// Seed our Mersenne Twister using steady_clock
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	// std::mt19937 mt{ static_cast<std::mt19937::result_type>(
	// 	std::chrono::high_resolution_clock::now().time_since_epoch().count()
	// 	) };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6_1{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6_1{ 1, 6 };

	// Print a bunch of random numbers, and record the numbers into array
	int numRollsArray1[6]{};	// instantiate array to hold die roll values for later use in histogram
	for (int count{ 1 }; count <= 40; ++count)
	{
		int currentRoll{ die6_1(mt) }; // save value of current roll
		std::cout << currentRoll << '\t'; // generate a roll of the die here (printed to console)
		++numRollsArray1[currentRoll - 1]; // increment index of the array corresponding to the number on the die roll

		// std::cout << die6_1(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	// Print basic histogram to display number distribution
	std::cout << '\n' << "== HISTOGRAM DISTRIBUTION ==" << '\n';
	for (int index{ 0 }; index < 6; ++index) {
		std::cout << index + 1 << " | ";
		for (int count { 0 }; count < numRollsArray1[index]; ++count) {
			std::cout << '*';	// Print a '*' for each time the die roll landed on a given number corresponding to an index
		}
		std::cout << '\n';
	}

	// SEEDING WITH THE RANDOM DEVICE

	/*
	The random library contains a type called std::random_device that is an implementation-defined PRNG.
	Normally we avoid implementation-defined capabilities because they have no guarantees about quality or
	portability, but this is one of the exception cases. Typically std::random_device will ask the OS for a
	pseudo-random number (how it does this depends on the OS).
	 */

	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
	std::mt19937 mt2{ ss }; // initialize our Mersenne Twister with the std::seed_seq

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6_2{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6_2{ 1, 6 };

	// Print a bunch of random numbers, and record the numbers into array
	int numRollsArray2[6]{};	// instantiate array to hold die roll values for later use in histogram
	for (int count{ 1 }; count <= 40; ++count)
	{
		int currentRoll{ die6_2(mt2) }; // save value of current roll
		std::cout << currentRoll << '\t'; // generate a roll of the die here (printed to console)
		++numRollsArray2[currentRoll - 1]; // increment index of the array corresponding to the number on the die roll

		// std::cout << die6_2(mt2) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	// Print basic histogram to display number distribution
	std::cout << '\n' << "== HISTOGRAM DISTRIBUTION ==" << '\n';
	for (int index{ 0 }; index < 6; ++index) {
		std::cout << index + 1 << " | ";
		for (int count { 0 }; count < numRollsArray2[index]; ++count) {
			std::cout << '*';	// Print a '*' for each time the die roll landed on a given number corresponding to an index
		}
		std::cout << '\n';
	}

	return 0;
}