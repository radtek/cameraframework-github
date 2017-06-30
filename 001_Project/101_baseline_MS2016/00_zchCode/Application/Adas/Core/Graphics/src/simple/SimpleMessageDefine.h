#ifndef _SIMPLE_MESSAGEDEFINE_H
#define _SIMPLE_MESSAGEDEFINE_H

#include "foundation.h"


//-------------------------capture-----------------------------------------
enum ECaptureMsgType
{
	eCaptureMsgType_Capture,
};

enum ECaptureMsgID
{
	eCaptureMsgID_CameraSource,
	eCaptureMsgID_PosSize,
	eCaptureMsgID_CameraState,
	eCaptureMsgID_AsyncPause,
	eCaptureMsgID_NeedReportIfLayerReady
};

struct tagCameraSource : public tagBaseMessage
{
	tagCameraSource()
	: tagBaseMessage(eCaptureMsgType_Capture, eCaptureMsgID_CameraSource)
	{
		_iCameraSrcIndex = 0;
	}

	Int32	_iCameraSrcIndex;
	void*	_pCaptureDriver;
    void*	_pSimpleCaptureThread;
};

struct tagCapturePosAndSize : public tagBaseMessage
{
	tagCapturePosAndSize()
	: tagBaseMessage(eCaptureMsgType_Capture, eCaptureMsgID_PosSize)
	{
		;
	}

	CRectangle	_rc;
	void*		_pSimpleCaptureThread;
};
//this msg is mean to close capture driver hw interruption
struct tagCameraState : public tagBaseMessage
{
	tagCameraState()
	: tagBaseMessage(eCaptureMsgType_Capture, eCaptureMsgID_CameraState)
	{
		;
	}

	BOOLEAN	_bCameraState;
	void*	_pCaptureDriver;
    void*	_pSimpleCaptureThread;
};
//this msg is mean to pause thread in async way in case to let last message send within one call to be finished
struct tagAsyncPause : public tagBaseMessage
{
	tagAsyncPause()
	: tagBaseMessage(eCaptureMsgType_Capture, eCaptureMsgID_AsyncPause)
	{
		;
	}
	void*	_pCapThread;
    CFunctorArg0*	_pAsyncPauseCALLBACK;
};
//this msg is mean to send a requst to driver to notify app that layer is ready
struct tagReportLayerReady : public tagBaseMessage
{
	tagReportLayerReady()
	: tagBaseMessage(eCaptureMsgType_Capture, eCaptureMsgID_NeedReportIfLayerReady)
	{
		;
	}
	void*	_pCapThread;
};
//-------------------------graphics-----------------------------------------


#endif
