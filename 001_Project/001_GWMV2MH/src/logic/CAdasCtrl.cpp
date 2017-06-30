
#include "CAdasCtrl.hpp"
#include "Env.hpp"
#include "CAdasService.hpp"
#include "CCamera.hpp"
#include "CCameraMANTruck.hpp"
#include "../CEOL.hpp"
#include "CCanClient.hpp"
#include "CCanProcessor.hpp"
#include "CScaniaOnOffClient.hpp"
#include "graphics/CScaniaGraphicsImpl.hpp"
#include "pps/CCANPPSParser.h"
#include "pps/CCANIterf_MAN.h"
#include "pps/CCANIterf_SCANIA.h"
#include "pps/CPPS.h"
#include "CDiagnosticClient.hpp"
#include "CDiagnosticProcessor.hpp"
#include "CLayerManagerClient.hpp"
#include "CCameraDetection.hpp"

const static char* s_pszCameraWakeup = "-iCameraWakeup";
CAdasCtrl * CAdasCtrl::m_pInstance = NULL;

//-----------------------------------------------------
TRC_SCOPE_DEF(ADAS, CAdasCtrl, onCameraSignalCallback);
void onCameraSignalCallback(ECapCamSigEvent eCapCamSigEvent)
{
    TRC_SCOPE(ADAS, CAdasCtrl, onCameraSignalCallback);
	tagCamSigState tagCamSig;	
	if(eSignal1Valid==eCapCamSigEvent)
	{
		DBG_MSG(("onCameraSignal 1 Callback valid\n"));
		tagCamSig.eCamState = eCameraValid;
		tagCamSig.uiCamChan	= 0;		
	}
	else if(eSignal2Valid==eCapCamSigEvent)
	{
		DBG_MSG(("onCameraSignal 2 Callback valid\n"));
		tagCamSig.eCamState= eCameraValid;
		tagCamSig.uiCamChan	= 1;	

	}
	else if(eSignal1Invalid==eCapCamSigEvent)
	{
		DBG_MSG(("onCameraSignal 1 Callback invalid\n"));
		tagCamSig.eCamState= eCameraInvalid;
		tagCamSig.uiCamChan	= 0;	

	}
	else if(eSignal2Invalid==eCapCamSigEvent)
	{
		DBG_MSG(("onCameraSignal 2 Callback invalid\n"));
		tagCamSig.eCamState= eCameraInvalid;
		tagCamSig.uiCamChan	= 1;	

	}
    else if(eSignal1InitValid==eCapCamSigEvent)
    {
		DBG_MSG(("onCameraSignalCallback Init to Valid\n"));
		tagCamSig.eCamState= eCameraInitValid;
		tagCamSig.uiCamChan	= 0;	

    }
	else if(eSignal2InitValid==eCapCamSigEvent)
    {
		DBG_MSG(("onCameraSignalCallback Init to Valid\n"));
		tagCamSig.eCamState= eCameraInitValid;
		tagCamSig.uiCamChan	= 1;
    }
    else if(eSignal1InitInvalid==eCapCamSigEvent)
    {
		DBG_MSG(("onCameraSignalCallback 1 Init to Invalid\n"));
		tagCamSig.eCamState= eCameraInitInvalid;
		tagCamSig.uiCamChan	= 0;

    }
	else if(eSignal2InitInvalid==eCapCamSigEvent)
    {
		DBG_MSG(("onCameraSignalCallback Init to Invalid\n"));
		tagCamSig.eCamState= eCameraInitInvalid;
		tagCamSig.uiCamChan	= 1;
    }
    else
    {
		DBG_MSG(("onCameraSignalCallback invalid eCapCamSigEvent %d\n",eCapCamSigEvent));
		return;
    }
	//asynSendMessage(tagCamSig,sizeof(tagCamSigState));
	CAdasManager::getInstance()->pushMessage((tagBaseMessage&)tagCamSig, sizeof(tagCamSig));

}
//when callback stata could change in fast switch use case
//this callback on old channel should cancle when new channel alread required
TRC_SCOPE_DEF(ADAS, CAdasCtrl, onCameraLayerReadyCallback);
void onCameraLayerReadyCallback()
{
    // make sure camera already avtived
    //actived camera num
    //static BOOLEAN FirstTimeLayerContronl = TRUE;
    TRC_SCOPE(ADAS, CAdasCtrl, onCameraLayerReadyCallback);
   
    CCamera::EPos  epos= CAdasCtrl::getInstance()->getCameraCtrl()->getCurShowCameraPos();

    CCamera::EPos  Lastepos = CAdasCtrl::getInstance()->getLastShowCameraPos();
    if((epos != Lastepos)&&(Lastepos !=CCamera::eCameraNum))
    {
        DBG_ERROR(("onCameraSignalCallback: callback on old channel %d should cancled , lastpos = %d\n",epos,Lastepos));
        return;
    }
#if 0 
    if(CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(epos)->IsRunningKPIshowTimer())
    {
        DBG_MSG(("onCameraSignalCallback stopped KPI timer\n"));
        CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(epos)->stopKPIshowTimer();
    }
    else
    {
        DBG_MSG(("onCameraSignalCallback exit for KPI timer is out\n"));
        return;
    }
#endif 
    //fast cancel camera berfore drvier returns
    if((epos !=  CCamera::eCamera1) &&(epos !=  CCamera::eCamera2))
    {
        CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(CCamera::eCamera1)->setStartupState(FALSE);
        CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(CCamera::eCamera2)->setStartupState(FALSE);
    }
    else
    {
        CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(epos)->setStartupState(FALSE);
    }
    #if 0
    //first request ,adas set layer request
    if(FirstTimeLayerContronl)
    {
        FirstTimeLayerContronl= FALSE;
        printf("@@@@@@@@@@@@@CCamera first layer request @@@@@@@@@@@@@\n");
        DBG_MSG(("@@@@@@@@@@@@@CCamera first layer request @@@@@@@@@@@@@\n"));
        CLayerManagerClient::getInstance()->RequestShowADASLayer();
    }
    #endif
    SEND_BASEMESSAGE(eMsgType_DriverCamera, eGetCameraState);
}


