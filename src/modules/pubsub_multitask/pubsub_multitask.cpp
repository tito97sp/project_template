//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: pubsub_multitask.cpp
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
#include "pubsub_multitask.h"
#include "pubsub_multitask_private.h"
#include "stdio.h"

// Named constants for Chart: '<Root>/Chart'
const uint8_T pubsub_multitask_IN_Check = 1U;
const uint8_T pubsub_multitask_IN_Check1 = 2U;
const nuttx_Bus_aa_tito_prueba pubsub_multitask_rtZnuttx_Bus_aa_tito_prueba = {
  (0ULL),                              // timestamp
  0U,                                  // armed_time_ms
  0                                    // sine_wave
} ;                                    // nuttx_Bus_aa_tito_prueba ground

const nuttx_Bus_aa_tito_prueba2 pubsub_multitask_rtZnuttx_Bus_aa_tito_prueba2 =
  {
  (0ULL),                              // timestamp
  0U,                                  // armed_time_ms
  0,                                   // state

  {
    0U, 0U, 0U }
  // _padding0
} ;                                    // nuttx_Bus_aa_tito_prueba2 ground

// Block signals (default storage)
B_pubsub_multitask_T pubsub_multitask_B;

// Block states (default storage)
DW_pubsub_multitask_T pubsub_multitask_DW;

// Real-time model
RT_MODEL_pubsub_multitask_T pubsub_multitask_M_ = RT_MODEL_pubsub_multitask_T();
RT_MODEL_pubsub_multitask_T *const pubsub_multitask_M = &pubsub_multitask_M_;

// Forward declaration for local functions
static void pubsub_multitask_SystemCore_release(const
  nuttx_internal_block_Publisher_pubsub_multitask_T *obj);
static void pubsub_multitask_SystemCore_delete(const
  nuttx_internal_block_Publisher_pubsub_multitask_T *obj);
static void pubsub_multitask_matlabCodegenHandle_matlabCodegenDestructor
  (nuttx_internal_block_Publisher_pubsub_multitask_T *obj);
static void pubsub_multitask_SystemCore_release_fr(const
  nuttx_internal_block_Subscriber_pubsub_multitask_T *obj);
static void pubsub_multitask_SystemCore_delete_fr(const
  nuttx_internal_block_Subscriber_pubsub_multitask_T *obj);
static void pubsub_multitask_matlabCodegenHandle_matlabCodegenDestructor_fr
  (nuttx_internal_block_Subscriber_pubsub_multitask_T *obj);

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

  (pubsub_multitask_M->Timing.TaskCounters.TID[1])++;
  if ((pubsub_multitask_M->Timing.TaskCounters.TID[1]) > 9) {// Sample time: [0.1s, 0.0s] 
    pubsub_multitask_M->Timing.TaskCounters.TID[1] = 0;
  }
}

static void pubsub_multitask_SystemCore_release(const
  nuttx_internal_block_Publisher_pubsub_multitask_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    uORB_write_terminate(&obj->orbAdvertiseObj);
  }
}

static void pubsub_multitask_SystemCore_delete(const
  nuttx_internal_block_Publisher_pubsub_multitask_T *obj)
{
  pubsub_multitask_SystemCore_release(obj);
}

static void pubsub_multitask_matlabCodegenHandle_matlabCodegenDestructor
  (nuttx_internal_block_Publisher_pubsub_multitask_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    pubsub_multitask_SystemCore_delete(obj);
  }
}

static void pubsub_multitask_SystemCore_release_fr(const
  nuttx_internal_block_Subscriber_pubsub_multitask_T *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    uORB_read_terminate(&obj->eventStructObj);
  }
}

static void pubsub_multitask_SystemCore_delete_fr(const
  nuttx_internal_block_Subscriber_pubsub_multitask_T *obj)
{
  pubsub_multitask_SystemCore_release_fr(obj);
}

static void pubsub_multitask_matlabCodegenHandle_matlabCodegenDestructor_fr
  (nuttx_internal_block_Subscriber_pubsub_multitask_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    pubsub_multitask_SystemCore_delete_fr(obj);
  }
}

