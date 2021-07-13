//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: pubsub_multitask_types.h
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
#ifndef RTW_HEADER_pubsub_multitask_types_h_
#define RTW_HEADER_pubsub_multitask_types_h_
#include "rtwtypes.h"
#include <uORB/topics/aa_tito_prueba.h>
#include <uORB/topics/aa_tito_prueba2.h>

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

#ifndef typedef_nuttx_internal_block_Publisher_pubsub_multitask_T
#define typedef_nuttx_internal_block_Publisher_pubsub_multitask_T

typedef struct tag_hYhAI2VNT1j8Vnv0YZeb1D
  nuttx_internal_block_Publisher_pubsub_multitask_T;

#endif               //typedef_nuttx_internal_block_Publisher_pubsub_multitask_T

#ifndef struct_tag_YgA2umAxY1QaUdNJg8JkbB
#define struct_tag_YgA2umAxY1QaUdNJg8JkbB

struct tag_YgA2umAxY1QaUdNJg8JkbB
{
  int32_T __dummy;
};

#endif                                 //struct_tag_YgA2umAxY1QaUdNJg8JkbB

#ifndef typedef_b_px4_internal_block_SampleTimeImpl_pubsub_multitask_T
#define typedef_b_px4_internal_block_SampleTimeImpl_pubsub_multitask_T

typedef struct tag_YgA2umAxY1QaUdNJg8JkbB
  b_px4_internal_block_SampleTimeImpl_pubsub_multitask_T;

#endif          //typedef_b_px4_internal_block_SampleTimeImpl_pubsub_multitask_T

#ifndef struct_tag_TU9Rnn74ZJKi9RaH5Ax4lF
#define struct_tag_TU9Rnn74ZJKi9RaH5Ax4lF

struct tag_TU9Rnn74ZJKi9RaH5Ax4lF
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  b_px4_internal_block_SampleTimeImpl_pubsub_multitask_T SampleTimeHandler;
  pollfd_t eventStructObj;
  orb_metadata_t * orbMetadataObj;
};

#endif                                 //struct_tag_TU9Rnn74ZJKi9RaH5Ax4lF

#ifndef typedef_nuttx_internal_block_Subscriber_pubsub_multitask_T
#define typedef_nuttx_internal_block_Subscriber_pubsub_multitask_T

typedef struct tag_TU9Rnn74ZJKi9RaH5Ax4lF
  nuttx_internal_block_Subscriber_pubsub_multitask_T;

#endif              //typedef_nuttx_internal_block_Subscriber_pubsub_multitask_T

// Forward declaration for rtModel
typedef struct tag_RTM_pubsub_multitask_T RT_MODEL_pubsub_multitask_T;

#endif                                 // RTW_HEADER_pubsub_multitask_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
