/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: TOGGLER.h
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

#ifndef RTW_HEADER_TOGGLER_h_
#define RTW_HEADER_TOGGLER_h_
#ifndef TOGGLER_COMMON_INCLUDES_
#define TOGGLER_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* TOGGLER_COMMON_INCLUDES_ */

#include "TOGGLER_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include <stddef.h>
#include <string.h>
#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block signals (default storage) */
typedef struct {
  creal_T dcv[6000];
  real_T csumrev[5999];
  real_T Merge;                        /* '<S17>/Merge' */
  real_T In;                           /* '<S88>/In' */
  boolean_T Merge3[3];                 /* '<S16>/Merge3' */
} B_TOGGLER_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  dsp_simulink_MovingAverage_TO_T obj; /* '<Root>/Moving Average2' */
  dsp_simulink_MovingAverage_TO_T obj_d;/* '<Root>/Moving Average' */
  dsp_simulink_MovingStandardDe_T obj_l;/* '<S25>/Moving Standard Deviation1' */
  dsp_simulink_MovingStandardDe_T obj_ds;/* '<S24>/Moving Standard Deviation1' */
  creal_T UnitDelay_DSTATE[6000];      /* '<S89>/Unit Delay' */
  real_T Delay_DSTATE;                 /* '<S25>/Delay' */
  real_T Delay_DSTATE_p;               /* '<S24>/Delay' */
  real_T UnitDelay1_DSTATE;            /* '<S15>/Unit Delay1' */
  real_T Delay_DSTATE_m;               /* '<S19>/Delay' */
  real_T UnitDelay_DSTATE_d;           /* '<S91>/Unit Delay' */
  real_T UnitDelay1_DSTATE_f;          /* '<S89>/Unit Delay1' */
  real_T UnitDelay_DSTATE_c;           /* '<S66>/Unit Delay' */
  real_T UnitDelay_DSTATE_e;           /* '<S77>/Unit Delay' */
  real_T UnitDelay1_DSTATE_j[4];       /* '<S66>/Unit Delay1' */
  real_T UnitDelay1_DSTATE_n[4];       /* '<S77>/Unit Delay1' */
  real_T UnitDelay3_DSTATE;            /* '<S68>/Unit Delay3' */
  real_T UnitDelay2_DSTATE;            /* '<S66>/Unit Delay2' */
  real_T UnitDelay3_DSTATE_h;          /* '<S79>/Unit Delay3' */
  real_T UnitDelay2_DSTATE_p;          /* '<S77>/Unit Delay2' */
  real_T Delay2_DSTATE;                /* '<S55>/Delay2' */
  real_T Memory2_PreviousInput;        /* '<S62>/Memory2' */
  real_T Memory1_PreviousInput;        /* '<S62>/Memory1' */
  real_T Memory2_PreviousInput_k;      /* '<S64>/Memory2' */
  real_T Memory1_PreviousInput_j;      /* '<S64>/Memory1' */
  real_T Memory_PreviousInput[4];      /* '<S68>/Memory' */
  real_T Memory4_PreviousInput;        /* '<S68>/Memory4' */
  real_T Memory3_PreviousInput[4];     /* '<S68>/Memory3' */
  real_T Memory5_PreviousInput;        /* '<S68>/Memory5' */
  real_T Memory_PreviousInput_m[4];    /* '<S79>/Memory' */
  real_T Memory4_PreviousInput_c;      /* '<S79>/Memory4' */
  real_T Memory3_PreviousInput_h[4];   /* '<S79>/Memory3' */
  real_T Memory5_PreviousInput_b;      /* '<S79>/Memory5' */
  boolean_T UnitDelay2_DSTATE_g;       /* '<S15>/Unit Delay2' */
  boolean_T UnitDelay3_DSTATE_d;       /* '<S15>/Unit Delay3' */
  boolean_T Delay_DSTATE_pp;           /* '<S55>/Delay' */
  boolean_T Delay1_DSTATE;             /* '<S55>/Delay1' */
  uint8_T Memory1_PreviousInput_l;     /* '<S68>/Memory1' */
  uint8_T Memory1_PreviousInput_p;     /* '<S79>/Memory1' */
  boolean_T Memory2_PreviousInput_kq;  /* '<S68>/Memory2' */
  boolean_T Memory2_PreviousInput_e;   /* '<S79>/Memory2' */
} DW_TOGGLER_T;

