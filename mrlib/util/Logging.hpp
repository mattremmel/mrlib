//
// Logging.hpp
// mrlib
//
// Created by Matthew Remmel on 12/16/15.
// Copyright (c) 2015 Matthew Remmel. All rights reserved.

/*
 * The purpose of this class is to provide a full featured and expandable logging class that
 * supports setting up a single configured shared logger and being able to easily use that
 * instance throughout your project. Convenience macros were created that will automatically
 * create a formatted log message that includes the file the log message came from, the line
 * number of the log message, the log level of the log message, and a timestamp. There is also
 * a macro if you would like to add the function information to your log message. By default,
 * the logging level is set to debug and to print to the console. If a log file is specified
 * then the logger will append to that log file as well as the console. Printing to the console
 * can optionally be turned off.
 */


#ifndef MRLIB_LOGGING_HPP
#define MRLIB_LOGGING_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include <fstream>


// File / Function Constants
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef __PRETTY_FUNCTION__
#define __FUNC_NAME__ __PRETTY_FUNCTION__
#else
#define __FUNC_NAME__ __func__
#endif


// Convenience macros for logging verbose messages and doing log level checks before string construction
#define _SHARED_LOG mrlib::Logging::SharedInstance()
#define _LOG(level, message) { _SHARED_LOG.level(message); }
#define _VLOG(level, message) { std::ostringstream oss; oss << "File: " << __FILENAME__ << ":" << __LINE__ << " Message: " << message; _SHARED_LOG.level(oss.str()); }

#define LOG_TRACE(message)     if (LOG.traceEnabled())     _LOG(trace, message)
#define LOG_DEBUG(message)     if (LOG.debugEnabled())     _LOG(debug, message)
#define LOG_INFO(message)      if (LOG.infoEnabled())      _LOG(info,  message)
#define LOG_NOTICE(message)    if (LOG.noticeEnabled())    _LOG(notice, message)
#define LOG_WARNING(message)   if (LOG.warningEnabled())   _LOG(warning,  message)
#define LOG_ERROR(message)     if (LOG.errorEnabled())     _LOG(error, message)
#define LOG_CRITICAL(message)  if (LOG.criticallEnabled()) _LOG(critical, message)
#define LOG_ALERT(message)     if (LOG.alertEnabled())     _LOG(alert, message)
#define LOG_FATAL(message)     if (LOG.fatalEnabled())     _LOG(fatal, message)

#define VLOG_TRACE(message)    if (LOG.traceEnabled())     _VLOG(trace, message)
#define VLOG_DEBUG(message)    if (LOG.debugEnabled())     _VLOG(debug, message)
#define VLOG_INFO(message)     if (LOG.infoEnabled())      _VLOG(info,  message)
#define VLOG_NOTICE(message)   if (LOG.noticeEnabled())    _VLOG(notice, message)
#define VLOG_WARNING(message)  if (LOG.warningEnabled())   _VLOG(warning,  message)
#define VLOG_ERROR(message)    if (LOG.errorEnabled())     _VLOG(error, message)
#define VLOG_CRITICAL(message) if (LOG.criticallEnabled()) _VLOG(critical, message)
#define VLOG_ALERT(message)    if (LOG.alertEnabled())     _VLOG(alert, message)
#define VLOG_FATAL(message)    if (LOG.fatalEnabled())     _VLOG(fatal, message)


namespace mrlib {

    enum class LogLevel {
        all      = 0,
        trace    = 10,
        debug    = 20,
        info     = 30,
        notice   = 40,
        warning  = 50,
        error    = 60,
        critical = 70,
        alert    = 80,
        fatal    = 90,
        off      = 100
    };

    class Logging {
    public:
        // Internal Data
        LogLevel    _logLevel;
        bool        _toConsole;
        std::string _logFilePath;

        // Singleton
        static Logging& SharedInstance();
        static void InitSharedInstance(LogLevel level = LogLevel::debug);
        static void InitSharedInstance(const std::string& log_file, bool to_console = true, LogLevel level = LogLevel::debug);

        // Constructors
        Logging(LogLevel level = LogLevel::debug);
        Logging(const std::string& log_file_path, bool to_console = true, LogLevel level = LogLevel::debug);

        // Logging
        void trace(const std::string& message) const;
        void debug(const std::string& message) const;
        void info(const std::string& message) const;
        void notice(const std::string& message) const;
        void warning(const std::string& message) const;
        void error(const std::string& message) const;
        void critical(const std::string& message) const;
        void alert(const std::string& message) const;
        void fatal(const std::string& message) const;
        void write(const std::string& message) const;

        // Getting Log Level
        LogLevel  getLogLevel() const;
        bool traceEnabled() const;
        bool debugEnabled() const;
        bool infoEnabled() const;
        bool noticeEnabled() const;
        bool warningEnabled() const;
        bool errorEnabled() const;
        bool criticalEnabled() const;
        bool alertEnabled() const;
        bool fatalEnabled() const;
        bool isOff() const;

        // Setting Log Level
        void setLogLevel(LogLevel level);

        // Getting Log File Path
        std::string getLogFilePath() const;

        // Setting Log File Path
        void setLogFilePath(const std::string& log_file_path);
    };


    ///////////////////////////
    // HEADER IMPLEMENTATION //
    ///////////////////////////

