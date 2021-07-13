//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: pubsub_monotask.cpp
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
#include "pubsub_monotask.h"
#include "pubsub_monotask_private.h"

const nuttx_Bus_aa_tito_prueba pubsub_monotask_rtZnuttx_Bus_aa_tito_prueba = {
  (0ULL),                              // timestamp
  0U,                                  // armed_time_ms
  0U                                   // sine_wave
} ;                                    // nuttx_Bus_aa_tito_prueba ground

// Block signals (default storage)
B_pubsub_monotask_T pubsub_monotask_B;

// Block states (default storage)
DW_pubsub_monotask_T pubsub_monotask_DW;

// Real-time model
RT_MODEL_pubsub_monotask_T pubsub_monotask_M_ = RT_MODEL_pubsub_monotask_T();
RT_MODEL_pubsub_monotask_T *const pubsub_monotask_M = &pubsub_monotask_M_;

// Forward declaration for local functions
static void pubsub_monot_SystemCore_release(const
  nuttx_internal_block_Publishe_T *obj);
static void pubsub_monota_SystemCore_delete(const
  nuttx_internal_block_Publishe_T *obj);
static void matlabCodegenHandle_matlabCodeg(nuttx_internal_block_Publishe_T *obj);
static void pubsub_mon_SystemCore_release_a(const
  nuttx_internal_block_Subscrib_T *obj);
static void pubsub_mono_SystemCore_delete_a(const
  nuttx_internal_block_Subscrib_T *obj);
static void matlabCodegenHandle_matlabCod_a(nuttx_internal_block_Subscrib_T *obj);

//
//   This function updates active task flag for each subrate.
// The function is called in the model base rate function.
// It maintains SampleHit information to allow scheduling
// of the subrates from the base rate function.
//
void rate_scheduler(void)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (pubsub_monotask_M->Timing.TaskCounters.TID[1])++;
  if ((pubsub_monotask_M->Timing.TaskCounters.TID[1]) > 9) {// Sample time: [0.01s, 0.0s] 
    pubsub_monotask_M->Timing.TaskCounters.TID[1] = 0;
  }

  (pubsub_monotask_M->Timing.TaskCounters.TID[2])++;
  if ((pubsub_monotask_M->Timing.TaskCounters.TID[2]) > 99) {// Sample time: [0.1s, 0.0s] 
    pubsub_monotask_M->Timing.TaskCounters.TID[2] = 0;
  }
}

static void pubsub_monot_SystemCore_release(const
  nuttx_internal_block_Publishe_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    uORB_write_terminate(&obj->orbAdvertiseObj);
  }
}

static void pubsub_monota_SystemCore_delete(const
  nuttx_internal_block_Publishe_T *obj)
{
  pubsub_monot_SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(nuttx_internal_block_Publishe_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    pubsub_monota_SystemCore_delete(obj);
  }
}

static void pubsub_mon_SystemCore_release_a(const
  nuttx_internal_block_Subscrib_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    uORB_read_terminate(&obj->eventStructObj);
  }
}

static void pubsub_mono_SystemCore_delete_a(const
  nuttx_internal_block_Subscrib_T *obj)
{
  pubsub_mon_SystemCore_release_a(obj);
}

static void matlabCodegenHandle_matlabCod_a(nuttx_internal_block_Subscrib_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    pubsub_mono_SystemCore_delete_a(obj);
  }
}

// Model step function for TID0
void pubsub_monotask_step0(void)       // Sample time: [0.001s, 0.0s]
{
  // (no output/update code required)
}

// Model step function for TID1
void pubsub_monotask_step1(void)       // Sample time: [0.01s, 0.0s]
{
  nuttx_Bus_aa_tito_prueba rtb_BusAssignment;
  real_T lastSin_tmp;

  // Update the flag to indicate when data transfers from
  //   Sample time: [0.01s, 0.0s] to Sample time: [0.1s, 0.0s]
  (pubsub_monotask_M->Timing.RateInteraction.TID1_2)++;
  if ((pubsub_monotask_M->Timing.RateInteraction.TID1_2) > 9) {
    pubsub_monotask_M->Timing.RateInteraction.TID1_2 = 0;
  }

  // RateTransition: '<Root>/RT'
  if (pubsub_monotask_M->Timing.RateInteraction.TID1_2 == 1) {
    pubsub_monotask_DW.RT_RdBufIdx = static_cast<int8_T>
      (pubsub_monotask_DW.RT_RdBufIdx == 0);
  }

  // Sin: '<Root>/Sine Wave'
  if (pubsub_monotask_DW.systemEnable != 0) {
    lastSin_tmp = ((pubsub_monotask_M->Timing.clockTick1) * 0.01);
    pubsub_monotask_DW.lastSin = std::sin(lastSin_tmp);
    pubsub_monotask_DW.lastCos = std::cos(lastSin_tmp);
    pubsub_monotask_DW.systemEnable = 0;
  }

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   Constant: '<S3>/Constant'

  rtb_BusAssignment = pubsub_monotask_rtZnuttx_Bus_aa_tito_prueba;

  // DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
  //   Sin: '<Root>/Sine Wave'

  lastSin_tmp = std::floor((pubsub_monotask_DW.lastSin * 0.99995000041666526 +
    pubsub_monotask_DW.lastCos * -0.0099998333341666645) * 0.99995000041666526 +
    (pubsub_monotask_DW.lastCos * 0.99995000041666526 -
     pubsub_monotask_DW.lastSin * -0.0099998333341666645) *
    0.0099998333341666645);
  if (rtIsNaN(lastSin_tmp) || rtIsInf(lastSin_tmp)) {
    lastSin_tmp = 0.0;
  } else {
    lastSin_tmp = std::fmod(lastSin_tmp, 4.294967296E+9);
  }

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion'
  //   RateTransition: '<Root>/RT'
  //   Sum: '<Root>/Add'

  rtb_BusAssignment.sine_wave = (lastSin_tmp < 0.0 ? static_cast<uint32_T>(-
    static_cast<int32_T>(static_cast<uint32_T>(-lastSin_tmp))) : static_cast<
    uint32_T>(lastSin_tmp)) +
    pubsub_monotask_DW.RT_Buf[pubsub_monotask_DW.RT_RdBufIdx];

  // MATLABSystem: '<S1>/SinkBlock'
  uORB_write_step(pubsub_monotask_DW.obj_g.orbMetadataObj,
                  &pubsub_monotask_DW.obj_g.orbAdvertiseObj, &rtb_BusAssignment);

  // Update for Sin: '<Root>/Sine Wave'
  lastSin_tmp = pubsub_monotask_DW.lastSin;
  pubsub_monotask_DW.lastSin = pubsub_monotask_DW.lastSin * 0.99995000041666526
    + pubsub_monotask_DW.lastCos * 0.0099998333341666645;
  pubsub_monotask_DW.lastCos = pubsub_monotask_DW.lastCos * 0.99995000041666526
    - lastSin_tmp * 0.0099998333341666645;

  // Update absolute time
  // The "clockTick1" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick1" ensures timer will not overflow during the
  //  application lifespan selected.

  pubsub_monotask_M->Timing.clockTick1++;
}

