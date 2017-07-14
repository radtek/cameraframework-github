
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
 * vehicle gears event
 */
// typedef enum _vehicle_Gears{
//     /* original vehicle Gears */
//     eSVS_TGSLever_MANUAL      = 0x4,
//     eSVS_TGSLever_DRIVE       = 0x5,
//     eSVS_TGSLever_NEUTRAL     = 0x6,
//     eSVS_TGSLever_REVERSE     = 0x7,
//     eSVS_TGSLever_PARKED      = 0x8,
//     eSVS_TGSLever_INVALID     = 0xF,

//     /* man-made vehicle Gears */
//     eSVS_TGSLever_ENTER_REVERSE = 0x9,
//     eSVS_TGSLever_EXIT_REVERSE  = 0xA
// } Enum_VehicleGear;
typedef enum _event
{
    eCameraStateTriggerEvent_Init_Complete,


    eCameraStateTriggerEvent_OpenCamera,
    eCameraStateTriggerEvent_CloseCamera,


    //suport 500ms shake
    eCameraStateTriggerEvent_OpenCamera_REAL,
    eCameraStateTriggerEvent_CloseCamera_REAL,


    eCameraStateTriggerEvent_INVALID
} Enum_CameraStateTriggerEvent_Internal;


typedef enum _way
{
    eTalkWithCameraDriver_V4L2,
    eTalkWithCameraDriver_OTHERS
}Enum_TheWayToTalkWithCameraDriver;

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERAEVENTDEFINE_H__