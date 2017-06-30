#include "CScaniaOnOffClient.hpp"
#include "CCanProcessor.hpp"
#include "CAdasMsgQueDefine.hpp"
#include "Env.hpp"
#include "CEOL.hpp"
#include "CCamera.hpp"
#define SCANIAONOFF_DBUS_NAME 	"com.harman.service.ScaniaOnOff"
#define SCANIAONOFF_OBJ_NAME 	"/com/harman/service/ScaniaOnOff"


CScaniaOnOffClient* CScaniaOnOffClient::s_pInstance = NULL;

CScaniaOnOffClient* CScaniaOnOffClient::getInstance()
{
	if ( s_pInstance == NULL )
	{
		s_pInstance = new CScaniaOnOffClient();
	}

	return s_pInstance;
}
/*
void CScaniaOnOffClient::delInstance()
{
	if ( s_pInstance == NULL )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}*/
TRC_SCOPE_DEF(ADAS, CScaniaOnOffClient, CScaniaOnOffClient);
CScaniaOnOffClient::CScaniaOnOffClient()
:m_eCurpowerMode(EOutOfStandby)
,m_bPowModeDefault(TRUE)
,m_bHardKeyWakeUpCycle(FALSE)
,m_uiCameraOneLastStatus(0)
,m_uiCameraTwoLastStatus(0)
{
    TRC_SCOPE(ADAS, CScaniaOnOffClient, CScaniaOnOffClient);
	registerTarget(SCANIAONOFF_DBUS_NAME,SCANIAONOFF_OBJ_NAME);
	registerAResponseCallback("OnOffSetSW12VOut", makeFunctor(this, &CScaniaOnOffClient::processPowerOnResponse));
	registerResponseCallback("getPowerModeInfo", makeFunctor(this, &CScaniaOnOffClient::procgetPowerModeInfoResp));
    registerSignalCallback("CameraStatusInfo", makeFunctor(this, &CScaniaOnOffClient::onCameraStatusInfo));
    registerSignalCallback("powerModeInfo", makeFunctor(this, &CScaniaOnOffClient::onpowerModeInfo));
    //registerAResponseCallback("onOffPmodePostEvent", makeFunctor(this, &CScaniaOnOffClient::processOnOffPmodePostEvent));

   m_ePINOnOffCam[0]=ePINOnOff_Off;
   m_ePINOnOffCam[1]=ePINOnOff_Off;

   m_eCamOnOffState[0]=eCamOnOff_Off;
   m_eCamOnOffState[1]=eCamOnOff_Off;

   m_eLogicPINOnOffCam[0]=ePINOnOff_Off;
   m_eLogicPINOnOffCam[1]=ePINOnOff_Off;   

    if(Env::isScaniaTarget())
    {
        m_eConfigStandbyCode = EStandbySCAINA; 
        m_eConfigWakeUpReqCode =  E_SCAINAWakeUp;
        m_eConfigPowerOffModeReqCode = E_SCAINAPowOffMode;
    }
    else if(Env::isMANTarget())
    {
        m_eConfigStandbyCode = EStandbyMAN;
        m_eConfigWakeUpReqCode =  E_MANWakeUp;
        m_eConfigPowerOffModeReqCode = E_NULLPowOffMode;
    }
    else
    {
        DBG_MSG(("CScaniaOnOffClient::CScaniaOnOffClient  init standby code error\n"));
    }
   //registerSignalCallback("CruiseControlVehSpeed", makeFunctor(this, &CCanClient::onCruiseControlVehSpeed));
	//registerSignalCallback("DirectionSwitchParams", makeFunctor(this, &CCanClient::onDirectionSwitchParams));
}

CScaniaOnOffClient::~CScaniaOnOffClient()
{
	s_pInstance = NULL;
}
TRC_SCOPE_DEF(ADAS, CScaniaOnOffClient, requestPowerOnCamera);
void CScaniaOnOffClient::requestPowerOnCamera(UInt32 uidx, UInt32 uiState,BOOLEAN bCamState)
{
    TRC_SCOPE(ADAS, CScaniaOnOffClient, requestPowerOnCamera);
	if( uidx != 0 && uidx != 1)
	{ 
		DBG_MSG(("CScaniaOnOffClient::requestPowerOnCamera error\n"));
		return;
	}

	string strParams;
	Json::Value jsonParams;
	Json::FastWriter writer;
	//string      strRet;
	//cam channel switched, but system side is not change power actually?
	static const UInt32 uiVOutId[2] = {4,5};
    //keep camera state in onoff client object, to restore power mode on standby event
    m_eCamOnOffState[uidx]=bCamState?(ECamOnOffValue)uiState:m_eCamOnOffState[uidx];

	jsonParams["sw12VOutId"] = uiVOutId[uidx];

	jsonParams["state"] = uiState;


	strParams = writer.write(jsonParams);
	ainvoke("OnOffSetSW12VOut", strParams);

	DBG_MSG(("ainvoke OnOffSetSW12VOut %s\n", strParams.c_str()));
}

