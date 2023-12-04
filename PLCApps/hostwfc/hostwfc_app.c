/**
********************************************************************************
* @file     hostwfc_app.c
* @author   Bachmann electronic GmbH
* @version  $Revision: 3.90 $ $LastChangedBy: BE $
* @date     $LastChangeDate: 2013-06-10 11:00:00 $
*
* @brief    This file contains the application algorithms
*           and the application specific SVI interface.
*
********************************************************************************
* COPYRIGHT BY BACHMANN ELECTRONIC GmbH 2013
*******************************************************************************/

/* VxWorks includes */
#include <vxWorks.h>
#include <taskLib.h>
#include <tickLib.h>
#include <intLib.h>
#include <semLib.h>
#include <sysLib.h>
#include <inetLib.h>
#include <string.h>
#include <stdio.h>
#include <symLib.h>
#include <sysSymTbl.h>

/* MSys includes */
#include <mtypes.h>
#include <msys_e.h>
#include <mio.h>
#include <mio_e.h>
#include <res_e.h>
#include <svi_e.h>
#include <log_e.h>
#include <prof_e.h>
#include <lst_e.h>

/* Project includes */
#include "hostwfc.h"
#include "hostwfc_e.h"
#include "hostwfc_int.h"

/* Functions: administration, to be called from outside this file */
SINT32  hostwfc_AppEOI(VOID);
VOID    hostwfc_AppDeinit(VOID);
SINT32  hostwfc_CfgRead(VOID);
SINT32  hostwfc_SviSrvInit(VOID);
VOID    hostwfc_SviSrvDeinit(VOID);

/* Functions: administration, to be called only from within this file */
MLOCAL VOID hostwfc_CfgInit(VOID);

/* Functions: task administration, being called only within this file */
MLOCAL SINT32 Task_CreateAll(VOID);
MLOCAL VOID Task_DeleteAll(VOID);
MLOCAL SINT32 Task_CfgRead(VOID);
MLOCAL SINT32 Task_InitTiming(TASK_PROPERTIES * pTaskData);
MLOCAL SINT32 Task_InitTiming_Tick(TASK_PROPERTIES * pTaskData);
MLOCAL SINT32 Task_InitTiming_Sync(TASK_PROPERTIES * pTaskData);
MLOCAL VOID Task_WaitCycle(TASK_PROPERTIES * pTaskData);

/* Functions: worker task "Control" */
MLOCAL VOID Control_Main(TASK_PROPERTIES * pTaskData);
MLOCAL VOID Control_CycleInit(VOID);
MLOCAL VOID Control_CycleStart(VOID);
MLOCAL VOID Control_Cycle(VOID);
MLOCAL VOID Control_CycleEnd(TASK_PROPERTIES * pTaskData);

/* Functions: SVI client */
MLOCAL SINT32 SviClt_Example(UINT32 * pTime_us);
MLOCAL SINT32 SviClt_Init(VOID);
MLOCAL VOID SviClt_Deinit(VOID);


MLOCAL SINT32 SviClt_Read();
MLOCAL SINT32 SviClt_Write(VOID);

/* Global variables: data structure for mconfig parameters */
HOSTWFC_BASE_PARMS hostwfc_BaseParams;

/* Global variables: SVI client */
MLOCAL  SINT32(**pSviLib) () = NULL;    /* Information about external SVI server */
MLOCAL SVI_ADDR TimeSviAddr;            /* SVI address of server's variable */
MLOCAL BOOL8 PrintTime = TRUE;



// MATLABCODEGEN: OpenField SVI Server Definition

MLOCAL SINT32  (**pSviLib_tumitfc)  ()= NULL;

// MATLABCODEGEN: CloseField SVI Server Definition


// MATLABCODEGEN: OpenField SA Address and Variables to be read from interface

REAL64 tumitfc_cw2InAr[58];
MLOCAL SVI_ADDR SA_tumitfc_cw2InAr;
REAL64 tumitfc_cw2OutAr[10];
MLOCAL SVI_ADDR SA_tumitfc_cw2OutAr;

// MATLABCODEGEN: CloseField SA Address and Variables to be read from interface

/* Global variables: miscellaneous */
char output_FileName_main[1024] = "hostwfc";
char output_path[1024] = "/usbBulk0/CW2/";
MLOCAL UINT32 newfile_time_s =60;




// Buffer and Writer Task Settings
MLOCAL UINT32 FAST_FREQ_RATIO = 1;       // Ratio between AppCklRate and Fast Buffer
MLOCAL UINT32 SLOW_FREQ_RATIO = 10;      // Ratio between AppCklRate and Slow Buffer
MLOCAL UINT32 CTRL_FREQ_RATIO = 10;      // Ratio between AppCklRate and Control Buffer



MLOCAL UINT16 Recording_Start = TRUE;      // Needs to be UINT16 in order to be modbus compatible
MLOCAL UINT16 Recording_Start_prev = TRUE;      // Needs to be UINT16 in order to be modbus compatible
MLOCAL UINT32 CycleCount_new_file = 0;
MLOCAL SVI_ADDR Time_ms1970_SviAddr;
UINT64  Time_ms1970;
#define TRUE 1
#define FALSE 0
#define MAXSTRLENGTH 1024
MLOCAL FILE *pFileFast  = NULL;                 // File for fast data recording
MLOCAL FILE *pFileSlow  = NULL;                 // File for slow data recording
MLOCAL FILE *pFileCtrl  = NULL;                 // File for recording controller data
MLOCAL SINT32 write_header_fast();
MLOCAL SINT32 write_output_fast();
MLOCAL SINT32 write_header_slow();
MLOCAL SINT32 write_output_slow();
MLOCAL SINT32 write_header_ctrl();
MLOCAL SINT32 write_output_ctrl();
char output_FileName_fast[MAXSTRLENGTH];
char output_FileName_slow[MAXSTRLENGTH];
char output_FileName_ctrl[MAXSTRLENGTH];
char dateYMD_HMS[MAXSTRLENGTH];
MLOCAL time_t rawtime;
struct tm * timeinfo;
MLOCAL REAL32 CycleTime_ms;
MLOCAL UINT32 offset_newfile;
MLOCAL BOOL8 create_new_file_fast = FALSE;
MLOCAL BOOL8 create_new_file_slow = FALSE;
MLOCAL BOOL8 create_new_file_ctrl = FALSE;
MLOCAL CHAR Date_and_Time[24] = "2023.04.24_19:41:00:000";




MLOCAL UINT32 CycleCount = 0;


// MATLABCODEGEN: OpenField SVI Variables Definition

MLOCAL REAL64 WT3_Azimuth_Angle=0;
MLOCAL REAL64 WT3_RotorSpeed=0;
MLOCAL REAL64 WT3_Pitch_Blade_1=0;
MLOCAL REAL64 WT3_Pitch_Blade_2=0;
MLOCAL REAL64 WT3_Pitch_Blade_3=0;
MLOCAL REAL64 WT3_Flapwise_blade_1=0;
MLOCAL REAL64 WT3_Flapwise_blade_2=0;
MLOCAL REAL64 WT3_Flapwise_blade_3=0;
MLOCAL REAL64 WT3_Edgewise_blade_1=0;
MLOCAL REAL64 WT3_Edgewise_blade_2=0;
MLOCAL REAL64 WT3_Edgewise_blade_3=0;
MLOCAL REAL64 WT4_Flapwise_blade_1=0;
MLOCAL REAL64 WT4_Flapwise_blade_2=0;
MLOCAL REAL64 WT4_Flapwise_blade_3=0;
MLOCAL REAL64 WT4_Edgewise_blade_1=0;
MLOCAL REAL64 WT4_Edgewise_blade_2=0;
MLOCAL REAL64 WT4_Edgewise_blade_3=0;
MLOCAL REAL64 WT3_Torque=0;
MLOCAL REAL64 Air_Density=0;
MLOCAL REAL64 Met_Mast_Wind_Speed_At_Hub_height=0;
MLOCAL REAL64 Met_Mast_Wind_Direction_From_North=0;
MLOCAL REAL64 WT3_Nacelle_Wind_Speed=0;
MLOCAL REAL64 WT3_Nacelle_Wind_Misalignment=0;
MLOCAL REAL64 WT3_Nacelle_Direction_from_North=0;
MLOCAL REAL64 WT3_Power_Output=0;
MLOCAL REAL64 WT3_Turbine_Operational_Status=0;
MLOCAL REAL64 Flag_WT3_Turbine_Yaw_Input_Type=0;
MLOCAL REAL64 Flag_Wind_Farm_Control_from_TUM_PLC=0;
MLOCAL REAL64 Met_Mast_Wind_Speed_At_54_2=0;
MLOCAL REAL64 WT4_Torque=0;
MLOCAL REAL64 WT4_Azimuth_Angle=0;
MLOCAL REAL64 WT4_RotorSpeed=0;
MLOCAL REAL64 WT4_Pitch_Blade_1=0;
MLOCAL REAL64 WT4_Pitch_Blade_2=0;
MLOCAL REAL64 WT4_Pitch_Blade_3=0;
MLOCAL REAL64 WT4_Nacelle_Wind_Speed=0;
MLOCAL REAL64 WT4_Nacelle_Wind_Misalignment=0;
MLOCAL REAL64 WT4_Nacelle_Direction_from_North=0;
MLOCAL REAL64 WT4_Power_Output=0;
MLOCAL REAL64 WT4_Turbine_Operational_Status=0;
MLOCAL REAL64 WT3_Wind_Observer_Yaw_Misalignment=0;
MLOCAL REAL64 WT3_Wind_Farm_Control_Offset=0;
MLOCAL REAL64 Flag_Wind_Observer_Operational_Status=0;
MLOCAL REAL64 Flag_Wind_Farm_Control_Operational_Status=0;
MLOCAL REAL64 INFLW1_WS_Filtered=0;
MLOCAL REAL64 INFLW1_Wdir_Filtered=0;
MLOCAL REAL64 INFLW1_TurbInt_Filtered=0;
MLOCAL REAL64 INFLW1_ShearExp_Filtered=0;
MLOCAL UINT16 INFLW1_Status=0;
MLOCAL REAL64 INFLW1_OK=0;
MLOCAL REAL64 OFFSET1_OK=0;
MLOCAL UINT16 OFFSET1_Status=0;
MLOCAL REAL64 OFFSET1_Offset_deg=0;
MLOCAL REAL64 INFLW2_WS_Filtered=0;
MLOCAL REAL64 INFLW2_Wdir_Filtered=0;
MLOCAL REAL64 INFLW2_TurbInt_Filtered=0;
MLOCAL REAL64 INFLW2_ShearExp_Filtered=0;
MLOCAL UINT16 INFLW2_Status=0;
MLOCAL REAL64 INFLW2_OK=0;
MLOCAL REAL64 OFFSET2_OK=0;
MLOCAL UINT16 OFFSET2_Status=0;
MLOCAL REAL64 OFFSET2_Offset_deg=0;
MLOCAL REAL64 OFFSET3_Offset_deg=0;
MLOCAL UINT16 OFFSET3_Status=0;
MLOCAL REAL64 TOGGLER_WFCStatus=0;
MLOCAL REAL64 TOGGLER_ActiveCTRL=0;
MLOCAL UINT16 TOGGLER_Status=0;
MLOCAL REAL64 TOGGLER_Offset_Demanded=0;
MLOCAL REAL64 TOGGLER_TotWFCTime=0;
MLOCAL REAL64 TOGGLER_WFC1Time=0;
MLOCAL REAL64 TOGGLER_GreedyWFCTime=0;
MLOCAL REAL64 TOGGLER_WFC2Time=0;
MLOCAL REAL64 TOGGLER_WFC3Time=0;
MLOCAL REAL64 TOGGLER_Nacelle_MetMast_Offset=95.252;
MLOCAL REAL64 Flag_ManualSwitch_WFC=1;
MLOCAL REAL64 Flag_ManualSwitch_WFC_1=1;
MLOCAL REAL64 Flag_ManualSwitch_GreedyWFC=1;
MLOCAL REAL64 Flag_ManualSwitch_WFC_2=1;
MLOCAL REAL64 Flag_ManualSwitch_WFC_3=1;

