/*******************************************************************************
 * 	     Project           	Rear Vision System on GM HMI2
 * (c) copyright    		2012
 * 	  Company           	Harman International 
 *                   		All rights reserved.
 * Secrecy Level     	STRICTLY CONFIDENTIAL
 *
 *  This header file includes basic RVS definitions 
 * 
 ******************************************************************************/
/**
 * @file RVSDefine.h
 * @ingroup RVS
 * @author LiZhao 
 * basic RVS definitions 
 */


#ifndef RVS_DEFINE_H_
#define RVS_DEFINE_H_

//#include <sys/neutrino.h>
//#include <screen/screen.h>
//#include <pthread.h>
//#include <time.h>
//#include <semaphore.h>
//#include "svcipc/svcipc.h"
#if 0
//#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "capture.h"
//#include "RVSInterface.h"
//#define DEMO_CAP_DRIVER_VER 1


typedef struct rvs_ctx
{
//display and drawing varibles
    screen_context_t             screen_ctx;
    screen_window_t             screen_overlaywin;    /*window for video display*/
    screen_display_t            *screen_disp;         /* native handle for our display */
    screen_buffer_t                screen_videoBuf[CAPTURE_BUF_CNT];
    rvs_DispCfg_t                   DispCfg;
    int                                     lastWindowStatus;//0 =  open 1 = close
    int                                     CameraWinStatus;   //0= open ;1=close
    rvs_NTSC_Sync_t             videoSyncInfo;//0= abnarmal ;1=normal

    int                                     zOverlay;//keep for debug
    int                                     videoInterlaceField;
    uint32_t                            videoFrameInterlaceFlags[CAPTURE_BUF_CNT];
    int                                     window_resize[2];     /* window resize parameter, [0]= width, [1] = height*/  
    int                                     transparency;         /*window transparency configuration*/
    RVS_symblAvailable_t        symblAvail;

    rvs_state                           operating_state;
    rvs_run_mode                   runMode;        /*run mode configuration*/
    bool                                   firstRun;       /*The first time run */
    
    rvs_GMLAN_t                     GMLANMessage;           /* GMLAN messages*/

    void*                                 videoCapture;
    int                                     eglSwap;
    int                                     remainDisable;      /*0 or 1:  a indication whether 2 seconds has expired */

    RVS_VehicleConfig_t            vehicleConfig;
    RVS_DriverCustom_t          driverCustom;
    RVS_DiagnosticState_t       diagnosticStat;
    
    int                                      onHysteresisTime;
    int                                      offHysteresisTime;
    float                                   disableHysteresisSpeed;
    int                                      calibFromPPS;// draw cfg from default or from pps file

    unsigned char                     videoBrightness;
    unsigned char                     videoContrast;

    //    int                       semDemoInput;    /*semphore for demo input*/
    bool                                    externalEvent;      /*Any hard mode keypress or screen touch */

    //IPC resouces
    int                         chid;                   /*channel ID */   
    int                         coid;                   /*connection ID */  
    SVCIPC_tConnection           sipcConn;
    
    rvs_MsgInfo  diagnosticMsg[eNumMsgs];   /*rendering messages for diagnostic results*/
    rvs_MsgType renderMsgType;
    RVS_Diag_Override_Ctrl_t    diagOverrideCtrl;    /*diagnostics control*///x100---debug or cr?

    //interface replace node
    RVSIntf_t* Intf;
}rvs_ctx_t;
#endif
/**
* Video capture buffers count
*/
#define CAPTURE_BUF_CNT	4



typedef enum rvs_state_t
{
    eRVS_STATE_ENABLE,
    eRVS_STATE_DISABLE,
    eRVS_STATE_OFF,
    eRVS_STATE_HYSTERESIS_ENTER_REVERSE,        //off -> enabled
    eRVS_STATE_HYSTERESIS_EXIT_REVERSE,         //enabled -> off
}rvs_state;

typedef enum RVS_FEATURE_AVAIL_VIDEO_t{
    EVideoAbsent                = 0,
    EVideoPresent               = 1,
    EVideo360                   = 2,
    EVideoAvailVideoNum
}RVS_FEATURE_AVAIL_VIDEO;

typedef enum RVS_FEATUER_AVAIL_GUIDELINES_t{
	EGdLAbscent,EGdLStatic,EGdLDynamic,EAvailGdLNum
}RVS_FEATUER_AVAIL_GUIDELINES;

typedef enum RVS_FEATURE_AVAIL_UPA_SYMBOLS_t{
	EUPASymAbsent,EUPASymPresent,EAvailUPASymNum
}RVS_FEATURE_AVAIL_UPA_SYMBOLS;

typedef struct RVS_VehicleConfig
{
	RVS_FEATURE_AVAIL_VIDEO video;
	RVS_FEATUER_AVAIL_GUIDELINES guideLine;
	RVS_FEATURE_AVAIL_UPA_SYMBOLS UPASymbol;
}RVS_VehicleConfig_t;

typedef struct RVS_DriverCustom{
	bool RVS_Video;
	bool RVS_Guidelines;
	bool RVS_ParkAsstSymbols;
}RVS_DriverCustom_t;

typedef struct RVS_DiagnosticState{
	bool RVS_Failed_Sync;
	bool RVS_Failed_Steering;
	bool RVS_Failed_UPA;
	bool RVS_Failed_Transmission;
	bool RVS_Failed_Speed;
	bool RVS_Failed_SWASensor;  //adding for monitor RVS_MSG_CALIB_STEERING message
}RVS_DiagnosticState_t;

/*
 * vehicle movement state parameter begin
 */

typedef enum rvs_VehicleMovementState{
	eRVS_VEHICLE_MOVEMENT_STATE_PARKED,
	eRVS_VEHICLE_MOVEMENT_STATE_NEUTRAL,
	eRVS_VEHICLE_MOVEMENT_STATE_FORWARD,
	eRVS_VEHICLE_MOVEMENT_STATE_REVERSE,
	eRVS_VEHICLE_MOVEMENT_STATE_INVALID
}rvs_VehicleMovementState_t;

/*
 * vehicle movement state parameter end
 */

