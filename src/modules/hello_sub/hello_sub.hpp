#ifndef HELLO_SUB_H
#define HELLO_SUB_H

#include <platform_common/module.h>
#include <uORB/uORB.h>
#include <uORB/SubscriptionCallback.hpp>

extern "C" { __EXPORT int hello_sub_main(int argc, char *argv[]); }

class HelloSub : public ModuleBase<HelloSub> , public uORB::SubscriptionCallback
{
public: 
    HelloSub();

    virtual ~HelloSub() = default;

    static int task_spawn(int argc, char *argv[]);

    static int print_usage(const char *reason = nullptr);

    static HelloSub *instantiate(int argc, char *argv[]);

	static int custom_command(int argc, char *argv[]);
 
    void run() override;

    void call() override;
};

#endif //HELLO_SUB_H