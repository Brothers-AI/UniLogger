/**
 * @file UniLogger.c
 * @author Brothers-AI (brothers.ai.local@gmail.com)
 * @brief UniLogger implementation in c
 * @version 0.1
 * @date 2024-01-25
 *
 * @copyright Copyright (c) 2024
 *
 */
// System Include
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <pthread.h>

#include <UniLogger.h>

// Global Variables

// Current Log Level, Default to Off
enum LogLevel gCurrLogLevel = LOG_LEVEL_OFF;
// Flag to Check Environment variable for Log Level is Read or not
unsigned char gIsLogLevelInitalized = 0;

// Current Log Stream, Default to stdout
static FILE *gCurrLogStream;
// Flag to Check Environment variable for Log Stream is Read or not
unsigned char gIsLogStreamInitalized = 0;

// Flag to Check is Log File Initalized, Default to 0
unsigned char gIsLogFileInitalized = 0;

// Mutex for log handler
static pthread_mutex_t s_logMutex;

// Flag to check mutex initalized
unsigned char gIsMutexInitalized = 0;

/**
 * @brief Log level names
 */
const char logLevelNames[LOG_MAX_LEVEL][10] = {
    "",
    " FATAL ",
    " ERROR ",
    " WARN  ",
    " INFO  ",
    " DEBUG ",
    " TRACE ",
    "PROFILE"};

/**
 * @brief Color Codes for Different Log Levels
 */
const char colorCodes[LOG_MAX_LEVEL][10] = {
    "",
    "\033[1;31m",
    "\033[0;31m",
    "\033[0;33m",
    "\033[0;32m",
    "\033[0;36m",
    "\033[0;35m",
    "\033[0;32m"};

/**
 * @brief Method to log line
 *
 * @param stream type of the stream
 * @param logLevelName log level name in string
 * @param logTag log tag in string
 * @param lineNum log line number
 * @param colorCode color code for the for log level
 * @param isSavingToFile flag to save the log to file
 * @param format format of print
 * @param ... arguments of print
 */
static inline void LogLine(FILE *stream,
                           const char *logLevelName,
                           const char *logTag,
                           unsigned int lineNum,
                           const char *colorCode,
                           unsigned char isSavingToFile,
                           const char *format,
                           ...);

/**
 * @brief Method to log the line with va_list args
 *
 * @param stream type of the stream
 * @param logLevelName log level name in string
 * @param logTag log tag in string
 * @param lineNum log line number
 * @param colorCode color code for the for log level
 * @param isSavingToFile flag to save the log to file
 * @param args args of the print
 * @param format format of the print
 */
static inline void LogLineArgs(FILE *stream,
                               const char *logLevelName,
                               const char *logTag,
                               unsigned int lineNum,
                               const char *colorCode,
                               unsigned char isSavingToFile,
                               va_list args,
                               const char *format);

/**
 * @brief Information log
 */
#define INFO_LOG(...) LogLine(stdout,                        \
                              logLevelNames[LOG_LEVEL_INFO], \
                              LOG_TAG,                       \
                              __LINE__,                      \
                              colorCodes[LOG_LEVEL_INFO],    \
                              0, ##__VA_ARGS__)

/**
 * @brief Error log
 */
#define ERROR_LOG(...) LogLine(stdout,                         \
                               logLevelNames[LOG_LEVEL_ERROR], \
                               LOG_TAG,                        \
                               __LINE__,                       \
                               colorCodes[LOG_LEVEL_ERROR],    \
                               0, ##__VA_ARGS__)

/**
 * @brief Warning log
 */
#define WARN_LOG(...) LogLine(stdout,                        \
                              logLevelNames[LOG_LEVEL_WARN], \
                              LOG_TAG,                       \
                              __LINE__,                      \
                              colorCodes[LOG_LEVEL_WARN],    \
                              0, ##__VA_ARGS__)

/**
 * @brief Print Available Log Levels
 *
 * @param name Name of the environment variable
 */