// MATLABCODEGEN: CloseField SVI Variables Definition

/*
 * Global variables: Settings for application task
 * A reference to these settings must be registered in TaskList[], see below.
 * If no configuration group is being specified, all values must be set properly
 * in this initialization.
 */
MLOCAL TASK_PROPERTIES TaskProperties_aControl = {
    "aHOSTWFC_Ctrl",                 /* unique task name, maximum length 14 */
    "ControlTask",                      /* configuration group name */
    Control_Main,                       /* task entry function (function pointer) */
    0,                                  /* default task priority (->Task_CfgRead) */
    100,                               /* default task cycle time in ms (->Task_CfgRead) */
    0,                                  /* default task time base (->Task_CfgRead, 0=tick, 1=sync) */
    5,                                  /* default ratio of watchdog time / cycle time
                                         * (->Task_CfgRead) */
    10000,                              /* task stack size in bytes, standard size is 10000 */
    TRUE                                /* task uses floating point operations */
};

/*
 * Global variables: List of all application tasks
 * TaskList[] is being used for all task administration functions.
 */
MLOCAL TASK_PROPERTIES *TaskList[] = {
    &TaskProperties_aControl
};

/*
 * Global variables: SVI server variables list
 * The following variables will be exported to the SVI of the module.
 * Variables in SviGlobVarList will be directly accessible.
 * Those in SviVirtVarList via read/write function pointers.
 * The settings in the SviGlobVarList are:
 * Visible name of SVI variable, max. length = SVI_ADDRLEN
 * - Visible format and access rights (see defines SVI_F_xxx from svi.h)
 * - Size of variable in bytes
 * - Pointer to variable in the software project
 */