    // Shared Instance
    inline
    Logging& Logging::SharedInstance() {
        static Logging shared;
        return shared;
    }

    inline
    void Logging::InitSharedInstance(LogLevel level) {
        Logging::SharedInstance()._logLevel = level;
    }

    inline
    void Logging::InitSharedInstance(const std::string& log_file_path, bool to_console, LogLevel level) {
        Logging::SharedInstance()._logFilePath = log_file_path;
        Logging::SharedInstance()._toConsole = to_console;
        Logging::SharedInstance()._logLevel = level;
    }

    // Constructors
    inline
    Logging::Logging(LogLevel level) {
        this->_logLevel = level;
        this->_toConsole = true;
        this->_logFilePath = "";
    }

    inline
    Logging::Logging(const std::string& log_file, bool to_console, LogLevel level) {
        this->_logLevel = level;
        this->_toConsole = to_console;
        this->_logFilePath = log_file;
    }


    // Logging
    inline
    void Logging::trace(const std::string& message) const {

        if (this->_logLevel <= LogLevel::trace) {
            this->write(std::string("[TRACE] ") + message);
        }
    }

    inline
    void Logging::debug(const std::string& message) const {

        if (this->_logLevel <= LogLevel::debug) {
            this->write(std::string("[DEBUG] ") + message);
        }
    }

    inline
    void Logging::info(const std::string& message) const {

        if (this->_logLevel <= LogLevel::info) {
            this->write(std::string("[INFO] ") + message);
        }
    }

    inline
    void Logging::notice(const std::string& message) const {

        if (this->_logLevel <= LogLevel::notice) {
            this->write(std::string("[NOTICE] ") + message);
        }
    }

    inline
    void Logging::warning(const std::string& message) const {

        if (this->_logLevel <= LogLevel::warning) {
            this->write(std::string("[WARNING] ") + message);
        }
    }

    inline
    void Logging::error(const std::string& message) const {

        if (this->_logLevel <= LogLevel::error) {
            this->write(std::string("[ERROR] ") + message);
        }
    }

    inline
    void Logging::critical(const std::string& message) const {

        if (this->_logLevel <= LogLevel::critical) {
            this->write(std::string("[CRITICAL] ") + message);
        }
    }

    inline
    void Logging::alert(const std::string& message) const {

        if (this->_logLevel <= LogLevel::alert) {
            this->write(std::string("[ALERT] ") + message);
        }
    }

    inline
    void Logging::fatal(const std::string& message) const {

        if (this->_logLevel <= LogLevel::fatal) {
            this->write(std::string("[FATAL] ") + message);
        }
    }

    inline
    void Logging::write(const std::string& message) const {

        // Get current timestamp
        time_t timestamp = time(NULL);

        // Get date info
        struct tm tm = {0};
        tm = *std::localtime(&timestamp);
        char date_str[25];
        strftime(date_str, 25, "%F %T", &tm);

        // Construct log message
        std::string output = date_str + std::string(" ") + message + "\n";

        // Print to std_log stream
        if (this->_toConsole) {
            std::clog << output;
        }

        // Write to log file
        if (this->_logFilePath.size() > 0) {
            try {
                std::ofstream ofs;
                ofs.open(this->_logFilePath.c_str(), std::ios::app);

                if (ofs.is_open()) {
                    ofs << output;
                    ofs.close();
                } else {
                    throw std::invalid_argument("Error opening file at path: " + this->_logFilePath);
                }
            }
            catch (std::exception e) {
                throw std::invalid_argument(
                        "Exception opening file at path: " + this->_logFilePath + " error: " + e.what());
            }
        }
    }


    // Getting Log Level
    inline
    LogLevel Logging::getLogLevel() const {
        return this->_logLevel;
    }

    inline
    bool Logging::traceEnabled() const {
        return this->_logLevel <= LogLevel::trace;
    }

    inline
    bool Logging::debugEnabled() const {
        return this->_logLevel <= LogLevel::debug;
    }

    inline
    bool Logging::infoEnabled() const {
        return this->_logLevel <= LogLevel::info;
    }

    inline
    bool Logging::noticeEnabled() const {
        return this->_logLevel <= LogLevel::notice;
    }

    inline
    bool Logging::warningEnabled() const {
        return this->_logLevel <= LogLevel::warning;
    }

    inline
    bool Logging::errorEnabled() const {
        return this->_logLevel <= LogLevel::error;
    }

    inline
    bool Logging::criticalEnabled() const {
        return this->_logLevel <= LogLevel::critical;
    }

    inline
    bool Logging::alertEnabled() const {
        return this->_logLevel <= LogLevel::alert;
    }

    inline
    bool Logging::fatalEnabled() const {
        return this->_logLevel <= LogLevel::fatal;
    }

    inline
    bool Logging::isOff() const {
        return this->_logLevel >= LogLevel::off;
    }


    // Setting Log Level
    inline
    void Logging::setLogLevel(LogLevel level) {
        this->_logLevel = level;
    }


    //  Getting Log File Path
    inline
    std::string Logging::getLogFilePath() const {
        return this->_logFilePath;
    }


    // Setting Log File Path
    inline
    void Logging::setLogFilePath(const std::string& log_file_path) {
        this->_logFilePath = log_file_path;
    }
}

#endif // MRLIB_LOGGING_HPP
