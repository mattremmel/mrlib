# mrlib

Collection of useful header only C++ classes

This is a collection of different header only C++ classes that i've created over time while working on different projects. The reason I chose to make these over using available libraries is to keep dependencies low, and the ease of use high. Each one of these classes can be dropped into a project with no other dependencies besides that standard library. Since they are header only there is no need to add any additional compilation rules.

There are pretty comprehensive unit tests for most of these classes in the 'tests' folder. The tests can be run by using the 'test' target inside the Makefile. i.e 'make test'

- mrlib
  - container
    - Array - This is a full featured generic array that has similar functionality and interface to a Java ArrayList.
    - Dictionary - This is a full featured generic dictionary that has similar functionality and interface to a Java Map.
    - String - This is a full featured generic String container that has similar functionality and interface to a Java String.
  - interface
    - EscapeSequences - This file includes macros and functions that make it easier to work with Posix terminals using ANSI escape codes. Its possible to make simple text base interfaces using this.
  - network
    - Socket - This is an attempt to make it easier to work with the raw socket class in C++. You can work with a socket similar to how you would in Python.
  - util
    - Exception - This is an Exception subclass that is to be used with the StackTrace class in this project to automatically get call trace information upon an exception.
    - Logging - This is a Logging class that has similar functionality and interface to a standard Logging framework.
    - MacroLogging - This is a simple logging class that is implemented entirely using only macros. This allows logging statements to not compile any instructions into the code when disabled.
    - Random - This is a random number generator that uses mersenne twister for generating numbers. It has a similar interface to the random class in Java.
    - StackTrace - This is a class that can be used to generate a pseudo stack trace in C++. Simply add the macro "MARK_STACK" at the beginning of each function, and the call stack can be printed at any point in the code.
    - Stopwatch - This class can be used with a simple 'start, stop, reset' interface to keep track of elapsed times at different granularities.
