cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

list(APPEND CMAKE_MODULE_PATH ${SOURCE_DIR}/cmake)
include(parse_function_args)

#=============================================================================
# git
#
include(add_git_submodule)

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
# configuration
#

set(CONFIG "stm_nucleo_h743zi_default.cmake" CACHE STRING "desired configuration")
#set(CONFIG "px4_fmu-v5_default.cmake" CACHE STRING "desired configuration")

include(add_module)
set(config_module_list)

include(add_config)
include(add_board)
include(${CONFIG_FILE})
message(STATUS "config: ${CONFIG}")
message(STATUS "platform: ${PLATFORM}")


# external modules
set(EXTERNAL_MODULES_LOCATION "" CACHE STRING "External modules source location")

if(NOT EXTERNAL_MODULES_LOCATION STREQUAL "")
	get_filename_component(EXTERNAL_MODULES_LOCATION "${EXTERNAL_MODULES_LOCATION}" ABSOLUTE)
endif()

set_property(GLOBAL PROPERTY MODULE_CONFIG_FILES)

include(platforms/${PLATFORM}/cmake/impl_os.cmake)
list(APPEND CMAKE_MODULE_PATH ${SOURCE_DIR}/platforms/${PLATFORM}/cmake)

if(EXISTS "${SOURCE_DIR}/platforms/${PLATFORM}/cmake/init.cmake")
	include(init)
endif()

# CMake build type (Debug Release RelWithDebInfo MinSizeRel Coverage)
if(NOT CMAKE_BUILD_TYPE)
	if(${PLATFORM} STREQUAL "nuttx")
		set(PROJECT_BUILD_TYPE "MinSizeRel")
	else()
		set(PROJECT_BUILD_TYPE "RelWithDebInfo")
	endif()

	set(CMAKE_BUILD_TYPE ${PROJECT_BUILD_TYPE} CACHE STRING "Build type" FORCE)
endif()

if((CMAKE_BUILD_TYPE STREQUAL "Debug") OR (CMAKE_BUILD_TYPE STREQUAL "Coverage"))
	set(MAX_CUSTOM_OPT_LEVEL -O0)
elseif(CMAKE_BUILD_TYPE MATCHES "Sanitizer")
	set(MAX_CUSTOM_OPT_LEVEL -O1)
else()
	if(constrained_flash_build)
		set(MAX_CUSTOM_OPT_LEVEL -Os)
	else()
		set(MAX_CUSTOM_OPT_LEVEL -O2)
	endif()
endif()

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel;Coverage;AddressSanitizer;UndefinedBehaviorSanitizer")
message(STATUS "cmake build type: ${CMAKE_BUILD_TYPE}")

#=============================================================================
# project definition
#
set(project_name embedded_project_template)
project(${project_name} CXX C ASM)

set(project_contact "andres.sanchez.engineering@gmail.com")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#=============================================================================
# find programs and packages
#
# Python
# If using catkin, Python 2 is found since it points
# to the Python libs installed with the ROS distro
if (NOT CATKIN_DEVEL_PREFIX)
	find_package(PythonInterp 3)
	# We have a custom error message to tell users how to install python3.
	if (NOT PYTHONINTERP_FOUND)
		message(FATAL_ERROR "Python 3 not found. Please install Python 3:\n"
			"    Ubuntu: sudo apt install python3 python3-dev python3-pip\n"
			"    macOS: brew install python")
	endif()
else()
	find_package(PythonInterp REQUIRED)
endif()

option(PYTHON_COVERAGE "Python code coverage" OFF)
if(PYTHON_COVERAGE)
	message(STATUS "python coverage enabled")
	set(PYTHON_EXECUTABLE coverage run -p)
endif()

#=============================================================================
# get chip and chip manufacturer
#
os_determine_build_chip()
if(NOT CHIP_MANUFACTURER)
	message(FATAL_ERROR "os_determine_build_chip() needs to set CHIP_MANUFACTURER")
endif()
if(NOT CHIP)
	message(FATAL_ERROR "os_determine_build_chip() needs to set CHIP")
endif()

#=============================================================================
# build flags
#
include(add_common_flags)
add_common_flags()
os_add_flags()

#=============================================================================
# board cmake init (optional)
#
if(EXISTS ${BOARD_DIR}/cmake/init.cmake)
	include(${BOARD_DIR}/cmake/init.cmake)
endif()

#=============================================================================
# subdirectories
#
# add libraries 
include(add_custom_library)
add_subdirectory(src/lib EXCLUDE_FROM_ALL)

#add_subdirectory(platforms/${PLATFORM}/src/px4)
#add_subdirectory(platforms EXCLUDE_FROM_ALL)
#add_subdirectory(src/modules/uORB EXCLUDE_FROM_ALL) # TODO: platform layer

if(EXISTS "${BOARD_DIR}/CMakeLists.txt")
	add_subdirectory(${BOARD_DIR})
endif()

foreach(module ${config_module_list})
	add_subdirectory(src/${module})
endforeach()

# must be the last module before firmware
#add_subdirectory(src/lib/parameters EXCLUDE_FROM_ALL)
#target_link_libraries(parameters_interface INTERFACE parameters)

# firmware added last to generate the builtin for included modules
add_subdirectory(platforms/${PLATFORM})


#=============================================================================
# doxygen
#
include(doxygen/doxygen)

#=============================================================================
# testing
#
enable_testing()
#include(gtest/gtest)
#add_subdirectory(test)
