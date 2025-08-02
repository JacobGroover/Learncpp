/*
Exception handling is best used when all of the following are true:

- The error being handled is likely to occur only infrequently.
- The error is serious and execution could not continue otherwise.
- The error cannot be handled at the place where it occurs.
- There isn’t a good alternative way to return an error code back to the caller.
 */

/*
Cleaning up resources

One of the biggest problems that new programmers run into when using exceptions is the issue of cleaning up
resources when an exception occurs. Consider the following example:

#include <iostream>

try
{
	openFile(filename);
	writeFile(filename, data);
	closeFile(filename);
}
catch (const FileException& exception)
{
	std::cerr << "Failed to write to file: " << exception.what() << '\n';
}


What happens if WriteFile() fails and throws a FileException? At this point, we’ve already opened the file, and
now control flow jumps to the FileException handler, which prints an error and exits. Note that the file was never
closed! This example should be rewritten as follows:

#include <iostream>

try
{
	openFile(filename);
	writeFile(filename, data);
}
catch (const FileException& exception)
{
	std::cerr << "Failed to write to file: " << exception.what() << '\n';
}

// Make sure file is closed
closeFile(filename);


This kind of error often crops up in another form when dealing with dynamically allocated memory:

#include <iostream>

try
{
    auto* john { new Person{ "John", 18, PERSON_MALE } };
    processPerson(john);
    delete john;
}
catch (const PersonException& exception)
{
    std::cerr << "Failed to process person: " << exception.what() << '\n';
}
If processPerson() throws an exception, control flow jumps to the catch handler. As a result, john is never deallocated! This example is a little more tricky than the previous one -- because john is local to the try block, it goes out of scope when the try block exits. That means the exception handler can not access john at all (its been destroyed already), so there’s no way for it to deallocate the memory.

However, there are two relatively easy ways to fix this. First, declare john outside of the try block so it does not go out of scope when the try block exits:

#include <iostream>

Person* john{ nullptr };

try
{
    john = new Person("John", 18, PERSON_MALE);
    processPerson(john);
}
catch (const PersonException& exception)
{
    std::cerr << "Failed to process person: " << exception.what() << '\n';
}

delete john;
Because john is declared outside the try block, it is accessible both within the try block and the catch handlers.
This means the catch handler can do cleanup properly.

The second way is to use a local variable of a class that knows how to cleanup itself when it goes out of scope
(often called a “smart pointer”). The standard library provides a class called std::unique_ptr that can be used for
this purpose. std::unique_ptr is a template class that holds a pointer, and deallocates it when it goes out of scope.

#include <iostream>
#include <memory> // for std::unique_ptr

try
{
    auto* john { new Person("John", 18, PERSON_MALE) };
    std::unique_ptr<Person> upJohn { john }; // upJohn now owns john

    ProcessPerson(john);

    // when upJohn goes out of scope, it will delete john
}
catch (const PersonException& exception)
{
    std::cerr << "Failed to process person: " << exception.what() << '\n';
}

The best option (whenever possible) is to prefer to stack allocate objects that implement RAII
(automatically allocate resources on construction, deallocate resource on destruction). That way when the object
managing the resource goes out of scope for any reason, it will automatically deallocate as appropriate, so we don’t
have to worry about such things!


Exceptions and destructors:

Unlike constructors, where throwing exceptions can be a useful way to indicate that object creation did not succeed,
exceptions should never be thrown in destructors.

The problem occurs when an exception is thrown out of a destructor during the stack unwinding process. If that happens,
the compiler is put in a situation where it doesn’t know whether to continue the stack unwinding process or handle the
new exception. The end result is that your program will be terminated immediately.

Consequently, the best course of action is just to abstain from using exceptions in destructors altogether. Write a
message to a log file instead.
 */