/* Zero-crossing (trigger) state */
typedef struct {
  ZCSigState SampleandHold_Trig_ZCE;   /* '<S19>/Sample and Hold' */
} PrevZCX_TOGGLER_T;

/* Invariant block signals (default storage) */
typedef struct {
  const real_T VectorConcatenate1[4];  /* '<Root>/Vector Concatenate1' */
  const real_T Gain3;                  /* '<S66>/Gain3' */
  const real_T Gain;                   /* '<S68>/Gain' */
  const real_T Gain_i[4];              /* '<S66>/Gain' */
  const real_T Gain3_e;                /* '<S77>/Gain3' */
  const real_T Gain_h;                 /* '<S79>/Gain' */
  const real_T Gain_o[4];              /* '<S77>/Gain' */
  const real_T VariableSelector3;      /* '<S42>/Variable Selector3' */
  const real_T VariableSelector3_k[2]; /* '<S43>/Variable Selector3' */
  const real_T MultiportSelector_o1;   /* '<S43>/Multiport Selector' */
  const real_T MultiportSelector_o2;   /* '<S43>/Multiport Selector' */
  const real_T Subtract;               /* '<S47>/Subtract' */
  const real_T VariableSelector3_g[2]; /* '<S44>/Variable Selector3' */
  const real_T MultiportSelector_o1_k; /* '<S44>/Multiport Selector' */
  const real_T MultiportSelector_o2_g; /* '<S44>/Multiport Selector' */
  const real_T Subtract_p;             /* '<S48>/Subtract' */
  const real_T WakeSteering_WSRange[4];
  const real_T VariableSelector3_h[2]; /* '<S45>/Variable Selector3' */
  const real_T MultiportSelector_o1_i; /* '<S45>/Multiport Selector' */
  const real_T MultiportSelector_o2_d; /* '<S45>/Multiport Selector' */
  const real_T VariableSelector3_o;    /* '<S34>/Variable Selector3' */
  const real_T VariableSelector3_gv[2];/* '<S35>/Variable Selector3' */
  const real_T MultiportSelector_o1_h; /* '<S35>/Multiport Selector' */
  const real_T MultiportSelector_o2_o; /* '<S35>/Multiport Selector' */
  const real_T Subtract_d;             /* '<S39>/Subtract' */
  const real_T VariableSelector3_j[2]; /* '<S36>/Variable Selector3' */
  const real_T MultiportSelector_o1_c; /* '<S36>/Multiport Selector' */
  const real_T MultiportSelector_o2_j; /* '<S36>/Multiport Selector' */
  const real_T Subtract_g;             /* '<S40>/Subtract' */
  const real_T WakeSteering_WSRange_g[4];
  const real_T VariableSelector3_kc[2];/* '<S37>/Variable Selector3' */
  const real_T MultiportSelector_o1_ks;/* '<S37>/Multiport Selector' */
  const real_T MultiportSelector_o2_dp;/* '<S37>/Multiport Selector' */
  const boolean_T Compare;             /* '<S69>/Compare' */
  const boolean_T Compare_n;           /* '<S80>/Compare' */
  const boolean_T Compare_nf;          /* '<S99>/Compare' */
  const boolean_T Compare_a;           /* '<S100>/Compare' */
  const boolean_T RelationalOperator;  /* '<S47>/Relational Operator' */
  const boolean_T RelationalOperator_k;/* '<S48>/Relational Operator' */
  const boolean_T RelationalOperator_j;/* '<S39>/Relational Operator' */
  const boolean_T RelationalOperator_l;/* '<S40>/Relational Operator' */
} ConstB_TOGGLER_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T input_WS_ms;                  /* '<Root>/input_WS_ms' */
  real_T input_Dir_deg;                /* '<Root>/input_Dir_deg' */
  real_T input_WT3_NacelleOrientation;
                                     /* '<Root>/input_WT3_NacelleOrientation' */
  real_T input_WT3_Misalignment;       /* '<Root>/input_WT3_Misalignment' */
  real_T input_INFLW_1_Status;         /* '<Root>/input_INFLW_1_Status' */
  real_T input_OFFSET_1_Status;        /* '<Root>/input_OFFSET_1_Status' */
  real_T input_INFLW_2_Status;         /* '<Root>/input_INFLW_2_Status' */
  real_T input_OFFSET_2_Status;        /* '<Root>/input_OFFSET_2_Status' */
  real_T input_WFC_Offset_1_deg;       /* '<Root>/input_WFC_Offset_1_deg' */
  real_T input_WFC_Offset_2_deg;       /* '<Root>/input_WFC_Offset_2_deg' */
  real_T input_FlagTurbineWFC_isActive;
                                    /* '<Root>/input_FlagTurbineWFC_isActive' */
  real_T input_Flag_ManualSwitch_WFC; /* '<Root>/input_Flag_ManualSwitch_WFC' */
  real_T input_ManualSwitch_WFC_1;     /* '<Root>/input_ManualSwitch_WFC_1' */
  real_T input_ManualSwitch_GreedyWFC;
                                     /* '<Root>/input_ManualSwitch_GreedyWFC' */
  real_T input_ManualSwitch_WFC_2;     /* '<Root>/input_ManualSwitch_WFC_2' */
  real_T input_ManualSwitch_WFC_3;     /* '<Root>/input_ManualSwitch_WFC_3' */
  real_T input_WFC_Offset_3_deg;       /* '<Root>/input_WFC_Offset_3_deg' */
  real_T input_WFC_3_Status;           /* '<Root>/input_WFC_3_Status' */
  real_T input_Nacelle_MetMast_Offset;
                                     /* '<Root>/input_Nacelle_MetMast_Offset' */
  real_T input_WT3_OpStatus;           /* '<Root>/input_WT3_OpStatus' */
} ExtU_TOGGLER_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T output_Flag_WFCIsActive;      /* '<Root>/output_Flag_WFCIsActive' */
  real_T output_WFCStatus;             /* '<Root>/output_WFCStatus' */
  real_T output_ActiveCTRL;            /* '<Root>/output_ActiveCTRL' */
  real_T output_WFC_Offset;            /* '<Root>/output_WFC_Offset' */
  real_T output_WFC_Offset_Demanded;   /* '<Root>/output_WFC_Offset_Demanded' */
  real_T output_TotWFCTime;            /* '<Root>/output_TotWFCTime' */
  real_T output_WFC1Time;              /* '<Root>/output_WFC1Time' */
  real_T output_GreedyWFCTime;         /* '<Root>/output_GreedyWFCTime' */
  real_T output_WFC2Time;              /* '<Root>/output_WFC2Time' */
  real_T output_WFC3Time;              /* '<Root>/output_WFC3Time' */
} ExtY_TOGGLER_T;

