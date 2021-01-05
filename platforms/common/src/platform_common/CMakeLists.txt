set(SRCS)

if (NOT "${PLATFORM}" MATCHES "qurt" AND NOT "${BOARD}" MATCHES "io-v2" AND NOT "${BOARD_LABEL}" MATCHES "bootloader")
	#list(APPEND SRCS
	#	px4_log.cpp
	#	)
endif()

add_library(platform_common
	#board_identity.c
	#external_reset_lockout.cpp
	#i2c.cpp
	#i2c_spi_buses.cpp
	module.cpp
	#px4_getopt.c
	#px4_cli.cpp
	#shutdown.cpp
	#spi.cpp
	${SRCS}
	)
add_dependencies(platform_common prebuild_targets)

if (NOT "${PLATFORM}" MATCHES "qurt" AND NOT "${BOARD}" MATCHES "io-v2")
	target_link_libraries(platform_common PRIVATE uORB) # px4_log awkward dependency with uORB, TODO: orb should part of the platform layer
endif()

#add_subdirectory(px4_work_queue)
#add_subdirectory(work_queue)
