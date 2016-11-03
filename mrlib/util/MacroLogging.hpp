//
// MacroLogging.hpp
// Archimedes
//
// Created by Matthew Remmel on 5/20/15.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.
//

/*
 * The purpose of this file was to provide a simple logging framework using only
 * macros. The downside is to change the logging level, this file has to be modified
 * where specified below, and the project recompiled. The upside is when disabled and
 * recompiled, there is nothing additional that get compiled into your code.
 */


#ifndef ARCHIMEDES_LOGGING_H
#define ARCHIMEDES_LOGGING_H

#include <iostream>

// Set to desired logging level. Comment out, or set to NONE to remove logging
#define LOGGING_LEVEL_DEBUG

#ifdef LOGGING_LEVEL_TRACE
    #define LOG_TRACE(message) std::cout << "[TRACE] " << message << std::endl
    #define LOGGING_LEVEL_DEBUG
    #define LOGGING_LEVEL_INFO
    #define LOGGING_LEVEL_FATAL
    #define LOGGING_LEVEL_WARNING
    #define LOGGING_LEVEL_ERROR
#endif
#ifdef LOGGING_LEVEL_DEBUG
    #define LOG_DEBUG(message) std::cout << "[DEBUG] " << message << std::endl
    #define LOGGING_LEVEL_INFO
    #define LOGGING_LEVEL_WARNING
    #define LOGGING_LEVEL_ERROR
    #define LOGGING_LEVEL_FATAL
#endif
#ifdef LOGGING_LEVEL_INFO
    #define LOG_INFO(message) std::cout << "[INFO]  " << message << std::endl
    #define LOGGING_LEVEL_WARNING
    #define LOGGING_LEVEL_ERROR
    #define LOGGING_LEVEL_FATAL
#endif
#ifdef LOGGING_LEVEL_WARNING
    #define LOG_WARN(message) std::cout << "[WARN]  " << message << std::endl
    #define LOGGING_LEVEL_ERROR
    #define LOGGING_LEVEL_FATAL
#endif
#ifdef LOGGING_LEVEL_ERROR
    #define LOG_ERROR(message) std::cout << "[ERROR] " << message << std::endl
    #define LOGGING_LEVEL_FATAL
#endif
#ifdef LOGGING_LEVEL_FATAL
    #define LOG_FATAL(message) std::cout << "[FATAL] " << message << std::endl
#endif


#ifndef LOGGING_LEVEL_TRACE
    #define LOG_TRACE(message)
#endif
#ifndef LOGGING_LEVEL_INFO
    #define LOG_INFO(message)
#endif
#ifndef LOGGING_LEVEL_FATAL
    #define LOG_FATAL(message)
#endif
#ifndef LOGGING_LEVEL_WARNING
    #define LOG_WARN(message)
#endif
#ifndef LOGGING_LEVEL_ERROR
    #define LOG_ERROR(message)
#endif
#ifndef LOGGING_LEVEL_DEBUG
    #define LOG_DEBUG(message)
#endif

#endif //ARCHIMEDES_LOGGING_H
