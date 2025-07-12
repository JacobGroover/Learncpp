#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)

/*
 NOTES ON RANDOM.H IMPLEMENTATION:

Normally, defining variables and functions in a header file would cause violations of the one-definition rule (ODR)
when that header file was included into more than one source file. However, we’ve made our mt variable and supporting
functions inline, which allows us to have duplicate definitions without violating the ODR so long as those definitions
are all identical. Because we’re #including those definitions from a header file (rather than typing them manually, or
copy/pasting them), we can ensure they are identical. Inline functions and variables were added to the language largely
to make doing this kind of header-only functionality possible.

The other challenge that we have to overcome is in how we initialize our global Random::mt object, as we want it to be
self-seeding so that we don’t have to remember to explicitly call an initialization function for it to work correctly.
Our initializer must be an expression. But in order to initialize a std::mt19937, we need several helper objects
(a std::random_device and a std::seed_seq) which must be defined as statements. This is where a helper function comes
in handy. A function call is an expression, so we can use the return value of a function as an initializer. And inside
the function itself, we can have any combination of statements that we need. Thus, our generate() function creates and
returns a fully-seeded std::mt19937 object (seeded using both the system clock and std::random_device) that we use as
the initializer to our global Random::mt object.
 */
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		// High resolution clock version, can be manipulated by users client-side by manually changing clock time, but
		// may be useful for higher granularity using server-side clock for certain applications:

		// std::seed_seq ss{
		// 	static_cast<std::seed_seq::result_type>(std::chrono::high_resolution_clock::now().time_since_epoch().count()),
		// 		rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
        // * also handles cases where the two arguments have different types but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers in other cases

	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
        // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif