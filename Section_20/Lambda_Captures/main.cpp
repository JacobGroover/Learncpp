/*
Lambdas can only access certain kinds of objects that have been defined outside the lambda,
including those with static storage duration (e.g. global variables and static locals) and
constexpr objects.
 */

/*
The capture clause is used to (indirectly) give a lambda access to variables available in the surrounding scope
that it normally would not have access to. All we need to do is list the entities we want to access from within
the lambda as part of the capture clause. In this case, we want to give our lambda access to the value of variable
search, so we add it to the capture clause:
 */
#include <algorithm>
#include <array>
#include <iostream>
#include <string_view>
#include <string>
#include <vector>

int main()
{
 std::array<std::string_view, 4> arr{ "apple", "banana", "walnut", "lemon" };

 std::cout << "search for: ";

 std::string search{};
 std::cin >> search;

 // Capture @search                                                        VVVVVV
 auto found{ std::find_if(arr.begin(), arr.end(), [&search](std::string_view str) {
   return str.find(search) != std::string_view::npos;
 }) };

 if (found == arr.end())
 {
  std::cout << "Not found\n";
 }
 else
 {
  std::cout << "Found " << *found << '\n';
 }

 return 0;
}

/*
The captured variables of a lambda are copies of the outer scope variables, not the actual variables.

Although lambdas look like functions, they’re actually objects that can be called like functions
(these are called functors -- we’ll discuss how to create your own functors from scratch in a future lesson).

When the compiler encounters a lambda definition, it creates a custom object definition for the lambda.
Each captured variable becomes a data member of the object.

At runtime, when the lambda definition is encountered, the lambda object is instantiated, and the members
of the lambda are initialized at that point.

To allow modifications of variables that were captured, we can mark the lambda as mutable after the parameters().

Because captured variables are members of the lambda object, their values are persisted across multiple calls to the lambda!

To capture a variable by reference, we prepend an ampersand (&) to the variable name in the capture.
Unlike variables that are captured by value, variables that are captured by reference are non-const,
unless the variable they’re capturing is const. Capture by reference should be preferred over capture
by value whenever you would normally prefer passing an argument to a function by reference (e.g. for
non-fundamental types).
When doing this, we don't need the mutable keyword anymore in order to modify the variable passed by reference.
 */

/*
Having to explicitly list the variables you want to capture can be burdensome. If you modify your lambda, you may
forget to add or remove captured variables. Fortunately, we can enlist the compiler’s help to auto-generate a list
of variables we need to capture.

A default capture (also called a capture-default) captures all variables that are mentioned in the lambda. Variables
not mentioned in the lambda are not captured if a default capture is used.

To capture all used variables by value, use a capture value of =.
To capture all used variables by reference, use a capture value of &.

Default captures can be mixed with normal captures. We can capture some variables by value and others by reference,
but each variable can only be captured once:
 */
// struct CEnemy {
//
// };
// int main() {
//  int health{ 33 };
//  int armor{ 100 };
//  std::vector<CEnemy> enemies{};
//
//  // Capture health and armor by value, and enemies by reference.
//  [health, armor, &enemies](){};
//
//  // Capture enemies by reference and everything else by value.
//  [=, &enemies](){};
//
//  // Capture armor by value and everything else by reference.
//  [&, armor](){};
//
//  // Illegal, we already said we want to capture everything by reference.
//  [&, &armor](){};
//
//  // Illegal, we already said we want to capture everything by value.
//  [=, armor](){};
//
//  // Illegal, armor appears twice.
//  [armor, &health, &armor](){};
//
//  // Illegal, the default capture has to be the first element in the capture group.
//  [armor, &](){};
// }


/*
Sometimes we want to capture a variable with a slight modification or declare a new variable that is only visible
in the scope of the lambda. We can do so by defining a variable in the lambda-capture without specifying its type.
 */
#include <array>
#include <iostream>
#include <algorithm>

// int main()
// {
//  std::array areas{ 100, 25, 121, 40, 56 };
//
//  int width{};
//  int height{};
//
//  std::cout << "Enter width and height: ";
//  std::cin >> width >> height;
//
//  // We store areas, but the user entered width and height.
//  // We need to calculate the area before we can search for it.
//  auto found{ std::find_if(areas.begin(), areas.end(),
//                           // Declare a new variable that's visible only to the lambda.
//                           // The type of userArea is automatically deduced to int.
//                           [userArea{ width * height }](int knownArea) {
//                             return userArea == knownArea;
//                           }) };
//
//  if (found == areas.end())
//  {
//   std::cout << "I don't know this area :(\n";
//  }
//  else
//  {
//   std::cout << "Area found :)\n";
//  }
//
//  return 0;
// }

/*
userArea will only be calculated once when the lambda is defined. The calculated area is stored in the lambda object
and is the same for every call. If a lambda is mutable and modifies a variable that was defined in the capture, the
original value will be overridden.

Only initialize variables in the capture if their value is short and their type is obvious.
Otherwise it’s best to define the variable outside of the lambda and capture it.
 */

/*
Variables are captured at the point where the lambda is defined. If a variable captured by reference dies
before the lambda, the lambda will be left holding a dangling reference.

For example:
 */

// #include <iostream>
// #include <string>
//
// // returns a lambda
// auto makeWalrus(const std::string& name)
// {
//  // Capture name by reference and return the lambda.
//  return [&]() {
//   std::cout << "I am a walrus, my name is " << name << '\n'; // Undefined behavior
//  };
// }
//
// int main()
// {
//  // Create a new walrus whose name is Roofus.
//  // sayName is the lambda returned by makeWalrus.
//  auto sayName{ makeWalrus("Roofus") };
//
//  // Call the lambda function that makeWalrus returned.
//  sayName();
//
//  return 0;
// }

/*
The call to makeWalrus() creates a temporary std::string from the string literal "Roofus". The lambda in makeWalrus()
captures the temporary string by reference. The temporary string dies at the end of the full expression containing the
call to makeWalrus(), but the lambda sayName still references it past that point. Thus, when we call sayName, the
dangling reference is accessed, causing undefined behavior.

Note that this also happens if "Roofus" is passed to makeWalrus() by value. Parameter name dies at the end of
makeWalrus(), and the lambda is left holding a dangling reference.
 */

/*
 NOTE: Standard library functions may copy function objects (reminder: lambdas are function objects). If you want to
 provide lambdas with mutable captured variables, pass them by reference using std::ref (which creates a std::reference_wrapper).

Try to avoid mutable lambdas. Non-mutable lambdas are easier to understand and don’t suffer from the above issues,
as well as more dangerous issues that arise when you add parallel execution.
 */