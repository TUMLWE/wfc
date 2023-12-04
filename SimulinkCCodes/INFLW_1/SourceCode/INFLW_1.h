/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: INFLW_1.h
 *
 * Code generated for Simulink model 'INFLW_1'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Sun Dec  3 21:59:01 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_INFLW_1_h_
#define RTW_HEADER_INFLW_1_h_
#ifndef INFLW_1_COMMON_INCLUDES_
#define INFLW_1_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* INFLW_1_COMMON_INCLUDES_ */

#include "INFLW_1_types.h"
#include "rtGetInf.h"
#include <stddef.h>
#include <string.h>
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals for system '<Root>/Moving Average2' */
typedef struct {
  real_T csumrev[5999];
  real_T MovingAverage2;               /* '<Root>/Moving Average2' */
} B_MovingAverage2_INFLW_1_T;

/* Block states (default storage) for system '<Root>/Moving Average2' */
typedef struct {
  dsp_simulink_MovingAverage_IN_T obj; /* '<Root>/Moving Average2' */
  boolean_T objisempty;                /* '<Root>/Moving Average2' */
} DW_MovingAverage2_INFLW_1_T;

/* Block signals for system '<S6>/Moving Average5' */
typedef struct {
  real_T csumrev[599];
  real_T MovingAverage5;               /* '<S6>/Moving Average5' */
} B_MovingAverage5_INFLW_1_T;

/* Block states (default storage) for system '<S6>/Moving Average5' */
typedef struct {
  dsp_simulink_MovingAverage_e_T obj;  /* '<S6>/Moving Average5' */
  boolean_T objisempty;                /* '<S6>/Moving Average5' */
} DW_MovingAverage5_INFLW_1_T;

/* Block signals for system '<S6>/Moving Standard Deviation1' */
typedef struct {
  real_T reverseSamples[600];
  real_T reverseS[600];
  real_T x[600];
  real_T MovingStandardDeviation1;     /* '<S6>/Moving Standard Deviation1' */
} B_MovingStandardDeviation1_IN_T;

/* Block states (default storage) for system '<S6>/Moving Standard Deviation1' */
typedef struct {
  dsp_simulink_MovingStandardDe_T obj; /* '<S6>/Moving Standard Deviation1' */
  boolean_T objisempty;                /* '<S6>/Moving Standard Deviation1' */
} DW_MovingStandardDeviation1_I_T;

