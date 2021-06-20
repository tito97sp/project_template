//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: pubsub_monotask_types.h
//
// Code generated for Simulink model 'pubsub_monotask'.
//
// Model version                  : 1.3
// Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
// C/C++ source code generated on : Sun May 30 21:41:32 2021
//
// Target selection: nuttx_ec.tlc
// Embedded hardware selection: ARM Compatible->ARM Cortex
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_pubsub_monotask_types_h_
#define RTW_HEADER_pubsub_monotask_types_h_
#include "rtwtypes.h"
#include <uORB/topics/aa_tito_prueba.h>

// Model Code Variants
#ifndef struct_tag_hYhAI2VNT1j8Vnv0YZeb1D
#define struct_tag_hYhAI2VNT1j8Vnv0YZeb1D

struct tag_hYhAI2VNT1j8Vnv0YZeb1D
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  orb_advert_t orbAdvertiseObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                 //struct_tag_hYhAI2VNT1j8Vnv0YZeb1D

#ifndef typedef_nuttx_internal_block_Publishe_T
#define typedef_nuttx_internal_block_Publishe_T

typedef struct tag_hYhAI2VNT1j8Vnv0YZeb1D nuttx_internal_block_Publishe_T;

#endif                                 //typedef_nuttx_internal_block_Publishe_T

#ifndef struct_tag_YgA2umAxY1QaUdNJg8JkbB
#define struct_tag_YgA2umAxY1QaUdNJg8JkbB

struct tag_YgA2umAxY1QaUdNJg8JkbB
{
  int32_T __dummy;
};

#endif                                 //struct_tag_YgA2umAxY1QaUdNJg8JkbB

#ifndef typedef_e_px4_internal_block_SampleTi_T
#define typedef_e_px4_internal_block_SampleTi_T

typedef struct tag_YgA2umAxY1QaUdNJg8JkbB e_px4_internal_block_SampleTi_T;

#endif                                 //typedef_e_px4_internal_block_SampleTi_T

#ifndef struct_tag_TU9Rnn74ZJKi9RaH5Ax4lF
#define struct_tag_TU9Rnn74ZJKi9RaH5Ax4lF

struct tag_TU9Rnn74ZJKi9RaH5Ax4lF
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  e_px4_internal_block_SampleTi_T SampleTimeHandler;
  pollfd_t eventStructObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                 //struct_tag_TU9Rnn74ZJKi9RaH5Ax4lF

#ifndef typedef_nuttx_internal_block_Subscrib_T
#define typedef_nuttx_internal_block_Subscrib_T

typedef struct tag_TU9Rnn74ZJKi9RaH5Ax4lF nuttx_internal_block_Subscrib_T;

#endif                                 //typedef_nuttx_internal_block_Subscrib_T

// Forward declaration for rtModel
typedef struct tag_RTM_pubsub_monotask_T RT_MODEL_pubsub_monotask_T;

#endif                                 // RTW_HEADER_pubsub_monotask_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
