#include "hello.hpp"

#include <uORB/Subscription.hpp>
#include <uORB/SubscriptionCallback.hpp>
#include <uORB/Publication.hpp>
#include <uORB/topics/ping.h>

int hello_main(int argc, char *argv[])
{   
    uORB::Subscription	_ping_sub{ORB_ID(ping)};
    if(_ping_sub.updated())
    {
        ping_s _ping_s;
        _ping_sub.copy(&_ping_s);
    }
    return 0;
}
