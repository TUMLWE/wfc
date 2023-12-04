/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OFFSET_3.h
 *
 * Code generated for Simulink model 'OFFSET_3'.
 *
 * Model version                  : 1.5
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec  4 03:09:55 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_OFFSET_3_h_
#define RTW_HEADER_OFFSET_3_h_
#ifndef OFFSET_3_COMMON_INCLUDES_
#define OFFSET_3_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* OFFSET_3_COMMON_INCLUDES_ */

#include "OFFSET_3_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include <stddef.h>
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay1_DSTATE;            /* '<Root>/Unit Delay1' */
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
} DW_OFFSET_3_T;

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [0 15 0 -15]
   * Referenced by: '<Root>/possible_offsets'
   */
  real_T possible_offsets_Value[4];
} ConstP_OFFSET_3_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T output_Offset_deg;            /* '<Root>/output_Offset_deg' */
} ExtY_OFFSET_3_T;

/* Real-time Model Data Structure */
struct tag_RTM_OFFSET_3_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_OFFSET_3_T OFFSET_3_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_OFFSET_3_T OFFSET_3_Y;

/* Constant parameters (default storage) */
extern const ConstP_OFFSET_3_T OFFSET_3_ConstP;

/* Model entry point functions */
extern void OFFSET_3_initialize(void);
extern void OFFSET_3_step(void);
extern void OFFSET_3_terminate(void);

/* Real-time Model object */
extern RT_MODEL_OFFSET_3_T *const OFFSET_3_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'OFFSET_3'
 * '<S1>'   : 'OFFSET_3/MATLAB Function'
 */
#endif                                 /* RTW_HEADER_OFFSET_3_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
