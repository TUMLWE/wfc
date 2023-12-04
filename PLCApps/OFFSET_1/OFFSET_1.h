/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OFFSET_1.h
 *
 * Code generated for Simulink model 'OFFSET_1'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec  4 03:06:35 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_OFFSET_1_h_
#define RTW_HEADER_OFFSET_1_h_
#ifndef OFFSET_1_COMMON_INCLUDES_
#define OFFSET_1_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* OFFSET_1_COMMON_INCLUDES_ */

#include "OFFSET_1_types.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: LUTOFFSET.Offset
   * Referenced by: '<S2>/n-D Lookup Table'
   */
  real_T nDLookupTable_tableData[2583];

  /* Expression: LUTOFFSET.WindSpeed
   * Referenced by: '<S2>/n-D Lookup Table'
   */
  real_T nDLookupTable_bp01Data[7];

  /* Expression: LUTOFFSET.WindDir
   * Referenced by: '<S2>/n-D Lookup Table'
   */
  real_T nDLookupTable_bp02Data[41];

  /* Expression: LUTOFFSET.TurbInt
   * Referenced by: '<S2>/n-D Lookup Table'
   */
  real_T nDLookupTable_bp03Data[3];

  /* Expression: LUTOFFSET.Shear
   * Referenced by: '<S2>/n-D Lookup Table'
   */
  real_T nDLookupTable_bp04Data[3];

  /* Computed Parameter: nDLookupTable_maxIndex
   * Referenced by: '<S2>/n-D Lookup Table'
   */
  uint32_T nDLookupTable_maxIndex[4];

  /* Computed Parameter: nDLookupTable_dimSizes
   * Referenced by: '<S2>/n-D Lookup Table'
   */
  uint32_T nDLookupTable_dimSizes[4];
} ConstP_OFFSET_1_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T input_WS_Filtered_ms;         /* '<Root>/input_WS_Filtered_ms' */
  real_T input_WDir_Filtered_deg;      /* '<Root>/input_WDir_Filtered_deg' */
  real_T input_TI_Filtered;            /* '<Root>/input_TI_Filtered' */
  real_T input_ShearExp_Filtered;      /* '<Root>/input_ShearExp_Filtered' */
  real_T input_inflowOK;               /* '<Root>/input_inflowOK' */
} ExtU_OFFSET_1_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T output_Offset_deg;            /* '<Root>/output_Offset_deg' */
  real_T output_OK;                    /* '<Root>/output_OK' */
} ExtY_OFFSET_1_T;

/* Real-time Model Data Structure */
struct tag_RTM_OFFSET_1_T {
  const char_T * volatile errorStatus;
};

/* External inputs (root inport signals with default storage) */
extern ExtU_OFFSET_1_T OFFSET_1_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_OFFSET_1_T OFFSET_1_Y;

/* Constant parameters (default storage) */
extern const ConstP_OFFSET_1_T OFFSET_1_ConstP;

/* Model entry point functions */
extern void OFFSET_1_initialize(void);
extern void OFFSET_1_step(void);
extern void OFFSET_1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_OFFSET_1_T *const OFFSET_1_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<S3>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
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
 * '<Root>' : 'OFFSET_1'
 * '<S1>'   : 'OFFSET_1/IsPositive'
 * '<S2>'   : 'OFFSET_1/Subsystem2'
 * '<S3>'   : 'OFFSET_1/Subsystem2/Interval Test'
 * '<S4>'   : 'OFFSET_1/Subsystem2/Interval Test1'
 * '<S5>'   : 'OFFSET_1/Subsystem2/Interval Test2'
 * '<S6>'   : 'OFFSET_1/Subsystem2/Interval Test3'
 */
#endif                                 /* RTW_HEADER_OFFSET_1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
