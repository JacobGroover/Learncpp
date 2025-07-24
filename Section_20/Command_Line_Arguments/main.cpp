/*
 Passing command line arguments

Executable programs can be run on the command line by invoking them by name. For example, to run the executable file
“WordCount” that is located in the current directory of a Windows machine, you could type:

WordCount
The equivalent command line on a Unix-based OS would be:

./WordCount
In order to pass command line arguments to WordCount, we simply list the command line arguments after the
executable name:

WordCount Myfile.txt
Now when WordCount is executed, Myfile.txt will be provided as a command line argument. A program can have multiple
command line arguments, separated by spaces:

WordCount Myfile.txt Myotherfile.txt
If you are running your program from an IDE, the IDE should provide a way to enter command line arguments.

In Microsoft Visual Studio, right click on your project in the solution explorer, then choose properties. Open the
“Configuration Properties” tree element, and choose “Debugging”. In the right pane, there is a line called
“Command Arguments”. You can enter your command line arguments there for testing, and they will be automatically
passed to your program when you run it.

In Code::Blocks, choose “Project -> Set program’s arguments”.

Using command line arguments

Now that you know how to provide command line arguments to a program, the next step is to access them from within
our C++ program. To do that, we use a different form of main() than we’ve seen before. This new form of main()
takes two arguments (named argc and argv by convention) as follows:

int main(int argc, char* argv[])
You will sometimes also see it written as:

int main(int argc, char** argv)
Even though these are treated identically, we prefer the first representation because it’s intuitively easier
to understand.

argc is an integer parameter containing a count of the number of arguments passed to the program
(think: argc = argument count). argc will always be at least 1, because the first argument is always the name of
the program itself. Each command line argument the user provides will cause argc to increase by 1.

argv is where the actual argument values are stored (think: argv = argument values, though the proper name is
“argument vectors”). Although the declaration of argv looks intimidating, argv is really just a C-style array
of char pointers (each of which points to a C-style string). The length of this array is argc.

Let’s write a short program named “MyArgs” to print the value of all the command line parameters:
 */

// #include <iostream>
//
// int main(int argc, char* argv[])
// {
//  std::cout << "There are " << argc << " arguments:\n";
//
//  // Loop through each argument and print its number and value
//  for (int count{ 0 }; count < argc; ++count)
//  {
//   std::cout << count << ' ' << argv[count] << '\n';
//  }
//
//  return 0;
// }

/*
Dealing with numeric arguments

Command line arguments are always passed as strings, even if the value provided is numeric in nature.
To use a command line argument as a number, you must convert it from a string to a number.
Unfortunately, C++ makes this a little more difficult than it should be.
 */

#include <iostream>
#include <sstream> // for std::stringstream
#include <string>

int main(int argc, char* argv[])
{
 if (argc <= 1)
 {
  // On some operating systems, argv[0] can end up as an empty string instead of the program's name.
  // We'll conditionalize our response on whether argv[0] is empty or not.
  if (argv[0])
   std::cout << "Usage: " << argv[0] << " <number>" << '\n';
  else
   std::cout << "Usage: <program name> <number>" << '\n';

  return 1;
 }

 std::stringstream convert{ argv[1] }; // set up a stringstream variable named convert, initialized with the input from argv[1]

 int myint{};
 if (!(convert >> myint)) // do the conversion
  myint = 0; // if conversion fails, set myint to a default value

 std::cout << "Got integer: " << myint << '\n';

 return 0;
}

/*
std::stringstream works much like std::cin. In this case, we’re initializing it with the value of argv[1],
so that we can use operator>> to extract the value to an integer variable (the same as we would with std::cin).
 */

/*
Generally, operating systems have special rules about how special characters like double quotes and backslashes are handled.

For example:

MyArgs Hello world!
prints:

There are 3 arguments:
0 C:\MyArgs
1 Hello
2 world!
Typically, strings passed in double quotes are considered to be part of the same string:

MyArgs "Hello world!"
prints:

There are 2 arguments:
0 C:\MyArgs
1 Hello world!
Most operating systems will allow you to include a literal double quote by backslashing the double quote:

MyArgs \"Hello world!\"
prints:

There are 3 arguments:
0 C:\MyArgs
1 "Hello
2 world!"
Other characters may also require backslashing or escaping depending on how your OS interprets them.

Conclusion

Command line arguments provide a great way for users or other programs to pass input data into a program at startup.
Consider making any input data that a program requires at startup to operate a command line parameter. If the command
line isn’t passed in, you can always detect that and ask the user for input. That way, your program can operate
either way.
 */