void onSetLayerReqCallback()
{
    CLayerManagerClient::getInstance()->RequestShowADASLayer();
    //fprintf(stderr,"@@@@@@@@@@@@@CCamera first layer request @@@@@@@@@@@@@\n");
}

void onGraphicLayerReadyCallback()
{
    // make sure camera already avtived
    SEND_BASEMESSAGE(eMsgType_DriverGraphic, eGetCameraState);
}

//-----------------------------------------------------

CAdasCtrl* CAdasCtrl::getInstance()
{
   if(m_pInstance == NULL)
   {
      m_pInstance = new CAdasCtrl();
   }
   return m_pInstance;
}

void CAdasCtrl::delInstance()
{
   if(m_pInstance != NULL)
   {
      delete m_pInstance;
      m_pInstance = NULL;
   }
}

CAdasCtrl::~CAdasCtrl()
{
   ;
}

CAdasCtrl::CAdasCtrl()
: m_bShowGuideLine(FALSE)
, m_pCameraCtrl(NULL)
, m_eLastShowCameraPos(CCamera::eCameraNum)
{
   m_pCameraCtrl = new CCameraCtrl();//todo:add MAN cameraCtrl Object
   for(int i=0; i<CCameraCtrl::eCameraNum;i++)
   {
       m_bNeedUpdateCameraState[i] = FALSE;
       m_aryLastCameraStatus[i] = CCamera::eStatus_Deactivated;
       m_aryLastCameraAAType[i] = CCamera::eType_NULL;
   }
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, onTimer);
void onTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
    TRC_SCOPE(ADAS, CAdasCtrl, onTimer);
	if( eStatus == CTimer::TS_TIMER )
	{
		DBG_MSG(("on Timer repeatCnt = %u\n", uiRepeatCnt));
	}
	else
	{
		DBG_MSG(("on Timer complete repeatCnt = %u\n", uiRepeatCnt));
	}
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, onExitRvsTimer);
void onExitRvsTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
    TRC_SCOPE(ADAS, CAdasCtrl, onExitRvsTimer);
	DBG_MSG(("onExitRvsTimer\n"));
	//CAdasManager::getInstance()->pushMessage(new CReverseTimerDeactivatedMsg((UInt32)getPos()));
}

TRC_SCOPE_DEF(ADAS, CAdasCtrl, initialize);
BOOLEAN CAdasCtrl::initialize()
{
    TRC_SCOPE(ADAS, CAdasCtrl, initialize);
	if( !Env::initialize() )
	{
		DBG_ERROR(("Env initialize failed\n"));
		return FALSE;
	}

	if( !EOL::initialize() )
	{
		DBG_MSG(("EOL::initialize failed\n"));
		return FALSE;
	}

	//for(UInt32 i = 0 ; i < )
	//CMemManager::getInstance()->registerSmallBin(8,100,10);
    //set guideline state on EOL
    if(Env::isScaniaTarget())
    {
        UInt32 guideline1 = EOL::getReverseGuideLineIndex(CCamera::eCamera1);
        UInt32 guideline2 = EOL::getReverseGuideLineIndex(CCamera::eCamera2);
        UInt32 guidelineMax = EOL::getOff_GuideLineNum();
        if(((0<=guideline1)&&(guidelineMax > guideline1))
         ||((0<=guideline2)&&(guidelineMax > guideline2)))
        {
            m_bShowGuideLine = TRUE;
            DBG_MSG(("EOL turn m_bShowGuideLine = TRUE;\n"));
        }
    }

	if( !bAdasInitCameraSystem() )
	{
		DBG_ERROR(("bAdasInitMiniCameraSystem failed\n"));
		return FALSE;
	}

	m_pCameraCtrl->initialize();

	CSvcIpcServiceAdaptor::getInstance()->registerServiceParser(CAdasService::getInstance());
	//CSvcIpcServiceAdaptor::getInstance()->registerClientParser(CCanClient::getInstance());//remove CAN ipc service
	CSvcIpcServiceAdaptor::getInstance()->registerClientParser(CScaniaOnOffClient::getInstance());
	CSvcIpcServiceAdaptor::getInstance()->registerClientParser(CDiagnosticClient::getInstance());
	CSvcIpcServiceAdaptor::getInstance()->registerClientParser(CLayerManagerClient::getInstance());
	CDiagnosticProcessor::getInstance();
	if(Env::isScaniaTarget())
	{
      CCANPPSParser::getInstance(CCANIterfSCAINA::getInstance());
	}
	else if(Env::isMANTarget())
    {
      CCANPPSParser::getInstance(CCANIterfMAN::getInstance());
    }
    else
    {
      DBG_MSG(("CAdasCtrl::unInitialize begin\n"));
    }
    
    m_GuideLineTimer.setDelay(0);
    m_GuideLineTimer.setRepeatCount(1);//0 is always loop
    m_GuideLineTimer.setCallBack(::makeFunctor(this, &CAdasCtrl::onGuideLineTimer), NULL);  
    CCameraDetection::getInstance()->start();
	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, unInitialize);
void CAdasCtrl::unInitialize()
{
    TRC_SCOPE(ADAS, CAdasCtrl, unInitialize);
	DBG_MSG(("CAdasCtrl::unInitialize begin\n"));
	CCanProcessor::delInstance();
	//CPPS::deleteInstance();

	DBG_MSG(("CAdasCtrl::unInitialize 1\n"));
	if( m_pCameraCtrl )
	{
		m_pCameraCtrl->unInitialize();
		delete m_pCameraCtrl;
		m_pCameraCtrl = NULL;
	}

	DBG_MSG(("CAdasCtrl::unInitialize 2\n"));
	//
	usleep(10000);
	//

	bAdasDestroyCameraSystem();

	//CTimerManager::getInstance()->quit();
	//CTimerManager::deleteInstance();
	EOL::unInitialize();

	DBG_MSG(("CAdasCtrl::unInitialize end\n"));

}

