/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OFFSET_3.c
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

#include "OFFSET_3.h"
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Block states (default storage) */
DW_OFFSET_3_T OFFSET_3_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_OFFSET_3_T OFFSET_3_Y;

/* Real-time model */
static RT_MODEL_OFFSET_3_T OFFSET_3_M_;
RT_MODEL_OFFSET_3_T *const OFFSET_3_M = &OFFSET_3_M_;

/* Forward declaration for local functions */
static real_T OFFSET_3_mod(real_T x);

/* Function for MATLAB Function: '<Root>/MATLAB Function' */
static real_T OFFSET_3_mod(real_T x)
{
  real_T r;
  if (rtIsNaN(x)) {
    r = (rtNaN);
  } else if (rtIsInf(x)) {
    r = (rtNaN);
  } else if (x == 0.0) {
    r = 0.0;
  } else {
    r = fmod(x, 4.0);
    if (r == 0.0) {
      r = 0.0;
    } else if (x < 0.0) {
      r += 4.0;
    }
  }

  return r;
}

/* Model step function */
void OFFSET_3_step(void)
{
  real_T cn;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Constant: '<Root>/Nmax'
   *  UnitDelay: '<Root>/Unit Delay'
   *  UnitDelay: '<Root>/Unit Delay1'
   */
  if (rtIsNaN(OFFSET_3_DW.UnitDelay_DSTATE + 1.0)) {
    cn = (rtNaN);
  } else if (rtIsInf(OFFSET_3_DW.UnitDelay_DSTATE + 1.0)) {
    cn = (rtNaN);
  } else if (OFFSET_3_DW.UnitDelay_DSTATE + 1.0 == 0.0) {
    cn = 0.0;
  } else {
    cn = fmod(OFFSET_3_DW.UnitDelay_DSTATE + 1.0, 19500.0);
    if (cn == 0.0) {
      cn = 0.0;
    } else if (OFFSET_3_DW.UnitDelay_DSTATE + 1.0 < 0.0) {
      cn += 19500.0;
    }
  }

  if (cn != 0.0) {
    OFFSET_3_DW.UnitDelay1_DSTATE = OFFSET_3_mod(OFFSET_3_DW.UnitDelay1_DSTATE);
  } else {
    OFFSET_3_DW.UnitDelay1_DSTATE = OFFSET_3_mod(OFFSET_3_DW.UnitDelay1_DSTATE +
      1.0);
  }

  /* Outport: '<Root>/output_Offset_deg' incorporates:
   *  Constant: '<Root>/possible_offsets'
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  OFFSET_3_Y.output_Offset_deg = OFFSET_3_ConstP.possible_offsets_Value[(int32_T)
    (OFFSET_3_DW.UnitDelay1_DSTATE + 1.0) - 1];

  /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function'
   */
  OFFSET_3_DW.UnitDelay_DSTATE = cn;
}

/* Model initialize function */
void OFFSET_3_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(OFFSET_3_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&OFFSET_3_DW, 0,
                sizeof(DW_OFFSET_3_T));

  /* external outputs */
  OFFSET_3_Y.output_Offset_deg = 0.0;
}

/* Model terminate function */
void OFFSET_3_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
