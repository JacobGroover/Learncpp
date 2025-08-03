/*
The file pointer

Each file stream class contains a file pointer that is used to keep track of the current read/write position within
the file. When something is read from or written to a file, the reading/writing happens at the file pointer’s current location. By default, when opening a file for reading or writing, the file pointer is set to the beginning of the file. However, if a file is opened in append mode, the file pointer is moved to the end of the file, so that writing does not overwrite any of the current contents of the file.

Random file access with seekg() and seekp()

So far, all of the file access we’ve done has been sequential -- that is, we’ve read or written the file contents
in order. However, it is also possible to do random file access -- that is, skip around to various points in the file
to read its contents. This can be useful when your file is full of records, and you wish to retrieve a specific record.
Rather than reading all of the records until you get to the one you want, you can skip directly to the record you wish to retrieve.

Random file access is done by manipulating the file pointer using either seekg() function (for input) and seekp()
function (for output). In case you are wondering, the g stands for “get” and the p for “put”. For some types of
streams, seekg() (changing the read position) and seekp() (changing the write position) operate
independently -- however, with file streams, the read and write position are always identical, so seekg and seekp
can be used interchangeably.

The seekg() and seekp() functions take two parameters. The first parameter is an offset that determines how many
bytes to move the file pointer. The second parameter is an ios flag that specifies what the offset parameter
should be offset from.

Ios seek flag		Meaning
beg					The offset is relative to the beginning of the file (default)
cur					The offset is relative to the current location of the file pointer
end					The offset is relative to the end of the file

A positive offset means move the file pointer towards the end of the file, whereas a negative offset means move the
file pointer towards the beginning of the file.

inf.seekg(14, std::ios::cur); // move forward 14 bytes
inf.seekg(-18, std::ios::cur); // move backwards 18 bytes
inf.seekg(22, std::ios::beg); // move to 22nd byte in file
inf.seekg(24); // move to 24th byte in file
inf.seekg(-28, std::ios::end); // move to the 28th byte before end of the file

Moving to the beginning or end of the file is easy:

inf.seekg(0, std::ios::beg); // move to beginning of file
inf.seekg(0, std::ios::end); // move to end of file


WARNING:

In a text file, seeking to a position other than the beginning of the file may result in unexpected behavior.

In programming, a newline (‘\n’) is actually an abstraction.

On Windows, a newline is represented as sequential CR (carriage return) and LF (line feed) characters (thus taking
2 bytes of storage).
On Unix, a newline is represented as a LF (line feed) character (thus taking 1 byte of storage).
Seeking past a newline in either direction takes a variable number of bytes depending on how the file was encoded,
which means results will vary depending on which encoding is used.

Also on some operating systems, files may be padded with trailing zero bytes (bytes that have value 0). Seeking to
the end of the file (or an offset from the end of the file) will produce different results on such files.
 */

/*
Just to give you an idea of how they work, let’s do an example using seekg() and the input file we created in the
last lesson. That input file looks like this:

This is line 1
This is line 2
This is line 3
This is line 4
Here is the example:
 */

// #include <fstream>
// #include <iostream>
// #include <string>
//
// int main()
// {
//  // re-making Sample.txt from last lesson
//  std::ofstream outf{ "Sample.txt" };
//  if (!outf)
//  {
//   // Print an error and exit
//   std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
//   return 1;
//  }
//
//  outf << "This is line 1\n" << "This is line 2\n" << "This is line 3\n" << "This is line 4\n";
//  outf.close();
//
//  // This new example starts here
//  std::ifstream inf{ "Sample.txt" };
//
//  // If we couldn't open the input file stream for reading
//  if (!inf)
//  {
//   // Print an error and exit
//   std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
//   return 1;
//  }
//
//  std::string strData;
//
//  inf.seekg(5); // move to 5th character
//  // Get the rest of the line and print it, moving to line 2
//  std::getline(inf, strData);
//  std::cout << strData << '\n';
//
//  inf.seekg(8, std::ios::cur); // move 8 more bytes into file
//  // Get rest of the line and print it
//  std::getline(inf, strData);
//  std::cout << strData << '\n';
//
//  inf.seekg(-14, std::ios::end); // move 14 bytes before end of file
//  // Get rest of the line and print it
//  std::getline(inf, strData); // undefined behavior
//  std::cout << strData << '\n';
//
//  inf.close();
//
//  // seekg() and seekp() are better used on binary files. You can open the above file in binary mode via:
//  std::ifstream inf2 {"Sample.txt", std::ifstream::binary};
//  inf2.close();
//
//  // Two other useful functions are tellg() and tellp(), which return the absolute position of the file pointer.
//  // This can be used to determine the size of a file:
//  std::ifstream inf3 {"Sample.txt"};
//  inf3.seekg(0, std::ios::end); // move to end of file
//  std::cout << inf3.tellg();
//
//  return 0;
// }

