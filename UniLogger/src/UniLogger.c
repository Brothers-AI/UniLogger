// System Include
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>

#include <UniLogger.h>

// Global Variables

// Current Log Level, Default to Off
enum LogLevel gCurrLogLevel = LOG_LEVEL_OFF;
// Flag to Check Environment Variable for Log Level is Read or not
unsigned char gIsLogLevelInitalized = 0;

// Current Log Stream, Default to stdout
enum LogStream gCurrLogStream = STREAM_STDOUT;
// Flag to Check Environment Variable for Log Stream is Read or not
unsigned char gIsLogStreamInitalized = 0;

// Flag to Check is Log File Initalized, Default to 0
unsigned char gIsLogFileInitalized = 0;

/**
 * @brief Log level names
 */
const char logLevelNames[LOG_MAX_LEVEL][10] = {
    "FATAL",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
    "TRACE",
    "PROFILE"};

/**
 * @brief Color Codes for Different Log Levels
 */
const char colorCodes[LOG_MAX_LEVEL][10] = {
            "\033[1;31m",
            "\033[0;31m",
            "\033[0;33m",
            "\033[0;32m",
            "\033[0;36m",
            "\033[0;35m",
            "\033[0;32m"};

/**
 * @brief Print Available Log Levels
 */
void printAvaialbleLogs()
{
    printf("Available Values are: ");
    for (unsigned char i = (unsigned char)(LOG_LEVEL_OFF);
            i <= (unsigned char)(LOG_MAX_LEVEL) - 2; i++)
    {
        // Log Levels
        printf("%d, ", i);
    }
    // Log Level for Profiling
    printf("P\n");
}

/**
 * @brief Function to initalize the log file with respective to the stream
 * 
 * @param stream current selected stream
 * @param filepath filepath to save the log
 * @return true 
 * @return false 
 */
unsigned char initalizeLogFile(enum LogStream stream, const char *filepath)
{
    unsigned char isInitalized = 1;
    if (STREAM_STDOUT == stream)
    {
        // Redirect stdout to file
        FILE *fp = freopen(filepath, "w", stdout);
        if (!fp)
        {
            printf("Failed to open file %s for writing\n", filepath);
            isInitalized = 0;
        }
    }
    else if (STREAM_STDERR == stream)
    {
        // Redirect stderr to file
        FILE *fp = freopen(filepath, "w", stderr);
        if (!fp)
        {
            printf("Failed to open file %s for writing\n", filepath);
            isInitalized = 0;
        }
    }
    else
    {
        printf("Not Implemented for Stream: %d\n", (unsigned char)(stream));
        isInitalized = 0;
    }
    return isInitalized;
}

/**
 * @brief Function to Print log on Console
 * 
 * @param stream Stream type (stdout or stderr) [Logger::LogStream]
 * @param logLevelName name of the log level
 * @param colorCode color code for the log level
 * @param format print format
 * @param args print arguments
 */
void printLog(const char *logLevelName, const char *logTag, const char *colorCode, const char *format, va_list args, unsigned char isSavingToFile)
{
    char dateTime[30];
    struct timeval currTime;

    // Get time
    gettimeofday(&currTime, NULL);

    // Get Milliseconds time
    int milliSeconds = currTime.tv_usec / 1000;

    struct tm tm = *localtime((time_t *)(&currTime.tv_sec));
    sprintf(dateTime, "%d-%02d-%02d %02d:%02d:%02d:%03d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, milliSeconds);

    if (STREAM_STDOUT == gCurrLogStream)
    {
        // Output Stream in stdout
        if (isSavingToFile)
        {
            // Remove the color codes from the string
            fprintf(stdout, "[%s]:[%s]:[%s] ", dateTime, logLevelName, logTag);
            vfprintf(stdout, format, args);
            vfprintf(stdout, "\n", args);
        }
        else
        {
            fprintf(stdout, "%s[%s]:[%s]:[%s] ", colorCode, dateTime, logLevelName, logTag);
            vfprintf(stdout, format, args);
            vfprintf(stdout, "\033[1;0m\n", args);
        }
    }
    else if (STREAM_STDERR == gCurrLogStream)
    {
        // Output Stream in stderr
        if (isSavingToFile)
        {
            // Remove the color codes from the string
            fprintf(stderr, "[%s]:[%s]:[%s] ", dateTime, logLevelName, logTag);
            vfprintf(stderr, format, args);
            vfprintf(stderr, "\n", args);
        }
        else
        {
            fprintf(stderr, "%s[%s]:[%s]:[%s] ", colorCode, dateTime, logLevelName, logTag);
            vfprintf(stderr, format, args);
            vfprintf(stderr, "\033[1;0m\n", args);
        }
    }
}

void setLogLevel(enum LogLevel level)
{
    // If Already Initalized, Return
    if (gIsLogLevelInitalized)
        return;
    
    // Read the Environment Variable
    const char *envName = "LOG_LEVEL";
    const char *envVarData = getenv(envName);

    if (envVarData == NULL)
    {
        printf("Environment Variable \"%s\" is not available.\n", envName);
        gCurrLogLevel = level;
        if (gCurrLogLevel == LOG_LEVEL_PROFILE)
            printf("Setting Log Level to Profile\n");
        else
            printf("Setting Log Level to %d\n", (unsigned char)(gCurrLogLevel));
    }
    else
    {
        printf("Environment Variable \"%s\" is set to %s\n", envName, envVarData);

        // Check the Size of the Environment Variable (it should be 1)
        size_t envVarSize = strlen(envVarData);
        if (envVarSize != 1)
        {
            printf("Invalid Environment Variable Value (%s) passed\n", envVarData);
            // Avaialble Logs
            printAvaialbleLogs();
            gCurrLogLevel = LOG_LEVEL_OFF;
            printf("Setting Log Level to %d\n", (unsigned char)(gCurrLogLevel));
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
                printf("Invalid Environment Variable Value (%s) passed\n", envVarData);
                printAvaialbleLogs();
                gCurrLogLevel = LOG_LEVEL_OFF;
                printf("Setting Log Level to %d\n", (unsigned char)(gCurrLogLevel));
                return;
            }

            if (logLevel == 'P')
            {
                gCurrLogLevel = LOG_LEVEL_PROFILE;
                printf("Setting Log Level to Profile\n");
            }
            else
            {
                gCurrLogLevel = (enum LogLevel)(logLevel - 48);
                printf("Setting Log Level to %d\n", (unsigned char)(gCurrLogLevel));
            }
        }
    }

    // Set the Flag for Initalize
    gIsLogLevelInitalized = 1;

    return;
}

