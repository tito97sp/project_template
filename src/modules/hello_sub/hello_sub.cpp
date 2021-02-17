#include "hello_sub.hpp"

#include <poll.h>

#include <uORB/Subscription.hpp>
#include <uORB/SubscriptionCallback.hpp>
#include <uORB/Publication.hpp>
#include <uORB/topics/hello.h>

HelloSub::HelloSub() : SubscriptionCallback(ORB_ID(hello)){registerCallback();}

int HelloSub::custom_command(int argc, char *argv[])
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

int HelloSub::print_usage(const char *reason)
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

int HelloSub::task_spawn(int argc, char *argv[])
{
    _task_id = os_task_spawn_cmd("hellosub",
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

HelloSub *HelloSub::instantiate(int argc, char *argv[])
{
	HelloSub *instance = new HelloSub();

	if (instance == nullptr) {
		printf("alloc failed\n");
	}

	return instance;
}

void HelloSub::run()
{
	printf("hello_sub module started\n");
    //uORB::SubscriptionCallback _hello_sub{(ORB_ID(hello))};

	for(;;){
		//if (_hello_sub.updated()) {
		//	hello_s hello;

		//	if (_hello_sub.copy(&hello)) {
		//		printf("hello number: %lu \n", hello.hello_number);
		//	}
		//}
		//printf("SUB: update\n");
		//sleep(1);
	}
	//int hello_sub_fd = orb_subscribe(ORB_ID(hello));

	
    // struct pollfd fds[1];
	// fds[0].fd = hello_sub_fd;
	// fds[0].events = POLLIN;


	// while (!should_exit()) {
	// 	//wait for up to 1000ms for data
	// 	int pret = poll(fds, (sizeof(fds) / sizeof(fds[0])), -1);

	// 	if (pret == 0) {
	// 	//Timeout: let the loop run anyway, don't do `continue` here

	// 	} else if (pret < 0) {
	// 	//this is undesirable but not much we can do
	// 			//PX4_ERR("poll error %d, %d \n", pret, errno);
	// 			//px4_usleep(50000);
	// 			//continue;
	// 	} else if (fds[0].revents & POLLIN) {
	// 		struct hello_s hello;
	// 		orb_copy(ORB_ID(hello), hello_sub_fd, &hello);
	// 		printf("hello number: %lu \n", hello.hello_number);
	// 	}
	// }
	// orb_unsubscribe(hello_sub_fd);
}

void HelloSub::call()
{
	//if (_hello_sub.updated()) {
 	hello_s hello;

		//	if (_hello_sub.copy(&hello)) {
		//		printf("hello number: %lu \n", hello.hello_number);
		//	}
		//}
		//printf("SUB: update\n");
	if (copy(&hello))
	{
		printf("hello number: %lu \n", hello.hello_number);
	}
}

int hello_sub_main(int argc, char *argv[])
{   
    return HelloSub::main(argc, argv);
}