/*
 * vehicle speed parameter begin
 */

/*
 * Vehicle Speed Validity
 */
typedef enum rvs_VehicleSpeed_Validity{
	eRVS_VEHICLE_SPEED_VALID             =   0x00,
	eRVS_VEHICLE_SPEED_INVALID     	 =   0x01
}rvs_VehicleSpeed_Validity_t;

typedef struct rvs_VehicleSpeed
{
	rvs_VehicleSpeed_Validity_t ValidityFlag;//bit 0
	float Speed;
}rvs_VehicleSpeed_t;

/*
 * vehicle speed parameter end
 */


/*
 * ParkAssist parameter begin
 */

//ParkAssistRearRegionObjectStatus
typedef enum rvs_PARearRegionObjectStatus{
	eRVS_PA_OBJECT_STATUS_UNKNOWN,
	eRVS_PA_OBJECT_STATUS_ZONE_1,
	eRVS_PA_OBJECT_STATUS_ZONE_2,
	eRVS_PA_OBJECT_STATUS_ZONE_3,
	eRVS_PA_OBJECT_STATUS_ZONE_4,
	eRVS_PA_OBJECT_STATUS_ZONE_5,
	eRVS_PA_OBJECT_STATUS_ZONE_6,
	eRVS_PA_OBJECT_STATUS_ZONE_7,
	eRVS_PA_OBJECT_STATUS_ZONE_8,
	eRVS_PA_OBJECT_STATUS_ZONE_9,
	eRVS_PA_OBJECT_STATUS_ZONE_10,
	eRVS_PA_OBJECT_STATUS_ZONE_11,
	eRVS_PA_OBJECT_STATUS_ZONE_12,
	eRVS_PA_OBJECT_STATUS_ZONE_13,
	eRVS_PA_OBJECT_STATUS_ZONE_14,
	eRVS_PA_OBJECT_STATUS_ZONE_15
}rvs_PARearRegionObjectStatus_t;

//ParkAssistRearSystemStatus
typedef enum rvs_PARearSystemStatus{
	eRVS_PA_SYSTEM_STATUS_DISABLED,
	eRVS_PA_SYSTEM_STATUS_ENABLED,
	eRVS_PA_SYSTEM_STATUS_INHIBITED,
	eRVS_PA_SYSTEM_STATUS_FAILED
}rvs_PARearSystemStatus_t;

typedef struct RVS_PARearStatus{
	rvs_PARearRegionObjectStatus_t PARearRegion1ObjectStatus;
	rvs_PARearRegionObjectStatus_t PARearRegion2ObjectStatus;
	rvs_PARearRegionObjectStatus_t PARearRegion3ObjectStatus;
    rvs_PARearRegionObjectStatus_t PARearRegion4ObjectStatus;
	float PARearExtendedDistance;
	rvs_PARearSystemStatus_t PARearSystemStatus;
}RVS_PARearStatus_t;

/*
 * ParkAssist parameter end
 */

/*
 * Rear Cross Traffic Alert parameter begin
 */
typedef enum rvs_RCTAIndicationCtl{
	eRVS_OUTSIDE_AMBIENT_LIGHT_LEVEL_UNKNOWN,
	eRVS_RCTA_CONTINUOUS_INDICATION,
	eRVS_RCTA_FLASHING_INDICATION
}rvs_RCTAIndicationCtl_t;

typedef struct rvs_RCTAState{
	unsigned int RCTAIndication;//using bit0
	rvs_RCTAIndicationCtl_t RCTAIndicationControl;
}rvs_RCTAState_t;
/*
 * Rear Cross Traffic Alert parameter end
 */


/*
 * Steering Wheel Angle Validity 
 */
typedef enum rvs_SteeringWheelAngle_Validity{
	eRVS_STEERING_WHEEL_ANGLE_VALID             =   0x00,
	eRVS_STEERING_WHEEL_ANGLE_VALID_INVALID     =   0x01
}rvs_SteeringWheelAngle_Validity_t;


/*
 * Steering Wheel Angle Sensor Calibration Status 
 */
typedef enum rvs_SteeringWheelAngle_SensorCalibrationStatus{
	eRVS_STEERING_WHEEL_ANGLE_SENSOR_CALIBRATION_STATUS_UNKNOW             =   0x00,
	eRVS_STEERING_WHEEL_ANGLE_SENSOR_CALIBRATION_STATUS_ESTIMATED          =   0x01,
	eRVS_STEERING_WHEEL_ANGLE_SENSOR_CALIBRATION_STATUS_CALIBRATED         =   0x02
}rvs_SteeringWheelAngle_SensorCalibrationStatus_t;


/*
 * SteeringWheelControlSwitchStatus begin
 */
typedef enum rvs_SWC_SwitchStatus{
		    SWC_ALL_RELEASED = 0x00,
			SWC_BAND_PRESSED = 0x01,
			SWC_VOLUME_UP_PRESSED = 0x02,
			SWC_VOLUME_DOWN_PRESSED = 0x03,
			SWC_NEXT_PRESSED = 0x04,
			SWC_PREVIOUS_PRESSED = 0x05,
			SWC_PTT_PRESSED = 0x06,
			SWC_END_PRESSED = 0x07,
			SWC_SRC_PRESSED = 0x08
}rvs_SWC_SwitchStatus_t;
/*
 * SteeringWheelControlSwitchStatus begin
 */


/*
 * HSGMLAN Message - System Power mode
 */

typedef enum 
{
	eRVS_SYSPWRMD_OFF       =   0x00,
	eRVS_SYSPWRMD_ACCESSORY =   0x01,
	eRVS_SYSPWRMD_RUN       =   0x02,
	eRVS_SYSPWRMD_CRUNKREQ  =   0x03	
}rvs_SystemPowerMode;


/*
 * HSGMLAN Message - BCM Communication
 */

typedef enum 
{
	eRVS_BCMComm_NORMAL         =   0x00,       /* no timeout has occurred */
	eRVS_BCMComm_TIMEOUT        =   0x01        /* timeout has occurred */
}rvs_BCMComm;

/*
 * HSGMLAN Message -Direct enable camera(from hmi or hard key)
 */