void CAdasCtrl::beforeHandleMessageQueue()
{
	;
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, afterHandleMessageQueue);
void CAdasCtrl::afterHandleMessageQueue()
{
	TRC_SCOPE(ADAS, CAdasCtrl, afterHandleMessageQueue);
	CCameraCtrl::EState eCurState = m_pCameraCtrl->getState();
	CCamera::EPos		eCurShowCameraPos = m_pCameraCtrl->getCurShowCameraPos();
	CCamera::EStatus	aryCurCameraStatus[2];
    CCamera::EAutoActiveType aryCurCameraActiveType[2];
	aryCurCameraStatus[0] = m_pCameraCtrl->getCameraStatus(CCamera::eCamera1);
	aryCurCameraStatus[1] = m_pCameraCtrl->getCameraStatus(CCamera::eCamera2);

	aryCurCameraActiveType[0] = m_pCameraCtrl->getCameraActiveType(CCamera::eCamera1);
	aryCurCameraActiveType[1] = m_pCameraCtrl->getCameraActiveType(CCamera::eCamera2);	
    
	BOOLEAN	bCameraStateChanged = ((m_eLastShowCameraPos != eCurShowCameraPos) 
                                 ||(aryCurCameraStatus[0] != m_aryLastCameraStatus[0])
			                     ||(aryCurCameraStatus[1] != m_aryLastCameraStatus[1])) ;

	BOOLEAN	bCameraActiveTypeChanged = (  (aryCurCameraActiveType[0] != m_aryLastCameraAAType[0] )
                                        ||(aryCurCameraActiveType[1] != m_aryLastCameraAAType[1] )) ;
    DBG_MSG(("s1 %d ls1 %d s2 %d ls2 %d t1 %d lt1 %d t2 %d lt2 %d\n",aryCurCameraStatus[0],m_aryLastCameraStatus[0],aryCurCameraStatus[1],m_aryLastCameraStatus[1],aryCurCameraActiveType[0] ,m_aryLastCameraAAType[0],aryCurCameraActiveType[1] ,m_aryLastCameraAAType[1]));
    //in HMI state5, startup timer is set, if switch overidable screen, this timer should not cancel but camera can not send out
	if(m_pCameraCtrl->IsManuallyClosed())
    { 
    	DBG_MSG(("-------------------camera%d off------------Disable capture manually - ver2-------------------------------\n",eCurShowCameraPos+1));
        //not release in  2015-9-18 verison, need more test
        //CCameraSysManager::getInstance()->setCameraState(false);
		//CCameraSysManager::getInstance()->pause();
    }
    //on new request to show camera -- cancel manully closed state
    //the usecase not cancel is... speed??
    if(((m_eLastShowCameraPos != eCurShowCameraPos)
     &&(CCamera::eCameraNum != eCurShowCameraPos)
     &&(CCamera::eCameraNum != m_eLastShowCameraPos))
     ||(bCameraActiveTypeChanged))
    {
		m_aryLastCameraAAType[0] = aryCurCameraActiveType[0];
		m_aryLastCameraAAType[1] = aryCurCameraActiveType[1];
        m_pCameraCtrl->DisableManuallyClose();      
    }

    //active on this same channel with new request use case: send out camera state direcly ,expect actived by speed after rear gear cancelled 
    //for acitve type reverse gear cancel but speed is in limit, no need to notify new active event to cancel override state
    //todo: send out when active tyoe of CAN reqeust is change?? now is not support!
    if((bCameraStateChanged||bCameraActiveTypeChanged)
        &&(m_eLastShowCameraPos == eCurShowCameraPos) 
        && (eCurShowCameraPos != CCamera::eCameraNum )
        &&(CCamera::eType_CAN_SPEED_DEA_REAR != m_pCameraCtrl->getCameraActiveType(eCurShowCameraPos)))
    {
        char str[] = "afterHandleMessageQueue";
        onGetCameraState((void *)str);
    } 

	if( bCameraStateChanged || (m_eLastState != eCurState) )
	{
		 if( m_pCameraCtrl->isAllCamerasOff())
		{
            CCamera* pCloseCamera;
            for(UInt32 uClzCam=0;  uClzCam<(CCamera::eCameraNum) ; uClzCam++)
            {
                pCloseCamera = m_pCameraCtrl->getCamera((CCamera::EPos) uClzCam);
                if(pCloseCamera)
                {
        			pCloseCamera->stopShowTimer();
                    pCloseCamera->stopKPIshowTimer();            
                }
            }            
            
            char str[] = "--->AllCamerasOff";
            onGetCameraState((void *)str);            
			// m_pCameraCtrl->onOff();
			// adas goto back and transit to other process
        	DBG_MSG(("-------------------camera%d off------------Disable capture - ver2-------------------------------\n",eCurShowCameraPos+1));
            CCameraSysManager::getInstance()->setCameraState(FALSE);
			CCameraSysManager::getInstance()->pause();
		}
		else
		{
            //resume can not push to queue --todo use case for delayed pause after resume
			CCameraSysManager::getInstance()->resume();
    		DBG_MSG(("-------------------camera%d on ------------Enable capture - ver2------------------------------\n",eCurShowCameraPos+1));
            //CCameraSysManager::getInstance()->setCameraState(true);
		}

		// DBG_MSG(("afterHandleMessageQueue 1\n"));
		static Int32 s_idxs[2] = {0,1};
        BOOLEAN bRearCamermaReActived = FALSE;
        //new channnel active use case: only send put state after layer update finished, then callback runs 
		if( m_eLastShowCameraPos != eCurShowCameraPos && eCurShowCameraPos != CCamera::eCameraNum )
		{
			//DBG_MSG(("afterHandleMessageQueue 2\n"));
			bRearCamermaReActived = TRUE;
			if(CCamera::eCameraNum != m_eLastShowCameraPos)
			{
    			CCamera* pLastActiveCamera = m_pCameraCtrl->getCamera((CCamera::EPos) m_eLastShowCameraPos);
    			pLastActiveCamera->stopShowTimer();
                pLastActiveCamera->stopKPIshowTimer();
            }
            CCamera* pCurActiveCamera = m_pCameraCtrl->getCamera((CCamera::EPos) eCurShowCameraPos);

			//no dealy send out state5, but flashed with black screen rightaway
		    CCameraSysManager::getInstance()->DisablePostData();//every state5 flush camera with black data before it is ready
 
            if(EOL::getCameraStartupTime(eCurShowCameraPos)!= 0)
            {
                //timer may out if it start in update() phase
                CScaniaGraphicsImpl::getInstance()->asynshowStartUpImage(s_idxs[eCurShowCameraPos],TRUE);
    			pCurActiveCamera->startShowTimer();//align with enable capture and post to hide switch after graphic hide
                //set callback in driver side to notify camerastate after graphic layer is ready
                //fast use case this call back will cause problem
                //CCameraSysManager::getInstance()->asyncSetReportGraphicLayerReady();
                char str[] = "GraphicTimer-ForceSentState5";
                onGetCameraState((void *)str);
            }		
            else
            {
			    // if no predefined image, not send out state5 too fast for last camera view will be displayed on screen
			    //but a dealy will cause HMI lost one state5 and outof sync!!               
                char str[] = "NoGraphicTimer-ForceSentState5";
                onGetCameraState((void *)str);
                //two image object use some buffer,new camera is not show image,so clear old image is necessary
                if(CCamera::eCameraNum != m_eLastShowCameraPos)
                CScaniaGraphicsImpl::getInstance()->asynshowStartUpImage(s_idxs[m_eLastShowCameraPos],FALSE);
                //set callback in driver side to notify camerastate after camera layer is ready
                //CCameraSysManager::getInstance()->asyncSetReportCameraLayerReady();
                //force to send out camera state if KPItimer out, and avoid call back is not trigger in fast switch use case
                //pCurActiveCamera->startKPIshowTimer();
            }
			CCameraSysManager::getInstance()->setCameraSourceIndex(s_idxs[eCurShowCameraPos]) ;
			
		}
        else if(!m_pCameraCtrl->isAllCamerasOff())
        {
            CCameraSysManager::getInstance()->setCameraState(TRUE);
        }
        

        //eCurShowCameraPos could be invalid! getCamera prvent it
		CCamera* pCamera = m_pCameraCtrl->getCamera(eCurShowCameraPos);
		if( pCamera && pCamera->isInShow() && m_bShowGuideLine && (CCamera::eType_Reverse ==pCamera->getType()))
		{
            UInt32 uiCameraStartupTime = EOL::getCameraStartupTime(eCurShowCameraPos);
            //bRearCamermaReActived: for multiactive use case, camera is not exit but dierctly continously to show
			if(( uiCameraStartupTime!= 0)&&(bRearCamermaReActived))
			{
                CScaniaGraphicsImpl::getInstance()->asynShowGuideLine(EOL::getOff_GuideLineNum());
                m_GuideLineTimer.stop();
		        m_GuideLineTimer.setDelay(uiCameraStartupTime);
                m_GuideLineTimer.setRepeatCount(1);
				m_GuideLineTimer.start();
			}
			else
			 	CScaniaGraphicsImpl::getInstance()->asynShowGuideLine(EOL::getReverseGuideLineIndex(eCurShowCameraPos));
			
		}
		else
		{
			m_GuideLineTimer.stop();
			CScaniaGraphicsImpl::getInstance()->asynShowGuideLine(EOL::getOff_GuideLineNum());
		}

		m_eLastState = eCurState;
		m_eLastShowCameraPos = eCurShowCameraPos;
		m_aryLastCameraStatus[0] = aryCurCameraStatus[0];
		m_aryLastCameraStatus[1] = aryCurCameraStatus[1];
	}
}

