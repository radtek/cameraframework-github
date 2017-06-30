#include "CSimpleCaptureMessageHandler.h"
#include "CSimpleCaptureThread.h"
#include "SimpleMessageDefine.h"
#include "videoCapture/CQNXCaptureDriver.hpp"
#include "CSimpleCaptureThread.h"

TRC_SCOPE_DEF(ADAS, CSimpleCaptureMessageHandler, _handle);
void CSimpleCaptureMessageHandler::_handle(UInt32 uiType, UInt32 uiID, void* pData)
{
	TRC_SCOPE(ADAS, CSimpleCaptureMessageHandler, _handle);
	if( uiType == eCaptureMsgType_Capture )
	{
		switch( uiID )
		{
		case eCaptureMsgID_CameraSource:
			{
				tagCameraSource* tagSrc = (tagCameraSource*)pData;
				if( tagSrc )
				{
					CQNXCaptureDriver* pCaptureDriver = (CQNXCaptureDriver*)tagSrc->_pCaptureDriver;
                    ((CSimpleCaptureThread*)(tagSrc->_pSimpleCaptureThread))->FlushDummyData();
					pCaptureDriver->setSourceIndex(tagSrc->_iCameraSrcIndex);
                    ((CSimpleCaptureThread*)(tagSrc->_pSimpleCaptureThread))->setReportLayerReady();
				}
                DBG_MSG(("CSimpleCaptureMessageHandler::_handled eCaptureMsgID_CameraSource\n"));
			}
			break;
		case eCaptureMsgID_PosSize:
			{
				tagCapturePosAndSize* pPosSize = (tagCapturePosAndSize*)pData;
				CSimpleCaptureThread* pThread = (CSimpleCaptureThread*)pPosSize->_pSimpleCaptureThread;
				pThread->_setScreenPosAndSize(pData);

				DBG_MSG(("CSimpleCaptureMessageHandler::_handled eCaptureMsgID_PosSize\n"));
			}
			break;
		case eCaptureMsgID_CameraState:
			{
				tagCameraState* tagEnable = (tagCameraState*)pData;
				if( tagEnable)
				{
					CQNXCaptureDriver* pCaptureDriver = (CQNXCaptureDriver*)tagEnable->_pCaptureDriver;
					if(tagEnable->_bCameraState)
					{
                        if(!pCaptureDriver->bIfCapEnabled())
                        {
    					    ((CSimpleCaptureThread*)(tagEnable->_pSimpleCaptureThread))->FlushDummyData();
    						pCaptureDriver->bCapEnable();
                            DBG_MSG(("CSimpleCaptureMessageHandler::_handle CaptureDriverEnable ver1\n"));
                            ((CSimpleCaptureThread*)(tagEnable->_pSimpleCaptureThread))->setReportLayerReady();
                        }
                        else
                        {
                            DBG_MSG(("CSimpleCaptureMessageHandler::_handle CaptureDriverEnable - channel already enabled no change\n"));
                        }

					}
					else
					{
						pCaptureDriver->bCapDisable();
                        DBG_MSG(("CSimpleCaptureMessageHandler::_handle CaptureDriverDisable%d\n"));

					}
				}
				DBG_MSG(("CSimpleCaptureMessageHandler::_handled eCaptureMsgID_CameraState\n"));
			}
			break;
		case eCaptureMsgID_AsyncPause:
			{
				tagAsyncPause* AsyncPause = (tagAsyncPause*)pData;
				if(AsyncPause)
				{
					CSimpleCaptureThread* pCapThread = (CSimpleCaptureThread*)AsyncPause->_pCapThread;
                    CFunctorArg0*	pAsyncPauseCALLBACK = AsyncPause->_pAsyncPauseCALLBACK;
					pCapThread->pause();
                    if(pAsyncPauseCALLBACK) (*pAsyncPauseCALLBACK)();
                    DBG_MSG(("CSimpleCaptureMessageHandler::_handled eCaptureMsgID_AsyncPause\n"));
				}
			}
			break;	
			
	   case eCaptureMsgID_NeedReportIfLayerReady:
			{
				tagReportLayerReady* ReportLayerReady = (tagReportLayerReady*)pData;
				if(ReportLayerReady)
				{
					CSimpleCaptureThread* pCapThread = (CSimpleCaptureThread*)ReportLayerReady->_pCapThread;
                    pCapThread->setReportLayerReady();
                    DBG_MSG(("CSimpleCaptureMessageHandler::_handled eCaptureMsgID_NeedReportIfLayerReady\n"));
				}	
			}
			break;	            
        }
	}
}
