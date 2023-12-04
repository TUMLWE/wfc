/**
********************************************************************************
* @file     toggler_app.c
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
#include "toggler.h"
#include "toggler_e.h"
#include "toggler_int.h"


// MATLABCODEGEN: OpenField #IncludeHeader
#include "TOGGLER.h"
// MATLABCODEGEN: CloseField #IncludeHeader


// MATLABCODEGEN: OpenField #Include rt_OneStep
void rt_OneStep(void);
void rt_OneStep(void)
{
    /* Step the model */
    TOGGLER_step();
}

// MATLABCODEGEN: CloseField #Include rt_OneStep

/* Functions: administration, to be called from outside this file */
SINT32  toggler_AppEOI(VOID);
VOID    toggler_AppDeinit(VOID);
SINT32  toggler_CfgRead(VOID);
SINT32  toggler_SviSrvInit(VOID);
VOID    toggler_SviSrvDeinit(VOID);

/* Functions: administration, to be called only from within this file */
MLOCAL VOID toggler_CfgInit(VOID);

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
TOGGLER_BASE_PARMS toggler_BaseParams;

/* Global variables: SVI client */
MLOCAL  SINT32(**pSviLib) () = NULL;    /* Information about external SVI server */
MLOCAL SVI_ADDR TimeSviAddr;            /* SVI address of server's variable */
MLOCAL BOOL8 PrintTime = TRUE;



// MATLABCODEGEN: OpenField SVI Server Definition

MLOCAL SINT32  (**pSviLib_hostwfc)  ()= NULL;

// MATLABCODEGEN: CloseField SVI Server Definition


// MATLABCODEGEN: OpenField SA Address and Variables to be read from interface

