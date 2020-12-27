cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

list(APPEND CMAKE_MODULE_PATH ${SOURCE_DIR}/cmake)
include(parse_function_args)

#=============================================================================
# git
#
#include(px4_git)

execute_process(
	COMMAND git describe --always --tags
	OUTPUT_VARIABLE GIT_TAG
	OUTPUT_STRIP_TRAILING_WHITESPACE
	WORKING_DIRECTORY ${SOURCE_DIR}
	)
message(STATUS "Project version: ${GIT_TAG}")

define_property(GLOBAL PROPERTY MODULE_LIBRARIES
                 BRIEF_DOCS "Project module libs"
                 FULL_DOCS "List of all project module libraries"
                 )

define_property(GLOBAL PROPERTY MODULE_PATHS
                 BRIEF_DOCS "Project module paths"
                 FULL_DOCS "List of paths to all project modules"
                 )



#=============================================================================
# project definition
#
set(project_name embedded_project_template)
project(${project_name} CXX C)

set(project_contact "andres.sanchez.engineering@gmail.com")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


#=============================================================================
# configuration
#
include(add_module)
set(config_module_list)

include(add_git_submodule)

#TODO: Eliminate hardcoded variables
set(PLATFORM nuttx)
set(BOARD nucleoh743zi)
set(CONFIG_DIR ${SOURCE_DIR}/configuration)
set(CONFIG_FILE ${SOURCE_DIR}/configuration/default.cmake)
set(NUTTX_CONFIG nsh)
set(BOARD_VENDOR stm)
set(BOARD_MODEL h743zi)
set(BOARD_LABEL nucleo)


# external modules
set(EXTERNAL_MODULES_LOCATION "" CACHE STRING "External modules source location")

if(NOT EXTERNAL_MODULES_LOCATION STREQUAL "")
	get_filename_component(EXTERNAL_MODULES_LOCATION "${EXTERNAL_MODULES_LOCATION}" ABSOLUTE)
endif()

set_property(GLOBAL PROPERTY MODULE_CONFIG_FILES)

#include(platforms/${PX4_PLATFORM}/cmake/px4_impl_os.cmake)
list(APPEND CMAKE_MODULE_PATH ${SOURCE_DIR}/platforms/${PLATFORM}/cmake)

if(EXISTS "${SOURCE_DIR}/platforms/${PLATFORM}/cmake/init.cmake")
	include(init)
endif()



# include(platforms/${PLATFORM}/cmake/impl_os.cmake)
# list(APPEND CMAKE_MODULE_PATH ${SOURCE_DIR}/platforms/${PLATFORM}/cmake)

# if(EXISTS "${SOURCE_DIR}/platforms/${PLATFORM}/cmake/init.cmake")
# 	include(init)
# endif()
#include(nuttx/nuttx)
add_subdirectory(${SOURCE_DIR}/platforms/${PLATFORM})


#=============================================================================
# subdirectories
#

# add libraries 
#include(add_library)
add_subdirectory(src/lib EXCLUDE_FROM_ALL)

# add modules
list(APPEND config_module_list "hello")

foreach(module ${config_module_list})
	add_subdirectory(src/modules/${module})
endforeach()



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
