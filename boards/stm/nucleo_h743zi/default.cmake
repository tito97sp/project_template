
add_board(
	PLATFORM nuttx
	VENDOR stm
	MODEL nucleo-h743zi
	LABEL default
	TOOLCHAIN arm-none-eabi
	ARCHITECTURE cortex-m7
	ROMFSROOT fmu_common
	MODULES
		hello_sub
		hello_pub
		blue_daemon
		module_develop
	SYSTEMCMDS
		param
	)
