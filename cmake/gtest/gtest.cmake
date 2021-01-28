
# Download and unpack googletest at configure time
configure_file(${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . RESULT_VARIABLE result1 WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
execute_process(COMMAND ${CMAKE_COMMAND} --build . RESULT_VARIABLE result2 WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)
if(result1 OR result2)
	message(FATAL_ERROR "Preparing googletest failed: ${result1} ${result2}")
endif()

# Add googletest, defines gtest and gtest_main targets
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src ${CMAKE_CURRENT_BINARY_DIR}/googletest-build EXCLUDE_FROM_ALL)

# Remove visibility.h from the compile flags for gtest because of poisoned exit()
get_target_property(GTEST_COMPILE_FLAGS gtest COMPILE_OPTIONS)
list(REMOVE_ITEM GTEST_COMPILE_FLAGS "-include")
list(REMOVE_ITEM GTEST_COMPILE_FLAGS "visibility.h")
set_target_properties(gtest PROPERTIES COMPILE_OPTIONS "${GTEST_COMPILE_FLAGS}")
