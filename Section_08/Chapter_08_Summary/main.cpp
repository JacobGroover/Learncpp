#include <algorithm>
#include <iostream>
#include "Random.h"

// QUESTION #1:

// In lesson 4.x -- Chapter 4 summary and quiz, we wrote a program to simulate a ball falling off of a tower.
// Because we didn’t have loops yet, the ball could only fall for 5 seconds.

// Take the program below and modify it so that the ball falls for as many seconds as needed until it reaches the
// ground. Update the program to use all covered best practices (namespaces, constexpr, etc…).

// ORIGINAL:

// // Gets tower height from user and returns it
// double getTowerHeight()
// {
// 	std::cout << "Enter the height of the tower in meters: ";
// 	double towerHeight{};
// 	std::cin >> towerHeight;
// 	return towerHeight;
// }
//
// // Returns the current ball height after "seconds" seconds
// double calculateBallHeight(double towerHeight, int seconds)
// {
// 	const double gravity { 9.8 };
//
// 	// Using formula: s = (u * t) + (a * t^2) / 2
// 	// here u (initial velocity) = 0, so (u * t) = 0
// 	const double fallDistance { gravity * (seconds * seconds) / 2.0 };
// 	const double ballHeight { towerHeight - fallDistance };
//
// 	// If the ball would be under the ground, place it on the ground
// 	if (ballHeight < 0.0)
// 		return 0.0;
//
// 	return ballHeight;
// }
//
// // Prints ball height above ground
// void printBallHeight(double ballHeight, int seconds)
// {
// 	if (ballHeight > 0.0)
// 		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
// 	else
// 		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
// }
//
// // Calculates the current ball height and then prints it
// // This is a helper function to make it easier to do this
// void calculateAndPrintBallHeight(double towerHeight, int seconds)
// {
// 	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
// 	printBallHeight(ballHeight, seconds);
// }

// ANSWER:

namespace Constants
{
	constexpr double gravity { 9.8 };
}

// Gets tower height from user and returns it
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Returns the current ball height after "seconds" seconds
// note: this function could be constexpr, but we haven't covered constexpr functions yet
double calculateBallHeight(double towerHeight, int seconds)
{
	// Using formula: s = (u * t) + (a * t^2) / 2
	// here u (initial velocity) = 0, so (u * t) = 0
	const double fallDistance { Constants::gravity * (seconds * seconds) / 2.0 };
	const double ballHeight { towerHeight - fallDistance };

	if (ballHeight < 0.0)
		return 0.0;

	return ballHeight;
}

// Prints ball height above ground
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// Calculates the current ball height and then prints it
// This is a helper function to make it easier to do this
double calculateAndPrintBallHeight(double towerHeight, int seconds)
{
	const double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);

	return ballHeight;
}

// QUESTION #2:

// A prime number is a natural number greater than 1 that is evenly divisible (with no remainder) only by 1 and itself.

// Complete the following program by writing the isPrime() function using a for-loop. When successful,
// the program will print “Success!”.

// Extra credit:

// The for-loop in the above solution is suboptimal for two reasons:

// It checks even divisors. We don’t need to test these (except for 2).
// It checks every number up to x to see if it is a divisor. A non-prime number (a composite number) must have at least one divisor less than or equal to its square root, so checking for divisors beyond the square root of x is unnecessary. std::sqrt(x) (in the <cmath> header) returns the square root of x.
// For the latter, we have two options: calculate std::sqrt(x) prior to the loop, then test our loop variable against that value. Alternately, we can optimize std::sqrt(x) out of the comparison entirely by squaring both sides of the comparison (h/t to reader JJag for suggesting this) (see the hint if you need additional help with this). We’ll use this latter option in the quiz solution.

// Hint: Given two variables a >= 0 and b >= 0, we can square both sides of the comparison a <= sqrt(b) and the comparison will still hold. This gives us a * a <= sqrt(b) * sqrt(b), which is equivalent to a * a <= b.

// Make sure that assert triggers even if we compile in release mode
#undef NDEBUG

#include <cassert> // for assert
// #include <iostream>

bool isPrime(int x)
{
	// non-optimized version:

	// if (x <= 1) {
	// 	return false;
	// }
	// // write this function using a for loop
	// for (int count { 2 }; count <= x; ++count) {
	// 	if (x % count == 0) {
	// 		return false;
	// 	}
	// }
	// return true;


	// optimized version:

	if (x <= 1)     // if x is negative, 0, or 1 then the number is not prime
		return false;
	if (x == 2)     // the number 2 is the only even prime
		return true;
	if (x % 2 == 0) // any other even number is not prime
		return false;

	// For any number 3 or greater, test odd values (this is why we add 2)
	// between 3 and sqrt(x) to see if they are a divisor
	// Also see https://stackoverflow.com/questions/5811151/why-do-we-check-up-to-the-square-root-of-a-number-to-determine-if-the-number-is
	// Since test >= 0 and x >=0, we can optimize test < std::sqrt(x) to test * text < x
	for (int count{ 3 }; count * count <= x; count += 2)
	{
		if (x % count == 0) // if x is evenly divisible
			return false;  // then this number isn't prime
	}

	return true; // if we didn't find any divisors, then x must be prime
}


// QUESTION #3

