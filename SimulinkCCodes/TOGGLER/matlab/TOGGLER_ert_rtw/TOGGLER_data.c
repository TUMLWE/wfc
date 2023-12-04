/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TOGGLER_data.c
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

/* Invariant block signals (default storage) */
const ConstB_TOGGLER_T TOGGLER_ConstB = {
  { 1.0, 2.0, 3.0, 4.0 },              /* '<Root>/Vector Concatenate1' */
  36000.0,                             /* '<S66>/Gain3' */
  3600.0,                              /* '<S68>/Gain' */

  { 0.0, 0.0, 0.0, 0.0 },              /* '<S66>/Gain' */
  36000.0,                             /* '<S77>/Gain3' */
  3600.0,                              /* '<S79>/Gain' */

  { 0.0, 0.0, 0.0, 0.0 },              /* '<S77>/Gain' */
  25.0,                                /* '<S42>/Variable Selector3' */

  { 180.0, 20.0 },                     /* '<S43>/Variable Selector3' */
  180.0,                               /* '<S43>/Multiport Selector' */
  20.0,                                /* '<S43>/Multiport Selector' */
  -160.0,                              /* '<S47>/Subtract' */

  { 268.0, 20.0 },                     /* '<S44>/Variable Selector3' */
  268.0,                               /* '<S44>/Multiport Selector' */
  20.0,                                /* '<S44>/Multiport Selector' */
  -248.0,                              /* '<S48>/Subtract' */

  { 4.0, 4.0, 11.0, 11.0 },

  { 4.0, 11.0 },                       /* '<S45>/Variable Selector3' */
  4.0,                                 /* '<S45>/Multiport Selector' */
  11.0,                                /* '<S45>/Multiport Selector' */
  25.0,                                /* '<S34>/Variable Selector3' */

  { 180.0, 20.0 },                     /* '<S35>/Variable Selector3' */
  180.0,                               /* '<S35>/Multiport Selector' */
  20.0,                                /* '<S35>/Multiport Selector' */
  -160.0,                              /* '<S39>/Subtract' */

  { 191.0, 259.0 },                    /* '<S36>/Variable Selector3' */
  191.0,                               /* '<S36>/Multiport Selector' */
  259.0,                               /* '<S36>/Multiport Selector' */
  68.0,                                /* '<S40>/Subtract' */

  { 4.0, 4.0, 11.0, 11.0 },

  { 4.0, 11.0 },                       /* '<S37>/Variable Selector3' */
  4.0,                                 /* '<S37>/Multiport Selector' */
  11.0,                                /* '<S37>/Multiport Selector' */
  0,                                   /* '<S69>/Compare' */
  0,                                   /* '<S80>/Compare' */
  1,                                   /* '<S99>/Compare' */
  1,                                   /* '<S100>/Compare' */
  0,                                   /* '<S47>/Relational Operator' */
  0,                                   /* '<S48>/Relational Operator' */
  0,                                   /* '<S39>/Relational Operator' */
  1                                    /* '<S40>/Relational Operator' */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
