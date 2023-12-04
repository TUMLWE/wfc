/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TOGGLER_private.h
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

#ifndef RTW_HEADER_TOGGLER_private_h_
#define RTW_HEADER_TOGGLER_private_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "TOGGLER_types.h"
#include "TOGGLER.h"

extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern real_T rt_modd_snf(real_T u0, real_T u1);
extern void TOGGLER_Setoffsettozero(real_T *rty_Out1);
extern void TOGGLER_MATLABFunction(const boolean_T rtu_CTRLToStopVec[4], const
  real_T rtu_CTRLList[4], real_T *rty_CTRLToSkip, real_T *rty_iL);
extern void TOGGLER_MATLABFunction1(real_T rty_y[4]);
extern void TOGGLER_MATLABFunction2(real_T rtu_u1, const real_T rtu_u2[4],
  real_T rtu_u3, real_T rty_y[4]);
extern void TOGGLER_MATLABFunction3(const real_T rtu_u1[4], real_T rtu_u2,
  real_T *rty_y);

#endif                                 /* RTW_HEADER_TOGGLER_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
