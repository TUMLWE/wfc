/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OFFSET_1_private.h
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

#ifndef RTW_HEADER_OFFSET_1_private_h_
#define RTW_HEADER_OFFSET_1_private_h_
#include "rtwtypes.h"
#include "OFFSET_1_types.h"
#include "OFFSET_1.h"

extern uint32_T plook_binca(real_T u, const real_T bp[], uint32_T maxIndex,
  real_T *fraction);
extern real_T intrp4d_la_pw(const uint32_T bpIndex[], const real_T frac[], const
  real_T table[], const uint32_T stride[], const uint32_T maxIndex[]);
extern uint32_T binsearch_u32d(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex);

#endif                                 /* RTW_HEADER_OFFSET_1_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
