
#include "CAdasService.hpp"
#include "MessageDefine.hpp"
#include "CAdasCtrl.hpp"
#include "CCanClient.hpp"
#include "Env.hpp"
#include "CCameraMANTruck.hpp"
#include "CCameraDetection.hpp"

#define  DBUS_NAME_ADAS     "com.harman.service.adas"
#define	 DBUS_OBJPATH_ADAS	"/com/harman/service/adas"

CAdasService * CAdasService::s_pInstance = NULL;

struct tagSetAttributeCmd
{
   const char*             			sCMDName;
   const char*             			sCMDContent;
   EAdasServiceEvent      	 		eInternalCmdId;
   CAdasService::CCommandFunctor*	pFunctor;
};

CAdasService::CAdasService()
: CBaseDBUSParser(FALSE)
{   
	registerTarget(DBUS_NAME_ADAS,DBUS_OBJPATH_ADAS);
	//registerTarget(CAN_DBUS_NAME,CAN_OBJ_NAME);

   registerRequestCallback("SetAttribute", makeFunctor(this, &CAdasService::setAttribute));
   registerRequestCallback("GetAttribute", makeFunctor(this, &CAdasService::getCameraState));
   registerRequestCallback("SetPositionAndSize", makeFunctor(this, &CAdasService::setPositionAndSize));
   //registerRequestCallback("VehicleParams", makeFunctor(this, &CAdasService::vehicleParams));
   registerRequestCallback("GetCameraState", makeFunctor(this, &CAdasService::getCameraState));
   registerRequestCallback("GetCameraConfig", makeFunctor(this, &CAdasService::getCameraConfig));
}

CAdasService::~CAdasService()
{
	s_pInstance = NULL;
}

CAdasService* CAdasService::getInstance()
{
   if(s_pInstance == NULL)
   {
	   s_pInstance = new CAdasService();
   }
   return s_pInstance;
}
/*
void CAdasService::delInstance()
{
   if(s_pInstance != NULL)
   {
      delete s_pInstance;
      s_pInstance = NULL;
   }
}*/

TRC_SCOPE_DEF(ADAS, CAdasService, setAttribute);
void CAdasService::setAttribute(SVCIPC_tReqContext context, const string&   parms)
{
	TRC_SCOPE(ADAS, CAdasService, setAttribute);
   Json::Value jsonParams;
   Json::Reader reader;

   //DBG_MSG(("CAdasService::SetAttribute %s\n ", parms.c_str()));

   if (!reader.parse(parms, jsonParams, false))
   {
      jsonParams.clear();
      DBG_MSG(("CAdasService::SetAttribute: failed to format json value\n"));
   }

   	string strAttributeName  = jsonParams["AttributeName"].asString();

	if( 0 == strAttributeName.compare("Command") )
	{
		parseADASCommand(context,jsonParams);
	}

	//return bRet;
}

TRC_SCOPE_DEF(ADAS, CAdasService, getAttribute);
void CAdasService::getAttribute(SVCIPC_tReqContext context, const string&   parms)
{
	TRC_SCOPE(ADAS, CAdasService, getAttribute);
   Json::Value jsonParams;
   Json::Reader reader;

   DBG_MSG(("CAdasService::GetAttribute %s\n ", parms.c_str()));

   if (!reader.parse(parms, jsonParams, false))
   {
      jsonParams.clear();
      DBG_MSG(("CAdasService::GetAttribute: failed to format json value\n"));
   }

   string strAttributeName  = jsonParams["AttributeName"].asString();

	if(0== strAttributeName.compare("GetColorAttribute"))
	{
		;
	}

}

TRC_SCOPE_DEF(ADAS, CAdasService, setPositionAndSize);
void CAdasService::setPositionAndSize(SVCIPC_tReqContext context, const string& parms)
{
	TRC_SCOPE(ADAS, CAdasService, setPositionAndSize);

   Json::Value jsonParams;
   Json::Reader reader;
   Json::Value result;
   Json::FastWriter fastWriter;

   DBG_MSG(("CAdasService::setPositionAndSize %s\n ", parms.c_str()));

   if (!reader.parse(parms, jsonParams, false))
   {
      jsonParams.clear();
      DBG_MSG(("CAdasService::GetAttribute: failed to format json value\n"));
   }

	tagPositionAndSize tagRC;
	tagRC._rc.set(jsonParams["x"].asInt(),jsonParams["y"].asInt(),
			jsonParams["width"].asUInt(),jsonParams["height"].asUInt());

	asynSendMessage(tagRC,sizeof(tagRC));

   result["SetPositionAndSize"] = "Success";
	std::string ret = fastWriter.write(result);
	//SVCIPC_asyncReturnResult(context, ret.c_str(), NULL, NULL);
   

	returnResult(context, ret.c_str() ,STRING_NULL);
}