BOOLEAN	CAdasCtrl::isNeedFastADAS()
{
    //todo:fastADAS process
	//if( Env::isMANTarget() )
    //fast ADAS from command line is all control by system, no limit by ADAS side
	{
		Int32 iCameraWakeup = CCommandLineParser::getInstance()->getItemInt(s_pszCameraWakeup);
		if( iCameraWakeup == 1 )
		{
		//	m_pCameraCtrl->setCameraWakeup(CCamera::eCamera1);
		    CScaniaOnOffClient::getInstance()->FastSetScaniaPinShowCam(CCamera::eCamera1);
			return TRUE;
		}
		else if( iCameraWakeup == 2 )
		{
		//	m_pCameraCtrl->setCameraWakeup(CCamera::eCamera2);
		    CScaniaOnOffClient::getInstance()->FastSetScaniaPinShowCam(CCamera::eCamera2);
			return TRUE;
		}
	}
#if 0    
	//else if( Env::isScaniaTarget() )
	{
		// SCANIA read commandline
		Int32 iCameraWakeup = CCommandLineParser::getInstance()->getItemInt(s_pszCameraWakeup);
		if( iCameraWakeup == 1 )
		{
		//	m_pCameraCtrl->setCameraWakeup(CCamera::eCamera1);
			return TRUE;
		}

		// SCANIA read pps fast ADAS
		CCameraSysManager::getInstance()->pause();
		Int32 i = 5;
		while( i-- )
		{
			//if( CCANPPSParser::getInstance()->isNeedFastADAS() )
			{
			//	CCameraSysManager::getInstance()->resume();
			//	return TRUE;
			}
			usleep(100000);
		}
	}
#endif
	return FALSE;
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, startFastADAS);
void CAdasCtrl::startFastADAS()
{
    TRC_SCOPE(ADAS, CAdasCtrl, startFastADAS);
	printf("start FAST ADAS - ver-2015-08-14\n");
	//bAdasInitCameraSystemGraphics();
	CCameraSysManager::getInstance()->resume();
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, startNormalADAS);
void CAdasCtrl::startNormalADAS()
{
    TRC_SCOPE(ADAS, CAdasCtrl, startNormalADAS);
	//printf("start normal ADAS - ver-2015-09-28\n");
    //found bug in special use case: camera state outof sync when first pause delayed
	//m_pCameraCtrl->updateState();
	//default pause will cause lose sync when show camera after process run,open for test fix
	CCameraSysManager::getInstance()->pause();
}

