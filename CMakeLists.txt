cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

list(APPEND CMAKE_MODULE_PATH ${SOURCE_DIR}/cmake)


#set the project name
set(project_name embedded_project_template)
project(project_name CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#=============================================================================
# doxygen
#
include(doxygen/doxygen)

#=============================================================================
# testing
#
enable_testing()
include(gtest/gtest)
add_subdirectory(test)