TRC_SCOPE_DEF(ADAS, CAdasService, getCameraConfig);
void CAdasService::getCameraConfig(SVCIPC_tReqContext context, const string& parms)
{
	TRC_SCOPE(ADAS, CAdasService, getCameraConfig);
	DBG_MSG(("CAdasService::getCameraConfig \n "));
	//asynSendMessage(eGetCameraConfig,NULL);
	SEND_BASEMESSAGE(eMsgType_HMI,eGetCameraConfig);
}
//MAN use case: ticket 1916886 - HMI shoud not get speed high on request camera state at background
TRC_SCOPE_DEF(ADAS, CAdasService, getCameraState);
void CAdasService::getCameraState(SVCIPC_tReqContext context, const string&   parms)
{
	Json::FastWriter writer;
	Json::Value result;
	TRC_SCOPE(ADAS, CAdasService, getCameraState);
    //cancel hide speed sate on camera off state to support HMI try manually active;
    //for SCANIA, always auto hide on high speed
    if(Env::isMANTarget())
    {
        CCameraCtrl* pCameraCtrl = CAdasCtrl::getInstance()->getCameraCtrl();
    	if( pCameraCtrl == NULL )
    	{
    		DBG_MSG(("error: CCameraCtrl==NULL \n "));
    		return;
    	}
        int iDeactiveNum=0;
        int iConfNum=0;
    	for(UInt32 i = 0; i < CCameraCtrl::eCameraNum; ++i)
    	{
    		CCamera* pCamera = pCameraCtrl->getCamera(CCamera::EPos(i));
    		if( pCamera && !pCamera->isOffCamera() )
    		{
                iConfNum++;
    			if(!( pCamera->isAutoActivated() 
                ||( pCamera->getStatus() == CCamera::eStatus_ManualActivated )))
    			{
                    iDeactiveNum++;
                }
    		}
    	}    
        if(iDeactiveNum ==iConfNum)
        {
            CReverseCameraMT::SetSpeedRestrictInvalid();
        }  
    }   
	DBG_MSG(("CAdasService::getCameraState \n "));
	//asynSendMessage(eGetCameraState,NULL);
	SEND_BASEMESSAGE(eMsgType_HMI,eGetCameraStateHMI);
	result["getCameraState"] = "Success";
	std::string ret = writer.write(result);
	returnResult(context, ret.c_str() ,STRING_NULL);
}