/*
 ===========================================================================================================

 READING AND WRITING A FILE AT THE SAME TIME USING FSTREAM

The fstream class is capable of both reading and writing a file at the same time -- almost! The big caveat here is
that it is not possible to switch between reading and writing arbitrarily. Once a read or write has taken place, the
only way to switch between the two is to perform an operation that modifies the file position (e.g. a seek). If you
don’t actually want to move the file pointer (because it’s already in the spot you want), you can always seek to the
current position:

// assume iofile is an object of type fstream
iofile.seekg(iofile.tellg(), std::ios::beg); // seek to current file position

If you do not do this, any number of strange and bizarre things may occur.

(Note: Although it may seem that iofile.seekg(0, std::ios::cur) would also work, it appears some compilers may
optimize this away).

One other bit of trickiness: Unlike ifstream, where we could say while (inf) to determine if there was more to read,
this will not work with fstream.

Let’s do a file I/O example using fstream. We’re going to write a program that opens a file, reads its contents,
and changes any vowels it finds to a ‘#’ symbol.
 */

// #include <fstream>
// #include <iostream>
// #include <string>
//
// int main()
// {
//  // re-making Sample.txt from last lesson
//  std::ofstream outf{ "Sample.txt" };
//  if (!outf)
//  {
//   // Print an error and exit
//   std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
//   return 1;
//  }
//
//  outf << "This is line 1\n" << "This is line 2\n" << "This is line 3\n" << "This is line 4\n";
//  outf.close();
//
//  // NEW EXAMPLE STARTS HERE:
//
//  // Note we have to specify both in and out because we're using fstream
//  std::fstream iofile{ "Sample.txt", std::ios::in | std::ios::out };
//
//  // If we couldn't open iofile, print an error
//  if (!iofile)
//  {
//   // Print an error and exit
//   std::cerr << "Uh oh, Sample.txt could not be opened!\n";
//   return 1;
//  }
//
//  char chChar{}; // we're going to do this character by character
//
//  // While there's still data to process
//  while (iofile.get(chChar))
//  {
//   switch (chChar)
//   {
//    // If we find a vowel
//    case 'a':
//    case 'e':
//    case 'i':
//    case 'o':
//    case 'u':
//    case 'A':
//    case 'E':
//    case 'I':
//    case 'O':
//    case 'U':
//
//     // Back up one character
//     iofile.seekg(-1, std::ios::cur);
//     // iofile.seekp(-1, std::ios::cur);
//
//     // Because we did a seek, we can now safely do a write, so
//     // let's write a # over the vowel
//     iofile << '#';
//
//     // Now we want to go back to read mode so the next call
//     // to get() will perform correctly.  We'll seekg() to the current
//     // location because we don't want to move the file pointer.
//     iofile.seekg(iofile.tellg(), std::ios::beg);
//     // iofile.seekp(iofile.tellp(), std::ios::beg);
//
//     break;
//   }
//  }
//
//  return 0;
// }

/*
 NOTE: The above is an extremely fragile methodology that can have unexpected results for a variety of reasons, from
 CRLF vs. LF on Windows vs. Unix, variable-width encoding, etc.

 Not sure why the tutorial recommended this approach... Below is a much better solution:
 */

