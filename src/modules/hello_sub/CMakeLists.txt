add_module(
	MODULE hello_sub
	MAIN hello_sub
	SRCS
		hello_sub.cpp
	DEPENDS
		uORB
	STACK_MAIN 1024
	)
	