
#ifndef _CADAS_MSGQUEDEFINE_H_
#define _CADAS_MSGQUEDEFINE_H_

#include "svs.h"

enum EMsgType
{
	eMsgType_CAN,
	eMsgType_HMI,
	eMsgType_ScaniaOnOff,
	eMsgType_Diagnostic,
	eMsgType_Others,
	eMsgType_Timer,
	eMsgType_DriverGraphic,
	eMsgType_DriverCamera,
	eMsgType_ActiveKPICamera,
	eMsgType_HMIShowRequestFailed,
	eMsgType_HMIToggleRequestFailed,
};

enum EAdasServiceEvent
{
	eToggleSwitchCamera,//camera hard key from HMI
	eCamera1Activate_ON,
	eCamera1Activate_OFF,
	eCamera2Activate_ON,
	eCamera2Activate_OFF,
	eShowGuideLine_ON,
	eShowGuideLine_OFF,
	eManualActivateReverseCamera_ON,
	eManualActivateReverseCamera_OFF,
	eManualActivateGeneralCamera_ON,
	eManualActivateGeneralCamera_OFF,
	eActiveSettingMode_ON,
	eActiveSettingMode_OFF,

	eSetPositionAndSize,

	eGetCameraState,
	//eGetCameraStateDiag,
	eGetCameraStateHMI,
	eGetCameraConfig,

	eOnOffSetSW12VOutSucceed,
	eOnOffSetSW12VOutFail,

	eOnOffHardPinCamera,

	eOtherEvent_CameraSignalEvent,
	eOtherEvent_ReverseCam1TimerDeactivate,
	eOtherEvent_ReverseCam2TimerDeactivate,
};


enum EDiagnosticEvent
{
	eDiag_Start,
	eDiag_Stop,
	eDiag_ResetCamera1,
	eDiag_ResetCamera2,
};





#endif /* _CADAS_DATATYPE_H_ */

