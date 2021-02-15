//***************************************************************************
// examples/helloxx/helloxx_main.cxx
//
//   Copyright (C) 2009, 2011-2013, 2017 Gregory Nutt. All rights reserved.
//   Author: Gregory Nutt <gnutt@nuttx.org>
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in
//    the documentation and/or other materials provided with the
//    distribution.
// 3. Neither the name NuttX nor the names of its contributors may be
//    used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
// OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
// AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//***************************************************************************

//***************************************************************************
// Included Files
//***************************************************************************

#include <nuttx/config.h>
#include <errno.h>

#include <cstdio>
#include <debug.h>

#include <fcntl.h>
#include <sys/types.h>

#include <lib/cdev/CDev.hpp>
#include "uORBManager.hpp"
#include "uORB.h"
#include "uORBCommon.hpp"

#include <platform_common/module.h>




extern "C" { __EXPORT int uorb_main(int argc, char *argv[]); }

static uORB::DeviceMaster *g_dev = nullptr;

int uorb_main(int argc, FAR char *argv[]){

    if (argc < 2) {
        //usage();
        return -EINVAL;
      }

      /*
      * Start/load the driver.
      */
      if (!strcmp(argv[1], "start")) {

        if (g_dev != nullptr) {
          printf("already loaded\n");
          /* user wanted to start uorb, its already running, no error */
          return 0;
        }

        if (!uORB::Manager::initialize()) {
          printf("uorb manager alloc failed\n");
          return -ENOMEM;
        }

        /* create the driver */
        g_dev = uORB::Manager::get_instance()->get_device_master();

        if (g_dev == nullptr) {
          return -errno;
        }

        return OK;
      }

      /*
      * Print driver information.
      */
      if (!strcmp(argv[1], "status")) {
        if (g_dev != nullptr) {
          g_dev->printStatistics();

        } else {
          printf("uorb is not running\n");
        }

        return OK;
      }

      if (!strcmp(argv[1], "top")) {
        if (g_dev != nullptr) {
          g_dev->showTop(argv + 2, argc - 2);

        } else {
          printf("uorb is not running\n");
        }

        return OK;
      }

      //usage();
      return -EINVAL;
}
