//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: rt_main.h
//
// Code generated for Simulink model 'pubsub_multitask'.
//
// Model version                  : 1.5
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Mon May 31 12:12:12 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_rt_main_h_
#define RTW_HEADER_rt_main_h_
#include <platform_common/module.h>
#include <platform_common/log.h>

extern "C" __EXPORT int_T pubsub_multitask_main(int_T argc, char_T *argv[]);
class pubsub_multitask_module : public ModuleBase<pubsub_multitask_module>
{
 public:
  pubsub_multitask_module()
  {
  }

  virtual ~pubsub_multitask_module() = default;

  //* @see ModuleBase
  static int_T task_spawn(int_T argc, char_T *argv[]);

  //* @see ModuleBase
  static pubsub_multitask_module *instantiate(int_T argc, char_T *argv[]);

  //* @see ModuleBase
  static int_T custom_command(int_T argc, char_T *argv[]);

  //* @see ModuleBase
  static int_T print_usage(const char_T *reason = nullptr);

  //* @see ModuleBase::run()
  void run() override;

  //* @see ModuleBase::print_status()
  //int_T print_status() override;
 private:
};

#endif                                 // RTW_HEADER_rt_main_h_

//
// File trailer for generated code.
//
// [EOF]
//
