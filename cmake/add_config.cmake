# find project config
#  look for in tree board config that matches CONFIG input
if(NOT CONFIG_FILE)

	file(GLOB_RECURSE board_configs
		RELATIVE "${SOURCE_DIR}/boards"
		"boards/*.cmake"
		)

	set(CONFIGS ${board_configs} CACHE STRING "project boards configs" FORCE)

	foreach(filename ${board_configs})
		# parse input CONFIG into components to match with existing in tree configs
		#  the platform prefix (eg nuttx_) is historical, and removed if present
		string(REPLACE ".cmake" "" filename_stripped ${filename})
		string(REPLACE "/" ";" config ${filename_stripped})
		list(LENGTH config config_len)

		if(${config_len} EQUAL 3)
			list(GET config 0 vendor)
			list(GET config 1 model)
			list(GET config 2 label)

			set(board "${vendor}${model}")

			# <VENDOR>_<MODEL>_<LABEL> (eg px4_fmu-v2_default)
			# <VENDOR>_<MODEL>_default (eg px4_fmu-v2) # allow skipping label if "default"
			if ((${CONFIG} MATCHES "${vendor}_${model}_${label}") OR # match full vendor, model, label
			    ((${label} STREQUAL "default") AND (${CONFIG} STREQUAL "${vendor}_${model}")) # default label can be omitted
			)
				set(CONFIG_FILE "${SOURCE_DIR}/boards/${filename}" CACHE FILEPATH "path to CONFIG file" FORCE)
				break()
			endif()

			# <BOARD>_<LABEL> (eg px4_fmu-v2_default)
			# <BOARD>_default (eg px4_fmu-v2) # allow skipping label if "default"
			if ((${CONFIG} MATCHES "${board}_${label}") OR # match full board, label
			    ((${label} STREQUAL "default") AND (${CONFIG} STREQUAL "${board}")) # default label can be omitted
			)
				set(CONFIG_FILE "${SOURCE_DIR}/boards/${filename}" CACHE FILEPATH "path to CONFIG file" FORCE)
				break()
			endif()
		endif()
	endforeach()
endif()

if(NOT CONFIG_FILE)
	message(FATAL_ERROR "config file not set, try one of ${CONFIGS}")
endif()

message(STATUS "config file: ${CONFIG_FILE}")

