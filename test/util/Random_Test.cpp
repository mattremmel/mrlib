//
// Created by Matthew on 11/14/15.
//

#include "gtest.h"
#include "Random.hpp" // TODO: If Random.hpp is included first before gtest.h, there are compile errors
                      // TODO: for undeclared identifier FLT_MAX and DBL_MAX
using namespace mrlib;

// Macro for asserting value between two values
#define EXPECT_BETWEEN(actual, lower, upper) EXPECT_GE(actual, lower); EXPECT_LE(actual, upper);
#define LOOP_ITERATIONS 1000


////////////////////
// Random Numbers //
////////////////////

// NextInt

TEST(Random, int_no_parameter) {
    // Setup
    Random random = Random();
    int n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextInt();
        EXPECT_BETWEEN(n, 0, INT_MAX);
    }
}

TEST(Random, int_max_parameter) {
    // Setup
    Random random = Random();
    int n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextInt(10);
        EXPECT_BETWEEN(n, 0, 10);
    }
}

#ifndef NO_BOUNDS_CHECK
TEST(Random, int_max_bounds_check) {
    // Setup
    Random random = Random();

    // Assertion
    EXPECT_ANY_THROW(random.nextInt(-1));
}
#endif

TEST(Random, int_min_max_positive) {
    // Setup
    Random random = Random();
    int n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextInt(10, 20);
        EXPECT_BETWEEN(n, 10, 20);
    }
}

TEST(Random, int_min_max_negative) {
    // Setup
    Random random = Random();
    int n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextInt(-20, -10);
        EXPECT_BETWEEN(n, -20, -10);
    }
}

#ifndef NO_BOUNDS_CHECK
TEST(Random, int_min_max_bounds_check) {
    // Setup
    Random random = Random();

    // Assertion
    EXPECT_ANY_THROW(random.nextInt(5, 1));
}
#endif

// NextLong

TEST(Random, long_no_parameter) {
    // Setup
    Random random = Random();
    long n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextLong();
        EXPECT_BETWEEN(n, 0, LONG_MAX);
    }
}

TEST(Random, long_max) {
    // Setup
    Random random = Random();
    long n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextLong(10);
        EXPECT_BETWEEN(n, 0, 10);
    }
}

#ifndef NO_BOUNDS_CHECK
TEST(Random, long_max_bounds_check) {
    // Setup
    Random random = Random();

    // Assertion
    EXPECT_ANY_THROW(random.nextLong(-1));
}
#endif

TEST(Random, long_min_max_positive) {
    // Setup
    Random random = Random();
    long n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextLong(10, 20);
        EXPECT_BETWEEN(n, 10, 20);
    }
}

TEST(Random, long_min_max_negative) {
    // Setup
    Random random = Random();
    long n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextLong(-20, -10);
        EXPECT_BETWEEN(n, -20, -10);
    }
}

#ifndef NO_BOUNDS_CHECK
TEST(Random, long_min_max_bounds_check) {
    // Setup
    Random random = Random();

    // Assertion
    EXPECT_ANY_THROW(random.nextLong(-1));
}
#endif

// NextFloat

TEST(Random, float_no_parameter) {
    // Setup
    Random random = Random();
    float n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextFloat();
        EXPECT_BETWEEN(n, 0, FLT_MAX);
    }
}

TEST(Random, float_max) {
    // Setup
    Random random = Random();
    float n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextFloat(10.5);
        EXPECT_BETWEEN(n, 0, 10.5);
    }
}

#ifndef NO_BOUNDS_CHECK
TEST(Random, float_max_no_bounds_check) {
    // Setup
    Random random = Random();

    // Assertion
    EXPECT_ANY_THROW(random.nextFloat(-1.5));
}
#endif

TEST(Random, float_min_max_positive) {
    // Setup
    Random random = Random();
    float n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextFloat(10.5, 20.5);
        EXPECT_BETWEEN(n, 10.5, 20.5);
    }
}

TEST(Random, float_min_max_negative) {
    // Setup
    Random random = Random();
    float n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextFloat(-20.5, -10.5);
        EXPECT_BETWEEN(n, -20.5, -10.5);
    }
}

#ifndef NO_BOUNDS_CHECK
TEST(Random, float_min_max_bounds_check) {
    // Setup
    Random random = Random();

    // Assertion
    EXPECT_ANY_THROW(random.nextFloat(5.5, 1.5));
}
#endif

// NextDouble

TEST(Random, double_no_parameter) {
    // Setup
    Random random = Random();
    double n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextDouble();
        EXPECT_BETWEEN(n, 0, DBL_MAX);
    }
}

TEST(Random, double_max) {
    // Setup
    Random random = Random();
    double n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextDouble(10.5);
        EXPECT_BETWEEN(n, 0, 10.5);
    }
}

#ifndef NO_BOUNDS_CHECK
TEST(Random, double_max_bounds_check) {
    // Setup
    Random random = Random();

    // Assertion
    EXPECT_ANY_THROW(random.nextDouble(-1.5));
}
#endif

TEST(Random, double_min_max_positive) {
    // Setup
    Random random = Random();
    double n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextDouble(10.5, 20.5);
        EXPECT_BETWEEN(n, 10.5, 20.5);
    }
}

TEST(Random, double_min_max_negative) {
    // Setup
    Random random = Random();
    double n;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextDouble(-20.5, -10.5);
        EXPECT_BETWEEN(n, -20.5, -10.5);
    }
}

#ifndef NO_BOUNDS_CHECK
TEST(Random, double_min_max_bounds_check) {
    // Setup
    Random random = Random();

    // Assertion
    EXPECT_ANY_THROW(random.nextDouble(5.5, 1.5));
}
#endif

// NextBoolean

TEST(Random, bool_no_parameter) {
    // Setup
    Random random = Random();
    bool n;
    bool hadTrue = false;
    bool hadFalse = false;

    // Assertion
    for (int i = 0; i < LOOP_ITERATIONS; ++i) {
        n = random.nextBoolean();
        if (n == true) hadTrue = true;
        if (n == false) hadFalse = true;
    }

    EXPECT_TRUE(hadTrue);
    EXPECT_TRUE(hadFalse);
}