// #include <fstream>
// #include <iostream>
// #include <string>
// #include <cstdio> // for remove and rename
//
// bool isVowel(char c)
// {
//  switch (c)
//  {
//   case 'a': case 'e': case 'i': case 'o': case 'u':
//   case 'A': case 'E': case 'I': case 'O': case 'U':
//    return true;
//   default:
//    return false;
//  }
// }
//
// int main()
// {
//  // re-making Sample.txt from last lesson
//  std::ofstream outf{ "Sample.txt" };
//  if (!outf)
//  {
//   // Print an error and exit
//   std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
//   return 1;
//  }
//
//  outf << "This is line 1\n" << "This is line 2\n" << "This is line 3\n" << "This is line 4\n";
//  outf.close();
//
//  // NEW EXAMPLE STARTS HERE:
//
//  std::ifstream inFile("Sample.txt"); // read mode
//  std::ofstream outFile("Sample_temp.txt"); // temp output
//
//  if (!inFile || !outFile)
//  {
//   std::cerr << "Error opening file.\n";
//   return 1;
//  }
//
//  char ch;
//  while (inFile.get(ch))
//  {
//   if (isVowel(ch))
//    outFile.put('#');
//   else
//    outFile.put(ch);
//  }
//
//  inFile.close();
//  outFile.close();
//
//  // Optional: Replace original file with the modified one
//  if (std::remove("Sample.txt") != 0)
//  {
//   std::cerr << "Failed to delete original file.\n";
//   return 1;
//  }
//
//  if (std::rename("Sample_temp.txt", "Sample.txt") != 0)
//  {
//   std::cerr << "Failed to rename temporary file.\n";
//   return 1;
//  }
//
//  std::cout << "Vowels replaced successfully.\n";
//  return 0;
// }

/*
 Below is a solution using std::filesystem (C++ 17+):
 */

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

bool isVowel(char c)
{
 switch (c)
 {
  case 'a': case 'e': case 'i': case 'o': case 'u':
  case 'A': case 'E': case 'I': case 'O': case 'U':
   return true;
  default:
   return false;
 }
}

int main()
{
 // re-making Sample.txt from last lesson
 std::ofstream outf{ "Sample.txt" };
 if (!outf)
 {
  // Print an error and exit
  std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
  return 1;
 }

 outf << "This is line 1\n" << "This is line 2\n" << "This is line 3\n" << "This is line 4\n";
 outf.close();

 // NEW EXAMPLE STARTS HERE:

 fs::path originalPath = "Sample.txt";
 fs::path tempPath = originalPath;
 tempPath += ".tmp"; // "Sample.txt.tmp"

 // Open original file for reading
 std::ifstream inFile(originalPath);
 if (!inFile)
 {
  std::cerr << "Failed to open " << originalPath << " for reading.\n";
  return 1;
 }

 // Open temp file for writing
 std::ofstream outFile(tempPath);
 if (!outFile)
 {
  std::cerr << "Failed to open " << tempPath << " for writing.\n";
  return 1;
 }

 char ch;
 while (inFile.get(ch))
 {
  outFile.put(isVowel(ch) ? '#' : ch);
 }

 inFile.close();
 outFile.close();

 // Optional: back up the original file
 fs::path backupPath = originalPath;
 backupPath += ".bak";
 if (fs::exists(backupPath))
 {
  fs::remove(backupPath); // overwrite if already exists
 }
 fs::rename(originalPath, backupPath); // move original to .bak

 // Replace original file with the modified one
 fs::rename(tempPath, originalPath);

 std::cout << "File processed and saved. Backup created: " << backupPath << "\n";
 return 0;
}

/*
 ===================================================================================================

Other useful file functions

To delete a file, simply use the remove() function.

Also, the is_open() function will return true if the stream is currently open, and false otherwise.

Warning

Do not write memory addresses to files. The variables that were originally at those addresses may be at different
addresses when you read their values back in from disk, and the addresses will be invalid.
 */