MLOCAL SVI_GLOBVAR SviGlobVarList[] = {
    {"CycleCounter", SVI_F_INOUT | SVI_F_UINT32, sizeof(UINT32), (UINT32 *) & CycleCount, 0, NULL,
     NULL}
    ,
    {"ModuleVersion", SVI_F_OUT | SVI_F_STRING, sizeof(hostwfc_Version),
     (UINT32 *) hostwfc_Version, 0, NULL, NULL}

,
    {"TimeStamp_UTC", SVI_F_OUT   | SVI_F_STRING, sizeof(Date_and_Time),  (UINT32 *) Date_and_Time},
     {"Recording/Flag_Record", SVI_F_INOUT   | SVI_F_UINT16, sizeof(UINT16), (UINT32*) &Recording_Start},




// MATLABCODEGEN: OpenField SVI Variables Coupling

{"WT3_Azimuth_Angle", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Azimuth_Angle, 0, NULL, NULL},
{"WT3_RotorSpeed", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_RotorSpeed, 0, NULL, NULL},
{"WT3_Pitch_Blade_1", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Pitch_Blade_1, 0, NULL, NULL},
{"WT3_Pitch_Blade_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Pitch_Blade_2, 0, NULL, NULL},
{"WT3_Pitch_Blade_3", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Pitch_Blade_3, 0, NULL, NULL},
{"WT3_Flapwise_blade_1", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Flapwise_blade_1, 0, NULL, NULL},
{"WT3_Flapwise_blade_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Flapwise_blade_2, 0, NULL, NULL},
{"WT3_Flapwise_blade_3", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Flapwise_blade_3, 0, NULL, NULL},
{"WT3_Edgewise_blade_1", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Edgewise_blade_1, 0, NULL, NULL},
{"WT3_Edgewise_blade_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Edgewise_blade_2, 0, NULL, NULL},
{"WT3_Edgewise_blade_3", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Edgewise_blade_3, 0, NULL, NULL},
{"WT4_Flapwise_blade_1", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Flapwise_blade_1, 0, NULL, NULL},
{"WT4_Flapwise_blade_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Flapwise_blade_2, 0, NULL, NULL},
{"WT4_Flapwise_blade_3", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Flapwise_blade_3, 0, NULL, NULL},
{"WT4_Edgewise_blade_1", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Edgewise_blade_1, 0, NULL, NULL},
{"WT4_Edgewise_blade_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Edgewise_blade_2, 0, NULL, NULL},
{"WT4_Edgewise_blade_3", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Edgewise_blade_3, 0, NULL, NULL},
{"WT3_Torque", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Torque, 0, NULL, NULL},
{"Air_Density", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Air_Density, 0, NULL, NULL},
{"Met_Mast_Wind_Speed_At_Hub_height", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Met_Mast_Wind_Speed_At_Hub_height, 0, NULL, NULL},
{"Met_Mast_Wind_Direction_From_North", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Met_Mast_Wind_Direction_From_North, 0, NULL, NULL},
{"WT3_Nacelle_Wind_Speed", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Nacelle_Wind_Speed, 0, NULL, NULL},
{"WT3_Nacelle_Wind_Misalignment", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Nacelle_Wind_Misalignment, 0, NULL, NULL},
{"WT3_Nacelle_Direction_from_North", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Nacelle_Direction_from_North, 0, NULL, NULL},
{"WT3_Power_Output", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Power_Output, 0, NULL, NULL},
{"WT3_Turbine_Operational_Status", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Turbine_Operational_Status, 0, NULL, NULL},
{"Flag_WT3_Turbine_Yaw_Input_Type", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_WT3_Turbine_Yaw_Input_Type, 0, NULL, NULL},
{"Flag_Wind_Farm_Control_from_TUM_PLC", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_Wind_Farm_Control_from_TUM_PLC, 0, NULL, NULL},
{"Met_Mast_Wind_Speed_At_54_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Met_Mast_Wind_Speed_At_54_2, 0, NULL, NULL},
{"WT4_Torque", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Torque, 0, NULL, NULL},
{"WT4_Azimuth_Angle", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Azimuth_Angle, 0, NULL, NULL},
{"WT4_RotorSpeed", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_RotorSpeed, 0, NULL, NULL},
{"WT4_Pitch_Blade_1", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Pitch_Blade_1, 0, NULL, NULL},
{"WT4_Pitch_Blade_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Pitch_Blade_2, 0, NULL, NULL},
{"WT4_Pitch_Blade_3", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Pitch_Blade_3, 0, NULL, NULL},
{"WT4_Nacelle_Wind_Speed", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Nacelle_Wind_Speed, 0, NULL, NULL},
{"WT4_Nacelle_Wind_Misalignment", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Nacelle_Wind_Misalignment, 0, NULL, NULL},
{"WT4_Nacelle_Direction_from_North", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Nacelle_Direction_from_North, 0, NULL, NULL},
{"WT4_Power_Output", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Power_Output, 0, NULL, NULL},
{"WT4_Turbine_Operational_Status", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT4_Turbine_Operational_Status, 0, NULL, NULL},
{"WT3_Wind_Observer_Yaw_Misalignment", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Wind_Observer_Yaw_Misalignment, 0, NULL, NULL},
{"WT3_Wind_Farm_Control_Offset", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &WT3_Wind_Farm_Control_Offset, 0, NULL, NULL},
{"Flag_Wind_Observer_Operational_Status", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_Wind_Observer_Operational_Status, 0, NULL, NULL},
{"Flag_Wind_Farm_Control_Operational_Status", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_Wind_Farm_Control_Operational_Status, 0, NULL, NULL},
{"INFLW1_WS_Filtered", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW1_WS_Filtered, 0, NULL, NULL},
{"INFLW1_Wdir_Filtered", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW1_Wdir_Filtered, 0, NULL, NULL},
{"INFLW1_TurbInt_Filtered", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW1_TurbInt_Filtered, 0, NULL, NULL},
{"INFLW1_ShearExp_Filtered", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW1_ShearExp_Filtered, 0, NULL, NULL},
{"INFLW1_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &INFLW1_Status, 0, NULL, NULL},
{"INFLW1_OK", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW1_OK, 0, NULL, NULL},
{"OFFSET1_OK", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &OFFSET1_OK, 0, NULL, NULL},
{"OFFSET1_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &OFFSET1_Status, 0, NULL, NULL},
{"OFFSET1_Offset_deg", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &OFFSET1_Offset_deg, 0, NULL, NULL},
{"INFLW2_WS_Filtered", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW2_WS_Filtered, 0, NULL, NULL},
{"INFLW2_Wdir_Filtered", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW2_Wdir_Filtered, 0, NULL, NULL},
{"INFLW2_TurbInt_Filtered", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW2_TurbInt_Filtered, 0, NULL, NULL},
{"INFLW2_ShearExp_Filtered", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW2_ShearExp_Filtered, 0, NULL, NULL},
{"INFLW2_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &INFLW2_Status, 0, NULL, NULL},
{"INFLW2_OK", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &INFLW2_OK, 0, NULL, NULL},
{"OFFSET2_OK", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &OFFSET2_OK, 0, NULL, NULL},
{"OFFSET2_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &OFFSET2_Status, 0, NULL, NULL},
{"OFFSET2_Offset_deg", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &OFFSET2_Offset_deg, 0, NULL, NULL},
{"OFFSET3_Offset_deg", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &OFFSET3_Offset_deg, 0, NULL, NULL},
{"OFFSET3_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &OFFSET3_Status, 0, NULL, NULL},
{"TOGGLER_WFCStatus", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_WFCStatus, 0, NULL, NULL},
{"TOGGLER_ActiveCTRL", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_ActiveCTRL, 0, NULL, NULL},
{"TOGGLER_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &TOGGLER_Status, 0, NULL, NULL},
{"TOGGLER_Offset_Demanded", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_Offset_Demanded, 0, NULL, NULL},
{"TOGGLER_TotWFCTime", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_TotWFCTime, 0, NULL, NULL},
{"TOGGLER_WFC1Time", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_WFC1Time, 0, NULL, NULL},
{"TOGGLER_GreedyWFCTime", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_GreedyWFCTime, 0, NULL, NULL},
{"TOGGLER_WFC2Time", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_WFC2Time, 0, NULL, NULL},
{"TOGGLER_WFC3Time", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_WFC3Time, 0, NULL, NULL},
{"TOGGLER_Nacelle_MetMast_Offset", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &TOGGLER_Nacelle_MetMast_Offset, 0, NULL, NULL},
{"Flag_ManualSwitch_WFC", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_ManualSwitch_WFC, 0, NULL, NULL},
{"Flag_ManualSwitch_WFC_1", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_ManualSwitch_WFC_1, 0, NULL, NULL},
{"Flag_ManualSwitch_GreedyWFC", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_ManualSwitch_GreedyWFC, 0, NULL, NULL},
{"Flag_ManualSwitch_WFC_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_ManualSwitch_WFC_2, 0, NULL, NULL},
{"Flag_ManualSwitch_WFC_3", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &Flag_ManualSwitch_WFC_3, 0, NULL, NULL},

// MATLABCODEGEN: CloseField SVI Variables Coupling

};

/**
********************************************************************************
* @brief Main entry function of the aTask of the application.
*        The input parameter is being passed by the task spawn call.
*
* @param[in]  pointer to task properties data structure
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
MLOCAL VOID Control_Main(TASK_PROPERTIES * pTaskData)
{
    /* Initialization upon task entry */
    Control_CycleInit();

    /*
     * This loop is executed endlessly
     * as long as there is no request to quit the task
     */
    while (!pTaskData->Quit)
    {
        /* cycle start administration */
        Control_CycleStart();

        /* operational code */
        Control_Cycle();

        /* cycle end administration */
        Control_CycleEnd(pTaskData);
    }
}

/**
********************************************************************************
* @brief Administration code to be called once before first cycle start.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
MLOCAL VOID Control_CycleInit(VOID)
{
    CycleTime_ms = TaskProperties_aControl.CycleTime_ms;
    offset_newfile = newfile_time_s / CycleTime_ms * 1000;




    /* TODO: add what is necessary before cyclic operation starts */

}

/**
********************************************************************************
* @brief Administration code to be called once at each task cycle start.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
MLOCAL VOID Control_CycleStart(VOID)
{
SINT32 ret;

if (SviClt_Read() < 0)
    LOG_W(0, "Control_CycleStart", "Could not read all SVI variables!");


// MATLABCODEGEN: OpenField Assign ITF Variables to HOST SVI

WT3_Azimuth_Angle = tumitfc_cw2InAr[1];
WT3_RotorSpeed = tumitfc_cw2InAr[2];
WT3_Pitch_Blade_1 = tumitfc_cw2InAr[3];
WT3_Pitch_Blade_2 = tumitfc_cw2InAr[4];
WT3_Pitch_Blade_3 = tumitfc_cw2InAr[5];
WT3_Flapwise_blade_1 = tumitfc_cw2InAr[12];
WT3_Flapwise_blade_2 = tumitfc_cw2InAr[13];
WT3_Flapwise_blade_3 = tumitfc_cw2InAr[14];
WT3_Edgewise_blade_1 = tumitfc_cw2InAr[15];
WT3_Edgewise_blade_2 = tumitfc_cw2InAr[16];
WT3_Edgewise_blade_3 = tumitfc_cw2InAr[17];
WT4_Flapwise_blade_1 = tumitfc_cw2InAr[24];
WT4_Flapwise_blade_2 = tumitfc_cw2InAr[25];
WT4_Flapwise_blade_3 = tumitfc_cw2InAr[26];
WT4_Edgewise_blade_1 = tumitfc_cw2InAr[27];
WT4_Edgewise_blade_2 = tumitfc_cw2InAr[28];
WT4_Edgewise_blade_3 = tumitfc_cw2InAr[29];
WT3_Torque = tumitfc_cw2InAr[30];
Air_Density = tumitfc_cw2InAr[31];
Met_Mast_Wind_Speed_At_Hub_height = tumitfc_cw2InAr[32];
Met_Mast_Wind_Direction_From_North = tumitfc_cw2InAr[33];
WT3_Nacelle_Wind_Speed = tumitfc_cw2InAr[34];
WT3_Nacelle_Wind_Misalignment = tumitfc_cw2InAr[35];
WT3_Nacelle_Direction_from_North = tumitfc_cw2InAr[36];
WT3_Power_Output = tumitfc_cw2InAr[37];
WT3_Turbine_Operational_Status = tumitfc_cw2InAr[38];
Flag_WT3_Turbine_Yaw_Input_Type = tumitfc_cw2InAr[39];
Flag_Wind_Farm_Control_from_TUM_PLC = tumitfc_cw2InAr[40];
Met_Mast_Wind_Speed_At_54_2 = tumitfc_cw2InAr[46];
WT4_Torque = tumitfc_cw2InAr[47];
WT4_Azimuth_Angle = tumitfc_cw2InAr[48];
WT4_RotorSpeed = tumitfc_cw2InAr[49];
WT4_Pitch_Blade_1 = tumitfc_cw2InAr[50];
WT4_Pitch_Blade_2 = tumitfc_cw2InAr[51];
WT4_Pitch_Blade_3 = tumitfc_cw2InAr[52];
WT4_Nacelle_Wind_Speed = tumitfc_cw2InAr[53];
WT4_Nacelle_Wind_Misalignment = tumitfc_cw2InAr[54];
WT4_Nacelle_Direction_from_North = tumitfc_cw2InAr[55];
WT4_Power_Output = tumitfc_cw2InAr[56];
WT4_Turbine_Operational_Status = tumitfc_cw2InAr[57];

// MATLABCODEGEN: CloseField Assign ITF Variables to HOST SVI

// MATLABCODEGEN: OpenField Assign ITF output Variables to HOST SVI

tumitfc_cw2OutAr[0] = WT3_Wind_Observer_Yaw_Misalignment;
tumitfc_cw2OutAr[1] = WT3_Wind_Farm_Control_Offset;
tumitfc_cw2OutAr[2] = Flag_Wind_Observer_Operational_Status;
tumitfc_cw2OutAr[3] = Flag_Wind_Farm_Control_Operational_Status;

// MATLABCODEGEN: CloseField Assign ITF output Variables to HOST SVI



time ( &rawtime );
timeinfo = gmtime( &rawtime );
sprintf(Date_and_Time, "%d.%02d.%02d_%02d:%02d:%02d:%03lld", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, Time_ms1970 % 1000);

//    filename_hostdata
sprintf(dateYMD_HMS,"%d%02d%02d_%02d%02d%02d", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
sprintf(output_FileName_fast,"%s%s_%s_FAST.dat", output_path, dateYMD_HMS, output_FileName_main);
sprintf(output_FileName_slow,"%s%s_%s_SLOW.dat", output_path, dateYMD_HMS, output_FileName_main);
sprintf(output_FileName_ctrl,"%s%s_%s_CTRL.dat", output_path, dateYMD_HMS, output_FileName_main);


// Check if Recording_Start has changed, and if it went off i should close all open files
if (Recording_Start == FALSE && Recording_Start_prev == TRUE ) {
    if (pFileFast != NULL) {fclose(pFileFast);}
    if (pFileSlow != NULL) {fclose(pFileSlow);}
    if (pFileCtrl != NULL) {fclose(pFileCtrl);}
} else if (Recording_Start == TRUE && Recording_Start_prev == FALSE ) { // if i just turned on the recording, create new files
    CycleCount_new_file = CycleCount;
}

// Shall we generate new files? (has time elapsed?)
if (CycleCount >= CycleCount_new_file && Recording_Start)
{
    create_new_file_fast = TRUE;
    create_new_file_slow = TRUE;
    create_new_file_ctrl = TRUE;

    CycleCount_new_file = CycleCount + offset_newfile;
}


// manage fast file
if ((CycleCount % FAST_FREQ_RATIO) == 0 && Recording_Start )  {

    if (create_new_file_fast) {
        if (pFileFast != NULL) {fclose(pFileFast);}
        pFileFast = fopen( output_FileName_fast, "w");
        if (pFileFast == NULL)
        {
            LOG_W(0, "Control_CycleStart", "Cannot open fast file!");
        } else {
        ret = write_header_fast();
        }
        create_new_file_fast = FALSE;
    };

    if (pFileFast != NULL) ret = write_output_fast();
    else LOG_W(0, "Control_CycleStart", "Cannot write into fast file!");

};

if ((CycleCount % SLOW_FREQ_RATIO) == 0) {

    if (create_new_file_slow) {
        if (pFileSlow != NULL) {fclose(pFileSlow);}
        pFileSlow = fopen( output_FileName_slow, "w");
        if (pFileSlow == NULL)
        {
            LOG_W(0, "Control_CycleStart", "Cannot open slow file!");
        } else {
        ret = write_header_slow();
        }
        create_new_file_slow = FALSE;
    };

    if (pFileSlow != NULL) ret = write_output_slow();
    else LOG_W(0, "Control_CycleStart", "Cannot write into slow file!");

};

if ((CycleCount % CTRL_FREQ_RATIO) == 0) {

    if (create_new_file_ctrl) {
        if (pFileCtrl != NULL) {fclose(pFileCtrl);}
        pFileCtrl = fopen( output_FileName_ctrl, "w");
        if (pFileCtrl == NULL)
        {
            LOG_W(0, "Control_CycleStart", "Cannot open ctrl file!");
        } else {
        ret = write_header_ctrl();
        }
        create_new_file_ctrl = FALSE;
    };

    if (pFileCtrl != NULL) ret = write_output_ctrl();
    else LOG_W(0, "Control_CycleStart", "Cannot write into ctrl file!");

};




    /* TODO: add what is necessary at each cycle start */

}

/**
********************************************************************************
* @brief Cyclic application code.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
MLOCAL VOID Control_Cycle(VOID)
{
    UINT32  Time_us;

    /* TODO: add operational code to be called in this task */

    /* Increase cycle counter */
    CycleCount++;

    /*
     * In this example, all values are read in a separated function.
     * It is also possible to read values on demand only.
     */
    if (SviClt_Example(&Time_us) < 0)
        LOG_W(0, "Control_Cycle", "Could not read SVI variable");
    else if (PrintTime)
    {
        LOG_I(0, "Control_Cycle", "%u microseconds since CPU boot ...", Time_us);
        PrintTime = FALSE;
    }

}

/**
********************************************************************************
* @brief Administration code to be called at each task cycle end
*
* @param[in]  pointer to task properties data structure
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
MLOCAL VOID Control_CycleEnd(TASK_PROPERTIES * pTaskData)
{
    SviClt_Write();



    Recording_Start_prev = Recording_Start;




    /* TODO: add what is to be called at each cycle end */

    /*
     * This is the very end of the cycle
     * Delay task in order to match desired cycle time
     */
    Task_WaitCycle(pTaskData);
}

/**
********************************************************************************
* @brief Performs the second phase of the module initialization.
* 		  Called at "End Of Init" by the bTask.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
SINT32 hostwfc_AppEOI(VOID)
{

    /* do while(0), to be left as soon as there is an error */
    do
    {
        /* TODO: set module info string, maximum length is SMI_DESCLEN_A */
        snprintf(hostwfc_ModuleInfoDesc, sizeof(hostwfc_ModuleInfoDesc), "TODO: set application specific module info string");

        /* TODO: add all initializations required by your application */

        /* Initialize SVI access to variables of other software modules */
        if (SviClt_Init() < 0)
            break;

        /* Start all application tasks listed in TaskList */
        if (Task_CreateAll() < 0)
            break;

        /* At this point, all init actions are done successfully */
        return (OK);
    }
    while (0);

    /*
     * At this point, an init action returned an error.
     * The application code is being de-initialized.
     */
    hostwfc_AppDeinit();
    return (ERROR);
}

/**
********************************************************************************
* @brief Frees all resources of the application
*        Called at De-Init of the module by the bTask.
*        The function does not quit on an error.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
VOID hostwfc_AppDeinit(VOID)
{

    /* TODO: Free all resources which have been allocated by the application */

    /* Delete all application tasks listed in TaskList */
    Task_DeleteAll();

    /* Delete all SVI client access data */
    SviClt_Deinit();

}

/**
********************************************************************************
* @brief Reads the settings from configuration file mconfig
*        for all tasks registered in TaskList[].
*        The task name in TaskList[] is being used as configuration group name.
*        The initialization values in TaskList[] are being used as default values.
*        For general configuration data, hostwfc_CfgParams is being used.
*        Being called by hostwfc_CfgRead.
*        All parameters are stored in the task properties data structure.
*        All parameters are being treated as optional.
*        There is no limitation checking of the parameters, the limits are being
*        specified in the cru and checked by the configurator.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
MLOCAL SINT32 Task_CfgRead(VOID)
{
    UINT32  idx;
    UINT32  NbOfTasks = sizeof(TaskList) / sizeof(TASK_PROPERTIES *);
    SINT32  ret;
    CHAR    section[PF_KEYLEN_A];
    CHAR    group[PF_KEYLEN_A];
    CHAR    key[PF_KEYLEN_A];
    SINT32  TmpVal;
    CHAR    TmpStrg[32];
    UINT32  Error = FALSE;
    CHAR    Func[] = "Task_CfgRead";

    /* section name is the application name, for all tasks */
    snprintf(section, sizeof(section), hostwfc_BaseParams.AppName);

    /* For all application tasks listed in TaskList */
    for (idx = 0; idx < NbOfTasks; idx++)
    {
        if (!TaskList[idx])
        {
            LOG_E(0, Func, "Invalid task properties pointer in task list entry #%d!", idx);
            Error = TRUE;
            continue;
        }

        /* group name is specified in the task properties */
        snprintf(group, sizeof(group), TaskList[idx]->CfgGroup);

        /* if no group name has been specified: skip configuration reading for this task */
        if (strlen(group) < 1)
        {
            LOG_I(0, Func, "Could not find task configuration for task '%s' in mconfig ",
                  TaskList[idx]->Name);
            continue;
        }

        /*
         * Read the desired value for the task cycle time.
         * If the keyword has not been found, the initialization value remains
         * in the task properties.
         */
        snprintf(key, sizeof(key), "CycleTime");
        snprintf(TmpStrg, sizeof(TmpStrg), "%f", TaskList[idx]->CycleTime_ms);
        ret = pf_GetStrg(section, group, key, "", (CHAR *) & TmpStrg, sizeof(TmpStrg),
                         hostwfc_BaseParams.CfgLine, hostwfc_BaseParams.CfgFileName);
        /* keyword has been found */
        if (ret >= 0)
        {
            *((REAL32 *) & TaskList[idx]->CycleTime_ms) = atof(TmpStrg);
        }
        /* keyword has not been found */
        else
        {
            LOG_W(0, Func, "Missing configuration parameter '[%s](%s)%s'", section, group, key);
            LOG_W(0, Func, " -> using initialization value of %f ms", TaskList[idx]->CycleTime_ms);
        }

        /*
         * Read the desired value for the task priority.
         * If the keyword has not been found, the initialization value remains
         * in the task properties.
         * As an additional fall back, the priority in the base parms will be used.
         */
        snprintf(key, sizeof(key), "Priority");
        ret = pf_GetInt(section, group, key, TaskList[idx]->Priority, &TmpVal,
                        hostwfc_BaseParams.CfgLine, hostwfc_BaseParams.CfgFileName);
        /* keyword has been found */
        if (ret >= 0)
        {
            TaskList[idx]->Priority = TmpVal;
        }
        /* keyword has not been found */
        else
        {
            LOG_W(0, Func, "Missing configuration parameter '[%s](%s)%s'", section, group, key);
            if (TaskList[idx]->Priority == 0)
            {
                TaskList[idx]->Priority = hostwfc_BaseParams.DefaultPriority;
                LOG_W(0, Func, " -> using base parms value of %d", TaskList[idx]->Priority);
            }
            else
                LOG_W(0, Func, " -> using initialization value of %d", TaskList[idx]->Priority);
        }

        /*
         * Read the software watchdog time ratio.
         * If the keyword has not been found, the initialization value remains
         * in the task properties.
         */
        snprintf(key, sizeof(key), "WatchdogRatio");
        ret = pf_GetInt(section, group, key, TaskList[idx]->WDogRatio, &TmpVal,
                        hostwfc_BaseParams.CfgLine, hostwfc_BaseParams.CfgFileName);
        /* keyword has been found */
        if (ret >= 0)
        {
            TaskList[idx]->WDogRatio = TmpVal;
        }
        /* keyword has not been found */
        else
        {
            LOG_W(0, Func, "Missing configuration parameter '[%s](%s)%s'", section, group, key);
            LOG_W(0, Func, " -> using initialization value of %d", TaskList[idx]->WDogRatio);
        }

        /*
         * Read the time base for the cycle time.
         * If the keyword has not been found, the initialization value remains
         * in the task properties.
         */
        snprintf(key, sizeof(key), "TimeBase");
        ret = pf_GetInt(section, group, key, TaskList[idx]->TimeBase, &TmpVal,
                        hostwfc_BaseParams.CfgLine, hostwfc_BaseParams.CfgFileName);
        /* keyword has been found */
        if (ret >= 0)
        {
            TaskList[idx]->TimeBase = TmpVal;
        }
        /* keyword has not been found */
        else
        {
            LOG_W(0, Func, "Missing configuration parameter '[%s](%s)%s'", section, group, key);
            LOG_W(0, Func, " -> using initialization value of %d", TaskList[idx]->TimeBase);
        }
    }

    /* Evaluate overall error flag */
    if (Error)
        return (ERROR);
    else
        return (OK);
}

/**
********************************************************************************
* @brief Starts all tasks which are registered in the global task list
*        - task watchdog is being created if specified
*        - priority is being checked and corrected if necessary
*        - semaphore for cycle timing is being created
*        - sync session is being started if necessary
*        - sync ISR is being attached if necessary
*        If there is an error creating a task, no further tasks will be started.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
MLOCAL SINT32 Task_CreateAll(VOID)
{
    UINT32  idx;
    UINT8   TaskName[M_TSKNAMELEN_A];
    UINT32  NbOfTasks = sizeof(TaskList) / sizeof(TASK_PROPERTIES *);
    UINT32  TaskOptions;
    UINT32  wdogtime_us;
    CHAR    Func[] = "Task_CreateAll";

    /* For all application tasks listed in TaskList */
    for (idx = 0; idx < NbOfTasks; idx++)
    {
        if (!TaskList[idx])
        {
            LOG_E(0, Func, "Invalid task properties pointer!");
            return (ERROR);
        }

        /* Initialize what is necessary */
        TaskList[idx]->SyncSessionId = ERROR;
        TaskList[idx]->TaskId = ERROR;
        TaskList[idx]->WdogId = 0;
        TaskList[idx]->Quit = FALSE;

        /* Create software watchdog if required */
        if (TaskList[idx]->WDogRatio > 0)
        {
            /* check watchdog ratio, minimum useful value is 2 */
            if (TaskList[idx]->WDogRatio < 3)
            {
                TaskList[idx]->WDogRatio = 3;
                LOG_W(0, Func, "Watchdog ratio increased to 3!");
            }

            wdogtime_us = (TaskList[idx]->CycleTime_ms * 1000) * TaskList[idx]->WDogRatio;
            TaskList[idx]->WdogId = sys_WdogCreate(hostwfc_AppName, wdogtime_us);
            if (TaskList[idx]->WdogId == 0)
            {
                LOG_E(0, Func, "Could not create watchdog!");
                return (ERROR);
            }
        }

        /* Create binary semaphore for cycle timing */
        TaskList[idx]->CycleSema = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
        if (!TaskList[idx]->CycleSema)
        {
            LOG_E(0, Func, "Could not create cycle timing semaphore for task '%s'!",
                  TaskList[idx]->Name);
            return (ERROR);
        }

        /* Initialize task cycle timing infrastructure */
        Task_InitTiming(TaskList[idx]);

        /* In case the priority has not been properly set */
        if (TaskList[idx]->Priority == 0)
        {
            LOG_E(0, Func, "Invalid priority for task '%s'", TaskList[idx]->Name);
            return (ERROR);
        }

        /* make sure task name string is terminated */
        TaskList[idx]->Name[M_TSKNAMELEN_A - 2] = 0;

        /* If no task name has been set: use application name and index */
        if (strlen(TaskList[idx]->Name) < 1)
            snprintf(TaskList[idx]->Name, sizeof(TaskList[idx]->Name), "a%s_%d", hostwfc_AppName, idx + 1);

        snprintf(TaskName, sizeof(TaskList[idx]->Name), "%s", TaskList[idx]->Name);

        /* Task options */
        TaskOptions = 0;
        if (TaskList[idx]->UseFPU)
            TaskOptions |= VX_FP_TASK;

        /* Spawn task with properties set in task list */
        TaskList[idx]->TaskId = sys_TaskSpawn(hostwfc_AppName, TaskName,
                                              TaskList[idx]->Priority, TaskOptions,
                                              TaskList[idx]->StackSize,
                                              (FUNCPTR) TaskList[idx]->pMainFunc, TaskList[idx]);

        /* Check if task has been created successfully */
        if (TaskList[idx]->TaskId == ERROR)
        {
            LOG_E(0, Func, "Error in sys_TaskSpawn for task '%s'!", TaskName);
            return (ERROR);
        }
    }

    /* At this point, all tasks have been started successfully */
    return (OK);
}

/**
********************************************************************************
* @brief Deletes all tasks which are registered in the global task list
*        Undo for all operations in Task_CreateAll
*        The function will not be left upon an error.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
MLOCAL VOID Task_DeleteAll(VOID)
{
    UINT32  idx;
    UINT32  NbOfTasks = sizeof(TaskList) / sizeof(TASK_PROPERTIES *);
    UINT32  RequestTime;
    CHAR    Func[] = "Task_DeleteAll";

    /*
     * Delete software watchdog if present
     * This must be done first, because tasks will end their cyclic operation
     * and thus won't trigger their watchdogs any more.
     */
    for (idx = 0; idx < NbOfTasks; idx++)
    {
        if (TaskList[idx]->WdogId)
            sys_WdogDelete(TaskList[idx]->WdogId);
    }

    /*
     * Set quit request for all existing tasks
     * This should make tasks complete their cycle and quit operation.
     */
    for (idx = 0; idx < NbOfTasks; idx++)
        TaskList[idx]->Quit = TRUE;

    /*
     * Give all cycle semaphores of listed tasks
     * This wakes up all tasks and thus speeds up the completion.
     */
    for (idx = 0; idx < NbOfTasks; idx++)
    {
        if (TaskList[idx]->CycleSema)
            semGive(TaskList[idx]->CycleSema);
    }

    /* Take a time stamp for the timeout check */
    RequestTime = m_GetProcTime();

    /*
     * Wait for all tasks to quit their cycle.
     * Apply a timeout of 500ms
     * Wait one tick in case of missing task quit
     */
    do
    {
        UINT32  AllTasksQuitted = TRUE;

        /* allow one tick for tasks to complete */
        taskDelay(1);

        /* Check if all tasks have terminated their cycles */
        for (idx = 0; idx < NbOfTasks; idx++)
            AllTasksQuitted &= (taskIdVerify(TaskList[idx]->TaskId) == ERROR);

        /* If all tasks have terminated themselves */
        if (AllTasksQuitted)
        {
            if (hostwfc_BaseParams.DebugMode & APP_DBG_INFO1)
                LOG_I(0, Func, "All tasks have terminated by themselves");
            break;
        }
        /* If timeout waiting for task self termination is over */
        else if ((m_GetProcTime() - RequestTime) > 500000)
        {
            LOG_W(0, Func, "Timeout at waiting for tasks to terminate by themselves");
            break;
        }
    }
    while (TRUE);

    /* Cleanup resources and delete all remaining tasks */
    for (idx = 0; idx < NbOfTasks; idx++)
    {
        /* Stop sync session if present and detach ISR */
        if (TaskList[idx]->SyncSessionId >= 0)
        {
            LOG_I(0, Func, "Stopping sync session for task %s", TaskList[idx]->Name);
            mio_StopSyncSession(TaskList[idx]->SyncSessionId);
        }

        /* Delete semaphore for cycle timing */
        if (TaskList[idx]->CycleSema)
        {
            if (semDelete(TaskList[idx]->CycleSema) < 0)
                LOG_W(0, Func, "Could not delete cycle semaphore of task %s!", TaskList[idx]->Name);
            else
            	TaskList[idx]->CycleSema = 0;
        }

        /* Remove application tasks which still exist */
        if (taskIdVerify(TaskList[idx]->TaskId) == OK)
        {
            if (taskDelete(TaskList[idx]->TaskId) == ERROR)
                LOG_E(0, Func, "Could not delete task %s!", TaskList[idx]->Name);
            else
                LOG_W(0, Func, "Task %s had to be deleted!", TaskList[idx]->Name);

            TaskList[idx]->TaskId = ERROR;
        }
    }
}

/**
********************************************************************************
* @brief Initializes infrastructure for task timing
*
* @param[in]  pointer to task properties data structure
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
MLOCAL SINT32 Task_InitTiming(TASK_PROPERTIES * pTaskData)
{
    CHAR    Func[] = "Task_InitTiming";

    if (!pTaskData)
    {
        LOG_E(0, Func, "Invalid input pointer!");
        return (ERROR);
    }

    /* independent of timing model */
    pTaskData->NbOfCycleBacklogs = 0;
    pTaskData->NbOfSkippedCycles = 0;

    /* depending on timing model */
    switch (pTaskData->TimeBase)
    {
            /* Tick based timing */
        case 0:
            return (Task_InitTiming_Tick(pTaskData));
            /* Sync based timing */
        case 1:
            pTaskData->SyncSessionId = ERROR;
            return (Task_InitTiming_Sync(pTaskData));
            /* Undefined */
        default:
            LOG_E(0, Func, "Unknown timing model!");
            return (ERROR);
    }
}

/**
********************************************************************************
* @brief Initializes infrastructure for task timing with tick timer
*
* @param[in]  pointer to task properties data structure
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
MLOCAL SINT32 Task_InitTiming_Tick(TASK_PROPERTIES * pTaskData)
{
    REAL32  TmpReal;
    CHAR    Func[] = "Task_InitTiming_Tick";

    if (!pTaskData)
    {
        LOG_E(0, Func, "Invalid input pointer!");
        return (ERROR);
    }

    /*
     * Calculate and check cycle time in ticks as integer value
     */
    TmpReal = ((pTaskData->CycleTime_ms / 1000.0) * sysClkRateGet()) + 0.5;
    pTaskData->CycleTime = (UINT32) TmpReal;

    /* If cycle time is less than a full tick */
    if (pTaskData->CycleTime < 1)
    {
        pTaskData->CycleTime = 1;
        LOG_W(0, Func, "Cycle time too small for tick rate %d, increased to 1 tick!",
              sysClkRateGet());
    }

    /* Take first cycle start time stamp */
    pTaskData->PrevCycleStart = tickGet();

    /* Initialize cycle time grid */
    pTaskData->NextCycleStart = tickGet() + pTaskData->CycleTime;

    return (OK);
}

/**
********************************************************************************
* @brief Initializes infrastructure for task timing with sync event.
*
* @param[in]  pointer to task properties data structure
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. Error
*******************************************************************************/
MLOCAL SINT32 Task_InitTiming_Sync(TASK_PROPERTIES * pTaskData)
{
    SINT32  ret;
    REAL32  SyncCycle_us, TmpReal;
    SYS_CPUINFO CpuInfo;
    CHAR    Func[] = "Task_InitTiming_Sync";

    if (!pTaskData)
    {
        LOG_E(0, Func, "Invalid input pointer!");
        return (ERROR);
    }

    /* Start sync session for this module (multiple starts are possible) */
    pTaskData->SyncSessionId = mio_StartSyncSession(hostwfc_AppName);
    if (pTaskData->SyncSessionId < 0)
    {
        LOG_E(0, Func, "Could not start sync session for task '%s'!", pTaskData->Name);
        return (ERROR);
    }

    /* Get cpu info, contains sync timer settings (always returns OK) */
    sys_GetCpuInfo(&CpuInfo);

    /* Calculate and check period time of sync timer */
    SyncCycle_us = CpuInfo.pExtCpuInfo->SyncHigh + CpuInfo.pExtCpuInfo->SyncLow;
    if ((SyncCycle_us == 0) || (CpuInfo.pExtCpuInfo->SyncHigh == 0)
        || (CpuInfo.pExtCpuInfo->SyncLow == 0))
    {
        LOG_E(0, Func, "System sync configuration invalid, can't use sync for task '%s'!",
              pTaskData->Name);
        return (ERROR);
    }

    /* Calculate multiple of specified task cycle time */
    TmpReal = ((pTaskData->CycleTime_ms * 1000) / SyncCycle_us) + 0.5;
    pTaskData->CycleTime = TmpReal;

    /* If cycle time is less than a full sync */
    if (pTaskData->CycleTime < 1)
    {
        pTaskData->CycleTime = 1;
        LOG_W(0, Func, "Cycle time too small for sync cycle %d us, increased to 1 sync!",
              SyncCycle_us);
    }

    /*
     * For application tasks,
     * MIO_SYNC_IN (falling edge of sync signal) is the normal option.
     */
    pTaskData->SyncEdge = MIO_SYNC_IN;

    /*
     * Attach semGive to sync event
     * -> semGive will be called according to the sync attach settings below.
     * -> semGive will give the semaphore pTaskData->CycleSema.
     * -> the task will be triggered as soon as this semaphore is given.
     */
    ret = mio_AttachSync(pTaskData->SyncSessionId,      /* from mio_StartSyncSession */
                         pTaskData->SyncEdge,   /* selection of sync edge */
                         pTaskData->CycleTime,  /* number of sync cycles */
                         (VOID *) semGive,      /* register semGive as ISR */
                         (UINT32) pTaskData->CycleSema);        /* semaphore id for semGive */
    if (ret < 0)
    {
        LOG_W(0, Func, "Could not attach to sync for task '%s'!", pTaskData->Name);
        if (pTaskData->SyncSessionId >= 0)
        	mio_StopSyncSession(pTaskData->SyncSessionId);
        pTaskData->SyncSessionId = ERROR;
        return (ERROR);
    }

    return (OK);
}

/**
********************************************************************************
* @brief Performs the necessary wait time for the specified cycle.
*        The wait time results from cycle time minus own run time.
*        NOTE: The time unit depends on the used time base (ticks or sync periods).
*
* @param[in]  pointer to task properties data structure
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
MLOCAL VOID Task_WaitCycle(TASK_PROPERTIES * pTaskData)
{
    UINT32  PrevCycleStart = 0;
    UINT32  NextCycleStart = 0;
    UINT32  CycleTime = 0;
    UINT32  TimeToWait = 0;
    UINT32  SkipNow = 0;
    UINT32  TimeNow = 0;
    UINT32  Backlog = 0;
    UINT32  MaxBacklog = 0;
    UINT32  CyclesSkipped = 0;

    /* Emergency behavior in case of missing task settings */
    if (!pTaskData)
    {
        LOG_E(0, "Task_WaitCycle", "Invalid input pointer, using alternative taskDelay(1000)");
        taskDelay(1000);
        return;
    }

    /* Trigger software watchdog if existing */
    if (pTaskData->WdogId)
        sys_WdogTrigg(pTaskData->WdogId);

    /*
     * Handle tick based cycle timing ("Time" unit is ticks)
     */
    if (pTaskData->TimeBase == 0)
    {
        /* Use local variables to make calculation as compressed as possible */
        PrevCycleStart = pTaskData->PrevCycleStart;
        NextCycleStart = pTaskData->NextCycleStart;
        CycleTime = pTaskData->CycleTime;
        MaxBacklog = CycleTime * 2;

        /* Calculate the time to wait before the next cycle can start. */
        NextCycleStart = PrevCycleStart + CycleTime;
        PrevCycleStart = NextCycleStart;

        /*
         * As soon as the current time stamp has been taken,
         * the code until semTake processing should be kept as short as possible,
         * so that the probability of being interrupted is as small as possible.
         */
        TimeNow = tickGet();

        /* This is the amount of until the next scheduled cycle start. */
        TimeToWait = NextCycleStart - TimeNow;

        /* Limit wait time to minimum 1 */
        if (!TimeToWait)
            TimeToWait++;

        /*
         * As long as the next scheduled cycle start lies in the future,
         * the resulting wait time must be smaller than the cycle time.
         * If the resulting wait time is higher than the cycle time,
         * the next scheduled cycle start already lies in the past.
         * This means that there is a cycle backlog.
         * NOTE: since the wait time is an unsigned value, a negative difference
         * is being interpreted as a large positive value.
         */
        if (TimeToWait > CycleTime)
        {
            /* Calculate cycle backlog */
            Backlog = TimeNow - NextCycleStart;

            /* As long as the backlog is below the limit */
            if (Backlog <= MaxBacklog)
            {
                /* Try to catch, but still use a small task delay */
                TimeToWait = 1;
            }
            /* If the backlog is beyond the limit */
            else
            {
                /* Skip the backlog and recalculate next cycle start */
                SkipNow = (Backlog / CycleTime) + 1;
                NextCycleStart = NextCycleStart + (SkipNow * CycleTime);
                PrevCycleStart = NextCycleStart;
                TimeToWait = NextCycleStart - TimeNow;
                CyclesSkipped += SkipNow;
            }
        }
    }

    /*
     * Handle sync based cycle timing ("Time" unit is syncs)
     */
    else if (pTaskData->TimeBase == 1)
    {
        /*
         * In case of sync timing, it is assumed, that the sync interrupt
         * directly determines the cycle time.
         * It would also be possible to use a multiple of sync's as cycle time.
         * The logic necessary for that is not yet implemented.
         */
        TimeToWait = WAIT_FOREVER;
    }

    /* Register cycle end in system timing statistics */
    sys_CycleEnd();

    /*
     * Wait for the calculated number of time units
     * by taking the cycle semaphore with a calculated timeout
     */
    semTake(pTaskData->CycleSema, TimeToWait);

    /*
     * Waiting for the cycle semaphore has now timed out in case of tick
     * or been given in case of sync.
     */

    /* Register cycle start in system timing statistics */
    sys_CycleStart();

    /*
     * The above logic uses local variables in order to keep the processing short.
     * Some of these local variables must be rescued for the next call of this
     * function.
     */
    pTaskData->PrevCycleStart = PrevCycleStart;
    pTaskData->NextCycleStart = NextCycleStart;
    pTaskData->NbOfSkippedCycles += CyclesSkipped;
    if (Backlog)
        pTaskData->NbOfCycleBacklogs++;

    /*
     * Consideration of software module state
     * If the module is in stop or eoi state,
     * all cyclic tasks of this module shall be stopped.
     * If the software module receives the RpcStart call,
     * it will give the state semaphore, and all tasks will continue.
     */
    if ((hostwfc_ModState == RES_S_STOP) || (hostwfc_ModState == RES_S_EOI))
    {
        /* Disable software watchdog if present */
        if (pTaskData->WdogId)
            sys_WdogDisable(pTaskData->WdogId);

        LOG_I(0, "Task_WaitCycle", "Stopping task '%s' due to module stop", pTaskData->Name);

        /*
         * semaphore will be given by SMI server with calls
         * RpcStart or RpcEndOfInit
         */
        semTake(hostwfc_StateSema, WAIT_FOREVER);
    }
}

/**
********************************************************************************
* @brief Initializes the module configuration data structure
*        with the values obtained in the module init.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
MLOCAL VOID hostwfc_CfgInit(VOID)
{
    /* Configuration file name (profile name) */
    strncpy(hostwfc_BaseParams.CfgFileName, hostwfc_ProfileName, M_PATHLEN);

    /* Application name */
    strncpy(hostwfc_BaseParams.AppName, hostwfc_AppName, M_MODNAMELEN);

    /* Line number in configuration file (used as start line for searching) */
    hostwfc_BaseParams.CfgLine = hostwfc_CfgLine;

    /* Worker task priority from module base parameters (BaseParms) */
    hostwfc_BaseParams.DefaultPriority = hostwfc_AppPrio;

    /* Debug mode from module base parameters (BaseParms) */
    hostwfc_BaseParams.DebugMode = hostwfc_Debug;

}

