if(POLICY CMP0079)
	cmake_policy(SET CMP0079 NEW)
endif()


set(NUTTX_DIR ${BINARY_DIR}/NuttX/nuttx)
set(NUTTX_APPS_DIR ${BINARY_DIR}/NuttX/apps)

add_executable(${project_name} ${SOURCE_DIR}/platforms/common/empty.c)
set(FW_NAME ${BOARD_VENDOR}_${BOARD_MODEL}_${BOARD_LABEL}.elf)
set_target_properties(${project_name} PROPERTIES OUTPUT_NAME ${FW_NAME})
add_dependencies(${project_name} git_nuttx nuttx_build)

get_property(module_libraries GLOBAL PROPERTY MODULE_LIBRARIES)

# build NuttX
add_subdirectory(NuttX ${BINARY_DIR}/NuttX)