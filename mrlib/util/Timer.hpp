//
// Timer.hpp
// mrlib
//
// Created by Matthew Remmel on 5/14/17.
// Copyright (c) 2017 Matthew Remmel. All rights reserved.


#ifndef MRLIB_TIMER_HPP
#define MRLIB_TIMER_HPP

#include <chrono>
#include <thread>


namespace mrlib {

    class Timer {
    public:
        // Constants
        static const size_t Infinite = -1l;

        // Internal Data
        std::thread                _thread;
        volatile bool              _isAlive;
        size_t                     _callCount;
        size_t                     _repeatCount;
        std::chrono::nanoseconds   _interval;
        std::function<void(void)>  _target;

        // Internal Functions
        void _run();

        // Constructors
        template<class Rep, class Period>
        Timer(const std::chrono::duration<Rep, Period>& interval, const std::function<void(void)>& target);
        template<class Rep, class Period>
        Timer(const std::chrono::duration<Rep, Period>& interval, size_t repeatCount, const std::function<void(void)>& target);

        // Getters
        bool                      isAlive() const;
        size_t                    getCallCount() const;
        size_t                    getRepeatCount() const;
        std::chrono::nanoseconds  getInterval() const;

        // Setters
        void  setRepeatCount(size_t count);
        template<class Rep, class Period>
        void  setInterval(const std::chrono::duration<Rep, Period>& interval);
        void  setTarget(const std::function<void(void)>& target);

        // Operation
        void  start(bool async = true);
        void  stop();
    };


    ///////////////////////////
    // HEADER IMPLEMENTATION //
    ///////////////////////////

    // Constructors
//    inline - ignore on explicit template instantiation
    template<class Rep, class Period>
    Timer::Timer(const std::chrono::duration<Rep, Period>& interval, const std::function<void(void)>& target) {
        this->_isAlive = false;
        this->_callCount = 0;
        this->_repeatCount = Timer::Infinite;
        this->_interval = std::chrono::duration_cast<std::chrono::nanoseconds>(interval);
        this->_target = target;
    }

//    inline - ignore on explicit template instantiation
    template<class Rep, class Period>
    Timer::Timer(const std::chrono::duration<Rep, Period>& interval, size_t repeatCount, const std::function<void(void)>& target) {
        this->_isAlive = false;
        this->_callCount = 0;
        this->_repeatCount = repeatCount;
        this->_interval = std::chrono::duration_cast<std::chrono::nanoseconds>(interval);
        this->_target = target;
    }

    // Getters
    inline
    bool Timer::isAlive() const {
        return this->_isAlive;
    }

    inline
    size_t Timer::getCallCount() const {
        return this->_callCount;
    }

    inline
    size_t Timer::getRepeatCount() const {
        return this->_repeatCount;
    }

    inline
    std::chrono::nanoseconds Timer::getInterval() const {
        return this->_interval;
    }

    // Setters
    inline
    void Timer::setRepeatCount(size_t count) {
        this->_repeatCount = count;
    }

//    inline - ignore on explicit template instantiation
    template<class Rep, class Period>
    void Timer::setInterval(const std::chrono::duration<Rep, Period>& interval) {
        this->_interval = std::chrono::duration_cast<std::chrono::nanoseconds>(interval);
    }

    inline
    void Timer::setTarget(const std::function<void(void)>& target) {
        this->_target = target;
    }

    // Operation
    inline
    void Timer::start(bool async) {

        if (this->_isAlive) return;

        this->_isAlive = true;

        if (async) {
            this->_thread = std::thread(&Timer::_run, this);
        }
        else {
            this->_run();
        }
    }

    inline
    void Timer::stop() {
        this->_isAlive = false;
        this->_thread.join();
    }

    // Internal Functions
    inline
    void Timer::_run() {

        while (this->_isAlive && (this->_repeatCount == Timer::Infinite || this->_repeatCount-- > 0)) {
            std::this_thread::sleep_for(this->_interval);
            this->_target();
            ++this->_callCount;
        }

        this->_isAlive = false;
    }
}

#endif // MRLIB_TIMER_HPP
