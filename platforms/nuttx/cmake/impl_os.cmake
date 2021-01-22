#=============================================================================
#
#	Defined functions in this file
#
#	Required OS Interface Functions
#
#		* os_add_flags
# 		* os_determine_build_chip
#		* os_prebuild_targets
#

#=============================================================================
#
#	os_add_flags
#
#	Set the nuttx build flags.
#
function(os_add_flags)

	include_directories(BEFORE SYSTEM
		${BINARY_DIR}/NuttX/nuttx/include
		${BINARY_DIR}/NuttX/nuttx/include/cxx
		${SOURCE_DIR}/platforms/nuttx/NuttX/include/cxx	# custom new
	)

	include_directories(
		${BINARY_DIR}/NuttX/nuttx/arch/${CONFIG_ARCH}/src/${CONFIG_ARCH_FAMILY}
		${BINARY_DIR}/NuttX/nuttx/arch/${CONFIG_ARCH}/src/chip
		${BINARY_DIR}/NuttX/nuttx/arch/${CONFIG_ARCH}/src/common
		${BINARY_DIR}/NuttX/apps/include
	)

	# prevent using the toolchain's std c++ library
	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-nostdinc++>)

	add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-fno-sized-deallocation>)

	add_definitions(
		-D__NUTTX

		-D_SYS_CDEFS_H_ # skip toolchain's <sys/cdefs.h>
		-D_SYS_REENT_H_	# skip toolchain's <sys/reent.h>
		)

	if("${CONFIG_ARMV7M_STACKCHECK}" STREQUAL "y")
		message(STATUS "NuttX Stack Checking (CONFIG_ARMV7M_STACKCHECK) enabled")
		add_compile_options(
			-ffixed-r10
			-finstrument-functions
			# instrumenting PX4 Matrix and Param methods is too burdensome
			-finstrument-functions-exclude-file-list=matrix/Matrix.hpp,px4_platform_common/param.h
		)
	endif()

endfunction()

#=============================================================================
#
#	os_determine_build_chip
#
#	Sets PROJECT_CHIP and PROJECT_CHIP_MANUFACTURER.
#
#	Usage:
#		os_determine_build_chip()
#
function(os_determine_build_chip)

	# determine chip and chip manufacturer based on NuttX config
	if (CONFIG_STM32_STM32F10XX)
		set(CHIP_MANUFACTURER "stm")
		set(CHIP "stm32f1")
	elseif(CONFIG_STM32_STM32F30XX)
		set(CHIP_MANUFACTURER "stm")
		set(CHIP "stm32f3")
	elseif(CONFIG_STM32_STM32F4XXX)
		set(CHIP_MANUFACTURER "stm")
		set(CHIP "stm32f4")
	elseif(CONFIG_ARCH_CHIP_STM32F7)
		set(CHIP_MANUFACTURER "stm")
		set(CHIP "stm32f7")
	elseif(CONFIG_ARCH_CHIP_STM32H7)
		set(CHIP_MANUFACTURER "stm")
		set(CHIP "stm32h7")
	elseif(CONFIG_ARCH_CHIP_MK66FN2M0VMD18)
		set(CHIP_MANUFACTURER "nxp")
		set(CHIP "k66")
	elseif(CONFIG_ARCH_CHIP_MIMXRT1062DVL6A)
		set(CHIP_MANUFACTURER "nxp")
		set(CHIP "rt106x")
	elseif(CONFIG_ARCH_CHIP_S32K146)
		set(CHIP_MANUFACTURER "nxp")
		set(CHIP "s32k14x")
	else()
		message(FATAL_ERROR "Could not determine chip architecture from NuttX config. You may have to add it.")
	endif()

	set(CHIP ${CHIP} CACHE STRING "Chip" FORCE)
	set(CHIP_MANUFACTURER ${CHIP_MANUFACTURER} CACHE STRING "Chip Manufacturer" FORCE)
endfunction()

#=============================================================================
#
#	os_prebuild_targets
#
#	This function generates os dependent targets
#
#	Usage:
#		os_prebuild_targets(
#			OUT <out-list_of_targets>
#			BOARD <in-string>
#			)
#
#	Input:
#		BOARD		: board
#
#	Output:
#		OUT	: the target list
#
#	Example:
#		os_prebuild_targets(OUT target_list BOARD px4_fmu-v2)
#
function(os_prebuild_targets)
	parse_function_args(
			NAME os_prebuild_targets
			ONE_VALUE OUT BOARD
			REQUIRED OUT
			ARGN ${ARGN})

	if(EXISTS ${BOARD_DIR}/nuttx-config/${BOARD_LABEL})
		set(NUTTX_CONFIG "${BOARD_LABEL}" CACHE INTERNAL "NuttX config" FORCE)
	else()
		set(NUTTX_CONFIG "nsh" CACHE INTERNAL "NuttX config" FORCE)
	endif()

	add_library(prebuild_targets INTERFACE)
	target_link_libraries(prebuild_targets INTERFACE nuttx_xx nuttx_c nuttx_fs nuttx_mm nuttx_sched m gcc)
	add_dependencies(prebuild_targets DEPENDS nuttx_build uorb_headers)

endfunction()
