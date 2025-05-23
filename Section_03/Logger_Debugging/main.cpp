/*
* An alternative approach to conditionalized debugging via the preprocessor is to send your debugging information
* to a log. A log is a sequential record of events that have happened, usually time-stamped. The process of generating
* a log is called logging. Typically, logs are written to a file on disk (called a log file) so they can be reviewed
* later. Most applications and operating systems write log files that can be used to help diagnose issues that occur.
*
* Log files have a few advantages. Because the information written to a log file is separated from your program’s
* output, you can avoid the clutter caused by mingling your normal output and debug output. Log files can also be
* easily sent to other people for diagnosis -- so if someone using your software has an issue, you can ask them to
* send you the log file, and it might help give you a clue where the issue is.
*
* C++ contains an output stream named std::clog that is intended to be used for writing logging information.
* However, by default, std::clog writes to the standard error stream (the same as std::cerr). And while you can
* redirect it to file instead, this is one area where you’re generally better off using one of the many existing
* third-party logging tools available. Which one you use is up to you.
*
* For illustrative purposes, we’ll show what outputting to a logger looks like using the
* plog (https://github.com/SergiusTheBest/plog) logger.
* Plog is implemented as a set of header files, so it’s easy to include anywhere you need it, and it’s
* lightweight and easy to use.
*
* How you include, initialize, and use a logger will vary depending on the specific logger you select.
*
* Note that conditional compilation directives are also not required using this method, as most loggers have a
* method to reduce/eliminate writing output to the log. This makes the code a lot easier to read, as the
* conditional compilation lines add a lot of clutter. With plog, logging can be temporarily disabled by changing
* the init statement to the following:
* plog::init(plog::none , "Logfile.txt"); // plog::none eliminates writing of most messages, essentially turning logging off
*
* If you want to compile the above example yourself, or use plog in your own projects, you can follow these
* instructions to install it:
*
* First, get the latest plog release:
* Visit the plog repo. (https://github.com/SergiusTheBest/plog)
* Click the green Code button in the top right corner, and choose “Download zip”
* Next, unzip the entire archive to somewhere on your hard drive.
*
* Finally, for each project, set the somewhere\plog-master\include\ directory as an include directory inside
* your IDE. There are instructions on how to do this for Visual Studio here:
* A.2 -- Using libraries with Visual Studio and
* Code::Blocks here: A.3 -- Using libraries with Code::Blocks.
*
* Since plog doesn’t have a precompiled library file, you can skip the parts related to precompiled library files.
*
* The log file will generally be created in the same directory as your executable.
*
* TIP:
* In larger or performance-sensitive projects, faster and more feature-rich loggers may be
* preferred, such as spdlog (https://github.com/gabime/spdlog).
*/

#include <plog/Log.h> // Step 1: include the logger headers
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>

int getUserInput()
{
	PLOGD << "getUserInput() called"; // PLOGD is defined by the plog library

	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	// As an aside, the following commented line can be used to disable automatic buffering for cout, for debugging purposes
	// std::cout << std::unitbuf;

	plog::init(plog::debug, "Logfile.txt"); // Step 2: initialize the logger

	PLOGD << "main() called"; // Step 3: Output to the log as if you were writing to the console

	int x{ getUserInput() };
	std::cout << "You entered: " << x << '\n';

	return 0;
}