void CAdasCtrl::onAutoUpdateState(void *pdata)
{
	m_bNeedUpdateCameraState[0] = TRUE;
	m_bNeedUpdateCameraState[1] = TRUE;
	if( m_pCameraCtrl )
	{
		m_pCameraCtrl->updateCameraStateAuto(0);
		m_pCameraCtrl->updateCameraStateAuto(1);
	}
}

void CAdasCtrl::checkSystemEventAfterStartUp()
{
	if( isNeedFastADAS() )
	{
		onAutoUpdateState(NULL);
		//CLayerManagerClient::getInstance()->RequestShowADASLayer();
	}
    //new request for all target can wakeup by hard pin now
    CScaniaOnOffClient::getInstance()->getPowerModeInfo();
    //DBG_MSG(("check signal state adas may miss before start !\n"));
}

//---------------------------------CAdasService--------------------------------------------------
BEGIN_DISPATCH(CAdasCtrl)
	DISPATCH_EVENT(eToggleSwitchCamera, toggleSwitchCamera)
	DISPATCH_EVENT(eCamera1Activate_ON, showCamera)
	DISPATCH_EVENT(eCamera1Activate_OFF, showCamera)
	DISPATCH_EVENT(eCamera2Activate_ON, showCamera)
	DISPATCH_EVENT(eCamera2Activate_OFF, showCamera)

	DISPATCH_EVENT(eShowGuideLine_ON, showGuideLine)
	DISPATCH_EVENT(eShowGuideLine_OFF, showGuideLine)
	DISPATCH_EVENT(eActiveSettingMode_ON, activeSettingMode)
	DISPATCH_EVENT(eActiveSettingMode_OFF, activeSettingMode)

	DISPATCH_EVENT(eGetCameraState, onGetCameraState)
	//DISPATCH_EVENT(eGetCameraStateDiag, onGetCameraStateDiag)
	DISPATCH_EVENT(eGetCameraStateHMI, onGetCameraStateHMI)	
	
	DISPATCH_EVENT(eGetCameraConfig, onGetCameraConfig)

	DISPATCH_EVENT(eSetPositionAndSize, setPosSize)

	DISPATCH_EVENT(eOnOffSetSW12VOutSucceed, onPowerOnOffSucceed)
	DISPATCH_EVENT(eOnOffSetSW12VOutFail, onPowerOnOffFail)
//todo: MAN/SCAINA
	DISPATCH_EVENT(eOnOffHardPinCamera,  onAutoUpdateState)

	DISPATCH_EVENT(eOtherEvent_CameraSignalEvent, onCaptureSignalEvent)

	
	DISPATCH_EVENT(eOtherEvent_ReverseCam1TimerDeactivate, setReverseTimerDeactivate)
	DISPATCH_EVENT(eOtherEvent_ReverseCam2TimerDeactivate, setReverseTimerDeactivate)
END_DISPATCH

BOOLEAN	CAdasCtrl::canToggleSwitchCamera()
{
    //let coach and trunk shares some logic
	//for MAN, hk request will cancel rear gear state
	return m_pCameraCtrl->canToggleSwitchCamera();
}

void CAdasCtrl::toggleSwitchCamera(void* pData)
{
	m_pCameraCtrl->toggleSwitchCamera();
}

BOOLEAN	CAdasCtrl::canManualActivateCamera1()
{
    //for MAN, hk request will cancel rear gear state
    //if(Env::isMANTarget()) sync to SCANIA
    {
        //if manually active same camera  ,level it to state -- supory A2M process now. otherwise just cancle it directly 
        if(CCamera::eCamera2== m_pCameraCtrl->getCurShowCameraPos())
    	CCanProcessor::getInstance()->cancelRearGearState(TRUE);
        CReverseCameraMT::SetSpeedRestrictInvalid();
    }
    //special rear active one first then manually active on the same one??
    
	return m_pCameraCtrl->canManualActivate(CCamera::eCamera1);
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, canManualDeactivateCamera1);
BOOLEAN	CAdasCtrl::canManualDeactivateCamera1()
{
    //if current is standby ignore this request
    TRC_SCOPE(ADAS, CAdasCtrl, canManualDeactivateCamera1);
    if(CScaniaOnOffClient::getInstance()->isInStandbyState())
    {
        DBG_MSG(("received hide camera1 manually request on standby mode, just ignore it \n"));
        return FALSE;
    }
        
    //for MAN, hk request will cancel rear gear state
    //if(Env::isMANTarget()) sync to SCANIA
    {
        //CReverseCamera::vSetDirectlyCancelRearCam();//for two rear camera case : avoid antoher cam keep acitve 
    	CCanProcessor::getInstance()->cancelRearGearState(TRUE);
    }
	return m_pCameraCtrl->canManualDeactivate(CCamera::eCamera1);
}