TRC_SCOPE_DEF(ADAS, CAdasService, emitCameraState);
void CAdasService::emitCameraState(BOOLEAN bSendDiagState,BOOLEAN bForceSend)
{
	TRC_SCOPE(ADAS, CAdasService, emitCameraState);

	CCameraCtrl* pCameraCtrl = CAdasCtrl::getInstance()->getCameraCtrl();
	if( pCameraCtrl == NULL )
	{
		DBG_MSG(("error: CCameraCtrl==NULL \n "));
		return;
	}

	Json::Value parameters[CCameraCtrl::eCameraNum];
	Json::Value out,outDiag;
	Json::FastWriter writer;
	string ret;
    static string sLastState= "none";

	for(UInt32 i = 0; i < CCameraCtrl::eCameraNum; ++i)
	{
		CCamera* pCamera = pCameraCtrl->getCamera(CCamera::EPos(i));
		Json::Value& jasonValue = parameters[i];
		if( pCamera && !pCamera->isOffCamera() )
		{

			jasonValue["CameraPos"]         = i + 1;
			jasonValue["CameraType"]        = (UInt32)pCamera->getType();
			jasonValue["CameraStatus"]      = (UInt32)pCamera->getExternalStatus();
			jasonValue["Show"]				= pCamera->isInShow();
			if( pCamera->isAutoActivated() )
			{
                if( pCamera->isHardPinActivated())
                {
                    jasonValue["TriggerMethod"]		= CCamera::eTrig_HardPin;
                }
	  	else if(pCamera->isCANCommandActivated()&&(CCamera::eType_General ==pCamera->getType()))
	  	{
	  		jasonValue["TriggerMethod"]		= CCamera::eTrig_CANCOMMAND;
			 // jasonValue["TriggerMethod"]		= CCamera::eTrig_CAN;//keep it as 1 for hmi not support it now
	  	}
                else if( pCamera->isCANActivated())
                {
                    jasonValue["TriggerMethod"]		= CCamera::eTrig_CAN;
                }
                else
                {
                    DBG_ERROR(("emitCameraState autoActive but unknow source %d\n", pCamera->getAutoActiveType()));
                    jasonValue["TriggerMethod"]		= CCamera::eTrig_Off;
                }
            }
			else if( pCamera->getStatus() == CCamera::eStatus_ManualActivated )
				jasonValue["TriggerMethod"]		= CCamera::eTrig_HMI;
			else
			{
                jasonValue["TriggerMethod"]		= (pCamera->IsSpeedHighState())?CCamera::eTrig_OverSpeed:CCamera::eTrig_Off;
            }
		}
		else
		{
			jasonValue["CameraPos"]         = i + 1;
			jasonValue["CameraType"]        = (UInt32)(CCamera::eType_Off);
			jasonValue["CameraStatus"]      = (UInt32) (CCamera::eEStatus_NotInitialised);
			jasonValue["Show"]				= FALSE;
			jasonValue["TriggerMethod"]		= CCamera::eTrig_Off;
		}
		
		out.append(jasonValue);
		if(bSendDiagState)
		{
			//is show = ture, dont override the trigger method to 3 to the show false channel
			int iState =  CCameraDetection::getInstance()->bGetCameraConnection(CCamera::EPos(i))?CCamera::eEStatus_Activated:CCamera::eEStatus_NotConnected;
			jasonValue["CameraStatus"] = iState;
			if(pCamera && (!pCamera->isOffCamera())&&(!pCamera->isInShow()))
			{
				jasonValue["TriggerMethod"]		= CCamera::eTrig_Detect;
				//jasonValue["CameraStatus"] 		= CCamera::eEStatus_NotConnected;
			}
		}
		#if 0
		 if(pCamera->isCANCommandActivated()&&(CCamera::eType_General ==pCamera->getType()))
	  	{
			 jasonValue["CANCmd"]		= 1;//add for debug
	  	}
		 else
		 {
			jasonValue["CANCmd"]		= 0;//add for debug
		 }
		 #endif
		outDiag.append(jasonValue);	
	}

	ret = writer.write(outDiag);
    //if(bSendDiagState)
    {
        emit("CameraStateDiag", ret);
        DBG_MSG(("emitCameraStateDiag: %s\n", ret.c_str()));
    }
	ret = writer.write(out);
    if(sLastState == ret && (!bForceSend))
    {
        DBG_ERROR(("same state not sent to HMI--> %s\n", ret.c_str()));
        return;
    }
	sLastState = ret;
	emit("CameraState", ret);
    DBG_MSG(("emitCameraState: %s\n", ret.c_str()));	

}

TRC_SCOPE_DEF(ADAS, CAdasService, emitCameraConfig);
void CAdasService::emitCameraConfig()
{
	TRC_SCOPE(ADAS, CAdasService, emitCameraConfig);
	Json::Value jsonParams;
	Json::FastWriter writer;
	string      strRet;

	CCameraCtrl* pCameraCtrl = CAdasCtrl::getInstance()->getCameraCtrl();
	if( pCameraCtrl == NULL )
	{
		DBG_MSG(("error: CCameraCtrl==NULL \n "));
	}

	CCamera* pCamera = pCameraCtrl->getCamera(CCamera::eCamera1);
	if( pCamera )
		jsonParams["Camera1"] = (UInt32)pCamera->getType();
	else
		jsonParams["Camera1"] = (UInt32)(CCamera::eType_Off);

	pCamera = pCameraCtrl->getCamera(CCamera::eCamera2);
	if( pCamera )
		jsonParams["Camera2"] = (UInt32)pCamera->getType();
	else
		jsonParams["Camera2"] = (UInt32)(CCamera::eType_Off);

	strRet = writer.write(jsonParams);
	emit("CameraConfig", strRet);

	DBG_MSG(("emitCameraConfig: %s\n", strRet.c_str()));
}