// Model step function for TID0
void pubsub_multitask_step0(void)      // Sample time: [0.01s, 0.0s]
{
  nuttx_Bus_aa_tito_prueba rtb_BusAssignment;
  real_T lastSin_tmp;

  // Sin: '<Root>/Sine Wave'
  if (pubsub_multitask_DW.systemEnable != 0) {
    lastSin_tmp = 6.2831853071795862 * ((pubsub_multitask_M->Timing.clockTick0) *
      0.01);
    pubsub_multitask_DW.lastSin = std::sin(lastSin_tmp);
    pubsub_multitask_DW.lastCos = std::cos(lastSin_tmp);
    pubsub_multitask_DW.systemEnable = 0;
  }

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   Constant: '<S5>/Constant'

  rtb_BusAssignment = pubsub_multitask_rtZnuttx_Bus_aa_tito_prueba;

  // DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
  //   Sin: '<Root>/Sine Wave'

  lastSin_tmp = std::floor(((pubsub_multitask_DW.lastSin * 0.99802672842827156 +
    pubsub_multitask_DW.lastCos * -0.062790519529313374) * 0.99802672842827156 +
    (pubsub_multitask_DW.lastCos * 0.99802672842827156 -
     pubsub_multitask_DW.lastSin * -0.062790519529313374) * 0.062790519529313374)
    * 100.0);
  if (rtIsNaN(lastSin_tmp) || rtIsInf(lastSin_tmp)) {
    lastSin_tmp = 0.0;
  } else {
    lastSin_tmp = std::fmod(lastSin_tmp, 4.294967296E+9);
  }

  // BusAssignment: '<Root>/Bus Assignment' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion'

  rtb_BusAssignment.sine_wave = lastSin_tmp < 0.0 ? -static_cast<int32_T>(
    static_cast<uint32_T>(-lastSin_tmp)) : static_cast<int32_T>
    (static_cast<uint32_T>(lastSin_tmp));

  // MATLABSystem: '<S2>/SinkBlock'
  uORB_write_step(pubsub_multitask_DW.obj_g.orbMetadataObj,
                  &pubsub_multitask_DW.obj_g.orbAdvertiseObj, &rtb_BusAssignment);

  // Update for Sin: '<Root>/Sine Wave'
  lastSin_tmp = pubsub_multitask_DW.lastSin;
  pubsub_multitask_DW.lastSin = pubsub_multitask_DW.lastSin *
    0.99802672842827156 + pubsub_multitask_DW.lastCos * 0.062790519529313374;
  pubsub_multitask_DW.lastCos = pubsub_multitask_DW.lastCos *
    0.99802672842827156 - lastSin_tmp * 0.062790519529313374;

  // Update absolute time
  // The "clockTick0" counts the number of times the code of this task has
  //  been executed. The resolution of this integer timer is 0.01, which is the step size
  //  of the task. Size of "clockTick0" ensures timer will not overflow during the
  //  application lifespan selected.

  pubsub_multitask_M->Timing.clockTick0++;
}

// Model step function for TID1
void pubsub_multitask_step1(void)      // Sample time: [0.1s, 0.0s]
{
  nuttx_Bus_aa_tito_prueba b_varargout_2;
  boolean_T b_varargout_1;
  nuttx_Bus_aa_tito_prueba2 rtb_BusAssignment1;
  int32_T rtb_output_1;

  // MATLABSystem: '<S4>/SourceBlock' incorporates:
  //   Inport: '<S7>/In1'

  b_varargout_1 = uORB_read_step(pubsub_multitask_DW.obj.orbMetadataObj,
    &pubsub_multitask_DW.obj.eventStructObj, &b_varargout_2, false, 1.0);

  // Outputs for Enabled SubSystem: '<S4>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S7>/Enable'

  if (b_varargout_1) {
    pubsub_multitask_B.In1 = b_varargout_2;
  }

  
  // End of MATLABSystem: '<S4>/SourceBlock'
  // End of Outputs for SubSystem: '<S4>/Enabled Subsystem'

  // Chart: '<Root>/Chart'
  if (pubsub_multitask_DW.is_active_c3_pubsub_multitask == 0U) {
    pubsub_multitask_DW.is_active_c3_pubsub_multitask = 1U;
    pubsub_multitask_DW.is_c3_pubsub_multitask = pubsub_multitask_IN_Check;
    rtb_output_1 = -1;
  } else if (pubsub_multitask_DW.is_c3_pubsub_multitask ==
             pubsub_multitask_IN_Check) {
    rtb_output_1 = -1;
    if (pubsub_multitask_B.In1.sine_wave < 0) {
      pubsub_multitask_DW.is_c3_pubsub_multitask = pubsub_multitask_IN_Check1;
      rtb_output_1 = 1;
    }
  } else {
    // case IN_Check1:
    rtb_output_1 = 1;
    if (pubsub_multitask_B.In1.sine_wave > 0) {
      pubsub_multitask_DW.is_c3_pubsub_multitask = pubsub_multitask_IN_Check;
      rtb_output_1 = -1;
    }
  }

  // End of Chart: '<Root>/Chart'

  // BusAssignment: '<Root>/Bus Assignment1' incorporates:
  //   Constant: '<S6>/Constant'

  rtb_BusAssignment1 = pubsub_multitask_rtZnuttx_Bus_aa_tito_prueba2;

  // DataTypeConversion: '<Root>/Data Type Conversion1'
  rtb_output_1 = static_cast<int32_T>(std::fmod(static_cast<real_T>(rtb_output_1),
    256.0));

  // BusAssignment: '<Root>/Bus Assignment1' incorporates:
  //   DataTypeConversion: '<Root>/Data Type Conversion1'

  rtb_BusAssignment1.state = static_cast<int8_T>(rtb_output_1 < 0 ? static_cast<
    int32_T>(static_cast<int8_T>(-static_cast<int8_T>(static_cast<uint8_T>(-
    static_cast<real_T>(rtb_output_1))))) : static_cast<int32_T>(static_cast<
    int8_T>(rtb_output_1)));



  // MATLABSystem: '<S3>/SinkBlock'
  uORB_write_step(pubsub_multitask_DW.obj_e.orbMetadataObj,
                  &pubsub_multitask_DW.obj_e.orbAdvertiseObj,
                  &rtb_BusAssignment1);
                
}

