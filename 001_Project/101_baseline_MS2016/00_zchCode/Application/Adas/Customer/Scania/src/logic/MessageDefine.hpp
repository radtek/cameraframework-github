#ifndef _MESSAGE_DEFINE_H
#define _MESSAGE_DEFINE_H

#include "svs.h"
#include "CAdasMsgQueDefine.hpp"
enum ECanEventSCANIA
{
	eCruiseControlVehSpeed,
	eDirectionSwitchParams,
	eCANRequestOnOffCamera
};


enum ESwitchValue
{
	eSV_Off 			= 0,
	eSV_On				= 1,
	eSV_NotAvailable	= 2,
	eSV_Error			= 3,
};

enum EParkBrakeSwitch
{
	ePBS_NotSet 			= 0,
	ePBS_Set				= 1,
	ePBS_Error				= 2,
	ePBS_NotAvailable		= 3,
};
struct tagSwitchParams : public tagBaseMessage
{
	tagSwitchParams()
	: tagBaseMessage(eMsgType_CAN, eDirectionSwitchParams)
	{
		;
	}

	ESwitchValue eWorkLigthToggleSwitch;
	ESwitchValue eLeftIndicatorIntended;
	ESwitchValue eRightIndicatorIntended;
	ESwitchValue eReverseSwitch;
};
struct tagCruiseControlVehSpeed : public tagBaseMessage
{
	tagCruiseControlVehSpeed()
	: tagBaseMessage(eMsgType_CAN, eCruiseControlVehSpeed)
	{

	}

	UInt32 				uiWheelBasedVehSpeed;
	EParkBrakeSwitch	eParkBrakeSwitch	;
};

enum EPINOnOffValue
{
	ePINOnOff_Off 			   = 0,
	ePINOnOff_On				= 1,
	//ePBS_Error				= 2,
	//ePBS_NotAvailable		= 3,
};

enum ECamOnOffValue
{
	eCamOnOff_Off 			   = 0,
	eCamOnOff_On				= 1,
	//ePBS_Error				= 2,
	//ePBS_NotAvailable		= 3,
};
//--------------------------------------HMI----------------------------
struct tagPositionAndSize : public tagBaseMessage
{
	tagPositionAndSize()
	: tagBaseMessage(eMsgType_HMI, eSetPositionAndSize)
	{
	
	}

	CRectangle	_rc;
};

//-------------------------------------others---------------------------------
enum ECamSigState
{
	eCameraInitValid 			= 0,
	eCameraInitInvalid			= 1,
	eCameraValid				= 2,
	eCameraInvalid				= 3,
};

struct tagCamSigState : public tagBaseMessage
{
	tagCamSigState()
	: tagBaseMessage(eMsgType_Others, eOtherEvent_CameraSignalEvent)
	{

	}

	ECamSigState 	eCamState;
	UInt32			uiCamChan;
};


#endif
