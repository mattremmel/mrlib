//
// Singleton_Test.cpp
// mrlib
//
// Created by Matthew Remmel on 6/1/17.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.

#include "Singleton.hpp"
#include "gtest.h"

using namespace mrlib;


// Shared Instance

TEST(Singleton, shared_instance) {
    // Setup
    Singleton<int>::SharedInstance() = 5;

    // Assertion
    EXPECT_EQ(5, Singleton<int>::SharedInstance());
}

TEST(Singleton, shared_instance_reference) {
    // Setup
    int& expect = Singleton<int>::SharedInstance();
    Singleton<int>::SharedInstance() = 5;

    // Assertion
    EXPECT_EQ(5, expect);
}

// Macro

TEST(Singleton, shared_instance_macro) {
    // Setup
    SINGLETON(int) = 5;

    // Assertion
    EXPECT_EQ(5, SINGLETON(int));
}

TEST(Singleton, shared_instance_reference_macro) {
    // Setup
    int& expect = SINGLETON(int);
    SINGLETON(int) = 5;

    // Assertion
    EXPECT_EQ(5, expect);
}