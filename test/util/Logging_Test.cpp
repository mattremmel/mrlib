//
// Logging_Test.cpp
// mrlib
//
// Created by Matthew Remmel on 3/1/16.
// Copyright (c) 2017 Matthew Remmel. All rights reserved.

#include "Logging.hpp"
#include "gtest.h"
#include <sstream>

using namespace mrlib;


//////////////////
// CONSTRUCTORS //
//////////////////

TEST(Logging, default_constructor) {
    // Setup
    Logging logger = Logging();

    // Assertion
    EXPECT_EQ(LogLevel::debug, logger._logLevel);
    EXPECT_TRUE(logger._toConsole);
    EXPECT_EQ("", logger._logFilePath);
}

TEST(Logging, log_file_constructor) {
    // Setup
    std::string filepath = "test";
    Logging logger = Logging(filepath, false, LogLevel::info);

    // Assertion
    EXPECT_EQ(LogLevel::info, logger._logLevel);
    EXPECT_FALSE(logger._toConsole);
    EXPECT_EQ("test", logger._logFilePath);
}


/////////////////////
// Shared Instance //
/////////////////////

// InitSharedInstance \level

TEST(Logging, init_shared_instance_level) {
    // Setup
    Logging::InitSharedInstance(LogLevel::info);
    Logging logger = Logging::SharedInstance();

    // Assertion
    EXPECT_EQ(LogLevel::info, logger._logLevel);
    EXPECT_TRUE(logger._toConsole);
    EXPECT_EQ("", logger._logFilePath);
}

// InitSharedInstance \logfile

TEST(Logging, init_shared_instance_log_file) {
    // Setup
    std::string filepath = "test";
    Logging::InitSharedInstance(filepath, false, LogLevel::info);
    Logging logger = Logging::SharedInstance();

    // Assertion
    EXPECT_EQ(LogLevel::info, logger._logLevel);
    EXPECT_FALSE(logger._toConsole);
    EXPECT_EQ("test", logger._logFilePath);
}

// Shared Instance

TEST(Logging, is_static_shared_instance) {
    // Setup
    Logging::InitSharedInstance(LogLevel::info);
    Logging& logger1 = Logging::SharedInstance();
    Logging::InitSharedInstance(LogLevel::trace);
    Logging& logger2 = Logging::SharedInstance();

    // Assertion
    EXPECT_EQ(LogLevel::trace, logger1._logLevel);
    EXPECT_EQ(LogLevel::trace, logger2._logLevel);
}


/////////////////////
// Shared Instance //
/////////////////////

// Trace

TEST(Logging, trace_log) {
    // Setup
    std::stringstream buffer;
    std::streambuf* old = std::clog.rdbuf(buffer.rdbuf());

    Logging logger = Logging(LogLevel::trace);
    std::string message = "trace test";
    logger.trace(message);

    struct tm tm = {0};
    time_t timestamp = time(NULL);
    tm = *std::localtime(&timestamp);
    char date_str[25];
    strftime(date_str, 25, "%F %T", &tm);

    std::string output = buffer.str();
    std::string expect = date_str + std::string(" [TRACE] ") + message + "\n";

    // Assertion
    EXPECT_EQ(expect, output);

    // Clean Up
    std::clog.rdbuf(old);
}

// Debug

TEST(Logging, debug_log) {
    // Setup
    std::stringstream buffer;
    std::streambuf* old = std::clog.rdbuf(buffer.rdbuf());

    Logging logger = Logging(LogLevel::debug);
    std::string message = "debug test";
    logger.debug(message);

    struct tm tm = {0};
    time_t timestamp = time(NULL);
    tm = *std::localtime(&timestamp);
    char date_str[25];
    strftime(date_str, 25, "%F %T", &tm);

    std::string output = buffer.str();
    std::string expect = date_str + std::string(" [DEBUG] ") + message + "\n";

    // Assertion
    EXPECT_EQ(expect, output);

    // Clean Up
    std::clog.rdbuf(old);
}

// Info

TEST(Logging, info_log) {
    // Setup
    std::stringstream buffer;
    std::streambuf* old = std::clog.rdbuf(buffer.rdbuf());

    Logging logger = Logging(LogLevel::info);
    std::string message = "info test";
    logger.info(message);

    struct tm tm = {0};
    time_t timestamp = time(NULL);
    tm = *std::localtime(&timestamp);
    char date_str[25];
    strftime(date_str, 25, "%F %T", &tm);

    std::string output = buffer.str();
    std::string expect = date_str + std::string(" [INFO] ") + message + "\n";

    // Assertion
    EXPECT_EQ(expect, output);

    // Clean Up
    std::clog.rdbuf(old);
}

// Warn

TEST(Logging, warning_log) {
    // Setup
    std::stringstream buffer;
    std::streambuf* old = std::clog.rdbuf(buffer.rdbuf());

    Logging logger = Logging(LogLevel::warning);
    std::string message = "warning test";
    logger.warning(message);

    struct tm tm = {0};
    time_t timestamp = time(NULL);
    tm = *std::localtime(&timestamp);
    char date_str[25];
    strftime(date_str, 25, "%F %T", &tm);

    std::string output = buffer.str();
    std::string expect = date_str + std::string(" [WARNING] ") + message + "\n";

    // Assertion
    EXPECT_EQ(expect, output);

    // Clean Up
    std::clog.rdbuf(old);
}

// Error