void PrintAvaialbleLogs(const char *name)
{
    char stringData[LOG_MAX_LEVEL * 2] = {0};
    unsigned char i;
    for (i = (unsigned char)(LOG_LEVEL_OFF);
         i <= (unsigned char)(LOG_MAX_LEVEL)-2; i++)
    {
        // Log Levels
        stringData[2 * i] = 48 + i;
        stringData[2 * i + 1] = ' ';
    }
    stringData[2 * i] = 'P';
    // Log Level for Profiling
    INFO_LOG("Available values for %s are: %s", name, stringData);
}

/**
 * @brief Function to initalize the mutex
 * for avoiding interleaved messages
 *
 * @return int 0 -> Success, -1 -> Failure
 */
int InitalizeMutex()
{
    if (pthread_mutex_init(&s_logMutex, NULL) != 0)
    {
        ERROR_LOG("Mutex initalization failed.");
        return -1;
    }

    // Set the flag
    gIsMutexInitalized = 1;

    return 0;
}

/**
 * @brief Function to initalize the log file with respective to the stream
 *
 * @param stream current selected stream
 * @param filepath filepath to save the log
 * @return true
 * @return false
 */
unsigned char InitalizeLogFile(FILE *stream, const char *filepath)
{
    unsigned char isInitalized = 1;
    FILE *fp = freopen(filepath, "w", stream);
    if (!fp)
    {
        ERROR_LOG("Failed to open file %s for writing", filepath);
        isInitalized = 0;
    }
    return isInitalized;
}

static inline void LogLineArgs(FILE *stream,
                               const char *logLevelName,
                               const char *logTag,
                               unsigned int lineNum,
                               const char *colorCode,
                               unsigned char isSavingToFile,
                               va_list args,
                               const char *format)
{
    static char dateTime[50];
    struct timeval currTime;

    // Get time
    gettimeofday(&currTime, NULL);

    struct tm tm = *localtime((time_t *)(&currTime.tv_sec));
    sprintf(dateTime,
#if __linux__
            "%d-%02d-%02d %02d:%02d:%02d:%06ld",
#else
            "%d-%02d-%02d %02d:%02d:%02d:%06d",
#endif // __linux__
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec,
            currTime.tv_usec);

    // To avoid interleaved messages
    if (gIsMutexInitalized)
    {
        pthread_mutex_lock(&s_logMutex);
    }

    // if saving to file remove color codes
    if (isSavingToFile)
    {
        // remove the color codes
        fprintf(stream,
                "[%s]:[%s] [%s:%d] ",
                dateTime,
                logLevelName,
                logTag,
                lineNum);
        vfprintf(stream, format, args);
        vfprintf(stream, "\n", args);
    }
    else
    {
        fprintf(stream,
                "%s[%s]:[%s] [%s:%d] ",
                colorCode,
                dateTime,
                logLevelName,
                logTag,
                lineNum);
        vfprintf(stream, format, args);
        vfprintf(stream, "\033[1;0m\n", args);
    }

    // To avoid interleaved messages
    if (gIsMutexInitalized)
    {
        pthread_mutex_unlock(&s_logMutex);
    }
}

static inline void LogLine(FILE *stream,
                           const char *logLevelName,
                           const char *logTag,
                           unsigned int lineNum,
                           const char *colorCode,
                           unsigned char isSavingToFile,
                           const char *format,
                           ...)
{
    va_list args;
    va_start(args, format);
    LogLineArgs(stream,
                logLevelName,
                logTag,
                lineNum,
                colorCode,
                isSavingToFile,
                args,
                format);
    va_end(args);
}