TRC_SCOPE_DEF(ADAS, CAdasService, parseADASCommand);
void CAdasService::parseADASCommand(SVCIPC_tReqContext context, Json::Value& parms)
{
	TRC_SCOPE(ADAS, CAdasService, parseADASCommand);
   Json::Value jsonParams;
   Json::FastWriter writer;
   string reply;
   string strItemName = parms["ItemName"].asString();
   string strValue = parms["Value"].asString();

   static tagSetAttributeCmd s_aryCmd[]=
   {
      {"ToggleSwitchCamera",           	"",    		eToggleSwitchCamera,              	makeFunctorWithRet(CAdasCtrl::getInstance(), &CAdasCtrl::canToggleSwitchCamera)},
      {"ShowCamera1",               	"On",     	eCamera1Activate_ON,               	makeFunctorWithRet(CAdasCtrl::getInstance(), &CAdasCtrl::canManualActivateCamera1)},
      {"ShowCamera1",                	"Off",     	eCamera1Activate_OFF,              	makeFunctorWithRet(CAdasCtrl::getInstance(), &CAdasCtrl::canManualDeactivateCamera1)},
      {"ShowCamera2",                	"On",      	eCamera2Activate_ON,               	makeFunctorWithRet(CAdasCtrl::getInstance(), &CAdasCtrl::canManualActivateCamera2)},
      {"ShowCamera2",                	"Off",     	eCamera2Activate_OFF,              	makeFunctorWithRet(CAdasCtrl::getInstance(), &CAdasCtrl::canManualDeactivateCamera2)},
      {"ShowGuideLine",                 "On",      	eShowGuideLine_ON,                 	NULL},
      {"ShowGuideLine",                 "Off",     	eShowGuideLine_OFF,                	NULL},
      {"CameraSettingState",   			"On",    	eActiveSettingMode_ON,     		   	NULL},
      {"CameraSettingState",   			"Off",    	eActiveSettingMode_OFF,				NULL},
   };

   UInt32 uiItemNum = sizeof(s_aryCmd)/sizeof(tagSetAttributeCmd);
   UInt32 i;
   for( i = 0; i < uiItemNum ; ++i)
   {
      if(0 == strItemName.compare(s_aryCmd[i].sCMDName))
      {
         if(0 == strValue.compare(s_aryCmd[i].sCMDContent))
         {
        	 CAdasService::CCommandFunctor* pFunctor = s_aryCmd[i].pFunctor;
        	 BOOLEAN bRet = TRUE;
        	 if( pFunctor )
        	 {
        		 bRet = (*pFunctor)();
        	 }

			 // todo send to mngr
			// asynSendMessage(s_aryCmd[i].eInternalCmdId, (void*)s_aryCmd[i].eInternalCmdId);
        	 if( bRet == FALSE )
			 {
				 DBG_MSG(("check preconditon of manually control camera is failed\n"));
                 //active failed use case for speed too high,need to send to HMI
                 //just send out state to notify HMI
				 SEND_BASEMESSAGE(eMsgType_HMIShowRequestFailed,eGetCameraState);
			 }
			 else
			 {
				 DBG_MSG(("check preconditon of manually control camera is Success\n"));
				 SEND_BASEMESSAGE(eMsgType_HMI,s_aryCmd[i].eInternalCmdId);
				 //jsonParams[strItemName.c_str()] = "Success";
			 } 
			 break;
         }
      }
    }
	if(uiItemNum > i)
	{
		jsonParams[strItemName.c_str()] = "Success";
	}
	else
	{
		jsonParams[strItemName.c_str()] = "Failed";
	}
	reply = writer.write(jsonParams);

	returnResult(context, reply,strItemName);
	DBG_MSG(("parsed HMI command %s - %s\n",strItemName.c_str(),strValue.c_str()));
}


