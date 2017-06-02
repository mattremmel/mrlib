//
// Singleton.hpp
// mrlib
//
// Created by Matthew Remmel on 6/1/17.
// Copyright (c) 2017 Matthew Remmel. All rights reserved.

#ifndef MRLIB_SINGLETON_HPP
#define MRLIB_SINGLETON_HPP

#define SINGLETON(type) Singleton<type>::SharedInstance()


namespace mrlib {

    template<class T>
    class Singleton {
    public:
        static T& SharedInstance();
    };


    ///////////////////////////
    // HEADER IMPLEMENTATION //
    ///////////////////////////

//    inline - ignore on explicit template instantiation
    template<class T>
    T& Singleton<T>::SharedInstance() {
        static T shared;
        return shared;
    }
}

#endif // MRLIB_SINGLETON_HPP
