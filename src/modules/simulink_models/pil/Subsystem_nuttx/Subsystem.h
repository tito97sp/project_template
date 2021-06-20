//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Subsystem.h
//
// Code generated for Simulink model 'Subsystem'.
//
// Model version                  : 1.8
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Wed Jun  2 13:31:59 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: Custom Processor->Custom
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_Subsystem_h_
#define RTW_HEADER_Subsystem_h_
#include "rtwtypes.h"
#include "Subsystem_types.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// External inputs (root inport signals with default storage)
typedef struct {
  int16_T In1;                         // '<Root>/In1'
  int8_T In2;                          // '<Root>/In2'
} ExtU_Subsystem_T;

// External outputs (root outports fed by signals with default storage)
typedef struct {
  int16_T Out1;                        // '<Root>/Out1'
} ExtY_Subsystem_T;

// Real-time Model Data Structure
struct tag_RTM_Subsystem_T {
  const char_T *errorStatus;
};

#ifdef __cplusplus

extern "C" {

#endif

  // External inputs (root inport signals with default storage)
  extern ExtU_Subsystem_T Subsystem_U;

  // External outputs (root outports fed by signals with default storage)
  extern ExtY_Subsystem_T Subsystem_Y;

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void Subsystem_initialize(void);
  extern void Subsystem_step(void);
  extern void Subsystem_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_Subsystem_T *const Subsystem_M;

#ifdef __cplusplus

}
#endif

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Note that this particular code originates from a subsystem build,
//  and has its own system numbers different from the parent model.
//  Refer to the system hierarchy for this subsystem below, and use the
//  MATLAB hilite_system command to trace the generated code back
//  to the parent model.  For example,
//
//  hilite_system('pil_main/Subsystem')    - opens subsystem pil_main/Subsystem
//  hilite_system('pil_main/Subsystem/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'pil_main'
//  '<S1>'   : 'pil_main/Subsystem'

#endif                                 // RTW_HEADER_Subsystem_h_

//
// File trailer for generated code.
//
// [EOF]
//