// Model step function for TID2
void pubsub_monotask_step2(void)       // Sample time: [0.1s, 0.0s]
{
  nuttx_Bus_aa_tito_prueba b_varargout_2;
  boolean_T b_varargout_1;

  // MATLABSystem: '<S2>/SourceBlock' incorporates:
  //   Inport: '<S4>/In1'

  b_varargout_1 = uORB_read_step(pubsub_monotask_DW.obj.orbMetadataObj,
    &pubsub_monotask_DW.obj.eventStructObj, &b_varargout_2, false, 1.0);

  // Outputs for Enabled SubSystem: '<S2>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S4>/Enable'

  if (b_varargout_1) {
    pubsub_monotask_B.In1 = b_varargout_2;
  }

  // End of MATLABSystem: '<S2>/SourceBlock'
  // End of Outputs for SubSystem: '<S2>/Enabled Subsystem'

  // Update for RateTransition: '<Root>/RT'
  pubsub_monotask_DW.RT_WrBufIdx = static_cast<int8_T>
    (pubsub_monotask_DW.RT_WrBufIdx == 0);
  pubsub_monotask_DW.RT_Buf[pubsub_monotask_DW.RT_WrBufIdx] =
    pubsub_monotask_B.In1.sine_wave;
}

// Model step wrapper function for compatibility with a static main program
void pubsub_monotask_step(int_T tid)
{
  switch (tid) {
   case 0 :
    pubsub_monotask_step0();
    break;

   case 1 :
    pubsub_monotask_step1();
    break;

   case 2 :
    pubsub_monotask_step2();
    break;

   default :
    break;
  }
}

// Model initialize function
void pubsub_monotask_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  (pubsub_monotask_M)->Timing.TaskCounters.cLimit[0] = 1;
  (pubsub_monotask_M)->Timing.TaskCounters.cLimit[1] = 10;
  (pubsub_monotask_M)->Timing.TaskCounters.cLimit[2] = 100;

  {
    nuttx_Bus_aa_tito_prueba rtb_BusAssignment;

    // InitializeConditions for RateTransition: '<Root>/RT'
    pubsub_monotask_DW.RT_RdBufIdx = 1;

    // Start for MATLABSystem: '<S1>/SinkBlock'
    pubsub_monotask_DW.obj_g.matlabCodegenIsDeleted = false;
    pubsub_monotask_DW.obj_g.isSetupComplete = false;
    pubsub_monotask_DW.obj_g.isInitialized = 1;
    pubsub_monotask_DW.obj_g.orbMetadataObj = ORB_ID(aa_tito_prueba);
    uORB_write_initialize(pubsub_monotask_DW.obj_g.orbMetadataObj,
                          &pubsub_monotask_DW.obj_g.orbAdvertiseObj,
                          &rtb_BusAssignment, 1);
    pubsub_monotask_DW.obj_g.isSetupComplete = true;

    // Start for MATLABSystem: '<S2>/SourceBlock'
    pubsub_monotask_DW.obj.matlabCodegenIsDeleted = false;
    pubsub_monotask_DW.obj.isSetupComplete = false;
    pubsub_monotask_DW.obj.isInitialized = 1;
    pubsub_monotask_DW.obj.orbMetadataObj = ORB_ID(aa_tito_prueba);
    uORB_read_initialize(pubsub_monotask_DW.obj.orbMetadataObj,
                         &pubsub_monotask_DW.obj.eventStructObj);
    pubsub_monotask_DW.obj.isSetupComplete = true;

    // Enable for Sin: '<Root>/Sine Wave'
    pubsub_monotask_DW.systemEnable = 1;
  }
}

// Model terminate function
void pubsub_monotask_terminate(void)
{
  // Terminate for MATLABSystem: '<S1>/SinkBlock'
  matlabCodegenHandle_matlabCodeg(&pubsub_monotask_DW.obj_g);

  // Terminate for MATLABSystem: '<S2>/SourceBlock'
  matlabCodegenHandle_matlabCod_a(&pubsub_monotask_DW.obj);
}

//
// File trailer for generated code.
//
// [EOF]
//
