
add_board(
	PLATFORM nuttx
	VENDOR px4
	MODEL fmu-v5
	LABEL default
	TOOLCHAIN arm-none-eabi
	ARCHITECTURE cortex-m7
	MODULES
			hello
	
	)
