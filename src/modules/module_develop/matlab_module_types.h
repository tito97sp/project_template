//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: matlab_module_types.h
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
#ifndef RTW_HEADER_matlab_module_types_h_
#define RTW_HEADER_matlab_module_types_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include <uORB/topics/log_message.h>

// Model Code Variants
#ifndef struct_nuttx_internal_block_Publishe_T
#define struct_nuttx_internal_block_Publishe_T

struct nuttx_internal_block_Publishe_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  orb_advert_t orbAdvertiseObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                // struct_nuttx_internal_block_Publishe_T

// Forward declaration for rtModel
typedef struct tag_RTM_matlab_module_T RT_MODEL_matlab_module_T;

#endif                                 // RTW_HEADER_matlab_module_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
