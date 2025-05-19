/*
* Creates a program that asks the user to enter an integer, waits for them to input an integer, then tells them what
 * 2 times that number is.
 */

#include <iostream>

using namespace std;
int main() {

	cout << "Enter an integer: ";
	int num{};
	cin >> num;
	cout << "Double that number is: " << num * 2 << '\n';
	cout << "Triple that number is: " << num * 3 << '\n';

	cout << "\nEnter a new number: ";
	int num2{};
	cin >> num2;
	cout << "Enter another number: ";
	int num3{};
	cin >> num3;

	cout << num2 << " + " << num3 << " = " << num2 + num3 << '\n';
	cout << num2 << " - " << num3 << " = " << num2 - num3 << '\n';

	return 0;
}