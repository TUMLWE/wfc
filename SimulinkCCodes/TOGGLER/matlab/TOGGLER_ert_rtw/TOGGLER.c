/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TOGGLER.c
 *
 * Code generated for Simulink model 'TOGGLER'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec  4 00:17:56 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "TOGGLER.h"
#include "rtwtypes.h"
#include "TOGGLER_types.h"
#include "TOGGLER_private.h"
#include <string.h>
#include <math.h>
#include "rt_nonfinite.h"
#include <float.h>
#include "rt_defines.h"
#include "zero_crossing_types.h"

/* Block signals (default storage) */
B_TOGGLER_T TOGGLER_B;

/* Block states (default storage) */
DW_TOGGLER_T TOGGLER_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_TOGGLER_T TOGGLER_PrevZCX;

/* External inputs (root inport signals with default storage) */
ExtU_TOGGLER_T TOGGLER_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_TOGGLER_T TOGGLER_Y;

/* Real-time model */
static RT_MODEL_TOGGLER_T TOGGLER_M_;
RT_MODEL_TOGGLER_T *const TOGGLER_M = &TOGGLER_M_;

/* Forward declaration for local functions */
static real_T TOGGLER_mod(real_T x);
static void TOGGLER_SystemCore_setup(dsp_simulink_MovingStandardDe_T *obj);
static void TOGGLER_SystemCore_setup_gi(dsp_simulink_MovingAverage_TO_T *obj);

/*
 * Output and update for action system:
 *    '<Root>/Set offset to zero'
 *    '<Root>/If Action Subsystem'
 *    '<Root>/If Action Subsystem6'
 */
void TOGGLER_Setoffsettozero(real_T *rty_Out1)
{
  /* SignalConversion generated from: '<S14>/Out1' incorporates:
   *  Constant: '<S14>/Zero'
   */
  *rty_Out1 = 0.0;
}

/*
 * Output and update for atomic system:
 *    '<S68>/MATLAB Function'
 *    '<S79>/MATLAB Function'
 */
