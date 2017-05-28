//
// Stopwatch_Test.cpp
// mrlib
//
// Created by Matthew Remmel on 11/16/15.
// Copyright (c) 2017 Matthew Remmel. All rights reserved.

#include "Stopwatch.hpp"
#include "gtest.h"
#include <thread> // TODO: Replace with custom blocking wait function

using namespace mrlib;

#define EXPECT_BETWEEN(actual, lower, upper) EXPECT_GE(actual, lower); EXPECT_LE(actual, upper);


//////////////////
// Constructors //
//////////////////

TEST(Stopwatch, default_constructor) {
    // Setup
    Stopwatch watch = Stopwatch();

    // Assertion
    EXPECT_FALSE(watch._running);
    EXPECT_EQ(watch._begin, watch._end);
}


////////////////////
// Timing Control //
////////////////////

// Start

TEST(Stopwatch, start_control) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();

    // Assertion
    EXPECT_TRUE(watch._running);
    EXPECT_GT(watch._begin, watch._end);
}

// Stop

TEST(Stopwatch, stop_control) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    watch.stop();

    // Assertion
    EXPECT_FALSE(watch._running);
    EXPECT_GE(watch._end, watch._begin);
}

// Reset

TEST(Stopwatch, reset_control_running) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::microseconds(1));
    watch.reset();

    // Assertion
    EXPECT_TRUE(watch._running);
    EXPECT_EQ(watch._begin, watch._end);
}

TEST(Stopwatch, reset_control_stopped) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.reset();

    // Assertion
    EXPECT_FALSE(watch._running);
    EXPECT_EQ(watch._begin, watch._end);
}

// IsRunning

TEST(Stopwatch, is_running_true) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch._running = true;

    // Assertion
    EXPECT_TRUE(watch.isRunning());
}

TEST(Stopwatch, is_running_false) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch._running = false;

    // Assertion
    EXPECT_FALSE(watch.isRunning());
}


//////////////////////////
// Getting Elapsed Time //
//////////////////////////

// ElapsedTimeNanoseconds

TEST(Stopwatch, elapsed_time_nanoseconds_zero) {
    // Setup
    Stopwatch watch = Stopwatch();

    // Assertion
    EXPECT_EQ(0, watch.elapsedNanoseconds());
}

TEST(Stopwatch, elapsed_time_nanoseconds_stopped) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    watch.stop();
    size_t time = watch.elapsedNanoseconds();

    // Assertion
    EXPECT_BETWEEN(time, 1000, 50000); // TODO: Could fail if OS waits to reschedule
    EXPECT_FALSE(watch._running);
}

TEST(Stopwatch, elapsed_time_nanoseconds_running) {
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
    size_t time = watch.elapsedNanoseconds();

    // Assertion
    EXPECT_BETWEEN(time, 1000, 50000); // TODO: Could fail if OS waits to reschedule
    EXPECT_TRUE(watch._running);
}

// ElapsedTimeNanoseconds

TEST(Stopwatch, elapsed_time_microseconds_zero) {
    // Setup
    Stopwatch watch = Stopwatch();

    // Assertion
    EXPECT_EQ(0, watch.elapsedMicroseconds());
}

TEST(Stopwatch, elapsed_time_microseconds_stopped) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    watch.stop();
    size_t time = watch.elapsedMicroseconds();

    // Assertion
    EXPECT_BETWEEN(time, 100, 500); // TODO: Could fail if OS waits to reschedule
    EXPECT_FALSE(watch._running);
}

TEST(Stopwatch, elapsed_time_microseconds_running) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::microseconds(100));
    size_t time = watch.elapsedMicroseconds();

    // Assertion
    EXPECT_BETWEEN(time, 100, 500); // TODO: Could fail if OS waits to reschedule
    EXPECT_TRUE(watch._running);
}

// ElapsedTimeMilliseconds

TEST(Stopwatch, elapsed_time_milliseconds_zero) {
    // Setup
    Stopwatch watch = Stopwatch();

    // Assertion
    EXPECT_EQ(0, watch.elapsedMilliseconds());
}

TEST(Stopwatch, elapsed_time_milliseconds_stopped) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    watch.stop();
    size_t time = watch.elapsedMilliseconds();

    // Assertion
    EXPECT_BETWEEN(time, 1, 5);
    EXPECT_FALSE(watch._running);
}

TEST(Stopwatch, elapsed_time_milliseconds_running) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    size_t time = watch.elapsedMilliseconds();

    // Assertion
    EXPECT_BETWEEN(time, 1, 5);
    EXPECT_TRUE(watch._running);
}

// ElapsedTimeSeconds

TEST(Stopwatch, elapsed_time_seconds_zero) {
    // Setup
    Stopwatch watch = Stopwatch();

    // Assertion
    EXPECT_EQ(0, watch.elapsedSeconds());
}

TEST(Stopwatch, elapsed_time_seconds_stopped) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    watch.stop();
    size_t time = watch.elapsedSeconds();

    // Assertion
    EXPECT_BETWEEN(time, 1, 2);
    EXPECT_FALSE(watch._running);
}

TEST(Stopwatch, elapsed_time_seconds_running) {
    // Setup
    Stopwatch watch = Stopwatch();
    watch.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    size_t time = watch.elapsedSeconds();

    // Assertion
    EXPECT_BETWEEN(time, 1, 2);
    EXPECT_TRUE(watch._running);
}