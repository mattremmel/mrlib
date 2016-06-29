//
// Stopwatch.hpp
// mrlib
//
// Created by Matthew Remmel on 11/15/15.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.

/*
 * The purpose of the class is to provide an easy interface for working with timestamps
 * in the form of a stopwatch. Controlling the stopwatch uses the normal start, stop,
 * and reset interface, and the elapsed time can be retrieved in either seconds,
 * milliseconds, microseconds, or nanoseconds.
 */


#ifndef MRLIB_STOPWATCH_HPP
#define MRLIB_STOPWATCH_HPP

#include <chrono>

namespace mrlib {

    class Stopwatch {
    public:

        // Internal Data
        std::chrono::time_point<std::chrono::steady_clock> _begin;
        std::chrono::time_point<std::chrono::steady_clock> _end;
        bool _running;

        // Constructors
        Stopwatch();

        // Timing Control
        std::chrono::time_point<std::chrono::steady_clock> start();
        std::chrono::time_point<std::chrono::steady_clock> stop();
        std::chrono::time_point<std::chrono::steady_clock> reset();
        bool isRunning();

        // Getting Elapsed Time
        size_t elapsedNanoseconds();
        size_t elapsedMicroseconds();
        size_t elapsedMilliseconds();
        size_t elapsedSeconds();
    };


    ///////////////////////////
    // HEADER IMPLEMENTATION //
    ///////////////////////////

    // Constructors
    inline
    Stopwatch::Stopwatch() {
        std::chrono::time_point<std::chrono::steady_clock> initial = std::chrono::steady_clock::now();
        this->_begin = initial;
        this->_end = initial;
        this->_running = false;
    }


    // Timing Control
    inline
    std::chrono::time_point<std::chrono::steady_clock> Stopwatch::start() {
        this->_begin = std::chrono::steady_clock::now();
        this->_running = true;
        return this->_begin;
    }

    inline
    std::chrono::time_point<std::chrono::steady_clock> Stopwatch::stop() {
        this->_end = std::chrono::steady_clock::now();
        this->_running = false;
        return this->_end;
    }

    inline
    std::chrono::time_point<std::chrono::steady_clock> Stopwatch::reset() {
        std::chrono::time_point<std::chrono::steady_clock> initial = std::chrono::steady_clock::now();
        this->_begin = initial;
        this->_end = initial;
        return this->_end;
    }

    inline
    bool Stopwatch::isRunning() {
        return this->_running;
    }


    // Getting Elapsed Time
    inline
    size_t Stopwatch::elapsedNanoseconds() {
        if (this->_running) {
            std::chrono::time_point<std::chrono::steady_clock> current = std::chrono::steady_clock::now();
            return (size_t)std::chrono::duration_cast<std::chrono::nanoseconds>(current - this->_begin).count();
        }
        else {
            return (size_t)std::chrono::duration_cast<std::chrono::nanoseconds>(this->_end - this->_begin).count();
        }
    }

    inline
    size_t Stopwatch::elapsedMicroseconds() {
        if (this->_running) {
            std::chrono::time_point<std::chrono::steady_clock> current = std::chrono::steady_clock::now();
            return (size_t)std::chrono::duration_cast<std::chrono::microseconds>(current - this->_begin).count();
        }
        else {
            return (size_t)std::chrono::duration_cast<std::chrono::microseconds>(this->_end - this->_begin).count();
        }
    }

    inline
    size_t Stopwatch::elapsedMilliseconds() {
        if (this->_running) {
            std::chrono::time_point<std::chrono::steady_clock> current = std::chrono::steady_clock::now();
            return (size_t)std::chrono::duration_cast<std::chrono::milliseconds>(current - this->_begin).count();
        }
        else {
            return (size_t)std::chrono::duration_cast<std::chrono::milliseconds>(this->_end - this->_begin).count();
        }
    }

    inline
    size_t Stopwatch::elapsedSeconds() {
        if (this->_running) {
            std::chrono::time_point<std::chrono::steady_clock> current = std::chrono::steady_clock::now();
            return (size_t)std::chrono::duration_cast<std::chrono::seconds>(current - this->_begin).count();
        }
        else {
            return (size_t)std::chrono::duration_cast<std::chrono::seconds>(this->_end - this->_begin).count();
        }
    }
}

#endif //MRLIB_STOPWATCH_HPP