void setLogStream(enum LogStream stream)
{
    // Return if already Intialized
    if (gIsLogStreamInitalized)
        return;
    
    // Read the Environment Variable
    const char *envName = "LOG_STREAM";
    const char *envVarData = getenv(envName);

    if (envVarData == NULL)
    {
        printf("Environment Variable \"%s\" is not available\n", envName);

        // Set the Log Stream
        gCurrLogStream = stream;

        printf("Setting Log Stream to %d\n", (unsigned char)(gCurrLogStream));
    }
    else
    {
        printf("Environment Variable \"%s\" is set to %s\n", envName, envVarData);

        // Check the Size of the Environment Variable (it should be 1)
        size_t envVarSize = strlen(envVarData);
        if (envVarSize != 1)
        {
            printf("Invalid Environment Variable Value (%s) passed\n", envVarData);
            // Avaialble Logs Stream
            printf("Available Log Stream are: 0 and 1\n");
            gCurrLogStream = STREAM_STDOUT;
            printf("Setting Log Stream to %d\n", (unsigned char)(gCurrLogStream));
            return;
        }
        else
        {
            // Check the Character in LOG_STREAM
            const unsigned char logStream = envVarData[0];
            // '0' and '1'
            if (logStream < 48 && logStream > 49)
            {
                printf("Invalid Environment Variable Value (%s) passed\n", envVarData);
                // Avaialble Logs Stream
                printf("Available Log Stream are: 0 and 1\n");
                gCurrLogStream = STREAM_STDOUT;
                printf("Setting Log Stream to %d\n", (unsigned char)(gCurrLogStream));
                return;
            }

            gCurrLogStream = (enum LogStream)(logStream - 48);
            printf("Setting Log Stream to %d\n", (unsigned char)(gCurrLogStream));
        }
    }

    // Set the Flag for Initalize
    gIsLogStreamInitalized = 1;

    return;
}

void setLogFile(const char *filepath)
{
    if (gIsLogLevelInitalized && gIsLogStreamInitalized)
    {
        // Return if already initalized
        if (gIsLogFileInitalized)
            return;
        
        // Read the Environment Variable
        const char *envName = "LOG_FILE";
        const char *envVarData = getenv(envName);

        // Check if the Environment variable is set
        if (NULL == envVarData)
        {
            printf("Environment Variable \"%s\" is not available\n", envName);

            // Check if the filepath passes is null
            if (NULL == filepath)
            {
                // Defaulting to logger.log
                printf("Found NULL in filepath, Defaulting to logger.log");
                gIsLogFileInitalized = initalizeLogFile(gCurrLogStream, "logger.log");
            }
            else
            {
                // Save to the respective file
                printf("Saving Logs to file (%s)\n", filepath);
                gIsLogFileInitalized = initalizeLogFile(gCurrLogStream, filepath);
            }
            return;
        }
        else
        {
            // Save to the Environment variable file
            printf("Environment Variable \"%s\" is set to %s\n", envName, envVarData);
            printf("Saving Logs to file (%s)\n", envVarData);
            gIsLogFileInitalized = initalizeLogFile(gCurrLogStream, envVarData);
            return;
        }
    }
    else
    {
        // Function Needs to be called after setLogLevel() and setLogStream()
        // Reason: File needs to created based on the LogStream
        printf("Please call the function setLogFile() after setLogLevel() and setLogStream()\n");
    }

    return;
}

void logCustom(enum LogLevel level, const char *logTag, const char *format, ...)
{
    if (LOG_LEVEL_PROFILE == gCurrLogLevel)
    {
        if (LOG_LEVEL_PROFILE == level)
        {
            // print profile logs and return
            va_list args;
            va_start(args, format);
            printLog(logLevelNames[(unsigned char)level - 1], logTag, colorCodes[(unsigned char)(level) - 1], format, args, gIsLogFileInitalized);
            va_end(args);
            return;
        }
    }
    else
    {
        // Check if the log level is greater than Enabled Log Level
        // If greater, return. as it is not required to print
        if (level > gCurrLogLevel)
            return;
        
        va_list args;
        va_start(args, format);
        printLog(logLevelNames[(unsigned char)level - 1], logTag, colorCodes[(unsigned char)(level) - 1], format, args, gIsLogFileInitalized);
        va_end(args);
        return;
    }
}