BOOLEAN	CAdasCtrl::canManualActivateCamera2()
{
    //for MAN, hk request will cancel rear gear state
    //if(Env::isMANTarget()) sync to SCANIA
    {
        if(CCamera::eCamera1== m_pCameraCtrl->getCurShowCameraPos())
    	CCanProcessor::getInstance()->cancelRearGearState(TRUE);
        CReverseCameraMT::SetSpeedRestrictInvalid();
    }
	return m_pCameraCtrl->canManualActivate(CCamera::eCamera2);
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, canManualDeactivateCamera2);
BOOLEAN	CAdasCtrl::canManualDeactivateCamera2()
{
    //if current is standby ignore this request
    TRC_SCOPE(ADAS, CAdasCtrl, canManualDeactivateCamera1);
    if(CScaniaOnOffClient::getInstance()->isInStandbyState())
    {
        DBG_MSG(("received hide camera2 manually request on standby mode, just ignore it \n"));
        return FALSE;
    }
    
    //for MAN, hk request will cancel rear gear state
    //if(Env::isMANTarget()) sync to SCANIA
    {
       // CReverseCamera::vSetDirectlyCancelRearCam();//for two rear camera case : avoid antoher cam keep acitve 
    	CCanProcessor::getInstance()->cancelRearGearState(TRUE);
    }
	return m_pCameraCtrl->canManualDeactivate(CCamera::eCamera2);
}

TRC_SCOPE_DEF(ADAS, CAdasCtrl, showCamera);
void CAdasCtrl::showCamera(void* pData)
{
    TRC_SCOPE(ADAS, CAdasCtrl, showCamera);

	tagBaseMessage* pMsg = (tagBaseMessage*)pData;
	DBG_MSG(("showCamera msg id = %d\n",pMsg->_uiID));
	switch(pMsg->_uiID)
	{
	case eCamera1Activate_ON:
	{
		m_pCameraCtrl->updateCameraStateManually(CCameraCtrl::eOp_ShowCamera1);
		break;
	}
	case eCamera1Activate_OFF:
	{
		m_pCameraCtrl->updateCameraStateManually(CCameraCtrl::eOp_HideCamera1);
		break;
	}
	case eCamera2Activate_ON:
	{
		m_pCameraCtrl->updateCameraStateManually(CCameraCtrl::eOp_ShowCamera2);
		break;
	}
	case eCamera2Activate_OFF:
	{
		m_pCameraCtrl->updateCameraStateManually(CCameraCtrl::eOp_HideCamera2);
		break;
	}
	default:
		break;
	}
}

TRC_SCOPE_DEF(ADAS, CAdasCtrl, showGuideLine);
void CAdasCtrl::showGuideLine(void* pData)
{
    TRC_SCOPE(ADAS, CAdasCtrl, showGuideLine);
	tagBaseMessage* pMsg = (tagBaseMessage*)pData;
	switch(pMsg->_uiID)
	{
	case eShowGuideLine_ON:
	{
		m_bShowGuideLine = TRUE;
		DBG_MSG(("show Guideline\n"));
		CCamera* pCamera = m_pCameraCtrl->getCamera(CCamera::eType_Reverse);
		if( pCamera && pCamera->isInShow() )
		{
			CScaniaGraphicsImpl::getInstance()->asynShowGuideLine(EOL::getReverseGuideLineIndex(pCamera->getPos()) );
		}
	}
		break;
	case eShowGuideLine_OFF:
	{
		m_bShowGuideLine = FALSE;
		DBG_MSG(("hide Guideline OFF %d\n",EOL::getOff_GuideLineNum()));
		CScaniaGraphicsImpl::getInstance()->asynShowGuideLine(EOL::getOff_GuideLineNum());
	}
		break;
	default:
		break;
	}
}

void CAdasCtrl::activeSettingMode(void* pData)
{
	tagBaseMessage* pMsg = (tagBaseMessage*)pData;
	switch(pMsg->_uiID)
	{
	case eActiveSettingMode_ON:
		m_pCameraCtrl->updateState(CCameraCtrl::eOp_EnterCameraSetting);
		break;
	case eActiveSettingMode_OFF:
		m_pCameraCtrl->updateState(CCameraCtrl::eOp_ExitCameraSetting);
		break;
	default:
			break;
	}
}

TRC_SCOPE_DEF(ADAS, CAdasCtrl, onGetCameraState);
void CAdasCtrl::onGetCameraState(void* pData)
{
    TRC_SCOPE(ADAS, CAdasCtrl, onGetCameraState);
    if(m_pCameraCtrl->IsManuallyClosed()) 
    {
        DBG_MSG(("cancelling sent out CameraState for manually hide camera now @ %s\n",(char*)pData));
    }
    DBG_MSG(("call onGetCameraState for %s\n",(char*)pData));
    //on HMI reqeust camera data, not reorting camera speed over limit
    //after HMI active camera, speed can not auto hide camera
	CAdasService::getInstance()->emitCameraState(FALSE,FALSE);
}
//to support HMI ask same camera state use case
TRC_SCOPE_DEF(ADAS, CAdasCtrl, onGetCameraStateHMI);
void CAdasCtrl::onGetCameraStateHMI(void* pData)
{
    TRC_SCOPE(ADAS, CAdasCtrl, onGetCameraStateHMI);
    if(m_pCameraCtrl->IsManuallyClosed()) 
    {
        DBG_MSG(("cancelling sent out CameraState for manually hide camera now @ %s\n",(char*)pData));
    }
    DBG_MSG(("call onGetCameraStateHMI for %s\n",(char*)pData));
    //on HMI reqeust camera data, not reorting camera speed over limit
    //after HMI active camera, speed can not auto hide camera
	CAdasService::getInstance()->emitCameraState(FALSE,TRUE);
}