typedef enum 
{
	eRVS_DIRECT_DISPLAY_OFF      =   0x00,          /*Direct enable camera on */
	eRVS_DIRECT_DISPLAY_ON        =   0x01        /* Direct enable camera off */
}rvs_DirectDisplay;

/*
 * GMLAN parameter begin
 */
typedef struct rvs_GMLAN{
    /*LS-GMLAN*/
    RVS_PARearStatus_t          PARearStatus;
    rvs_RCTAState_t               RCTALeft;
    rvs_RCTAState_t               RCTARight;
    rvs_SWC_SwitchStatus_t    SWCSwitchStatus;

    /*HS-GMLAN*/
    rvs_VehicleMovementState_t  VehicleMoveState;
    float                         steeringWheelAngle;
    rvs_SteeringWheelAngle_Validity_t   SWAValidity;
    rvs_SteeringWheelAngle_SensorCalibrationStatus_t  SWASensorCalibStatus;
    rvs_BCMComm                 BCMComm;
    rvs_DirectDisplay               DirectDisplay;
    rvs_SystemPowerMode         sysPwrMd;
    rvs_VehicleSpeed_t          VehicleSpeed;

    bool                        CPMImageRequest;        // From CPM module,  0 -Don't display,  1- display camera images    
}rvs_GMLAN_t;
/*
 * GMLAN parameter end
 */

/*
 * RVS message parameter begin
 */

#define MAXMSGLENGTH 64

//not uniformed,based on screen size(0~W, 0~H)
typedef struct screen_coord_t
{
	int u;
	int v;
}screenCoord;

typedef enum rvs_MsgType_t {
	RVS_MSG_FAILED_SYNC,
	RVS_MSG_FAILED_TRANSMISSION,
//	RVS_MSG_PROPER_USAGE,
	RVS_MSG_GUIDELINES_FAIL,
	RVS_MSG_CALIB_STEERING,
	RVS_MSG_PARK_ASST_FAIL,
	eNumMsgs,
}rvs_MsgType;

//postion for messages to render
typedef enum rvs_MsgPos_t {
	RVS_MSG_LINE1 = 1,
	RVS_MSG_LINE2 = 2,
	RVS_MSG_CENTER
}rvs_MsgPos;

#define MSGPOS_FAIL_SYNC  RVS_MSG_CENTER
#define MSGPOS_FAIL_GUIDELINE RVS_MSG_LINE2
#define MSGPOS_CALIB_STEERING RVS_MSG_LINE2
#define MSGPOS_FAIL_PARKASSIST RVS_MSG_LINE2
#define MSGPOS_FAIL_TRANSMISSION RVS_MSG_CENTER

//#define MSGPOS_LINE1_OFFSET 0
//#define MSGPOS_LINE2_OFFSET 10
//#define MSGPOS_CENTER_OFFSET (SCREEN_H/2)

#define SCREEN_TOTAL_LINENUM   5
#define SCREEN_LINE1 1
#define SCREEN_LINE2 2
#define SCREEN_LINE_CENTER 3

typedef struct rvs_MsgInfo_t{
	char msgString[MAXMSGLENGTH];
//	screenCoord msgPos;
	int verticalLine;
}rvs_MsgInfo;

/*
 * RVS message parameter end
 */

typedef enum rvs_NTSC_Sync{
	eRVS_NTSC_SYNC_INVALID,
	eRVS_NTSC_SYNC_VALID
}rvs_NTSC_Sync_t;


/*
* Hysteresis timer definitions
*/
typedef void* RVSTimer_context;
typedef void (*RVSTimer_callback)(RVSTimer_context context);

#define TIMER_PULSE_CODE                			 _PULSE_CODE_MINAVAIL
#define GMLAN_PULSE_CODE                			(_PULSE_CODE_MINAVAIL + 1)
#define VIDEO_CONTROL_PULSE_CODE        			(_PULSE_CODE_MINAVAIL + 2)
#define DRIVER_CUSTOM_PULSE_CODE        			(_PULSE_CODE_MINAVAIL + 3)
#define EXTERNAL_EVENTS_PULSE_CODE      			(_PULSE_CODE_MINAVAIL + 4)
#define NTSC_SYNC_PULSE_CODE                			(_PULSE_CODE_MINAVAIL + 5)


/*
* Thread communication message  
*/
typedef union my_message{
       // struct _pulse   pulse;
        /* your other message structures would go here too */
} my_message_t;

/*
* Camera video control
*/
typedef enum rvs_video_control_t{
    eRVS_VIDEO_CONTROL_BRIGHTNESS   =   0x00,
    eRVS_VIDEO_CONTROL_CONTRAST     =   0x01
}rvs_video_control;

/*
 * driver customization control
 */
typedef enum rvs_driver_custom_t{
	eRVS_DRIVER_CUSTOM_GUIDELINE   = 0x00,
			eRVS_DRIVER_CUSTOM_UPA  = 0x01
}rvs_driver_custom;


typedef enum rvs_run_mode
{
    eRVS_RUN_MODE_ALL       = 0x00,     //As GM required
    eRVS_RUN_MODE_SIMPLE    = 0x01      //Simple run mode
}rvs_run_mode_t;


/**
*  Indications of symbol files(UPA, RCTA) available on file system
*/
typedef struct RVS_Available
{
    bool    UPAResourceAvail; 
    bool    RCTAResourceAvail;
}RVS_symblAvailable_t;


typedef enum _RVS_Override_Mode
{
    eDIAG_OVERRIDE_NO_ACTION  =   0,
    eDIAG_OVERRIDE_DISABLE    =   1,
    eDIAG_OVERRIDE_ENABLE     =   2
}RVS_Override_Mode;


typedef enum _RVS_Override_SWPos
{
    eDIAG_OVERRIDE_SWPOS_ZERO     =   0,
    eDIAG_OVERRIDE_SWPOS_GMLAN    =   1
}RVS_Override_SWPos;