REAL64 hostwfc_MetMastWindSpeedAtHubheight[1];
MLOCAL SVI_ADDR SA_hostwfc_MetMastWindSpeedAtHubheight;
REAL64 hostwfc_MetMastWindDirectionFromNorth[1];
MLOCAL SVI_ADDR SA_hostwfc_MetMastWindDirectionFromNorth;
REAL64 hostwfc_WT3NacelleDirectionfromNorth[1];
MLOCAL SVI_ADDR SA_hostwfc_WT3NacelleDirectionfromNorth;
REAL64 hostwfc_WT3NacelleWindMisalignment[1];
MLOCAL SVI_ADDR SA_hostwfc_WT3NacelleWindMisalignment;
UINT16 hostwfc_INFLW1Status[1];
MLOCAL SVI_ADDR SA_hostwfc_INFLW1Status;
UINT16 hostwfc_OFFSET1Status[1];
MLOCAL SVI_ADDR SA_hostwfc_OFFSET1Status;
UINT16 hostwfc_INFLW2Status[1];
MLOCAL SVI_ADDR SA_hostwfc_INFLW2Status;
UINT16 hostwfc_OFFSET2Status[1];
MLOCAL SVI_ADDR SA_hostwfc_OFFSET2Status;
REAL64 hostwfc_OFFSET1Offsetdeg[1];
MLOCAL SVI_ADDR SA_hostwfc_OFFSET1Offsetdeg;
REAL64 hostwfc_OFFSET2Offsetdeg[1];
MLOCAL SVI_ADDR SA_hostwfc_OFFSET2Offsetdeg;
REAL64 hostwfc_FlagWindFarmControlfromTUMPLC[1];
MLOCAL SVI_ADDR SA_hostwfc_FlagWindFarmControlfromTUMPLC;
REAL64 hostwfc_FlagManualSwitchWFC[1];
MLOCAL SVI_ADDR SA_hostwfc_FlagManualSwitchWFC;
REAL64 hostwfc_FlagManualSwitchWFC1[1];
MLOCAL SVI_ADDR SA_hostwfc_FlagManualSwitchWFC1;
REAL64 hostwfc_FlagManualSwitchGreedyWFC[1];
MLOCAL SVI_ADDR SA_hostwfc_FlagManualSwitchGreedyWFC;
REAL64 hostwfc_FlagManualSwitchWFC2[1];
MLOCAL SVI_ADDR SA_hostwfc_FlagManualSwitchWFC2;
REAL64 hostwfc_FlagManualSwitchWFC3[1];
MLOCAL SVI_ADDR SA_hostwfc_FlagManualSwitchWFC3;
REAL64 hostwfc_OFFSET3Offsetdeg[1];
MLOCAL SVI_ADDR SA_hostwfc_OFFSET3Offsetdeg;
UINT16 hostwfc_OFFSET3Status[1];
MLOCAL SVI_ADDR SA_hostwfc_OFFSET3Status;
REAL64 hostwfc_TOGGLERNacelleMetMastOffset[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLERNacelleMetMastOffset;
REAL64 hostwfc_WT3PowerOutput[1];
MLOCAL SVI_ADDR SA_hostwfc_WT3PowerOutput;
REAL64 hostwfc_FlagWindFarmControlOperationalStatus[1];
MLOCAL SVI_ADDR SA_hostwfc_FlagWindFarmControlOperationalStatus;
REAL64 hostwfc_TOGGLERWFCStatus[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLERWFCStatus;
REAL64 hostwfc_TOGGLERActiveCTRL[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLERActiveCTRL;
REAL64 hostwfc_WT3WindFarmControlOffset[1];
MLOCAL SVI_ADDR SA_hostwfc_WT3WindFarmControlOffset;
REAL64 hostwfc_TOGGLEROffsetDemanded[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLEROffsetDemanded;
REAL64 hostwfc_TOGGLERTotWFCTime[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLERTotWFCTime;
REAL64 hostwfc_TOGGLERWFC1Time[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLERWFC1Time;
REAL64 hostwfc_TOGGLERGreedyWFCTime[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLERGreedyWFCTime;
REAL64 hostwfc_TOGGLERWFC2Time[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLERWFC2Time;
REAL64 hostwfc_TOGGLERWFC3Time[1];
MLOCAL SVI_ADDR SA_hostwfc_TOGGLERWFC3Time;

// MATLABCODEGEN: CloseField SA Address and Variables to be read from interface


MLOCAL SVI_ADDR SA_AppStatus;


/* Global variables: miscellaneous */
MLOCAL UINT32 CycleCount = 0;
// MATLABCODEGEN: OpenField Output Variable Definition
// MATLABCODEGEN: CloseField Output Variable Definition

MLOCAL UINT16 AppStatus = 0;







// MATLABCODEGEN: OpenField SVI Variables Definition

MLOCAL REAL64 input_WS_ms=0;
MLOCAL REAL64 input_Dir_deg=0;
MLOCAL REAL64 input_WT3_NacelleOrientation=0;
MLOCAL REAL64 input_WT3_Misalignment=0;
MLOCAL UINT16 input_INFLW_1_Status=0;
MLOCAL UINT16 input_OFFSET_1_Status=0;
MLOCAL UINT16 input_INFLW_2_Status=0;
MLOCAL UINT16 input_OFFSET_2_Status=0;
MLOCAL REAL64 input_WFC_Offset_1_deg=0;
MLOCAL REAL64 input_WFC_Offset_2_deg=0;
MLOCAL REAL64 input_FlagTurbineWFC_isActive=0;
MLOCAL REAL64 input_Flag_ManualSwitch_WFC=0;
MLOCAL REAL64 input_ManualSwitch_WFC_1=0;
MLOCAL REAL64 input_ManualSwitch_GreedyWFC=0;
MLOCAL REAL64 input_ManualSwitch_WFC_2=0;
MLOCAL REAL64 input_ManualSwitch_WFC_3=0;
MLOCAL REAL64 input_WFC_Offset_3_deg=0;
MLOCAL UINT16 input_WFC_3_Status=0;
MLOCAL REAL64 input_Nacelle_MetMast_Offset=0;
MLOCAL REAL64 input_WT3_OpStatus=0;
MLOCAL REAL64 output_Flag_WFCIsActive=0;
MLOCAL REAL64 output_WFCStatus=0;
MLOCAL REAL64 output_ActiveCTRL=0;
MLOCAL REAL64 output_WFC_Offset=0;
MLOCAL REAL64 output_WFC_Offset_Demanded=0;
MLOCAL REAL64 output_TotWFCTime=0;
MLOCAL REAL64 output_WFC1Time=0;
MLOCAL REAL64 output_GreedyWFCTime=0;
MLOCAL REAL64 output_WFC2Time=0;
MLOCAL REAL64 output_WFC3Time=0;

// MATLABCODEGEN: CloseField SVI Variables Definition

/*
 * Global variables: Settings for application task
 * A reference to these settings must be registered in TaskList[], see below.
 * If no configuration group is being specified, all values must be set properly
 * in this initialization.
 */
MLOCAL TASK_PROPERTIES TaskProperties_aControl = {
    "aTOGGLER_Ctrl",                 /* unique task name, maximum length 14 */
    "ControlTask",                      /* configuration group name */
    Control_Main,                       /* task entry function (function pointer) */
    0,                                  /* default task priority (->Task_CfgRead) */
    10.0,                               /* default task cycle time in ms (->Task_CfgRead) */
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
    {"ModuleVersion", SVI_F_OUT | SVI_F_STRING, sizeof(toggler_Version),
     (UINT32 *) toggler_Version, 0, NULL, NULL},

// MATLABCODEGEN: OpenField SVI Variables Coupling

{"input_WS_ms", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_WS_ms, 0, NULL, NULL},
{"input_Dir_deg", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_Dir_deg, 0, NULL, NULL},
{"input_WT3_NacelleOrientation", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_WT3_NacelleOrientation, 0, NULL, NULL},
{"input_WT3_Misalignment", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_WT3_Misalignment, 0, NULL, NULL},
{"input_INFLW_1_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &input_INFLW_1_Status, 0, NULL, NULL},
{"input_OFFSET_1_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &input_OFFSET_1_Status, 0, NULL, NULL},
{"input_INFLW_2_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &input_INFLW_2_Status, 0, NULL, NULL},
{"input_OFFSET_2_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &input_OFFSET_2_Status, 0, NULL, NULL},
{"input_WFC_Offset_1_deg", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_WFC_Offset_1_deg, 0, NULL, NULL},
{"input_WFC_Offset_2_deg", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_WFC_Offset_2_deg, 0, NULL, NULL},
{"input_FlagTurbineWFC_isActive", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_FlagTurbineWFC_isActive, 0, NULL, NULL},
{"input_Flag_ManualSwitch_WFC", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_Flag_ManualSwitch_WFC, 0, NULL, NULL},
{"input_ManualSwitch_WFC_1", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_ManualSwitch_WFC_1, 0, NULL, NULL},
{"input_ManualSwitch_GreedyWFC", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_ManualSwitch_GreedyWFC, 0, NULL, NULL},
{"input_ManualSwitch_WFC_2", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_ManualSwitch_WFC_2, 0, NULL, NULL},
{"input_ManualSwitch_WFC_3", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_ManualSwitch_WFC_3, 0, NULL, NULL},
{"input_WFC_Offset_3_deg", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_WFC_Offset_3_deg, 0, NULL, NULL},
{"input_WFC_3_Status", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &input_WFC_3_Status, 0, NULL, NULL},
{"input_Nacelle_MetMast_Offset", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_Nacelle_MetMast_Offset, 0, NULL, NULL},
{"input_WT3_OpStatus", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &input_WT3_OpStatus, 0, NULL, NULL},
{"output_Flag_WFCIsActive", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_Flag_WFCIsActive, 0, NULL, NULL},
{"output_WFCStatus", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_WFCStatus, 0, NULL, NULL},
{"output_ActiveCTRL", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_ActiveCTRL, 0, NULL, NULL},
{"output_WFC_Offset", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_WFC_Offset, 0, NULL, NULL},
{"output_WFC_Offset_Demanded", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_WFC_Offset_Demanded, 0, NULL, NULL},
{"output_TotWFCTime", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_TotWFCTime, 0, NULL, NULL},
{"output_WFC1Time", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_WFC1Time, 0, NULL, NULL},
{"output_GreedyWFCTime", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_GreedyWFCTime, 0, NULL, NULL},
{"output_WFC2Time", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_WFC2Time, 0, NULL, NULL},
{"output_WFC3Time", SVI_F_INOUT | SVI_F_BLK | SVI_F_REAL64, sizeof(REAL64[1]), (UINT32 *) &output_WFC3Time, 0, NULL, NULL},

// MATLABCODEGEN: CloseField SVI Variables Coupling
{"AppStatus", SVI_F_INOUT | SVI_F_UINT16, sizeof(UINT16[1]), (UINT32 *) &AppStatus, 0, NULL, NULL},


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
// MATLABCODEGEN: OpenField #terminate model
    /* Terminate model */
    TOGGLER_terminate();

// MATLABCODEGEN: CloseField #terminate model

// MATLABCODEGEN: OpenField Terminate Variables

output_Flag_WFCIsActive=0;
output_WFCStatus=0;
output_ActiveCTRL=0;
output_WFC_Offset=0;
output_WFC_Offset_Demanded=0;
output_TotWFCTime=0;
output_WFC1Time=0;
output_GreedyWFCTime=0;
output_WFC2Time=0;
output_WFC3Time=0;

// MATLABCODEGEN: CloseField Terminate Variables



AppStatus = 0;
SviClt_Write();




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
// MATLABCODEGEN: OpenField #initialize model
    TOGGLER_initialize();

// MATLABCODEGEN: CloseField #initialize model

AppStatus = 1;






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
if (SviClt_Read() < 0)
    LOG_W(0, "Control_CycleStart", "Could not read all SVI variables!");




// MATLABCODEGEN: OpenField Assign ITF Variables to HOST SVI

input_WS_ms = hostwfc_MetMastWindSpeedAtHubheight[0];
input_Dir_deg = hostwfc_MetMastWindDirectionFromNorth[0];
input_WT3_NacelleOrientation = hostwfc_WT3NacelleDirectionfromNorth[0];
input_WT3_Misalignment = hostwfc_WT3NacelleWindMisalignment[0];
input_INFLW_1_Status = hostwfc_INFLW1Status[0];
input_OFFSET_1_Status = hostwfc_OFFSET1Status[0];
input_INFLW_2_Status = hostwfc_INFLW2Status[0];
input_OFFSET_2_Status = hostwfc_OFFSET2Status[0];
input_WFC_Offset_1_deg = hostwfc_OFFSET1Offsetdeg[0];
input_WFC_Offset_2_deg = hostwfc_OFFSET2Offsetdeg[0];
input_FlagTurbineWFC_isActive = hostwfc_FlagWindFarmControlfromTUMPLC[0];
input_Flag_ManualSwitch_WFC = hostwfc_FlagManualSwitchWFC[0];
input_ManualSwitch_WFC_1 = hostwfc_FlagManualSwitchWFC1[0];
input_ManualSwitch_GreedyWFC = hostwfc_FlagManualSwitchGreedyWFC[0];
input_ManualSwitch_WFC_2 = hostwfc_FlagManualSwitchWFC2[0];
input_ManualSwitch_WFC_3 = hostwfc_FlagManualSwitchWFC3[0];
input_WFC_Offset_3_deg = hostwfc_OFFSET3Offsetdeg[0];
input_WFC_3_Status = hostwfc_OFFSET3Status[0];
input_Nacelle_MetMast_Offset = hostwfc_TOGGLERNacelleMetMastOffset[0];
input_WT3_OpStatus = hostwfc_WT3PowerOutput[0];

// MATLABCODEGEN: CloseField Assign ITF Variables to HOST SVI

// MATLABCODEGEN: OpenField3 Simulink Model Input Assignment Definition

TOGGLER_U.input_WS_ms =  input_WS_ms;
TOGGLER_U.input_Dir_deg =  input_Dir_deg;
TOGGLER_U.input_WT3_NacelleOrientation =  input_WT3_NacelleOrientation;
TOGGLER_U.input_WT3_Misalignment =  input_WT3_Misalignment;
TOGGLER_U.input_INFLW_1_Status =  input_INFLW_1_Status;
TOGGLER_U.input_OFFSET_1_Status =  input_OFFSET_1_Status;
TOGGLER_U.input_INFLW_2_Status =  input_INFLW_2_Status;
TOGGLER_U.input_OFFSET_2_Status =  input_OFFSET_2_Status;
TOGGLER_U.input_WFC_Offset_1_deg =  input_WFC_Offset_1_deg;
TOGGLER_U.input_WFC_Offset_2_deg =  input_WFC_Offset_2_deg;
TOGGLER_U.input_FlagTurbineWFC_isActive =  input_FlagTurbineWFC_isActive;
TOGGLER_U.input_Flag_ManualSwitch_WFC =  input_Flag_ManualSwitch_WFC;
TOGGLER_U.input_ManualSwitch_WFC_1 =  input_ManualSwitch_WFC_1;
TOGGLER_U.input_ManualSwitch_GreedyWFC =  input_ManualSwitch_GreedyWFC;
TOGGLER_U.input_ManualSwitch_WFC_2 =  input_ManualSwitch_WFC_2;
TOGGLER_U.input_ManualSwitch_WFC_3 =  input_ManualSwitch_WFC_3;
TOGGLER_U.input_WFC_Offset_3_deg =  input_WFC_Offset_3_deg;
TOGGLER_U.input_WFC_3_Status =  input_WFC_3_Status;
TOGGLER_U.input_Nacelle_MetMast_Offset =  input_Nacelle_MetMast_Offset;
TOGGLER_U.input_WT3_OpStatus =  input_WT3_OpStatus;

// MATLABCODEGEN: CloseField3 Simulink Model Input Assignment Definition



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
    CycleCount++;    rt_OneStep();
// MATLABCODEGEN: OpenField Output Variable Assignment

output_Flag_WFCIsActive =  TOGGLER_Y.output_Flag_WFCIsActive;
output_WFCStatus =  TOGGLER_Y.output_WFCStatus;
output_ActiveCTRL =  TOGGLER_Y.output_ActiveCTRL;
output_WFC_Offset =  TOGGLER_Y.output_WFC_Offset;
output_WFC_Offset_Demanded =  TOGGLER_Y.output_WFC_Offset_Demanded;
output_TotWFCTime =  TOGGLER_Y.output_TotWFCTime;
output_WFC1Time =  TOGGLER_Y.output_WFC1Time;
output_GreedyWFCTime =  TOGGLER_Y.output_GreedyWFCTime;
output_WFC2Time =  TOGGLER_Y.output_WFC2Time;
output_WFC3Time =  TOGGLER_Y.output_WFC3Time;

// MATLABCODEGEN: CloseField Output Variable Assignment

// MATLABCODEGEN: OpenField Assign ITF output Variables to HOST SVI

hostwfc_FlagWindFarmControlOperationalStatus[0] = output_Flag_WFCIsActive;
hostwfc_TOGGLERWFCStatus[0] = output_WFCStatus;
hostwfc_TOGGLERActiveCTRL[0] = output_ActiveCTRL;
hostwfc_WT3WindFarmControlOffset[0] = output_WFC_Offset;
hostwfc_TOGGLEROffsetDemanded[0] = output_WFC_Offset_Demanded;
hostwfc_TOGGLERTotWFCTime[0] = output_TotWFCTime;
hostwfc_TOGGLERWFC1Time[0] = output_WFC1Time;
hostwfc_TOGGLERGreedyWFCTime[0] = output_GreedyWFCTime;
hostwfc_TOGGLERWFC2Time[0] = output_WFC2Time;
hostwfc_TOGGLERWFC3Time[0] = output_WFC3Time;

// MATLABCODEGEN: CloseField Assign ITF output Variables to HOST SVI





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
SINT32 toggler_AppEOI(VOID)
{

    /* do while(0), to be left as soon as there is an error */
    do
    {
        /* TODO: set module info string, maximum length is SMI_DESCLEN_A */
        snprintf(toggler_ModuleInfoDesc, sizeof(toggler_ModuleInfoDesc), "TODO: set application specific module info string");

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
    toggler_AppDeinit();
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
VOID toggler_AppDeinit(VOID)
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
*        For general configuration data, toggler_CfgParams is being used.
*        Being called by toggler_CfgRead.
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
    snprintf(section, sizeof(section), toggler_BaseParams.AppName);

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
                         toggler_BaseParams.CfgLine, toggler_BaseParams.CfgFileName);
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
                        toggler_BaseParams.CfgLine, toggler_BaseParams.CfgFileName);
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
                TaskList[idx]->Priority = toggler_BaseParams.DefaultPriority;
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
                        toggler_BaseParams.CfgLine, toggler_BaseParams.CfgFileName);
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
                        toggler_BaseParams.CfgLine, toggler_BaseParams.CfgFileName);
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
            TaskList[idx]->WdogId = sys_WdogCreate(toggler_AppName, wdogtime_us);
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
            snprintf(TaskList[idx]->Name, sizeof(TaskList[idx]->Name), "a%s_%d", toggler_AppName, idx + 1);

        snprintf(TaskName, sizeof(TaskList[idx]->Name), "%s", TaskList[idx]->Name);

        /* Task options */
        TaskOptions = 0;
        if (TaskList[idx]->UseFPU)
            TaskOptions |= VX_FP_TASK;

        /* Spawn task with properties set in task list */
        TaskList[idx]->TaskId = sys_TaskSpawn(toggler_AppName, TaskName,
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
            if (toggler_BaseParams.DebugMode & APP_DBG_INFO1)
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
    pTaskData->SyncSessionId = mio_StartSyncSession(toggler_AppName);
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
    if ((toggler_ModState == RES_S_STOP) || (toggler_ModState == RES_S_EOI))
    {
        /* Disable software watchdog if present */
        if (pTaskData->WdogId)
            sys_WdogDisable(pTaskData->WdogId);

        LOG_I(0, "Task_WaitCycle", "Stopping task '%s' due to module stop", pTaskData->Name);

        /*
         * semaphore will be given by SMI server with calls
         * RpcStart or RpcEndOfInit
         */
        semTake(toggler_StateSema, WAIT_FOREVER);
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
MLOCAL VOID toggler_CfgInit(VOID)
{
    /* Configuration file name (profile name) */
    strncpy(toggler_BaseParams.CfgFileName, toggler_ProfileName, M_PATHLEN);

    /* Application name */
    strncpy(toggler_BaseParams.AppName, toggler_AppName, M_MODNAMELEN);

    /* Line number in configuration file (used as start line for searching) */
    toggler_BaseParams.CfgLine = toggler_CfgLine;

    /* Worker task priority from module base parameters (BaseParms) */
    toggler_BaseParams.DefaultPriority = toggler_AppPrio;

    /* Debug mode from module base parameters (BaseParms) */
    toggler_BaseParams.DebugMode = toggler_Debug;

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
SINT32 toggler_CfgRead(VOID)
{
    SINT32  ret;

    /* Initialize configuration with values taken at module init */
    toggler_CfgInit();

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
SINT32 toggler_SviSrvInit(VOID)
{
    SINT32  ret;
    UINT32  NbOfGlobVars = sizeof(SviGlobVarList) / sizeof(SVI_GLOBVAR);
    UINT32  i;
    CHAR    Func[] = "toggler_SviSrvInit";

    /* If there are any SVI variables to be exported */
    if (NbOfGlobVars)
    {
        /* Initialize SVI-handler */
        toggler_SviHandle = svi_Init(toggler_AppName, 0, 0);
        if (!toggler_SviHandle)
        {
            LOG_E(0, Func, "Could not initialize SVI server handle!");
            return (ERROR);
        }
    }
    else
    {
        toggler_SviHandle = 0;
        return (OK);
    }

    /* Add the global variables from the list SviGlobVarList */
    for (i = 0; i < NbOfGlobVars; i++)
    {
        ret = svi_AddGlobVar(toggler_SviHandle, SviGlobVarList[i].VarName,
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
* @brief Frees SVI server resources according to toggler_SviSrvInit()
*        Being called at module deinit by the bTask.
*
* @param[in]  N/A
* @param[out] N/A
*
* @retval     N/A
*******************************************************************************/
VOID toggler_SviSrvDeinit(VOID)
{
    /* If there was no or no successful SVI init */
    if (!toggler_SviHandle)
        return;

    if (svi_DeInit(toggler_SviHandle) < 0)
        LOG_E(0, "toggler_SviSrvDeinit", "Could not de-initialize SVI server");

    toggler_SviHandle = 0;
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

pSviLib_hostwfc = svi_GetLib("hostwfc");
if (!pSviLib_hostwfc)
{
   LOG_W(0, Func, "Could not get SVI of module hostwfc!");
   return (ERROR);
}


// MATLABCODEGEN: CloseField Get Specified App Module

// MATLABCODEGEN: OpenField Get ITF SA Address

if (svi_GetAddr(pSviLib_hostwfc, "Met_Mast_Wind_Speed_At_Hub_height", &SA_hostwfc_MetMastWindSpeedAtHubheight, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_MetMastWindSpeedAtHubheight!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "Met_Mast_Wind_Direction_From_North", &SA_hostwfc_MetMastWindDirectionFromNorth, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_MetMastWindDirectionFromNorth!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "WT3_Nacelle_Direction_from_North", &SA_hostwfc_WT3NacelleDirectionfromNorth, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_WT3NacelleDirectionfromNorth!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "WT3_Nacelle_Wind_Misalignment", &SA_hostwfc_WT3NacelleWindMisalignment, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_WT3NacelleWindMisalignment!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "INFLW1_Status", &SA_hostwfc_INFLW1Status, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_INFLW1Status!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "OFFSET1_Status", &SA_hostwfc_OFFSET1Status, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_OFFSET1Status!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "INFLW2_Status", &SA_hostwfc_INFLW2Status, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_INFLW2Status!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "OFFSET2_Status", &SA_hostwfc_OFFSET2Status, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_OFFSET2Status!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "OFFSET1_Offset_deg", &SA_hostwfc_OFFSET1Offsetdeg, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_OFFSET1Offsetdeg!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "OFFSET2_Offset_deg", &SA_hostwfc_OFFSET2Offsetdeg, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_OFFSET2Offsetdeg!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "Flag_Wind_Farm_Control_from_TUM_PLC", &SA_hostwfc_FlagWindFarmControlfromTUMPLC, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_FlagWindFarmControlfromTUMPLC!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "Flag_ManualSwitch_WFC", &SA_hostwfc_FlagManualSwitchWFC, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_FlagManualSwitchWFC!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "Flag_ManualSwitch_WFC_1", &SA_hostwfc_FlagManualSwitchWFC1, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_FlagManualSwitchWFC1!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "Flag_ManualSwitch_GreedyWFC", &SA_hostwfc_FlagManualSwitchGreedyWFC, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_FlagManualSwitchGreedyWFC!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "Flag_ManualSwitch_WFC_2", &SA_hostwfc_FlagManualSwitchWFC2, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_FlagManualSwitchWFC2!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "Flag_ManualSwitch_WFC_3", &SA_hostwfc_FlagManualSwitchWFC3, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_FlagManualSwitchWFC3!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "OFFSET3_Offset_deg", &SA_hostwfc_OFFSET3Offsetdeg, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_OFFSET3Offsetdeg!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "OFFSET3_Status", &SA_hostwfc_OFFSET3Status, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_OFFSET3Status!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_Nacelle_MetMast_Offset", &SA_hostwfc_TOGGLERNacelleMetMastOffset, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLERNacelleMetMastOffset!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "WT3_Power_Output", &SA_hostwfc_WT3PowerOutput, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_WT3PowerOutput!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "Flag_Wind_Farm_Control_Operational_Status", &SA_hostwfc_FlagWindFarmControlOperationalStatus, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_FlagWindFarmControlOperationalStatus!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_WFCStatus", &SA_hostwfc_TOGGLERWFCStatus, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLERWFCStatus!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_ActiveCTRL", &SA_hostwfc_TOGGLERActiveCTRL, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLERActiveCTRL!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "WT3_Wind_Farm_Control_Offset", &SA_hostwfc_WT3WindFarmControlOffset, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_WT3WindFarmControlOffset!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_Offset_Demanded", &SA_hostwfc_TOGGLEROffsetDemanded, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLEROffsetDemanded!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_TotWFCTime", &SA_hostwfc_TOGGLERTotWFCTime, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLERTotWFCTime!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_WFC1Time", &SA_hostwfc_TOGGLERWFC1Time, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLERWFC1Time!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_GreedyWFCTime", &SA_hostwfc_TOGGLERGreedyWFCTime, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLERGreedyWFCTime!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_WFC2Time", &SA_hostwfc_TOGGLERWFC2Time, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLERWFC2Time!");
    return (ERROR);
}
if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_WFC3Time", &SA_hostwfc_TOGGLERWFC3Time, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value hostwfc_TOGGLERWFC3Time!");
    return (ERROR);
}

// MATLABCODEGEN: CloseField Get ITF SA Address

if (svi_GetAddr(pSviLib_hostwfc, "TOGGLER_Status", &SA_AppStatus, &SviFormat) != SVI_E_OK)
{
    LOG_W(0, Func, "Could not get address of value AppStatus!");
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

UINT32 hostwfc_MetMastWindSpeedAtHubheight_size = sizeof(hostwfc_MetMastWindSpeedAtHubheight);
UINT32 hostwfc_MetMastWindDirectionFromNorth_size = sizeof(hostwfc_MetMastWindDirectionFromNorth);
UINT32 hostwfc_WT3NacelleDirectionfromNorth_size = sizeof(hostwfc_WT3NacelleDirectionfromNorth);
UINT32 hostwfc_WT3NacelleWindMisalignment_size = sizeof(hostwfc_WT3NacelleWindMisalignment);
UINT32 hostwfc_INFLW1Status_size = sizeof(hostwfc_INFLW1Status);
UINT32 hostwfc_OFFSET1Status_size = sizeof(hostwfc_OFFSET1Status);
UINT32 hostwfc_INFLW2Status_size = sizeof(hostwfc_INFLW2Status);
UINT32 hostwfc_OFFSET2Status_size = sizeof(hostwfc_OFFSET2Status);
UINT32 hostwfc_OFFSET1Offsetdeg_size = sizeof(hostwfc_OFFSET1Offsetdeg);
UINT32 hostwfc_OFFSET2Offsetdeg_size = sizeof(hostwfc_OFFSET2Offsetdeg);
UINT32 hostwfc_FlagWindFarmControlfromTUMPLC_size = sizeof(hostwfc_FlagWindFarmControlfromTUMPLC);
UINT32 hostwfc_FlagManualSwitchWFC_size = sizeof(hostwfc_FlagManualSwitchWFC);
UINT32 hostwfc_FlagManualSwitchWFC1_size = sizeof(hostwfc_FlagManualSwitchWFC1);
UINT32 hostwfc_FlagManualSwitchGreedyWFC_size = sizeof(hostwfc_FlagManualSwitchGreedyWFC);
UINT32 hostwfc_FlagManualSwitchWFC2_size = sizeof(hostwfc_FlagManualSwitchWFC2);
UINT32 hostwfc_FlagManualSwitchWFC3_size = sizeof(hostwfc_FlagManualSwitchWFC3);
UINT32 hostwfc_OFFSET3Offsetdeg_size = sizeof(hostwfc_OFFSET3Offsetdeg);
UINT32 hostwfc_OFFSET3Status_size = sizeof(hostwfc_OFFSET3Status);
UINT32 hostwfc_TOGGLERNacelleMetMastOffset_size = sizeof(hostwfc_TOGGLERNacelleMetMastOffset);
UINT32 hostwfc_WT3PowerOutput_size = sizeof(hostwfc_WT3PowerOutput);

// MATLABCODEGEN: CloseField Size of Array definition


    // MATLABCODEGEN: OpenField assign variable from SA_Address

ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_MetMastWindSpeedAtHubheight, (UINT32*) &hostwfc_MetMastWindSpeedAtHubheight,  &hostwfc_MetMastWindSpeedAtHubheight_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_MetMastWindSpeedAtHubheight!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_MetMastWindDirectionFromNorth, (UINT32*) &hostwfc_MetMastWindDirectionFromNorth,  &hostwfc_MetMastWindDirectionFromNorth_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_MetMastWindDirectionFromNorth!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_WT3NacelleDirectionfromNorth, (UINT32*) &hostwfc_WT3NacelleDirectionfromNorth,  &hostwfc_WT3NacelleDirectionfromNorth_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_WT3NacelleDirectionfromNorth!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_WT3NacelleWindMisalignment, (UINT32*) &hostwfc_WT3NacelleWindMisalignment,  &hostwfc_WT3NacelleWindMisalignment_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_WT3NacelleWindMisalignment!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_INFLW1Status, (UINT32*) &hostwfc_INFLW1Status,  &hostwfc_INFLW1Status_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_INFLW1Status!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_OFFSET1Status, (UINT32*) &hostwfc_OFFSET1Status,  &hostwfc_OFFSET1Status_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_OFFSET1Status!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_INFLW2Status, (UINT32*) &hostwfc_INFLW2Status,  &hostwfc_INFLW2Status_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_INFLW2Status!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_OFFSET2Status, (UINT32*) &hostwfc_OFFSET2Status,  &hostwfc_OFFSET2Status_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_OFFSET2Status!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_OFFSET1Offsetdeg, (UINT32*) &hostwfc_OFFSET1Offsetdeg,  &hostwfc_OFFSET1Offsetdeg_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_OFFSET1Offsetdeg!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_OFFSET2Offsetdeg, (UINT32*) &hostwfc_OFFSET2Offsetdeg,  &hostwfc_OFFSET2Offsetdeg_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_OFFSET2Offsetdeg!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_FlagWindFarmControlfromTUMPLC, (UINT32*) &hostwfc_FlagWindFarmControlfromTUMPLC,  &hostwfc_FlagWindFarmControlfromTUMPLC_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_FlagWindFarmControlfromTUMPLC!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_FlagManualSwitchWFC, (UINT32*) &hostwfc_FlagManualSwitchWFC,  &hostwfc_FlagManualSwitchWFC_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_FlagManualSwitchWFC!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_FlagManualSwitchWFC1, (UINT32*) &hostwfc_FlagManualSwitchWFC1,  &hostwfc_FlagManualSwitchWFC1_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_FlagManualSwitchWFC1!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_FlagManualSwitchGreedyWFC, (UINT32*) &hostwfc_FlagManualSwitchGreedyWFC,  &hostwfc_FlagManualSwitchGreedyWFC_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_FlagManualSwitchGreedyWFC!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_FlagManualSwitchWFC2, (UINT32*) &hostwfc_FlagManualSwitchWFC2,  &hostwfc_FlagManualSwitchWFC2_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_FlagManualSwitchWFC2!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_FlagManualSwitchWFC3, (UINT32*) &hostwfc_FlagManualSwitchWFC3,  &hostwfc_FlagManualSwitchWFC3_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_FlagManualSwitchWFC3!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_OFFSET3Offsetdeg, (UINT32*) &hostwfc_OFFSET3Offsetdeg,  &hostwfc_OFFSET3Offsetdeg_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_OFFSET3Offsetdeg!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_OFFSET3Status, (UINT32*) &hostwfc_OFFSET3Status,  &hostwfc_OFFSET3Status_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_OFFSET3Status!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLERNacelleMetMastOffset, (UINT32*) &hostwfc_TOGGLERNacelleMetMastOffset,  &hostwfc_TOGGLERNacelleMetMastOffset_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_TOGGLERNacelleMetMastOffset!");
ret = svi_GetBlk(pSviLib_hostwfc, SA_hostwfc_WT3PowerOutput, (UINT32*) &hostwfc_WT3PowerOutput,  &hostwfc_WT3PowerOutput_size);
if (ret != SVI_E_OK)
   LOG_W(0, "SviClt_Read", "Could not read value hostwfc_WT3PowerOutput!");
 // MATLABCODEGEN: CloseField assign variable from SA_Address
    return (ret);
}
MLOCAL SINT32 SviClt_Write(VOID)
{
    SINT32  ret;
    // MATLABCODEGEN: OpenField assign variable in SviClt_Write

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_FlagWindFarmControlOperationalStatus, (UINT32*) &hostwfc_FlagWindFarmControlOperationalStatus, sizeof(hostwfc_FlagWindFarmControlOperationalStatus) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_FlagWindFarmControlOperationalStatus!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLERWFCStatus, (UINT32*) &hostwfc_TOGGLERWFCStatus, sizeof(hostwfc_TOGGLERWFCStatus) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_TOGGLERWFCStatus!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLERActiveCTRL, (UINT32*) &hostwfc_TOGGLERActiveCTRL, sizeof(hostwfc_TOGGLERActiveCTRL) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_TOGGLERActiveCTRL!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_WT3WindFarmControlOffset, (UINT32*) &hostwfc_WT3WindFarmControlOffset, sizeof(hostwfc_WT3WindFarmControlOffset) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_WT3WindFarmControlOffset!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLEROffsetDemanded, (UINT32*) &hostwfc_TOGGLEROffsetDemanded, sizeof(hostwfc_TOGGLEROffsetDemanded) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_TOGGLEROffsetDemanded!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLERTotWFCTime, (UINT32*) &hostwfc_TOGGLERTotWFCTime, sizeof(hostwfc_TOGGLERTotWFCTime) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_TOGGLERTotWFCTime!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLERWFC1Time, (UINT32*) &hostwfc_TOGGLERWFC1Time, sizeof(hostwfc_TOGGLERWFC1Time) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_TOGGLERWFC1Time!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLERGreedyWFCTime, (UINT32*) &hostwfc_TOGGLERGreedyWFCTime, sizeof(hostwfc_TOGGLERGreedyWFCTime) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_TOGGLERGreedyWFCTime!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLERWFC2Time, (UINT32*) &hostwfc_TOGGLERWFC2Time, sizeof(hostwfc_TOGGLERWFC2Time) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_TOGGLERWFC2Time!");

ret = svi_SetBlk(pSviLib_hostwfc, SA_hostwfc_TOGGLERWFC3Time, (UINT32*) &hostwfc_TOGGLERWFC3Time, sizeof(hostwfc_TOGGLERWFC3Time) );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value hostwfc_TOGGLERWFC3Time!");

 // MATLABCODEGEN: CloseField assign variable in SviClt_Write

ret = svi_SetVal(pSviLib_hostwfc, SA_AppStatus, *(UINT32*) &AppStatus );
if (ret != SVI_E_OK)
     LOG_W(0, "SviClt_Write", "Could not read value AppStatus!");





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