/**
********************************************************************************
* @brief Calls all configuration read functions of the application
*        Being called at module init by the bTask.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
SINT32 hostwfc_CfgRead(VOID)
{
    SINT32  ret;

    /* Initialize configuration with values taken at module init */
    hostwfc_CfgInit();

    /* Read all task configuration settings from mconfig.ini */
    ret = Task_CfgRead();
    if (ret < 0)
        return ret;

    /*
     * TODO:
     * Call other specific configuration read functions here
     */

    return (OK);
}

/**
********************************************************************************
* @brief Initializes the SVI-Interface.
*        Being called at module init by the bTask.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
SINT32 hostwfc_SviSrvInit(VOID)
{
    SINT32  ret;
    UINT32  NbOfGlobVars = sizeof(SviGlobVarList) / sizeof(SVI_GLOBVAR);
    UINT32  i;
    CHAR    Func[] = "hostwfc_SviSrvInit";

    /* If there are any SVI variables to be exported */
    if (NbOfGlobVars)
    {
        /* Initialize SVI-handler */
        hostwfc_SviHandle = svi_Init(hostwfc_AppName, 0, 0);
        if (!hostwfc_SviHandle)
        {
            LOG_E(0, Func, "Could not initialize SVI server handle!");
            return (ERROR);
        }
    }
    else
    {
        hostwfc_SviHandle = 0;
        return (OK);
    }

    /* Add the global variables from the list SviGlobVarList */
    for (i = 0; i < NbOfGlobVars; i++)
    {
        ret = svi_AddGlobVar(hostwfc_SviHandle, SviGlobVarList[i].VarName,
                             SviGlobVarList[i].Format, SviGlobVarList[i].Size,
                             SviGlobVarList[i].pVar, 0, SviGlobVarList[i].UserParam,
                             SviGlobVarList[i].pSviStart, SviGlobVarList[i].pSviEnd);
        if (ret)
        {
            LOG_E(0, Func, "Could not add SVI variable '%s'!, Error %d",
                  SviGlobVarList[i].VarName, ret);
            /*
             * TODO:
             * Decide if the module shall be de-installed in this case.
             * If yes, return an error here.
             */
        }
    }

    return (OK);
}