/*
* GuideLineControl:           0=No action, 1=Disable, 2=Enable
* RPADataControl:             0=No action, 1=Disable, 2=Enable
* SteeringWheelPosOvr:     0=0 Deg, 1=Use GMLAN Message Data
* RearCameraControl:        0=No action, 1=Camera Display Off, 2=Camera Display On
*/
typedef struct RVS_Diag_Override_Ctrl
{
    RVS_Override_Mode   guideLineControl;
    RVS_Override_Mode   RPADataControl;
    RVS_Override_SWPos  steeringWheelPosOvr;
    RVS_Override_Mode   rearCameraControl;
}RVS_Diag_Override_Ctrl_t;

typedef struct _rvs_videoCfg
{
    int     device;         /* device index */
    int     source;         /* input source index */
    int     source_type;    /* input source type */
    int     sfsize[2];      /* source frame wndsize */
    int     dfsize[2];      /* destination frame wndsize */
    int     bsize[2];       /* buffer size */
    int     wndsize[2];        /* size of the window */
    int     pos[2];         /* position of the window */
    int     ssize[2];       /* size of the source viewport */
    int     spos[2];        /* position of the source viewport */
    int     csize[2];       /* size for cropping */
    int     cpos[2];        /* position for cropping */
    int     format;         /* buffer format */
    int     pipeline;       /* wfd pipeline id */
    double  frame_rate;     /* expected frame rate (frames per second)*/
    int     video_info_frame_cnt;   /*Checks the video information every [int] frames*/
}rvs_videoCfg_t;

typedef struct _rvs_CapCfg
{
    int     device;         /* device index */
    int     source;         /* input source index */
    int     source_type;    /* input source type */
    int     sfsize[2];      /* source frame wndsize */
    int     dfsize[2];      /* destination frame wndsize */
    int     csize[2];       /* size for cropping */
    int     cpos[2];        /* position for cropping */
    int     format;         /* buffer format */
    int     video_info_frame_cnt;   /*Checks the video information every [int] frames,0=no check*/
    double  frame_rate;     /* expected frame rate (frames per second)*/
    
    unsigned int  frameflags_rt[CAPTURE_BUF_CNT];//runtime params from cap moudle,indicated the frame interlace type
}rvs_CapCfg_t;

typedef struct _rvs_DispCfg
{
    int     bsize[2];       /* buffer size */
    int     wndsize[2];   /* size of the window */
    int     pos[2];         /* position of the window */
    int     ssize[2];       /* size of the source viewport */
    int     spos[2];        /* position of the source viewport */
    int     format;         /* buffer format */
    int     pipeline;       /* wfd pipeline id */
    
    int     stride_rt;      //runtime params from disp moudle,
    int     rendbufcnts_rt;
    void *pscreenbuf_rt[CAPTURE_BUF_CNT];
}rvs_DispCfg_t;
typedef struct rvs_ctx
{

    rvs_DispCfg_t                   DispCfg;
    int                                     lastWindowStatus;//0 =  open 1 = close
    int                                     CameraWinStatus;   //0= open ;1=close
    rvs_NTSC_Sync_t             videoSyncInfo;//0= abnarmal ;1=normal

    int                                     zOverlay;//keep for debug
    int                                     videoInterlaceField;

    int                                     window_resize[2];     /* window resize parameter, [0]= width, [1] = height*/  
    int                                     transparency;         /*window transparency configuration*/
    RVS_symblAvailable_t        symblAvail;

    rvs_state                           operating_state;
    rvs_run_mode                   runMode;        /*run mode configuration*/
    bool                                   firstRun;       /*The first time run */
    
    rvs_GMLAN_t                     GMLANMessage;           /* GMLAN messages*/

    void*                                 videoCapture;
    int                                     eglSwap;
    int                                     remainDisable;      /*0 or 1:  a indication whether 2 seconds has expired */

    RVS_VehicleConfig_t            vehicleConfig;
    RVS_DriverCustom_t          driverCustom;
    RVS_DiagnosticState_t       diagnosticStat;
    
    int                                      onHysteresisTime;
    int                                      offHysteresisTime;
    float                                   disableHysteresisSpeed;
    int                                      calibFromPPS;// draw cfg from default or from pps file

    unsigned char                     videoBrightness;
    unsigned char                     videoContrast;

    //    int                       semDemoInput;    /*semphore for demo input*/
    bool                                    externalEvent;      /*Any hard mode keypress or screen touch */

    //IPC resouces
    int                         chid;                   /*channel ID */   
    int                         coid;                   /*connection ID */  

    
    rvs_MsgInfo  diagnosticMsg[eNumMsgs];   /*rendering messages for diagnostic results*/
    rvs_MsgType renderMsgType;
    RVS_Diag_Override_Ctrl_t    diagOverrideCtrl;    /*diagnostics control*///x100---debug or cr?


}rvs_ctx_t;

#define RENDFREQ 60

#define SCREEN_W 800
#define SCREEN_H 480

#define PIX_W 720
#define PIX_H 480


#define TOTAL_VIDEO_BUFFER_SIZE     4
#define TOTAL_OVERLAY_BUFFER_SIZE   1  


#define DBUS_METHOD_STRING_SET_OPERATING_STATE  "setOperatingState"
#define DBUS_METHOD_STRING_GET_OPERATING_STATE  "getOperatingState"

#define DBUS_METHOD_STRING_VMS                  "setVehicleMovementState"
#define DBUS_METHOD_STRING_PAREARSTATUS         "setPARearStatus"
#define DBUS_METHOD_STRING_LEFTRCTA             "setLeftRCTA"
#define DBUS_METHOD_STRING_RIGHTRCTA			"setRightRCTA"


#define DBUS_METHOD_STRING_VEHICLE_POWER_MODE   "setVehiclePowerMode"

#define DBUS_METHOD_STRING_EGLSWAP              "setEglSwap"

//video property settings(contrast, brightness)
#define DBUS_METHOD_STRING_SLIDERAVAILABLE      "videoSliderAvailable"
#define DBUS_METHOD_STRING_SET_BRIGHTNESS       "setBrightness"
#define DBUS_METHOD_STRING_SET_CONTRAST         "setContrast"
#define DBUS_METHOD_STRING_GETVIDEOBRIGHTNESS   "getBrightness"
#define DBUS_METHOD_STRING_GETVIDEOCONTRAST     "getContrast"
#define DBUS_METHOD_STRING_SLIDER_STATUS        "getSliderStatus"


