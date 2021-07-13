#=============================================================================
#
#	add_board
#
#	This function creates a board.
#
#	Usage:
#		add_board(
#			PLATFORM <string>
#			VENDOR <string>
#			MODEL <string>
#			[ LABEL <string> ]
#			[ TOOLCHAIN <string> ]
#			[ ARCHITECTURE <string> ]
#			[ ROMFSROOT <string> ]
#			[ BUILD_BOOTLOADER ]
#			[ IO <string> ]
#			[ BOOTLOADER <string> ]
#			[ UAVCAN_INTERFACES <string> ]
#			[ DRIVERS <list> ]
#			[ MODULES <list> ]
#			[ SYSTEMCMDS <list> ]
#			[ EXAMPLES <list> ]
#			[ SERIAL_PORTS <list> ]
#			[ CONSTRAINED_FLASH ]
#			[ TESTING ]
#			[ LINKER_PREFIX <string> ]
#			[ EMBEDDED_METADATA <string> ]
#			[ ETHERNET ]
#			)
#
#	Input:
#		PLATFORM			: platform name (posix, nuttx, qurt)
#		VENDOR				: name of board vendor/manufacturer/brand/etc
#		MODEL				: name of board model
#		LABEL				: optional label, set to default if not specified
#		TOOLCHAIN			: cmake toolchain
#		ARCHITECTURE		: name of the CPU CMake is building for (used by the toolchain)
#		ROMFSROOT			: relative path to the ROMFS root directory
#		BUILD_BOOTLOADER	: flag to enable building and including the bootloader config
#		IO					: name of IO board to be built and included in the ROMFS (requires a valid ROMFSROOT)
#		BOOTLOADER			: bootloader file to include for flashing via bl_update (currently NuttX only)
#		UAVCAN_INTERFACES	: number of interfaces for UAVCAN
#		DRIVERS				: list of drivers to build for this board (relative to src/drivers)
#		MODULES				: list of modules to build for this board (relative to src/modules)
#		SYSTEMCMDS			: list of system commands to build for this board (relative to src/systemcmds)
#		EXAMPLES			: list of example modules to build for this board (relative to src/examples)
#		SERIAL_PORTS		: mapping of user configurable serial ports and param facing name
#		EMBEDDED_METADATA	: list of metadata to embed to ROMFS
#		CONSTRAINED_FLASH	: flag to enable constrained flash options (eg limit init script status text)
#		TESTING				: flag to enable automatic inclusion of testing modules
#		LINKER_PREFIX		: optional to prefix on the Linker script.
#		ETHERNET		: flag to indicate that ethernet is enabled
#
#
#	Example:
#		add_board(
#			PLATFORM nuttx
#			VENDOR stm
#			MODEL nucleo_h743zi
#			TOOLCHAIN arm-none-eabi
#			ARCHITECTURE cortex-m7
#			ROMFSROOT px4fmu_common
#			IO px4_io-v2_default
#			SERIAL_PORTS
#				GPS1:/dev/ttyS0
#				TEL1:/dev/ttyS1
#				TEL2:/dev/ttyS2
#				TEL4:/dev/ttyS3
#			DRIVERS
#				barometer/ms5611
#				gps
#				imu/bmi055
#				imu/mpu6000
#				magnetometer/isentek/ist8310
#				pwm_out
#				px4io
#				rgbled
#			MODULES
#				commander
#				ekf2
#				land_detector
#				mavlink
#				mc_att_control
#				mc_pos_control
#				navigator
#				sensors
#			MODULES
#				mixer
#				mtd
#				param
#				perf
#				pwm
#				reboot
#				shutdown
#				top
#				topic_listener
#				tune_control
#			)
#

