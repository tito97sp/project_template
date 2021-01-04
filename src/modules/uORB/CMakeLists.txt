# this includes the generated topics directory
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_module(
	MODULE uORB
	MAIN uorb
	COMPILE_FLAGS
		${MAX_CUSTOM_OPT_LEVEL}
	SRCS
		ORBSet.hpp
		Publication.hpp
		PublicationMulti.hpp
		Subscription.cpp
		Subscription.hpp
		SubscriptionCallback.hpp
		SubscriptionInterval.hpp
		SubscriptionMultiArray.hpp
		uORB.cpp
		uORB.h
		uORBCommon.hpp
		uORBCommunicator.hpp
		uORBDeviceMaster.cpp
		uORBDeviceMaster.hpp
		uORBDeviceNode.cpp
		uORBDeviceNode.hpp
		uORBMain.cpp
		uORBManager.cpp
		uORBManager.hpp
		uORBUtils.cpp
		uORBUtils.hpp
	DEPENDS
		cdev
		#uorb_msgs
	)

# if(PX4_TESTING)
# 	add_subdirectory(uORB_tests)
# endif()