void UniLogger_SetLogLevel(enum LogLevel level)
{
    // initalize the stream
    gCurrLogStream = stdout;

    // initalize the mutex
    if (!gIsMutexInitalized)
    {
        if (0 != InitalizeMutex())
        {
            ERROR_LOG("Failed to initalize mutex");
        }
    }

    // If Already Initalized, Return
    if (gIsLogLevelInitalized)
        return;

    // Read the Environment variable
    const char *envName = "LOG_LEVEL";
    const char *envVarData = getenv(envName);

    if (envVarData == NULL)
    {
        INFO_LOG("Environment variable \"%s\" is not available.", envName);
        gCurrLogLevel = level;
        if (gCurrLogLevel == LOG_LEVEL_PROFILE)
        {
            INFO_LOG("Setting Log Level to Profile");
        }
        else
        {
            INFO_LOG("Setting Log Level to %d", (unsigned char)(gCurrLogLevel));
        }
    }
    else
    {
        INFO_LOG("Environment variable \"%s\" is set to %s", envName, envVarData);

        // Check the Size of the Environment variable (it should be 1)
        size_t envVarSize = strlen(envVarData);
        if (envVarSize != 1)
        {
            ERROR_LOG("Invalid Environment variable Value (%s) passed", envVarData);
            // Avaialble Logs
            PrintAvaialbleLogs(envName);
            gCurrLogLevel = LOG_LEVEL_OFF;
            INFO_LOG("Setting Log Level to %d", (unsigned char)(gCurrLogLevel));
            return;
        }
        else
        {
            // Check the Character in LOG_LEVEL
            const unsigned char logLevel = envVarData[0];
            // '0' to (LOG_MAX_LEVEL - 2) - 48 to -
            // 'P' for Profile Log Level
            if ((logLevel < 48 || logLevel > (48 + (LOG_MAX_LEVEL - 2))) && (logLevel != 'P'))
            {
                ERROR_LOG("Invalid Environment variable Value (%s) passed", envVarData);
                PrintAvaialbleLogs(envName);
                gCurrLogLevel = LOG_LEVEL_OFF;
                INFO_LOG("Setting Log Level to %d", (unsigned char)(gCurrLogLevel));
                return;
            }

            if (logLevel == 'P')
            {
                gCurrLogLevel = LOG_LEVEL_PROFILE;
                INFO_LOG("Setting Log Level to Profile");
            }
            else
            {
                gCurrLogLevel = (enum LogLevel)(logLevel - 48);
                INFO_LOG("Setting Log Level to %d", (unsigned char)(gCurrLogLevel));
            }
        }
    }

    // Set the Flag for Initalize
    gIsLogLevelInitalized = 1;

    return;
}

void UniLogger_SetLogStream(enum LogStream stream)
{
    // default value of strea,
    gCurrLogStream = stdout;

    // initalize the mutex
    if (!gIsMutexInitalized)
    {
        if (0 != InitalizeMutex())
        {
            ERROR_LOG("Failed to initalize mutex");
        }
    }

    // Return if already Intialized
    if (gIsLogStreamInitalized)
        return;

    // Read the Environment variable
    const char *envName = "LOG_STREAM";
    const char *envVarData = getenv(envName);

    if (envVarData == NULL)
    {
        char *streamName = "stdout";
        // Set the Log Stream
        if (STREAM_STDOUT == stream)
        {
            gCurrLogStream = stdout;
            streamName = "stdout";
        }
        else if (STREAM_STDERR == stream)
        {
            gCurrLogStream = stderr;
            streamName = "stderr";
        }
        else
        {
            // unknown log stream
            gCurrLogStream = stdout;
        }

        INFO_LOG("Environment variable \"%s\" is not available", envName);
        INFO_LOG("Setting Log Stream to %s", streamName);
    }
    else
    {
        INFO_LOG("Environment variable \"%s\" is set to %s", envName, envVarData);

        // Check the Size of the Environment variable (it should be 1)
        size_t envVarSize = strlen(envVarData);
        if (envVarSize != 1)
        {
            ERROR_LOG("Invalid Environment variable Value (%s) passed", envVarData);
            // Avaialble Logs Stream
            INFO_LOG("Available values for Log Stream are: 0 and 1");
            gCurrLogStream = stdout;
            INFO_LOG("Setting Log Stream to stdout");
            return;
        }
        else
        {
            // stream name
            char *streamName = "stdout";

            // Check the Character in LOG_STREAM
            const unsigned char logStream = envVarData[0];
            // '0' and '1'
            if (48 == logStream)
            {
                gCurrLogStream = stdout;
                streamName = "stdout";
            }
            else if (49 == logStream)
            {
                gCurrLogStream = stderr;
                streamName = "stderr";
            }
            else
            {
                ERROR_LOG("Invalid Environment variable Value (%s) passed", envVarData);
                // Avaialble Logs Stream
                INFO_LOG("Available values for Log Stream are: 0 and 1");
                gCurrLogStream = stdout;
                streamName = "stdout";
            }
            LOG_INFO("Setting Log Stream to %s", streamName);
        }
    }

    // Set the Flag for Initalize
    gIsLogStreamInitalized = 1;

    return;
}

