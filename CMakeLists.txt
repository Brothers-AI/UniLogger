#
# @file CMakeLists.txt
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief CMake for Logger Library
# @version 0.1
# @date 2024-01-25
#
cmake_minimum_required(VERSION 3.1)

# Project
project(UniLogger)

# Build options
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildOptions.cmake)

# settings of UniLogger
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Settings.cmake)

# Build Flags for Windows MSVC Compiler
if(CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /wd4710 /wd4711 /wd4774 /wd4820 /wd4996")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /wd4571 /wd4625 /wd4626 /wd5026 /wd5027 /wd5039")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4710 /wd4711 /wd4774 /wd4820 /wd4996")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4571 /wd4625 /wd4626 /wd5026 /wd5027 /wd5039")
endif()

# Build Library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_DIR})

set(CMAKE_C_FLAGS   "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(NOT UL_BUILD_SHARED_LIBS)
    message(STATUS "Enabling -fPIC option for static library")
    set(CMAKE_C_FLAGS   "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

# Include folders for UniLogger
include_directories(
    ${UNI_LOGGER_DIR}/include
)

# Set the Source files for UniLogger
set(SOURCE_FILES
    ${UNI_LOGGER_DIR}/src/UniLogger.c
)

# Building Shared or Static Library
if(UL_BUILD_SHARED_LIBS)
    add_library(
        ${PROJECT_NAME} SHARED
        ${SOURCE_FILES}
    )
else()
    add_library(
        ${PROJECT_NAME} STATIC
        ${SOURCE_FILES}
    )
endif()

# Building Examples
if(${UL_BUILD_EXAMPLES})
    # Set Runtime Directory
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_EXAMPLES_EXE_DIR})

    # Include Folders for test
    include_directories(
        ${UNI_LOGGER_DIR}/include
    )

    # Directories where the Library is present
    link_directories(
        ${PROJECT_LIBRARY_DIR}/
    )

    # Create Executable
    add_executable(
        testLogger
        ${UNI_LOGGER_EXAMPLES_DIR}/src/testLogger.cpp
    )

    # Linking Libraries
    target_link_libraries(
        testLogger
        UniLogger
    )

    # Create Executable
    add_executable(
        testLoggerFile
        ${UNI_LOGGER_EXAMPLES_DIR}/src/testLoggerFile.c
    )

    # Linking Libraries
    target_link_libraries(
        testLoggerFile
        UniLogger
    )

    if(${UL_BUILD_SHARED_LIBS})
        # Copy the DLL to Executable folder
        if(WIN32)
            add_custom_command(
                TARGET ${EXE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                ${PROJECT_LIBRARY_DIR}/${CMAKE_BUILD_TYPE}/UniLogger.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}
            )
        endif(WIN32)
    endif()

    # Copy Binary to install directory
    install(DIRECTORY ${PROJECT_EXE_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()

# Copy Include folder to install directory
install(DIRECTORY ${UNI_LOGGER_DIR}/include DESTINATION ${CMAKE_INSTALL_PREFIX}/)

# Copy lib folder to install directory
install(DIRECTORY ${PROJECT_LIBRARY_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})

# Summary
message(STATUS "------------------------------------------------")
message(STATUS "Configuration Summary for ${PROJECT_NAME}")
message(STATUS "------------------------------------------------")
message(STATUS "| System Name         : ${CMAKE_SYSTEM_NAME}")
message(STATUS "| System Processor    : ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "| C Compiler          : ${CMAKE_C_COMPILER}")
message(STATUS "| C++ Compiler        : ${CMAKE_CXX_COMPILER}")
message(STATUS "| C Flags             : ${CMAKE_C_FLAGS}")
message(STATUS "| C++ Flags           : ${CMAKE_CXX_FLAGS}")
message(STATUS "| C Standard          : ${CMAKE_C_STANDARD}")
message(STATUS "| CXX Standard        : ${CMAKE_CXX_STANDARD}")
message(STATUS "| Build Type          : ${CMAKE_BUILD_TYPE}")

if(UL_BUILD_SHARED_LIBS)
    set(LIBRARY_TYPE "Shared Library (.so / .dll)")
else()
    set(LIBRARY_TYPE "Static Library (.a / .lib)")
endif()

message(STATUS "| LIBRARY_TYPE        : ${LIBRARY_TYPE}")
message(STATUS "| UniLogger Directory : ${UNI_LOGGER_DIR}")
message(STATUS "| Build Examples      : ${UL_BUILD_EXAMPLES}")
message(STATUS "| Install to          : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "------------------------------------------------")
