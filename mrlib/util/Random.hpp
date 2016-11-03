//
// Random.hpp
// mrlib
//
// Created by Matthew Remmel on 11/14/15.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.

/*
 * The purpose of this class is to make working with uniform distributions
 * easier in order to get a better random number generator.
 */


#ifndef MRLIB_RANDOM_HPP
#define MRLIB_RANDOM_HPP

#include <random>
#include <cfloat>

namespace mrlib {

    class Random {
    private:
        std::mt19937 _mersenneTwister;

    public:
        // Constructors
        Random();

        // Random Numbers
        int nextInt(int max = INT_MAX);
        int nextInt(int min, int max);
        long nextLong(long max = LONG_MAX);
        long nextLong(long min, long max);
        float nextFloat(float max = FLT_MAX);
        float nextFloat(float min, float max);
        double nextDouble(double max = DBL_MAX);
        double nextDouble(double min, double max);
        bool nextBoolean();
    };


    /////////////////////////////
    // TEMPLATE IMPLEMENTATION //
    /////////////////////////////

    // Constructors
    inline
    Random::Random() {
        std::random_device random_device;
        this->_mersenneTwister = std::mt19937(random_device());
    }

    // Random Numbers
    inline
    int Random::nextInt(int max) {
        if (max > 0) {
            std::uniform_int_distribution<int> distribution(0, max - 1);
            return distribution(this->_mersenneTwister);
        }
        else {
            throw std::invalid_argument("Max parameter must be greater than zero");
        }
    }

    inline
    int Random::nextInt(int min, int max) {
        if (min < max) {
            std::uniform_int_distribution<int> distribution(min, max - 1);
            return distribution(this->_mersenneTwister);
        }
        else {
            throw std::invalid_argument("Min parameter must be less than max parameter");
        }
    }

    inline
    long Random::nextLong(long max) {
        if (max > 0) {
            std::uniform_int_distribution<long> distribution(0, max - 1);
            return distribution(this->_mersenneTwister);
        }
        else {
            throw std::invalid_argument("Max parameter must be greater than zero");
        }
    }

    inline
    long Random::nextLong(long min, long max) {
        if (min < max) {
            std::uniform_int_distribution<long> distribution(min, max - 1);
            return distribution(this->_mersenneTwister);
        }
        else {
            throw std::invalid_argument("Min parameter must be less than max parameter");
        }
    }

    inline
    float Random::nextFloat(float max) {
        if (max > 0) {
            std::uniform_real_distribution<float> distribution(0, max - 1);
            return distribution(this->_mersenneTwister);
        }
        else {
            throw std::invalid_argument("Max parameter must be greater than zero");
        }
    }

    inline
    float Random::nextFloat(float min, float max) {
        if (min < max) {
            std::uniform_real_distribution<float> distribution(min, max - 1);
            return distribution(this->_mersenneTwister);
        }
        else {
            throw std::invalid_argument("Min parameter must be less than max parameter");
        }
    }

    inline
    double Random::nextDouble(double max) {
        if (max > 0) {
            std::uniform_real_distribution<double> distribution(0, max - 1);
            return distribution(this->_mersenneTwister);
        }
        else {
            throw std::invalid_argument("Max parameter must be greater than zero");
        }
    }

    inline
    double Random::nextDouble(double min, double max) {
        if (min < max) {
            std::uniform_real_distribution<double> distribution(min, max - 1);
            return distribution(this->_mersenneTwister);
        }
        else {
            throw std::invalid_argument("Min parameter must be less than max parameter");
        }
    }

    inline
    bool Random::nextBoolean() {
        std::bernoulli_distribution distribution;
        return distribution(this->_mersenneTwister);
    }
}

#endif //MRLIB_RANDOM_HPP