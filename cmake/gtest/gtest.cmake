#=============================================================================
# Testing - Automatic unit and integration testing with CTest
#

# optionally enable cmake testing (supported only on posix)
configure_file(${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in External/googletest/googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . 
  RESULT_VARIABLE     result
  WORKING_DIRECTORY   ${BINARY_DIR}/External/googletest/googletest-download 
  OUTPUT_QUIET
)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build . 
  RESULT_VARIABLE     result
  WORKING_DIRECTORY   ${BINARY_DIR}/External/googletest/googletest-download 
  OUTPUT_QUIET
)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/External/googletest/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/External/googletest/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${googletest_SOURCE_DIR}/include")
endif()