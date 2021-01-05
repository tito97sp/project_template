
add_board(
	PLATFORM nuttx
	VENDOR stm
	MODEL nucleo-h743zi
	LABEL default
	TOOLCHAIN arm-none-eabi
	ARCHITECTURE cortex-m7
	MODULES
		hello
		uORB
		template_module
	)