/*
Implement a game of Hi-Lo. First, your program should pick a random integer between 1 and 100.
The user is given 7 tries to guess the number.

If the user does not guess the correct number, the program should tell them whether they guessed too high or too low.
If the user guesses the right number, the program should tell them they won. If they run out of guesses, the program
should tell them they lost, and what the correct number is. At the end of the game, the user should be asked if they
want to play again. If the user doesn’t enter ‘y’ or ‘n’, ask them again.

For this quiz, assume the user enters a valid number.

Use the Random.h header from 8.15 -- Global random numbers (Random.h).

Here’s what your output should look like:

Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.
Guess #1: 64
Your guess is too high.
Guess #2: 32
Your guess is too low.
Guess #3: 54
Your guess is too high.
Guess #4: 51
Correct! You win!
Would you like to play again (y/n)? y
Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.
Guess #1: 64
Your guess is too high.
Guess #2: 32
Your guess is too low.
Guess #3: 54
Your guess is too high.
Guess #4: 51
Your guess is too high.
Guess #5: 36
Your guess is too low.
Guess #6: 45
Your guess is too low.
Guess #7: 48
Your guess is too low.
Sorry, you lose. The correct number was 49.
Would you like to play again (y/n)? q
Would you like to play again (y/n)? n
Thank you for playing.


For extra credit: make the minimum and maximum values and the number of guesses a configurable parameter.
*/

int promptForGuess(const int guessNumber) {
	std::cout << "Guess #" << guessNumber << ": ";
	int guess{};
	std::cin >> guess;
	return guess;
}

bool promptForNewGame() {
	// Keep asking the user if they want to play again until they pick y or n.
	char answer{};
	do {
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> answer;
	} while (answer != 'y' && answer != 'n');
	if (answer == 'n') {
		return false;
	}
	return true;

	// Could also use this approach with a switch statement:

	// while (true)
	// {
	// 	char ch{};
	// 	std::cout << "Would you like to play again (y/n)? ";
	// 	std::cin >> ch;
	//
	// 	switch (ch)
	// 	{
	// 		case 'y': return true;
	// 		case 'n': return false;
	// 	}
	// }
}

void playHiLoGame(const int min, const int max, const int numGuesses) {

	bool stillPlaying;
	do {
		int guessesRemaining { numGuesses };

		// Output start game text
		std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max << ". You have " << guessesRemaining << " tries to guess what it is." << '\n';

		// Seed PRNG
		const int answer = Random::get(min, max);

		// Declare currentGuess variable where it can be accessed at the end of a game session to compare with answer
		int currentGuess;

		// Start loop for number of guesses
		while (true) {
			// decrement numGuesses at the start of the loop in this case
			--guessesRemaining;

			// Call helper function to facilitate number input for a single guess (returns int containing the guess)
			currentGuess = promptForGuess(numGuesses - guessesRemaining);

			// Use returned value to decide if guess is correct, print that for player.
			// If the user guesses correctly, end the loop.
			// If incorrect, inform the player if they were too high or too low.
			if (currentGuess < answer) {
				std::cout << "Your guess is too low." << '\n';
			} else if (currentGuess > answer) {
				std::cout << "Your guess is too high." << '\n';
			} else {
				break;
			}

			if (guessesRemaining == 0) {
				break;
			}
		}

		// If player guessed correctly, tell them they win. Otherwise, tell them they lost and what the correct answer was.
		currentGuess == answer ? std::cout << "Correct! You win!" << '\n' : std::cout << "Sorry, you lose. The correct number was " << answer << '\n';

		// Reset game state (in case of a new game, or any other reason we may need to do so)
		guessesRemaining = numGuesses;	// Could later be replaced with another helper function for resetting the entire game state if needed

		// Ask player if they would like to play again, save their answer to the stillPlaying bool
		stillPlaying = promptForNewGame();

	} while (stillPlaying);

	// Print message thanking player for playing the game
	std::cout << "Thank you for playing" << '\n';

}

int main() {
	// QUESTION #1:

	// ORIGINAL:

	// const double towerHeight{getTowerHeight()};
	//
	// calculateAndPrintBallHeight(towerHeight, 0);
	// calculateAndPrintBallHeight(towerHeight, 1);
	// calculateAndPrintBallHeight(towerHeight, 2);
	// calculateAndPrintBallHeight(towerHeight, 3);
	// calculateAndPrintBallHeight(towerHeight, 4);
	// calculateAndPrintBallHeight(towerHeight, 5);

	// ANSWER:
	const double towerHeight{getTowerHeight()};

	int seconds{0};
	while (calculateAndPrintBallHeight(towerHeight, seconds) > 0.0) {
		++seconds;
	}

	std::cout << "\n\n";

	// QUESTION #2:

	assert(!isPrime(0)); // terminate program if isPrime(0) is true
	assert(!isPrime(1));
	assert(isPrime(2)); // terminate program if isPrime(2) is false
	assert(isPrime(3));
	assert(!isPrime(4));
	assert(isPrime(5));
	assert(isPrime(7));
	assert(!isPrime(9));
	assert(isPrime(11));
	assert(isPrime(13));
	assert(!isPrime(15));
	assert(!isPrime(16));
	assert(isPrime(17));
	assert(isPrime(19));
	assert(isPrime(97));
	assert(!isPrime(99));
	assert(isPrime(13417));

	std::cout << "Success!\n";

	/*
	 assert is a preprocessor macro that terminates the program if the associated argument evaluates to false.
	 So when we write assert(!isPrime(0)), we’re meaning “if isPrime(0) is true, then terminate the program”.
	 We cover assert in more detail in lesson 9.6 -- Assert and static_assert.
	 */

	std::cout << "\n\n";

	// QUESTION #3:

	// call Hi-Lo game function with min/max and number of guesses as parameters
	playHiLoGame(1, 100, 7);

	return 0;
}