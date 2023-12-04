/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TOGGLER_types.h
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

#ifndef RTW_HEADER_TOGGLER_types_h_
#define RTW_HEADER_TOGGLER_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_CTRLSector_Bus_
#define DEFINED_TYPEDEF_FOR_CTRLSector_Bus_

typedef struct {
  real_T SectorLabel[2];
  real_T WakeSteering_WSRange[4];
  real_T WakeSteering_WDirRange[4];
  real_T NacOrientationIsOK[4];
  real_T MisalignmentLimit[2];
  real_T Sect1_WFCStrategiesLabel[3];
  real_T Sect2_WFCStrategiesLabel;
} CTRLSector_Bus;

#endif

#ifndef struct_tag_QIw1dc1REk6fgXjfuao6bC
#define struct_tag_QIw1dc1REk6fgXjfuao6bC

struct tag_QIw1dc1REk6fgXjfuao6bC
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T pReverseSamples[100];
  real_T pReverseT[100];
  real_T pReverseS[100];
  real_T pT;
  real_T pS;
  real_T pM;
  real_T pCounter;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_QIw1dc1REk6fgXjfuao6bC */

#ifndef typedef_g_dsp_internal_SlidingWindowV_T
#define typedef_g_dsp_internal_SlidingWindowV_T

typedef struct tag_QIw1dc1REk6fgXjfuao6bC g_dsp_internal_SlidingWindowV_T;

#endif                             /* typedef_g_dsp_internal_SlidingWindowV_T */

#ifndef struct_tag_ecGlYU5M2GXxUVZuTSH6kD
#define struct_tag_ecGlYU5M2GXxUVZuTSH6kD

struct tag_ecGlYU5M2GXxUVZuTSH6kD
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T pCumSum;
  real_T pCumSumRev[5999];
  real_T pCumRevIndex;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_ecGlYU5M2GXxUVZuTSH6kD */

#ifndef typedef_g_dsp_internal_SlidingWindowA_T
#define typedef_g_dsp_internal_SlidingWindowA_T

typedef struct tag_ecGlYU5M2GXxUVZuTSH6kD g_dsp_internal_SlidingWindowA_T;

#endif                             /* typedef_g_dsp_internal_SlidingWindowA_T */

#ifndef struct_tag_BlgwLpgj2bjudmbmVKWwDE
#define struct_tag_BlgwLpgj2bjudmbmVKWwDE

struct tag_BlgwLpgj2bjudmbmVKWwDE
{
  uint32_T f1[8];
};

#endif                                 /* struct_tag_BlgwLpgj2bjudmbmVKWwDE */

#ifndef typedef_cell_wrap_TOGGLER_T
#define typedef_cell_wrap_TOGGLER_T

typedef struct tag_BlgwLpgj2bjudmbmVKWwDE cell_wrap_TOGGLER_T;

#endif                                 /* typedef_cell_wrap_TOGGLER_T */

#ifndef struct_tag_oSVjVMPVsBT3vlK4u4l7uB
#define struct_tag_oSVjVMPVsBT3vlK4u4l7uB

struct tag_oSVjVMPVsBT3vlK4u4l7uB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_TOGGLER_T inputVarSize;
  g_dsp_internal_SlidingWindowV_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWindowV_T _pobj0;
};

#endif                                 /* struct_tag_oSVjVMPVsBT3vlK4u4l7uB */

#ifndef typedef_dsp_simulink_MovingStandardDe_T
#define typedef_dsp_simulink_MovingStandardDe_T

typedef struct tag_oSVjVMPVsBT3vlK4u4l7uB dsp_simulink_MovingStandardDe_T;

#endif                             /* typedef_dsp_simulink_MovingStandardDe_T */

#ifndef struct_tag_rKScUQSS6qN2Sp349o0TPC
#define struct_tag_rKScUQSS6qN2Sp349o0TPC

struct tag_rKScUQSS6qN2Sp349o0TPC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_TOGGLER_T inputVarSize;
  g_dsp_internal_SlidingWindowA_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWindowA_T _pobj0;
};

#endif                                 /* struct_tag_rKScUQSS6qN2Sp349o0TPC */

#ifndef typedef_dsp_simulink_MovingAverage_TO_T
#define typedef_dsp_simulink_MovingAverage_TO_T

typedef struct tag_rKScUQSS6qN2Sp349o0TPC dsp_simulink_MovingAverage_TO_T;

#endif                             /* typedef_dsp_simulink_MovingAverage_TO_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_TOGGLER_T RT_MODEL_TOGGLER_T;

#endif                                 /* RTW_HEADER_TOGGLER_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
