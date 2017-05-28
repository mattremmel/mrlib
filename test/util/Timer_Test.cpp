//
// Timer_Test.hpp
// mrlib
//
// Created by Matthew Remmel on 5/25/17.
// Copyright (c) 2017 Matthew Remmel. All rights reserved.

#include "Timer.hpp"
#include "gtest.h"

using namespace mrlib;


//////////////////
// Constructors //
//////////////////

TEST(Timer, interval_constructor) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), [](){});
    std::chrono::nanoseconds expect_interval = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1));

    // Assertion
    EXPECT_FALSE(t._isAlive);
    EXPECT_EQ(0, t._callCount);
    EXPECT_EQ(1, t._repeatCount);
    EXPECT_EQ(expect_interval, t._interval);
}

TEST(Timer, repeat_constructor) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), 5, [](){});
    std::chrono::nanoseconds expect_interval = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1));

    // Assertion
    EXPECT_FALSE(t._isAlive);
    EXPECT_EQ(0, t._callCount);
    EXPECT_EQ(5, t._repeatCount);
    EXPECT_EQ(expect_interval, t._interval);
}


/////////////
// Getters //
/////////////

// IsAlive

TEST(Timer, is_alive_false) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), [](){});

    // Assertion
    EXPECT_FALSE(t.isAlive());
}

TEST(Timer, is_alive_true) {
    // Setup
    Timer t = Timer(std::chrono::milliseconds(1), 5, [](){});
    t.start();

    // Assertion
    EXPECT_TRUE(t.isAlive());

    // Clean Up
    if (t._thread.joinable()) {
        t._thread.join();
    }
}

// GetCallCount

TEST(Timer, get_call_count_zero) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), [](){});

    // Assertion
    EXPECT_EQ(0, t.getCallCount());
}

TEST(Timer, get_call_count_five) {
    // Setup
    Timer t = Timer(std::chrono::milliseconds(1), 5, [](){});
    t.start();

    if (t._thread.joinable()) { t._thread.join(); }

    // Assertion
    EXPECT_EQ(5, t.getCallCount());
}

// GetRepeatCount

TEST(Timer, get_repeat_count_zero) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), 0, [](){});

    // Assertion
    EXPECT_EQ(0, t.getRepeatCount());
}

TEST(Timer, get_repeat_count_one) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), 5, [](){});

    // Assertion
    EXPECT_EQ(5, t.getRepeatCount());
}

// GetInterval

TEST(Timer, get_interval) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), [](){});
    std::chrono::nanoseconds expect = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(1));

    // Assertion
    EXPECT_EQ(expect, t.getInterval());
}

TEST(Timer, get_interval_cast) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), [](){});

    // Assertion
    EXPECT_EQ(std::chrono::seconds(1), std::chrono::duration_cast<std::chrono::seconds>(t.getInterval()));
}


/////////////
// Setters //
/////////////

// SetRepeatCount

TEST(Timer, set_repeat_count_zero) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), [](){});
    t.setRepeatCount(0);

    // Assertion
    EXPECT_EQ(0, t._repeatCount);
}

TEST(Timer, set_repeat_count_five) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), [](){});
    t.setRepeatCount(5);

    // Assertion
    EXPECT_EQ(5, t._repeatCount);
}

// SetInterval

TEST(Timer, set_interval) {
    // Setup
    Timer t = Timer(std::chrono::seconds(1), [](){});
    t.setInterval(std::chrono::nanoseconds(100));

    // Assertion
    EXPECT_EQ(std::chrono::nanoseconds(100), t._interval);
}

// SetTarget

TEST(Timer, set_target) {
    // Setup
    int i = 0;
    Timer t = Timer(std::chrono::milliseconds(1), 1, [&i](){
        i = 5;
    });

    t.setTarget([&i](){
        i = 10;
    });

    t.start();
    if (t._thread.joinable()) { t._thread.join(); }

    // Assertion
    EXPECT_EQ(10, i);
}


///////////////
// Operation //
///////////////

// Start

TEST(Timer, started_sync) {
    // Setup
    int i = 0;
    Timer t = Timer(std::chrono::milliseconds(1), [&i](){
        i = 5;
    });

    t.start(false);

    // Assertion
    EXPECT_EQ(5, i);
}

TEST(Timer, started_async) {
    // Setup
    int i = 0;
    Timer t = Timer(std::chrono::milliseconds(1), [&i](){
        i = 5;
    });

    t.start();
    if (t._thread.joinable()) { t._thread.join(); }

    // Assertion
    EXPECT_EQ(5, i);
}

TEST(Timer, did_repeat_five_sync) {
    // Setup
    int i = 0;
    Timer t = Timer(std::chrono::milliseconds(1), 5, [&i](){
        ++i;
    });

    t.start(false);

    // Assertion
    EXPECT_EQ(5, i);
}

TEST(Timer, did_repeat_five_async) {
    // Setup
    int i = 0;
    Timer t = Timer(std::chrono::milliseconds(1), 5, [&i](){
       ++i;
    });

    t.start();
    if (t._thread.joinable()) { t._thread.join(); }

    // Assertion
    EXPECT_EQ(5, i);
}

// Stop

TEST(Timer, stopped_early_sync) {
    // Setup
    int i = 0;
    Timer t = Timer(std::chrono::milliseconds(1), 5, [&i, &t](){
        ++i;
        if (i == 3) { t.stop(); }
    });

    t.start(false);

    // Assertion
    EXPECT_EQ(3, i);
}

TEST(Timer, stopped_early_async) {
    // Setup
    int i = 0;
    Timer t = Timer(std::chrono::milliseconds(50), 10, [&i](){
       ++i;
    });

    t.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    t.stop();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    // Assertion
    EXPECT_LT(i, 5);
}
