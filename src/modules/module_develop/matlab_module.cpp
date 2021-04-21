//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: matlab_module.cpp
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
#include "matlab_module.h"
#include "matlab_module_private.h"

const log_message_s matlab_module_rtZlog_message_s = {
  0UL,                    // timestamp
  0U,                                  // severity

  {
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
    0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U }
  // text
} ;                                    // log_message_s ground

// Block states (default storage)
DW_matlab_module_T matlab_module_DW;

// Real-time model
RT_MODEL_matlab_module_T matlab_module_M_ = RT_MODEL_matlab_module_T();
RT_MODEL_matlab_module_T *const matlab_module_M = &matlab_module_M_;
void Double2MultiWord(real_T u1, uint32_T y[], int32_T n)
{
  real_T yd;
  real_T yn;
  int32_T currExp;
  int32_T i;
  int32_T msl;
  int32_T prevExp;
  uint32_T cb;
  uint32_T u1i;
  boolean_T isNegative;
  isNegative = (u1 < 0.0);
  yn = frexp(u1, &currExp);
  msl = currExp <= 0 ? -1 : div_s32(currExp - 1, 32);
  cb = 1U;
  for (i = msl + 1; i < n; i++) {
    y[i] = 0U;
  }

  yn = isNegative ? -yn : yn;
  prevExp = 32 * msl;
  for (i = msl; i >= 0; i--) {
    yn = std::ldexp(yn, currExp - prevExp);
    yd = std::floor(yn);
    yn -= yd;
    if (i < n) {
      y[i] = static_cast<uint32_T>(yd);
    }

    currExp = prevExp;
    prevExp -= 32;
  }

  if (isNegative) {
    for (i = 0; i < n; i++) {
      u1i = ~y[i];
      cb += u1i;
      y[i] = cb;
      cb = (cb < u1i);
    }
  }
}

int32_T div_s32(int32_T numerator, int32_T denominator)
{
  int32_T quotient;
  uint32_T tempAbsQuotient;
  if (denominator == 0) {
    quotient = numerator >= 0 ? MAX_int32_T : MIN_int32_T;

    // Divide by zero handler
  } else {
    tempAbsQuotient = (numerator < 0 ? ~static_cast<uint32_T>(numerator) + 1U :
                       static_cast<uint32_T>(numerator)) / (denominator < 0 ? ~
      static_cast<uint32_T>(denominator) + 1U : static_cast<uint32_T>
      (denominator));
    quotient = (numerator < 0) != (denominator < 0) ? -static_cast<int32_T>
      (tempAbsQuotient) : static_cast<int32_T>(tempAbsQuotient);
  }

  return quotient;
}

//
// System initialize for atomic system:
//    synthesized block
//    synthesized block
//
void matlab_module_SinkBlock_Init(const log_message_s *rtu_0,
  DW_SinkBlock_matlab_module_T *localDW)
{
  // Start for MATLABSystem: '<S1>/SinkBlock'
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isSetupComplete = false;
  localDW->obj.isInitialized = 1;
  localDW->obj.orbMetadataObj = ORB_ID(log_message);
  uORB_write_initialize(localDW->obj.orbMetadataObj,
                        &localDW->obj.orbAdvertiseObj, rtu_0, 1);
  localDW->obj.isSetupComplete = true;
}

//
// Output and update for atomic system:
//    synthesized block
//    synthesized block
//
void matlab_module_SinkBlock(const log_message_s *rtu_0,
  DW_SinkBlock_matlab_module_T *localDW)
{
  // MATLABSystem: '<S1>/SinkBlock'
  uORB_write_step(localDW->obj.orbMetadataObj, &localDW->obj.orbAdvertiseObj,
                  rtu_0);
}

//
// Termination for atomic system:
//    synthesized block
//    synthesized block
//
void matlab_module_SinkBlock_Term(DW_SinkBlock_matlab_module_T *localDW)
{
  // Terminate for MATLABSystem: '<S1>/SinkBlock'
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      uORB_write_terminate(&localDW->obj.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S1>/SinkBlock'
}

// Model step function
void matlab_module_step(void)
{
  // local block i/o variables
  log_message_s rtb_BusAssignment;
  real_T u;

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   Constant: '<S3>/Constant'

  rtb_BusAssignment = matlab_module_rtZlog_message_s;

  // Sin: '<Root>/Sine Wave'
  u = std::sin(static_cast<real_T>(matlab_module_DW.counter) * 2.0 *
               3.1415926535897931 / 10.0);

  // DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment'

  if (std::abs(u) >= 0.5) {
    u = std::floor(u + 0.5);
  } else {
    u *= 0.0;
  }

  Double2MultiWord(u, &rtb_BusAssignment.timestamp.chunks[0U], 2);

  // End of DataTypeConversion: '<Root>/Data Type Conversion'
  matlab_module_SinkBlock(&rtb_BusAssignment, &matlab_module_DW.SinkBlock);
  matlab_module_SinkBlock(&rtb_BusAssignment, &matlab_module_DW.SinkBlock_f);

  // Update for Sin: '<Root>/Sine Wave'
  matlab_module_DW.counter++;
  if (matlab_module_DW.counter == 10) {
    matlab_module_DW.counter = 0;
  }

  // End of Update for Sin: '<Root>/Sine Wave'
}

// Model initialize function
void matlab_module_initialize(void)
{
  {
    // local block i/o variables
    log_message_s rtb_BusAssignment;
    matlab_module_SinkBlock_Init(&rtb_BusAssignment, &matlab_module_DW.SinkBlock);
    matlab_module_SinkBlock_Init(&rtb_BusAssignment,
      &matlab_module_DW.SinkBlock_f);
  }
}

// Model terminate function
void matlab_module_terminate(void)
{
  matlab_module_SinkBlock_Term(&matlab_module_DW.SinkBlock);
  matlab_module_SinkBlock_Term(&matlab_module_DW.SinkBlock_f);
}

//
// File trailer for generated code.
//
// [EOF]
//