TRC_SCOPE_DEF(ADAS, CAdasCtrl, onGetCameraStateDiag);
void CAdasCtrl::onGetCameraStateDiag(void* pData)
{
    TRC_SCOPE(ADAS, CAdasCtrl, onGetCameraStateDiag);
    DBG_MSG(("call onGetCameraState for Diag @ %s\n",(char*)pData));
    CAdasService::getInstance()->emitCameraState(TRUE,FALSE);
}

void CAdasCtrl::onGetCameraConfig(void* pData)
{
	CAdasService::getInstance()->emitCameraConfig();
}

void CAdasCtrl::setPosSize(void* pData)
{
	//DBG_MSG(("CAdasCtrl::setPosSize\n"));
	tagPositionAndSize* pRC = static_cast<tagPositionAndSize*>(pData);
	if( pRC )
	{
		CScaniaGraphicsImpl::getInstance()->asynSetPosAndSize(pRC->_rc);
		//DBG_MSG(("CAdasCtrl::setPosSize 1\n"));

		CCameraSysManager::getInstance()->setPosAndSize(pRC->_rc);
		//DBG_MSG(("CAdasCtrl::setPosSize 2\n"));
	}
	//DBG_MSG(("CAdasCtrl::setPosSize end\n"));
}

TRC_SCOPE_DEF(ADAS, CAdasCtrl, setReverseTimerDeactivate);
void CAdasCtrl::setReverseTimerDeactivate(void* pData)
{
    TRC_SCOPE(ADAS, CAdasCtrl, setReverseTimerDeactivate);
	DBG_MSG(("CAdasCtrl::setReverseTimerDeactivate start\n"));
	if( m_pCameraCtrl )
	{
		tagBaseMessage* pMsg = (tagBaseMessage*)pData;
		if( pMsg->_uiID == eOtherEvent_ReverseCam1TimerDeactivate )
			m_pCameraCtrl->updateState(CCameraCtrl::eOp_DeaCamera1);
		else if( pMsg->_uiID == eOtherEvent_ReverseCam2TimerDeactivate )
			m_pCameraCtrl->updateState(CCameraCtrl::eOp_DeaCamera2);
	}
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, onPowerOnOffSucceed);
void CAdasCtrl::onPowerOnOffSucceed(void* pData)
{
   TRC_SCOPE(ADAS, CAdasCtrl, onPowerOnOffSucceed);
   DBG_MSG(("CAdasCtrl::power on Camera Succeed\n"));
   return;
}

TRC_SCOPE_DEF(ADAS, CAdasCtrl, onPowerOnOffFail);
void CAdasCtrl::onPowerOnOffFail(void* pData)
{
   TRC_SCOPE(ADAS, CAdasCtrl, onPowerOnOffFail);
   DBG_MSG(("CAdasCtrl::power on Camera failed\n"));
   //power on failed need show blue screen
   //CCameraSysManager::getInstance()->pause();
}
static Int32 s_LogicCamChan[2] = {0,1};
//queued event from driver call back after enable camera or camsera state change
TRC_SCOPE_DEF(ADAS, CAdasCtrl, onCaptureSignalEvent);
void CAdasCtrl::onCaptureSignalEvent(void* pdata)
{
    TRC_SCOPE(ADAS, CAdasCtrl, onCaptureSignalEvent);
	tagCamSigState* pcamstate = (tagCamSigState*)pdata;
	Int32 ilogicChan = (Int32)s_LogicCamChan[pcamstate->uiCamChan];
	CCamera::EPos ePos = m_pCameraCtrl->getCurShowCameraPos();
	if(ePos>=CCamera::eCameraNum) 
	{
		DBG_ERROR(("error:current active cam = %d, driver report cam state on chan= %d\n",(int)ePos,ilogicChan));
	}
	CCamera* pCamera = m_pCameraCtrl->getCamera(ePos);
	if( ilogicChan != (Int32)ePos )
	{
		DBG_MSG(("current active cam = %d, driver report cam state on chan= %d\n",(int)ePos,ilogicChan));
	}
	DBG_MSG(("onCaptureSignalEvent active cam = %d, driver report cam state on chan= %d\n",(int)ePos,ilogicChan));

	//udpate backgound thread state
	BOOLEAN bCameraState = FALSE;
	if((eCameraValid == pcamstate->eCamState)||(eCameraInitValid == pcamstate->eCamState)) bCameraState = TRUE;
	if((eCameraInvalid == pcamstate->eCamState)||(eCameraInitInvalid == pcamstate->eCamState)) bCameraState = FALSE;
	
	CCameraDetection::getInstance()->vCB_CamDetection(bCameraState,ilogicChan);
	
	//update a valid camera detection to detection moudle
	if(eCameraValid == pcamstate->eCamState)
	{
		if( pCamera )
		{
			//if( !bValid )
			{
				pCamera->setSignalValid(TRUE);
                if(pCamera->isInStartUpPhase())
                {
                   DBG_MSG(("camera is not finish start up, signal good state is not emit\n"));
                }
                else
                {
                	char str[] = "onCaptureSignalValid";
                    onGetCameraState((void *)str);
                }
			}
		}
	}
	else if(eCameraInvalid == pcamstate->eCamState)
	{
		if( pCamera )
		{
			//if( bValid )
			{
				pCamera->setSignalValid(FALSE);

				if(pCamera->isInStartUpPhase())
				{
				   DBG_MSG(("camera is not finish start up, signal lost state is not emit\n"));
				}
				else
				{
					char str[] = "onCaptureSignalInvalid";
				    onGetCameraState((void *)str);
				}	
			}
		}	
	}
	else if(eCameraInitValid == pcamstate->eCamState)
	{
		if( ePos == ilogicChan )
		{
			if( pCamera )
			{
				pCamera->setSignalValid(TRUE);
				pCamera->SetVsynSigIsReadyToChk(TRUE);
			}
		}

	}	
	else if(eCameraInitInvalid == pcamstate->eCamState)
	{
		if( ePos == ilogicChan )
		{
			if( pCamera )
			{
				pCamera->setSignalValid(FALSE);
				pCamera->SetVsynSigIsReadyToChk(TRUE);
			}
		}

	}
}

