# 
# @file CMakeLists.txt
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief CMake for Logger test app
# @version 0.1
# @date 2024-01-25
# 
cmake_minimum_required(VERSION 3.1)

# Setting Cmake
include(${CMAKE_SOURCE_DIR}/cmake/Settings.cmake)

# Project
project(ExamplesUniLogger)

# Create Directory
file(MAKE_DIRECTORY ${PROJECT_EXAMPLES_EXE_DIR})

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

# Copy Binary to install directory
install(DIRECTORY ${PROJECT_EXAMPLES_EXE_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})