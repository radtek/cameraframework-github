#ifndef RVC_MSGQ_DEFINE_H_
#define RVC_MSGQ_DEFINE_H_

#define  ADAS_MODULE_RVC    string("RVC")

enum eRVCEvent
{
    eCameraActivate_ON,
    eCameraActivate_OFF,
    eShowGuideLine_ON,
    eShowGuideLine_OFF,
    eManualActivateReverseCamera_ON,
    eManualActivateReverseCamera_OFF,
    eActiveSettingMode_ON,
    eActiveSettingMode_OFF,
    eSetPositionAndSize,

    eGetCameraState,
    eGetCameraConfig,

    eOtherEvent_ReverseCam1TimerDeactivate,
    eOtherEvent_ReverseCam2TimerDeactivate
};

enum eDiagnosticRVCEvent
{
    eDiag_Start,
    eDiag_Stop,
    eDiag_ResetCamera,
};



#endif