#include "CSCANIAMessageHandler.h"
#include "CCanProcessor.hpp"
#include "CAdasCtrl.hpp"
#include "CDiagnosticProcessor.hpp"


void CSCANIAMessageHandler::_handle(UInt32 uiType, UInt32 uiID, void* pData)
{
	switch( uiType )
	{
	case eMsgType_CAN:
		CCanProcessor::getInstance()->dispatchEvent(uiID, pData);
		break;
	case eMsgType_HMI:
	case eMsgType_Others:
	case eMsgType_ScaniaOnOff:
    case eMsgType_Timer:
    case eMsgType_DriverCamera:
    case eMsgType_DriverGraphic:
    case eMsgType_ActiveKPICamera:
    case eMsgType_HMIShowRequestFailed:
    case eMsgType_HMIToggleRequestFailed:
        if(eGetCameraState == uiID)
        {
            if(eMsgType_HMI == uiType)                  pData  = (void*)"call getCameraState by HMI";
            //if(eMsgType_Timer == uiType)                pData  = (void*)"call getCameraState by Timer";
            if(eMsgType_DriverCamera == uiType)      	pData  = (void*)"call getCameraState by DriverCamera";
            if(eMsgType_DriverGraphic == uiType)        pData  = (void*)"call getCameraState by DriverGraphic";
            if(eMsgType_ActiveKPICamera == uiType)      pData  = (void*)"call getCameraState by ActiveKPICamera";
            if(eMsgType_HMIShowRequestFailed == uiType)         pData  = (void*)"call getCameraState by HMIShowRequestFailed";
            if(eMsgType_HMIToggleRequestFailed == uiType)       pData  = (void*)"call getCameraState by HMIToggleRequestFailed";
        }
		CAdasCtrl::getInstance()->dispatchEvent(uiID, pData);
		break;
	case eMsgType_Diagnostic:
		CDiagnosticProcessor::getInstance()->dispatchEvent(uiID, pData);
		break;
	}
}
