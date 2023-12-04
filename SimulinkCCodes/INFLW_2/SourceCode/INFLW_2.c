/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: INFLW_2.c
 *
 * Code generated for Simulink model 'INFLW_2'.
 *
 * Model version                  : 1.6
 * Simulink Coder version         : 9.8 (R2022b) 13-May-2022
 * C/C++ source code generated on : Mon Dec  4 03:05:59 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "INFLW_2.h"
#include "rtwtypes.h"
#include "INFLW_2_types.h"
#include "INFLW_2_private.h"
#include <string.h>
#include <math.h>
#include "rt_nonfinite.h"
#include <float.h>
#include "rt_defines.h"

/* Block signals (default storage) */
B_INFLW_2_T INFLW_2_B;

/* Block states (default storage) */
DW_INFLW_2_T INFLW_2_DW;

/* External inputs (root inport signals with default storage) */
ExtU_INFLW_2_T INFLW_2_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_INFLW_2_T INFLW_2_Y;

/* Real-time model */
static RT_MODEL_INFLW_2_T INFLW_2_M_;
RT_MODEL_INFLW_2_T *const INFLW_2_M = &INFLW_2_M_;

/* Forward declaration for local functions */
static void INFLW_2_SystemCore_setup(dsp_simulink_MovingAverage_IN_T *obj);

/* Forward declaration for local functions */
static void INFLW_2_SystemCore_setup_n(dsp_simulink_MovingAverage_e_T *obj);

/* Forward declaration for local functions */
static void INFLW_2_SystemCore_setup_n2(dsp_simulink_MovingStandardDe_T *obj);

/* Forward declaration for local functions */
static void INFLW_2_SystemCore_setup_meu(dsp_simulink_MovingStandardDe_T *obj);
static void INFLW_2_SystemCore_setup_me(dsp_simulink_MovingStandard_m_T *obj);
static void INFLW_2_SystemCore_setup_meus(dsp_simulink_MovingAverage_me_T *obj);
static void INFLW_2_SystemCore_setup_m(dsp_simulink_MovingAverage_m_T *obj);
static void INFLW_2_SystemCore_setup(dsp_simulink_MovingAverage_IN_T *obj)
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

/* System initialize for atomic system: */
void INFLW_2_MovingAverage2_Init(DW_MovingAverage2_INFLW_2_T *localDW)
{
  g_dsp_internal_SlidingWindowA_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<Root>/Moving Average2' */
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.FrameLength = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  INFLW_2_SystemCore_setup(&localDW->obj);

  /* InitializeConditions for MATLABSystem: '<Root>/Moving Average2' */
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized == 1) {
    obj->pCumSum = 0.0;
    for (i = 0; i < 5999; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->pModValueRev = 0.0;
  }

  /* End of InitializeConditions for MATLABSystem: '<Root>/Moving Average2' */
}

/* Output and update for atomic system: */
void INFLW_2_MovingAverage2(real_T rtu_0, B_MovingAverage2_INFLW_2_T *localB,
  DW_MovingAverage2_INFLW_2_T *localDW)
{
  g_dsp_internal_SlidingWindowA_T *obj;
  real_T csum;
  real_T cumRevIndex;
  real_T modValueRev;
  real_T z;
  int32_T i;

  /* MATLABSystem: '<Root>/Moving Average2' */
  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
  }

  obj = localDW->obj.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->pCumSum = 0.0;
    for (i = 0; i < 5999; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->pModValueRev = 0.0;
    obj->isSetupComplete = true;
    obj->pCumSum = 0.0;
    for (i = 0; i < 5999; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->pModValueRev = 0.0;
  }

  cumRevIndex = obj->pCumRevIndex;
  csum = obj->pCumSum;
  for (i = 0; i < 5999; i++) {
    localB->csumrev[i] = obj->pCumSumRev[i];
  }

  modValueRev = obj->pModValueRev;
  z = 0.0;

  /* MATLABSystem: '<Root>/Moving Average2' */
  localB->MovingAverage2 = 0.0;

  /* MATLABSystem: '<Root>/Moving Average2' */
  csum += rtu_0;
  if (modValueRev == 0.0) {
    z = localB->csumrev[(int32_T)cumRevIndex - 1] + csum;
  }

  localB->csumrev[(int32_T)cumRevIndex - 1] = rtu_0;
  if (cumRevIndex != 5999.0) {
    cumRevIndex++;
  } else {
    cumRevIndex = 1.0;
    csum = 0.0;
    for (i = 5997; i >= 0; i--) {
      localB->csumrev[i] += localB->csumrev[i + 1];
    }
  }

  if (modValueRev == 0.0) {
    /* MATLABSystem: '<Root>/Moving Average2' */
    localB->MovingAverage2 = z / 6000.0;
  }

  obj->pCumSum = csum;
  for (i = 0; i < 5999; i++) {
    obj->pCumSumRev[i] = localB->csumrev[i];
  }

  obj->pCumRevIndex = cumRevIndex;
  if (modValueRev > 0.0) {
    obj->pModValueRev = modValueRev - 1.0;
  } else {
    obj->pModValueRev = 0.0;
  }
}

/* Termination for atomic system: */
void INFLW_2_MovingAverage2_Term(DW_MovingAverage2_INFLW_2_T *localDW)
{
  g_dsp_internal_SlidingWindowA_T *obj;

  /* Terminate for MATLABSystem: '<Root>/Moving Average2' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      obj = localDW->obj.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      localDW->obj.NumChannels = -1;
      localDW->obj.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Moving Average2' */
}

static void INFLW_2_SystemCore_setup_n(dsp_simulink_MovingAverage_e_T *obj)
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

/* System initialize for atomic system: */
void INFLW_2_MovingAverage5_Init(DW_MovingAverage5_INFLW_2_T *localDW)
{
  g_dsp_internal_SlidingWindo_l_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S6>/Moving Average5' */
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.FrameLength = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  INFLW_2_SystemCore_setup_n(&localDW->obj);

  /* InitializeConditions for MATLABSystem: '<S6>/Moving Average5' */
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized == 1) {
    obj->pCumSum = 0.0;
    for (i = 0; i < 599; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->pModValueRev = 0.0;
  }

  /* End of InitializeConditions for MATLABSystem: '<S6>/Moving Average5' */
}

/* Output and update for atomic system: */
void INFLW_2_MovingAverage5(real_T rtu_0, B_MovingAverage5_INFLW_2_T *localB,
  DW_MovingAverage5_INFLW_2_T *localDW)
{
  g_dsp_internal_SlidingWindo_l_T *obj;
  real_T csum;
  real_T cumRevIndex;
  real_T modValueRev;
  real_T z;
  int32_T i;

  /* MATLABSystem: '<S6>/Moving Average5' */
  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
  }

  obj = localDW->obj.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    obj->pCumSum = 0.0;
    for (i = 0; i < 599; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->pModValueRev = 0.0;
    obj->isSetupComplete = true;
    obj->pCumSum = 0.0;
    for (i = 0; i < 599; i++) {
      obj->pCumSumRev[i] = 0.0;
    }

    obj->pCumRevIndex = 1.0;
    obj->pModValueRev = 0.0;
  }

  cumRevIndex = obj->pCumRevIndex;
  csum = obj->pCumSum;
  for (i = 0; i < 599; i++) {
    localB->csumrev[i] = obj->pCumSumRev[i];
  }

  modValueRev = obj->pModValueRev;
  z = 0.0;

  /* MATLABSystem: '<S6>/Moving Average5' */
  localB->MovingAverage5 = 0.0;

  /* MATLABSystem: '<S6>/Moving Average5' */
  csum += rtu_0;
  if (modValueRev == 0.0) {
    z = localB->csumrev[(int32_T)cumRevIndex - 1] + csum;
  }

  localB->csumrev[(int32_T)cumRevIndex - 1] = rtu_0;
  if (cumRevIndex != 599.0) {
    cumRevIndex++;
  } else {
    cumRevIndex = 1.0;
    csum = 0.0;
    for (i = 597; i >= 0; i--) {
      localB->csumrev[i] += localB->csumrev[i + 1];
    }
  }

  if (modValueRev == 0.0) {
    /* MATLABSystem: '<S6>/Moving Average5' */
    localB->MovingAverage5 = z / 600.0;
  }

  obj->pCumSum = csum;
  for (i = 0; i < 599; i++) {
    obj->pCumSumRev[i] = localB->csumrev[i];
  }

  obj->pCumRevIndex = cumRevIndex;
  if (modValueRev > 0.0) {
    obj->pModValueRev = modValueRev - 1.0;
  } else {
    obj->pModValueRev = 0.0;
  }
}

