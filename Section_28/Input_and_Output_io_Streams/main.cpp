/*
Input/output in C++

ios is a typedef for std::basic_ios<char> that defines a bunch of stuff that is common to both input and output
streams. We’ll deal with this stuff in a future lesson.

The istream class is the primary class used when dealing with input streams. With input streams, the extraction
operator (>>) is used to remove values from the stream. This makes sense: when the user presses a key on the keyboard,
the key code is placed in an input stream. Your program then extracts the value from the stream so it can be used.

The ostream class is the primary class used when dealing with output streams. With output streams, the insertion
operator (<<) is used to put values in the stream. This also makes sense: you insert your values into the stream,
and the data consumer (e.g. monitor) uses them.

The iostream class can handle both input and output, allowing bidirectional I/O.

Standard streams in C++

A standard stream is a pre-connected stream provided to a computer program by its environment. C++ comes with four
predefined standard stream objects that have already been set up for your use. The first three, you have seen before:

1. cin -- an istream object tied to the standard input (typically the keyboard)
2. cout -- an ostream object tied to the standard output (typically the monitor)
3. cerr -- an ostream object tied to the standard error (typically the monitor), providing unbuffered output
4. clog -- an ostream object tied to the standard error (typically the monitor), providing buffered output

Unbuffered output is typically handled immediately, whereas buffered output is typically stored and written out as a
block. Because clog isn’t used very often, it is often omitted from the list of standard streams.
 */