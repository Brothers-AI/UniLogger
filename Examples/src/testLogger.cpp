/**
 * @file testLogger.cpp
 * @author Brothers-AI (brothers.ai.local@gmail.com)
 * @brief Test example for using UniLogger
 * @version 0.1
 * @date 2024-01-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <iostream>

// UniLogger Includes
#include <UniLogger.h>

int main(int argc, char const *argv[])
{
    // Set the Log level
    UniLogger_SetLogLevel(LOG_LEVEL_TRACE);
    // Set the stream type
    UniLogger_SetLogStream(STREAM_STDOUT);

    LOG_FATAL("Fatal logs");
    LOG_ERROR("Error logs");
    LOG_WARN("Warning logs");
    LOG_INFO("Information logs");
    LOG_DEBUG("Debug logs");
    LOG_TRACE("Trace logs");
    LOG_PROFILE("Profile logs");

    // Close the logger
    UniLogger_CloseLogger();

    return 0;
}