void TOGGLER_MATLABFunction(const boolean_T rtu_CTRLToStopVec[4], const real_T
  rtu_CTRLList[4], real_T *rty_CTRLToSkip, real_T *rty_iL)
{
  int32_T b_iL;
  int32_T iL;
  *rty_CTRLToSkip = 0.0;
  b_iL = 0;
  int32_T exitg1;
  do {
    exitg1 = 0;
    if (b_iL < 4) {
      iL = b_iL + 1;
      if (rtu_CTRLToStopVec[b_iL]) {
        *rty_CTRLToSkip = rtu_CTRLList[b_iL];
        exitg1 = 1;
      } else {
        b_iL++;
      }
    } else {
      iL = 0;
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  *rty_iL = iL;
}

/*
 * Output and update for atomic system:
 *    '<S68>/MATLAB Function1'
 *    '<S79>/MATLAB Function1'
 */
void TOGGLER_MATLABFunction1(real_T rty_y[4])
{
  rty_y[0] = 1.0;
  rty_y[1] = 1.0;
  rty_y[2] = 1.0;
  rty_y[3] = 1.0;
}

/*
 * Output and update for atomic system:
 *    '<S68>/MATLAB Function2'
 *    '<S79>/MATLAB Function2'
 */
void TOGGLER_MATLABFunction2(real_T rtu_u1, const real_T rtu_u2[4], real_T
  rtu_u3, real_T rty_y[4])
{
  rty_y[0] = rtu_u2[0];
  rty_y[1] = rtu_u2[1];
  rty_y[2] = rtu_u2[2];
  rty_y[3] = rtu_u2[3];
  if (!(rtu_u3 == 0.0)) {
    rty_y[(int32_T)rtu_u3 - 1] = rtu_u1;
  }
}

/*
 * Output and update for atomic system:
 *    '<S68>/MATLAB Function3'
 *    '<S79>/MATLAB Function3'
 */
void TOGGLER_MATLABFunction3(const real_T rtu_u1[4], real_T rtu_u2, real_T
  *rty_y)
{
  if (rtu_u2 == 0.0) {
    *rty_y = 0.0;
  } else {
    *rty_y = rtu_u1[(int32_T)rtu_u2 - 1];
  }
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = atan2(tmp, tmp_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T y;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    boolean_T yEq;
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      real_T q;
      q = fabs(u0 / u1);
      yEq = !(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

/* Function for MATLAB Function: '<S62>/Toggler' */
static real_T TOGGLER_mod(real_T x)
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

static void TOGGLER_SystemCore_setup(dsp_simulink_MovingStandardDe_T *obj)
{
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->NumChannels = 1;
  obj->FrameLength = 1;
  obj->_pobj0.isInitialized = 0;
  obj->_pobj0.isInitialized = 0;
  obj->pStatistic = &obj->_pobj0;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

static void TOGGLER_SystemCore_setup_gi(dsp_simulink_MovingAverage_TO_T *obj)
{
  obj->isSetupComplete = false;
  obj->isInitialized = 1;
  obj->NumChannels = 1;
  obj->FrameLength = 1;
  obj->_pobj0.isInitialized = 0;
  obj->_pobj0.isInitialized = 0;
  obj->pStatistic = &obj->_pobj0;
  obj->isSetupComplete = true;
  obj->TunablePropsChanged = false;
}

/* Model step function */
void TOGGLER_step(void)
{
  g_dsp_internal_SlidingWindowA_T *obj_0;
  g_dsp_internal_SlidingWindowV_T *obj;
  real_T reverseS[100];
  real_T reverseSamples[100];
  real_T x[100];
  real_T rtb_available[4];
  real_T rtb_available_h[4];
  real_T rtb_y_i[4];
  real_T rtb_y_l[4];
  real_T rtb_y_n[4];
  real_T M;
  real_T Mprev;
  real_T S;
  real_T T;
  real_T counter;
  real_T modValueRev;
  real_T rtb_CTRLToSkip_b;
  real_T rtb_Mod1;
  real_T rtb_MovingAverage2_0;
  real_T rtb_MovingStandardDeviation1;
  real_T rtb_available_tmp;
  real_T rtb_iL_k;
  real_T rtb_y_e;
  real_T rtb_y_p;
  real_T y;
  int32_T exitg1;
  int32_T i;
  int32_T idxOldActive;
  int32_T rtb_available_nt;
  uint32_T intVal;
  boolean_T rtb_TmpSignalConversionAtBittoI[5];
  boolean_T rtb_RelationalOperator_hc[4];
  boolean_T rtb_FixPtLogicalOperator;
  boolean_T rtb_FixPtLogicalOperator_i;
  boolean_T rtb_FixPtLogicalOperator_jj;
  boolean_T rtb_FixPtLogicalOperator_o;
  boolean_T rtb_GreaterThan;
  boolean_T rtb_LogicalOperator_i2;
  boolean_T rtb_LogicalOperator_n;
  boolean_T rtb_LogicalOperator_op;
  boolean_T rtb_NOT;
  boolean_T rtb_Switch_e2;
  boolean_T rtb_Switch_it;
  boolean_T rtb_Switch_kn;
  boolean_T rtb_Switch_p2;

  /* MATLABSystem: '<S25>/Moving Standard Deviation1' incorporates:
   *  Inport: '<Root>/input_WS_ms'
   */
  if (TOGGLER_DW.obj_l.TunablePropsChanged) {
    TOGGLER_DW.obj_l.TunablePropsChanged = false;
  }

  obj = TOGGLER_DW.obj_l.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    for (i = 0; i < 100; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 100; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 100; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 0.0;
    obj->pModValueRev = 0.0;
    obj->isSetupComplete = true;
    for (i = 0; i < 100; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 100; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 100; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 1.0;
    obj->pModValueRev = 0.0;
  }

  for (i = 0; i < 100; i++) {
    reverseSamples[i] = obj->pReverseSamples[i];
  }

  for (i = 0; i < 100; i++) {
    x[i] = obj->pReverseT[i];
  }

  for (i = 0; i < 100; i++) {
    reverseS[i] = obj->pReverseS[i];
  }

  T = obj->pT;
  S = obj->pS;
  M = obj->pM;
  counter = obj->pCounter;
  modValueRev = obj->pModValueRev;
  y = 0.0;
  T += TOGGLER_U.input_WS_ms;
  Mprev = M;
  M += 1.0 / counter * (TOGGLER_U.input_WS_ms - M);
  Mprev = TOGGLER_U.input_WS_ms - Mprev;
  S += (counter - 1.0) * Mprev * Mprev / counter;
  if (modValueRev == 0.0) {
    y = (100.0 - counter) / counter * T - x[(int32_T)(100.0 - counter) - 1];
    y = (counter / (((100.0 - counter) + counter) * (100.0 - counter)) * (y * y)
         + (reverseS[(int32_T)(100.0 - counter) - 1] + S)) / 99.0;
  }

  reverseSamples[(int32_T)(100.0 - counter) - 1] = TOGGLER_U.input_WS_ms;
  if (counter < 99.0) {
    counter++;
  } else {
    counter = 1.0;
    memcpy(&x[0], &reverseSamples[0], 100U * sizeof(real_T));
    T = 0.0;
    S = 0.0;
    for (i = 0; i < 99; i++) {
      M = reverseSamples[i];
      x[i + 1] += x[i];
      Mprev = T;
      T += 1.0 / ((real_T)i + 1.0) * (M - T);
      M -= Mprev;
      S += (((real_T)i + 1.0) - 1.0) * M * M / ((real_T)i + 1.0);
      reverseS[i] = S;
    }

    T = 0.0;
    S = 0.0;
    M = 0.0;
  }

  for (i = 0; i < 100; i++) {
    obj->pReverseSamples[i] = reverseSamples[i];
  }

  for (i = 0; i < 100; i++) {
    obj->pReverseT[i] = x[i];
  }

  for (i = 0; i < 100; i++) {
    obj->pReverseS[i] = reverseS[i];
  }

  obj->pT = T;
  obj->pS = S;
  obj->pM = M;
  obj->pCounter = counter;
  if (modValueRev > 0.0) {
    obj->pModValueRev = modValueRev - 1.0;
  } else {
    obj->pModValueRev = 0.0;
  }

  rtb_MovingStandardDeviation1 = sqrt(y);

  /* End of MATLABSystem: '<S25>/Moving Standard Deviation1' */

  /* Sum: '<S25>/Sum' incorporates:
   *  Constant: '<S25>/One'
   *  Delay: '<S25>/Delay'
   */
  TOGGLER_DW.Delay_DSTATE++;

  /* Switch: '<S29>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S25>/Constant'
   *  Delay: '<S25>/Delay'
   *  RelationalOperator: '<S29>/LowerRelop1'
   *  RelationalOperator: '<S29>/UpperRelop'
   *  Switch: '<S29>/Switch'
   */
  if (TOGGLER_DW.Delay_DSTATE > 6000.0) {
    counter = 6000.0;
  } else if (TOGGLER_DW.Delay_DSTATE < 0.0) {
    /* Switch: '<S29>/Switch' incorporates:
     *  Constant: '<S25>/Constant'
     */
    counter = 0.0;
  } else {
    counter = TOGGLER_DW.Delay_DSTATE;
  }

  /* End of Switch: '<S29>/Switch2' */

  /* RelationalOperator: '<S25>/GreaterThan' incorporates:
   *  Constant: '<S1>/Constant2'
   */
  rtb_GreaterThan = (counter < 6000.0);

  /* RelationalOperator: '<S30>/IsNaN' */
  rtb_FixPtLogicalOperator_jj = rtIsNaN(rtb_MovingStandardDeviation1);

  /* RelationalOperator: '<S30>/IsInf' */
  rtb_FixPtLogicalOperator_o = rtIsInf(rtb_MovingStandardDeviation1);

  /* Logic: '<S25>/Logical Operator' incorporates:
   *  Abs: '<S30>/Abs'
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S31>/Constant'
   *  Logic: '<S30>/Logical Operator'
   *  RelationalOperator: '<S25>/GreaterThan'
   *  RelationalOperator: '<S30>/IsInf'
   *  RelationalOperator: '<S30>/IsNaN'
   *  RelationalOperator: '<S31>/Compare'
   */
  rtb_LogicalOperator_op = ((rtb_MovingStandardDeviation1 <= 1.0E-5) ||
    rtb_FixPtLogicalOperator_jj || rtb_FixPtLogicalOperator_o || (counter <
    6000.0));

  /* MATLABSystem: '<S24>/Moving Standard Deviation1' incorporates:
   *  Inport: '<Root>/input_Dir_deg'
   */
  if (TOGGLER_DW.obj_ds.TunablePropsChanged) {
    TOGGLER_DW.obj_ds.TunablePropsChanged = false;
  }

  obj = TOGGLER_DW.obj_ds.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    for (i = 0; i < 100; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 100; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 100; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 0.0;
    obj->pModValueRev = 0.0;
    obj->isSetupComplete = true;
    for (i = 0; i < 100; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 100; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 100; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 1.0;
    obj->pModValueRev = 0.0;
  }

  for (i = 0; i < 100; i++) {
    reverseSamples[i] = obj->pReverseSamples[i];
  }

  for (i = 0; i < 100; i++) {
    x[i] = obj->pReverseT[i];
  }

  for (i = 0; i < 100; i++) {
    reverseS[i] = obj->pReverseS[i];
  }

  T = obj->pT;
  S = obj->pS;
  M = obj->pM;
  counter = obj->pCounter;
  modValueRev = obj->pModValueRev;
  y = 0.0;
  T += TOGGLER_U.input_Dir_deg;
  Mprev = M;
  M += 1.0 / counter * (TOGGLER_U.input_Dir_deg - M);
  Mprev = TOGGLER_U.input_Dir_deg - Mprev;
  S += (counter - 1.0) * Mprev * Mprev / counter;
  if (modValueRev == 0.0) {
    y = (100.0 - counter) / counter * T - x[(int32_T)(100.0 - counter) - 1];
    y = (counter / (((100.0 - counter) + counter) * (100.0 - counter)) * (y * y)
         + (reverseS[(int32_T)(100.0 - counter) - 1] + S)) / 99.0;
  }

  reverseSamples[(int32_T)(100.0 - counter) - 1] = TOGGLER_U.input_Dir_deg;
  if (counter < 99.0) {
    counter++;
  } else {
    counter = 1.0;
    memcpy(&x[0], &reverseSamples[0], 100U * sizeof(real_T));
    T = 0.0;
    S = 0.0;
    for (i = 0; i < 99; i++) {
      M = reverseSamples[i];
      x[i + 1] += x[i];
      Mprev = T;
      T += 1.0 / ((real_T)i + 1.0) * (M - T);
      M -= Mprev;
      S += (((real_T)i + 1.0) - 1.0) * M * M / ((real_T)i + 1.0);
      reverseS[i] = S;
    }

    T = 0.0;
    S = 0.0;
    M = 0.0;
  }

  for (i = 0; i < 100; i++) {
    obj->pReverseSamples[i] = reverseSamples[i];
  }

  for (i = 0; i < 100; i++) {
    obj->pReverseT[i] = x[i];
  }

  for (i = 0; i < 100; i++) {
    obj->pReverseS[i] = reverseS[i];
  }

  obj->pT = T;
  obj->pS = S;
  obj->pM = M;
  obj->pCounter = counter;
  if (modValueRev > 0.0) {
    obj->pModValueRev = modValueRev - 1.0;
  } else {
    obj->pModValueRev = 0.0;
  }

  modValueRev = sqrt(y);

  /* End of MATLABSystem: '<S24>/Moving Standard Deviation1' */

  /* Sum: '<S24>/Sum' incorporates:
   *  Constant: '<S24>/One'
   *  Delay: '<S24>/Delay'
   */
  TOGGLER_DW.Delay_DSTATE_p++;

  /* Switch: '<S26>/Switch2' incorporates:
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S24>/Constant'
   *  Delay: '<S24>/Delay'
   *  RelationalOperator: '<S26>/LowerRelop1'
   *  RelationalOperator: '<S26>/UpperRelop'
   *  Switch: '<S26>/Switch'
   */
  if (TOGGLER_DW.Delay_DSTATE_p > 6000.0) {
    counter = 6000.0;
  } else if (TOGGLER_DW.Delay_DSTATE_p < 0.0) {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S24>/Constant'
     */
    counter = 0.0;
  } else {
    counter = TOGGLER_DW.Delay_DSTATE_p;
  }

  /* End of Switch: '<S26>/Switch2' */

  /* RelationalOperator: '<S27>/IsNaN' */
  rtb_NOT = rtIsNaN(modValueRev);

  /* RelationalOperator: '<S27>/IsInf' */
  rtb_LogicalOperator_n = rtIsInf(modValueRev);

  /* Logic: '<S1>/Logical Operator' incorporates:
   *  Abs: '<S27>/Abs'
   *  Abs: '<S30>/Abs'
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S28>/Constant'
   *  Constant: '<S31>/Constant'
   *  Logic: '<S24>/Logical Operator'
   *  Logic: '<S25>/Logical Operator'
   *  Logic: '<S27>/Logical Operator'
   *  Logic: '<S30>/Logical Operator'
   *  RelationalOperator: '<S24>/GreaterThan'
   *  RelationalOperator: '<S27>/IsInf'
   *  RelationalOperator: '<S27>/IsNaN'
   *  RelationalOperator: '<S28>/Compare'
   *  RelationalOperator: '<S31>/Compare'
   */
  rtb_GreaterThan = ((rtb_MovingStandardDeviation1 <= 1.0E-5) ||
                     rtb_FixPtLogicalOperator_jj || rtb_FixPtLogicalOperator_o ||
                     rtb_GreaterThan || ((modValueRev <= 1.0E-5) || rtb_NOT ||
    rtb_LogicalOperator_n || (counter < 6000.0)));

  /* Logic: '<S1>/NOT' incorporates:
   *  Abs: '<S27>/Abs'
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S28>/Constant'
   *  Logic: '<S1>/Logical Operator'
   *  Logic: '<S24>/Logical Operator'
   *  Logic: '<S27>/Logical Operator'
   *  RelationalOperator: '<S24>/GreaterThan'
   *  RelationalOperator: '<S27>/IsInf'
   *  RelationalOperator: '<S27>/IsNaN'
   *  RelationalOperator: '<S28>/Compare'
   */
  rtb_NOT = ((!rtb_LogicalOperator_op) && ((!(modValueRev <= 1.0E-5)) &&
              (!rtb_NOT) && (!rtb_LogicalOperator_n) && (!(counter < 6000.0))));

  /* MATLABSystem: '<Root>/Moving Average' incorporates:
   *  Inport: '<Root>/input_WS_ms'
   */
  if (TOGGLER_DW.obj_d.TunablePropsChanged) {
    TOGGLER_DW.obj_d.TunablePropsChanged = false;
  }

  obj_0 = TOGGLER_DW.obj_d.pStatistic;
  if (obj_0->isInitialized != 1) {
    obj_0->isSetupComplete = false;
    obj_0->isInitialized = 1;
    obj_0->pCumSum = 0.0;
    for (i = 0; i < 5999; i++) {
      obj_0->pCumSumRev[i] = 0.0;
    }

    obj_0->pCumRevIndex = 1.0;
    obj_0->pModValueRev = 0.0;
    obj_0->isSetupComplete = true;
    obj_0->pCumSum = 0.0;
    for (i = 0; i < 5999; i++) {
      obj_0->pCumSumRev[i] = 0.0;
    }

    obj_0->pCumRevIndex = 1.0;
    obj_0->pModValueRev = 0.0;
  }

  T = obj_0->pCumRevIndex;
  S = obj_0->pCumSum;
  for (i = 0; i < 5999; i++) {
    TOGGLER_B.csumrev[i] = obj_0->pCumSumRev[i];
  }

  modValueRev = obj_0->pModValueRev;
  M = 0.0;
  y = 0.0;
  S += TOGGLER_U.input_WS_ms;
  if (modValueRev == 0.0) {
    M = TOGGLER_B.csumrev[(int32_T)T - 1] + S;
  }

  TOGGLER_B.csumrev[(int32_T)T - 1] = TOGGLER_U.input_WS_ms;
  if (T != 5999.0) {
    T++;
  } else {
    T = 1.0;
    S = 0.0;
    for (i = 5997; i >= 0; i--) {
      TOGGLER_B.csumrev[i] += TOGGLER_B.csumrev[i + 1];
    }
  }

  if (modValueRev == 0.0) {
    y = M / 6000.0;
  }

  obj_0->pCumSum = S;
  for (i = 0; i < 5999; i++) {
    obj_0->pCumSumRev[i] = TOGGLER_B.csumrev[i];
  }

  obj_0->pCumRevIndex = T;
  if (modValueRev > 0.0) {
    obj_0->pModValueRev = modValueRev - 1.0;
  } else {
    obj_0->pModValueRev = 0.0;
  }

  /* RelationalOperator: '<S87>/Compare' incorporates:
   *  Constant: '<S87>/Constant'
   *  Inport: '<Root>/input_Dir_deg'
   */
  rtb_LogicalOperator_op = (TOGGLER_U.input_Dir_deg >= 600.0);

  /* Outputs for Triggered SubSystem: '<S19>/Sample and Hold' incorporates:
   *  TriggerPort: '<S88>/Trigger'
   */
  if (rtb_LogicalOperator_op && (TOGGLER_PrevZCX.SampleandHold_Trig_ZCE !=
       POS_ZCSIG)) {
    /* SignalConversion generated from: '<S88>/In' incorporates:
     *  Delay: '<S19>/Delay'
     */
    TOGGLER_B.In = TOGGLER_DW.Delay_DSTATE_m;
  }

  TOGGLER_PrevZCX.SampleandHold_Trig_ZCE = rtb_LogicalOperator_op;

  /* End of Outputs for SubSystem: '<S19>/Sample and Hold' */

  /* Switch: '<S19>/Switch' incorporates:
   *  Inport: '<Root>/input_Dir_deg'
   */
  if (rtb_LogicalOperator_op) {
    rtb_MovingStandardDeviation1 = TOGGLER_B.In;
  } else {
    rtb_MovingStandardDeviation1 = TOGGLER_U.input_Dir_deg;
  }

  /* End of Switch: '<S19>/Switch' */

  /* Switch: '<S89>/Switch5' incorporates:
   *  Abs: '<S91>/Abs'
   *  Constant: '<S89>/Constant2'
   *  Constant: '<S89>/Constant8'
   *  Constant: '<S92>/Constant'
   *  Constant: '<S93>/Constant'
   *  Constant: '<S94>/Constant'
   *  Logic: '<S91>/Logical Operator'
   *  RelationalOperator: '<S91>/Relational Operator'
   *  RelationalOperator: '<S92>/Compare'
   *  RelationalOperator: '<S93>/Compare'
   *  RelationalOperator: '<S94>/Compare'
   *  Sum: '<S91>/Sum'
   *  Switch: '<S89>/Switch6'
   *  UnitDelay: '<S91>/Unit Delay'
   */
  if ((fabs(rtb_MovingStandardDeviation1 - TOGGLER_DW.UnitDelay_DSTATE_d) <=
       420.0) && (rtb_MovingStandardDeviation1 == rtb_MovingStandardDeviation1) &&
      (rtb_MovingStandardDeviation1 < (rtInf)) && (rtb_MovingStandardDeviation1 >
       (rtMinusInf))) {
    /* Gain: '<S89>/Gain4' incorporates:
     *  Switch: '<S89>/Switch'
     */
    counter = 0.017453292519943295 * rtb_MovingStandardDeviation1;

    /* Switch: '<S89>/Switch' incorporates:
     *  MagnitudeAngleToComplex: '<S89>/Magnitude-Angle to Complex'
     *  UnitDelay: '<S89>/Unit Delay'
     */
    TOGGLER_B.dcv[0].re = cos(counter);
    TOGGLER_B.dcv[0].im = sin(counter);
    memcpy(&TOGGLER_B.dcv[1], &TOGGLER_DW.UnitDelay_DSTATE[0], 5999U * sizeof
           (creal_T));

    /* Switch: '<S89>/Switch5' incorporates:
     *  Switch: '<S89>/Switch'
     *  UnitDelay: '<S89>/Unit Delay'
     */
    memcpy(&TOGGLER_DW.UnitDelay_DSTATE[0], &TOGGLER_B.dcv[0], 6000U * sizeof
           (creal_T));
    i = 1;
  } else {
    i = -1;
  }

  /* End of Switch: '<S89>/Switch5' */

  /* Sum: '<S89>/Sum1' incorporates:
   *  Switch: '<S89>/Switch6'
   *  UnitDelay: '<S89>/Unit Delay1'
   */
  counter = (real_T)i + TOGGLER_DW.UnitDelay1_DSTATE_f;

  /* Saturate: '<S89>/Saturation' */
  if (counter > 6000.0) {
    counter = 6000.0;
  } else if (counter < 0.0) {
    counter = 0.0;
  }

  /* End of Saturate: '<S89>/Saturation' */

  /* Saturate: '<S89>/Saturation1' */
  if (counter < 6000.0) {
    modValueRev = 6000.0;
  } else {
    modValueRev = counter;
  }

  /* End of Saturate: '<S89>/Saturation1' */

  /* MATLAB Function: '<S89>/MATLAB Function' incorporates:
   *  Switch: '<S89>/Switch5'
   *  UnitDelay: '<S89>/Unit Delay'
   */
  T = 0.0;
  S = 0.0;
  for (i = 0; i < 6000; i++) {
    T += TOGGLER_DW.UnitDelay_DSTATE[i].re;
    S += TOGGLER_DW.UnitDelay_DSTATE[i].im;
  }

  /* End of MATLAB Function: '<S89>/MATLAB Function' */

  /* Product: '<S89>/Divide' */
  if (S == 0.0) {
    T /= modValueRev;
    S = 0.0;
  } else if (T == 0.0) {
    T = 0.0;
    S /= modValueRev;
  } else {
    T /= modValueRev;
    S /= modValueRev;
  }

  /* Switch: '<S89>/Switch2' incorporates:
   *  ComplexToMagnitudeAngle: '<S89>/Complex to Magnitude-Angle'
   *  Constant: '<S89>/Constant4'
   *  Gain: '<S89>/Gain2'
   *  Product: '<S89>/Divide'
   */
  if (counter >= 6000.0) {
    modValueRev = 57.295779513082323 * rt_atan2d_snf(S, T);
  } else {
    modValueRev = 0.0;
  }

  /* Math: '<S89>/Math Function1' incorporates:
   *  Constant: '<S89>/Constant11'
   *  Switch: '<S89>/Switch2'
   */
  Mprev = rt_modd_snf(modValueRev, 360.0);

  /* Math: '<Root>/Mod1' incorporates:
   *  Constant: '<Root>/Constant'
   *  Inport: '<Root>/input_Nacelle_MetMast_Offset'
   *  Inport: '<Root>/input_WT3_NacelleOrientation'
   *  Sum: '<Root>/Sum'
   */
  rtb_Mod1 = rt_modd_snf(TOGGLER_U.input_WT3_NacelleOrientation +
    TOGGLER_U.input_Nacelle_MetMast_Offset, 360.0);

  /* MATLABSystem: '<Root>/Moving Average2' incorporates:
   *  Inport: '<Root>/input_WT3_Misalignment'
   */
  if (TOGGLER_DW.obj.TunablePropsChanged) {
    TOGGLER_DW.obj.TunablePropsChanged = false;
  }

  obj_0 = TOGGLER_DW.obj.pStatistic;
  if (obj_0->isInitialized != 1) {
    obj_0->isSetupComplete = false;
    obj_0->isInitialized = 1;
    obj_0->pCumSum = 0.0;
    for (i = 0; i < 5999; i++) {
      obj_0->pCumSumRev[i] = 0.0;
    }

    obj_0->pCumRevIndex = 1.0;
    obj_0->pModValueRev = 0.0;
    obj_0->isSetupComplete = true;
    obj_0->pCumSum = 0.0;
    for (i = 0; i < 5999; i++) {
      obj_0->pCumSumRev[i] = 0.0;
    }

    obj_0->pCumRevIndex = 1.0;
    obj_0->pModValueRev = 0.0;
  }

  T = obj_0->pCumRevIndex;
  S = obj_0->pCumSum;
  for (i = 0; i < 5999; i++) {
    TOGGLER_B.csumrev[i] = obj_0->pCumSumRev[i];
  }

  modValueRev = obj_0->pModValueRev;
  M = 0.0;
  rtb_MovingAverage2_0 = 0.0;
  S += TOGGLER_U.input_WT3_Misalignment;
  if (modValueRev == 0.0) {
    M = TOGGLER_B.csumrev[(int32_T)T - 1] + S;
  }

  TOGGLER_B.csumrev[(int32_T)T - 1] = TOGGLER_U.input_WT3_Misalignment;
  if (T != 5999.0) {
    T++;
  } else {
    T = 1.0;
    S = 0.0;
    for (i = 5997; i >= 0; i--) {
      TOGGLER_B.csumrev[i] += TOGGLER_B.csumrev[i + 1];
    }
  }

  if (modValueRev == 0.0) {
    rtb_MovingAverage2_0 = M / 6000.0;
  }

  obj_0->pCumSum = S;
  for (i = 0; i < 5999; i++) {
    obj_0->pCumSumRev[i] = TOGGLER_B.csumrev[i];
  }

  obj_0->pCumRevIndex = T;
  if (modValueRev > 0.0) {
    obj_0->pModValueRev = modValueRev - 1.0;
  } else {
    obj_0->pModValueRev = 0.0;
  }

  /* Abs: '<Root>/Abs' incorporates:
   *  MATLABSystem: '<Root>/Moving Average2'
   */
  modValueRev = fabs(rtb_MovingAverage2_0);

  /* Outputs for Atomic SubSystem: '<S2>/Atomic Subsystem' */
  /* Logic: '<S41>/FixPt Logical Operator' incorporates:
   *  MATLABSystem: '<Root>/Moving Average'
   *  RelationalOperator: '<S41>/Lower Test'
   *  RelationalOperator: '<S41>/Upper Test'
   */
  rtb_FixPtLogicalOperator_jj = ((TOGGLER_ConstB.MultiportSelector_o1_ks <= y) &&
    (y <= TOGGLER_ConstB.MultiportSelector_o2_dp));

  /* Logic: '<S38>/FixPt Logical Operator' incorporates:
   *  Constant: '<S34>/Zero'
   *  RelationalOperator: '<S38>/Lower Test'
   *  RelationalOperator: '<S38>/Upper Test'
   */
  rtb_FixPtLogicalOperator_o = ((modValueRev >= 0.0) && (modValueRev <=
    TOGGLER_ConstB.VariableSelector3_o));

  /* Switch: '<S39>/Switch' incorporates:
   *  Logic: '<S39>/Logical Operator'
   *  Logic: '<S39>/Logical Operator1'
   *  RelationalOperator: '<S39>/Relational Operator1'
   *  RelationalOperator: '<S39>/Relational Operator2'
   */
  if (TOGGLER_ConstB.RelationalOperator_j) {
    rtb_Switch_p2 = ((rtb_Mod1 >= TOGGLER_ConstB.MultiportSelector_o1_h) &&
                     (rtb_Mod1 <= TOGGLER_ConstB.MultiportSelector_o2_o));
  } else {
    rtb_Switch_p2 = ((rtb_Mod1 >= TOGGLER_ConstB.MultiportSelector_o1_h) ||
                     (rtb_Mod1 <= TOGGLER_ConstB.MultiportSelector_o2_o));
  }

  /* End of Switch: '<S39>/Switch' */

  /* Switch: '<S40>/Switch' incorporates:
   *  Logic: '<S40>/Logical Operator'
   *  Logic: '<S40>/Logical Operator1'
   *  RelationalOperator: '<S40>/Relational Operator1'
   *  RelationalOperator: '<S40>/Relational Operator2'
   */
  if (TOGGLER_ConstB.RelationalOperator_l) {
    rtb_Switch_kn = ((Mprev >= TOGGLER_ConstB.MultiportSelector_o1_c) && (Mprev <=
      TOGGLER_ConstB.MultiportSelector_o2_j));
  } else {
    rtb_Switch_kn = ((Mprev >= TOGGLER_ConstB.MultiportSelector_o1_c) || (Mprev <=
      TOGGLER_ConstB.MultiportSelector_o2_j));
  }

  /* End of Switch: '<S40>/Switch' */

  /* Logic: '<S32>/Logical Operator' */
  rtb_LogicalOperator_i2 = (rtb_FixPtLogicalOperator_jj && rtb_Switch_kn &&
    rtb_Switch_p2 && rtb_FixPtLogicalOperator_o);

  /* End of Outputs for SubSystem: '<S2>/Atomic Subsystem' */

  /* Outputs for Atomic SubSystem: '<S2>/Atomic Subsystem1' */
  /* Logic: '<S49>/FixPt Logical Operator' incorporates:
   *  MATLABSystem: '<Root>/Moving Average'
   *  RelationalOperator: '<S49>/Lower Test'
   *  RelationalOperator: '<S49>/Upper Test'
   */
  rtb_FixPtLogicalOperator = ((TOGGLER_ConstB.MultiportSelector_o1_i <= y) && (y
    <= TOGGLER_ConstB.MultiportSelector_o2_d));

  /* Logic: '<S46>/FixPt Logical Operator' incorporates:
   *  Constant: '<S42>/Zero'
   *  RelationalOperator: '<S46>/Lower Test'
   *  RelationalOperator: '<S46>/Upper Test'
   */
  rtb_FixPtLogicalOperator_i = ((modValueRev >= 0.0) && (modValueRev <=
    TOGGLER_ConstB.VariableSelector3));

  /* Switch: '<S47>/Switch' incorporates:
   *  Logic: '<S47>/Logical Operator'
   *  Logic: '<S47>/Logical Operator1'
   *  RelationalOperator: '<S47>/Relational Operator1'
   *  RelationalOperator: '<S47>/Relational Operator2'
   */
  if (TOGGLER_ConstB.RelationalOperator) {
    rtb_Switch_it = ((rtb_Mod1 >= TOGGLER_ConstB.MultiportSelector_o1) &&
                     (rtb_Mod1 <= TOGGLER_ConstB.MultiportSelector_o2));
  } else {
    rtb_Switch_it = ((rtb_Mod1 >= TOGGLER_ConstB.MultiportSelector_o1) ||
                     (rtb_Mod1 <= TOGGLER_ConstB.MultiportSelector_o2));
  }

  /* End of Switch: '<S47>/Switch' */

  /* Switch: '<S48>/Switch' incorporates:
   *  Logic: '<S48>/Logical Operator'
   *  Logic: '<S48>/Logical Operator1'
   *  RelationalOperator: '<S48>/Relational Operator1'
   *  RelationalOperator: '<S48>/Relational Operator2'
   */
  if (TOGGLER_ConstB.RelationalOperator_k) {
    rtb_Switch_e2 = ((Mprev >= TOGGLER_ConstB.MultiportSelector_o1_k) && (Mprev <=
      TOGGLER_ConstB.MultiportSelector_o2_g));
  } else {
    rtb_Switch_e2 = ((Mprev >= TOGGLER_ConstB.MultiportSelector_o1_k) || (Mprev <=
      TOGGLER_ConstB.MultiportSelector_o2_g));
  }

  /* End of Switch: '<S48>/Switch' */

  /* Logic: '<S33>/Logical Operator' */
  rtb_LogicalOperator_n = (rtb_FixPtLogicalOperator && rtb_Switch_e2 &&
    rtb_Switch_it && rtb_FixPtLogicalOperator_i);

  /* End of Outputs for SubSystem: '<S2>/Atomic Subsystem1' */

  /* Logic: '<Root>/SafetyCheck' */
  rtb_LogicalOperator_op = rtb_LogicalOperator_i2 ^ rtb_LogicalOperator_n;

  /* Switch: '<S15>/Switch2' incorporates:
   *  RelationalOperator: '<S50>/Compare'
   *  UnitDelay: '<S15>/Unit Delay1'
   *  UnitDelay: '<S15>/Unit Delay2'
   */
  if (!(TOGGLER_DW.UnitDelay1_DSTATE != 0.0)) {
    TOGGLER_DW.UnitDelay2_DSTATE_g = rtb_LogicalOperator_op;
  }

  /* End of Switch: '<S15>/Switch2' */

  /* DataTypeConversion: '<Root>/Cast To Double1' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S4>/Constant'
   *  Inport: '<Root>/input_Flag_ManualSwitch_WFC'
   *  Inport: '<Root>/input_WT3_OpStatus'
   *  Logic: '<Root>/SafetyCheck1'
   *  Logic: '<Root>/SafetyCheck2'
   *  Logic: '<S1>/NOT'
   *  RelationalOperator: '<S3>/Compare'
   *  RelationalOperator: '<S4>/Compare'
   *  UnitDelay: '<S15>/Unit Delay2'
   */
  rtb_iL_k = ((!rtb_GreaterThan) && (TOGGLER_U.input_WT3_OpStatus == 30.0) &&
              (TOGGLER_U.input_Flag_ManualSwitch_WFC == 1.0) &&
              TOGGLER_DW.UnitDelay2_DSTATE_g);

  /* Outport: '<Root>/output_Flag_WFCIsActive' incorporates:
   *  Constant: '<S3>/Constant'
   *  Constant: '<S4>/Constant'
   *  DataTypeConversion: '<Root>/Cast To Double1'
   *  Inport: '<Root>/input_Flag_ManualSwitch_WFC'
   *  Inport: '<Root>/input_WT3_OpStatus'
   *  Logic: '<Root>/SafetyCheck1'
   *  Logic: '<Root>/SafetyCheck2'
   *  RelationalOperator: '<S3>/Compare'
   *  RelationalOperator: '<S4>/Compare'
   *  UnitDelay: '<S15>/Unit Delay2'
   */
  TOGGLER_Y.output_Flag_WFCIsActive = (rtb_NOT && (TOGGLER_U.input_WT3_OpStatus ==
    30.0) && (TOGGLER_U.input_Flag_ManualSwitch_WFC == 1.0) &&
    TOGGLER_DW.UnitDelay2_DSTATE_g);

  /* Outputs for Enabled SubSystem: '<S16>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S51>/Enable'
   */
  if (rtb_Switch_kn) {
    /* Merge: '<S16>/Merge3' incorporates:
     *  SignalConversion generated from: '<S51>/In1'
     */
    TOGGLER_B.Merge3[0] = rtb_FixPtLogicalOperator_jj;
    TOGGLER_B.Merge3[1] = rtb_Switch_p2;
    TOGGLER_B.Merge3[2] = rtb_FixPtLogicalOperator_o;
  }

  /* End of Outputs for SubSystem: '<S16>/Enabled Subsystem' */

  /* Outputs for Enabled SubSystem: '<S16>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S52>/Enable'
   */
  if (rtb_Switch_e2) {
    /* Merge: '<S16>/Merge3' incorporates:
     *  SignalConversion generated from: '<S52>/In1'
     */
    TOGGLER_B.Merge3[0] = rtb_FixPtLogicalOperator;
    TOGGLER_B.Merge3[1] = rtb_Switch_it;
    TOGGLER_B.Merge3[2] = rtb_FixPtLogicalOperator_i;
  }

  /* End of Outputs for SubSystem: '<S16>/Enabled Subsystem1' */

  /* Switch: '<S16>/Switch' incorporates:
   *  Logic: '<S16>/Logical Operator'
   */
  if ((boolean_T)(rtb_Switch_kn ^ rtb_Switch_e2)) {
    /* SignalConversion generated from: '<Root>/Bit to Integer Converter1' */
    rtb_TmpSignalConversionAtBittoI[2] = TOGGLER_B.Merge3[0];
    rtb_TmpSignalConversionAtBittoI[3] = TOGGLER_B.Merge3[1];
    rtb_TmpSignalConversionAtBittoI[4] = TOGGLER_B.Merge3[2];
  } else {
    /* SignalConversion generated from: '<Root>/Bit to Integer Converter1' incorporates:
     *  Gain: '<S16>/Gain'
     */
    rtb_TmpSignalConversionAtBittoI[2] = false;
    rtb_TmpSignalConversionAtBittoI[3] = false;
    rtb_TmpSignalConversionAtBittoI[4] = false;
  }

  /* End of Switch: '<S16>/Switch' */

  /* SignalConversion generated from: '<Root>/Bit to Integer Converter1' */
  rtb_TmpSignalConversionAtBittoI[0] = rtb_Switch_kn;
  rtb_TmpSignalConversionAtBittoI[1] = rtb_Switch_e2;

  /* S-Function (scominttobit): '<Root>/Bit to Integer Converter1' */
  /* Bit to Integer Conversion */
  idxOldActive = 0;
  intVal = 0U;
  for (i = 0; i < 5; i++) {
    /* Input bit order is MSB first */
    intVal = intVal << 1U | rtb_TmpSignalConversionAtBittoI[idxOldActive];
    idxOldActive++;
  }

  /* Outport: '<Root>/output_WFCStatus' incorporates:
   *  DataTypeConversion: '<Root>/Cast To Double'
   *  S-Function (scominttobit): '<Root>/Bit to Integer Converter1'
   */
  TOGGLER_Y.output_WFCStatus = (uint8_T)intVal;

  /* Logic: '<S57>/Logical Operator' incorporates:
   *  Logic: '<S63>/Logical Operator'
   */
  rtb_GreaterThan = (rtb_LogicalOperator_i2 && rtb_LogicalOperator_op);

  /* Logic: '<S57>/Logical Operator1' incorporates:
   *  Logic: '<S63>/Logical Operator1'
   */
  rtb_NOT = (rtb_LogicalOperator_n && rtb_LogicalOperator_op);

  /* Logic: '<S20>/Logical Operator3' incorporates:
   *  Constant: '<S95>/Constant'
   *  Constant: '<S96>/Constant'
   *  Constant: '<S97>/Constant'
   *  Inport: '<Root>/input_INFLW_1_Status'
   *  Inport: '<Root>/input_ManualSwitch_WFC_1'
   *  Inport: '<Root>/input_OFFSET_1_Status'
   *  RelationalOperator: '<S95>/Compare'
   *  RelationalOperator: '<S96>/Compare'
   *  RelationalOperator: '<S97>/Compare'
   */
  rtb_RelationalOperator_hc[0] = ((TOGGLER_U.input_INFLW_1_Status == 1.0) &&
    (TOGGLER_U.input_OFFSET_1_Status == 1.0) &&
    (TOGGLER_U.input_ManualSwitch_WFC_1 == 1.0));

  /* Logic: '<S21>/Logical Operator3' incorporates:
   *  Constant: '<S98>/Constant'
   *  Inport: '<Root>/input_ManualSwitch_GreedyWFC'
   *  RelationalOperator: '<S98>/Compare'
   */
  rtb_RelationalOperator_hc[1] = (TOGGLER_ConstB.Compare_nf &&
    TOGGLER_ConstB.Compare_a && (TOGGLER_U.input_ManualSwitch_GreedyWFC == 1.0));

  /* Logic: '<S22>/Logical Operator3' incorporates:
   *  Constant: '<S101>/Constant'
   *  Constant: '<S102>/Constant'
   *  Constant: '<S103>/Constant'
   *  Inport: '<Root>/input_INFLW_2_Status'
   *  Inport: '<Root>/input_ManualSwitch_WFC_2'
   *  Inport: '<Root>/input_OFFSET_2_Status'
   *  RelationalOperator: '<S101>/Compare'
   *  RelationalOperator: '<S102>/Compare'
   *  RelationalOperator: '<S103>/Compare'
   */
  rtb_RelationalOperator_hc[2] = ((TOGGLER_U.input_INFLW_2_Status == 1.0) &&
    (TOGGLER_U.input_OFFSET_2_Status == 1.0) &&
    (TOGGLER_U.input_ManualSwitch_WFC_2 == 1.0));

  /* Logic: '<S23>/Logical Operator3' incorporates:
   *  Constant: '<S104>/Constant'
   *  Constant: '<S105>/Constant'
   *  Inport: '<Root>/input_ManualSwitch_WFC_3'
   *  Inport: '<Root>/input_WFC_3_Status'
   *  RelationalOperator: '<S104>/Compare'
   *  RelationalOperator: '<S105>/Compare'
   */
  rtb_RelationalOperator_hc[3] = ((TOGGLER_U.input_WFC_3_Status == 1.0) &&
    (TOGGLER_U.input_ManualSwitch_WFC_3 == 1.0));

  /* MATLAB Function: '<S62>/Toggler' */
  idxOldActive = -1;
  for (i = 0; i < 4; i++) {
    /* MATLAB Function: '<S18>/MATLAB Function' incorporates:
     *  Constant: '<Root>/INPUTBUS'
     */
    rtb_available_nt = 0;
    if (((TOGGLER_ConstB.VectorConcatenate1[i] == 1.0) +
         (TOGGLER_ConstB.VectorConcatenate1[i] == 2.0)) +
        (TOGGLER_ConstB.VectorConcatenate1[i] == 3.0) != 0) {
      rtb_available_nt = 1;
    }

    /* Product: '<S18>/Product' */
    rtb_available_nt *= rtb_RelationalOperator_hc[i];

    /* MATLAB Function: '<S62>/Toggler' incorporates:
     *  Memory: '<S62>/Memory2'
     */
    if (TOGGLER_ConstB.VectorConcatenate1[i] == TOGGLER_DW.Memory2_PreviousInput)
    {
      idxOldActive = i;
    }

    /* MATLAB Function: '<S18>/MATLAB Function' */
    rtb_available_h[i] = rtb_available_nt;
  }

  /* MATLAB Function: '<S62>/Toggler' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Memory: '<S62>/Memory1'
   *  Memory: '<S62>/Memory2'
   */
  if ((TOGGLER_DW.Memory2_PreviousInput == 0.0) || ((((int32_T)rtb_available_h[0]
         + (int32_T)rtb_available_h[1]) + (int32_T)rtb_available_h[2]) +
       (int32_T)rtb_available_h[3] == 0)) {
    if ((((int32_T)rtb_available_h[0] + (int32_T)rtb_available_h[1]) + (int32_T)
         rtb_available_h[2]) + (int32_T)rtb_available_h[3] == 0) {
      TOGGLER_DW.Memory2_PreviousInput = 0.0;
    } else {
      modValueRev = 1.0;
      do {
        exitg1 = 0;
        i = (int32_T)modValueRev - 1;
        if (!(rtb_available_h[i] != 0.0)) {
          modValueRev++;
          if (modValueRev > 4.0) {
            modValueRev = 1.0;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      TOGGLER_DW.Memory2_PreviousInput = TOGGLER_ConstB.VectorConcatenate1[i];
    }

    TOGGLER_DW.Memory1_PreviousInput = 0.0;
  } else {
    modValueRev = TOGGLER_mod((real_T)idxOldActive + 1.0) + 1.0;
    while (!(rtb_available_h[(int32_T)modValueRev - 1] != 0.0)) {
      modValueRev = TOGGLER_mod(modValueRev) + 1.0;
    }

    if (rtb_available_h[idxOldActive] != 0.0) {
      if (TOGGLER_DW.Memory1_PreviousInput < 21000.0) {
        TOGGLER_DW.Memory1_PreviousInput++;
      } else {
        TOGGLER_DW.Memory1_PreviousInput = 0.0;
        TOGGLER_DW.Memory2_PreviousInput = TOGGLER_ConstB.VectorConcatenate1
          [(int32_T)modValueRev - 1];
      }
    } else {
      TOGGLER_DW.Memory1_PreviousInput = 0.0;
      TOGGLER_DW.Memory2_PreviousInput = TOGGLER_ConstB.VectorConcatenate1
        [(int32_T)modValueRev - 1];
    }
  }

  /* MATLAB Function: '<S64>/Toggler' */
  idxOldActive = -1;

  /* MATLAB Function: '<S18>/MATLAB Function1' incorporates:
   *  Constant: '<Root>/INPUTBUS'
   */
  rtb_available_nt = 0;
  if (TOGGLER_ConstB.VectorConcatenate1[0] == 4.0) {
    rtb_available_nt = 1;
  }

  /* Product: '<S18>/Product1' */
  rtb_available_nt *= rtb_RelationalOperator_hc[0];

  /* MATLAB Function: '<S64>/Toggler' incorporates:
   *  Memory: '<S64>/Memory2'
   */
  if (TOGGLER_ConstB.VectorConcatenate1[0] == TOGGLER_DW.Memory2_PreviousInput_k)
  {
    idxOldActive = 0;
  }

  /* MATLAB Function: '<S18>/MATLAB Function1' incorporates:
   *  Constant: '<Root>/INPUTBUS'
   */
  rtb_available[0] = rtb_available_nt;
  rtb_available_nt = 0;
  if (TOGGLER_ConstB.VectorConcatenate1[1] == 4.0) {
    rtb_available_nt = 1;
  }

  /* Product: '<S18>/Product1' */
  rtb_available_nt *= rtb_RelationalOperator_hc[1];

  /* MATLAB Function: '<S64>/Toggler' incorporates:
   *  Memory: '<S64>/Memory2'
   */
  if (TOGGLER_ConstB.VectorConcatenate1[1] == TOGGLER_DW.Memory2_PreviousInput_k)
  {
    idxOldActive = 1;
  }

  /* MATLAB Function: '<S18>/MATLAB Function1' incorporates:
   *  Constant: '<Root>/INPUTBUS'
   */
  rtb_available[1] = rtb_available_nt;
  rtb_available_nt = 0;
  if (TOGGLER_ConstB.VectorConcatenate1[2] == 4.0) {
    rtb_available_nt = 1;
  }

  /* Product: '<S18>/Product1' */
  rtb_available_nt *= rtb_RelationalOperator_hc[2];

  /* MATLAB Function: '<S64>/Toggler' incorporates:
   *  Memory: '<S64>/Memory2'
   */
  if (TOGGLER_ConstB.VectorConcatenate1[2] == TOGGLER_DW.Memory2_PreviousInput_k)
  {
    idxOldActive = 2;
  }

  /* MATLAB Function: '<S18>/MATLAB Function1' incorporates:
   *  Constant: '<Root>/INPUTBUS'
   */
  rtb_available[2] = rtb_available_nt;
  rtb_available_nt = 0;
  if (TOGGLER_ConstB.VectorConcatenate1[3] == 4.0) {
    rtb_available_nt = 1;
  }

  /* Product: '<S18>/Product1' */
  rtb_available_nt *= rtb_RelationalOperator_hc[3];

  /* MATLAB Function: '<S64>/Toggler' incorporates:
   *  Memory: '<S64>/Memory2'
   */
  if (TOGGLER_ConstB.VectorConcatenate1[3] == TOGGLER_DW.Memory2_PreviousInput_k)
  {
    idxOldActive = 3;
  }

  /* MATLAB Function: '<S18>/MATLAB Function1' */
  rtb_available[3] = rtb_available_nt;

  /* MATLAB Function: '<S64>/Toggler' incorporates:
   *  Constant: '<Root>/Constant4'
   *  Memory: '<S64>/Memory1'
   *  Memory: '<S64>/Memory2'
   */
  if ((TOGGLER_DW.Memory2_PreviousInput_k == 0.0) || ((((int32_T)rtb_available[0]
         + (int32_T)rtb_available[1]) + (int32_T)rtb_available[2]) +
       rtb_available_nt == 0)) {
    if ((((int32_T)rtb_available[0] + (int32_T)rtb_available[1]) + (int32_T)
         rtb_available[2]) + rtb_available_nt == 0) {
      TOGGLER_DW.Memory2_PreviousInput_k = 0.0;
    } else {
      modValueRev = 1.0;
      do {
        exitg1 = 0;
        i = (int32_T)modValueRev - 1;
        if (!(rtb_available[i] != 0.0)) {
          modValueRev++;
          if (modValueRev > 4.0) {
            modValueRev = 1.0;
          }
        } else {
          exitg1 = 1;
        }
      } while (exitg1 == 0);

      TOGGLER_DW.Memory2_PreviousInput_k = TOGGLER_ConstB.VectorConcatenate1[i];
    }

    TOGGLER_DW.Memory1_PreviousInput_j = 0.0;
  } else {
    modValueRev = TOGGLER_mod((real_T)idxOldActive + 1.0) + 1.0;
    while (!(rtb_available[(int32_T)modValueRev - 1] != 0.0)) {
      modValueRev = TOGGLER_mod(modValueRev) + 1.0;
    }

    if (rtb_available[idxOldActive] != 0.0) {
      if (TOGGLER_DW.Memory1_PreviousInput_j < 21000.0) {
        TOGGLER_DW.Memory1_PreviousInput_j++;
      } else {
        TOGGLER_DW.Memory1_PreviousInput_j = 0.0;
        TOGGLER_DW.Memory2_PreviousInput_k = TOGGLER_ConstB.VectorConcatenate1
          [(int32_T)modValueRev - 1];
      }
    } else {
      TOGGLER_DW.Memory1_PreviousInput_j = 0.0;
      TOGGLER_DW.Memory2_PreviousInput_k = TOGGLER_ConstB.VectorConcatenate1
        [(int32_T)modValueRev - 1];
    }
  }

  /* Outputs for Atomic SubSystem: '<S17>/Enabled Subsystem2' */
  /* Switch: '<S55>/Switch3' incorporates:
   *  Constant: '<S55>/Zero1'
   *  Delay: '<S55>/Delay'
   *  Delay: '<S55>/Delay1'
   *  Delay: '<S55>/Delay2'
   *  Logic: '<S55>/Logical Operator'
   *  Logic: '<S55>/Logical Operator1'
   *  Logic: '<S57>/Logical Operator'
   *  Logic: '<S57>/Logical Operator1'
   *  RelationalOperator: '<S58>/Compare'
   *  RelationalOperator: '<S59>/Compare'
   *  Switch: '<S55>/Switch'
   */
  if ((!rtb_NOT) && TOGGLER_DW.Delay1_DSTATE) {
    TOGGLER_DW.Delay2_DSTATE = 0.0;
  } else if ((!rtb_GreaterThan) && TOGGLER_DW.Delay_DSTATE_pp) {
    /* Switch: '<S55>/Switch' incorporates:
     *  Constant: '<S55>/Zero'
     *  Delay: '<S55>/Delay2'
     */
    TOGGLER_DW.Delay2_DSTATE = 1.0;
  }

  /* End of Switch: '<S55>/Switch3' */

  /* Update for Delay: '<S55>/Delay' incorporates:
   *  Logic: '<S57>/Logical Operator'
   */
  TOGGLER_DW.Delay_DSTATE_pp = rtb_GreaterThan;

  /* Update for Delay: '<S55>/Delay1' incorporates:
   *  Logic: '<S57>/Logical Operator1'
   */
  TOGGLER_DW.Delay1_DSTATE = rtb_NOT;

  /* End of Outputs for SubSystem: '<S17>/Enabled Subsystem2' */

  /* Outputs for Enabled SubSystem: '<S17>/Enabled Subsystem3' incorporates:
   *  EnablePort: '<S56>/Enable'
   */
  /* Logic: '<S57>/NOT' */
  if (!rtb_LogicalOperator_op) {
    /* Outputs for Atomic SubSystem: '<S17>/Enabled Subsystem2' */
    /* Switch: '<S55>/Switch1' incorporates:
     *  Delay: '<S55>/Delay2'
     */
    if (TOGGLER_DW.Delay2_DSTATE != 0.0) {
      /* Merge: '<S17>/Merge' incorporates:
       *  SignalConversion generated from: '<S56>/In1'
       */
      TOGGLER_B.Merge = TOGGLER_DW.Memory2_PreviousInput;
    } else {
      /* Merge: '<S17>/Merge' incorporates:
       *  SignalConversion generated from: '<S56>/In1'
       */
      TOGGLER_B.Merge = TOGGLER_DW.Memory2_PreviousInput_k;
    }

    /* End of Switch: '<S55>/Switch1' */
    /* End of Outputs for SubSystem: '<S17>/Enabled Subsystem2' */
  }

  /* End of Logic: '<S57>/NOT' */
  /* End of Outputs for SubSystem: '<S17>/Enabled Subsystem3' */

  /* Outputs for Enabled SubSystem: '<S17>/Enabled Subsystem' incorporates:
   *  EnablePort: '<S53>/Enable'
   */
  /* Logic: '<S57>/Logical Operator' */
  if (rtb_GreaterThan) {
    /* Merge: '<S17>/Merge' incorporates:
     *  SignalConversion generated from: '<S53>/In1'
     */
    TOGGLER_B.Merge = TOGGLER_DW.Memory2_PreviousInput;
  }

  /* End of Outputs for SubSystem: '<S17>/Enabled Subsystem' */

  /* Outputs for Enabled SubSystem: '<S17>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S54>/Enable'
   */
  /* Logic: '<S57>/Logical Operator1' */
  if (rtb_NOT) {
    /* Merge: '<S17>/Merge' incorporates:
     *  SignalConversion generated from: '<S54>/In1'
     */
    TOGGLER_B.Merge = TOGGLER_DW.Memory2_PreviousInput_k;
  }

  /* End of Outputs for SubSystem: '<S17>/Enabled Subsystem1' */

  /* Outport: '<Root>/output_ActiveCTRL' */
  TOGGLER_Y.output_ActiveCTRL = TOGGLER_B.Merge;

  /* Saturate: '<S5>/Saturation' incorporates:
   *  Inport: '<Root>/input_WT3_Misalignment'
   */
  if (TOGGLER_U.input_WT3_Misalignment > 20.0) {
    /* Outport: '<Root>/output_WFC_Offset' */
    TOGGLER_Y.output_WFC_Offset = 20.0;
  } else if (TOGGLER_U.input_WT3_Misalignment < -20.0) {
    /* Outport: '<Root>/output_WFC_Offset' */
    TOGGLER_Y.output_WFC_Offset = -20.0;
  } else {
    /* Outport: '<Root>/output_WFC_Offset' */
    TOGGLER_Y.output_WFC_Offset = TOGGLER_U.input_WT3_Misalignment;
  }

  /* End of Saturate: '<S5>/Saturation' */

  /* If: '<Root>/If3' */
  if (TOGGLER_B.Merge == 0.0) {
    /* Outputs for IfAction SubSystem: '<Root>/If Action Subsystem' incorporates:
     *  ActionPort: '<S6>/Action Port'
     */
    /* Outport: '<Root>/output_WFC_Offset_Demanded' */
    TOGGLER_Setoffsettozero(&TOGGLER_Y.output_WFC_Offset_Demanded);

    /* End of Outputs for SubSystem: '<Root>/If Action Subsystem' */
  } else if (TOGGLER_B.Merge == TOGGLER_ConstB.VectorConcatenate1[0]) {
    /* Outputs for IfAction SubSystem: '<Root>/If Action Subsystem3' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    /* Outport: '<Root>/output_WFC_Offset_Demanded' incorporates:
     *  Inport: '<Root>/input_WFC_Offset_1_deg'
     *  SignalConversion generated from: '<S8>/In1'
     */
    TOGGLER_Y.output_WFC_Offset_Demanded = TOGGLER_U.input_WFC_Offset_1_deg;

    /* End of Outputs for SubSystem: '<Root>/If Action Subsystem3' */
  } else if (TOGGLER_B.Merge == TOGGLER_ConstB.VectorConcatenate1[1]) {
    /* Outputs for IfAction SubSystem: '<Root>/If Action Subsystem4' incorporates:
     *  ActionPort: '<S9>/Action Port'
     */
    /* Outport: '<Root>/output_WFC_Offset_Demanded' incorporates:
     *  Constant: '<Root>/Greedy_Offset_deg'
     *  SignalConversion generated from: '<S9>/In1'
     */
    TOGGLER_Y.output_WFC_Offset_Demanded = 0.0;

    /* End of Outputs for SubSystem: '<Root>/If Action Subsystem4' */
  } else if (TOGGLER_B.Merge == TOGGLER_ConstB.VectorConcatenate1[2]) {
    /* Outputs for IfAction SubSystem: '<Root>/If Action Subsystem5' incorporates:
     *  ActionPort: '<S10>/Action Port'
     */
    /* Outport: '<Root>/output_WFC_Offset_Demanded' incorporates:
     *  Inport: '<Root>/input_WFC_Offset_2_deg'
     *  SignalConversion generated from: '<S10>/In1'
     */
    TOGGLER_Y.output_WFC_Offset_Demanded = TOGGLER_U.input_WFC_Offset_2_deg;

    /* End of Outputs for SubSystem: '<Root>/If Action Subsystem5' */
  } else if (TOGGLER_B.Merge == TOGGLER_ConstB.VectorConcatenate1[3]) {
    /* Outputs for IfAction SubSystem: '<Root>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    /* Outport: '<Root>/output_WFC_Offset_Demanded' incorporates:
     *  Inport: '<Root>/input_WFC_Offset_3_deg'
     *  SignalConversion generated from: '<S7>/In1'
     */
    TOGGLER_Y.output_WFC_Offset_Demanded = TOGGLER_U.input_WFC_Offset_3_deg;

    /* End of Outputs for SubSystem: '<Root>/If Action Subsystem1' */
  } else {
    /* Outputs for IfAction SubSystem: '<Root>/If Action Subsystem6' incorporates:
     *  ActionPort: '<S11>/Action Port'
     */
    /* Outport: '<Root>/output_WFC_Offset_Demanded' */
    TOGGLER_Setoffsettozero(&TOGGLER_Y.output_WFC_Offset_Demanded);

    /* End of Outputs for SubSystem: '<Root>/If Action Subsystem6' */
  }

  /* End of If: '<Root>/If3' */

  /* Product: '<S66>/Product' incorporates:
   *  Constant: '<S66>/Constant'
   *  Constant: '<S67>/Constant'
   *  Inport: '<Root>/input_FlagTurbineWFC_isActive'
   *  Logic: '<S18>/Logical Operator'
   *  RelationalOperator: '<S67>/Compare'
   */
  rtb_CTRLToSkip_b = (real_T)(TOGGLER_U.input_FlagTurbineWFC_isActive == 1.0) *
    0.1 * (real_T)(rtb_GreaterThan && (rtb_iL_k != 0.0));

  /* Sum: '<S66>/Sum' incorporates:
   *  UnitDelay: '<S66>/Unit Delay'
   */
  TOGGLER_DW.UnitDelay_DSTATE_c += rtb_CTRLToSkip_b;

  /* Product: '<S77>/Product' incorporates:
   *  Constant: '<S77>/Constant'
   *  Constant: '<S78>/Constant'
   *  Inport: '<Root>/input_FlagTurbineWFC_isActive'
   *  Logic: '<S18>/Logical Operator1'
   *  RelationalOperator: '<S78>/Compare'
   */
  rtb_y_p = (real_T)(TOGGLER_U.input_FlagTurbineWFC_isActive == 1.0) * 0.1 *
    (real_T)(rtb_NOT && (rtb_iL_k != 0.0));

  /* Sum: '<S77>/Sum' incorporates:
   *  UnitDelay: '<S77>/Unit Delay'
   */
  TOGGLER_DW.UnitDelay_DSTATE_e += rtb_y_p;

  /* Outport: '<Root>/output_TotWFCTime' incorporates:
   *  Gain: '<S66>/Gain2'
   *  Gain: '<S77>/Gain2'
   *  Sum: '<S18>/Add1'
   *  UnitDelay: '<S66>/Unit Delay'
   *  UnitDelay: '<S77>/Unit Delay'
   */
  TOGGLER_Y.output_TotWFCTime = 0.00027777777777777778 *
    TOGGLER_DW.UnitDelay_DSTATE_c + 0.00027777777777777778 *
    TOGGLER_DW.UnitDelay_DSTATE_e;

  /* Switch: '<S66>/Switch' incorporates:
   *  UnitDelay: '<S66>/Unit Delay'
   */
  rtb_GreaterThan = (TOGGLER_DW.UnitDelay_DSTATE_c != 0.0);

  /* Switch: '<S77>/Switch' incorporates:
   *  UnitDelay: '<S77>/Unit Delay'
   */
  rtb_NOT = (TOGGLER_DW.UnitDelay_DSTATE_e != 0.0);

  /* Switch: '<S66>/Switch' incorporates:
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  if (rtb_GreaterThan) {
    modValueRev = TOGGLER_DW.UnitDelay1_DSTATE_j[0];
  } else {
    modValueRev = TOGGLER_ConstB.Gain_i[0];
  }

  /* Sum: '<S66>/Sum1' incorporates:
   *  Product: '<S66>/Product1'
   *  RelationalOperator: '<S66>/Relational Operator'
   *  Switch: '<S66>/Switch'
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_j[0] = (real_T)(TOGGLER_DW.Memory2_PreviousInput ==
    TOGGLER_ConstB.VectorConcatenate1[0]) * rtb_CTRLToSkip_b + modValueRev;

  /* Product: '<S77>/Product1' incorporates:
   *  RelationalOperator: '<S77>/Relational Operator'
   */
  M = (real_T)(TOGGLER_DW.Memory2_PreviousInput_k ==
               TOGGLER_ConstB.VectorConcatenate1[0]) * rtb_y_p;

  /* Switch: '<S77>/Switch' incorporates:
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  if (rtb_NOT) {
    modValueRev = TOGGLER_DW.UnitDelay1_DSTATE_n[0];
  } else {
    modValueRev = TOGGLER_ConstB.Gain_o[0];
  }

  /* Sum: '<S77>/Sum1' incorporates:
   *  Switch: '<S77>/Switch'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_n[0] = modValueRev + M;

  /* Sum: '<S18>/Add' incorporates:
   *  Gain: '<S66>/Gain1'
   *  Gain: '<S77>/Gain1'
   *  UnitDelay: '<S66>/Unit Delay1'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  rtb_y_n[0] = 0.00027777777777777778 * TOGGLER_DW.UnitDelay1_DSTATE_j[0] +
    0.00027777777777777778 * TOGGLER_DW.UnitDelay1_DSTATE_n[0];

  /* Product: '<S77>/Product1' */
  rtb_y_i[0] = M;

  /* Switch: '<S66>/Switch' incorporates:
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  if (rtb_GreaterThan) {
    modValueRev = TOGGLER_DW.UnitDelay1_DSTATE_j[1];
  } else {
    modValueRev = TOGGLER_ConstB.Gain_i[1];
  }

  /* Sum: '<S66>/Sum1' incorporates:
   *  Product: '<S66>/Product1'
   *  RelationalOperator: '<S66>/Relational Operator'
   *  Switch: '<S66>/Switch'
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_j[1] = (real_T)(TOGGLER_DW.Memory2_PreviousInput ==
    TOGGLER_ConstB.VectorConcatenate1[1]) * rtb_CTRLToSkip_b + modValueRev;

  /* Product: '<S77>/Product1' incorporates:
   *  RelationalOperator: '<S77>/Relational Operator'
   */
  M = (real_T)(TOGGLER_DW.Memory2_PreviousInput_k ==
               TOGGLER_ConstB.VectorConcatenate1[1]) * rtb_y_p;

  /* Switch: '<S77>/Switch' incorporates:
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  if (rtb_NOT) {
    modValueRev = TOGGLER_DW.UnitDelay1_DSTATE_n[1];
  } else {
    modValueRev = TOGGLER_ConstB.Gain_o[1];
  }

  /* Sum: '<S77>/Sum1' incorporates:
   *  Switch: '<S77>/Switch'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_n[1] = modValueRev + M;

  /* Sum: '<S18>/Add' incorporates:
   *  Gain: '<S66>/Gain1'
   *  Gain: '<S77>/Gain1'
   *  UnitDelay: '<S66>/Unit Delay1'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  rtb_y_n[1] = 0.00027777777777777778 * TOGGLER_DW.UnitDelay1_DSTATE_j[1] +
    0.00027777777777777778 * TOGGLER_DW.UnitDelay1_DSTATE_n[1];

  /* Product: '<S77>/Product1' */
  rtb_y_i[1] = M;

  /* Switch: '<S66>/Switch' incorporates:
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  if (rtb_GreaterThan) {
    modValueRev = TOGGLER_DW.UnitDelay1_DSTATE_j[2];
  } else {
    modValueRev = TOGGLER_ConstB.Gain_i[2];
  }

  /* Sum: '<S66>/Sum1' incorporates:
   *  Product: '<S66>/Product1'
   *  RelationalOperator: '<S66>/Relational Operator'
   *  Switch: '<S66>/Switch'
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_j[2] = (real_T)(TOGGLER_DW.Memory2_PreviousInput ==
    TOGGLER_ConstB.VectorConcatenate1[2]) * rtb_CTRLToSkip_b + modValueRev;

  /* Product: '<S77>/Product1' incorporates:
   *  RelationalOperator: '<S77>/Relational Operator'
   */
  M = (real_T)(TOGGLER_DW.Memory2_PreviousInput_k ==
               TOGGLER_ConstB.VectorConcatenate1[2]) * rtb_y_p;

  /* Switch: '<S77>/Switch' incorporates:
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  if (rtb_NOT) {
    modValueRev = TOGGLER_DW.UnitDelay1_DSTATE_n[2];
  } else {
    modValueRev = TOGGLER_ConstB.Gain_o[2];
  }

  /* Sum: '<S77>/Sum1' incorporates:
   *  Switch: '<S77>/Switch'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_n[2] = modValueRev + M;

  /* Sum: '<S18>/Add' incorporates:
   *  Gain: '<S66>/Gain1'
   *  Gain: '<S77>/Gain1'
   *  UnitDelay: '<S66>/Unit Delay1'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  rtb_y_n[2] = 0.00027777777777777778 * TOGGLER_DW.UnitDelay1_DSTATE_j[2] +
    0.00027777777777777778 * TOGGLER_DW.UnitDelay1_DSTATE_n[2];

  /* Product: '<S77>/Product1' */
  rtb_y_i[2] = M;

  /* Switch: '<S66>/Switch' incorporates:
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  if (rtb_GreaterThan) {
    modValueRev = TOGGLER_DW.UnitDelay1_DSTATE_j[3];
  } else {
    modValueRev = TOGGLER_ConstB.Gain_i[3];
  }

  /* Sum: '<S66>/Sum1' incorporates:
   *  Product: '<S66>/Product1'
   *  RelationalOperator: '<S66>/Relational Operator'
   *  Switch: '<S66>/Switch'
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_j[3] = (real_T)(TOGGLER_DW.Memory2_PreviousInput ==
    TOGGLER_ConstB.VectorConcatenate1[3]) * rtb_CTRLToSkip_b + modValueRev;

  /* Product: '<S77>/Product1' incorporates:
   *  RelationalOperator: '<S77>/Relational Operator'
   */
  M = (real_T)(TOGGLER_DW.Memory2_PreviousInput_k ==
               TOGGLER_ConstB.VectorConcatenate1[3]) * rtb_y_p;

  /* Switch: '<S77>/Switch' incorporates:
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  if (rtb_NOT) {
    modValueRev = TOGGLER_DW.UnitDelay1_DSTATE_n[3];
  } else {
    modValueRev = TOGGLER_ConstB.Gain_o[3];
  }

  /* Sum: '<S77>/Sum1' incorporates:
   *  Switch: '<S77>/Switch'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_n[3] = modValueRev + M;

  /* Sum: '<S18>/Add' incorporates:
   *  Gain: '<S66>/Gain1'
   *  Gain: '<S77>/Gain1'
   *  UnitDelay: '<S66>/Unit Delay1'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  rtb_y_n[3] = 0.00027777777777777778 * TOGGLER_DW.UnitDelay1_DSTATE_j[3] +
    0.00027777777777777778 * TOGGLER_DW.UnitDelay1_DSTATE_n[3];

  /* Product: '<S77>/Product1' */
  rtb_y_i[3] = M;

  /* Outport: '<Root>/output_WFC1Time' */
  TOGGLER_Y.output_WFC1Time = rtb_y_n[0];

  /* Outport: '<Root>/output_GreedyWFCTime' */
  TOGGLER_Y.output_GreedyWFCTime = rtb_y_n[1];

  /* Outport: '<Root>/output_WFC2Time' */
  TOGGLER_Y.output_WFC2Time = rtb_y_n[2];

  /* Outport: '<Root>/output_WFC3Time' */
  TOGGLER_Y.output_WFC3Time = rtb_y_n[3];

  /* If: '<Root>/If' */
  if (!(rtb_iL_k == 1.0)) {
    /* Outputs for IfAction SubSystem: '<Root>/Set offset to zero' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    TOGGLER_Setoffsettozero(&modValueRev);

    /* End of Outputs for SubSystem: '<Root>/Set offset to zero' */
  }

  /* End of If: '<Root>/If' */

  /* Switch: '<S15>/Switch1' incorporates:
   *  Constant: '<S15>/Constant'
   *  Logic: '<S15>/Logical Operator'
   *  RelationalOperator: '<S50>/Compare'
   *  Switch: '<S15>/Switch3'
   *  UnitDelay: '<S15>/Unit Delay1'
   *  UnitDelay: '<S15>/Unit Delay3'
   */
  if ((boolean_T)(rtb_LogicalOperator_op ^ TOGGLER_DW.UnitDelay3_DSTATE_d)) {
    rtb_y_p = 1000.0;
  } else {
    rtb_y_p = TOGGLER_DW.UnitDelay1_DSTATE;
  }

  /* End of Switch: '<S15>/Switch1' */

  /* Sum: '<S15>/Sum' incorporates:
   *  UnitDelay: '<S15>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE = rtb_y_p - 1.0;

  /* Product: '<S68>/Divide' incorporates:
   *  Sum: '<S68>/Sum of Elements1'
   *  Sum: '<S68>/Sum of Elements2'
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  modValueRev = (((TOGGLER_DW.UnitDelay1_DSTATE_j[0] +
                   TOGGLER_DW.UnitDelay1_DSTATE_j[1]) +
                  TOGGLER_DW.UnitDelay1_DSTATE_j[2]) +
                 TOGGLER_DW.UnitDelay1_DSTATE_j[3]) / (real_T)((((int32_T)
    rtb_available_h[0] + (int32_T)rtb_available_h[1]) + (int32_T)
    rtb_available_h[2]) + (int32_T)rtb_available_h[3]);

  /* Product: '<S68>/Product2' incorporates:
   *  Sum: '<S68>/Subtract'
   *  UnitDelay: '<S66>/Unit Delay1'
   */
  M = (TOGGLER_DW.UnitDelay1_DSTATE_j[0] - modValueRev) * rtb_available_h[0];
  rtb_available_h[0] = M;
  Mprev = (TOGGLER_DW.UnitDelay1_DSTATE_j[1] - modValueRev) * rtb_available_h[1];
  rtb_available_h[1] = Mprev;
  rtb_Mod1 = (TOGGLER_DW.UnitDelay1_DSTATE_j[2] - modValueRev) *
    rtb_available_h[2];
  rtb_available_h[2] = rtb_Mod1;
  rtb_MovingAverage2_0 = (TOGGLER_DW.UnitDelay1_DSTATE_j[3] - modValueRev) *
    rtb_available_h[3];
  rtb_available_h[3] = rtb_MovingAverage2_0;

  /* MATLAB Function: '<S68>/MATLAB Function1' */
  TOGGLER_MATLABFunction1(rtb_y_n);

  /* Product: '<S68>/Product' */
  modValueRev = rtb_y_n[0] * TOGGLER_ConstB.Gain3;
  y = rtb_y_n[1] * TOGGLER_ConstB.Gain3;
  T = rtb_y_n[2] * TOGGLER_ConstB.Gain3;
  S = rtb_y_n[3] * TOGGLER_ConstB.Gain3;

  /* MATLAB Function: '<S68>/MATLAB Function2' incorporates:
   *  Memory: '<S68>/Memory3'
   *  Memory: '<S68>/Memory4'
   *  Memory: '<S68>/Memory5'
   */
  TOGGLER_MATLABFunction2(TOGGLER_DW.Memory4_PreviousInput,
    TOGGLER_DW.Memory3_PreviousInput, TOGGLER_DW.Memory5_PreviousInput, rtb_y_l);

  /* Switch: '<S68>/Switch' incorporates:
   *  Memory: '<S68>/Memory2'
   */
  if (TOGGLER_DW.Memory2_PreviousInput_kq) {
    /* Switch: '<S68>/Switch1' incorporates:
     *  Memory: '<S68>/Memory'
     *  Memory: '<S68>/Memory1'
     */
    if (TOGGLER_DW.Memory1_PreviousInput_l != 0) {
      rtb_y_l[0] = TOGGLER_DW.Memory_PreviousInput[0];
      rtb_y_l[1] = TOGGLER_DW.Memory_PreviousInput[1];
      rtb_y_l[2] = TOGGLER_DW.Memory_PreviousInput[2];
      rtb_y_l[3] = TOGGLER_DW.Memory_PreviousInput[3];
    } else {
      rtb_y_l[0] = modValueRev;
      rtb_y_l[1] = y;
      rtb_y_l[2] = T;
      rtb_y_l[3] = S;
    }

    /* End of Switch: '<S68>/Switch1' */
  }

  /* End of Switch: '<S68>/Switch' */

  /* RelationalOperator: '<S68>/GT' incorporates:
   *  Product: '<S68>/Product2'
   */
  rtb_RelationalOperator_hc[0] = (M > rtb_y_l[0]);
  rtb_RelationalOperator_hc[1] = (Mprev > rtb_y_l[1]);
  rtb_RelationalOperator_hc[2] = (rtb_Mod1 > rtb_y_l[2]);
  rtb_RelationalOperator_hc[3] = (rtb_MovingAverage2_0 > rtb_y_l[3]);

  /* RelationalOperator: '<S71>/Compare' incorporates:
   *  Constant: '<S71>/Constant'
   *  Sum: '<S68>/Sum of Elements'
   */
  rtb_GreaterThan = ((uint8_T)((((uint32_T)rtb_RelationalOperator_hc[0] +
    rtb_RelationalOperator_hc[1]) + rtb_RelationalOperator_hc[2]) +
    rtb_RelationalOperator_hc[3]) != 0);

  /* MATLAB Function: '<S68>/MATLAB Function' */
  TOGGLER_MATLABFunction(rtb_RelationalOperator_hc,
    TOGGLER_ConstB.VectorConcatenate1, &M, &TOGGLER_DW.Memory5_PreviousInput);

  /* MATLAB Function: '<S68>/MATLAB Function3' */
  TOGGLER_MATLABFunction3(rtb_available_h, TOGGLER_DW.Memory5_PreviousInput,
    &Mprev);

  /* Switch: '<S68>/Switch2' incorporates:
   *  UnitDelay: '<S68>/Unit Delay3'
   */
  if (rtb_GreaterThan) {
    TOGGLER_DW.UnitDelay3_DSTATE = M;
  }

  /* End of Switch: '<S68>/Switch2' */

  /* Logic: '<S66>/Logical Operator' incorporates:
   *  Constant: '<S70>/Constant'
   *  RelationalOperator: '<S66>/Relational Operator1'
   *  RelationalOperator: '<S66>/Relational Operator2'
   *  RelationalOperator: '<S70>/Compare'
   *  UnitDelay: '<S66>/Unit Delay2'
   *  UnitDelay: '<S68>/Unit Delay3'
   */
  rtb_NOT = (rtb_GreaterThan && (TOGGLER_DW.UnitDelay3_DSTATE ==
              TOGGLER_DW.Memory2_PreviousInput) &&
             (TOGGLER_DW.Memory2_PreviousInput != TOGGLER_DW.UnitDelay2_DSTATE) &&
             TOGGLER_ConstB.Compare && (TOGGLER_DW.Memory1_PreviousInput == 0.0));

  /* Sum: '<S68>/Sum of Elements3' */
  i = (int32_T)((((uint32_T)rtb_RelationalOperator_hc[0] +
                  rtb_RelationalOperator_hc[1]) + rtb_RelationalOperator_hc[2])
                + rtb_RelationalOperator_hc[3]);

  /* Product: '<S79>/Divide' incorporates:
   *  Sum: '<S79>/Sum of Elements1'
   *  Sum: '<S79>/Sum of Elements2'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  M = (((TOGGLER_DW.UnitDelay1_DSTATE_n[0] + TOGGLER_DW.UnitDelay1_DSTATE_n[1])
        + TOGGLER_DW.UnitDelay1_DSTATE_n[2]) + TOGGLER_DW.UnitDelay1_DSTATE_n[3])
    / (real_T)((((int32_T)rtb_available[0] + (int32_T)rtb_available[1]) +
                (int32_T)rtb_available[2]) + rtb_available_nt);

  /* Product: '<S79>/Product2' incorporates:
   *  Sum: '<S79>/Subtract'
   *  UnitDelay: '<S77>/Unit Delay1'
   */
  rtb_iL_k = (TOGGLER_DW.UnitDelay1_DSTATE_n[0] - M) * rtb_available[0];
  rtb_available[0] = rtb_iL_k;
  rtb_y_p = (TOGGLER_DW.UnitDelay1_DSTATE_n[1] - M) * rtb_available[1];
  rtb_available[1] = rtb_y_p;
  rtb_CTRLToSkip_b = (TOGGLER_DW.UnitDelay1_DSTATE_n[2] - M) * rtb_available[2];
  rtb_available[2] = rtb_CTRLToSkip_b;
  rtb_available_tmp = (TOGGLER_DW.UnitDelay1_DSTATE_n[3] - M) * (real_T)
    rtb_available_nt;
  rtb_available[3] = rtb_available_tmp;

  /* MATLAB Function: '<S79>/MATLAB Function1' */
  TOGGLER_MATLABFunction1(rtb_y_i);

  /* Product: '<S79>/Product' */
  M = rtb_y_i[0] * TOGGLER_ConstB.Gain3_e;
  rtb_Mod1 = rtb_y_i[1] * TOGGLER_ConstB.Gain3_e;
  rtb_MovingAverage2_0 = rtb_y_i[2] * TOGGLER_ConstB.Gain3_e;
  rtb_y_e = rtb_y_i[3] * TOGGLER_ConstB.Gain3_e;

  /* MATLAB Function: '<S79>/MATLAB Function2' incorporates:
   *  Memory: '<S79>/Memory3'
   *  Memory: '<S79>/Memory4'
   *  Memory: '<S79>/Memory5'
   */
  TOGGLER_MATLABFunction2(TOGGLER_DW.Memory4_PreviousInput_c,
    TOGGLER_DW.Memory3_PreviousInput_h, TOGGLER_DW.Memory5_PreviousInput_b,
    rtb_y_n);

  /* Switch: '<S79>/Switch' incorporates:
   *  Memory: '<S79>/Memory2'
   */
  if (TOGGLER_DW.Memory2_PreviousInput_e) {
    /* Switch: '<S79>/Switch1' incorporates:
     *  Memory: '<S79>/Memory'
     *  Memory: '<S79>/Memory1'
     */
    if (TOGGLER_DW.Memory1_PreviousInput_p != 0) {
      rtb_y_n[0] = TOGGLER_DW.Memory_PreviousInput_m[0];
      rtb_y_n[1] = TOGGLER_DW.Memory_PreviousInput_m[1];
      rtb_y_n[2] = TOGGLER_DW.Memory_PreviousInput_m[2];
      rtb_y_n[3] = TOGGLER_DW.Memory_PreviousInput_m[3];
    } else {
      rtb_y_n[0] = M;
      rtb_y_n[1] = rtb_Mod1;
      rtb_y_n[2] = rtb_MovingAverage2_0;
      rtb_y_n[3] = rtb_y_e;
    }

    /* End of Switch: '<S79>/Switch1' */
  }

  /* End of Switch: '<S79>/Switch' */

  /* RelationalOperator: '<S79>/GT' incorporates:
   *  Product: '<S79>/Product2'
   */
  rtb_RelationalOperator_hc[0] = (rtb_iL_k > rtb_y_n[0]);
  rtb_RelationalOperator_hc[1] = (rtb_y_p > rtb_y_n[1]);
  rtb_RelationalOperator_hc[2] = (rtb_CTRLToSkip_b > rtb_y_n[2]);
  rtb_RelationalOperator_hc[3] = (rtb_available_tmp > rtb_y_n[3]);

  /* Sum: '<S79>/Sum of Elements' incorporates:
   *  Sum: '<S79>/Sum of Elements3'
   */
  TOGGLER_DW.Memory1_PreviousInput_p = (uint8_T)((((uint32_T)
    rtb_RelationalOperator_hc[0] + rtb_RelationalOperator_hc[1]) +
    rtb_RelationalOperator_hc[2]) + rtb_RelationalOperator_hc[3]);

  /* RelationalOperator: '<S82>/Compare' incorporates:
   *  Constant: '<S82>/Constant'
   *  Sum: '<S79>/Sum of Elements'
   */
  rtb_GreaterThan = (TOGGLER_DW.Memory1_PreviousInput_p != 0);

  /* MATLAB Function: '<S79>/MATLAB Function' */
  TOGGLER_MATLABFunction(rtb_RelationalOperator_hc,
    TOGGLER_ConstB.VectorConcatenate1, &rtb_CTRLToSkip_b, &rtb_iL_k);

  /* MATLAB Function: '<S79>/MATLAB Function3' */
  TOGGLER_MATLABFunction3(rtb_available, rtb_iL_k, &rtb_y_p);

  /* Switch: '<S79>/Switch2' incorporates:
   *  UnitDelay: '<S79>/Unit Delay3'
   */
  if (rtb_GreaterThan) {
    TOGGLER_DW.UnitDelay3_DSTATE_h = rtb_CTRLToSkip_b;
  }

  /* End of Switch: '<S79>/Switch2' */

  /* Switch: '<S89>/Switch1' incorporates:
   *  UnitDelay: '<S89>/Unit Delay1'
   */
  TOGGLER_DW.UnitDelay1_DSTATE_f = counter;

  /* Update for Delay: '<S19>/Delay' incorporates:
   *  Inport: '<Root>/input_Dir_deg'
   */
  TOGGLER_DW.Delay_DSTATE_m = TOGGLER_U.input_Dir_deg;

  /* Update for UnitDelay: '<S91>/Unit Delay' */
  TOGGLER_DW.UnitDelay_DSTATE_d = rtb_MovingStandardDeviation1;

  /* Switch: '<S66>/Switch1' */
  if (rtb_NOT) {
    /* Update for Memory: '<S62>/Memory1' incorporates:
     *  Constant: '<S66>/Constant4'
     */
    TOGGLER_DW.Memory1_PreviousInput = 21000.0;
  }

  /* End of Switch: '<S66>/Switch1' */

  /* Switch: '<S77>/Switch1' incorporates:
   *  Constant: '<S81>/Constant'
   *  Logic: '<S77>/Logical Operator'
   *  RelationalOperator: '<S77>/Relational Operator1'
   *  RelationalOperator: '<S77>/Relational Operator2'
   *  RelationalOperator: '<S81>/Compare'
   *  UnitDelay: '<S77>/Unit Delay2'
   *  UnitDelay: '<S79>/Unit Delay3'
   */
  if (rtb_GreaterThan && (TOGGLER_DW.UnitDelay3_DSTATE_h ==
                          TOGGLER_DW.Memory2_PreviousInput_k) &&
      (TOGGLER_DW.Memory2_PreviousInput_k != TOGGLER_DW.UnitDelay2_DSTATE_p) &&
      TOGGLER_ConstB.Compare_n && (TOGGLER_DW.Memory1_PreviousInput_j == 0.0)) {
    /* Update for Memory: '<S64>/Memory1' incorporates:
     *  Constant: '<S77>/Constant4'
     */
    TOGGLER_DW.Memory1_PreviousInput_j = 21000.0;
  }

  /* End of Switch: '<S77>/Switch1' */

  /* Update for UnitDelay: '<S15>/Unit Delay3' incorporates:
   *  RelationalOperator: '<S50>/Compare'
   */
  TOGGLER_DW.UnitDelay3_DSTATE_d = rtb_LogicalOperator_op;

  /* Update for Memory: '<S68>/Memory1' incorporates:
   *  Sum: '<S68>/Sum of Elements3'
   */
  TOGGLER_DW.Memory1_PreviousInput_l = (uint8_T)i;

  /* Update for Memory: '<S68>/Memory2' incorporates:
   *  RelationalOperator: '<S68>/Relational Operator'
   */
  TOGGLER_DW.Memory2_PreviousInput_kq = (Mprev <= TOGGLER_ConstB.Gain);

  /* Update for Memory: '<S68>/Memory4' */
  TOGGLER_DW.Memory4_PreviousInput = TOGGLER_ConstB.Gain;

  /* Update for UnitDelay: '<S66>/Unit Delay2' */
  TOGGLER_DW.UnitDelay2_DSTATE = TOGGLER_DW.Memory2_PreviousInput;

  /* Update for Memory: '<S79>/Memory2' incorporates:
   *  RelationalOperator: '<S79>/Relational Operator'
   */
  TOGGLER_DW.Memory2_PreviousInput_e = (rtb_y_p <= TOGGLER_ConstB.Gain_h);

  /* Update for Memory: '<S79>/Memory4' */
  TOGGLER_DW.Memory4_PreviousInput_c = TOGGLER_ConstB.Gain_h;

  /* Update for Memory: '<S68>/Memory' */
  TOGGLER_DW.Memory_PreviousInput[0] = rtb_y_l[0];

  /* Update for Memory: '<S68>/Memory3' */
  TOGGLER_DW.Memory3_PreviousInput[0] = modValueRev;

  /* Update for Memory: '<S79>/Memory' */
  TOGGLER_DW.Memory_PreviousInput_m[0] = rtb_y_n[0];

  /* Update for Memory: '<S79>/Memory3' */
  TOGGLER_DW.Memory3_PreviousInput_h[0] = M;

  /* Update for Memory: '<S68>/Memory' */
  TOGGLER_DW.Memory_PreviousInput[1] = rtb_y_l[1];

  /* Update for Memory: '<S68>/Memory3' */
  TOGGLER_DW.Memory3_PreviousInput[1] = y;

  /* Update for Memory: '<S79>/Memory' */
  TOGGLER_DW.Memory_PreviousInput_m[1] = rtb_y_n[1];

  /* Update for Memory: '<S79>/Memory3' */
  TOGGLER_DW.Memory3_PreviousInput_h[1] = rtb_Mod1;

  /* Update for Memory: '<S68>/Memory' */
  TOGGLER_DW.Memory_PreviousInput[2] = rtb_y_l[2];

  /* Update for Memory: '<S68>/Memory3' */
  TOGGLER_DW.Memory3_PreviousInput[2] = T;

  /* Update for Memory: '<S79>/Memory' */
  TOGGLER_DW.Memory_PreviousInput_m[2] = rtb_y_n[2];

  /* Update for Memory: '<S79>/Memory3' */
  TOGGLER_DW.Memory3_PreviousInput_h[2] = rtb_MovingAverage2_0;

  /* Update for Memory: '<S68>/Memory' */
  TOGGLER_DW.Memory_PreviousInput[3] = rtb_y_l[3];

  /* Update for Memory: '<S68>/Memory3' */
  TOGGLER_DW.Memory3_PreviousInput[3] = S;

  /* Update for Memory: '<S79>/Memory' */
  TOGGLER_DW.Memory_PreviousInput_m[3] = rtb_y_n[3];

  /* Update for Memory: '<S79>/Memory3' */
  TOGGLER_DW.Memory3_PreviousInput_h[3] = rtb_y_e;

  /* Update for Memory: '<S79>/Memory5' */
  TOGGLER_DW.Memory5_PreviousInput_b = rtb_iL_k;

  /* Update for UnitDelay: '<S77>/Unit Delay2' */
  TOGGLER_DW.UnitDelay2_DSTATE_p = TOGGLER_DW.Memory2_PreviousInput_k;
}

/* Model initialize function */
void TOGGLER_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(TOGGLER_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &TOGGLER_B), 0,
                sizeof(B_TOGGLER_T));

  /* states (dwork) */
  (void) memset((void *)&TOGGLER_DW, 0,
                sizeof(DW_TOGGLER_T));

  /* external inputs */
  (void)memset(&TOGGLER_U, 0, sizeof(ExtU_TOGGLER_T));

  /* external outputs */
  (void)memset(&TOGGLER_Y, 0, sizeof(ExtY_TOGGLER_T));

  {
    g_dsp_internal_SlidingWindowA_T *obj_0;
    g_dsp_internal_SlidingWindowV_T *obj;
    int32_T i;
    TOGGLER_PrevZCX.SampleandHold_Trig_ZCE = POS_ZCSIG;

    /* InitializeConditions for Memory: '<S68>/Memory2' */
    TOGGLER_DW.Memory2_PreviousInput_kq = true;

    /* InitializeConditions for Memory: '<S79>/Memory2' */
    TOGGLER_DW.Memory2_PreviousInput_e = true;

    /* SystemInitialize for Merge: '<S16>/Merge3' */
    TOGGLER_B.Merge3[0] = false;
    TOGGLER_B.Merge3[1] = false;
    TOGGLER_B.Merge3[2] = false;

    /* SystemInitialize for Merge: '<S17>/Merge' */
    TOGGLER_B.Merge = 0.0;

    /* Start for MATLABSystem: '<S25>/Moving Standard Deviation1' */
    TOGGLER_DW.obj_l.isInitialized = 0;
    TOGGLER_DW.obj_l.NumChannels = -1;
    TOGGLER_DW.obj_l.FrameLength = -1;
    TOGGLER_DW.obj_l.matlabCodegenIsDeleted = false;
    TOGGLER_SystemCore_setup(&TOGGLER_DW.obj_l);

    /* InitializeConditions for MATLABSystem: '<S25>/Moving Standard Deviation1' */
    obj = TOGGLER_DW.obj_l.pStatistic;
    if (obj->isInitialized == 1) {
      for (i = 0; i < 100; i++) {
        obj->pReverseSamples[i] = 0.0;
      }

      for (i = 0; i < 100; i++) {
        obj->pReverseT[i] = 0.0;
      }

      for (i = 0; i < 100; i++) {
        obj->pReverseS[i] = 0.0;
      }

      obj->pT = 0.0;
      obj->pS = 0.0;
      obj->pM = 0.0;
      obj->pCounter = 1.0;
      obj->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<S25>/Moving Standard Deviation1' */

    /* Start for MATLABSystem: '<S24>/Moving Standard Deviation1' */
    TOGGLER_DW.obj_ds.isInitialized = 0;
    TOGGLER_DW.obj_ds.NumChannels = -1;
    TOGGLER_DW.obj_ds.FrameLength = -1;
    TOGGLER_DW.obj_ds.matlabCodegenIsDeleted = false;
    TOGGLER_SystemCore_setup(&TOGGLER_DW.obj_ds);

    /* InitializeConditions for MATLABSystem: '<S24>/Moving Standard Deviation1' */
    obj = TOGGLER_DW.obj_ds.pStatistic;
    if (obj->isInitialized == 1) {
      for (i = 0; i < 100; i++) {
        obj->pReverseSamples[i] = 0.0;
      }

      for (i = 0; i < 100; i++) {
        obj->pReverseT[i] = 0.0;
      }

      for (i = 0; i < 100; i++) {
        obj->pReverseS[i] = 0.0;
      }

      obj->pT = 0.0;
      obj->pS = 0.0;
      obj->pM = 0.0;
      obj->pCounter = 1.0;
      obj->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<S24>/Moving Standard Deviation1' */

    /* Start for MATLABSystem: '<Root>/Moving Average' */
    TOGGLER_DW.obj_d.isInitialized = 0;
    TOGGLER_DW.obj_d.NumChannels = -1;
    TOGGLER_DW.obj_d.FrameLength = -1;
    TOGGLER_DW.obj_d.matlabCodegenIsDeleted = false;
    TOGGLER_SystemCore_setup_gi(&TOGGLER_DW.obj_d);

    /* InitializeConditions for MATLABSystem: '<Root>/Moving Average' */
    obj_0 = TOGGLER_DW.obj_d.pStatistic;
    if (obj_0->isInitialized == 1) {
      obj_0->pCumSum = 0.0;
      for (i = 0; i < 5999; i++) {
        obj_0->pCumSumRev[i] = 0.0;
      }

      obj_0->pCumRevIndex = 1.0;
      obj_0->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/Moving Average' */

    /* Start for MATLABSystem: '<Root>/Moving Average2' */
    TOGGLER_DW.obj.isInitialized = 0;
    TOGGLER_DW.obj.NumChannels = -1;
    TOGGLER_DW.obj.FrameLength = -1;
    TOGGLER_DW.obj.matlabCodegenIsDeleted = false;
    TOGGLER_SystemCore_setup_gi(&TOGGLER_DW.obj);

    /* InitializeConditions for MATLABSystem: '<Root>/Moving Average2' */
    obj_0 = TOGGLER_DW.obj.pStatistic;
    if (obj_0->isInitialized == 1) {
      obj_0->pCumSum = 0.0;
      for (i = 0; i < 5999; i++) {
        obj_0->pCumSumRev[i] = 0.0;
      }

      obj_0->pCumRevIndex = 1.0;
      obj_0->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/Moving Average2' */
  }
}

/* Model terminate function */
void TOGGLER_terminate(void)
{
  g_dsp_internal_SlidingWindowA_T *obj_0;
  g_dsp_internal_SlidingWindowV_T *obj;

  /* Terminate for MATLABSystem: '<S25>/Moving Standard Deviation1' */
  if (!TOGGLER_DW.obj_l.matlabCodegenIsDeleted) {
    TOGGLER_DW.obj_l.matlabCodegenIsDeleted = true;
    if ((TOGGLER_DW.obj_l.isInitialized == 1) &&
        TOGGLER_DW.obj_l.isSetupComplete) {
      obj = TOGGLER_DW.obj_l.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      TOGGLER_DW.obj_l.NumChannels = -1;
      TOGGLER_DW.obj_l.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S25>/Moving Standard Deviation1' */

  /* Terminate for MATLABSystem: '<S24>/Moving Standard Deviation1' */
  if (!TOGGLER_DW.obj_ds.matlabCodegenIsDeleted) {
    TOGGLER_DW.obj_ds.matlabCodegenIsDeleted = true;
    if ((TOGGLER_DW.obj_ds.isInitialized == 1) &&
        TOGGLER_DW.obj_ds.isSetupComplete) {
      obj = TOGGLER_DW.obj_ds.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      TOGGLER_DW.obj_ds.NumChannels = -1;
      TOGGLER_DW.obj_ds.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S24>/Moving Standard Deviation1' */

  /* Terminate for MATLABSystem: '<Root>/Moving Average' */
  if (!TOGGLER_DW.obj_d.matlabCodegenIsDeleted) {
    TOGGLER_DW.obj_d.matlabCodegenIsDeleted = true;
    if ((TOGGLER_DW.obj_d.isInitialized == 1) &&
        TOGGLER_DW.obj_d.isSetupComplete) {
      obj_0 = TOGGLER_DW.obj_d.pStatistic;
      if (obj_0->isInitialized == 1) {
        obj_0->isInitialized = 2;
      }

      TOGGLER_DW.obj_d.NumChannels = -1;
      TOGGLER_DW.obj_d.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Moving Average' */

  /* Terminate for MATLABSystem: '<Root>/Moving Average2' */
  if (!TOGGLER_DW.obj.matlabCodegenIsDeleted) {
    TOGGLER_DW.obj.matlabCodegenIsDeleted = true;
    if ((TOGGLER_DW.obj.isInitialized == 1) && TOGGLER_DW.obj.isSetupComplete) {
      obj_0 = TOGGLER_DW.obj.pStatistic;
      if (obj_0->isInitialized == 1) {
        obj_0->isInitialized = 2;
      }

      TOGGLER_DW.obj.NumChannels = -1;
      TOGGLER_DW.obj.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Moving Average2' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
