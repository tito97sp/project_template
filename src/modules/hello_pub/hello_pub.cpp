/****************************************************************************
 *
 *   Copyright (c) 2018 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "hello_pub.h"

//#include <px4_platform_common/getopt.h>
//#include <px4_platform_common/log.h>
//#include <px4_platform_common/posix.h>




int HelloPub::print_status()
{
	printf("Running\n");
	return 0;
}

int HelloPub::custom_command(int argc, char *argv[])
{
	/*
	if (!is_running()) {
		print_usage("not running");
		return 1;
	}

	// additional custom commands can be handled like this:
	if (!strcmp(argv[0], "do-something")) {
		get_instance()->do_something();
		return 0;
	}
	 */

	return print_usage("unknown command\n");
}

int HelloPub::task_spawn(int argc, char *argv[])
{
	_task_id = os_task_spawn_cmd("hellopub",
				      SCHED_DEFAULT,
				      SCHED_PRIORITY_DEFAULT,
				      1024,
				      (os_main_t)&run_trampoline,
				      (char *const *)argv);
	

	if (_task_id < 0) {
		_task_id = -1;
		return -errno;
	}

	return 0;
}

HelloPub *HelloPub::instantiate(int argc, char *argv[])
{
	HelloPub *instance = new HelloPub();

	if (instance == nullptr) {
		printf("ERROR: alloc failed\n");
	}

	return instance;
}

HelloPub::HelloPub() : ModuleParams(nullptr)
{
}

void HelloPub::run()
{
	printf("hello_pub module started\n");
	
	struct hello_s hello{};

	uint32_t iter = 0;

	for(;;){
		if (_parameter_update_sub.updated()) {
			// clear update
			parameter_update_s param_update;
			_parameter_update_sub.copy(&param_update);

			updateParams();
		}
		
		
		hello.hello_number = iter;
		hello_pub.publish(hello);

		iter++;

		printf("PUB: iter = %lu\n", iter);

		unsigned int sleep_time = (unsigned int)(_hello_param.get()/1000);
		sleep(sleep_time);
	}
}

int HelloPub::print_usage(const char *reason)
{
// 	if (reason) {
// 		PX4_WARN("%s\n", reason);
// 	}

// 	PRINT_MODULE_DESCRIPTION(
// 		R"DESCR_STR(
// ### Description
// Section that describes the provided module functionality.

// This is a template for a module running as a task in the background with start/stop/status functionality.

// ### Implementation
// Section describing the high-level implementation of this module.

// ### Examples
// CLI usage example:
// $ module start -f -p 42

// )DESCR_STR");

// 	PRINT_MODULE_USAGE_NAME("module", "template");
// 	PRINT_MODULE_USAGE_COMMAND("start");
// 	PRINT_MODULE_USAGE_PARAM_FLAG('f', "Optional example flag", true);
// 	PRINT_MODULE_USAGE_PARAM_INT('p', 0, 0, 1000, "Optional example parameter", true);
// 	PRINT_MODULE_USAGE_DEFAULT_COMMANDS();

 	return 0;
}

int hello_pub_main(int argc, char *argv[])
{
	return HelloPub::main(argc, argv);
}
