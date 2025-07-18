#include <iostream>
#include <algorithm> // for std::transform
#include <cctype>    // for std::tolower
#include <iterator>  // for std::back_inserter
#include <string>
#include <string_view>

#include <optional> // for std::optional

// This function returns a std::string that is the lower-case version of the std::string_view passed in.
// Only 1:1 character mapping can be performed by this function
std::string toASCIILowerCase(std::string_view sv)
{
	std::string lower{};
	std::transform(sv.begin(), sv.end(), std::back_inserter(lower),
		[](char c)
		{
			return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
		});
	return lower;
}

enum Pet
{
	cat,   // 0
	dog,   // 1
	pig,   // 2
	whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
	switch (pet)
	{
		case cat:   return "cat";
		case dog:   return "dog";
		case pig:   return "pig";
		case whale: return "whale";
		default:    return "???";
	}
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
	// We can only switch on an integral value (or enum), not a string
	// so we have to use if-statements here
	if (sv == "cat")   return cat;
	if (sv == "dog")   return dog;
	if (sv == "pig")   return pig;
	if (sv == "whale") return whale;

	return {};
}

int main()
{
	std::cout << "Enter a pet: cat, dog, pig, or whale: ";
	std::string s{};
	std::cin >> s;
	s = toASCIILowerCase(s);

	std::optional<Pet> pet { getPetFromString(s) };

	if (!pet)
		std::cout << "You entered an invalid pet\n";
	else
		std::cout << "You entered: " << getPetName(*pet) << '\n';

	return 0;
}