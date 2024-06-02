/**
 * @file testLoggerFile.c
 * @author Brothers-AI (brothers.ai.local@gmail.com)
 * @brief Test example for using UniLogger with logfile
 * @version 0.1
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>

// UniLogger Includes
#include <UniLogger.h>

int main(int argc, char const *argv[])
{
    // Set the log level
    setLogLevel(LOG_LEVEL_TRACE);
    // Set the stream type
    setLogStream(STREAM_STDOUT);
    // Set the log file path
    setLogFile("logger.log");

    LOG_FATAL("Fatal logs");
    LOG_ERROR("Error logs");
    LOG_WARN("Warning logs");
    LOG_INFO("Information logs");
    LOG_DEBUG("Debug logs");
    LOG_TRACE("Trace logs");
    LOG_PROFILE("Profile logs");

    // Close the logger
    closeLogger();

    return 0;
}

