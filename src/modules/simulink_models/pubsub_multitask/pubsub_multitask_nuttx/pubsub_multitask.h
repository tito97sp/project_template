//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: pubsub_multitask.h
//
// Code generated for Simulink model 'pubsub_multitask'.
//
// Model version                  : 1.5
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun May 30 22:17:46 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_pubsub_multitask_h_
#define RTW_HEADER_pubsub_multitask_h_
#include <cmath>
#include <stddef.h>
#include <poll.h>
#include <uORB/uORB.h>
#include "rtwtypes.h"
#include "MW_uORB_Write.h"
#include "MW_uORB_Read.h"
#include "pubsub_multitask_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmCounterLimit
# define rtmCounterLimit(rtm, idx)     ((rtm)->Timing.TaskCounters.cLimit[(idx)])
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

// Block signals (default storage)
typedef struct {
  nuttx_Bus_aa_tito_prueba In1;        // '<S4>/In1'
} B_pubsub_multitask_T;

// Block states (default storage) for system '<Root>'
typedef struct {
  nuttx_internal_block_Subscriber_pubsub_multitask_T obj;// '<S2>/SourceBlock'
  nuttx_internal_block_Publisher_pubsub_multitask_T obj_g;// '<S1>/SinkBlock'
  real_T lastSin;                      // '<Root>/Sine Wave'
  real_T lastCos;                      // '<Root>/Sine Wave'
  int32_T systemEnable;                // '<Root>/Sine Wave'
  uint32_T RT_Buf[2];                  // '<Root>/RT'
  int8_T RT_RdBufIdx;                  // '<Root>/RT'
  int8_T RT_WrBufIdx;                  // '<Root>/RT'
} DW_pubsub_multitask_T;

// Real-time Model Data Structure
struct tag_RTM_pubsub_multitask_T {
  const char_T *errorStatus;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    uint32_T clockTick1;
    struct {
      uint8_T TID[3];
      uint8_T cLimit[3];
    } TaskCounters;

    struct {
      uint8_T TID1_2;
    } RateInteraction;
  } Timing;
};

// Block signals (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern B_pubsub_multitask_T pubsub_multitask_B;

#ifdef __cplusplus

}
#endif

// Block states (default storage)
extern DW_pubsub_multitask_T pubsub_multitask_DW;

// External data declarations for dependent source files
extern const nuttx_Bus_aa_tito_prueba
  pubsub_multitask_rtZnuttx_Bus_aa_tito_prueba;// nuttx_Bus_aa_tito_prueba ground 
extern void rate_scheduler(void);

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void pubsub_multitask_initialize(void);
  extern void pubsub_multitask_step(int_T tid);
  extern void pubsub_multitask_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_pubsub_multitask_T *const pubsub_multitask_M;

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S2>/NOT' : Unused code path elimination


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
//  '<Root>' : 'pubsub_multitask'
//  '<S1>'   : 'pubsub_multitask/uORB Publish'
//  '<S2>'   : 'pubsub_multitask/uORB Subscribe'
//  '<S3>'   : 'pubsub_multitask/uORB Topic'
//  '<S4>'   : 'pubsub_multitask/uORB Subscribe/Enabled Subsystem'

#endif                                 // RTW_HEADER_pubsub_multitask_h_

//
// File trailer for generated code.
//
// [EOF]
//
