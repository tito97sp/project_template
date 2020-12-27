function(add_git_submodule)
	parse_function_args(
		NAME add_git_submodule
		ONE_VALUE TARGET PATH
		REQUIRED TARGET PATH
		ARGN ${ARGN})

	set(REL_PATH)

	if(IS_ABSOLUTE ${PATH})
		file(RELATIVE_PATH REL_PATH ${SOURCE_DIR} ${PATH})
	else()
		file(RELATIVE_PATH REL_PATH ${SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${PATH})
	endif()

	execute_process(
		COMMAND Tools/check_submodules.sh ${REL_PATH}
		WORKING_DIRECTORY ${SOURCE_DIR}
		)

	string(REPLACE "/" "_" NAME ${PATH})
	string(REPLACE "." "_" NAME ${NAME})

	add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/git_init_${NAME}.stamp
		COMMAND Tools/check_submodules.sh ${REL_PATH}
		COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/git_init_${NAME}.stamp
		DEPENDS ${SOURCE_DIR}/.gitmodules ${PATH}/.git
		COMMENT "git submodule ${REL_PATH}"
		WORKING_DIRECTORY ${SOURCE_DIR}
		USES_TERMINAL
		)

	add_custom_target(${TARGET} DEPENDS git_init_${NAME}.stamp)
endfunction()