/* Termination for atomic system: */
void INFLW_2_MovingAverage5_Term(DW_MovingAverage5_INFLW_2_T *localDW)
{
  g_dsp_internal_SlidingWindo_l_T *obj;

  /* Terminate for MATLABSystem: '<S6>/Moving Average5' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      obj = localDW->obj.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      localDW->obj.NumChannels = -1;
      localDW->obj.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S6>/Moving Average5' */
}

static void INFLW_2_SystemCore_setup_n2(dsp_simulink_MovingStandardDe_T *obj)
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

/* System initialize for atomic system: */
void I_MovingStandardDeviation1_Init(DW_MovingStandardDeviation1_I_T *localDW)
{
  g_dsp_internal_SlidingWindowV_T *obj;
  int32_T i;

  /* Start for MATLABSystem: '<S6>/Moving Standard Deviation1' */
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.FrameLength = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  INFLW_2_SystemCore_setup_n2(&localDW->obj);

  /* InitializeConditions for MATLABSystem: '<S6>/Moving Standard Deviation1' */
  obj = localDW->obj.pStatistic;
  if (obj->isInitialized == 1) {
    for (i = 0; i < 600; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 1.0;
    obj->pModValueRev = 0.0;
  }

  /* End of InitializeConditions for MATLABSystem: '<S6>/Moving Standard Deviation1' */
}

/* Output and update for atomic system: */
void INFLW__MovingStandardDeviation1(real_T rtu_0,
  B_MovingStandardDeviation1_IN_T *localB, DW_MovingStandardDeviation1_I_T
  *localDW)
{
  g_dsp_internal_SlidingWindowV_T *obj;
  real_T M;
  real_T Mprev;
  real_T S;
  real_T T;
  real_T counter;
  real_T modValueRev;
  real_T y;
  int32_T i;

  /* MATLABSystem: '<S6>/Moving Standard Deviation1' */
  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
  }

  obj = localDW->obj.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    for (i = 0; i < 600; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 0.0;
    obj->pModValueRev = 0.0;
    obj->isSetupComplete = true;
    for (i = 0; i < 600; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 1.0;
    obj->pModValueRev = 0.0;
  }

  for (i = 0; i < 600; i++) {
    localB->reverseSamples[i] = obj->pReverseSamples[i];
  }

  for (i = 0; i < 600; i++) {
    localB->x[i] = obj->pReverseT[i];
  }

  for (i = 0; i < 600; i++) {
    localB->reverseS[i] = obj->pReverseS[i];
  }

  T = obj->pT;
  S = obj->pS;
  M = obj->pM;
  counter = obj->pCounter;
  modValueRev = obj->pModValueRev;
  y = 0.0;
  T += rtu_0;
  Mprev = M;
  M += 1.0 / counter * (rtu_0 - M);
  Mprev = rtu_0 - Mprev;
  S += (counter - 1.0) * Mprev * Mprev / counter;
  if (modValueRev == 0.0) {
    y = (600.0 - counter) / counter * T - localB->x[(int32_T)(600.0 - counter) -
      1];
    y = (counter / (((600.0 - counter) + counter) * (600.0 - counter)) * (y * y)
         + (localB->reverseS[(int32_T)(600.0 - counter) - 1] + S)) / 599.0;
  }

  localB->reverseSamples[(int32_T)(600.0 - counter) - 1] = rtu_0;
  if (counter < 599.0) {
    counter++;
  } else {
    counter = 1.0;
    memcpy(&localB->x[0], &localB->reverseSamples[0], 600U * sizeof(real_T));
    T = 0.0;
    S = 0.0;
    for (i = 0; i < 599; i++) {
      M = localB->reverseSamples[i];
      localB->x[i + 1] += localB->x[i];
      Mprev = T;
      T += 1.0 / ((real_T)i + 1.0) * (M - T);
      M -= Mprev;
      S += (((real_T)i + 1.0) - 1.0) * M * M / ((real_T)i + 1.0);
      localB->reverseS[i] = S;
    }

    T = 0.0;
    S = 0.0;
    M = 0.0;
  }

  for (i = 0; i < 600; i++) {
    obj->pReverseSamples[i] = localB->reverseSamples[i];
  }

  for (i = 0; i < 600; i++) {
    obj->pReverseT[i] = localB->x[i];
  }

  for (i = 0; i < 600; i++) {
    obj->pReverseS[i] = localB->reverseS[i];
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

  /* MATLABSystem: '<S6>/Moving Standard Deviation1' */
  localB->MovingStandardDeviation1 = sqrt(y);
}

/* Termination for atomic system: */
void I_MovingStandardDeviation1_Term(DW_MovingStandardDeviation1_I_T *localDW)
{
  g_dsp_internal_SlidingWindowV_T *obj;

  /* Terminate for MATLABSystem: '<S6>/Moving Standard Deviation1' */
  if (!localDW->obj.matlabCodegenIsDeleted) {
    localDW->obj.matlabCodegenIsDeleted = true;
    if ((localDW->obj.isInitialized == 1) && localDW->obj.isSetupComplete) {
      obj = localDW->obj.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      localDW->obj.NumChannels = -1;
      localDW->obj.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S6>/Moving Standard Deviation1' */
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

static void INFLW_2_SystemCore_setup_meu(dsp_simulink_MovingStandardDe_T *obj)
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

static void INFLW_2_SystemCore_setup_me(dsp_simulink_MovingStandard_m_T *obj)
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

static void INFLW_2_SystemCore_setup_meus(dsp_simulink_MovingAverage_me_T *obj)
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

static void INFLW_2_SystemCore_setup_m(dsp_simulink_MovingAverage_m_T *obj)
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
void INFLW_2_step(void)
{
  /* local block i/o variables */
  real_T rtb_Mod;
  g_dsp_internal_SlidingWin_meu_T *obj_1;
  g_dsp_internal_SlidingWind_me_T *obj_0;
  g_dsp_internal_SlidingWindo_m_T *obj_2;
  g_dsp_internal_SlidingWindowV_T *obj;
  real_T csumrev[299];
  real_T M;
  real_T Mprev;
  real_T S;
  real_T T;
  real_T counter;
  real_T im;
  real_T modValueRev;
  real_T re;
  real_T y;
  real_T z_im;
  int32_T i;
  boolean_T rtb_Compare_b;
  boolean_T rtb_Compare_lf;
  boolean_T rtb_Compare_lw;
  boolean_T rtb_Compare_n;
  boolean_T rtb_Compare_o;
  boolean_T rtb_NOT1_a;
  boolean_T rtb_NOT1_b;
  boolean_T rtb_NOT1_m;
  boolean_T rtb_NOT1_n;

  /* Inport: '<Root>/input_WS_ms' */
  INFLW_2_MovingAverage5(INFLW_2_U.input_WS_ms, &INFLW_2_B.MovingAverage5_pn,
    &INFLW_2_DW.MovingAverage5_pn);

  /* MATLABSystem: '<S8>/Moving Standard Deviation1' incorporates:
   *  Inport: '<Root>/input_WS_ms'
   */
  if (INFLW_2_DW.obj_c.TunablePropsChanged) {
    INFLW_2_DW.obj_c.TunablePropsChanged = false;
  }

  obj = INFLW_2_DW.obj_c.pStatistic;
  if (obj->isInitialized != 1) {
    obj->isSetupComplete = false;
    obj->isInitialized = 1;
    for (i = 0; i < 600; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 0.0;
    obj->pModValueRev = 0.0;
    obj->isSetupComplete = true;
    for (i = 0; i < 600; i++) {
      obj->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 600; i++) {
      obj->pReverseS[i] = 0.0;
    }

    obj->pT = 0.0;
    obj->pS = 0.0;
    obj->pM = 0.0;
    obj->pCounter = 1.0;
    obj->pModValueRev = 0.0;
  }

  for (i = 0; i < 600; i++) {
    INFLW_2_B.reverseSamples_m[i] = obj->pReverseSamples[i];
  }

  for (i = 0; i < 600; i++) {
    INFLW_2_B.x_k[i] = obj->pReverseT[i];
  }

  for (i = 0; i < 600; i++) {
    INFLW_2_B.reverseS_c[i] = obj->pReverseS[i];
  }

  T = obj->pT;
  S = obj->pS;
  M = obj->pM;
  counter = obj->pCounter;
  modValueRev = obj->pModValueRev;
  y = 0.0;
  T += INFLW_2_U.input_WS_ms;
  Mprev = M;
  M += 1.0 / counter * (INFLW_2_U.input_WS_ms - M);
  Mprev = INFLW_2_U.input_WS_ms - Mprev;
  S += (counter - 1.0) * Mprev * Mprev / counter;
  if (modValueRev == 0.0) {
    y = (600.0 - counter) / counter * T - INFLW_2_B.x_k[(int32_T)(600.0 -
      counter) - 1];
    y = (counter / (((600.0 - counter) + counter) * (600.0 - counter)) * (y * y)
         + (INFLW_2_B.reverseS_c[(int32_T)(600.0 - counter) - 1] + S)) / 599.0;
  }

  INFLW_2_B.reverseSamples_m[(int32_T)(600.0 - counter) - 1] =
    INFLW_2_U.input_WS_ms;
  if (counter < 599.0) {
    counter++;
  } else {
    counter = 1.0;
    memcpy(&INFLW_2_B.x_k[0], &INFLW_2_B.reverseSamples_m[0], 600U * sizeof
           (real_T));
    T = 0.0;
    S = 0.0;
    for (i = 0; i < 599; i++) {
      M = INFLW_2_B.reverseSamples_m[i];
      INFLW_2_B.x_k[i + 1] += INFLW_2_B.x_k[i];
      Mprev = T;
      T += 1.0 / ((real_T)i + 1.0) * (M - T);
      M -= Mprev;
      S += (((real_T)i + 1.0) - 1.0) * M * M / ((real_T)i + 1.0);
      INFLW_2_B.reverseS_c[i] = S;
    }

    T = 0.0;
    S = 0.0;
    M = 0.0;
  }

  for (i = 0; i < 600; i++) {
    obj->pReverseSamples[i] = INFLW_2_B.reverseSamples_m[i];
  }

  for (i = 0; i < 600; i++) {
    obj->pReverseT[i] = INFLW_2_B.x_k[i];
  }

  for (i = 0; i < 600; i++) {
    obj->pReverseS[i] = INFLW_2_B.reverseS_c[i];
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

  counter = sqrt(y);

  /* End of MATLABSystem: '<S8>/Moving Standard Deviation1' */

  /* Sum: '<S8>/Sum' incorporates:
   *  Constant: '<S8>/One'
   *  Delay: '<S8>/Delay'
   */
  INFLW_2_DW.Delay_DSTATE++;

  /* Switch: '<S31>/Switch2' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Constant: '<S8>/Constant'
   *  Delay: '<S8>/Delay'
   *  RelationalOperator: '<S31>/LowerRelop1'
   *  RelationalOperator: '<S31>/UpperRelop'
   *  Switch: '<S31>/Switch'
   */
  if (INFLW_2_DW.Delay_DSTATE > 6000.0) {
    modValueRev = 6000.0;
  } else if (INFLW_2_DW.Delay_DSTATE < 0.0) {
    /* Switch: '<S31>/Switch' incorporates:
     *  Constant: '<S8>/Constant'
     */
    modValueRev = 0.0;
  } else {
    modValueRev = INFLW_2_DW.Delay_DSTATE;
  }

  /* Logic: '<S8>/Logical Operator' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Constant: '<S34>/Constant'
   *  Constant: '<S35>/Constant'
   *  Logic: '<S32>/Logical Operator'
   *  Logic: '<S33>/Logical Operator'
   *  RelationalOperator: '<S32>/IsInf'
   *  RelationalOperator: '<S32>/IsNaN'
   *  RelationalOperator: '<S33>/IsInf'
   *  RelationalOperator: '<S33>/IsNaN'
   *  RelationalOperator: '<S34>/Compare'
   *  RelationalOperator: '<S35>/Compare'
   *  RelationalOperator: '<S8>/GreaterThan'
   *  Switch: '<S31>/Switch2'
   */
  rtb_NOT1_b = ((INFLW_2_B.MovingAverage5_pn.MovingAverage5 <= 1.0E-5) ||
                rtIsNaN(INFLW_2_B.MovingAverage5_pn.MovingAverage5) || rtIsInf
                (INFLW_2_B.MovingAverage5_pn.MovingAverage5) || ((counter <=
    1.0E-5) || rtIsNaN(counter) || rtIsInf(counter)) || (modValueRev < 6000.0));

  /* RelationalOperator: '<S16>/Compare' incorporates:
   *  Logic: '<S3>/NOT'
   */
  rtb_Compare_o = !rtb_NOT1_b;

  /* Switch: '<S15>/Switch2' incorporates:
   *  UnitDelay: '<S15>/Unit Delay1'
   *  UnitDelay: '<S15>/Unit Delay2'
   */
  if (!(INFLW_2_DW.UnitDelay1_DSTATE != 0.0)) {
    INFLW_2_DW.UnitDelay2_DSTATE = rtb_Compare_o;
  }

  /* End of Switch: '<S15>/Switch2' */

  /* Logic: '<S3>/NOT1' incorporates:
   *  UnitDelay: '<S15>/Unit Delay2'
   */
  rtb_NOT1_n = !INFLW_2_DW.UnitDelay2_DSTATE;

  /* Math: '<Root>/Mod' incorporates:
   *  Constant: '<Root>/Constant'
   *  Inport: '<Root>/input_Dir_deg'
   */
  rtb_Mod = rt_modd_snf(INFLW_2_U.input_Dir_deg, 360.0);
  INFLW_2_MovingAverage5(rtb_Mod, &INFLW_2_B.MovingAverage5_p,
    &INFLW_2_DW.MovingAverage5_p);
  INFLW__MovingStandardDeviation1(rtb_Mod, &INFLW_2_B.MovingStandardDeviation1_p,
    &INFLW_2_DW.MovingStandardDeviation1_p);

  /* Sum: '<S7>/Sum' incorporates:
   *  Constant: '<S7>/One'
   *  Delay: '<S7>/Delay'
   */
  INFLW_2_DW.Delay_DSTATE_c++;

  /* Switch: '<S26>/Switch2' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Constant: '<S7>/Constant'
   *  Delay: '<S7>/Delay'
   *  RelationalOperator: '<S26>/LowerRelop1'
   *  RelationalOperator: '<S26>/UpperRelop'
   *  Switch: '<S26>/Switch'
   */
  if (INFLW_2_DW.Delay_DSTATE_c > 6000.0) {
    modValueRev = 6000.0;
  } else if (INFLW_2_DW.Delay_DSTATE_c < 0.0) {
    /* Switch: '<S26>/Switch' incorporates:
     *  Constant: '<S7>/Constant'
     */
    modValueRev = 0.0;
  } else {
    modValueRev = INFLW_2_DW.Delay_DSTATE_c;
  }

  /* RelationalOperator: '<S20>/Compare' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Constant: '<S29>/Constant'
   *  Constant: '<S30>/Constant'
   *  Logic: '<S27>/Logical Operator'
   *  Logic: '<S28>/Logical Operator'
   *  Logic: '<S5>/NOT'
   *  Logic: '<S7>/Logical Operator'
   *  RelationalOperator: '<S27>/IsInf'
   *  RelationalOperator: '<S27>/IsNaN'
   *  RelationalOperator: '<S28>/IsInf'
   *  RelationalOperator: '<S28>/IsNaN'
   *  RelationalOperator: '<S29>/Compare'
   *  RelationalOperator: '<S30>/Compare'
   *  RelationalOperator: '<S7>/GreaterThan'
   *  Switch: '<S26>/Switch2'
   */
  rtb_Compare_b = ((!(INFLW_2_B.MovingAverage5_p.MovingAverage5 <= 1.0E-5)) && (
    !rtIsNaN(INFLW_2_B.MovingAverage5_p.MovingAverage5)) && (!rtIsInf
    (INFLW_2_B.MovingAverage5_p.MovingAverage5)) &&
                   ((!(INFLW_2_B.MovingStandardDeviation1_p.MovingStandardDeviation1
                       <= 1.0E-5)) && (!rtIsNaN
    (INFLW_2_B.MovingStandardDeviation1_p.MovingStandardDeviation1)) &&
                    (!rtIsInf
                     (INFLW_2_B.MovingStandardDeviation1_p.MovingStandardDeviation1)))
                   && (!(modValueRev < 6000.0)));

  /* Switch: '<S19>/Switch2' incorporates:
   *  UnitDelay: '<S19>/Unit Delay1'
   *  UnitDelay: '<S19>/Unit Delay2'
   */
  if (!(INFLW_2_DW.UnitDelay1_DSTATE_n != 0.0)) {
    INFLW_2_DW.UnitDelay2_DSTATE_m = rtb_Compare_b;
  }

  /* End of Switch: '<S19>/Switch2' */

  /* Logic: '<S5>/NOT1' incorporates:
   *  UnitDelay: '<S19>/Unit Delay2'
   */
  rtb_NOT1_a = !INFLW_2_DW.UnitDelay2_DSTATE_m;

  /* RelationalOperator: '<S18>/Compare' incorporates:
   *  Logic: '<S4>/NOT'
   */
  rtb_Compare_lw = !rtb_NOT1_b;

  /* Switch: '<S17>/Switch2' incorporates:
   *  UnitDelay: '<S17>/Unit Delay1'
   *  UnitDelay: '<S17>/Unit Delay2'
   */
  if (!(INFLW_2_DW.UnitDelay1_DSTATE_n3 != 0.0)) {
    INFLW_2_DW.UnitDelay2_DSTATE_n = rtb_Compare_lw;
  }

  /* End of Switch: '<S17>/Switch2' */

  /* Logic: '<S4>/NOT1' incorporates:
   *  UnitDelay: '<S17>/Unit Delay2'
   */
  rtb_NOT1_m = !INFLW_2_DW.UnitDelay2_DSTATE_n;

  /* RelationalOperator: '<S13>/Compare' incorporates:
   *  Logic: '<S10>/NOT'
   */
  rtb_Compare_lf = !rtb_NOT1_b;

  /* Switch: '<S12>/Switch2' incorporates:
   *  UnitDelay: '<S12>/Unit Delay1'
   *  UnitDelay: '<S12>/Unit Delay2'
   */
  if (!(INFLW_2_DW.UnitDelay1_DSTATE_h != 0.0)) {
    INFLW_2_DW.UnitDelay2_DSTATE_f = rtb_Compare_lf;
  }

  /* End of Switch: '<S12>/Switch2' */

  /* Logic: '<S10>/NOT1' incorporates:
   *  UnitDelay: '<S12>/Unit Delay2'
   */
  rtb_NOT1_b = !INFLW_2_DW.UnitDelay2_DSTATE_f;

  /* Outport: '<Root>/output_InflowOK' incorporates:
   *  DataTypeConversion: '<Root>/Cast To Double'
   *  S-Function (scominttobit): '<Root>/Bit to Integer Converter1'
   *  SignalConversion generated from: '<Root>/Bit to Integer Converter1'
   */
  /* Bit to Integer Conversion */
  /* Input bit order is MSB first */
  INFLW_2_Y.output_InflowOK = (uint8_T)((((uint32_T)rtb_NOT1_n << 1U |
    rtb_NOT1_a) << 1U | rtb_NOT1_m) << 1U | rtb_NOT1_b);

  /* Inport: '<Root>/input_WS_54m' */
  INFLW_2_MovingAverage5(INFLW_2_U.input_WS_54m, &INFLW_2_B.MovingAverage5,
    &INFLW_2_DW.MovingAverage5);
  INFLW__MovingStandardDeviation1(INFLW_2_U.input_WS_54m,
    &INFLW_2_B.MovingStandardDeviation1, &INFLW_2_DW.MovingStandardDeviation1);

  /* Sum: '<S6>/Sum' incorporates:
   *  Constant: '<S6>/One'
   *  Delay: '<S6>/Delay'
   */
  INFLW_2_DW.Delay_DSTATE_p++;

  /* Switch: '<S21>/Switch2' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Constant: '<S6>/Constant'
   *  Delay: '<S6>/Delay'
   *  RelationalOperator: '<S21>/LowerRelop1'
   *  RelationalOperator: '<S21>/UpperRelop'
   *  Switch: '<S21>/Switch'
   */
  if (INFLW_2_DW.Delay_DSTATE_p > 6000.0) {
    modValueRev = 6000.0;
  } else if (INFLW_2_DW.Delay_DSTATE_p < 0.0) {
    /* Switch: '<S21>/Switch' incorporates:
     *  Constant: '<S6>/Constant'
     */
    modValueRev = 0.0;
  } else {
    modValueRev = INFLW_2_DW.Delay_DSTATE_p;
  }

  /* RelationalOperator: '<S14>/Compare' incorporates:
   *  Constant: '<Root>/Constant5'
   *  Constant: '<S24>/Constant'
   *  Constant: '<S25>/Constant'
   *  Logic: '<S22>/Logical Operator'
   *  Logic: '<S23>/Logical Operator'
   *  Logic: '<S2>/NOT'
   *  Logic: '<S6>/Logical Operator'
   *  RelationalOperator: '<S22>/IsInf'
   *  RelationalOperator: '<S22>/IsNaN'
   *  RelationalOperator: '<S23>/IsInf'
   *  RelationalOperator: '<S23>/IsNaN'
   *  RelationalOperator: '<S24>/Compare'
   *  RelationalOperator: '<S25>/Compare'
   *  RelationalOperator: '<S6>/GreaterThan'
   *  Switch: '<S21>/Switch2'
   */
  rtb_Compare_n = ((!(INFLW_2_B.MovingAverage5.MovingAverage5 <= 1.0E-5)) &&
                   (!rtIsNaN(INFLW_2_B.MovingAverage5.MovingAverage5)) &&
                   (!rtIsInf(INFLW_2_B.MovingAverage5.MovingAverage5)) &&
                   ((!(INFLW_2_B.MovingStandardDeviation1.MovingStandardDeviation1
                       <= 1.0E-5)) && (!rtIsNaN
    (INFLW_2_B.MovingStandardDeviation1.MovingStandardDeviation1)) && (!rtIsInf
    (INFLW_2_B.MovingStandardDeviation1.MovingStandardDeviation1))) &&
                   (!(modValueRev < 6000.0)));

  /* Switch: '<S11>/Switch2' incorporates:
   *  UnitDelay: '<S11>/Unit Delay1'
   *  UnitDelay: '<S11>/Unit Delay2'
   */
  if (!(INFLW_2_DW.UnitDelay1_DSTATE_i != 0.0)) {
    INFLW_2_DW.UnitDelay2_DSTATE_j = rtb_Compare_n;
  }

  /* End of Switch: '<S11>/Switch2' */

  /* Inport: '<Root>/input_WS_ms' */
  INFLW_2_MovingAverage2(INFLW_2_U.input_WS_ms, &INFLW_2_B.MovingAverage2,
    &INFLW_2_DW.MovingAverage2);

  /* Inport: '<Root>/input_WS_54m' */
  INFLW_2_MovingAverage2(INFLW_2_U.input_WS_54m, &INFLW_2_B.MovingAverage3,
    &INFLW_2_DW.MovingAverage3);

  /* Switch: '<S10>/Switch' incorporates:
   *  Logic: '<S2>/NOT1'
   *  Switch: '<S2>/Switch'
   *  UnitDelay: '<S11>/Unit Delay2'
   */
  if (rtb_NOT1_b) {
    /* Outport: '<Root>/output_ShearExp' incorporates:
     *  Constant: '<S2>/Constant'
     */
    INFLW_2_Y.output_ShearExp = 1.0;
  } else if (!INFLW_2_DW.UnitDelay2_DSTATE_j) {
    /* Switch: '<S2>/Switch' incorporates:
     *  Constant: '<Root>/Constant1'
     *  Outport: '<Root>/output_ShearExp'
     */
    INFLW_2_Y.output_ShearExp = 0.1;
  } else {
    /* Outport: '<Root>/output_ShearExp' incorporates:
     *  MATLAB Function: '<Root>/MATLAB Function'
     */
    INFLW_2_Y.output_ShearExp = (log(INFLW_2_B.MovingAverage2.MovingAverage2) -
      log(INFLW_2_B.MovingAverage3.MovingAverage2)) / 0.763492151079018;
  }

  /* End of Switch: '<S10>/Switch' */

  /* MATLABSystem: '<Root>/Moving Standard Deviation' incorporates:
   *  Inport: '<Root>/input_WS_ms'
   */
  if (INFLW_2_DW.obj.TunablePropsChanged) {
    INFLW_2_DW.obj.TunablePropsChanged = false;
  }

  obj_0 = INFLW_2_DW.obj.pStatistic;
  if (obj_0->isInitialized != 1) {
    obj_0->isSetupComplete = false;
    obj_0->isInitialized = 1;
    for (i = 0; i < 6000; i++) {
      obj_0->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 6000; i++) {
      obj_0->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 6000; i++) {
      obj_0->pReverseS[i] = 0.0;
    }

    obj_0->pT = 0.0;
    obj_0->pS = 0.0;
    obj_0->pM = 0.0;
    obj_0->pCounter = 0.0;
    obj_0->pModValueRev = 0.0;
    obj_0->isSetupComplete = true;
    for (i = 0; i < 6000; i++) {
      obj_0->pReverseSamples[i] = 0.0;
    }

    for (i = 0; i < 6000; i++) {
      obj_0->pReverseT[i] = 0.0;
    }

    for (i = 0; i < 6000; i++) {
      obj_0->pReverseS[i] = 0.0;
    }

    obj_0->pT = 0.0;
    obj_0->pS = 0.0;
    obj_0->pM = 0.0;
    obj_0->pCounter = 1.0;
    obj_0->pModValueRev = 0.0;
  }

  for (i = 0; i < 6000; i++) {
    INFLW_2_B.reverseSamples[i] = obj_0->pReverseSamples[i];
  }

  for (i = 0; i < 6000; i++) {
    INFLW_2_B.x[i] = obj_0->pReverseT[i];
  }

  for (i = 0; i < 6000; i++) {
    INFLW_2_B.reverseS[i] = obj_0->pReverseS[i];
  }

  T = obj_0->pT;
  S = obj_0->pS;
  M = obj_0->pM;
  counter = obj_0->pCounter;
  modValueRev = obj_0->pModValueRev;
  y = 0.0;
  T += INFLW_2_U.input_WS_ms;
  Mprev = M;
  M += 1.0 / counter * (INFLW_2_U.input_WS_ms - M);
  Mprev = INFLW_2_U.input_WS_ms - Mprev;
  S += (counter - 1.0) * Mprev * Mprev / counter;
  if (modValueRev == 0.0) {
    y = (6000.0 - counter) / counter * T - INFLW_2_B.x[(int32_T)(6000.0 -
      counter) - 1];
    y = (counter / (((6000.0 - counter) + counter) * (6000.0 - counter)) * (y *
          y) + (INFLW_2_B.reverseS[(int32_T)(6000.0 - counter) - 1] + S)) /
      5999.0;
  }

  INFLW_2_B.reverseSamples[(int32_T)(6000.0 - counter) - 1] =
    INFLW_2_U.input_WS_ms;
  if (counter < 5999.0) {
    counter++;
  } else {
    counter = 1.0;
    memcpy(&INFLW_2_B.x[0], &INFLW_2_B.reverseSamples[0], 6000U * sizeof(real_T));
    T = 0.0;
    S = 0.0;
    for (i = 0; i < 5999; i++) {
      M = INFLW_2_B.reverseSamples[i];
      INFLW_2_B.x[i + 1] += INFLW_2_B.x[i];
      Mprev = T;
      T += 1.0 / ((real_T)i + 1.0) * (M - T);
      M -= Mprev;
      S += (((real_T)i + 1.0) - 1.0) * M * M / ((real_T)i + 1.0);
      INFLW_2_B.reverseS[i] = S;
    }

    T = 0.0;
    S = 0.0;
    M = 0.0;
  }

  for (i = 0; i < 6000; i++) {
    obj_0->pReverseSamples[i] = INFLW_2_B.reverseSamples[i];
  }

  for (i = 0; i < 6000; i++) {
    obj_0->pReverseT[i] = INFLW_2_B.x[i];
  }

  for (i = 0; i < 6000; i++) {
    obj_0->pReverseS[i] = INFLW_2_B.reverseS[i];
  }

  obj_0->pT = T;
  obj_0->pS = S;
  obj_0->pM = M;
  obj_0->pCounter = counter;
  if (modValueRev > 0.0) {
    obj_0->pModValueRev = modValueRev - 1.0;
  } else {
    obj_0->pModValueRev = 0.0;
  }

  /* Switch: '<S4>/Switch' */
  if (rtb_NOT1_m) {
    /* Outport: '<Root>/output_TI' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    INFLW_2_Y.output_TI = 1.0;
  } else {
    /* Outport: '<Root>/output_TI' incorporates:
     *  MATLABSystem: '<Root>/Moving Standard Deviation'
     *  Product: '<Root>/Divide'
     */
    INFLW_2_Y.output_TI = sqrt(y) / INFLW_2_B.MovingAverage2.MovingAverage2;
  }

  /* End of Switch: '<S4>/Switch' */

  /* Switch: '<S11>/Switch1' incorporates:
   *  Logic: '<S11>/Logical Operator'
   *  Sum: '<S11>/Sum'
   *  UnitDelay: '<S11>/Unit Delay3'
   */
  if ((boolean_T)(rtb_Compare_n ^ INFLW_2_DW.UnitDelay3_DSTATE)) {
    /* Switch: '<S11>/Switch3' incorporates:
     *  Constant: '<S11>/Constant'
     *  Constant: '<S11>/ForceOutput'
     *  Logic: '<S11>/Logical Operator1'
     *  Logic: '<S11>/Logical Operator2'
     */
    if ((!rtb_Compare_n) && INFLW_2_DW.UnitDelay3_DSTATE) {
      INFLW_2_DW.UnitDelay1_DSTATE_i = 1.0;
    } else {
      INFLW_2_DW.UnitDelay1_DSTATE_i = 10000.0;
    }

    /* End of Switch: '<S11>/Switch3' */
  }

  INFLW_2_DW.UnitDelay1_DSTATE_i--;

  /* End of Switch: '<S11>/Switch1' */

  /* Switch: '<S12>/Switch1' incorporates:
   *  Logic: '<S12>/Logical Operator'
   *  Sum: '<S12>/Sum'
   *  UnitDelay: '<S12>/Unit Delay3'
   */
  if ((boolean_T)(rtb_Compare_lf ^ INFLW_2_DW.UnitDelay3_DSTATE_p)) {
    /* Switch: '<S12>/Switch3' incorporates:
     *  Constant: '<S12>/Constant'
     *  Constant: '<S12>/ForceOutput'
     *  Logic: '<S12>/Logical Operator1'
     *  Logic: '<S12>/Logical Operator2'
     */
    if ((!rtb_Compare_lf) && INFLW_2_DW.UnitDelay3_DSTATE_p) {
      INFLW_2_DW.UnitDelay1_DSTATE_h = 1.0;
    } else {
      INFLW_2_DW.UnitDelay1_DSTATE_h = 10000.0;
    }

    /* End of Switch: '<S12>/Switch3' */
  }

  INFLW_2_DW.UnitDelay1_DSTATE_h--;

  /* End of Switch: '<S12>/Switch1' */

  /* Switch: '<S17>/Switch1' incorporates:
   *  Logic: '<S17>/Logical Operator'
   *  Sum: '<S17>/Sum'
   *  UnitDelay: '<S17>/Unit Delay3'
   */
  if ((boolean_T)(rtb_Compare_lw ^ INFLW_2_DW.UnitDelay3_DSTATE_pl)) {
    /* Switch: '<S17>/Switch3' incorporates:
     *  Constant: '<S17>/Constant'
     *  Constant: '<S17>/ForceOutput'
     *  Logic: '<S17>/Logical Operator1'
     *  Logic: '<S17>/Logical Operator2'
     */
    if ((!rtb_Compare_lw) && INFLW_2_DW.UnitDelay3_DSTATE_pl) {
      INFLW_2_DW.UnitDelay1_DSTATE_n3 = 1.0;
    } else {
      INFLW_2_DW.UnitDelay1_DSTATE_n3 = 10000.0;
    }

    /* End of Switch: '<S17>/Switch3' */
  }

  INFLW_2_DW.UnitDelay1_DSTATE_n3--;

  /* End of Switch: '<S17>/Switch1' */

  /* Gain: '<S9>/Gain' */
  modValueRev = 0.017453292519943295 * rtb_Mod;

  /* MagnitudeAngleToComplex: '<S9>/Magnitude-Angle to Complex' */
  y = cos(modValueRev);
  T = sin(modValueRev);

  /* MATLABSystem: '<S9>/Moving Average1' incorporates:
   *  MagnitudeAngleToComplex: '<S9>/Magnitude-Angle to Complex'
   */
  if (INFLW_2_DW.obj_p.TunablePropsChanged) {
    INFLW_2_DW.obj_p.TunablePropsChanged = false;
  }

  obj_1 = INFLW_2_DW.obj_p.pStatistic;
  if (obj_1->isInitialized != 1) {
    obj_1->isSetupComplete = false;
    obj_1->isInitialized = 1;
    obj_1->pCumSum.re = 0.0;
    obj_1->pCumSum.im = 0.0;
    for (i = 0; i < 999; i++) {
      obj_1->pCumSumRev[i].re = 0.0;
      obj_1->pCumSumRev[i].im = 0.0;
    }

    obj_1->pCumRevIndex = 1.0;
    obj_1->pModValueRev = 0.0;
    obj_1->isSetupComplete = true;
    obj_1->pCumSum.re = 0.0;
    obj_1->pCumSum.im = 0.0;
    for (i = 0; i < 999; i++) {
      obj_1->pCumSumRev[i].re = 0.0;
      obj_1->pCumSumRev[i].im = 0.0;
    }

    obj_1->pCumRevIndex = 1.0;
    obj_1->pModValueRev = 0.0;
  }

  counter = obj_1->pCumRevIndex;
  S = obj_1->pCumSum.re;
  M = obj_1->pCumSum.im;
  for (i = 0; i < 999; i++) {
    INFLW_2_B.csumrev[i] = obj_1->pCumSumRev[i];
  }

  modValueRev = obj_1->pModValueRev;
  Mprev = 0.0;
  z_im = 0.0;
  re = 0.0;
  im = 0.0;
  S += y;
  M += T;
  if (modValueRev == 0.0) {
    Mprev = INFLW_2_B.csumrev[(int32_T)counter - 1].re + S;
    z_im = INFLW_2_B.csumrev[(int32_T)counter - 1].im + M;
  }

  INFLW_2_B.csumrev[(int32_T)counter - 1].re = y;
  INFLW_2_B.csumrev[(int32_T)counter - 1].im = T;
  if (counter != 999.0) {
    counter++;
  } else {
    counter = 1.0;
    S = 0.0;
    M = 0.0;
    for (i = 997; i >= 0; i--) {
      INFLW_2_B.csumrev[i].re += INFLW_2_B.csumrev[i + 1].re;
      INFLW_2_B.csumrev[i].im += INFLW_2_B.csumrev[i + 1].im;
    }
  }

  if (modValueRev == 0.0) {
    if (z_im == 0.0) {
      re = Mprev / 1000.0;
    } else if (Mprev == 0.0) {
      im = z_im / 1000.0;
    } else {
      re = Mprev / 1000.0;
      im = z_im / 1000.0;
    }
  }

  obj_1->pCumSum.re = S;
  obj_1->pCumSum.im = M;
  for (i = 0; i < 999; i++) {
    obj_1->pCumSumRev[i] = INFLW_2_B.csumrev[i];
  }

  obj_1->pCumRevIndex = counter;
  if (modValueRev > 0.0) {
    obj_1->pModValueRev = modValueRev - 1.0;
  } else {
    obj_1->pModValueRev = 0.0;
  }

  /* Switch: '<S5>/Switch' */
  if (rtb_NOT1_a) {
    /* Outport: '<Root>/output_WDir' incorporates:
     *  Constant: '<Root>/Constant4'
     */
    INFLW_2_Y.output_WDir = 1000.0;
  } else {
    /* Outport: '<Root>/output_WDir' incorporates:
     *  ComplexToMagnitudeAngle: '<S9>/Complex to Magnitude-Angle'
     *  Constant: '<S9>/One1'
     *  Gain: '<S9>/Gain1'
     *  MATLABSystem: '<S9>/Moving Average1'
     *  Math: '<S9>/Mod'
     */
    INFLW_2_Y.output_WDir = rt_modd_snf(57.295779513082323 * rt_atan2d_snf(im,
      re), 360.0);
  }

  /* End of Switch: '<S5>/Switch' */

  /* Switch: '<S19>/Switch1' incorporates:
   *  Logic: '<S19>/Logical Operator'
   *  Sum: '<S19>/Sum'
   *  UnitDelay: '<S19>/Unit Delay3'
   */
  if ((boolean_T)(rtb_Compare_b ^ INFLW_2_DW.UnitDelay3_DSTATE_a)) {
    /* Switch: '<S19>/Switch3' incorporates:
     *  Constant: '<S19>/Constant'
     *  Constant: '<S19>/ForceOutput'
     *  Logic: '<S19>/Logical Operator1'
     *  Logic: '<S19>/Logical Operator2'
     */
    if ((!rtb_Compare_b) && INFLW_2_DW.UnitDelay3_DSTATE_a) {
      INFLW_2_DW.UnitDelay1_DSTATE_n = 1.0;
    } else {
      INFLW_2_DW.UnitDelay1_DSTATE_n = 10000.0;
    }

    /* End of Switch: '<S19>/Switch3' */
  }

  INFLW_2_DW.UnitDelay1_DSTATE_n--;

  /* End of Switch: '<S19>/Switch1' */

  /* MATLABSystem: '<Root>/Moving Average' incorporates:
   *  Inport: '<Root>/input_WS_ms'
   */
  if (INFLW_2_DW.obj_k.TunablePropsChanged) {
    INFLW_2_DW.obj_k.TunablePropsChanged = false;
  }

  obj_2 = INFLW_2_DW.obj_k.pStatistic;
  if (obj_2->isInitialized != 1) {
    obj_2->isSetupComplete = false;
    obj_2->isInitialized = 1;
    obj_2->pCumSum = 0.0;
    for (i = 0; i < 299; i++) {
      obj_2->pCumSumRev[i] = 0.0;
    }

    obj_2->pCumRevIndex = 1.0;
    obj_2->pModValueRev = 0.0;
    obj_2->isSetupComplete = true;
    obj_2->pCumSum = 0.0;
    for (i = 0; i < 299; i++) {
      obj_2->pCumSumRev[i] = 0.0;
    }

    obj_2->pCumRevIndex = 1.0;
    obj_2->pModValueRev = 0.0;
  }

  counter = obj_2->pCumRevIndex;
  y = obj_2->pCumSum;
  for (i = 0; i < 299; i++) {
    csumrev[i] = obj_2->pCumSumRev[i];
  }

  modValueRev = obj_2->pModValueRev;
  T = 0.0;
  INFLW_2_Y.output_WS = 0.0;
  y += INFLW_2_U.input_WS_ms;
  if (modValueRev == 0.0) {
    T = csumrev[(int32_T)counter - 1] + y;
  }

  csumrev[(int32_T)counter - 1] = INFLW_2_U.input_WS_ms;
  if (counter != 299.0) {
    counter++;
  } else {
    counter = 1.0;
    y = 0.0;
    for (i = 297; i >= 0; i--) {
      csumrev[i] += csumrev[i + 1];
    }
  }

  if (modValueRev == 0.0) {
    INFLW_2_Y.output_WS = T / 300.0;
  }

  obj_2->pCumSum = y;
  for (i = 0; i < 299; i++) {
    obj_2->pCumSumRev[i] = csumrev[i];
  }

  obj_2->pCumRevIndex = counter;
  if (modValueRev > 0.0) {
    obj_2->pModValueRev = modValueRev - 1.0;
  } else {
    obj_2->pModValueRev = 0.0;
  }

  /* Switch: '<S3>/Switch' */
  if (rtb_NOT1_n) {
    /* MATLABSystem: '<Root>/Moving Average' incorporates:
     *  Constant: '<Root>/Constant2'
     *  Outport: '<Root>/output_WS'
     */
    INFLW_2_Y.output_WS = 0.0;
  }

  /* End of Switch: '<S3>/Switch' */

  /* Switch: '<S15>/Switch1' incorporates:
   *  Logic: '<S15>/Logical Operator'
   *  Sum: '<S15>/Sum'
   *  UnitDelay: '<S15>/Unit Delay3'
   */
  if ((boolean_T)(rtb_Compare_o ^ INFLW_2_DW.UnitDelay3_DSTATE_f)) {
    /* Switch: '<S15>/Switch3' incorporates:
     *  Constant: '<S15>/Constant'
     *  Constant: '<S15>/ForceOutput'
     *  Logic: '<S15>/Logical Operator1'
     *  Logic: '<S15>/Logical Operator2'
     */
    if ((!rtb_Compare_o) && INFLW_2_DW.UnitDelay3_DSTATE_f) {
      INFLW_2_DW.UnitDelay1_DSTATE = 1.0;
    } else {
      INFLW_2_DW.UnitDelay1_DSTATE = 10000.0;
    }

    /* End of Switch: '<S15>/Switch3' */
  }

  INFLW_2_DW.UnitDelay1_DSTATE--;

  /* End of Switch: '<S15>/Switch1' */

  /* Update for UnitDelay: '<S11>/Unit Delay3' */
  INFLW_2_DW.UnitDelay3_DSTATE = rtb_Compare_n;

  /* Update for UnitDelay: '<S12>/Unit Delay3' */
  INFLW_2_DW.UnitDelay3_DSTATE_p = rtb_Compare_lf;

  /* Update for UnitDelay: '<S17>/Unit Delay3' */
  INFLW_2_DW.UnitDelay3_DSTATE_pl = rtb_Compare_lw;

  /* Update for UnitDelay: '<S19>/Unit Delay3' */
  INFLW_2_DW.UnitDelay3_DSTATE_a = rtb_Compare_b;

  /* Update for UnitDelay: '<S15>/Unit Delay3' */
  INFLW_2_DW.UnitDelay3_DSTATE_f = rtb_Compare_o;
}

/* Model initialize function */
void INFLW_2_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(INFLW_2_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &INFLW_2_B), 0,
                sizeof(B_INFLW_2_T));

  /* states (dwork) */
  (void) memset((void *)&INFLW_2_DW, 0,
                sizeof(DW_INFLW_2_T));

  /* external inputs */
  (void)memset(&INFLW_2_U, 0, sizeof(ExtU_INFLW_2_T));

  /* external outputs */
  (void)memset(&INFLW_2_Y, 0, sizeof(ExtY_INFLW_2_T));

  {
    g_dsp_internal_SlidingWin_meu_T *obj_1;
    g_dsp_internal_SlidingWind_me_T *obj_0;
    g_dsp_internal_SlidingWindo_m_T *obj_2;
    g_dsp_internal_SlidingWindowV_T *obj;
    int32_T i;

    /* SystemInitialize for Inport: '<Root>/input_WS_ms' */
    INFLW_2_MovingAverage5_Init(&INFLW_2_DW.MovingAverage5_pn);

    /* Start for MATLABSystem: '<S8>/Moving Standard Deviation1' */
    INFLW_2_DW.obj_c.isInitialized = 0;
    INFLW_2_DW.obj_c.NumChannels = -1;
    INFLW_2_DW.obj_c.FrameLength = -1;
    INFLW_2_DW.obj_c.matlabCodegenIsDeleted = false;
    INFLW_2_SystemCore_setup_meu(&INFLW_2_DW.obj_c);

    /* InitializeConditions for MATLABSystem: '<S8>/Moving Standard Deviation1' */
    obj = INFLW_2_DW.obj_c.pStatistic;
    if (obj->isInitialized == 1) {
      for (i = 0; i < 600; i++) {
        obj->pReverseSamples[i] = 0.0;
      }

      for (i = 0; i < 600; i++) {
        obj->pReverseT[i] = 0.0;
      }

      for (i = 0; i < 600; i++) {
        obj->pReverseS[i] = 0.0;
      }

      obj->pT = 0.0;
      obj->pS = 0.0;
      obj->pM = 0.0;
      obj->pCounter = 1.0;
      obj->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<S8>/Moving Standard Deviation1' */
    INFLW_2_MovingAverage5_Init(&INFLW_2_DW.MovingAverage5_p);
    I_MovingStandardDeviation1_Init(&INFLW_2_DW.MovingStandardDeviation1_p);

    /* SystemInitialize for Inport: '<Root>/input_WS_54m' */
    INFLW_2_MovingAverage5_Init(&INFLW_2_DW.MovingAverage5);
    I_MovingStandardDeviation1_Init(&INFLW_2_DW.MovingStandardDeviation1);

    /* SystemInitialize for Inport: '<Root>/input_WS_ms' */
    INFLW_2_MovingAverage2_Init(&INFLW_2_DW.MovingAverage2);

    /* SystemInitialize for Inport: '<Root>/input_WS_54m' */
    INFLW_2_MovingAverage2_Init(&INFLW_2_DW.MovingAverage3);

    /* Start for MATLABSystem: '<Root>/Moving Standard Deviation' */
    INFLW_2_DW.obj.isInitialized = 0;
    INFLW_2_DW.obj.NumChannels = -1;
    INFLW_2_DW.obj.FrameLength = -1;
    INFLW_2_DW.obj.matlabCodegenIsDeleted = false;
    INFLW_2_SystemCore_setup_me(&INFLW_2_DW.obj);

    /* InitializeConditions for MATLABSystem: '<Root>/Moving Standard Deviation' */
    obj_0 = INFLW_2_DW.obj.pStatistic;
    if (obj_0->isInitialized == 1) {
      for (i = 0; i < 6000; i++) {
        obj_0->pReverseSamples[i] = 0.0;
      }

      for (i = 0; i < 6000; i++) {
        obj_0->pReverseT[i] = 0.0;
      }

      for (i = 0; i < 6000; i++) {
        obj_0->pReverseS[i] = 0.0;
      }

      obj_0->pT = 0.0;
      obj_0->pS = 0.0;
      obj_0->pM = 0.0;
      obj_0->pCounter = 1.0;
      obj_0->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/Moving Standard Deviation' */

    /* Start for MATLABSystem: '<S9>/Moving Average1' */
    INFLW_2_DW.obj_p.isInitialized = 0;
    INFLW_2_DW.obj_p.NumChannels = -1;
    INFLW_2_DW.obj_p.FrameLength = -1;
    INFLW_2_DW.obj_p.matlabCodegenIsDeleted = false;
    INFLW_2_SystemCore_setup_meus(&INFLW_2_DW.obj_p);

    /* InitializeConditions for MATLABSystem: '<S9>/Moving Average1' */
    obj_1 = INFLW_2_DW.obj_p.pStatistic;
    if (obj_1->isInitialized == 1) {
      obj_1->pCumSum.re = 0.0;
      obj_1->pCumSum.im = 0.0;
      for (i = 0; i < 999; i++) {
        obj_1->pCumSumRev[i].re = 0.0;
        obj_1->pCumSumRev[i].im = 0.0;
      }

      obj_1->pCumRevIndex = 1.0;
      obj_1->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<S9>/Moving Average1' */

    /* Start for MATLABSystem: '<Root>/Moving Average' */
    INFLW_2_DW.obj_k.isInitialized = 0;
    INFLW_2_DW.obj_k.NumChannels = -1;
    INFLW_2_DW.obj_k.FrameLength = -1;
    INFLW_2_DW.obj_k.matlabCodegenIsDeleted = false;
    INFLW_2_SystemCore_setup_m(&INFLW_2_DW.obj_k);

    /* InitializeConditions for MATLABSystem: '<Root>/Moving Average' */
    obj_2 = INFLW_2_DW.obj_k.pStatistic;
    if (obj_2->isInitialized == 1) {
      obj_2->pCumSum = 0.0;
      for (i = 0; i < 299; i++) {
        obj_2->pCumSumRev[i] = 0.0;
      }

      obj_2->pCumRevIndex = 1.0;
      obj_2->pModValueRev = 0.0;
    }

    /* End of InitializeConditions for MATLABSystem: '<Root>/Moving Average' */
  }
}

/* Model terminate function */
void INFLW_2_terminate(void)
{
  g_dsp_internal_SlidingWin_meu_T *obj_1;
  g_dsp_internal_SlidingWind_me_T *obj_0;
  g_dsp_internal_SlidingWindo_m_T *obj_2;
  g_dsp_internal_SlidingWindowV_T *obj;
  INFLW_2_MovingAverage5_Term(&INFLW_2_DW.MovingAverage5_pn);

  /* Terminate for MATLABSystem: '<S8>/Moving Standard Deviation1' */
  if (!INFLW_2_DW.obj_c.matlabCodegenIsDeleted) {
    INFLW_2_DW.obj_c.matlabCodegenIsDeleted = true;
    if ((INFLW_2_DW.obj_c.isInitialized == 1) &&
        INFLW_2_DW.obj_c.isSetupComplete) {
      obj = INFLW_2_DW.obj_c.pStatistic;
      if (obj->isInitialized == 1) {
        obj->isInitialized = 2;
      }

      INFLW_2_DW.obj_c.NumChannels = -1;
      INFLW_2_DW.obj_c.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S8>/Moving Standard Deviation1' */
  INFLW_2_MovingAverage5_Term(&INFLW_2_DW.MovingAverage5_p);
  I_MovingStandardDeviation1_Term(&INFLW_2_DW.MovingStandardDeviation1_p);
  INFLW_2_MovingAverage5_Term(&INFLW_2_DW.MovingAverage5);
  I_MovingStandardDeviation1_Term(&INFLW_2_DW.MovingStandardDeviation1);
  INFLW_2_MovingAverage2_Term(&INFLW_2_DW.MovingAverage2);
  INFLW_2_MovingAverage2_Term(&INFLW_2_DW.MovingAverage3);

  /* Terminate for MATLABSystem: '<Root>/Moving Standard Deviation' */
  if (!INFLW_2_DW.obj.matlabCodegenIsDeleted) {
    INFLW_2_DW.obj.matlabCodegenIsDeleted = true;
    if ((INFLW_2_DW.obj.isInitialized == 1) && INFLW_2_DW.obj.isSetupComplete) {
      obj_0 = INFLW_2_DW.obj.pStatistic;
      if (obj_0->isInitialized == 1) {
        obj_0->isInitialized = 2;
      }

      INFLW_2_DW.obj.NumChannels = -1;
      INFLW_2_DW.obj.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Moving Standard Deviation' */

  /* Terminate for MATLABSystem: '<S9>/Moving Average1' */
  if (!INFLW_2_DW.obj_p.matlabCodegenIsDeleted) {
    INFLW_2_DW.obj_p.matlabCodegenIsDeleted = true;
    if ((INFLW_2_DW.obj_p.isInitialized == 1) &&
        INFLW_2_DW.obj_p.isSetupComplete) {
      obj_1 = INFLW_2_DW.obj_p.pStatistic;
      if (obj_1->isInitialized == 1) {
        obj_1->isInitialized = 2;
      }

      INFLW_2_DW.obj_p.NumChannels = -1;
      INFLW_2_DW.obj_p.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<S9>/Moving Average1' */

  /* Terminate for MATLABSystem: '<Root>/Moving Average' */
  if (!INFLW_2_DW.obj_k.matlabCodegenIsDeleted) {
    INFLW_2_DW.obj_k.matlabCodegenIsDeleted = true;
    if ((INFLW_2_DW.obj_k.isInitialized == 1) &&
        INFLW_2_DW.obj_k.isSetupComplete) {
      obj_2 = INFLW_2_DW.obj_k.pStatistic;
      if (obj_2->isInitialized == 1) {
        obj_2->isInitialized = 2;
      }

      INFLW_2_DW.obj_k.NumChannels = -1;
      INFLW_2_DW.obj_k.FrameLength = -1;
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Moving Average' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
