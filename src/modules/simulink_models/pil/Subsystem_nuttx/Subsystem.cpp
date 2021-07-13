//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Subsystem.cpp
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
#include "Subsystem.h"
#include "Subsystem_private.h"

// External inputs (root inport signals with default storage)
ExtU_Subsystem_T Subsystem_U;

// External outputs (root outports fed by signals with default storage)
ExtY_Subsystem_T Subsystem_Y;

// Real-time model
RT_MODEL_Subsystem_T Subsystem_M_ = RT_MODEL_Subsystem_T();
RT_MODEL_Subsystem_T *const Subsystem_M = &Subsystem_M_;

// Model step function
void Subsystem_step(void)
{
  // Outputs for Atomic SubSystem: '<Root>/Subsystem'
  // Outport: '<Root>/Out1' incorporates:
  //   Inport: '<Root>/In1'
  //   Inport: '<Root>/In2'
  //   Sum: '<S1>/Add'

  Subsystem_Y.Out1 = static_cast<int16_T>(Subsystem_U.In1 + Subsystem_U.In2);

  // End of Outputs for SubSystem: '<Root>/Subsystem'
}

// Model initialize function
void Subsystem_initialize(void)
{
  // (no initialization code required)
}

// Model terminate function
void Subsystem_terminate(void)
{
  // (no terminate code required)
}

//
// File trailer for generated code.
//
// [EOF]
//
