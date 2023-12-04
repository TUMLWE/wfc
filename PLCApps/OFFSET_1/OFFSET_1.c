/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: OFFSET_1.c
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

#include "OFFSET_1.h"
#include "rtwtypes.h"
#include <string.h>
#include "OFFSET_1_private.h"

/* External inputs (root inport signals with default storage) */
ExtU_OFFSET_1_T OFFSET_1_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_OFFSET_1_T OFFSET_1_Y;

/* Real-time model */
static RT_MODEL_OFFSET_1_T OFFSET_1_M_;
RT_MODEL_OFFSET_1_T *const OFFSET_1_M = &OFFSET_1_M_;
uint32_T plook_binca(real_T u, const real_T bp[], uint32_T maxIndex, real_T
                     *fraction)
{
  uint32_T bpIndex;

  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'on'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u <= bp[0U]) {
    bpIndex = 0U;
    *fraction = 0.0;
  } else if (u < bp[maxIndex]) {
    bpIndex = binsearch_u32d(u, bp, maxIndex >> 1U, maxIndex);
    *fraction = (u - bp[bpIndex]) / (bp[bpIndex + 1U] - bp[bpIndex]);
  } else {
    bpIndex = maxIndex;
    *fraction = 0.0;
  }

  return bpIndex;
}

real_T intrp4d_la_pw(const uint32_T bpIndex[], const real_T frac[], const real_T
                     table[], const uint32_T stride[], const uint32_T maxIndex[])
{
  real_T y;
  real_T yL_0d0;
  real_T yL_1d;
  uint32_T offset_0d;
  uint32_T offset_1d;
  uint32_T offset_3d;

  /* Column-major Interpolation 4-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'on'
     Overflow mode: 'portable wrapping'
   */
  offset_3d = ((bpIndex[3U] * stride[3U] + bpIndex[2U] * stride[2U]) + bpIndex
               [1U] * stride[1U]) + bpIndex[0U];
  if (bpIndex[0U] == maxIndex[0U]) {
    y = table[offset_3d];
  } else {
    yL_0d0 = table[offset_3d];
    y = (table[offset_3d + 1U] - yL_0d0) * frac[0U] + yL_0d0;
  }

  if (bpIndex[1U] == maxIndex[1U]) {
  } else {
    offset_0d = offset_3d + stride[1U];
    if (bpIndex[0U] == maxIndex[0U]) {
      yL_0d0 = table[offset_0d];
    } else {
      yL_0d0 = table[offset_0d];
      yL_0d0 += (table[offset_0d + 1U] - yL_0d0) * frac[0U];
    }

    y += (yL_0d0 - y) * frac[1U];
  }

  if (bpIndex[2U] == maxIndex[2U]) {
  } else {
    offset_1d = offset_3d + stride[2U];
    if (bpIndex[0U] == maxIndex[0U]) {
      yL_1d = table[offset_1d];
    } else {
      yL_0d0 = table[offset_1d];
      yL_1d = (table[offset_1d + 1U] - yL_0d0) * frac[0U] + yL_0d0;
    }

    if (bpIndex[1U] == maxIndex[1U]) {
    } else {
      offset_0d = offset_1d + stride[1U];
      if (bpIndex[0U] == maxIndex[0U]) {
        yL_0d0 = table[offset_0d];
      } else {
        yL_0d0 = table[offset_0d];
        yL_0d0 += (table[offset_0d + 1U] - yL_0d0) * frac[0U];
      }

      yL_1d += (yL_0d0 - yL_1d) * frac[1U];
    }

    y += (yL_1d - y) * frac[2U];
  }

  if (bpIndex[3U] == maxIndex[3U]) {
  } else {
    offset_1d = offset_3d + stride[3U];
    if (bpIndex[0U] == maxIndex[0U]) {
      yL_1d = table[offset_1d];
    } else {
      yL_0d0 = table[offset_1d];
      yL_1d = (table[offset_1d + 1U] - yL_0d0) * frac[0U] + yL_0d0;
    }

    if (bpIndex[1U] == maxIndex[1U]) {
    } else {
      offset_0d = offset_1d + stride[1U];
      if (bpIndex[0U] == maxIndex[0U]) {
        yL_0d0 = table[offset_0d];
      } else {
        yL_0d0 = table[offset_0d];
        yL_0d0 += (table[offset_0d + 1U] - yL_0d0) * frac[0U];
      }

      yL_1d += (yL_0d0 - yL_1d) * frac[1U];
    }

    if (bpIndex[2U] == maxIndex[2U]) {
    } else {
      real_T yL_1d_0;
      offset_1d += stride[2U];
      if (bpIndex[0U] == maxIndex[0U]) {
        yL_1d_0 = table[offset_1d];
      } else {
        yL_0d0 = table[offset_1d];
        yL_1d_0 = (table[offset_1d + 1U] - yL_0d0) * frac[0U] + yL_0d0;
      }

      if (bpIndex[1U] == maxIndex[1U]) {
      } else {
        offset_0d = offset_1d + stride[1U];
        if (bpIndex[0U] == maxIndex[0U]) {
          yL_0d0 = table[offset_0d];
        } else {
          yL_0d0 = table[offset_0d];
          yL_0d0 += (table[offset_0d + 1U] - yL_0d0) * frac[0U];
        }

        yL_1d_0 += (yL_0d0 - yL_1d_0) * frac[1U];
      }

      yL_1d += (yL_1d_0 - yL_1d) * frac[2U];
    }

    y += (yL_1d - y) * frac[3U];
  }

  return y;
}