/**
********************************************************************************
* @brief Frees SVI server resources according to hostwfc_SviSrvInit()
*        Being called at module deinit by the bTask.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
VOID hostwfc_SviSrvDeinit(VOID)
{
    /* If there was no or no successful SVI init */
    if (!hostwfc_SviHandle)
        return;

    if (svi_DeInit(hostwfc_SviHandle) < 0)
        LOG_E(0, "hostwfc_SviSrvDeinit", "Could not de-initialize SVI server");

    hostwfc_SviHandle = 0;
}

/**
********************************************************************************
* @brief This function demonstrates the implementation of an SVI client.
*        It will connect to the server of another software module (RES)
*        and will get the address of one SVI variable. The variable is
*        accessed in AppMain(VOID)
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
MLOCAL SINT32 SviClt_Init(VOID)
{
    UINT32  SviFormat = 0;
    CHAR    Func[] = "SviClt_Init";

    /* Get library pointer to access SVI server of other software module. */
    pSviLib = svi_GetLib("RES");
    if (!pSviLib)
    {
        LOG_W(0, Func, "Could not get SVI of module 'RES'!");
        return (ERROR);
    }
// MATLABCODEGEN: OpenField Get Specified  App Module

pSviLib_tumitfc = svi_GetLib("tumitfc");
if (!pSviLib_tumitfc)
{
   LOG_W(0, Func, "Could not get SVI of module tumitfc!");
   return (ERROR);
}


