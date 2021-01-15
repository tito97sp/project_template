if(POLICY CMP0079)
	cmake_policy(SET CMP0079 NEW)
endif()

include(cygwin_cygpath)

set(NUTTX_DIR ${BINARY_DIR}/NuttX/nuttx)
set(NUTTX_APPS_DIR ${BINARY_DIR}/NuttX/apps)

add_executable(${project_name} ${SOURCE_DIR}/platforms/common/src/platform_common/empty.c)
set(FW_NAME ${BOARD_VENDOR}_${BOARD_MODEL}_${BOARD_LABEL}.elf)
set_target_properties(${project_name} PROPERTIES OUTPUT_NAME ${FW_NAME})
add_dependencies(${project_name} git_nuttx nuttx_build)

get_property(module_libraries GLOBAL PROPERTY MODULE_LIBRARIES)


# build NuttX
add_subdirectory(NuttX ${BINARY_DIR}/NuttX)

set(nuttx_libs)
set(SCRIPT_PREFIX)
if("${BOARD_LABEL}" STREQUAL "bootloader")
	set(SCRIPT_PREFIX ${BOARD_LABEL}_)
	add_subdirectory(src/bootloader)
	list(APPEND nuttx_libs
		bootloader
		bootloader_lib
		drivers_board
	)
elseif("${BOARD_LABEL}" STREQUAL "canbootloader")
	set(SCRIPT_PREFIX ${BOARD_LABEL}_)
	add_subdirectory(src/canbootloader)
	list(APPEND nuttx_libs
		canbootloader
		drivers_board
	)

	target_link_libraries(${project_name} PRIVATE
		-Wl,-wrap,sched_process_timer -Wl,-wrap,nx_sem_post -Wl,-wrap,nx_sem_wait
	)
else()
	if(NOT "${BOARD_LINKER_PREFIX}" STREQUAL "")
		set(SCRIPT_PREFIX ${BOARD_LINKER_PREFIX}-)
	endif()
endif()

list(APPEND nuttx_libs
 	nuttx_apps
 	nuttx_arch
 	nuttx_binfmt
 	nuttx_c
 	nuttx_boards
 	nuttx_xx
 	nuttx_drivers
 	nuttx_fs
 	nuttx_mm
 	nuttx_sched
 	)

if (CONFIG_NET)
	list(APPEND nuttx_libs nuttx_net)
 	target_link_libraries(nuttx_fs INTERFACE nuttx_net)
endif()

file(RELATIVE_PATH BINARY_DIR_REL ${CMAKE_CURRENT_BINARY_DIR} ${BINARY_DIR})

# only in the cygwin environment: convert absolute linker script path to mixed windows (C:/...)
# because even relative linker script paths are different for linux, mac and windows
CYGPATH(BINARY_DIR BINARY_DIR_CYG)

target_link_libraries(nuttx_arch
 	INTERFACE
 		drivers_board
# 		arch_hrt
	)

target_link_libraries(nuttx_c INTERFACE nuttx_drivers)
target_link_libraries(nuttx_xx INTERFACE nuttx_c)

target_link_libraries(${project_name} PRIVATE

	-nostartfiles
	-nodefaultlibs
	-nostdlib
	-nostdinc++

	-fno-exceptions
	-fno-rtti

	-Wl,--script=${BINARY_DIR_CYG}/NuttX/nuttx-config/scripts/${SCRIPT_PREFIX}script.ld
	-Wl,-Map=${CONFIG}.map
	-Wl,--warn-common
	-Wl,--gc-sections

	-Wl,--start-group
		${nuttx_libs}
	-Wl,--end-group

	m
	gcc
	)

if(NOT USE_LD_GOLD)
	target_link_libraries(${project_name} PRIVATE -Wl,--print-memory-usage)
endif()

target_link_libraries(${project_name} PRIVATE ${module_libraries})

if (config_romfs_root)
	add_subdirectory(${SOURCE_DIR}/ROMFS ${BINARY_DIR}/ROMFS)
	target_link_libraries(${project_name} PRIVATE romfs)
endif()

message(STATUS "Binary_dir_rel ${BINARY_DIR_REL}")

add_custom_command(
	OUTPUT ${BINARY_DIR}/${BOARD}.bin
	COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_CURRENT_BINARY_DIR}/${FW_NAME} ${BINARY_DIR_REL}/${BOARD}.bin
	DEPENDS ${project_name}
	)

add_custom_target(make_bin
	DEPENDS ${BINARY_DIR}/${BOARD}.bin
	)	




# print weak symbols
add_custom_target(weak_symbols
	COMMAND ${CMAKE_NM} $<TARGET_FILE:${project_name}> | ${GREP} " w " | cat
	DEPENDS ${project_name}
	VERBATIM
	USES_TERMINAL
)
