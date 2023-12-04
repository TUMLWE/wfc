/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: INFLW_1_types.h
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

#ifndef RTW_HEADER_INFLW_1_types_h_
#define RTW_HEADER_INFLW_1_types_h_
#include "rtwtypes.h"
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

#ifndef typedef_cell_wrap_INFLW_1_T
#define typedef_cell_wrap_INFLW_1_T

typedef struct tag_BlgwLpgj2bjudmbmVKWwDE cell_wrap_INFLW_1_T;

#endif                                 /* typedef_cell_wrap_INFLW_1_T */

#ifndef struct_tag_rKScUQSS6qN2Sp349o0TPC
#define struct_tag_rKScUQSS6qN2Sp349o0TPC

struct tag_rKScUQSS6qN2Sp349o0TPC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_INFLW_1_T inputVarSize;
  g_dsp_internal_SlidingWindowA_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWindowA_T _pobj0;
};

#endif                                 /* struct_tag_rKScUQSS6qN2Sp349o0TPC */

#ifndef typedef_dsp_simulink_MovingAverage_IN_T
#define typedef_dsp_simulink_MovingAverage_IN_T

typedef struct tag_rKScUQSS6qN2Sp349o0TPC dsp_simulink_MovingAverage_IN_T;

#endif                             /* typedef_dsp_simulink_MovingAverage_IN_T */

#ifndef struct_tag_NI3XcQY1yNDmhdXZqGpsEG
#define struct_tag_NI3XcQY1yNDmhdXZqGpsEG

struct tag_NI3XcQY1yNDmhdXZqGpsEG
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T pCumSum;
  real_T pCumSumRev[599];
  real_T pCumRevIndex;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_NI3XcQY1yNDmhdXZqGpsEG */

#ifndef typedef_g_dsp_internal_SlidingWindo_l_T
#define typedef_g_dsp_internal_SlidingWindo_l_T

typedef struct tag_NI3XcQY1yNDmhdXZqGpsEG g_dsp_internal_SlidingWindo_l_T;

#endif                             /* typedef_g_dsp_internal_SlidingWindo_l_T */

#ifndef struct_tag_9cuXCXpi332w8lcAt63ilH
#define struct_tag_9cuXCXpi332w8lcAt63ilH

struct tag_9cuXCXpi332w8lcAt63ilH
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_INFLW_1_T inputVarSize;
  g_dsp_internal_SlidingWindo_l_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWindo_l_T _pobj0;
};

#endif                                 /* struct_tag_9cuXCXpi332w8lcAt63ilH */

#ifndef typedef_dsp_simulink_MovingAverage_e_T
#define typedef_dsp_simulink_MovingAverage_e_T

typedef struct tag_9cuXCXpi332w8lcAt63ilH dsp_simulink_MovingAverage_e_T;

#endif                              /* typedef_dsp_simulink_MovingAverage_e_T */

#ifndef struct_tag_QbB2XqHP2Jm7umsQ7n5yUD
#define struct_tag_QbB2XqHP2Jm7umsQ7n5yUD

struct tag_QbB2XqHP2Jm7umsQ7n5yUD
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T pReverseSamples[600];
  real_T pReverseT[600];
  real_T pReverseS[600];
  real_T pT;
  real_T pS;
  real_T pM;
  real_T pCounter;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_QbB2XqHP2Jm7umsQ7n5yUD */

#ifndef typedef_g_dsp_internal_SlidingWindowV_T
#define typedef_g_dsp_internal_SlidingWindowV_T

typedef struct tag_QbB2XqHP2Jm7umsQ7n5yUD g_dsp_internal_SlidingWindowV_T;

#endif                             /* typedef_g_dsp_internal_SlidingWindowV_T */

#ifndef struct_tag_B5EFeaAhe8w7MUFMfqJCvD
#define struct_tag_B5EFeaAhe8w7MUFMfqJCvD

struct tag_B5EFeaAhe8w7MUFMfqJCvD
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_INFLW_1_T inputVarSize;
  g_dsp_internal_SlidingWindowV_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWindowV_T _pobj0;
};

#endif                                 /* struct_tag_B5EFeaAhe8w7MUFMfqJCvD */

#ifndef typedef_dsp_simulink_MovingStandardDe_T
#define typedef_dsp_simulink_MovingStandardDe_T

typedef struct tag_B5EFeaAhe8w7MUFMfqJCvD dsp_simulink_MovingStandardDe_T;

#endif                             /* typedef_dsp_simulink_MovingStandardDe_T */

#ifndef struct_tag_CWH6DTHP01Gd55CkkzwSIG
#define struct_tag_CWH6DTHP01Gd55CkkzwSIG

struct tag_CWH6DTHP01Gd55CkkzwSIG
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T pCumSum;
  real_T pCumSumRev[299];
  real_T pCumRevIndex;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_CWH6DTHP01Gd55CkkzwSIG */