//driver customization
#define DBUS_METHOD_STRING_SETUPSCREENAVAILABLE  "setupScreenAvailable"
#define DBUS_METHOD_STRING_GUIDELINESETAVAILABLE  "guidelineSetAvailable"
#define DBUS_METHOD_STRING_GETGUIDELINESTATUS     "getGuidelineStatus"
#define DBUS_METHOD_STRING_SETGUIDELINESTATUS     "setGuidelineStatus"
#define DBUS_METHOD_STRING_UPASETAVAILABLE        "UPASetAvailable"
#define DBUS_METHOD_STRING_GETUPASTATUS           "getUPAStatus"
#define DBUS_METHOD_STRING_SETUPASTATUS           "setUPAStatus"

#define DBUS_METHOD_STRING_SETCPMREQUSE     "setCPMRequest"

#define DBUS_METHOD_STRING_GETSETUPSCREENSTATUS   "getDriverCustomStatus"

#define DBUS_METHOD_STRING_RESIZE                 "resize"  
#define DBUS_METHOD_STRING_GETMSGINFO        "getMessageInfo"

/*
*   set Z Order
*/
#define DBUS_METHOD_STRING_SET_ZORDER             "setZOrder"  

/*
*Diagnostics API 
*/
#define DBUS_METHOD_STRING_DIAG_GET_VI                  "RearCameraInputSignalCircuit"
#define DBUS_METHOD_STRING_DIAG_OVERRIDE                "Override" 
#define DBUS_PARAM_STRING_NAME_GUIDELINE_CONTROL        "GuideLineControl"
#define DBUS_PARAM_STRING_NAME_RPADATA_CONTROL          "RPADataControl"
#define DBUS_PARAM_STRING_NAME_SWPOS_CONTROL            "SteeringWheelPosOvr"
#define DBUS_PARAM_STRING_NAME_CAMERA_CONTROL           "RearCameraControl"


/*
 * message info param
 */
#define DBUS_PARAM_STRING_NAME_BRENDER    "bRender"
#define DBUS_PARAM_STRING_NAME_STRING    "string"
#define DBUS_PARAM_STRING_NAME_VERTICALPOS "verticalPos"


/*
 *  PA rear status parameter
 */
#define DBUS_PARAM_STRING_NAME_REGION1           "region1"
#define DBUS_PARAM_STRING_NAME_REGION2           "region2"
#define DBUS_PARAM_STRING_NAME_REGION3           "region3"
#define DBUS_PARAM_STRING_NAME_EXTENDDIS         "extendDis"
#define DBUS_PARAM_STRING_NAME_SYSTEMSTATUS      "systemStatus"

#define DBUS_PARAM_STRING_VALUE_DISABLED              "disabled"
#define DBUS_PARAM_STRING_VALUE_ENABLED               "enabled"
#define DBUS_PARAM_STRING_VALUE_INHIBITED             "inhibited"
#define DBUS_PARAM_STRING_VALUE_FAILED                "failed"

/*
 * vehicle movement state parameters
 */
#define DBUS_PARAM_STRING_NAME_STATE                   "state"
#define DBUS_PARAM_STRING_VALUE_PARKED                 "parked"
#define DBUS_PARAM_STRING_VALUE_NEUTRAL                "neutral"
#define DBUS_PARAM_STRING_VALUE_FORWARD                "forward"
#define DBUS_PARAM_STRING_VALUE_REVERSE                "reverse"
#define DBUS_PARAM_STRING_VALUE_INVALID                "invalid"


/*
 * RCTA parameter
 */
#define DBUS_PARAM_STRING_NAME_INDICATION             "indication"
#define DBUS_PARAM_STRING_NAME_INDICATIONCNTL         "indicationCntl"

#define DBUS_PARAM_STRING_NAME_DATA                    "data"
#define DBUS_PARAM_STRING_VALUE_UNKNOWN                "unknown"
#define DBUS_PARAM_STRING_VALUE_CONTINUOUS             "continuous"
#define DBUS_PARAM_STRING_VALUE_FLASHING               "flashing"

/*
*   set Z Order
*/
#define DBUS_PARAM_STRING_NANE_ZVIDEO                  "zVideo"
#define DBUS_PARAM_STRING_NANE_ZGRAGHICS               "zGraphics"


/*
*   set video contrast and brighteness
*/
#define DBUS_PARAM_STRING_NANE_CONTRAST                  "contrast"
#define DBUS_PARAM_STRING_NANE_BRIGHTNESS                "brightness"

//temp defines
#define RVS_STEERING_WHEEL_DELTA 5

#define RVS_REMAIN_DISABLE_TIMEOUT        2       //  2 seconds 

#define RVS_UPA_FLASH_FREQUENCY 4
#define RVS_UPA_FLASH_DURATION 3
//RVS_GUIDELINE_MARKER_STARTDIS+(RVS_OVLAY_NUM_DIST_MARKS-1)*RVS_OVLAY_DELTA_DIST_MARKS should= FAR_END DISTANCE
//RVS_GUIDELINE_L_SEGMENT_DISTANCE <= 1M as CR from GM
#define RVS_GUIDELINE_GROUP_NUM         4     //set L segment dist length to zero. the guidle line out from bumper has 2 style:0.5m and 1m & red and orange----but allocate??
#define RVS_GUIDELINE_L_SEGMENT_DISTANCE   1              //should <1.0 as L segment out the bumper within 1m
#define RVS_GUIDELINE_FAR_END_DISTANCE   6.5                //the far end of the guideline in the realworld, 5 as 5m which  should equal the far distance of the camera view
#define RVS_GUIDELINE_L_SEGMENT_LENGTH    10.0/320 //(10.0/320.0)the length of the L segment which extend inside of side guide line
#define RVS_GUIDELINE_MARKER_STARTDIS    2.0    //the begin distance of the guideline = 1M
#define RVS_GUIDELINE_WIDTH             (4) //the width in pixels of the line dispalyed, not the length =4/320

