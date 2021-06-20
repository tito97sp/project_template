set(SRCS_PLATFORM)
if (${PLATFORM} STREQUAL "nuttx")
	list(APPEND SRCS_PLATFORM
		nuttx/cdev_platform.cpp
		nuttx/cdev_platform.hpp
	)

	add_custom_library(cdev
	CDev.cpp
	CDev.hpp
	${SRCS_PLATFORM}
	)
	target_compile_options(cdev PRIVATE ${MAX_CUSTOM_OPT_LEVEL})

else()
	# list(APPEND SRCS_PLATFORM
	# 	posix/cdev_platform.cpp
	# 	posix/cdev_platform.hpp
	# )
endif()