void UniLogger_SetLogFile(const char *filepath)
{
    // initalize the mutex
    if (!gIsMutexInitalized)
    {
        if (0 != InitalizeMutex())
        {
            ERROR_LOG("Failed to initalize mutex");
        }
    }

    if (gIsLogLevelInitalized && gIsLogStreamInitalized)
    {
        // Return if already initalized
        if (gIsLogFileInitalized)
        {
            return;
        }

        // Read the Environment variable
        const char *envName = "LOG_FILE";
        const char *envVarData = getenv(envName);

        // Check if the Environment variable is set
        if (NULL == envVarData)
        {
            INFO_LOG("Environment variable \"%s\" is not available", envName);

            // Check if the filepath passes is null
            if (NULL == filepath)
            {
                // Defaulting to logger.log
                WARN_LOG("Found NULL in filepath, Defaulting to logger.log");
                gIsLogFileInitalized = InitalizeLogFile(gCurrLogStream, "logger.log");
            }
            else
            {
                // Save to the respective file
                INFO_LOG("Saving Logs to file (%s)", filepath);
                gIsLogFileInitalized = InitalizeLogFile(gCurrLogStream, filepath);
            }
            return;
        }
        else
        {
            // Save to the Environment variable file
            INFO_LOG("Environment variable \"%s\" is set to %s", envName, envVarData);
            INFO_LOG("Saving Logs to file (%s)", envVarData);
            gIsLogFileInitalized = InitalizeLogFile(gCurrLogStream, envVarData);
            return;
        }
    }
    else
    {
        // Function Needs to be called after UniLogger_SetLogLevel() and UniLogger_SetLogStream()
        // Reason: File needs to created based on the LogStream
        ERROR_LOG("Please call the function UniLogger_SetLogFile() after UniLogger_SetLogLevel() and UniLogger_SetLogStream()");
    }

    return;
}

void UniLogger_CustomLogFn(enum LogLevel level, const char *logTag, unsigned int lineNum, const char *format, ...)
{
    if (!gCurrLogStream)
    {
        gCurrLogStream = stdout;
    }

    if (LOG_LEVEL_PROFILE == gCurrLogLevel)
    {
        if (LOG_LEVEL_PROFILE == level)
        {
            // print profile logs and return
            va_list args;
            va_start(args, format);
            LogLineArgs(gCurrLogStream,
                        logLevelNames[(unsigned char)level],
                        logTag,
                        lineNum,
                        colorCodes[(unsigned char)(level)],
                        gIsLogFileInitalized,
                        args,
                        format);
            va_end(args);
            return;
        }
    }
    else
    {
        // Check if the log level is greater than Enabled Log Level
        // If greater, return. as it is not required to print
        if (level > gCurrLogLevel)
        {
            return;
        }

        va_list args;
        va_start(args, format);
        LogLineArgs(gCurrLogStream,
                    logLevelNames[(unsigned char)level],
                    logTag,
                    lineNum,
                    colorCodes[(unsigned char)(level)],
                    gIsLogFileInitalized,
                    args,
                    format);
        va_end(args);
        return;
    }
}

void UniLogger_CloseLogger()
{
    if (gIsMutexInitalized)
    {
        // Destroy the mutex
        pthread_mutex_destroy(&s_logMutex);
    }

    // close the file if opened
    if (gIsLogFileInitalized)
    {
        fclose(gCurrLogStream);
    }

    if (gIsLogLevelInitalized)
    {
        // Reset the values
        gIsLogLevelInitalized = 0;
        gCurrLogLevel = LOG_LEVEL_OFF;
    }

    if (gIsLogStreamInitalized)
    {
        // Reset the values
        gIsLogStreamInitalized = 0;
        gCurrLogStream = stdout;
    }

    return;
}