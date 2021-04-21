//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: matlab_module.h
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
#ifndef RTW_HEADER_matlab_module_h_
#define RTW_HEADER_matlab_module_h_
#include <cmath>
#include <math.h>
#include <poll.h>
#include <uORB/uORB.h>
#include "rtwtypes.h"
#include "MW_uORB_Write.h"
#include "matlab_module_types.h"

// Shared type includes
#include "multiword_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Block states (default storage) for system '<S1>/SinkBlock'
struct DW_SinkBlock_matlab_module_T {
  nuttx_internal_block_Publishe_T obj; // '<S1>/SinkBlock'
  boolean_T objisempty;                // '<S1>/SinkBlock'
};

// Block states (default storage) for system '<Root>'
struct DW_matlab_module_T {
  int32_T counter;                     // '<Root>/Sine Wave'
  DW_SinkBlock_matlab_module_T SinkBlock_f;// '<S1>/SinkBlock'
  DW_SinkBlock_matlab_module_T SinkBlock;// '<S1>/SinkBlock'
};

// Real-time Model Data Structure
struct tag_RTM_matlab_module_T {
  const char_T * volatile errorStatus;
};

// Block states (default storage)
extern struct DW_matlab_module_T matlab_module_DW;

// External data declarations for dependent source files
extern const uint64m_T matlab_module_uint64_GND;// uint64m_T ground
extern const log_message_s matlab_module_rtZnuttx_Bus_log_message;// nuttx_Bus_log_message ground 

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void matlab_module_initialize(void);
  extern void matlab_module_step(void);
  extern void matlab_module_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_matlab_module_T *const matlab_module_M;

#ifdef __cplusplus

}
#endif

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'matlab_module'
//  '<S1>'   : 'matlab_module/Publisher1'
//  '<S2>'   : 'matlab_module/Publisher2'
//  '<S3>'   : 'matlab_module/uORB Topic'

#endif                                 // RTW_HEADER_matlab_module_h_

//
// File trailer for generated code.
//
// [EOF]
//