#define RVS_COLOR_RED                   {1.0,0.0,0.0}
#define RVS_COLOR_YELLOW                {1.0,1.0,0.0}
#define RVS_COLOR_GREEN                {0.0,1.0,0.0}

#define RVS_OVLAY_MARKER_WIDTH 2.72    //define the width of the distance line ---2.72=2.72m in the real world should equal the width of the car
#define RVS_OVLAY_DELTA_DIST_MARKS 1    // the distance of two lines which between 2 side line, as in realworld repesents 1 m
#define RVS_OVLAY_NUM_DIST_MARKS 1  // the num of line nums you will see on the overlaywindow which mark the distance in the real world(1 m in GM as CR)
#define RVS_OVLAY_LINE_WIDTH 5

/*
 * RCTA definition
 */
#define RVS_RCTA_ICON_SIZE          0.1125
#define RVS_RCTA_ICON_LEFTU         0.25
#define RVS_RCTA_ICON_LEFTV         0.5
#define RVS_RCTA_ICON_RIGHTU        0.75
#define RVS_RCTA_ICON_RIGHTV        0.5
#define RVS_RCTA_ICON_FLASH_FREQUENCY  4

/*
 * UPA definition
 */
#define RVS_UPA_SIZE_ZONE0   0.0
#define RVS_UPA_SIZE_ZONE1   0.225
#define RVS_UPA_SIZE_ZONE2   0.1875
#define RVS_UPA_SIZE_ZONE3   0.15
#define RVS_UPA_SIZE_ZONE4   0.1125

//RVS_PACKED_PARK_ASST_PARAMS
#define RVS_UPA_CENTER_U_PIXEL_1 0.6875
#define RVS_UPA_CENTER_V_PIXEL_1 0.3125
#define RVS_UPA_CENTER_U_PIXEL_2 0.5125
#define RVS_UPA_CENTER_V_PIXEL_2 0.3125
#define RVS_UPA_CENTER_U_PIXEL_3 0.3063
#define RVS_UPA_CENTER_V_PIXEL_3 0.3125
#define RVS_UPA_CENTER_U_PIXEL_4 0.7563
#define RVS_UPA_CENTER_V_PIXEL_4 0.4417
#define RVS_UPA_CENTER_U_PIXEL_5 0.5125
#define RVS_UPA_CENTER_V_PIXEL_5 0.4417
#define RVS_UPA_CENTER_U_PIXEL_6 0.2438
#define RVS_UPA_CENTER_V_PIXEL_6 0.4417
#define RVS_UPA_CENTER_U_PIXEL_7 0.8125
#define RVS_UPA_CENTER_V_PIXEL_7 0.5667
#define RVS_UPA_CENTER_U_PIXEL_8 0.5125
#define RVS_UPA_CENTER_V_PIXEL_8 0.575
#define RVS_UPA_CENTER_U_PIXEL_9 0.1875
#define RVS_UPA_CENTER_V_PIXEL_9 0.5667
#define RVS_UPA_CENTER_U_PIXEL_10 0.85
#define RVS_UPA_CENTER_V_PIXEL_10 0.6792
#define RVS_UPA_CENTER_U_PIXEL_11 0.5063
#define RVS_UPA_CENTER_V_PIXEL_11 0.725
#define RVS_UPA_CENTER_U_PIXEL_12 0.15
#define RVS_UPA_CENTER_V_PIXEL_12 0.6792

#define RVS_K_UPA_TYPE 0

#define RVS_TEXT_LOCATION 0


//typedef float color3[3];
#define RVS_BUS_NAME    "com.harman.service.RearVisionSystem"
#define RVS_OBJ_PATH    "/com/harman/service/RearVisionSystem"


/*
 * For PPS Initialization
 */
#define RVS_PPS_BUS_NAME "com.harman.service.PersistentKeyValue"
#define RVS_PPS_OBJ_PATH "/com/harman/service/PersistentKeyValue"


#define RVS_LAYERMANAGER_BUS_NAME "com.harman.service.LayerManager"
#define RVS_LAYERMANAGER_OBJ_PATH "/com/harman/service/LayerManager"

#define RVS_ISPSCREEN_BUS_NAME "com.harman.service.VideoManager"
#define RVS_ISPSCREEN_OBJ_PATH "/com/harman/service/VideoManager"


//pps data precision

typedef struct rvs_video_params_t
{
	unsigned char brightness;
	unsigned char contrast;
}rvs_video_params;

typedef struct rvs_misc_params_t
{
	unsigned int onHysteresis;
	unsigned int offHysteresis;
	float disableHysteresisSpeed;
	bool videoAvail;
	int guideLineAvail;
	bool UPAAvail;
	bool textLoc;
//	unsigned int steerWheelDelta;
//	unsigned int upaType;
}rvs_misc_params;

typedef struct screen_pos_t
{
	float u;
	float v;
}screenPos;
#define UPAPOSNUM 12
typedef struct rvs_parkAssist_params_t
{
	screenPos pixel[UPAPOSNUM];
	unsigned int upaType;
}rvs_parkAssist_params;

#define RCTAPOSNUM 2
typedef struct rvs_rcta_params_t
{
//	unsigned int rctaEnable;
	screenPos pixel[RCTAPOSNUM];
}rvs_rcta_params;

#define MAXMSGLENGTH 64
#define DRIVERMSGNUM 6
//typedef struct rvs_driverMsg_t
//{
//	char failSync[MAXMSGLENGTH];
//	char failTransmission[MAXMSGLENGTH];
////	char properUsage[MAXMSGLENGTH];
//	char failGuideLine[MAXMSGLENGTH];
//	char failCalibSteering[MAXMSGLENGTH];
//	char failParkAsst[MAXMSGLENGTH];
//}rvs_driverMsg;

//calibration--x100
#define RVS_STRING_ON_HYSTERESIS  "RVS_ON_HYSTERESIS"
#define RVS_STRING_FEATURE_AVAIL_VIDEO  "RVS_FEATURE_AVAIL_VIDEO"

