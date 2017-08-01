
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERAEVENTDEFINE_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERAEVENTDEFINE_H__

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define HYSTERESISTIME_REVGEAR 500

//name of four camera
#define FRONTCAMERANAME    "FrontCamera"
#define RESERVECAMERANAME  "ReserveCamera"
#define LEFTCAMERANAME     "LeftCamera"
#define RIGHTCAMERANAME    "RightCamera"

//name of camera state
#define DEFAULTCAMERASTATE  "DefaultState"
#define OFFCAMERASTATE      "OffState"
#define ENABLECAMERASTATE   "EnableState"
#define SUSPENDCAMERASTATE  "SuspendState"

/******** cameraCreatFlag :  which model need which cameras *****
 * BIT  : 1:need  /  0:no need  /  X:reserve
 * BYTE : X      X      X      X      1/0    1/0   1/0  1/0
 *                                  (front reserve left right)
 * eg :  rvc: 0000 0100
 *       svc: 0000 0001
 *       avm: 0000 1111
*****************************************************************/
static const BYTE s_SVC_Map_Cameras = 0x01;  //  0000 0001
static const BYTE s_RVC_Map_Cameras = 0x04;  //  0000 0100
static const BYTE s_AVM_Map_Cameras = 0x0F;  //  0000 1111
static const BYTE s_PAS_Map_Cameras = 0x04;  //  0000 0100
static const BYTE s_APA_Map_Cameras = 0x04;  //  0000 0100
static const BYTE s_COMMON_Map_Cameras = 0x00;
static const BYTE s_UNKNOWN_Map_Cameras = 0x00;

/*
 * vehicle camera state
 */
typedef enum _vehicle_Camera_State{
    eSVS_Camera_State_OFF      = 0x0,
    eSVS_Camera_State_Suspend  = 0x1,
    eSVS_Camera_State_Enable   = 0x2,


    eSVS_Camera_State_Invalid  = 0xFF
} Enum_VehicleCameraState;

/*
 * State Trigger Event (message type used by CameraStateMachine)
 */
typedef enum _event
{

    eCameraStateTriggerEvent_Init_Complete,   // do not be used until now

    /*original Trigger*******************************************/
    eCameraStateTriggerEvent_OpenCamera,    // OpenCamera
    eCameraStateTriggerEvent_CloseCamera,   // CloseCamera

    eCameraStateTriggerEvent_StartCapture,
    eCameraStateTriggerEvent_StopCapture,
    /*original Trigger*******************************************/

    /*manual Trigger*********************************************/
    //depend on original Trigger, purpose : suport 500ms shake (depend on Timmer)
    eCameraStateTriggerEvent_StartCapture_REAL,
    eCameraStateTriggerEvent_StopCapture_REAL,
    /*manual Trigger*********************************************/

    eCameraStateTriggerEvent_INVALID
} Enum_CameraStateTriggerEvent_Internal;

inline string TiggerStr(UInt32 trigger)
{
    switch(trigger) {
        case eCameraStateTriggerEvent_Init_Complete :
            return "eCameraStateTriggerEvent_Init_Complete";

        case eCameraStateTriggerEvent_OpenCamera :
            return "eCameraStateTriggerEvent_OpenCamera";

        case eCameraStateTriggerEvent_CloseCamera :
            return "eCameraStateTriggerEvent_CloseCamera";

        case eCameraStateTriggerEvent_StartCapture :
            return "eCameraStateTriggerEvent_StartCapture";

        case eCameraStateTriggerEvent_StopCapture :
            return "eCameraStateTriggerEvent_StopCapture";

        case eCameraStateTriggerEvent_StartCapture_REAL :
            return "eCameraStateTriggerEvent_StartCapture_REAL";

        case eCameraStateTriggerEvent_StopCapture_REAL :
            return "eCameraStateTriggerEvent_StopCapture_REAL";

        case eCameraStateTriggerEvent_INVALID :
            return "eCameraStateTriggerEvent_INVALID";

        default:
            return "eCameraStateTriggerEvent_INVALID";
    }
}

/*
 * the way to talk with camera driver
 */
typedef enum _way
{
    eTalkWithCameraDriver_V4L2,
    eTalkWithCameraDriver_OTHERS
} Enum_TheWayToTalkWithCameraDriver;

/*
 * the param to talk with camera driver
 */
typedef struct _param
{
    Int32 with = 1280;
    Int32 hight = 760;
} CameraDriverParams;

/*
 * ERROR CODE
 */
static const ECode NO_ERROR = 0;

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERAEVENTDEFINE_H__