TRC_SCOPE_DEF(ADAS, CScaniaOnOffClient, processPowerOnResponse);
void CScaniaOnOffClient::processPowerOnResponse(const string& strData)
{
    
	Json::Value jsonParams;
	Json::Reader reader;
	//DBG_MSG(("CScaniaOnOffClient::OnOffSetSW12VOut response %s\n ", strData.c_str()));

	if (!reader.parse(strData, jsonParams, false))
	{
        TRC_SCOPE(ADAS, CScaniaOnOffClient, processPowerOnResponse);
		jsonParams.clear();
		DBG_MSG(("CScaniaOnOffClient::processPowerOnResponse failed to format json value\n"));
		return;
	}

	UInt32 value = jsonParams["code"].asUInt() ;
	if( value == 1 )
	{
		SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffSetSW12VOutSucceed);
	}
	else if(value == 0 )
	{
		SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffSetSW12VOutFail);
	}
}

void CScaniaOnOffClient::getPowerModeInfo()
{
   
	string strParams ="";
   
    //DBG_MSG(("11111111111start invoke getPowerModeInfo \n"));

	invoke("getPowerModeInfo", strParams);
	//DBG_MSG(("2222222222 invoke getPowerModeInfo \n"));
}
static EPINOnOffValue m_LastPIN1OnOffCam = ePINOnOff_Off;
static EPINOnOffValue m_LastPIN2OnOffCam = ePINOnOff_Off;
TRC_SCOPE_DEF(ADAS, CScaniaOnOffClient, procgetPowerModeInfoResp);
void CScaniaOnOffClient::procgetPowerModeInfoResp(const string& strData)
{
    TRC_SCOPE(ADAS, CScaniaOnOffClient, procgetPowerModeInfoResp);
	Json::Value jsonParams;
	Json::Reader reader;
	//DBG_MSG(("CScaniaOnOffClient::procgetPowerModeInfoResp %s\n ", strData.c_str()));

	if (!reader.parse(strData, jsonParams, false))
	{
		jsonParams.clear();
		DBG_MSG(("CScaniaOnOffClient::procgetPowerModeInfoResp failed to format json value\n"));
		return;
	}
	UInt32 CameraOneStatus;
	UInt32 CameraTwoStatus;
		
	if(jsonParams.isMember("CameraOneStatus"))
	{
		CameraOneStatus = jsonParams["CameraOneStatus"].asUInt() ;
		m_uiCameraOneLastStatus = CameraOneStatus;
	}
	else
	{
		CameraOneStatus = m_uiCameraOneLastStatus;
	}
	
	if(jsonParams.isMember("CameraTwoStatus"))
	{
		CameraTwoStatus = jsonParams["CameraTwoStatus"].asUInt() ;
		m_uiCameraTwoLastStatus = CameraTwoStatus;
	}
	else
	{
		CameraTwoStatus = m_uiCameraTwoLastStatus;
	}	

    //update power mode-- usecase: after power on first standby is missing,use active camera in standby mode
    m_eCurpowerMode = (EStandby)jsonParams["powerMode"].asUInt() ;
    m_bPowModeDefault = FALSE;
    DBG_MSG(("CameraOneStatus = %d,CameraTwoStatus = %d m_eCurpowerMode= %d \n",CameraOneStatus,CameraTwoStatus,m_eCurpowerMode));
    fprintf(stderr,"CameraOneStatus = %d,CameraTwoStatus = %d m_eCurpowerMode= %d \n",CameraOneStatus,CameraTwoStatus,m_eCurpowerMode);

	if( CameraOneStatus == 1 )
	{
	   DBG_MSG(("hardpin turn on camera1\n"));
       
       if(Env::isScaniaTarget())
       {
            CCanProcessor::getInstance()->cancelRearGearState(FALSE);
       }
       m_ePINOnOffCam[0] = ePINOnOff_On;
		//SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera1On);
	}
   else if( CameraOneStatus == 0 )
   {
	   DBG_MSG(("hardpin turn off camera1\n"));
      m_ePINOnOffCam[0] = ePINOnOff_Off;
		//SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera1Off);
   }
	if( CameraTwoStatus == 1 )
	{
	   DBG_MSG(("hardpin turn on camera2\n"));
       
       if(Env::isScaniaTarget())
       {
            CCanProcessor::getInstance()->cancelRearGearState(FALSE);
       }
       m_ePINOnOffCam[1] = ePINOnOff_On;
		//SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera2On);
	}
   else if( CameraTwoStatus == 0 )
   {
	   DBG_MSG(("hardpin turn off camera2\n"));
      m_ePINOnOffCam[1] = ePINOnOff_Off;
		//SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera2Off);
   }
   if( m_LastPIN1OnOffCam != m_ePINOnOffCam[0])
   {
      m_eLogicPINOnOffCam[0]= m_ePINOnOffCam[0];
   }
   if( m_LastPIN2OnOffCam != m_ePINOnOffCam[1])
   {
      m_eLogicPINOnOffCam[1]= m_ePINOnOffCam[1];
   }
   m_LastPIN1OnOffCam = m_ePINOnOffCam[0];
   m_LastPIN2OnOffCam = m_ePINOnOffCam[1];

    if(isInStandbyState())
    {
        if(m_eCamOnOffState[0] == eCamOnOff_On)
        {
            requestPowerOnCamera(0,0,FALSE);
            DBG_MSG(("CScaniaOnOffClient::standby - camera1 power off\n "));
        }
        if(m_eCamOnOffState[1] == eCamOnOff_On)
        {
            requestPowerOnCamera(1,0,FALSE);
            DBG_MSG(("CScaniaOnOffClient::standby - camera2 power off\n "));
        }
        //CANCLE ALL ACITVE CAMERA STATE
        vSetLogicPinOff();
		CCanProcessor::getInstance()->vDisableLogicState();
        CCanProcessor::getInstance()->cancelRearGearState(TRUE);
        CCanProcessor::getInstance()->vDisableRearGearLogicState();  
    }
   
   SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera);

}