// Model step wrapper function for compatibility with a static main program
void pubsub_multitask_step(int_T tid)
{
  switch (tid) {
   case 0 :
    pubsub_multitask_step0();
    break;

   case 1 :
    pubsub_multitask_step1();
    break;

   default :
    break;
  }
}

// Model initialize function
void pubsub_multitask_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  (pubsub_multitask_M)->Timing.TaskCounters.cLimit[0] = 1;
  (pubsub_multitask_M)->Timing.TaskCounters.cLimit[1] = 10;

  {
    nuttx_Bus_aa_tito_prueba2 rtb_BusAssignment1;
    nuttx_Bus_aa_tito_prueba rtb_BusAssignment;

    // Start for MATLABSystem: '<S2>/SinkBlock'
    pubsub_multitask_DW.obj_g.matlabCodegenIsDeleted = false;
    pubsub_multitask_DW.obj_g.isSetupComplete = false;
    pubsub_multitask_DW.obj_g.isInitialized = 1;
    pubsub_multitask_DW.obj_g.orbMetadataObj = ORB_ID(aa_tito_prueba);
    uORB_write_initialize(pubsub_multitask_DW.obj_g.orbMetadataObj,
                          &pubsub_multitask_DW.obj_g.orbAdvertiseObj,
                          &rtb_BusAssignment, 1);
    pubsub_multitask_DW.obj_g.isSetupComplete = true;

    // Start for MATLABSystem: '<S4>/SourceBlock'
    pubsub_multitask_DW.obj.matlabCodegenIsDeleted = false;
    pubsub_multitask_DW.obj.isSetupComplete = false;
    pubsub_multitask_DW.obj.isInitialized = 1;
    pubsub_multitask_DW.obj.orbMetadataObj = ORB_ID(aa_tito_prueba);
    uORB_read_initialize(pubsub_multitask_DW.obj.orbMetadataObj,
                         &pubsub_multitask_DW.obj.eventStructObj);
    pubsub_multitask_DW.obj.isSetupComplete = true;

    // Start for MATLABSystem: '<S3>/SinkBlock'
    pubsub_multitask_DW.obj_e.matlabCodegenIsDeleted = false;
    pubsub_multitask_DW.obj_e.isSetupComplete = false;
    pubsub_multitask_DW.obj_e.isInitialized = 1;
    pubsub_multitask_DW.obj_e.orbMetadataObj = ORB_ID(aa_tito_prueba2);
    uORB_write_initialize(pubsub_multitask_DW.obj_e.orbMetadataObj,
                          &pubsub_multitask_DW.obj_e.orbAdvertiseObj,
                          &rtb_BusAssignment1, 1);
    pubsub_multitask_DW.obj_e.isSetupComplete = true;

    // Enable for Sin: '<Root>/Sine Wave'
    pubsub_multitask_DW.systemEnable = 1;
  }
}

// Model terminate function
void pubsub_multitask_terminate(void)
{
  // Terminate for MATLABSystem: '<S2>/SinkBlock'
  pubsub_multitask_matlabCodegenHandle_matlabCodegenDestructor
    (&pubsub_multitask_DW.obj_g);

  // Terminate for MATLABSystem: '<S4>/SourceBlock'
  pubsub_multitask_matlabCodegenHandle_matlabCodegenDestructor_fr
    (&pubsub_multitask_DW.obj);

  // Terminate for MATLABSystem: '<S3>/SinkBlock'
  pubsub_multitask_matlabCodegenHandle_matlabCodegenDestructor
    (&pubsub_multitask_DW.obj_e);
}

//
// File trailer for generated code.
//
// [EOF]
//