/* Block signals (default storage) */
typedef struct {
  real_T reverseSamples[6000];
  real_T reverseS[6000];
  real_T x[6000];
  creal_T csumrev[999];
  real_T reverseSamples_m[600];
  real_T reverseS_c[600];
  real_T x_k[600];
  B_MovingAverage5_INFLW_1_T MovingAverage5_pn;/* '<S6>/Moving Average5' */
  B_MovingStandardDeviation1_IN_T MovingStandardDeviation1_p;/* '<S6>/Moving Standard Deviation1' */
  B_MovingAverage5_INFLW_1_T MovingAverage5_p;/* '<S6>/Moving Average5' */
  B_MovingStandardDeviation1_IN_T MovingStandardDeviation1;/* '<S6>/Moving Standard Deviation1' */
  B_MovingAverage5_INFLW_1_T MovingAverage5;/* '<S6>/Moving Average5' */
  B_MovingAverage2_INFLW_1_T MovingAverage3;/* '<Root>/Moving Average2' */
  B_MovingAverage2_INFLW_1_T MovingAverage2;/* '<Root>/Moving Average2' */
} B_INFLW_1_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  dsp_simulink_MovingStandard_m_T obj; /* '<Root>/Moving Standard Deviation' */
  dsp_simulink_MovingAverage_ma_T obj_p;/* '<S9>/Moving Average1' */
  dsp_simulink_MovingStandardDe_T obj_c;/* '<S8>/Moving Standard Deviation1' */
  dsp_simulink_MovingAverage_m_T obj_k;/* '<Root>/Moving Average' */
  real_T UnitDelay1_DSTATE;            /* '<S15>/Unit Delay1' */
  real_T Delay_DSTATE;                 /* '<S8>/Delay' */
  real_T UnitDelay1_DSTATE_n;          /* '<S19>/Unit Delay1' */
  real_T Delay_DSTATE_c;               /* '<S7>/Delay' */
  real_T UnitDelay1_DSTATE_n3;         /* '<S17>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_h;          /* '<S12>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_i;          /* '<S11>/Unit Delay1' */
  real_T Delay_DSTATE_p;               /* '<S6>/Delay' */
  boolean_T UnitDelay2_DSTATE;         /* '<S15>/Unit Delay2' */
  boolean_T UnitDelay2_DSTATE_m;       /* '<S19>/Unit Delay2' */
  boolean_T UnitDelay2_DSTATE_n;       /* '<S17>/Unit Delay2' */
  boolean_T UnitDelay2_DSTATE_f;       /* '<S12>/Unit Delay2' */
  boolean_T UnitDelay2_DSTATE_j;       /* '<S11>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE;         /* '<S11>/Unit Delay3' */
  boolean_T UnitDelay3_DSTATE_p;       /* '<S12>/Unit Delay3' */
  boolean_T UnitDelay3_DSTATE_pl;      /* '<S17>/Unit Delay3' */
  boolean_T UnitDelay3_DSTATE_a;       /* '<S19>/Unit Delay3' */
  boolean_T UnitDelay3_DSTATE_f;       /* '<S15>/Unit Delay3' */
  DW_MovingAverage5_INFLW_1_T MovingAverage5_pn;/* '<S6>/Moving Average5' */
  DW_MovingStandardDeviation1_I_T MovingStandardDeviation1_p;/* '<S6>/Moving Standard Deviation1' */
  DW_MovingAverage5_INFLW_1_T MovingAverage5_p;/* '<S6>/Moving Average5' */
  DW_MovingStandardDeviation1_I_T MovingStandardDeviation1;/* '<S6>/Moving Standard Deviation1' */
  DW_MovingAverage5_INFLW_1_T MovingAverage5;/* '<S6>/Moving Average5' */
  DW_MovingAverage2_INFLW_1_T MovingAverage3;/* '<Root>/Moving Average2' */
  DW_MovingAverage2_INFLW_1_T MovingAverage2;/* '<Root>/Moving Average2' */
} DW_INFLW_1_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T input_WS_ms;                  /* '<Root>/input_WS_ms' */
  real_T input_Dir_deg;                /* '<Root>/input_Dir_deg' */
  real_T input_WS_54m;                 /* '<Root>/input_WS_54m' */
} ExtU_INFLW_1_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T output_WS;                    /* '<Root>/output_WS' */
  real_T output_WDir;                  /* '<Root>/output_WDir' */
  real_T output_TI;                    /* '<Root>/output_TI' */
  real_T output_ShearExp;              /* '<Root>/output_ShearExp' */
  real_T output_InflowOK;              /* '<Root>/output_InflowOK' */
} ExtY_INFLW_1_T;

/* Real-time Model Data Structure */
struct tag_RTM_INFLW_1_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_INFLW_1_T INFLW_1_B;

/* Block states (default storage) */
extern DW_INFLW_1_T INFLW_1_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_INFLW_1_T INFLW_1_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_INFLW_1_T INFLW_1_Y;

