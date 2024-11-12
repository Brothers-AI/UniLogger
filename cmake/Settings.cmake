#
# @file CMakeLists.txt
# @author Brothers.AI (brothers.ai.local@gmail.com)
# @brief CMake for Logger Library
# @version 0.1
# @date 2024-11-12
#
cmake_minimum_required(VERSION 3.1)

# UniLogger Directory
set(UNI_LOGGER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/UniLogger)

# Logger Examples Directory
set(UNI_LOGGER_EXAMPLES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Examples)

# Project Binary Directory
# Library Directory
set(PROJECT_LIBRARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Binary / Executable Directory
set(PROJECT_EXE_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Examples executable directory
set(PROJECT_EXAMPLES_EXE_DIR ${PROJECT_EXE_DIR}/Examples)
