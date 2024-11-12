<h1 style="text-align: center;">Cpp Logger - User Guide</h1>

## User Guide

**APIs**
 - **UniLogger_SetLogLevel()**            - To set the Log Level for Logging
 - **UniLogger_SetLogStream()**           - To set the Log Stream type (stdout / stderr)
 - **UniLogger_SetLogFile()**             - To set the Log file for saving the logs
 - **LOG_FATAL()**              - To print fatal logs (LOG_LEVEL = 1)
 - **LOG_ERROR()**              - To print error logs (LOG_LEVEL = 2)
 - **LOG_WARN()**               - To print warning logs (LOG_LEVEL = 3)
 - **LOG_INFO()**               - To print information logs (LOG_LEVEL = 4)
 - **LOG_DEBUG()**              - To print debug logs (LOG_LEVEL = 5)
 - **LOG_TRACE()**              - To print trace logs (LOG_LEVEL = 6)
 - **LOG_PROFILE()**            - To print profile logs (LOG_LEVEL = P)
  
**Enumerations**
 - LogLevel
   - LOG_LEVEL_OFF        - For No Logs
   - LOG_LEVEL_FATAL      - For Fatal Logs
   - LOG_LEVEL_ERROR      - For Logs upto Error
   - LOG_LEVEL_WARN       - For Logs upto Warning
   - LOG_LEVEL_INFO       - For Logs upto Information
   - LOG_LEVEL_DEBUG      - For Logs upto Debug
   - LOG_LEVEL_TRACE      - For Logs upto Trace
   - LOG_LEVEL_PROFILE    - For only Profile Logs
   - LOG_MAX_LEVEL  - Maxmum Log Levels
 - LogStream
   - STREAM_STDOUT        - For stdout stream prints
   - STREAM_STDERR        - For stderr stream prints
  
## Usage

1. **UniLogger_SetLogLevel()**
   1. Use this API to set the Log Level for Logging prints
   2. This API must be used in order to use the Environment variable `LOG_LEVEL` to get affect at runtime
   3. Environment Variable `LOG_LEVEL` if available, Log level will be setted to the value of `LOG_LEVEL` else the value passed to `UniLogger_SetLogLevel` will be used.
   4. Available Values for `LOG_LEVEL` are: 0, 1, 2, 3, 4, 5, 6, P
   5. Environment Variable `LOG_LEVEL` can be set using: `export LOG_LEVEL=0`
   6. This API must be called only once in the main function

   Example:
   ```
   #include <UniLogger.h>

   int main()
   {
      UniLogger_SetLogLevel(LOG_LEVEL_PROFILE);
      return 0;
   }
   ```


2. **UniLogger_SetLogStream()**
   1. Use this API to set the Log Stream for Logging
   2. This API must be used in order to use the Environment Variable `LOG_STREAM` to get affect at runtime.
   3. Envirnoment Variable `LOG_STREAM` if available, Log stream will be setted to the value of `LOG_STREAM` else the value passes to `UniLogger_SetLogStream` will be used.
   4. Available values for `LOG_STREAM` are: 0 (stdout), 1 (stderr)
   5. Environment Variable `LOG_STREAM` can be set using `export LOG_STREAM=0`
   6. This API must be called only once in the main function
   
   Example:
   ```
   #include <UniLogger.h>

   int main()
   {
      UniLogger_SetLogStream(STREAM_STDOUT);
      return 0;
   }
   ```

3. **UniLogger_SetLogFile()**
   1. Use this API to set the Log File for saving the logs
   2. This API must be used in order to use the Environment variable `LOG_FILE` to get affect at runtime
   3. Environment Variable `LOG_FILE` if available, Log file will used as the value of `LOG_FILE` else the value passed to `UniLogger_SetLogFile` will be used.
   4. Environment Variable `LOG_FILE` can be set using: `export LOG_FILE=logger.log`
   5. This API must be called only once in main function

    Example:
    ```
    #include <UniLogger.h>

   int main()
   {
      UniLogger_SetLogFile("logfile.log");
      return 0;
   }
    ```


## Test Example Cpp Without Saving File

```
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

   return 0;
}
```

## Test Example Cpp With Saving File

```
#include <iostream>

// UniLogger Includes
#include <UniLogger.h>

int main(int argc, char const *argv[])
{
   // Set the Log level
   UniLogger_SetLogLevel(LOG_LEVEL_TRACE);
   // Set the stream type
   UniLogger_SetLogStream(STREAM_STDOUT);
   // Set the log file path
   UniLogger_SetLogFile("logger.log");

   LOG_FATAL("Fatal logs");
   LOG_ERROR("Error logs");
   LOG_WARN("Warning logs");
   LOG_INFO("Information logs");
   LOG_DEBUG("Debug logs");
   LOG_TRACE("Trace logs");
   LOG_PROFILE("Profile logs");

   return 0;
}
```

## Test Example C Without Saving File

```
#include <stdio.h>

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

   return 0;
}
```

## Test Example C With Saving File

```
#include <stdio.h>

// UniLogger Includes
#include <UniLogger.h>

int main(int argc, char const *argv[])
{
   // Set the Log level
   UniLogger_SetLogLevel(LOG_LEVEL_TRACE);
   // Set the stream type
   UniLogger_SetLogStream(STREAM_STDOUT);
   // Set the log file path
   UniLogger_SetLogFile("logger.log");

   LOG_FATAL("Fatal logs");
   LOG_ERROR("Error logs");
   LOG_WARN("Warning logs");
   LOG_INFO("Information logs");
   LOG_DEBUG("Debug logs");
   LOG_TRACE("Trace logs");
   LOG_PROFILE("Profile logs");

   return 0;
}
```