#ifndef typedef_g_dsp_internal_SlidingWindo_m_T
#define typedef_g_dsp_internal_SlidingWindo_m_T

typedef struct tag_CWH6DTHP01Gd55CkkzwSIG g_dsp_internal_SlidingWindo_m_T;

#endif                             /* typedef_g_dsp_internal_SlidingWindo_m_T */

#ifndef struct_tag_mc80LTkxA91dajiaRpnwiF
#define struct_tag_mc80LTkxA91dajiaRpnwiF

struct tag_mc80LTkxA91dajiaRpnwiF
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real_T pReverseSamples[6000];
  real_T pReverseT[6000];
  real_T pReverseS[6000];
  real_T pT;
  real_T pS;
  real_T pM;
  real_T pCounter;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_mc80LTkxA91dajiaRpnwiF */

#ifndef typedef_g_dsp_internal_SlidingWind_ma_T
#define typedef_g_dsp_internal_SlidingWind_ma_T

typedef struct tag_mc80LTkxA91dajiaRpnwiF g_dsp_internal_SlidingWind_ma_T;

#endif                             /* typedef_g_dsp_internal_SlidingWind_ma_T */

#ifndef struct_tag_uuKGx9UEdnOnhqLoPxYEkC
#define struct_tag_uuKGx9UEdnOnhqLoPxYEkC

struct tag_uuKGx9UEdnOnhqLoPxYEkC
{
  int32_T isInitialized;
  boolean_T isSetupComplete;
  creal_T pCumSum;
  creal_T pCumSumRev[999];
  real_T pCumRevIndex;
  real_T pModValueRev;
};

#endif                                 /* struct_tag_uuKGx9UEdnOnhqLoPxYEkC */

#ifndef typedef_g_dsp_internal_SlidingWin_mab_T
#define typedef_g_dsp_internal_SlidingWin_mab_T

typedef struct tag_uuKGx9UEdnOnhqLoPxYEkC g_dsp_internal_SlidingWin_mab_T;

#endif                             /* typedef_g_dsp_internal_SlidingWin_mab_T */

#ifndef struct_tag_bpXjadQgrd0jNiqC0SXNYB
#define struct_tag_bpXjadQgrd0jNiqC0SXNYB

struct tag_bpXjadQgrd0jNiqC0SXNYB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_INFLW_1_T inputVarSize;
  g_dsp_internal_SlidingWindo_m_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWindo_m_T _pobj0;
};

#endif                                 /* struct_tag_bpXjadQgrd0jNiqC0SXNYB */

#ifndef typedef_dsp_simulink_MovingAverage_m_T
#define typedef_dsp_simulink_MovingAverage_m_T

typedef struct tag_bpXjadQgrd0jNiqC0SXNYB dsp_simulink_MovingAverage_m_T;

#endif                              /* typedef_dsp_simulink_MovingAverage_m_T */

#ifndef struct_tag_IYErJ6Xqcp0jBI50a9ajyF
#define struct_tag_IYErJ6Xqcp0jBI50a9ajyF

struct tag_IYErJ6Xqcp0jBI50a9ajyF
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_INFLW_1_T inputVarSize;
  g_dsp_internal_SlidingWind_ma_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWind_ma_T _pobj0;
};

#endif                                 /* struct_tag_IYErJ6Xqcp0jBI50a9ajyF */

#ifndef typedef_dsp_simulink_MovingStandard_m_T
#define typedef_dsp_simulink_MovingStandard_m_T

typedef struct tag_IYErJ6Xqcp0jBI50a9ajyF dsp_simulink_MovingStandard_m_T;

#endif                             /* typedef_dsp_simulink_MovingStandard_m_T */

#ifndef struct_tag_0cC6za4GUjuHxkpgef1ylC
#define struct_tag_0cC6za4GUjuHxkpgef1ylC

struct tag_0cC6za4GUjuHxkpgef1ylC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_INFLW_1_T inputVarSize;
  g_dsp_internal_SlidingWin_mab_T *pStatistic;
  int32_T NumChannels;
  int32_T FrameLength;
  g_dsp_internal_SlidingWin_mab_T _pobj0;
};

#endif                                 /* struct_tag_0cC6za4GUjuHxkpgef1ylC */

#ifndef typedef_dsp_simulink_MovingAverage_ma_T
#define typedef_dsp_simulink_MovingAverage_ma_T

typedef struct tag_0cC6za4GUjuHxkpgef1ylC dsp_simulink_MovingAverage_ma_T;

#endif                             /* typedef_dsp_simulink_MovingAverage_ma_T */

/* Forward declaration for rtModel */
typedef struct tag_RTM_INFLW_1_T RT_MODEL_INFLW_1_T;

#endif                                 /* RTW_HEADER_INFLW_1_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