//-----------------------------------------------------------------------------
//TODO set screen micro SCREEN_FORMAT_UYVY = 14
TRC_SCOPE_DEF(ADAS, CAdasCtrl, bAdasInitCameraSystem);
#define NUM_CAPTURE_FRAME_BUFFER 5
bool CAdasCtrl::bAdasInitCameraSystem()
{
    TRC_SCOPE(ADAS, CAdasCtrl, bAdasInitCameraSystem);
	//return TRUE;
	UInt32 uiSkipFrames = CCommandLineParser::getInstance()->getItemUInt("-uiSkipFrames");
    UInt32 uiSigDelay = CCommandLineParser::getInstance()->getItemUInt("-uiSigDelay");
    Int32  iverbosity = CCommandLineParser::getInstance()->getItemInt("-iCapVerbosity");
    string snorm = CCommandLineParser::getInstance()->getItemstring("-sNorm");
    
	tagCaptureConfig stCaptureParam;
	stCaptureParam.strWinName = "ADAS_camera";
	stCaptureParam.iPipeline = 2;
	stCaptureParam.iWinPos[0] = 0;
	stCaptureParam.iWinPos[1] = 0;
	stCaptureParam.uiWinSize[0] = 800;
	stCaptureParam.uiWinSize[1] = 480;
	stCaptureParam.uiBufNum = NUM_CAPTURE_FRAME_BUFFER;
	stCaptureParam.uiBufSize[0] = 720;
	stCaptureParam.uiBufSize[1] = 240;
	stCaptureParam.uiPixelBytes = 2;
	stCaptureParam.uiFormat = 14;//SCREEN_FORMAT_UYVY
	stCaptureParam.pSignalCallback = &onCameraSignalCallback;
    stCaptureParam.pLayerReadyCallback= &onCameraLayerReadyCallback;
    stCaptureParam.pSetLayerReqCallback= &onSetLayerReqCallback;
    
	stCaptureParam.uiCheckSignal = 15;
    stCaptureParam.uiSkipFrames= uiSkipFrames;
    stCaptureParam.uiSkipFramesForSigDelay= (uiSigDelay==0)?60:uiSigDelay;//default delay is verified by system
    
	stCaptureParam.eDriverType = eQNX_J5;

	m_captureDriverCfg.device = 2;
	m_captureDriverCfg.csize[0] = 720;
	m_captureDriverCfg.csize[1] = 240;
	m_captureDriverCfg.cpos[0] = 0;
	m_captureDriverCfg.cpos[1] = 10;
	m_captureDriverCfg.source[0] = 2;//revert cam channel as customer request
	m_captureDriverCfg.source[1] = 0;
	m_captureDriverCfg.uiSrcNum = 2;
	m_captureDriverCfg.verbosity = iverbosity;
	m_captureDriverCfg.sfsize[0] = -1;
	m_captureDriverCfg.sfsize[1] = -1;
	m_captureDriverCfg.dfsize[0] = 720;
	m_captureDriverCfg.dfsize[1] = 240;
	m_captureDriverCfg.format = 14;//SCREEN_FORMAT_UYVY
	m_captureDriverCfg.pipeline = 1;
	//capConfig.norm = "NTSC_M_J";
	m_captureDriverCfg.source_type = 0;

    if(""!=snorm)
    {
        m_captureDriverCfg.norm = snorm;
        //printf("--->cap norm format is #%s#", m_captureDriverCfg.norm.c_str());
    }
    else
    {
        //printf("--->cap norm format is NULL");
    }
    
	if(!CCameraSysManager::getInstance()->initialize(CCameraSysManager::eType_Simple))
	{
		DBG_MSG(("CAdasCtrl adas CameraSys  initialize failed\n"));
		return FALSE;
	};

	//if( EOL::getInitCapture() )
	{
		CCameraSysManager::getInstance()->addCapture(stCaptureParam,&m_captureDriverCfg,NULL);
	}

	//CCameraSysManager::getInstance()->pause();
	tagGraphicsConfig tagGraphicsCfg = {(char*)"ADAS_graphic", 2,
												  {0,0},{800,480},2,&onGraphicLayerReadyCallback};

	CCameraSysManager::getInstance()->initGraphics(tagGraphicsCfg, CScaniaGraphicsImpl::getInstance());


	DBG_MSG(("CAdasCtrl adas_InitGraphicRes success\n"));

  return TRUE;
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, bAdasDestroyCameraSystem);
bool CAdasCtrl::bAdasDestroyCameraSystem()
{
    TRC_SCOPE(ADAS, CAdasCtrl, bAdasDestroyCameraSystem);
	//return TRUE;
	CCameraSysManager::getInstance()->resume();

	DBG_MSG(("CAdasCtrl::bAdasDestroyGraphic begin\n"));

	CCameraSysManager::getInstance()->unInitialize();

	DBG_MSG(("CAdasCtrl::bAdasDestroyGraphic end\n"));

	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CAdasCtrl, onGuideLineTimer);
void CAdasCtrl::onGuideLineTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
    TRC_SCOPE(ADAS, CAdasCtrl, onGuideLineTimer);
	DBG_MSG(("CAdasCtrl::onGuideLineTimer works!\n"));
	
	CCamera* pCamera = m_pCameraCtrl->getCamera(m_pCameraCtrl->getCurShowCameraPos());
	if( pCamera && pCamera->isInShow() && m_bShowGuideLine && (CCamera::eType_Reverse ==pCamera->getType()))
	{
		CScaniaGraphicsImpl::getInstance()->asynShowGuideLine(EOL::getReverseGuideLineIndex(pCamera->getPos()) );
	}
}





