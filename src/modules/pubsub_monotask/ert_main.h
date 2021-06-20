//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: ert_main.h
//
// Code generated for Simulink model 'pubsub_monotask'.
//
// Model version                  : 1.3
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun May 30 21:24:27 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
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

extern "C" __EXPORT int_T pubsub_monotask_main(int_T argc, char_T *argv[]);
class pubsub_monotaskModule : public ModuleBase<pubsub_monotaskModule>
{
 public:
  pubsub_monotaskModule()
  {
  }

  virtual ~pubsub_monotaskModule() = default;

  //* @see ModuleBase
  static int_T task_spawn(int_T argc, char_T *argv[]);

  //* @see ModuleBase
  static pubsub_monotaskModule *instantiate(int_T argc, char_T *argv[]);

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