/* Model entry point functions */
extern void INFLW_1_initialize(void);
extern void INFLW_1_step(void);
extern void INFLW_1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_INFLW_1_T *const INFLW_1_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/CheckInputAndFlags' : Unused code path elimination
 * Block '<Root>/Scope' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<S12>/Scope1' : Unused code path elimination
 * Block '<S11>/Scope1' : Unused code path elimination
 * Block '<S15>/Scope1' : Unused code path elimination
 * Block '<S17>/Scope1' : Unused code path elimination
 * Block '<S19>/Scope1' : Unused code path elimination
 * Block '<S21>/Data Type Duplicate' : Unused code path elimination
 * Block '<S21>/Data Type Propagation' : Unused code path elimination
 * Block '<S26>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Data Type Propagation' : Unused code path elimination
 * Block '<S31>/Data Type Duplicate' : Unused code path elimination
 * Block '<S31>/Data Type Propagation' : Unused code path elimination
 * Block '<S12>/Saturation' : Eliminated Saturate block
 * Block '<S11>/Saturation' : Eliminated Saturate block
 * Block '<S15>/Saturation' : Eliminated Saturate block
 * Block '<S17>/Saturation' : Eliminated Saturate block
 * Block '<S19>/Saturation' : Eliminated Saturate block
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
 * '<Root>' : 'INFLW_1'
 * '<S1>'   : 'INFLW_1/MATLAB Function'
 * '<S2>'   : 'INFLW_1/Subsystem'
 * '<S3>'   : 'INFLW_1/Subsystem1'
 * '<S4>'   : 'INFLW_1/Subsystem2'
 * '<S5>'   : 'INFLW_1/Subsystem3'
 * '<S6>'   : 'INFLW_1/Subsystem4'
 * '<S7>'   : 'INFLW_1/Subsystem5'
 * '<S8>'   : 'INFLW_1/Subsystem6'
 * '<S9>'   : 'INFLW_1/Subsystem7'
 * '<S10>'  : 'INFLW_1/Subsystem/Subsystem'
 * '<S11>'  : 'INFLW_1/Subsystem/Subsystem1'
 * '<S12>'  : 'INFLW_1/Subsystem/Subsystem/Subsystem1'
 * '<S13>'  : 'INFLW_1/Subsystem/Subsystem/Subsystem1/Compare To Zero'
 * '<S14>'  : 'INFLW_1/Subsystem/Subsystem1/Compare To Zero'
 * '<S15>'  : 'INFLW_1/Subsystem1/Subsystem1'
 * '<S16>'  : 'INFLW_1/Subsystem1/Subsystem1/Compare To Zero'
 * '<S17>'  : 'INFLW_1/Subsystem2/Subsystem1'
 * '<S18>'  : 'INFLW_1/Subsystem2/Subsystem1/Compare To Zero'
 * '<S19>'  : 'INFLW_1/Subsystem3/Subsystem1'
 * '<S20>'  : 'INFLW_1/Subsystem3/Subsystem1/Compare To Zero'
 * '<S21>'  : 'INFLW_1/Subsystem4/Saturation Dynamic'
 * '<S22>'  : 'INFLW_1/Subsystem4/Subsystem4'
 * '<S23>'  : 'INFLW_1/Subsystem4/Subsystem5'
 * '<S24>'  : 'INFLW_1/Subsystem4/Subsystem4/Compare To Constant'
 * '<S25>'  : 'INFLW_1/Subsystem4/Subsystem5/Compare To Constant'
 * '<S26>'  : 'INFLW_1/Subsystem5/Saturation Dynamic'
 * '<S27>'  : 'INFLW_1/Subsystem5/Subsystem4'
 * '<S28>'  : 'INFLW_1/Subsystem5/Subsystem5'
 * '<S29>'  : 'INFLW_1/Subsystem5/Subsystem4/Compare To Constant'
 * '<S30>'  : 'INFLW_1/Subsystem5/Subsystem5/Compare To Constant'
 * '<S31>'  : 'INFLW_1/Subsystem6/Saturation Dynamic'
 * '<S32>'  : 'INFLW_1/Subsystem6/Subsystem4'
 * '<S33>'  : 'INFLW_1/Subsystem6/Subsystem5'
 * '<S34>'  : 'INFLW_1/Subsystem6/Subsystem4/Compare To Constant'
 * '<S35>'  : 'INFLW_1/Subsystem6/Subsystem5/Compare To Constant'
 */
#endif                                 /* RTW_HEADER_INFLW_1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