uint32_T binsearch_u32d(real_T u, const real_T bp[], uint32_T startIndex,
  uint32_T maxIndex)
{
  uint32_T bpIdx;
  uint32_T bpIndex;
  uint32_T iRght;

  /* Binary Search */
  bpIdx = startIndex;
  bpIndex = 0U;
  iRght = maxIndex;
  while (iRght - bpIndex > 1U) {
    if (u < bp[bpIdx]) {
      iRght = bpIdx;
    } else {
      bpIndex = bpIdx;
    }

    bpIdx = (iRght + bpIndex) >> 1U;
  }

  return bpIndex;
}

/* Model step function */
void OFFSET_1_step(void)
{
  real_T fractions[4];
  real_T frac;
  uint32_T bpIndices[4];
  boolean_T output_OK_tmp;
  boolean_T output_OK_tmp_0;
  boolean_T output_OK_tmp_1;
  boolean_T rtb_AND;

  /* Logic: '<S3>/AND' incorporates:
   *  Constant: '<S3>/Lower Limit'
   *  Constant: '<S3>/Upper Limit'
   *  Inport: '<Root>/input_WS_Filtered_ms'
   *  RelationalOperator: '<S3>/Lower Test'
   *  RelationalOperator: '<S3>/Upper Test'
   */
  rtb_AND = ((OFFSET_1_U.input_WS_Filtered_ms >= 3.0) &&
             (OFFSET_1_U.input_WS_Filtered_ms <= 12.0));

  /* Logic: '<S2>/NOT1' incorporates:
   *  Constant: '<S4>/Lower Limit'
   *  Constant: '<S4>/Upper Limit'
   *  Constant: '<S5>/Lower Limit'
   *  Constant: '<S5>/Upper Limit'
   *  Constant: '<S6>/Lower Limit'
   *  Constant: '<S6>/Upper Limit'
   *  Inport: '<Root>/input_ShearExp_Filtered'
   *  Inport: '<Root>/input_TI_Filtered'
   *  Inport: '<Root>/input_WDir_Filtered_deg'
   *  Logic: '<S2>/Logical Operator'
   *  Logic: '<S4>/AND'
   *  Logic: '<S5>/AND'
   *  Logic: '<S6>/AND'
   *  RelationalOperator: '<S4>/Lower Test'
   *  RelationalOperator: '<S4>/Upper Test'
   *  RelationalOperator: '<S5>/Lower Test'
   *  RelationalOperator: '<S5>/Upper Test'
   *  RelationalOperator: '<S6>/Lower Test'
   *  RelationalOperator: '<S6>/Upper Test'
   */
  /* Bit to Integer Conversion */
  /* Input bit order is MSB first */
  output_OK_tmp = ((!(OFFSET_1_U.input_WDir_Filtered_deg >= 185.0)) ||
                   (!(OFFSET_1_U.input_WDir_Filtered_deg <= 260.0)));
  output_OK_tmp_0 = ((!(OFFSET_1_U.input_TI_Filtered >= 0.0)) ||
                     (!(OFFSET_1_U.input_TI_Filtered <= 0.4)));
  output_OK_tmp_1 = ((!(OFFSET_1_U.input_ShearExp_Filtered >= -0.99)) ||
                     (!(OFFSET_1_U.input_ShearExp_Filtered <= 0.99)));

  /* Outport: '<Root>/output_OK' incorporates:
   *  DataTypeConversion: '<Root>/Cast To Double'
   *  Logic: '<S2>/NOT1'
   *  S-Function (scominttobit): '<Root>/Bit to Integer Converter1'
   */
  OFFSET_1_Y.output_OK = (uint8_T)((((uint32_T)!rtb_AND << 1U | output_OK_tmp) <<
    1U | output_OK_tmp_0) << 1U | output_OK_tmp_1);

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<S1>/Constant'
   *  Inport: '<Root>/input_inflowOK'
   *  Logic: '<Root>/Logical Operator'
   *  Logic: '<S2>/Logical Operator'
   *  Logic: '<S2>/NOT'
   *  RelationalOperator: '<S1>/Compare'
   */
  if ((!rtb_AND) || output_OK_tmp || output_OK_tmp_0 || output_OK_tmp_1 ||
      (OFFSET_1_U.input_inflowOK > 0.0)) {
    /* Outport: '<Root>/output_Offset_deg' incorporates:
     *  Constant: '<Root>/Zero'
     */
    OFFSET_1_Y.output_Offset_deg = 0.0;
  } else {
    /* Lookup_n-D: '<S2>/n-D Lookup Table' incorporates:
     *  Inport: '<Root>/input_ShearExp_Filtered'
     *  Inport: '<Root>/input_TI_Filtered'
     *  Inport: '<Root>/input_WDir_Filtered_deg'
     *  Inport: '<Root>/input_WS_Filtered_ms'
     */
    bpIndices[0U] = plook_binca(OFFSET_1_U.input_WS_Filtered_ms,
      OFFSET_1_ConstP.nDLookupTable_bp01Data, 6U, &frac);
    fractions[0U] = frac;
    bpIndices[1U] = plook_binca(OFFSET_1_U.input_WDir_Filtered_deg,
      OFFSET_1_ConstP.nDLookupTable_bp02Data, 40U, &frac);
    fractions[1U] = frac;
    bpIndices[2U] = plook_binca(OFFSET_1_U.input_TI_Filtered,
      OFFSET_1_ConstP.nDLookupTable_bp03Data, 2U, &frac);
    fractions[2U] = frac;
    bpIndices[3U] = plook_binca(OFFSET_1_U.input_ShearExp_Filtered,
      OFFSET_1_ConstP.nDLookupTable_bp04Data, 2U, &frac);
    fractions[3U] = frac;

    /* Outport: '<Root>/output_Offset_deg' incorporates:
     *  Lookup_n-D: '<S2>/n-D Lookup Table'
     */
    OFFSET_1_Y.output_Offset_deg = intrp4d_la_pw(bpIndices, fractions,
      OFFSET_1_ConstP.nDLookupTable_tableData,
      OFFSET_1_ConstP.nDLookupTable_dimSizes,
      OFFSET_1_ConstP.nDLookupTable_maxIndex);
  }

  /* End of Switch: '<Root>/Switch' */
}

/* Model initialize function */
void OFFSET_1_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(OFFSET_1_M, (NULL));

  /* external inputs */
  (void)memset(&OFFSET_1_U, 0, sizeof(ExtU_OFFSET_1_T));

  /* external outputs */
  (void)memset(&OFFSET_1_Y, 0, sizeof(ExtY_OFFSET_1_T));
}

/* Model terminate function */
void OFFSET_1_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