TRC_SCOPE_DEF(ADAS, CScaniaOnOffClient, onCameraStatusInfo);
void CScaniaOnOffClient::onCameraStatusInfo(const string& strData)
{
    TRC_SCOPE(ADAS, CScaniaOnOffClient, onCameraStatusInfo);
	Json::Value jsonParams;
	Json::Reader reader;
	DBG_MSG(("CScaniaOnOffClient::onCameraStatusInfo--> %s\n ", strData.c_str()));
   //string  strData1 = "onCameraStatusInfo";
#if 1
	if (!reader.parse(strData, jsonParams, false))
	{
		jsonParams.clear();
		DBG_MSG(("CScaniaOnOffClient::onCameraStatusInfo: failed to format json value\n"));
		return;
	}
#endif
	UInt32 CameraOneStatus;
	UInt32 CameraTwoStatus;
		
	if(jsonParams.isMember("CameraOneStatus"))
	{
		CameraOneStatus = jsonParams["CameraOneStatus"].asUInt() ;
		m_uiCameraOneLastStatus = CameraOneStatus;
	}
	else
	{
		CameraOneStatus = m_uiCameraOneLastStatus;
	}
	
	if(jsonParams.isMember("CameraTwoStatus"))
	{
		CameraTwoStatus = jsonParams["CameraTwoStatus"].asUInt() ;
		m_uiCameraTwoLastStatus = CameraTwoStatus;
	}
	else
	{
		CameraTwoStatus = m_uiCameraTwoLastStatus;
	}

    //DBG_MSG(("CScaniaOnOffClient::onCameraStatusInfo--> %s\n ", strData.c_str()));
	if( CameraOneStatus == 1 )
	{
	   DBG_MSG(("hardpin turn on camera1\n"));
      
      //if(Env::isScaniaTarget())
      // {
        //specail process on active same camaera is needed
        //    CCanProcessor::getInstance()->cancelRearGearState(FALSE);
     //  }
      m_ePINOnOffCam[0] = ePINOnOff_On;
		//SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera1On);
	}
   else if( CameraOneStatus == 0 )
   {
	   DBG_MSG(("hardpin turn off camera1\n"));
      m_ePINOnOffCam[0] = ePINOnOff_Off;
		//SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera1Off);
   }
	if( CameraTwoStatus == 1 )
	{
	   DBG_MSG(("hardpin turn on camera2\n"));
      
     // if(Env::isScaniaTarget())
     //  {
        //    CCanProcessor::getInstance()->cancelRearGearState(FALSE);
     //  }
      m_ePINOnOffCam[1] = ePINOnOff_On;
		//SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera2On);
	}
    else if( CameraTwoStatus == 0 )
    {
	   DBG_MSG(("hardpin turn off camera2\n"));
      m_ePINOnOffCam[1] = ePINOnOff_Off;
		//SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera2Off);
    }
    if( m_LastPIN1OnOffCam != m_ePINOnOffCam[0])
    {
      m_eLogicPINOnOffCam[0]= m_ePINOnOffCam[0];
    }
    if( m_LastPIN2OnOffCam != m_ePINOnOffCam[1])
    {
      m_eLogicPINOnOffCam[1]= m_ePINOnOffCam[1];
    }
    m_LastPIN1OnOffCam = m_ePINOnOffCam[0];
    m_LastPIN2OnOffCam = m_ePINOnOffCam[1];
    
    SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera);
}

