/*
Extraction and whitespace

As a reminder, the extraction operator skips whitespace (blanks, tabs, and newlines).

Take a look at the following program:
 */

// #include <iostream>
//
// int main()
// {
// 	char ch{};
// 	while (std::cin >> ch)
// 		std::cout << ch;
//
// 	return 0;
// }

/*
When the user inputs the following:

Hello my name is Alex
The extraction operator skips the spaces and the newline. Consequently, the output is:

HellomynameisAlex


Oftentimes, you’ll want to get user input but not discard whitespace. To do this, the istream class provides many
functions that can be used for this purpose.

One of the most useful is the get() function, which simply gets a character from the input stream. Here’s the same
program as above using get():
 */

// int main()
// {
// 	char ch{};
// 	while (std::cin.get(ch))
// 		std::cout << ch;
//
// 	return 0;
// }

/*
get() also has a string version that takes a maximum number of characters to read:
 */

// int main()
// {
//  char strBuf[11]{};
//  std::cin.get(strBuf, 11);
//  std::cout << strBuf << '\n';
//
//  return 0;
// }

/*
Note that we only read the first 10 characters (we had to leave one character for a terminator).
The remaining characters were left in the input stream.

One important thing to note about get() is that it does not read in a newline character! This can cause some unexpected results:
 */

// int main()
// {
//  char strBuf[11]{};
//  // Read up to 10 characters
//  std::cin.get(strBuf, 11);
//  std::cout << strBuf << '\n';
//
//  // Read up to 10 more characters
//  std::cin.get(strBuf, 11);
//  std::cout << strBuf << '\n';
//  return 0;
// }

/*
The second get() saw there was still input in the cin stream and tried to read it. But the first character was the
newline, so it stopped immediately.

Consequently, there is another function called getline() that works similarly to get(), but will extract (and
discard) the delimiter.
 */

// int main()
// {
//  char strBuf[11]{};
//  // Read up to 10 characters
//  std::cin.getline(strBuf, 11);
//  std::cout << strBuf << '\n';
//
//  // Read up to 10 more characters
//  std::cin.getline(strBuf, 11);
//  std::cout << strBuf << '\n';
//  return 0;
// }

/*
If you need to know how many character were extracted by the last call of getline(), use gcount()

gcount() includes any extracted and discarded delimiters:
 */

// int main()
// {
//  char strBuf[100]{};
//  std::cin.getline(strBuf, 100);
//  std::cout << strBuf << '\n';
//  std::cout << std::cin.gcount() << " characters were read" << '\n';
//
//  return 0;
// }

/*
There is a special version of getline() that lives outside the istream class that is used for reading in variables of
type std::string. This special version is not a member of either ostream or istream, and is included in the string
header. Here is an example of its use:
 */

#include <string>
#include <iostream>

int main()
{
 std::string strBuf{};
 std::getline(std::cin, strBuf);
 std::cout << strBuf << '\n';

 return 0;
}

/*
There are a few more useful input functions that you might want to make use of:

ignore() discards the first character in the stream.
ignore(int nCount) discards the first nCount characters.
peek() allows you to read a character from the stream without removing it from the stream.
unget() returns the last character read back into the stream so it can be read again by the next call.
putback(char ch) allows you to put a character of your choice back into the stream to be read by the next call.

istream contains many other functions and variants of the above mentioned functions that may be useful, depending on
what you need to do. You can find these on a reference site such as https://en.cppreference.com/w/cpp/io/basic_istream.
 */