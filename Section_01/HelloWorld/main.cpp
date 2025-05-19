#include <iostream> // Preprocessor Directive
#include <limits>

using namespace std;

int main() {
    cout << "Hello, World!"; // << is the insertion operator
    cout << "Hello" " " "World";    // string concatenation

    // The below will cause your program to wait for the user to press enter before continuing (you may have to press
    // enter twice), which will give you time to examine your program’s output before your IDE closes the console window.

    // cin.clear(); // reset any error flags
    // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find a newline
    // cin.get(); // get one more char from the user (waits for user to press enter)

    // https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/

    // This code demonstrates the space on line 19 is working, but CLion currently has a bug placing it on the next line
    std::string prompt = "\nEnter a number: ";
    for (char c : prompt)
        std::cout << '[' << c << "] ";

    std::cout << "\nEnter a number: ";  // ask user for a number

    int x{};       // define variable x to hold user input (and value-initialize it)
    std::cin >> x; // get number from keyboard and store it in variable x

    std::cout << "You entered " << x << '\n';

    std::cout << "Enter two numbers separated by a space: ";

    int z1{}; // define variable x to hold user input (and value-initialize it)
    int z2{}; // define variable y to hold user input (and value-initialize it)
    std::cin >> z1 >> z2; // get two numbers and store in variable x and y respectively

    std::cout << "You entered " << z1 << " and " << z2 << '\n';

    std::cout << "Enter two numbers: ";

    int z3{};
    std::cin >> z3;

    int z4{};
    std::cin >> z4;

    std::cout << "You entered " << z3 << " and " << z4 << '\n';

    // https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/
    /*
    * When std::cin >> x is encountered, the program will wait for input. Enter 4 5. The input 4 5\n goes into the
    * input buffer, but only the 4 is extracted to variable x (extraction stops at the space).
    *
    * When std::cin >> y is encountered, the program will not wait for input. Instead, the 5 that is still in
    * the input buffer is extracted to variable y. The program then prints You entered 4 and 5.
    *
    * Note that in run 2, the program didn't wait for the user to enter additional input when extracting to
    * variable y because there was already prior input in the input buffer that could be used.
     */

    // Prompt user to enter 3 values, then display them:
    int v1{};
    int v2{};
    int v3{};

    std::cout << "Enter three numbers: ";
    std::cin >> v1 >> v2 >> v3;
    std::cout << "You entered: " << v1 << ", " << v2 << ", and " << v3 << "." << '\n';

    return 0;
}