TRC_SCOPE_DEF(ADAS, CScaniaOnOffClient, onpowerModeInfo);
void CScaniaOnOffClient::onpowerModeInfo(const string& strData)
{
    TRC_SCOPE(ADAS, CScaniaOnOffClient, onpowerModeInfo);
	Json::Value jsonParams;
	Json::Reader reader;
   //string  strData1 = "onCameraStatusInfo";

    BOOLEAN bLastIsStandbyState = isInStandbyState(); 
#if 1
	if (!reader.parse(strData, jsonParams, false))
	{
		jsonParams.clear();
		DBG_MSG(("CScaniaOnOffClient::onpowerModeInfo: failed to format json value\n"));
		return;
	}
#endif
	m_eCurpowerMode = (EStandby)jsonParams["powerMode"].asUInt() ;
    DBG_MSG(("CScaniaOnOffClient::onpowerModeInfo--> %s @ %d\n ", strData.c_str(),m_eCurpowerMode));

    if(isInStandbyState())
    {
        m_bHardKeyWakeUpCycle =  FALSE;
        if(m_eCamOnOffState[0] == eCamOnOff_On)
        {
            requestPowerOnCamera(0,0,FALSE);
            DBG_MSG(("CScaniaOnOffClient::standby - camera1 power off\n "));
        }
        if(m_eCamOnOffState[1] == eCamOnOff_On)
        {
            requestPowerOnCamera(1,0,FALSE);
            DBG_MSG(("CScaniaOnOffClient::standby - camera2 power off\n "));
        }
        //CANCLE ALL ACITVE CAMERA STATE
        vSetLogicPinOff();
        //only rear camera is overridable, cancel manually request on this
        CCanProcessor::getInstance()->vDisableLogicState();
        CCanProcessor::getInstance()->cancelRearGearState(TRUE);
        CCanProcessor::getInstance()->vDisableRearGearLogicState();
        //should remve hard key acitve state too ---to send a repsonse to HMI side
        SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera);
    }
    else
    {
        if(m_eCamOnOffState[0] == eCamOnOff_On)
        {
            requestPowerOnCamera(0,1,FALSE);
            DBG_MSG(("CScaniaOnOffClient::outof standby - camera1 power on\n "));
        }
        if(m_eCamOnOffState[1] == eCamOnOff_On)
        {
            requestPowerOnCamera(1,1,FALSE);
            DBG_MSG(("CScaniaOnOffClient::outof standby - camera2 power on\n "));
        }
        if(m_bPowModeDefault)
        {
            printf("received power info signal before request it\n");
        }
        else if((bLastIsStandbyState)
            //if cam is activated by camera key , then dont override it....
            &&(!m_bHardKeyWakeUpCycle)
            //only set for SCAINA
            &&(Env::isScaniaTarget()))
        {
            //if rear gear is on, even it is overrided , it should be turned on - ticket 1777188
            
            #if 0
            for(int i=0;i<CCamera::eCameraNum;i++)
            {
                //if one camera is manually activated -- press CAMERA key instead of press power key
                //show manually request cam
                if ((CCameraCtrl::getCameraStatus((CCamera::EPos)i)== CCamera::eStatus_ManualActivated))
                 //   &&(EOL::getCameraType((CCamera::EPos)i)==CCamera::eType_Reverse))
                return ;
            }
            #endif
            BOOLEAN bWakeUp = FALSE;
			//general camera and direction indicator is override by standby request
            if(CCanProcessor::getInstance()->isReverseEngaged())
            {
                CCanProcessor::getInstance()->vSetRearGearLogicState();
                bWakeUp = TRUE;
            }
			
            if((((EOL::isGelActivateWorkLightOn(CCamera::eCamera1))&&(EOL::getCameraType(CCamera::eCamera1)==CCamera::eType_General))
			||((EOL::isGelActivateWorkLightOn(CCamera::eCamera2))&&(EOL::getCameraType(CCamera::eCamera2)==CCamera::eType_General)))
			&& CCanProcessor::getInstance()->IsOutOfStandbyWorkLight())
            {
                bWakeUp = TRUE;
            }
			
            if(((EOL::isGelActivateDirIndicatorOn(CCamera::eCamera1)&&(EOL::getCameraType(CCamera::eCamera1)==CCamera::eType_General))
			||(EOL::isGelActivateDirIndicatorOn(CCamera::eCamera2)&&(EOL::getCameraType(CCamera::eCamera2)==CCamera::eType_General)))
			&& (CCanProcessor::getInstance()->isOutOfStandbyTurnRight()||CCanProcessor::getInstance()->isOutOfStandbyTurnLeft()))
            {
                bWakeUp = TRUE;
            }			
			
#if 1
            if(CCanProcessor::getInstance()->isCANOnOffRearCam())
            {
                CCanProcessor::getInstance()->vSetRearOnoffLogicState();
                bWakeUp = TRUE;
            }                
            if(CCanProcessor::getInstance()->isCANOnOffFrntCam())
            {
                CCanProcessor::getInstance()->vSetFrontOnoffLogicState();
                bWakeUp = TRUE;
            }
            if(CCanProcessor::getInstance()->isCANOnOffGenCam1())
            {
                CCanProcessor::getInstance()->vSetGen1OnoffLogicState();
                bWakeUp = TRUE;
            }   
            if(CCanProcessor::getInstance()->isCANOnOffGenCam2())
            {
                CCanProcessor::getInstance()->vSetGen2OnoffLogicState();
                bWakeUp = TRUE;
            }     
#endif            
            //to trigger state auto update
            if(bWakeUp) SEND_BASEMESSAGE(eMsgType_ScaniaOnOff,eOnOffHardPinCamera);
        }
    }
    
}

