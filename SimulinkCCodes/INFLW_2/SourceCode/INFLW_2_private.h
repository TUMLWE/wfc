/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: INFLW_2_private.h
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

#ifndef RTW_HEADER_INFLW_2_private_h_
#define RTW_HEADER_INFLW_2_private_h_
#include "rtwtypes.h"
#include "INFLW_2.h"
#include "INFLW_2_types.h"

extern real_T rt_modd_snf(real_T u0, real_T u1);
extern real_T rt_atan2d_snf(real_T u0, real_T u1);
extern void INFLW_2_MovingAverage2_Init(DW_MovingAverage2_INFLW_2_T *localDW);
extern void INFLW_2_MovingAverage2(real_T rtu_0, B_MovingAverage2_INFLW_2_T
  *localB, DW_MovingAverage2_INFLW_2_T *localDW);
extern void INFLW_2_MovingAverage5_Init(DW_MovingAverage5_INFLW_2_T *localDW);
extern void INFLW_2_MovingAverage5(real_T rtu_0, B_MovingAverage5_INFLW_2_T
  *localB, DW_MovingAverage5_INFLW_2_T *localDW);
extern void I_MovingStandardDeviation1_Init(DW_MovingStandardDeviation1_I_T
  *localDW);
extern void INFLW__MovingStandardDeviation1(real_T rtu_0,
  B_MovingStandardDeviation1_IN_T *localB, DW_MovingStandardDeviation1_I_T
  *localDW);
extern void INFLW_2_MovingAverage2_Term(DW_MovingAverage2_INFLW_2_T *localDW);
extern void INFLW_2_MovingAverage5_Term(DW_MovingAverage5_INFLW_2_T *localDW);
extern void I_MovingStandardDeviation1_Term(DW_MovingStandardDeviation1_I_T
  *localDW);

#endif                                 /* RTW_HEADER_INFLW_2_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