TEST(Logging, error_log) {
    // Setup
    std::stringstream buffer;
    std::streambuf* old = std::clog.rdbuf(buffer.rdbuf());

    Logging logger = Logging(LogLevel::error);
    std::string message = "error test";
    logger.error(message);

    struct tm tm = {0};
    time_t timestamp = time(NULL);
    tm = *std::localtime(&timestamp);
    char date_str[25];
    strftime(date_str, 25, "%F %T", &tm);

    std::string output = buffer.str();
    std::string expect = date_str + std::string(" [ERROR] ") + message + "\n";

    // Assertion
    EXPECT_EQ(expect, output);

    // Clean Up
    std::clog.rdbuf(old);
}

// Fatal

TEST(Logging, fatal_log) {
    // Setup
    std::stringstream buffer;
    std::streambuf* old = std::clog.rdbuf(buffer.rdbuf());

    Logging logger = Logging(LogLevel::fatal);
    std::string message = "fatal test";
    logger.fatal(message);

    struct tm tm = {0};
    time_t timestamp = time(NULL);
    tm = *std::localtime(&timestamp);
    char date_str[25];
    strftime(date_str, 25, "%F %T", &tm);

    std::string output = buffer.str();
    std::string expect = date_str + std::string(" [FATAL] ") + message + "\n";

    // Assertion
    EXPECT_EQ(expect, output);

    // Clean Up
    std::clog.rdbuf(old);
}


///////////////////////
// Getting Log Level //
///////////////////////

// LogLevel

TEST(Logging, get_log_level) {
    // Setup
    Logging logger = Logging(LogLevel::info);

    // Assertion
    EXPECT_EQ(LogLevel::info, logger.getLogLevel());
}

// TraceEnabled

TEST(Logging, trace_enabled_true) {
    // Setup
    Logging logger = Logging(LogLevel::trace);

    // Assertion
    EXPECT_TRUE(logger.traceEnabled());
}

TEST(Logging, trace_enabled_false) {
    // Setup
    Logging logger = Logging(LogLevel::debug);

    // Assertion
    EXPECT_FALSE(logger.traceEnabled());
}

// DebugEnabled

TEST(Logging, debug_enabled_true) {
    // Setup
    Logging logger = Logging(LogLevel::debug);

    // Assertion
    EXPECT_TRUE(logger.debugEnabled());
}

TEST(Logging, debug_enabled_false) {
    // Setup
    Logging logger = Logging(LogLevel::info);

    // Assertion
    EXPECT_FALSE(logger.debugEnabled());
}

// InfoEnabled

TEST(Logging, info_enabled_true) {
    // Setup
    Logging logger = Logging(LogLevel::info);

    // Assertion
    EXPECT_TRUE(logger.infoEnabled());
}

TEST(Logging, info_enabled_false) {
    // Setup
    Logging logger = Logging(LogLevel::warning);

    // Assertion
    EXPECT_FALSE(logger.infoEnabled());
}

// WarnEnabled

TEST(Logging, warning_enabled_true) {
    // Setup
    Logging logger = Logging(LogLevel::warning);

    // Assertion
    EXPECT_TRUE(logger.warningEnabled());
}

TEST(Logging, warning_enabled_false) {
    // Setup
    Logging logger = Logging(LogLevel::error);

    // Assertion
    EXPECT_FALSE(logger.warningEnabled());
}

// ErrorEnabled

TEST(Logging, error_enabled_true) {
    // Setup
    Logging logger = Logging(LogLevel::error);

    // Assertion
    EXPECT_TRUE(logger.errorEnabled());
}

TEST(Logging, error_enabled_false) {
    // Setup
    Logging logger = Logging(LogLevel::fatal);

    // Assertion
    EXPECT_FALSE(logger.errorEnabled());
}

// FatalEnabled

TEST(Logging, fatal_enabled_true) {
    // Setup
    Logging logger = Logging(LogLevel::fatal);

    // Assertion
    EXPECT_TRUE(logger.fatalEnabled());
}

TEST(Logging, fatal_enabled_false) {
    // Setup
    Logging logger = Logging(LogLevel::off);

    // Assertion
    EXPECT_FALSE(logger.fatalEnabled());
}

// AllEnabled

TEST(Logging, all_enabled_true) {
    // Setup
    Logging logger = Logging(LogLevel::all);

    // Assertion
    EXPECT_TRUE(logger.traceEnabled());
    EXPECT_TRUE(logger.debugEnabled());
    EXPECT_TRUE(logger.infoEnabled());
    EXPECT_TRUE(logger.warningEnabled());
    EXPECT_TRUE(logger.errorEnabled());
    EXPECT_TRUE(logger.fatalEnabled());
}

// IsOff

TEST(Logging, is_off_true) {
    // Setup
    Logging logger = Logging(LogLevel::off);

    // Assertion
    EXPECT_TRUE(logger.isOff());
}

TEST(Logging, is_off_false) {
    // Setup
    Logging logger = Logging(LogLevel::all);

    // Assertion
    EXPECT_FALSE(logger.isOff());
}


///////////////////////
// Setting Log Level //
///////////////////////

// SetLogLevel

TEST(Logging, set_log_level) {
    // Setup
    Logging logger = Logging(LogLevel::debug);
    logger.setLogLevel(LogLevel::error);

    // Assertion
    EXPECT_EQ(LogLevel::error, logger._logLevel);
}


///////////////////////////
// Getting Log File Path //
///////////////////////////

// GetLogFilePath

TEST(Logging, get_log_file_path) {
    // Setup
    Logging logger = Logging("test");

    // Assertion
    EXPECT_EQ("test", logger.getLogFilePath());
}


///////////////////////////
// Setting Log File Path //
///////////////////////////

//SetLogFilePath

TEST(Logging, set_log_file_path) {
    // Setup
    Logging logger = Logging("test");
    logger.setLogFilePath("new path");

    // Assertion
    EXPECT_EQ("new path", logger.getLogFilePath());
}