//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.h
//
// Code generated for Simulink model 'matlab_module'.
//
// Model version                  : 1.21
// Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
// C/C++ source code generated on : Mon Apr 19 22:22:06 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_ert_main_h_
#define RTW_HEADER_ert_main_h_
#include <getopt.h>
#include <platform_common/module.h>
#include <uORB/Subscription.hpp>
#include <uORB/Publication.hpp>
#include "rtwtypes.h"

extern "C" __EXPORT int_T matlab_module_main(int_T argc, char_T *argv[]);
class matlab_moduleModule : public ModuleBase<matlab_moduleModule>
{
 public:
  matlab_moduleModule()
  {
  }

  virtual ~matlab_moduleModule() = default;

  //* @see ModuleBase
  static int_T task_spawn(int_T argc, char_T *argv[]);

  //* @see ModuleBase
  static matlab_moduleModule *instantiate(int_T argc, char_T *argv[]);

  //* @see ModuleBase
  static int_T custom_command(int_T argc, char_T *argv[]);

  //* @see ModuleBase
  static int_T print_usage(const char_T *reason = nullptr);

  //* @see ModuleBase::run()
  void run() override;

  //* @see ModuleBase::print_status()
  //int_T print_status() override;
 private:
  struct sigaction act;
  struct sigaction oact;
  struct sigevent notify;
  struct itimerspec timer;
  timer_t timerid;
  int status;
  struct sched_param sparam;
  int prio_min;
  int prio_max;
  int prio_mid;
  pthread_attr_t attr;
};

#endif                                 // RTW_HEADER_ert_main_h_

//
// File trailer for generated code.
//
// [EOF]
//
