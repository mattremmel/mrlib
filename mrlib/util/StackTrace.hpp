//
// StackTrace.hpp
// mrlib
//
// Created by Matthew Remmel on 1/22/16.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.

/*
 * The purpose of this class is to create a simple framework for generating something
 * akin to a stacktrace. Unfortunately this requires adding the 'MARK_STACK' macro at
 * the top of each function. This works by pushing the function information onto a stack
 * and removing when the function exits. At anytime, if an exception occurs, the stacktrace
 * can be printed out so that you can see the call stack. Using the Exception.hpp class will
 * automate this.
 */


#ifndef MRLIB_STACKTRACE_HPP
#define MRLIB_STACKTRACE_HPP

#include "LConstants.h"
#include <signal.h>
#include <iostream>

#define MARK_STACK StackMarker sm(__FILENAME__, __FUNC_NAME__, __LINE__);

// TODO: Capture cpu signals and print stacktrace

namespace mrlib {

    class StackMarker {
    public:
        // Internal Data
        std::string _filename;
        std::string _functionName;
        int _lineNumber;

        // Constructors
        StackMarker(const std::string& filename, const std::string& function_name, int line_number);

        // Destructors
        ~StackMarker();

        // Getters
        std::string getFileName() const;
        int getLineNumber() const;

        // String Representation
        std::string description() const;
        std::string inspect() const;
    };


    class StackTrace {
    public:
        // Internal Data
        static std::vector<StackMarker> _callStack;

        // Init StackTrace
        static void init();

        // Abort Handler
        static void abortHandler(int signum);

        // Adding StackMarker
        static void push(StackMarker marker);

        // Removing StackMarker
        static void pop();

        // Getters
        static std::vector<StackMarker> getCallStack();
        static int size();

        // String Representation
        static std::string description();
        static std::string inspect();
    };


    /////////////////////////////
    // TEMPLATE IMPLEMENTATION //
    /////////////////////////////

    // StackMarker //

    // Constructors
    StackMarker::StackMarker(const std::string& filename, const std::string& function_name, int line_number) {
        this->_filename = filename;
        this->_functionName = filename;
        this->_lineNumber = line_number;
        StackTrace::push(*this);
    }

    // Destructors
    StackMarker::~StackMarker() {
        StackTrace::pop();
    }

    // Getters
    std::string StackMarker::getFileName() const {
        return this->_filename;
    }

    int StackMarker::getLineNumber() const {
        return this->_lineNumber;
    }

    // String Representation
    std::string StackMarker::description() const {
        return this->_filename + ":" + std::to_string(this->_lineNumber) + " " + this->_functionName;
    }

    std::string StackMarker::inspect() const {
        return "filename: " + this->_filename + "\nfunction name: " + this->_functionName +  "\nline number: " + std::to_string(this->_lineNumber);
    }

    // StackTrace //

    // Init StackTrace
    void StackTrace::init() {
        signal(SIGABRT, StackTrace::abortHandler);
    }

    // Abort Handler
    void StackTrace::abortHandler(int signum) {
        // Signal Name
        std::string name = "";
        switch (signum) {
            case SIGABRT:
                name = "SIGABRT";
                break;

            default:
                name = "Unregistered Signal";
                break;
        }

        fprintf(stderr, "Caught signal %d (%s)\n", signum, name.c_str());
        fprintf(stderr, "Cought signal %d\n", signum);

        // Print Stack Trace
        fprintf(stderr, StackTrace::description().c_str());

        exit(signum);
    }

    // Adding StackMarker
    void StackTrace::push(StackMarker marker) {
        StackTrace::_callStack.push_back(marker);
    }

    // Removing StackMarker
    void StackTrace::pop() {
        StackTrace::_callStack.pop_back();
    }

    // Getters
    std::vector<StackMarker> StackTrace::getCallStack() {
        return StackTrace::_callStack;
    }

    int StackTrace::size() {
        return StackTrace::_callStack.size();
    }

    // String Representation
    std::string StackTrace::description() {
        if (StackTrace::_callStack.size() > 0) {
            std::string header = "StackTrace:\n";
            std::string output = "";

            for (const StackMarker& sm : StackTrace::_callStack) {
                output = "\t" + sm.description() + "\n" + output;
            }

            return header + output;
        }
        else {
            return "StackTrace:\n\t-No Stack Trace Information-";
        }
    }

    std::string StackTrace::inspect() {
        return "stack size: " + std::to_string(StackTrace::_callStack.size()) + "\n" + StackTrace::description();
    }
}

#endif // MRLIB_STACKTRACE_HPP