/* Real-time Model Data Structure */
struct tag_RTM_TOGGLER_T {
  const char_T * volatile errorStatus;
};

/* Block signals (default storage) */
extern B_TOGGLER_T TOGGLER_B;

/* Block states (default storage) */
extern DW_TOGGLER_T TOGGLER_DW;

/* Zero-crossing (trigger) state */
extern PrevZCX_TOGGLER_T TOGGLER_PrevZCX;

/* External inputs (root inport signals with default storage) */
extern ExtU_TOGGLER_T TOGGLER_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_TOGGLER_T TOGGLER_Y;
extern const ConstB_TOGGLER_T TOGGLER_ConstB;/* constant block i/o */

/* Model entry point functions */
extern void TOGGLER_initialize(void);
extern void TOGGLER_step(void);
extern void TOGGLER_terminate(void);

/* Real-time Model object */
extern RT_MODEL_TOGGLER_T *const TOGGLER_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Scope9' : Unused code path elimination
 * Block '<S26>/Data Type Duplicate' : Unused code path elimination
 * Block '<S26>/Data Type Propagation' : Unused code path elimination
 * Block '<S29>/Data Type Duplicate' : Unused code path elimination
 * Block '<S29>/Data Type Propagation' : Unused code path elimination
 * Block '<S38>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S34>/Scope' : Unused code path elimination
 * Block '<S35>/Scope' : Unused code path elimination
 * Block '<S36>/Scope' : Unused code path elimination
 * Block '<S41>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S37>/Scope' : Unused code path elimination
 * Block '<S32>/Scope' : Unused code path elimination
 * Block '<S46>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S42>/Scope' : Unused code path elimination
 * Block '<S43>/Scope' : Unused code path elimination
 * Block '<S44>/Scope' : Unused code path elimination
 * Block '<S44>/Scope1' : Unused code path elimination
 * Block '<S49>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S45>/Scope' : Unused code path elimination
 * Block '<S33>/Scope' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<Root>/Delay' : Unused code path elimination
 * Block '<S13>/Compare' : Unused code path elimination
 * Block '<S13>/Constant' : Unused code path elimination
 * Block '<Root>/Scope1' : Unused code path elimination
 * Block '<Root>/Scope2' : Unused code path elimination
 * Block '<Root>/Scope3' : Unused code path elimination
 * Block '<Root>/Scope4' : Unused code path elimination
 * Block '<Root>/Scope5' : Unused code path elimination
 * Block '<Root>/Scope6' : Unused code path elimination
 * Block '<Root>/Scope7' : Unused code path elimination
 * Block '<Root>/Scope8' : Unused code path elimination
 * Block '<S15>/Scope1' : Unused code path elimination
 * Block '<S55>/Scope' : Unused code path elimination
 * Block '<S55>/Scope1' : Unused code path elimination
 * Block '<S68>/Scope' : Unused code path elimination
 * Block '<S68>/Scope1' : Unused code path elimination
 * Block '<S68>/Scope2' : Unused code path elimination
 * Block '<S66>/Scope1' : Unused code path elimination
 * Block '<S66>/Scope2' : Unused code path elimination
 * Block '<S66>/Scope3' : Unused code path elimination
 * Block '<S66>/Scope4' : Unused code path elimination
 * Block '<S66>/Scope6' : Unused code path elimination
 * Block '<S66>/Scope7' : Unused code path elimination
 * Block '<S63>/NOT' : Unused code path elimination
 * Block '<S79>/Scope' : Unused code path elimination
 * Block '<S79>/Scope1' : Unused code path elimination
 * Block '<S79>/Scope2' : Unused code path elimination
 * Block '<S77>/Scope1' : Unused code path elimination
 * Block '<S77>/Scope2' : Unused code path elimination
 * Block '<S77>/Scope3' : Unused code path elimination
 * Block '<S77>/Scope4' : Unused code path elimination
 * Block '<S77>/Scope6' : Unused code path elimination
 * Block '<S77>/Scope7' : Unused code path elimination
 * Block '<S19>/Scope' : Unused code path elimination
 * Block '<S89>/Constant3' : Unused code path elimination
 * Block '<S89>/Constant5' : Unused code path elimination
 * Block '<S89>/Constant6' : Unused code path elimination
 * Block '<S89>/Constant7' : Unused code path elimination
 * Block '<S89>/Gain' : Unused code path elimination
 * Block '<S89>/Gain1' : Unused code path elimination
 * Block '<S89>/Gain3' : Unused code path elimination
 * Block '<S89>/Logical Operator' : Unused code path elimination
 * Block '<S89>/Math Function' : Unused code path elimination
 * Block '<S89>/Relational Operator' : Unused code path elimination
 * Block '<S89>/Saturation2' : Unused code path elimination
 * Block '<S89>/Signed Sqrt' : Unused code path elimination
 * Block '<S89>/Switch3' : Unused code path elimination
 * Block '<S89>/Switch4' : Unused code path elimination
 * Block '<S89>/Switch7' : Unused code path elimination
 * Block '<S15>/Saturation' : Eliminated Saturate block
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'TOGGLER'
 * '<S1>'   : 'TOGGLER/Check Input'
 * '<S2>'   : 'TOGGLER/CheckSectorsInflow'
 * '<S3>'   : 'TOGGLER/Compare To Constant'
 * '<S4>'   : 'TOGGLER/Compare To Constant1'
 * '<S5>'   : 'TOGGLER/Dummy_SaturationBlock'
 * '<S6>'   : 'TOGGLER/If Action Subsystem'
 * '<S7>'   : 'TOGGLER/If Action Subsystem1'
 * '<S8>'   : 'TOGGLER/If Action Subsystem3'
 * '<S9>'   : 'TOGGLER/If Action Subsystem4'
 * '<S10>'  : 'TOGGLER/If Action Subsystem5'
 * '<S11>'  : 'TOGGLER/If Action Subsystem6'
 * '<S12>'  : 'TOGGLER/If Action Subsystem8'
 * '<S13>'  : 'TOGGLER/IsZero'
 * '<S14>'  : 'TOGGLER/Set offset to zero'
 * '<S15>'  : 'TOGGLER/Subsystem1'
 * '<S16>'  : 'TOGGLER/Subsystem2'
 * '<S17>'  : 'TOGGLER/Subsystem3'
 * '<S18>'  : 'TOGGLER/Subsystem4'
 * '<S19>'  : 'TOGGLER/WDirCheck'
 * '<S20>'  : 'TOGGLER/isWFCStrategyOn?'
 * '<S21>'  : 'TOGGLER/isWFCStrategyOn?1'
 * '<S22>'  : 'TOGGLER/isWFCStrategyOn?2'
 * '<S23>'  : 'TOGGLER/isWFCStrategyOn?3'
 * '<S24>'  : 'TOGGLER/Check Input/Subsystem5'
 * '<S25>'  : 'TOGGLER/Check Input/Subsystem6'
 * '<S26>'  : 'TOGGLER/Check Input/Subsystem5/Saturation Dynamic'
 * '<S27>'  : 'TOGGLER/Check Input/Subsystem5/Subsystem5'
 * '<S28>'  : 'TOGGLER/Check Input/Subsystem5/Subsystem5/Compare To Constant'
 * '<S29>'  : 'TOGGLER/Check Input/Subsystem6/Saturation Dynamic'
 * '<S30>'  : 'TOGGLER/Check Input/Subsystem6/Subsystem5'
 * '<S31>'  : 'TOGGLER/Check Input/Subsystem6/Subsystem5/Compare To Constant'
 * '<S32>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem'
 * '<S33>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1'
 * '<S34>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem/CheckRangeMisal'
 * '<S35>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem/CheckRangeNacelle'
 * '<S36>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem/CheckRangeWDir'
 * '<S37>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem/CheckRangeWS'
 * '<S38>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem/CheckRangeMisal/Interval Test Dynamic'
 * '<S39>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem/CheckRangeNacelle/Subsystem'
 * '<S40>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem/CheckRangeWDir/Subsystem'
 * '<S41>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem/CheckRangeWS/Interval Test Dynamic'
 * '<S42>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1/CheckRangeMisal'
 * '<S43>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1/CheckRangeNacelle'
 * '<S44>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1/CheckRangeWDir'
 * '<S45>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1/CheckRangeWS'
 * '<S46>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1/CheckRangeMisal/Interval Test Dynamic'
 * '<S47>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1/CheckRangeNacelle/Subsystem'
 * '<S48>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1/CheckRangeWDir/Subsystem'
 * '<S49>'  : 'TOGGLER/CheckSectorsInflow/Atomic Subsystem1/CheckRangeWS/Interval Test Dynamic'
 * '<S50>'  : 'TOGGLER/Subsystem1/Compare To Zero'
 * '<S51>'  : 'TOGGLER/Subsystem2/Enabled Subsystem'
 * '<S52>'  : 'TOGGLER/Subsystem2/Enabled Subsystem1'
 * '<S53>'  : 'TOGGLER/Subsystem3/Enabled Subsystem'
 * '<S54>'  : 'TOGGLER/Subsystem3/Enabled Subsystem1'
 * '<S55>'  : 'TOGGLER/Subsystem3/Enabled Subsystem2'
 * '<S56>'  : 'TOGGLER/Subsystem3/Enabled Subsystem3'
 * '<S57>'  : 'TOGGLER/Subsystem3/Subsystem'
 * '<S58>'  : 'TOGGLER/Subsystem3/Enabled Subsystem2/IsZero'
 * '<S59>'  : 'TOGGLER/Subsystem3/Enabled Subsystem2/IsZero1'
 * '<S60>'  : 'TOGGLER/Subsystem4/MATLAB Function'
 * '<S61>'  : 'TOGGLER/Subsystem4/MATLAB Function1'
 * '<S62>'  : 'TOGGLER/Subsystem4/Subsystem'
 * '<S63>'  : 'TOGGLER/Subsystem4/Subsystem1'
 * '<S64>'  : 'TOGGLER/Subsystem4/Subsystem3'
 * '<S65>'  : 'TOGGLER/Subsystem4/Subsystem/Toggler'
 * '<S66>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager'
 * '<S67>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/Compare To Constant'
 * '<S68>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/ControlLogic_DEVIATION'
 * '<S69>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/IsNonZero'
 * '<S70>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/IsZero'
 * '<S71>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/ControlLogic_DEVIATION/Compare To Zero'
 * '<S72>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/ControlLogic_DEVIATION/MATLAB Function'
 * '<S73>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/ControlLogic_DEVIATION/MATLAB Function1'
 * '<S74>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/ControlLogic_DEVIATION/MATLAB Function2'
 * '<S75>'  : 'TOGGLER/Subsystem4/Subsystem/WFC Time Manager/ControlLogic_DEVIATION/MATLAB Function3'
 * '<S76>'  : 'TOGGLER/Subsystem4/Subsystem3/Toggler'
 * '<S77>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager'
 * '<S78>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/Compare To Constant'
 * '<S79>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/ControlLogic_DEVIATION'
 * '<S80>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/IsNonZero'
 * '<S81>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/IsZero'
 * '<S82>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/ControlLogic_DEVIATION/Compare To Zero'
 * '<S83>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/ControlLogic_DEVIATION/MATLAB Function'
 * '<S84>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/ControlLogic_DEVIATION/MATLAB Function1'
 * '<S85>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/ControlLogic_DEVIATION/MATLAB Function2'
 * '<S86>'  : 'TOGGLER/Subsystem4/Subsystem3/WFC Time Manager/ControlLogic_DEVIATION/MATLAB Function3'
 * '<S87>'  : 'TOGGLER/WDirCheck/Compare To Constant'
 * '<S88>'  : 'TOGGLER/WDirCheck/Sample and Hold'
 * '<S89>'  : 'TOGGLER/WDirCheck/Subsystem5'
 * '<S90>'  : 'TOGGLER/WDirCheck/Subsystem5/MATLAB Function'
 * '<S91>'  : 'TOGGLER/WDirCheck/Subsystem5/feasibility check'
 * '<S92>'  : 'TOGGLER/WDirCheck/Subsystem5/feasibility check/Compare To Constant'
 * '<S93>'  : 'TOGGLER/WDirCheck/Subsystem5/feasibility check/Compare To Constant1'
 * '<S94>'  : 'TOGGLER/WDirCheck/Subsystem5/feasibility check/Compare To Constant2'
 * '<S95>'  : 'TOGGLER/isWFCStrategyOn?/Compare To Constant1'
 * '<S96>'  : 'TOGGLER/isWFCStrategyOn?/Compare To Constant7'
 * '<S97>'  : 'TOGGLER/isWFCStrategyOn?/Compare To Constant8'
 * '<S98>'  : 'TOGGLER/isWFCStrategyOn?1/Compare To Constant1'
 * '<S99>'  : 'TOGGLER/isWFCStrategyOn?1/Compare To Constant7'
 * '<S100>' : 'TOGGLER/isWFCStrategyOn?1/Compare To Constant8'
 * '<S101>' : 'TOGGLER/isWFCStrategyOn?2/Compare To Constant1'
 * '<S102>' : 'TOGGLER/isWFCStrategyOn?2/Compare To Constant7'
 * '<S103>' : 'TOGGLER/isWFCStrategyOn?2/Compare To Constant8'
 * '<S104>' : 'TOGGLER/isWFCStrategyOn?3/Compare To Constant1'
 * '<S105>' : 'TOGGLER/isWFCStrategyOn?3/Compare To Constant7'
 * '<S106>' : 'TOGGLER/isWFCStrategyOn?3/Compare To Constant8'
 */
#endif                                 /* RTW_HEADER_TOGGLER_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