TRC_SCOPE_DEF(ADAS, CScaniaOnOffClient, isInStandbyState);
BOOLEAN CScaniaOnOffClient::isInStandbyState()
{
    TRC_SCOPE(ADAS, CScaniaOnOffClient, isInStandbyState);
	if((m_eConfigStandbyCode== m_eCurpowerMode)||(EStandbyComm== m_eCurpowerMode))
    {
       return TRUE;
    }   
    else
    {
       return FALSE;
    }
}

TRC_SCOPE_DEF(ADAS, CScaniaOnOffClient, onOffPmodePostEvent);
void CScaniaOnOffClient::onOffPmodePostEvent(UInt32 uidx,BOOLEAN bHKWakeup)
{
    TRC_SCOPE(ADAS, CScaniaOnOffClient, onOffPmodePostEvent);
	string strParams;
	Json::Value jsonParams;
	Json::FastWriter writer;
    
	if(( uidx == 0 )||(uidx == 1))
	{
        jsonParams["event"] = bHKWakeup?E_HKWakeUp:m_eConfigWakeUpReqCode;
		DBG_MSG(("CScaniaOnOffClient::onOffPmodePostEvent  pos - %d\n",uidx));
	}
    //define index 4 as a power mode off request 
    else if(( uidx == 4 )&&(E_NULLPowOffMode != m_eConfigPowerOffModeReqCode))
    {
        jsonParams["event"] = m_eConfigPowerOffModeReqCode;
    }
    else
    {
		DBG_MSG(("CScaniaOnOffClient::onOffPmodePostEvent wrong pos - %d\n",uidx));
        return;
    }   
    
    m_bHardKeyWakeUpCycle=bHKWakeup;
	strParams = writer.write(jsonParams);
	ainvoke("onOffPmodePostEvent", strParams);

	DBG_MSG(("ainvoke onOffPmodePostEvent %s\n", strParams.c_str()));
}