//RVS_MISC_PARAMS--x100
#define RVS_STRING_OFF_HYSTERESIS  "RVS_OFF_HYSTERESIS"
#define RVS_STRING_DISABLE_HYSTERESIS_SPEED  "RVS_DISABLE_HYSTERESIS_SPEED"
#define RVS_STRING_FEATURE_AVAIL_GUIDELINES  "RVS_FEATURE_AVAIL_GUIDELINES"
#define RVS_STRING_STEERING_WHEEL_DELTA "RVS_STEERING_WHEEL_DELTA"
//RVS_MISC_PARAMS--gm
#define RVS_STRING_K_UPA_TYPE       "K_UPA_TYPE"
#define RVS_STRING_FEATURE_AVAIL_UPA_SYMBOLS  "RVS_FEATURE_AVAIL_UPA_SYMBOLS"
#define RVS_STRING_TEXT_LOCATION  "RVS_TEXT_LOCATION"


//RVS_PACKED_CAMERA_PARAMS
#define RVS_STRING_CAMERA_ROTATION_X  "RVS_CAMERA_ROTATION_X"
#define RVS_STRING_CAMERA_ROTATION_Y  "RVS_CAMERA_ROTATION_Y"
#define RVS_STRING_CAMERA_ROTATION_Z  "RVS_CAMERA_ROTATION_Z"
#define RVS_STRING_CAMERA_OFFSET_X    "RVS_CAMERA_OFFSET_X"
#define RVS_STRING_CAMERA_OFFSET_Y    "RVS_CAMERA_OFFSET_Y"
#define RVS_STRING_CAMERA_OFFSET_Z    "RVS_CAMERA_OFFSET_Z"
#define RVS_STRING_CAMERA_FOCAL_LENGTH_U  "RVS_CAMERA_FOCAL_LENGTH_U"
#define RVS_STRING_CAMERA_FOCAL_LENGTH_V  "RVS_CAMERA_FOCAL_LENGTH_V"
#define RVS_STRING_CAMERA_DISTORT_COEF_1  "RVS_CAMERA_DISTORT_COEF_1"
#define RVS_STRING_CAMERA_DISTORT_COEF_2  "RVS_CAMERA_DISTORT_COEF_2"
#define RVS_STRING_CAMERA_OPTICAL_OFFSET_U  "RVS_CAMERA_OPTICAL_OFFSET_U"
#define RVS_STRING_CAMERA_OPTICAL_OFFSET_V  "RVS_CAMERA_OPTICAL_OFFSET_V"

//RVS_STEER
//x100tbd RVS_OVLAY_MARKER_WIDTH
#define RVS_STRING_OVLAY_TRACK_WIDTH  "RVS_OVLAY_TRACK_WIDTH"
#define RVS_STRING_OVLAY_MARKS_PARAM  "RVS_OVLAY_MARKS_PARAM"
#define RVS_STRING_STEER_REAR_AXLE_OFFSET  "RVS_STEER_REAR_AXLE_OFFSET"
#define RVS_STRING_STEER_INVERSE_FRONT_RATIO  "RVS_STEER_INVERSE_FRONT_RATIO"
#define RVS_STRING_STEER_INVERSE_REAR_RATIO  "RVS_STEER_INVERSE_REAR_RATIO"
#define RVS_STRING_STEER_WHEELBASE  "RVS_STEER_WHEELBASE"
#define RVS_STRING_STEER_SATURATION_ANGLE  "RVS_STEER_SATURATION_ANGLE"

//RVS_ParkAssit
#define RVS_STRING_UPA_CENTER_U_PIXEL_1  "RVS_UPA_CENTER_U_PIXEL_1"
#define RVS_STRING_UPA_CENTER_V_PIXEL_1  "RVS_UPA_CENTER_V_PIXEL_1"
#define RVS_STRING_UPA_CENTER_U_PIXEL_2  "RVS_UPA_CENTER_U_PIXEL_2"
#define RVS_STRING_UPA_CENTER_V_PIXEL_2  "RVS_UPA_CENTER_V_PIXEL_2"
#define RVS_STRING_UPA_CENTER_U_PIXEL_3  "RVS_UPA_CENTER_U_PIXEL_3"
#define RVS_STRING_UPA_CENTER_V_PIXEL_3  "RVS_UPA_CENTER_V_PIXEL_3"
#define RVS_STRING_UPA_CENTER_U_PIXEL_4  "RVS_UPA_CENTER_U_PIXEL_4"
#define RVS_STRING_UPA_CENTER_V_PIXEL_4  "RVS_UPA_CENTER_V_PIXEL_4"
#define RVS_STRING_UPA_CENTER_U_PIXEL_5  "RVS_UPA_CENTER_U_PIXEL_5"
#define RVS_STRING_UPA_CENTER_V_PIXEL_5  "RVS_UPA_CENTER_V_PIXEL_5"
#define RVS_STRING_UPA_CENTER_U_PIXEL_6  "RVS_UPA_CENTER_U_PIXEL_6"
#define RVS_STRING_UPA_CENTER_V_PIXEL_6  "RVS_UPA_CENTER_V_PIXEL_6"
#define RVS_STRING_UPA_CENTER_U_PIXEL_7  "RVS_UPA_CENTER_U_PIXEL_7"
#define RVS_STRING_UPA_CENTER_V_PIXEL_7  "RVS_UPA_CENTER_V_PIXEL_7"
#define RVS_STRING_UPA_CENTER_U_PIXEL_8  "RVS_UPA_CENTER_U_PIXEL_8"
#define RVS_STRING_UPA_CENTER_V_PIXEL_8  "RVS_UPA_CENTER_V_PIXEL_8"
#define RVS_STRING_UPA_CENTER_U_PIXEL_9  "RVS_UPA_CENTER_U_PIXEL_9"
#define RVS_STRING_UPA_CENTER_V_PIXEL_9  "RVS_UPA_CENTER_V_PIXEL_9"
#define RVS_STRING_UPA_CENTER_U_PIXEL_10  "RVS_UPA_CENTER_U_PIXEL_10"
#define RVS_STRING_UPA_CENTER_V_PIXEL_10  "RVS_UPA_CENTER_V_PIXEL_10"
#define RVS_STRING_UPA_CENTER_U_PIXEL_11  "RVS_UPA_CENTER_U_PIXEL_11"
#define RVS_STRING_UPA_CENTER_V_PIXEL_11  "RVS_UPA_CENTER_V_PIXEL_11"
#define RVS_STRING_UPA_CENTER_U_PIXEL_12  "RVS_UPA_CENTER_U_PIXEL_12"
#define RVS_STRING_UPA_CENTER_V_PIXEL_12  "RVS_UPA_CENTER_V_PIXEL_12"