function(add_board)

	parse_function_args(
		NAME add_board
		ONE_VALUE
			PLATFORM
			VENDOR
			MODEL
			LABEL
			TOOLCHAIN
			ARCHITECTURE
			ROMFSROOT
			IO
			BOOTLOADER
			UAVCAN_INTERFACES
			UAVCAN_TIMER_OVERRIDE
			LINKER_PREFIX
		MULTI_VALUE
			DRIVERS
			MODULES
			SYSTEMCMDS
			EXAMPLES
			SERIAL_PORTS
			EMBEDDED_METADATA
		OPTIONS
			BUILD_BOOTLOADER
			CONSTRAINED_FLASH
			CONSTRAINED_MEMORY
			TESTING
			ETHERNET
		REQUIRED
			PLATFORM
			VENDOR
			MODEL
		ARGN ${ARGN})

	set(BOARD_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "board directory" FORCE)
	include_directories(${BOARD_DIR}/src)

	set(BOARD ${VENDOR}_${MODEL} CACHE STRING "board" FORCE)

	# board name is uppercase with no underscores when used as a define
	string(TOUPPER ${BOARD} BOARD_NAME)
	string(REPLACE "-" "_" BOARD_NAME ${BOARD_NAME})
	set(BOARD_NAME ${BOARD_NAME} CACHE STRING "board define" FORCE)

	set(BOARD_VENDOR ${VENDOR} CACHE STRING "board vendor" FORCE)
	set(BOARD_MODEL ${MODEL} CACHE STRING "board model" FORCE)

	if(LABEL)
		set(BOARD_LABEL ${LABEL} CACHE STRING "board label" FORCE)
	else()
		set(BOARD_LABEL "default" CACHE STRING "board label" FORCE)
	endif()

	set(CONFIG "${BOARD_VENDOR}_${BOARD_MODEL}_${BOARD_LABEL}" CACHE STRING "config" FORCE)

	# set OS, and append specific platform module path
	set(PLATFORM ${PLATFORM} CACHE STRING "board OS" FORCE)
	list(APPEND CMAKE_MODULE_PATH ${SOURCE_DIR}/platforms/${PLATFORM}/cmake)

	# platform-specific include path
	include_directories(${SOURCE_DIR}/platforms/${PLATFORM}/src/px4/common/include)

	if(ARCHITECTURE)
		set(CMAKE_SYSTEM_PROCESSOR ${ARCHITECTURE} CACHE INTERNAL "system processor" FORCE)
	endif()

	if(TOOLCHAIN)
		set(CMAKE_TOOLCHAIN_FILE Toolchain-${TOOLCHAIN} CACHE INTERNAL "toolchain file" FORCE)
	endif()

	set(romfs_extra_files)
	set(config_romfs_extra_dependencies)
	if(BOOTLOADER)
		list(APPEND romfs_extra_files ${BOOTLOADER})
	endif()
	foreach(metadata ${EMBEDDED_METADATA})
		if(${metadata} STREQUAL "parameters")
			list(APPEND romfs_extra_files ${PX4_BINARY_DIR}/parameters.json.gz)
			list(APPEND romfs_extra_dependencies parameters_xml)
		else()
			message(FATAL_ERROR "invalid value for EMBEDDED_METADATA: ${metadata}")
		endif()
	endforeach()
	set(config_romfs_extra_files ${romfs_extra_files} CACHE INTERNAL "extra ROMFS files" FORCE)
	set(config_romfs_extra_dependencies ${romfs_extra_dependencies} CACHE INTERNAL "extra ROMFS deps" FORCE)

	if(SERIAL_PORTS)
		set(board_serial_ports ${SERIAL_PORTS} PARENT_SCOPE)
	endif()

	# ROMFS
	if(ROMFSROOT)
		set(config_romfs_root ${ROMFSROOT} CACHE INTERNAL "ROMFS root" FORCE)

		if(BUILD_BOOTLOADER)
			set(config_build_bootloader "1" CACHE INTERNAL "build bootloader" FORCE)
		endif()

		# IO board (placed in ROMFS)
		if(IO)
			set(config_io_board ${IO} CACHE INTERNAL "IO" FORCE)
		endif()
	endif()

	if(UAVCAN_INTERFACES)
		set(config_uavcan_num_ifaces ${UAVCAN_INTERFACES} CACHE INTERNAL "UAVCAN interfaces" FORCE)
	endif()

	if(UAVCAN_TIMER_OVERRIDE)
		set(config_uavcan_timer_override ${UAVCAN_TIMER_OVERRIDE} CACHE INTERNAL "UAVCAN TIMER OVERRIDE" FORCE)
	endif()

	# OPTIONS

	if(CONSTRAINED_FLASH)
		set(constrained_flash_build "1" CACHE INTERNAL "constrained flash build" FORCE)
		add_definitions(-DCONSTRAINED_FLASH)
	endif()

	if(TESTING)
		set(TESTING "1" CACHE INTERNAL "testing enabled" FORCE)
	endif()
	if(ETHERNET)
		set(ETHERNET "1" CACHE INTERNAL "ethernet enabled" FORCE)
	endif()

	if(LINKER_PREFIX)
		set(BOARD_LINKER_PREFIX ${LINKER_PREFIX} CACHE STRING "board linker prefix" FORCE)
	else()
		set(BOARD_LINKER_PREFIX "" CACHE STRING "board linker prefix" FORCE)
	endif()

	include(impl_os)
	os_prebuild_targets(OUT prebuild_targets BOARD ${BOARD})


	###########################################################################
	# Modules (includes drivers, examples, modules, systemcmds)
	set(config_module_list)

	if(DRIVERS)
		foreach(driver ${DRIVERS})
			list(APPEND config_module_list drivers/${driver})
		endforeach()
	endif()

	if(MODULES)
		foreach(module ${MODULES})
			list(APPEND config_module_list modules/${module})
		endforeach()
	endif()

	if(SYSTEMCMDS)
		foreach(systemcmd ${SYSTEMCMDS})
			list(APPEND config_module_list systemcmds/${systemcmd})
		endforeach()
	endif()

	if(EXAMPLES)
		foreach(example ${EXAMPLES})
			list(APPEND config_module_list examples/${example})
		endforeach()
	endif()

	# add board config directory src to build modules
	file(RELATIVE_PATH board_support_src_rel ${SOURCE_DIR}/src ${BOARD_DIR})
	list(APPEND config_module_list ${board_support_src_rel}/src)

	set(config_module_list ${config_module_list} PARENT_SCOPE)

endfunction()
