//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: matlab_module.cpp
//
// Code generated for Simulink model 'matlab_module'.
//
// Model version                  : 1.7
// Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
// C/C++ source code generated on : Wed Apr 21 18:10:14 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "matlab_module.h"
#include "matlab_module_private.h"

// Block states (default storage)
DW_matlab_module_T matlab_module_DW;

// Real-time model
RT_MODEL_matlab_module_T matlab_module_M_ = RT_MODEL_matlab_module_T();
RT_MODEL_matlab_module_T *const matlab_module_M = &matlab_module_M_;

// Model step function
void matlab_module_step(void)
{
  // (no output/update code required)
}

// Model initialize function
void matlab_module_initialize(void)
{
  // Start for MATLABSystem: '<S1>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment'

  matlab_module_DW.obj.matlabCodegenIsDeleted = false;
  matlab_module_DW.obj.isSetupComplete = false;
  matlab_module_DW.obj.isInitialized = 1;
  matlab_module_DW.obj.orbMetadataObj = ORB_ID(log_message);
  uORB_write_initialize(matlab_module_DW.obj.orbMetadataObj,
                        &matlab_module_DW.obj.orbAdvertiseObj,
                        &matlab_module_ConstB.BusAssignment, 1);
  matlab_module_DW.obj.isSetupComplete = true;

  // ConstCode for MATLABSystem: '<S1>/SinkBlock' incorporates:
  //   BusAssignment: '<Root>/Bus Assignment'

  uORB_write_step(matlab_module_DW.obj.orbMetadataObj,
                  &matlab_module_DW.obj.orbAdvertiseObj,
                  &matlab_module_ConstB.BusAssignment);
}

// Model terminate function
void matlab_module_terminate(void)
{
  // Terminate for MATLABSystem: '<S1>/SinkBlock'
  if (!matlab_module_DW.obj.matlabCodegenIsDeleted) {
    matlab_module_DW.obj.matlabCodegenIsDeleted = true;
    if ((matlab_module_DW.obj.isInitialized == 1) &&
        matlab_module_DW.obj.isSetupComplete) {
      uORB_write_terminate(&matlab_module_DW.obj.orbAdvertiseObj);
    }
  }

  // End of Terminate for MATLABSystem: '<S1>/SinkBlock'
}

//
// File trailer for generated code.
//
// [EOF]
//
