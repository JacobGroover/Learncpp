#include <iostream>

int main() {
	std::cout << "Enter your full name: " << "\n";
	std::string name{};
	std::getline(std::cin >> std::ws, name);

	std::cout << "Enter your age: " << "\n";
	int age{};
	std::cin >> age;

	// age is signed, and name.length() is unsigned. The two shouldn't be mixed so convert name.length() to a signed value
	int nameLength {static_cast<int>(name.length())}; // get number of chars in name (including spaces)
	std::cout << "Your age + the length of your name is: " << age + nameLength << "\n";

	return 0;
}