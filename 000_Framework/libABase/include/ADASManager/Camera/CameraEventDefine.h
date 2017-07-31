
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
    eSVS_Camera_State_Enable   = 0x1,


    eSVS_Camera_State_Invalid  = 0xFF
} Enum_VehicleCameraState;

/*
 * State Trigger Event (message type used by CameraStateMachine)
 */
typedef enum _event
{

    eCameraStateTriggerEvent_Init_Complete,   // do not be used until now

    //original Trigger
    eCameraStateTriggerEvent_OpenCamera,                 // OpenCamera()
    eCameraStateTriggerEvent_CloseCamera_DriverFalse,    // CloseCamera(FALSE)
    eCameraStateTriggerEvent_CloseCamera_DriverTrue,     // CloseCamera(TRUE)

    //manual Trigger depend on original Trigger, purpose : suport 500ms shake (depend on Timmer)
    eCameraStateTriggerEvent_OpenCamera_REAL,
    eCameraStateTriggerEvent_CloseCamera_REAL_DriverFalse,
    eCameraStateTriggerEvent_CloseCamera_REAL_DriverTrue,

    eCameraStateTriggerEvent_INVALID
} Enum_CameraStateTriggerEvent_Internal;

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

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERAEVENTDEFINE_H__