// MATLABCODEGEN: CloseField Get Specified App Module

// MATLABCODEGEN: OpenField Get ITF SA Address

if (svi_GetAddr(pSviLib_tumitfc, "cw2InAr", &SA_tumitfc_cw2InAr, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value tumitfc_cw2InAr!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_tumitfc, "cw2OutAr", &SA_tumitfc_cw2OutAr, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value tumitfc_cw2OutAr!");
    return (ERROR);
}

// MATLABCODEGEN: CloseField Get ITF SA Address




    if (svi_GetAddr(pSviLib, "Time/Time_ms1970", &Time_ms1970_SviAddr, &SviFormat) != SVI_E_OK)
    {
        LOG_W(0, Func, "Could not get address of value 'Time_ms1970'!");
        return (ERROR);
    }





    /* Convert symbolic address "Time_us" to binary SVI address. */
    if (svi_GetAddr(pSviLib, "Time_us", &TimeSviAddr, &SviFormat) != SVI_E_OK)
    {
        LOG_W(0, Func, "Could not get address of value 'Time_us'!");
        return (ERROR);
    }
    return (OK);
}

/**
********************************************************************************
* @brief This function informs the RES that the function library of
*        the server (in this example the server is also RES) is no
*        longer required
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
MLOCAL VOID SviClt_Deinit(VOID)
{
    if (pSviLib)
    {
        if (svi_UngetLib(pSviLib) < 0)
            LOG_E(0, "SviClt_DeInit", "svi_UngetLib Error!");
        pSviLib = NULL;
    }

}

/**
********************************************************************************
* @brief This function demonstrates the implementation of an SVI client.
*        It will simply read one SVI variable. pLib and binary SVI address
*        have been retrieved in alt_SviClientInit().
*
* @param[in]  pTime_us    Buffer provided by caller to read the value
* @param[out] N/A
*
* @retval     = 0 .. OK
* @retval     < 0 .. ERROR
*******************************************************************************/
MLOCAL SINT32 SviClt_Read()
{
    SINT32  ret;
// MATLABCODEGEN: OpenField Size of Array definition

UINT32 tumitfc_cw2InAr_size = sizeof(tumitfc_cw2InAr);

// MATLABCODEGEN: CloseField Size of Array definition

UINT32 Time_ms1970_size = sizeof(Time_ms1970);
ret = svi_GetBlk(pSviLib, Time_ms1970_SviAddr, (UINT32*) &Time_ms1970,  &Time_ms1970_size);
if (ret != SVI_E_OK)
    LOG_W(0, "SviClt_Read", "Could not read value Time_ms1970!");





    // MATLABCODEGEN: OpenField assign variable from SA_Address

ret = svi_GetBlk(pSviLib_tumitfc, SA_tumitfc_cw2InAr, (UINT32*) &tumitfc_cw2InAr,  &tumitfc_cw2InAr_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value tumitfc_cw2InAr!");
 // MATLABCODEGEN: CloseField assign variable from SA_Address
    return (ret);
}
MLOCAL SINT32 SviClt_Write(VOID)
{
    SINT32  ret;
    // MATLABCODEGEN: OpenField assign variable in SviClt_Write

ret = svi_SetBlk(pSviLib_tumitfc, SA_tumitfc_cw2OutAr, (UINT32*) &tumitfc_cw2OutAr, sizeof(tumitfc_cw2OutAr) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value tumitfc_cw2OutAr!");

 // MATLABCODEGEN: CloseField assign variable in SviClt_Write
    return (ret);
}
MLOCAL SINT32 SviClt_Example(UINT32 * pTime_us)
{
    SINT32  ret;

    /* Read the microseconds since CPU boot from module RES. */
    ret = svi_GetVal(pSviLib, TimeSviAddr, pTime_us);
    if (ret != SVI_E_OK)
        LOG_W(0, "SviClt_Example", "Could not read value!");

    return (ret);
}


MLOCAL SINT32 write_header_fast()
{
    FILE *fp = pFileFast;

    if (fp == NULL)
     {
         LOG_W(0, "write_header_fast", "File pointer for fast file is empty when writing fast header.");
         return(1);
     }
// MATLABCODEGEN: OpenField  Label Names Output Fields fast
fprintf(fp, "TimeStamp_UTC; WT3_Azimuth_Angle[deg]; WT3_RotorSpeed[RPM]; WT3_Pitch_Blade_1[deg]; WT3_Pitch_Blade_2[deg]; WT3_Pitch_Blade_3[deg]; WT3_Flapwise_blade_1[Nm]; WT3_Flapwise_blade_2[Nm]; WT3_Flapwise_blade_3[Nm]; WT3_Edgewise_blade_1[Nm]; WT3_Edgewise_blade_2[Nm]; WT3_Edgewise_blade_3[Nm]; WT4_Flapwise_blade_1[Nm]; WT4_Flapwise_blade_2[Nm]; WT4_Flapwise_blade_3[Nm]; WT4_Edgewise_blade_1[Nm]; WT4_Edgewise_blade_2[Nm]; WT4_Edgewise_blade_3[Nm]; WT3_Torque[Nm]; Air_Density[Kg/m3]; Met_Mast_Wind_Speed_At_Hub_height[m/s]; Met_Mast_Wind_Direction_From_North[deg]; WT3_Nacelle_Wind_Speed[m/s]; WT3_Nacelle_Wind_Misalignment[deg]; WT3_Nacelle_Direction_from_North[deg]; WT3_Power_Output[kW]; WT3_Turbine_Operational_Status[-]; Flag_WT3_Turbine_Yaw_Input_Type[-]; Flag_Wind_Farm_Control_from_TUM_PLC[-]; Met_Mast_Wind_Speed_At_54_2[m/s]; WT4_Torque[Nm]; WT4_Azimuth_Angle[deg]; WT4_RotorSpeed[RPM]; WT4_Pitch_Blade_1[deg]; WT4_Pitch_Blade_2[deg]; WT4_Pitch_Blade_3[deg]; WT4_Nacelle_Wind_Speed[m/s]; WT4_Nacelle_Wind_Misalignment[deg]; WT4_Nacelle_Direction_from_North[deg]; WT4_Power_Output[kW]; WT4_Turbine_Operational_Status[-]; WT3_Wind_Observer_Yaw_Misalignment[deg]; WT3_Wind_Farm_Control_Offset[deg]; Flag_Wind_Observer_Operational_Status[-]; Flag_Wind_Farm_Control_Operational_Status[-]; INFLW1_WS_Filtered[m/s]; INFLW1_Wdir_Filtered[deg]; INFLW1_TurbInt_Filtered[-]; INFLW1_ShearExp_Filtered[-]; INFLW1_Status[-]; INFLW1_OK[-]; OFFSET1_OK[-]; OFFSET1_Status[-]; OFFSET1_Offset_deg[deg]; INFLW2_WS_Filtered[m/s]; INFLW2_Wdir_Filtered[deg]; INFLW2_TurbInt_Filtered[-]; INFLW2_ShearExp_Filtered[-]; INFLW2_Status[-]; INFLW2_OK[-]; OFFSET2_OK[-]; OFFSET2_Status[-]; OFFSET2_Offset_deg[deg]; \n");
// MATLABCODEGEN: CloseField  Label Names Output Fields fast




    return(0);
}

MLOCAL SINT32 write_header_slow()
{
    FILE *fp = pFileSlow;

    if (fp == NULL)
     {
         LOG_W(0, "write_header_slow", "File pointer for fast file is empty when writing slow header.");
         return(1);
     }
// MATLABCODEGEN: OpenField  Label Names Output Fields slow
fprintf(fp, "TimeStamp_UTC; OFFSET3_Offset_deg[deg]; OFFSET3_Status[-]; TOGGLER_WFCStatus[-]; TOGGLER_ActiveCTRL[-]; TOGGLER_Status[-]; TOGGLER_Offset_Demanded[deg]; TOGGLER_TotWFCTime[hrs]; TOGGLER_WFC1Time[hrs]; TOGGLER_GreedyWFCTime[hrs]; TOGGLER_WFC2Time[hrs]; TOGGLER_WFC3Time[hrs]; TOGGLER_Nacelle_MetMast_Offset[deg]; \n");
// MATLABCODEGEN: CloseField  Label Names Output Fields slow




    return(0);
}

MLOCAL SINT32 write_header_ctrl()
{
    FILE *fp = pFileCtrl;

    if (fp == NULL)
     {
         LOG_W(0, "write_header_ctrl", "File pointer for fast file is empty when writing ctrl header.");
         return(1);
     }
// MATLABCODEGEN: OpenField  Label Names Output Fields ctrl
fprintf(fp, "TimeStamp_UTC; Flag_ManualSwitch_WFC[-]; Flag_ManualSwitch_WFC_1[-]; Flag_ManualSwitch_GreedyWFC[-]; Flag_ManualSwitch_WFC_2[-]; Flag_ManualSwitch_WFC_3[-]; \n");
// MATLABCODEGEN: CloseField  Label Names Output Fields ctrl




    return(0);
}

MLOCAL SINT32 write_output_fast()
{

    FILE *fp = pFileFast;
    // Printing to file, checking for nan

    if (fp == NULL)
     {
         LOG_W(0, "write_output_fast", "File pointer for fast file is empty when writing fast.");
         return(1);
     }

    fprintf(fp, "%s; ", Date_and_Time);
// MATLABCODEGEN: OpenField  Print output to file fast


if (WT3_Azimuth_Angle==WT3_Azimuth_Angle)
{
     fprintf(fp, "%llf; ", WT3_Azimuth_Angle);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_RotorSpeed==WT3_RotorSpeed)
{
     fprintf(fp, "%llf; ", WT3_RotorSpeed);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Pitch_Blade_1==WT3_Pitch_Blade_1)
{
     fprintf(fp, "%llf; ", WT3_Pitch_Blade_1);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Pitch_Blade_2==WT3_Pitch_Blade_2)
{
     fprintf(fp, "%llf; ", WT3_Pitch_Blade_2);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Pitch_Blade_3==WT3_Pitch_Blade_3)
{
     fprintf(fp, "%llf; ", WT3_Pitch_Blade_3);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Flapwise_blade_1==WT3_Flapwise_blade_1)
{
     fprintf(fp, "%llf; ", WT3_Flapwise_blade_1);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Flapwise_blade_2==WT3_Flapwise_blade_2)
{
     fprintf(fp, "%llf; ", WT3_Flapwise_blade_2);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Flapwise_blade_3==WT3_Flapwise_blade_3)
{
     fprintf(fp, "%llf; ", WT3_Flapwise_blade_3);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Edgewise_blade_1==WT3_Edgewise_blade_1)
{
     fprintf(fp, "%llf; ", WT3_Edgewise_blade_1);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Edgewise_blade_2==WT3_Edgewise_blade_2)
{
     fprintf(fp, "%llf; ", WT3_Edgewise_blade_2);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Edgewise_blade_3==WT3_Edgewise_blade_3)
{
     fprintf(fp, "%llf; ", WT3_Edgewise_blade_3);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Flapwise_blade_1==WT4_Flapwise_blade_1)
{
     fprintf(fp, "%llf; ", WT4_Flapwise_blade_1);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Flapwise_blade_2==WT4_Flapwise_blade_2)
{
     fprintf(fp, "%llf; ", WT4_Flapwise_blade_2);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Flapwise_blade_3==WT4_Flapwise_blade_3)
{
     fprintf(fp, "%llf; ", WT4_Flapwise_blade_3);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Edgewise_blade_1==WT4_Edgewise_blade_1)
{
     fprintf(fp, "%llf; ", WT4_Edgewise_blade_1);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Edgewise_blade_2==WT4_Edgewise_blade_2)
{
     fprintf(fp, "%llf; ", WT4_Edgewise_blade_2);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Edgewise_blade_3==WT4_Edgewise_blade_3)
{
     fprintf(fp, "%llf; ", WT4_Edgewise_blade_3);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Torque==WT3_Torque)
{
     fprintf(fp, "%llf; ", WT3_Torque);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Air_Density==Air_Density)
{
     fprintf(fp, "%llf; ", Air_Density);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Met_Mast_Wind_Speed_At_Hub_height==Met_Mast_Wind_Speed_At_Hub_height)
{
     fprintf(fp, "%llf; ", Met_Mast_Wind_Speed_At_Hub_height);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Met_Mast_Wind_Direction_From_North==Met_Mast_Wind_Direction_From_North)
{
     fprintf(fp, "%llf; ", Met_Mast_Wind_Direction_From_North);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Nacelle_Wind_Speed==WT3_Nacelle_Wind_Speed)
{
     fprintf(fp, "%llf; ", WT3_Nacelle_Wind_Speed);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Nacelle_Wind_Misalignment==WT3_Nacelle_Wind_Misalignment)
{
     fprintf(fp, "%llf; ", WT3_Nacelle_Wind_Misalignment);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Nacelle_Direction_from_North==WT3_Nacelle_Direction_from_North)
{
     fprintf(fp, "%llf; ", WT3_Nacelle_Direction_from_North);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Power_Output==WT3_Power_Output)
{
     fprintf(fp, "%llf; ", WT3_Power_Output);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Turbine_Operational_Status==WT3_Turbine_Operational_Status)
{
     fprintf(fp, "%llf; ", WT3_Turbine_Operational_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Flag_WT3_Turbine_Yaw_Input_Type==Flag_WT3_Turbine_Yaw_Input_Type)
{
     fprintf(fp, "%llf; ", Flag_WT3_Turbine_Yaw_Input_Type);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Flag_Wind_Farm_Control_from_TUM_PLC==Flag_Wind_Farm_Control_from_TUM_PLC)
{
     fprintf(fp, "%llf; ", Flag_Wind_Farm_Control_from_TUM_PLC);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Met_Mast_Wind_Speed_At_54_2==Met_Mast_Wind_Speed_At_54_2)
{
     fprintf(fp, "%llf; ", Met_Mast_Wind_Speed_At_54_2);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Torque==WT4_Torque)
{
     fprintf(fp, "%llf; ", WT4_Torque);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Azimuth_Angle==WT4_Azimuth_Angle)
{
     fprintf(fp, "%llf; ", WT4_Azimuth_Angle);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_RotorSpeed==WT4_RotorSpeed)
{
     fprintf(fp, "%llf; ", WT4_RotorSpeed);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Pitch_Blade_1==WT4_Pitch_Blade_1)
{
     fprintf(fp, "%llf; ", WT4_Pitch_Blade_1);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Pitch_Blade_2==WT4_Pitch_Blade_2)
{
     fprintf(fp, "%llf; ", WT4_Pitch_Blade_2);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Pitch_Blade_3==WT4_Pitch_Blade_3)
{
     fprintf(fp, "%llf; ", WT4_Pitch_Blade_3);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Nacelle_Wind_Speed==WT4_Nacelle_Wind_Speed)
{
     fprintf(fp, "%llf; ", WT4_Nacelle_Wind_Speed);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Nacelle_Wind_Misalignment==WT4_Nacelle_Wind_Misalignment)
{
     fprintf(fp, "%llf; ", WT4_Nacelle_Wind_Misalignment);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Nacelle_Direction_from_North==WT4_Nacelle_Direction_from_North)
{
     fprintf(fp, "%llf; ", WT4_Nacelle_Direction_from_North);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Power_Output==WT4_Power_Output)
{
     fprintf(fp, "%llf; ", WT4_Power_Output);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT4_Turbine_Operational_Status==WT4_Turbine_Operational_Status)
{
     fprintf(fp, "%llf; ", WT4_Turbine_Operational_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Wind_Observer_Yaw_Misalignment==WT3_Wind_Observer_Yaw_Misalignment)
{
     fprintf(fp, "%llf; ", WT3_Wind_Observer_Yaw_Misalignment);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (WT3_Wind_Farm_Control_Offset==WT3_Wind_Farm_Control_Offset)
{
     fprintf(fp, "%llf; ", WT3_Wind_Farm_Control_Offset);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Flag_Wind_Observer_Operational_Status==Flag_Wind_Observer_Operational_Status)
{
     fprintf(fp, "%llf; ", Flag_Wind_Observer_Operational_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Flag_Wind_Farm_Control_Operational_Status==Flag_Wind_Farm_Control_Operational_Status)
{
     fprintf(fp, "%llf; ", Flag_Wind_Farm_Control_Operational_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW1_WS_Filtered==INFLW1_WS_Filtered)
{
     fprintf(fp, "%llf; ", INFLW1_WS_Filtered);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW1_Wdir_Filtered==INFLW1_Wdir_Filtered)
{
     fprintf(fp, "%llf; ", INFLW1_Wdir_Filtered);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW1_TurbInt_Filtered==INFLW1_TurbInt_Filtered)
{
     fprintf(fp, "%llf; ", INFLW1_TurbInt_Filtered);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW1_ShearExp_Filtered==INFLW1_ShearExp_Filtered)
{
     fprintf(fp, "%llf; ", INFLW1_ShearExp_Filtered);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW1_Status==INFLW1_Status)
{
     fprintf(fp, "%d; ", INFLW1_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW1_OK==INFLW1_OK)
{
     fprintf(fp, "%llf; ", INFLW1_OK);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (OFFSET1_OK==OFFSET1_OK)
{
     fprintf(fp, "%llf; ", OFFSET1_OK);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (OFFSET1_Status==OFFSET1_Status)
{
     fprintf(fp, "%d; ", OFFSET1_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (OFFSET1_Offset_deg==OFFSET1_Offset_deg)
{
     fprintf(fp, "%llf; ", OFFSET1_Offset_deg);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW2_WS_Filtered==INFLW2_WS_Filtered)
{
     fprintf(fp, "%llf; ", INFLW2_WS_Filtered);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW2_Wdir_Filtered==INFLW2_Wdir_Filtered)
{
     fprintf(fp, "%llf; ", INFLW2_Wdir_Filtered);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW2_TurbInt_Filtered==INFLW2_TurbInt_Filtered)
{
     fprintf(fp, "%llf; ", INFLW2_TurbInt_Filtered);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW2_ShearExp_Filtered==INFLW2_ShearExp_Filtered)
{
     fprintf(fp, "%llf; ", INFLW2_ShearExp_Filtered);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW2_Status==INFLW2_Status)
{
     fprintf(fp, "%d; ", INFLW2_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (INFLW2_OK==INFLW2_OK)
{
     fprintf(fp, "%llf; ", INFLW2_OK);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (OFFSET2_OK==OFFSET2_OK)
{
     fprintf(fp, "%llf; ", OFFSET2_OK);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (OFFSET2_Status==OFFSET2_Status)
{
     fprintf(fp, "%d; ", OFFSET2_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (OFFSET2_Offset_deg==OFFSET2_Offset_deg)
{
     fprintf(fp, "%llf; ", OFFSET2_Offset_deg);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

// MATLABCODEGEN: CloseField  Print output to file fast


    fprintf(fp, "\n");
    fflush(fp);

    return 0;
}

MLOCAL SINT32 write_output_slow()
{

    FILE *fp = pFileSlow;
    // Printing to file, checking for nan

    if (fp == NULL)
     {
         LOG_W(0, "write_output_slow", "File pointer for fast file is empty when writing slow.");
         return(1);
     }

    fprintf(fp, "%s; ", Date_and_Time);
// MATLABCODEGEN: OpenField  Print output to file slow


if (OFFSET3_Offset_deg==OFFSET3_Offset_deg)
{
     fprintf(fp, "%llf; ", OFFSET3_Offset_deg);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (OFFSET3_Status==OFFSET3_Status)
{
     fprintf(fp, "%d; ", OFFSET3_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_WFCStatus==TOGGLER_WFCStatus)
{
     fprintf(fp, "%llf; ", TOGGLER_WFCStatus);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_ActiveCTRL==TOGGLER_ActiveCTRL)
{
     fprintf(fp, "%llf; ", TOGGLER_ActiveCTRL);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_Status==TOGGLER_Status)
{
     fprintf(fp, "%d; ", TOGGLER_Status);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_Offset_Demanded==TOGGLER_Offset_Demanded)
{
     fprintf(fp, "%llf; ", TOGGLER_Offset_Demanded);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_TotWFCTime==TOGGLER_TotWFCTime)
{
     fprintf(fp, "%llf; ", TOGGLER_TotWFCTime);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_WFC1Time==TOGGLER_WFC1Time)
{
     fprintf(fp, "%llf; ", TOGGLER_WFC1Time);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_GreedyWFCTime==TOGGLER_GreedyWFCTime)
{
     fprintf(fp, "%llf; ", TOGGLER_GreedyWFCTime);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_WFC2Time==TOGGLER_WFC2Time)
{
     fprintf(fp, "%llf; ", TOGGLER_WFC2Time);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_WFC3Time==TOGGLER_WFC3Time)
{
     fprintf(fp, "%llf; ", TOGGLER_WFC3Time);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (TOGGLER_Nacelle_MetMast_Offset==TOGGLER_Nacelle_MetMast_Offset)
{
     fprintf(fp, "%llf; ", TOGGLER_Nacelle_MetMast_Offset);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

// MATLABCODEGEN: CloseField  Print output to file slow


    fprintf(fp, "\n");
    fflush(fp);

    return 0;
}

MLOCAL SINT32 write_output_ctrl()
{

    FILE *fp = pFileCtrl;
    // Printing to file, checking for nan

    if (fp == NULL)
     {
         LOG_W(0, "write_output_ctrl", "File pointer for fast file is empty when writing ctrl.");
         return(1);
     }

    fprintf(fp, "%s; ", Date_and_Time);
// MATLABCODEGEN: OpenField  Print output to file ctrl


if (Flag_ManualSwitch_WFC==Flag_ManualSwitch_WFC)
{
     fprintf(fp, "%llf; ", Flag_ManualSwitch_WFC);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Flag_ManualSwitch_WFC_1==Flag_ManualSwitch_WFC_1)
{
     fprintf(fp, "%llf; ", Flag_ManualSwitch_WFC_1);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Flag_ManualSwitch_GreedyWFC==Flag_ManualSwitch_GreedyWFC)
{
     fprintf(fp, "%llf; ", Flag_ManualSwitch_GreedyWFC);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Flag_ManualSwitch_WFC_2==Flag_ManualSwitch_WFC_2)
{
     fprintf(fp, "%llf; ", Flag_ManualSwitch_WFC_2);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

if (Flag_ManualSwitch_WFC_3==Flag_ManualSwitch_WFC_3)
{
     fprintf(fp, "%llf; ", Flag_ManualSwitch_WFC_3);
}
else
{
     fprintf(fp, "%s; ", "NaN");
}

// MATLABCODEGEN: CloseField  Print output to file ctrl


    fprintf(fp, "\n");
    fflush(fp);

    return 0;
}