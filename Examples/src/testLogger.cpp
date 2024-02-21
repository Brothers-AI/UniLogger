#include <iostream>

// UniLogger Includes
#include <UniLogger.h>

int main(int argc, char const *argv[])
{
    // Set the Log level
    setLogLevel(LOG_LEVEL_TRACE);
    // Set the stream type
    setLogStream(STREAM_STDOUT);

    LOG_FATAL("Fatal logs");
    LOG_ERROR("Error logs");
    LOG_WARN("Warning logs");
    LOG_INFO("Information logs");
    LOG_DEBUG("Debug logs");
    LOG_TRACE("Trace logs");
    LOG_PROFILE("Profile logs");

    return 0;
}