//RVS_RCTA
#define RVS_STRING_RCTA_CENTER_U_PIXEL_1  "RVS_RCTA_CENTER_U_PIXEL_1"
#define RVS_STRING_RCTA_CENTER_V_PIXEL_1  "RVS_RCTA_CENTER_V_PIXEL_1"
#define RVS_STRING_RCTA_CENTER_U_PIXEL_2  "RVS_RCTA_CENTER_U_PIXEL_2"
#define RVS_STRING_RCTA_CENTER_V_PIXEL_2  "RVS_RCTA_CENTER_V_PIXEL_2"

//RVS_DriverCustom
#define RVS_STRING_VIDEO    "RVS_Video"
#define RVS_STRING_GUIDELINE   "RVS_GuideLine"
//RVS_DriverCustom--gm
#define RVS_STRING_PARKASSTSYMBOLS   "RVS_ParkAsstSymbols"

//RVS_videoProperty
#define RVS_STRING_VIDEO_CONTRAST        "RVS_VIDEO_CONTRAST"
#define RVS_STRING_VIDEO_BRIGHTNESS     "RVS_VIDEO_BRIGHTNESS"

//RVS_driverMsg
#define RVS_STRING_MSG_FAILED_SYNC      "RVS_MSG_FAILED_SYNC"
#define RVS_STRING_MSG_FAILED_TRANSMISSION   "RVS_MSG_FAILED_TRANSMISSION"
#define RVS_STRING_MSG_GUIDELINES_FAIL    "RVS_MSG_GUIDELINES_FAIL"
#define RVS_STRING_MSG_CALIB_STEERING     "RVS_MSG_CALIB_STEERING"
#define RVS_STRING_MSG_PARK_ASST_FAIL     "RVS_MSG_PARK_ASST_FAIL"

//RVS_Failed_state_variable
//x100 tbd ---only for rvs internal use?saved in pps but no other usage
#define RVS_STRING_FAILED_STEERING  "RVS_Failed_Steering"
#define RVS_STRING_FAILED_UPA           "RVS_Failed_UPA"
#define RVS_STRING_FAILED_TRANSMISSION   "RVS_Failed_Transmission"
#define RVS_STRING_FAILED_SPEED     "RVS_Failed_Speed"
#define RVS_STRING_FAILED_SYNC       "RVS_Failed_Sync"

#define RVS_ON_HYSTERESIS_SCALE 32
#define RVS_VEHICLE_SPEED_COEFF 0.015625
#define RVS_REAR_EXTEND_DISTANCE_COEFF 0.01
#define RVS_HALF_PI_DEG 90
//cam scale
#define RVS_CAM_OFFSETX_SCALE -0.01
#define RVS_CAM_OFFSETY_SCALE 0.01
#define RVS_CAM_OFFSETZ_SCALE 0.01
#define RVS_CAM_ROT_SCALE (0.00573/*0.0001*/)
#define RVS_CAM_FU_SCALE  (10.0/640.0)
#define RVS_CAM_FV_SCALE  (10.0/480.0)
#define RVS_CAM_U0_SCALE  (20.0/64.0)
#define RVS_CAM_V0_SCALE  (20.0/48.0)
#define RVS_CAM_DISTORT_COEF_SCALE  0.0001
#define RVS_STEER_INVRATIO_SCALE 0.00001
#define RVS_CAM_ROT_DELTA_SCALE 0.1
#define RVS_CAM_DISPBORDERWIDTH_SCALE 2
//steer scale
#define RVS_TRACK_WIDTH_SCALE (0.02/*0.0127*/)
#define RVS_MARK_DELTADIS_SCALE (1/*0.0254*/)
#define RVS_REAR_AXLE_OFFSET_SCALE (0.01/*0.0127*/)
#define RVS_INV_RATIO_SCALE 0.00001
#define RVS_WHEELBASE_SCALE (0.001/*0.0127*/)
#define RVS_SATURATION_ANGLE_SCALE (4/*2*/)
//UPA
#define RVS_UPA_U_SCALE (10.0/16.0/*2*/)
#define RVS_UPA_V_SCALE (10.0/24.0/*1*/)
//RCTA
#define RVS_RCTA_U_SCALE (10.0/16.0/*2*/)
#define RVS_RCTA_V_SCALE (10.0/24.0/*1*/)

#define RVS_RCTALEFT_RES   "/usr/lib/RVS/res/RCTA_Left.bmp"
#define RVS_RCTARIGHT_RES  "/usr/lib/RVS/res/RCTA_Right.bmp"
#define RVS_UPA_RES        "/usr/lib/RVS/res/UPA.bmp"
#define RVS_FONTTEXINFO_RES  "/usr/lib/RVS/res/FontTexInfo_bin.txt"
#define RVS_FONTTEX_RES      "/usr/lib/RVS/res/FontTex_bin.txt"

typedef float color3[3];

#define RVS_ZORDER_VIDEO        400
#define RVS_ZORDER_OVERLAY      700 //test

#define RVS_SUCCESS  0x0
#define RVS_FAIL        0x1


typedef struct rvs_camera_params_t
{
	float rotx;   //rad
	float roty;
	float rotz;
	float offsetx;  //meters;
	float offsety;
	float offsetz;
	float fu;
	float fv;
	float distortCoef1;
	float distortCoef2;
	float cu;
	float cv;
}rvs_camera_params;

typedef struct rvs_steer_params_t
{
	float trackWidth;
	float deltaDistMarks;
	int numDistMarks;
	float rearAxleOffset;
	float invFrontRatio;
	float invRearRatio;
	float wheelBase;
	float saturationAngle;
	float swaDeltaAngle;
}rvs_steer_params;
#endif
