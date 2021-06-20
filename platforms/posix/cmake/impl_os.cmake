############################################################################
#
# Copyright (c) 2015 PX4 Development Team. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name PX4 nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

#=============================================================================
#
#	Defined functions in this file
#
# 	OS Specific Functions
#
#		* posix_generate_builtin_commands
#
# 	Required OS Interface Functions
#
# 		* px4_os_add_flags
# 		* px4_os_determine_build_chip
#		* px4_os_prebuild_targets
#

#=============================================================================
#
#	posix_generate_builtin_commands
#
#	This function generates the builtin_commands.c src for posix
#
#	Usage:
#		posix_generate_builtin_commands(
#			MODULE_LIST <in-list>
#			OUT <file>)
#
#	Input:
#		MODULE_LIST	: list of modules
#
#	Output:
#		OUT	: stem of generated apps.cpp/apps.h ("apps")
#
#	Example:
#		posix_generate_builtin_commands(
#			OUT <generated-src> MODULE_LIST px4_simple_app)
#
function(generate_builtin_commands)
	parse_function_args(
		NAME posix_generate_builtin_commands
		ONE_VALUE OUT
		MULTI_VALUE MODULE_LIST
		REQUIRED MODULE_LIST OUT
		ARGN ${ARGN})

	set(builtin_apps_string)
	set(builtin_apps_decl_string)
	set(command_count 0)
	foreach(module ${MODULE_LIST})
		# default
		set(MAIN_DEFAULT MAIN-NOTFOUND)
		set(STACK_DEFAULT 1024)
		set(PRIORITY_DEFAULT SCHED_PRIORITY_DEFAULT)
		foreach(property MAIN STACK PRIORITY)
			get_target_property(${property} ${module} ${property})
			if(NOT ${property})
				set(${property} ${${property}_DEFAULT})
			endif()
		endforeach()
		if (MAIN)
			set(builtin_apps_string
				"${builtin_apps_string}\tapps[\"${MAIN}\"] = ${MAIN}_main;\n")
			set(builtin_apps_decl_string
				"${builtin_apps_decl_string}int ${MAIN}_main(int argc, char *argv[]);\n")
			math(EXPR command_count "${command_count}+1")
		endif()
	endforeach()
	configure_file(${SOURCE_DIR}/platforms/common/apps.cpp.in ${OUT}.cpp)
	configure_file(${SOURCE_DIR}/platforms/common/apps.h.in ${OUT}.h)
endfunction()


#=============================================================================
#
#	posix_generate_alias
#
#	This function generates the qpro-alias.sh script containing the command
#	aliases for all modules and commands.
#
#	Usage:
#		posix_generate_alias(
#			MODULE_LIST <in-list>
#			OUT <file>
#			PREFIX <prefix>)
#
#	Input:
#		MODULE_LIST	: list of modules
#		PREFIX	: command prefix (e.g. "qpro-")
#
#	Output:
#		OUT	: qpro-alias.sh file path
#
#	Example:
#		posix_generate_alias(
#			OUT <generated-src> MODULE_LIST qpro_simple_app PREFIX qpro-)
#
function(posix_generate_alias)
	parse_function_args(
		NAME posix_generate_alias
		ONE_VALUE OUT PREFIX
		MULTI_VALUE MODULE_LIST
		REQUIRED OUT PREFIX MODULE_LIST
		ARGN ${ARGN})

	set(alias_string)
	foreach(module ${MODULE_LIST})
		foreach(property MAIN STACK PRIORITY)
			get_target_property(${property} ${module} ${property})
			if(NOT ${property})
				set(${property} ${${property}_DEFAULT})
			endif()
		endforeach()
		if (MAIN)
			set(alias_string
				"${alias_string}alias ${MAIN}='${PREFIX}${MAIN} --instance $qpro_instance'\n"
			)
		endif()
	endforeach()
	#configure_file(${SOURCE_DIR}/platforms/posix/src/qpro/common/qpro-alias.sh_in ${OUT})
endfunction()


#=============================================================================
#
#	posix_generate_symlinks
#
#	This function generates symlinks for all modules/commands.
#
#	Usage:
#		posix_generate_symlinks(
#			TARGET <target>
#			MODULE_LIST <in-list>
#			PREFIX <prefix>)
#
#	Input:
#		MODULE_LIST	: list of modules
#		PREFIX	: command prefix (e.g. "qpro-")
#		TARGET	: cmake target for which the symlinks should be created
#
#	Example:
#		posix_generate_symlinks(
#			TARGET qpro MODULE_LIST qpro_simple_app PREFIX qpro-)
#
function(posix_generate_symlinks)
	parse_function_args(
		NAME posix_generate_symlinks
		ONE_VALUE TARGET PREFIX
		MULTI_VALUE MODULE_LIST
		REQUIRED TARGET PREFIX MODULE_LIST
		ARGN ${ARGN})

	foreach(module ${MODULE_LIST})

		foreach(property MAIN STACK PRIORITY)
			get_target_property(${property} ${module} ${property})
			if(NOT ${property})
				set(${property} ${${property}_DEFAULT})
			endif()
		endforeach()

		if (MAIN)
			set(ln_name "${PREFIX}${MAIN}")
			add_custom_command(TARGET ${TARGET}
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E create_symlink ${TARGET} ${ln_name}
				WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
			)
		endif()
	endforeach()
endfunction()


#=============================================================================
#
#	os_add_flags
#
#	Set the posix build flags.
#
#	Usage:
#		os_add_flags()
#
function(os_add_flags)

	add_definitions(
		-D__POSIX
		-Dnoreturn_function=__attribute__\(\(noreturn\)\)
		)

	include_directories(platforms/posix/include)

	if ("${BOARD}" MATCHES "sitl")

		if(UNIX AND APPLE)
			add_definitions(-D__DARWIN)

			if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
				message(FATAL_ERROR "QPRO Firmware requires XCode 8 or newer on Mac OS. Version installed on this system: ${CMAKE_CXX_COMPILER_VERSION}")
			endif()

			execute_process(COMMAND uname -v OUTPUT_VARIABLE DARWIN_VERSION)
			string(REGEX MATCH "[0-9]+" DARWIN_VERSION ${DARWIN_VERSION})
			# message(STATUS "QPRO Darwin Version: ${DARWIN_VERSION}")
			if (DARWIN_VERSION LESS 16)
				add_definitions(
					-DCLOCK_MONOTONIC=1
					-DCLOCK_REALTIME=0
					-D__APPLE_LEGACY
					)
			endif()

		elseif(CYGWIN)
			add_definitions(
				-D__CYGWIN
				-D_GNU_SOURCE
				-D__USE_LINUX_IOCTL_DEFS
				-U__CUSTOM_FILE_IO__
				)
		else()
			add_definitions(-D__LINUX)
		endif()

	endif()

endfunction()

#=============================================================================
#
#	os_determine_build_chip
#
#	Sets CHIP and CHIP_MANUFACTURER.
#
#	Usage:
#		os_determine_build_chip()
#
function(os_determine_build_chip)

	# always use generic chip and chip manufacturer
	set(CHIP "generic" CACHE STRING "Chip" FORCE)
	set(CHIP_MANUFACTURER "generic" CACHE STRING "Chip Manufacturer" FORCE)

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

	add_library(prebuild_targets INTERFACE)
	add_dependencies(prebuild_targets DEPENDS uorb_headers)

endfunction()
