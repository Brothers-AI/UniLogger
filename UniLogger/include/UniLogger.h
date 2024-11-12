/**
 * @file UniLogger.h
 * @author Brothers-AI (brothers.ai.local@gmail.com)
 * @brief UniLogger header file
 * @version 0.1
 * @date 2024-01-25
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef __UNI_LOGGER_H__
#define __UNI_LOGGER_H__

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @brief Log tag for logging
 * Can be changed in respective files where this header is included
 *
 * @paragraph
 * Example:
 * #include <UniLogger.h>
 *
 * #ifdef LOG_TAG
 * #undef LOG_TAG
 * #define LOG_TAG "NAME"
 * #else
 * #define LOG_TAG "NAME"
 * #endif // LOG_TAG
 */
#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#endif // __FILENAME__

#ifdef USE_FILE_NAME
#define LOG_TAG __FILENAME__
#else
#define LOG_TAG "UniLogger"
#endif // USE_FILE_NAME

    /**
     * @brief Enums for Log Levels
     */
    enum LogLevel
    {
        // Log level for No Logging
        LOG_LEVEL_OFF = 0,
        // Log Level for Only Fatal Logs
        LOG_LEVEL_FATAL,
        // Log Level till Error Logs
        LOG_LEVEL_ERROR,
        // Log Level till Warn Logs
        LOG_LEVEL_WARN,
        // Log Level till Info Logs
        LOG_LEVEL_INFO,
        // Log Level till Debug Logs
        LOG_LEVEL_DEBUG,
        // Log Level till Trace Logs
        LOG_LEVEL_TRACE,
        // Log Level for Only Profile Logs
        LOG_LEVEL_PROFILE,
        // Maximum Number of Log Level
        LOG_MAX_LEVEL,
    };

    /**
     * @brief Enum for Stream
     */
    enum LogStream
    {
        // For stdout stream prints
        STREAM_STDOUT,
        // For stderr stream prints
        STREAM_STDERR
    };

    /**
     * @brief Set the Log Level for Logging
     *
     * @param level Log Level (LogLevel)
     */
    void UniLogger_SetLogLevel(enum LogLevel level);

    /**
     * @brief Set the Log Stream
     *
     * @param stream stream (LogStream)
     */
    void UniLogger_SetLogStream(enum LogStream stream);

    /**
     * @brief Saves Logs to File instead of console print
     *
     * @param filepath filepath to save the log
     */
    void UniLogger_SetLogFile(const char *filepath);

    /**
     * @brief Function to close the UniLogger
     */
    void UniLogger_CloseLogger();

    /**
     * @brief Common function to log the prints
     *
     * @param level log level
     * @param logTag log tag
     * @param lineNum line number of log
     * @param format print format arguments
     * @param ...
     */
    void UniLogger_CustomLogFn(enum LogLevel level,
                               const char *logTag,
                               unsigned int lineNum,
                               const char *format, ...);

/**
 * @brief Log method for fatal error
 */
#define LOG_FATAL(...) UniLogger_CustomLogFn(LOG_LEVEL_FATAL, \
                                             LOG_TAG,         \
                                             __LINE__, ##__VA_ARGS__)
/**
 * @brief Log method for default error
 */
#define LOG_ERROR(...) UniLogger_CustomLogFn(LOG_LEVEL_ERROR, \
                                             LOG_TAG,         \
                                             __LINE__, ##__VA_ARGS__)
/**
 * @brief Log method for warnings
 */
#define LOG_WARN(...) UniLogger_CustomLogFn(LOG_LEVEL_WARN, \
                                            LOG_TAG,        \
                                            __LINE__, ##__VA_ARGS__)
/**
 * @brief Log method for information logs
 */
#define LOG_INFO(...) UniLogger_CustomLogFn(LOG_LEVEL_INFO, \
                                            LOG_TAG,        \
                                            __LINE__, ##__VA_ARGS__)
/**
 * @brief Log method for debug logs
 */
#define LOG_DEBUG(...) UniLogger_CustomLogFn(LOG_LEVEL_DEBUG, \
                                             LOG_TAG,         \
                                             __LINE__, ##__VA_ARGS__)
/**
 * @brief Log method for trace logs
 */
#define LOG_TRACE(...) UniLogger_CustomLogFn(LOG_LEVEL_TRACE, \
                                             LOG_TAG,         \
                                             __LINE__, ##__VA_ARGS__)
/**
 * @brief Log method for profile logs
 */
#define LOG_PROFILE(...) UniLogger_CustomLogFn(LOG_LEVEL_PROFILE, \
                                               LOG_TAG,           \
                                               __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // __UNI_LOGGER_H__