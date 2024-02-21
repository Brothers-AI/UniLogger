#ifndef __UNI_LOGGER_H__
#define __UNI_LOGGER_H__

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Common function to log the prints
 * 
 * @param level log level
 * @param format print format arguments
 * @param ... 
 */
void logCustom(enum LogLevel level, const char *logTag, const char *format, ...);

#define LOG_FATAL(...)   logCustom(LOG_LEVEL_FATAL, LOG_TAG, ##__VA_ARGS__)
#define LOG_ERROR(...)   logCustom(LOG_LEVEL_ERROR, LOG_TAG, ##__VA_ARGS__)
#define LOG_WARN(...)    logCustom(LOG_LEVEL_WARN, LOG_TAG, ##__VA_ARGS__)
#define LOG_INFO(...)    logCustom(LOG_LEVEL_INFO, LOG_TAG, ##__VA_ARGS__)
#define LOG_DEBUG(...)   logCustom(LOG_LEVEL_DEBUG, LOG_TAG, ##__VA_ARGS__)
#define LOG_TRACE(...)   logCustom(LOG_LEVEL_TRACE, LOG_TAG, ##__VA_ARGS__)
#define LOG_PROFILE(...) logCustom(LOG_LEVEL_PROFILE, LOG_TAG, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // __UNI_LOGGER_H__