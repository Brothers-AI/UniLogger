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
#define LOG_TAG "UniLogger"

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
    void setLogLevel(enum LogLevel level);

    /**
     * @brief Set the Log Stream
     *
     * @param stream stream (LogStream)
     */
    void setLogStream(enum LogStream stream);

    /**
     * @brief Saves Logs to File instead of console print
     *
     * @param filepath filepath to save the log
     */
    void setLogFile(const char *filepath);

    /**
     * @brief Function to close the UniLogger
     */
    void closeLogger();

    /**
     * @brief Common function to log the prints
     * 
     * @param level log level
     * @param logTag log tag
     * @param lineNum line number of log
     * @param format print format arguments
     * @param ... 
     */
    void logCustom(enum LogLevel level,
                   const char *logTag,
                   unsigned int lineNum,
                   const char *format, ...);

#define LOG_FATAL(...) logCustom(LOG_LEVEL_FATAL, LOG_TAG, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(...) logCustom(LOG_LEVEL_ERROR, LOG_TAG, __LINE__, ##__VA_ARGS__)
#define LOG_WARN(...) logCustom(LOG_LEVEL_WARN, LOG_TAG, __LINE__, ##__VA_ARGS__)
#define LOG_INFO(...) logCustom(LOG_LEVEL_INFO, LOG_TAG, __LINE__, ##__VA_ARGS__)
#define LOG_DEBUG(...) logCustom(LOG_LEVEL_DEBUG, LOG_TAG, __LINE__, ##__VA_ARGS__)
#define LOG_TRACE(...) logCustom(LOG_LEVEL_TRACE, LOG_TAG, __LINE__, ##__VA_ARGS__)
#define LOG_PROFILE(...) logCustom(LOG_LEVEL_PROFILE, LOG_TAG, __LINE__, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // __UNI_LOGGER_H__