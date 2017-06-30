#include "CCamera.hpp"
#include "CCameraSysManager.h"
#include "CAdasCtrl.hpp"
#include "CCanProcessor.hpp"
#include "../CEOL.hpp"
#include "CScaniaGraphicsImpl.hpp"
#include "CDiagnosticProcessor.hpp"
#include "CScaniaOnOffClient.hpp"
#include "CLayerManagerClient.hpp"
TRC_SCOPE_DEF(ADAS, CCamera, CCamera);
CCamera::CCamera(EPos ePos, EType eType)
: m_eAutoActiveType(eType_NULL)
, m_bSpeedHighSate(FALSE)
, m_eStatus(eStatus_Deactivated)
, m_ePos(ePos)
, m_eType(eType)
, m_bVsynValid(TRUE)
, m_bVsynSigIsReadyToChk(FALSE)
, m_eShowState(eShowState_Hide)
, m_bManualActivatedLastScreen(FALSE)
, m_bStartup(TRUE)
, m_eSpeedLastState(eSpeedLastState_0)
{
    TRC_SCOPE(ADAS, CCamera, CCamera);
	if(EOL::getCameraStartupTime(ePos)!= 0)
	{
		m_showTimer.setDelay(EOL::getCameraStartupTime(ePos));
		m_showTimer.setRepeatCount(1);
		m_showTimer.setCallBack(::makeFunctor(this, &CCamera::onShowTimer), NULL);
		//m_bStartup = TRUE;
		DBG_MSG(("CCamera startup timer is set!!  pos=%d,delay=%d\n", ePos, EOL::getCameraStartupTime(ePos)));
	}
    //m_KPIshowTimer.setDelay(500);//camera KPI 500ms
    //m_KPIshowTimer.setRepeatCount(1);
    //m_KPIshowTimer.setCallBack(::makeFunctor(this, &CCamera::OnKPIshowTimer), NULL);
}

//add timer out for fast switch out and swicth back
//capture thread will not send out state 1/3 for camera state is not push into que.
void CCamera::OnKPIshowTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
    m_bStartup = FALSE;
	SEND_BASEMESSAGE(eMsgType_ActiveKPICamera, eGetCameraState);
}

TRC_SCOPE_DEF(ADAS, CCamera, show);
void CCamera::show()
{
	TRC_SCOPE(ADAS, CCamera, show);
    static BOOLEAN FirstTimeLayerContronl = TRUE;
	EShowState eOldState = m_eShowState;
    //reset speed state on every active event
    m_bSpeedHighSate = FALSE;
    
    //keep last state  if alread activated
    if(!isInShow())
    {
    	m_eShowState = eShowState_onGoing;
        m_bStartup = TRUE;//send out state5 when start a camera anyway  ----fast switch??
    }
	if( eOldState == eShowState_Hide )
	{
        DBG_MSG(("CCamera::show() pos%d\n",m_ePos));
		CDiagnosticProcessor::getInstance()->onShowCamera(m_ePos);
	}

#if 1
    //set layer waitout waiting for driver will see unexpected frame
    //this frame is not post to window but still we  see on screen!!
    if(FirstTimeLayerContronl)
    {
        FirstTimeLayerContronl= FALSE;
        //printf("@@@@@@@@@@@@@CCamera first layer request @@@@@@@@@@@@@\n");
        DBG_MSG(("@@@@@@@@@@@@@CCamera first layer request @@@@@@@@@@@@@\n"));
        CLayerManagerClient::getInstance()->RequestShowADASLayer();
    }
#endif

}

TRC_SCOPE_DEF(ADAS, CCamera, isStandbyWakeUp);
BOOLEAN    CCamera::isStandbyWakeUp()
{ 
    TRC_SCOPE(ADAS, CCamera, isStandbyWakeUp);
    BOOLEAN bHKWakeup = FALSE;
    if(Env::isScaniaTarget())
    {
        bHKWakeup =  isManualActivated();
    }
    DBG_MSG(("Ver2:CCamera::isStandbyWakeUp =isCANActivated %d -isAutoActivated %d  -bHKWakeup %d pos%d\n", isCANActivated(),isAutoActivated(),bHKWakeup,EOL::getCameraStartupTime(m_ePos)));
    //front camera is actived by "speed", so speed active should be considerate in this case
    return ((isCANActivated()&&isAutoActivated())||bHKWakeup);
}

TRC_SCOPE_DEF(ADAS, CCamera, stopShowTimer);
void CCamera::stopShowTimer()
{
    TRC_SCOPE(ADAS, CCamera, stopShowTimer);
	if(EOL::getCameraStartupTime(m_ePos)!= 0)
	{
    	m_showTimer.stop();  	
    	DBG_MSG(("CCamera::stopShowTimer =%d\n", EOL::getCameraStartupTime(m_ePos)));
	}
    m_bStartup = FALSE;
}

TRC_SCOPE_DEF(ADAS, CCamera, hide);
void CCamera::hide()
{
	TRC_SCOPE(ADAS, CCamera, hide);
	DBG_MSG(("CCamera::hide()- %d\n",m_ePos));
	EShowState eOldState = m_eShowState;
	m_eShowState = eShowState_Hide;
    m_bVsynSigIsReadyToChk = FALSE;
	if( eOldState != eShowState_Hide )
	{
		CDiagnosticProcessor::getInstance()->onHideCamera(m_ePos);
	}


}
TRC_SCOPE_DEF(ADAS, CCamera, getExternalStatus);
CCamera::EExternalStatus CCamera::getExternalStatus() const
{
    TRC_SCOPE(ADAS, CCamera, getExternalStatus);
	DBG_MSG(("CCamera::getExternalStatus m_eStatus=%x,m_bVsynValid=%x, bStartup=%d\n",m_eStatus,m_bVsynValid,m_bStartup));
	if( m_eStatus == CCamera::eStatus_Deactivated )
	{
		return eEStatus_Deactivated;

	}
	else
	{
		//DBG_MSG(("getExternalStatus CONNECT %s\n", m_bConnected? "true":"false"));
		if(m_bStartup == TRUE)
		{
            return eEStatus_ActivationOngoing;
        }
				
		if( m_bVsynValid == FALSE )
		{
			return eEStatus_NotConnected;
		}
		else
		{
			return eEStatus_Activated;
		}
	}

}

void CCamera::setSignalValid(BOOLEAN bValid)
{
	if( m_bVsynValid == FALSE && bValid == TRUE )
	{
		CDiagnosticProcessor::getInstance()->onVsyncValid(m_ePos);
	}
	else if( m_bVsynValid == TRUE && bValid == FALSE )
	{
		CDiagnosticProcessor::getInstance()->onVsyncInvalid(m_ePos);
	}

	m_bVsynValid = bValid;
}


TRC_SCOPE_DEF(ADAS, CCamera, onShowTimer);
void CCamera::onShowTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
	//m_showTimer.stop();
	m_bStartup = FALSE; 
	CScaniaGraphicsImpl::getInstance()->asynshowStartUpImage(m_ePos,FALSE);
    if(m_bVsynSigIsReadyToChk)
    {
        //SEND_BASEMESSAGE(eMsgType_Timer,eGetCameraState);
    }
    else
    {
        TRC_SCOPE(ADAS, CCamera, onShowTimer);
        DBG_MSG(("onShowTimer %d timerout too fast, camera signal is not finished detection, first state will send out after detection complete\n",m_ePos+1));
        //normal layer reprt condintion will not meet as first request to send state is alredy passed
        //use case for fast switch also not working for normal layer report
        //when timer is too short, setup KPI timer to send out  state
        //startKPIshowTimer();

        //send out a good camera state first to sync HMI  text lable
        //later driver will report a real state for differet dealy of camera signal detection
        //!!! send a fake state for 1 diagnosis need correct camera state but delay is long 2 HMI need fast sync text lable but camers state is not ready 
        m_bVsynValid = TRUE;
        //remove this state for "ongoing" popup , control the delay by parameter uiSigDelay

    }
}

BOOLEAN	CCamera::isInReverse() const
{
    return CCanProcessor::getInstance()->isReverseEngaged();
}
//four state variant !isInReverse  !=  isNotInReverse
BOOLEAN	CCamera::isNotInReverse() const
{
    return CCanProcessor::getInstance()->isDrivingForward();
}
BOOLEAN	CCamera::isParkBrakeSwitchNotSet() const
{
	return CCanProcessor::getInstance()->isParkBrakeSwitchNotSet();
}

BOOLEAN	CCamera::isPinOnOffRequestShowCamera(EPos epos) const
{
	return CScaniaOnOffClient::getInstance()->isScaniaPinShowCam(epos);
}
TRC_SCOPE_DEF(ADAS, CCamera, startShowTimer);
void CCamera::startShowTimer()
{
    TRC_SCOPE(ADAS, CCamera, startShowTimer);
	//m_showTimer.stop();
	m_showTimer.start();
	m_bStartup = TRUE;
	DBG_MSG(("CCamera::startShowTimer m_bStartup=%d\n", m_bStartup));

}

//---------------------------------------------------------
BOOLEAN CReverseCamera::m_bEnableAutoHideTimer = TRUE;
CTimer* CReverseCamera::m_pDeactivatedTimer= NULL;
BOOLEAN CReverseCamera::m_bDirectlyCancelRearCam[CCamera::eCameraNum] = {FALSE,FALSE};

TRC_SCOPE_DEF(ADAS, CReverseCamera, onExitRvsTimer);
void CReverseCamera::onExitRvsTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
    TRC_SCOPE(ADAS, CReverseCamera, onExitRvsTimer);
    if(!m_bEnableAutoHideTimer) return;
	DBG_MSG(("CReverseCamera timer for Function_ReverseCameraActiveTimer works!\n"));
    m_bLsatIsReverseState = FALSE;
	SEND_BASEMESSAGE(eMsgType_Others, eOtherEvent_ReverseCam1TimerDeactivate+getPos() );

}

TRC_SCOPE_DEF(ADAS, CReverseCamera, CReverseCamera);
CReverseCamera::CReverseCamera(EPos ePos)
: CCamera(ePos,eType_Reverse)
, m_uiDeactivatedTime(0)
, m_bLsatIsReverseState(FALSE)
{
    TRC_SCOPE(ADAS, CReverseCamera, CReverseCamera);
	m_uiDeactivatedTime = EOL::getReverseActiveTime();
	m_pDeactivatedTimer = new CTimer();
	m_pDeactivatedTimer->setDelay(m_uiDeactivatedTime*1000);
	m_pDeactivatedTimer->setRepeatCount(1);
	m_pDeactivatedTimer->setCallBack(::makeFunctor(this,&CReverseCamera::onExitRvsTimer),NULL);
    for(int i=0;i<CCamera::eCameraNum;i++)
    {
        m_bDirectlyCancelRearCam[i]=FALSE;
    }
	DBG_MSG(("generate reverse timer = %u\n", (UInt32)m_pDeactivatedTimer ));
}

TRC_SCOPE_DEF(ADAS, CReverseCamera, deCReverseCamera);
CReverseCamera::~CReverseCamera()
{
    TRC_SCOPE(ADAS, CReverseCamera, deCReverseCamera);
	if( m_pDeactivatedTimer )
	{
		DBG_MSG(("CReverseCamera::~CReverseCamera()\n"));
		//m_pDeactivatedTimer->setRepeatCount(1);
		//m_pDeactivatedTimer->stop();
		delete m_pDeactivatedTimer;
		m_pDeactivatedTimer = NULL;

		DBG_MSG(("CReverseCamera::~CReverseCamera() end\n"));
	}
}

// speed normal /high /too high
//consider auto event speed! and update speed state for HMI at any time!
//for reverse cam, only speed too high is applied
TRC_SCOPE_DEF(ADAS, CReverseCamera, canAutoActivated);
BOOLEAN CReverseCamera::canAutoActivated()
{
    TRC_SCOPE(ADAS, CReverseCamera, canAutoActivated);
	setAutoActivatedType_NULL();
	if(isEitherHardPinActived())
	{
    	//stopDeactivateTimer(); if camera is normally deactive and a hardpin actived  
        //manully active state should cancel in new request 
        /*no need to reset Manual*/
        //ResetLastManualActivated();
        m_bLsatIsReverseState = FALSE;
        if(isPinOnOffRequestShowCamera(getPos())) 
        {
            DBG_MSG(("CReverseCamera::canAutoActivated() success @ PIN request\n"));
            m_bSpeedHighSate = FALSE;
            setAutoActivatedType_HardPin();
            return TRUE;
        }
        else
        {
            //just keep run cancel rear camera logic state process           
            DBG_MSG(("CReverseCamera::canAutoActivated() found another PIN request\n"));
        }             
	}

	if(isCANOnOffRequestShowCamera())
	{
    	stopDeactivateTimer();	   
        DBG_MSG(("CReverseCamera::canAutoActivated() success @ CAN request\n"));
        //setAutoActivatedType_CAN();
        m_eAutoActiveType = eType_CAN_REQUEST;
        m_bSpeedHighSate = FALSE;
		return TRUE;
	}

    //check with front camera, only one camera shall active
    if((CCamera::eCameraNum > getPos())&& m_bDirectlyCancelRearCam[getPos()])
    {
        m_bDirectlyCancelRearCam[getPos()] = FALSE;
        m_bLsatIsReverseState = FALSE;
        DBG_MSG(("CReverseCamera::canAutoActivated() failed @  front camera auto on rear camera close immediately\n"));
        setAutoActivatedType_NULL();
		/*no need to reset Manual*/
        //ResetLastManualActivated();//tbd
        return FALSE;
    }

	if(isInReverse()) // Now reverse priority highest
	{
        //manully active state should cancel in new request
        //ResetLastManualActivated();
        vEnableAutoHideTimer();
        stopDeactivateTimer();     
        m_bLsatIsReverseState = TRUE;
        DBG_MSG(("CReverseCamera::canAutoActivated() success @ isInReverse\n"));
        m_eAutoActiveType = eType_CAN_REVERSE;
        m_bSpeedHighSate = FALSE;
	}
    else 
    {
		if(isLastManualActivated())
		{
            if( isSpeedTooHigh() )
            {
            	ResetLastManualActivated();
            }			
			DBG_MSG(("CReverseCamera::canAutoActivated() failed @ last manually activat\n"));
			m_bLsatIsReverseState = FALSE;
			setAutoActivatedType_NULL();
			return FALSE;
		}
		
        if(m_bLsatIsReverseState)
    	{
            //auto hide timer is disabled = manually cancel rear camera, close rear camera immediately
            //if reverse is canceled ,start timer anyway
            //last reverse state should be updated in timer out process too
        	if ( m_bLsatIsReverseState && bIsAutoHideTimerEnabled() && isAutoActivated() && m_uiDeactivatedTime != 0 && (m_pDeactivatedTimer != NULL && !m_pDeactivatedTimer->isRunning() ) )
        	{
        		DBG_MSG(("CReverseCamera::canAutoActivated()check startDeactivateTimer()\n"));
        		startDeactivateTimer();
				//keep active state until timer out
				m_eAutoActiveType = eType_CAN_SPEED_DEA_REAR;

        	}
            else if (m_bLsatIsReverseState && (m_uiDeactivatedTime==0)&& bIsAutoHideTimerEnabled())
            {
                m_bLsatIsReverseState = FALSE;
                DBG_MSG(("CReverseCamera::canAutoActivated() failed @ timer out =0  rear gear inactive\n"));
                setAutoActivatedType_NULL();
                //ResetLastManualActivated();//tbd
                return FALSE;
            }
            //cancel reverse gear but speed low
            DBG_MSG(("CReverseCamera::canAutoActivated() success @  SpeednotHigh & rear gear keeplast state \n"));
            if( !isSpeedTooHigh() )
            {
                //NOT UPDATE FOR OVERRIDE USE CASE
                //for manaul active, this state not updated
				//speed active rear camera will be change to manually active state so be able to overridable
                if(m_bLsatIsReverseState)
                {
                    m_eAutoActiveType = eType_CAN_SPEED_DEA_REAR;
                }
            }
            //cancel reverse gear but speed high
            else
            {
                stopDeactivateTimer();
                m_bLsatIsReverseState = FALSE;
                DBG_MSG(("CReverseCamera::canAutoActivated() failed @  Speedhigh & rear gear inactive1\n"));
                setAutoActivatedType_NULL();
                //ResetLastManualActivated();
            }
    	}
		//not rear gear state but high speed deactive use case is covered in CanManuallyActive process
		//update high speed state for HMI special logic - get camera state without camera reqeust
    	else if(isSpeedTooHigh())
    	{
           ResetLastManualActivated(); 
           DBG_MSG(("CReverseCameraMT::canAutoActivated() failed @  SpeedHigh & rear gear inactive2@ pos%d\n",getPos()));
    	}
        else
        {
           // speed updated can trigger this condition  
           DBG_MSG(("CReverseCamera::canAutoActivated() fail @  & last rear gear state or manaully actived = inactive\n"));
           
        }
    }
	
//sync form MAN - speed auto active rear camera- set it to manually active state
//20160713 HMI last screen depends on camera active method - can not set to manually active for speed active camera mode
	if(eType_NULL!=getAutoActiveType())
     //&&(eType_CAN_SPEED_DEA_REAR!=getAutoActiveType()))
	{
		return TRUE;
	}
	else
	{
		DBG_MSG(("exit CReverseCamera::canAutoActivated() fail @ all@ pos%d\n",getPos()));
		return FALSE;
	}
}


void CReverseCamera::vSetDirectlyCancelRearCam()   
{
    for(int i=0;i<CCamera::eCameraNum;i++)
    {
        m_bDirectlyCancelRearCam[i]=TRUE;
    }
}

void CReverseCamera::vCancelDirectlyCancelRearCam()   
{
    for(int i=0;i<CCamera::eCameraNum;i++)
    {
        m_bDirectlyCancelRearCam[i]=FALSE;
    }
}

BOOLEAN CReverseCamera::bDirectlyCancelledRearCam()   
{
    for(int i=0;i<CCamera::eCameraNum;i++)
    {
        //only check the one have config as rear cam
        if ((m_bDirectlyCancelRearCam[i])&&(EOL::getCameraType((CCamera::EPos)i)==CCamera::eType_Reverse))
            return TRUE;
    }
    return FALSE;
}

BOOLEAN CReverseCamera::canManualActivated()
{
    //HMI will also block manually request on hardpin actived case for non-overidable state
    //a special case for camera is standby override camera screen
    if(eStatus_ManualActivated == getStatus()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
    {
        return FALSE;
    }
	if( isEitherHardPinActived())
		return FALSE;

	if( isSpeedTooHigh() )
	{
        ResetLastManualActivated();
		return FALSE;
	}

	if( isInReverse() ) // Now reverse priority highest
	{
		//overridable case, should cancel rear gear
		//return FALSE;
	}
    setLastManualActivated();
	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CReverseCamera, canManualDeactivated);
BOOLEAN	CReverseCamera::canManualDeactivated()
{
    TRC_SCOPE(ADAS, CReverseCamera, canManualDeactivated);
	//HMI will also block manually request on hardpin actived case for non-overidable state
	if( isAutoActivated()&& isHardPinActivated())
	{
		DBG_MSG(("exit CReverseCamera::canManualDeactivated() fail @isHardPinActivated \n"));
		return FALSE;
	}
	//on showoff cmd , overridable case: expcept hardpin active 
#if 0
	if( isInReverse() )
	{
		return FALSE;
	}
#endif    
    DBG_MSG(("exit CReverseCamera::canManualDeactivated() success @ all@ pos%d\n",getPos()));
	ResetLastManualActivated();
	return TRUE;
}

void CReverseCamera::deactivate()
{
	if( m_pDeactivatedTimer )
	{
		m_pDeactivatedTimer->stop();
	}

	CCamera::SetStateDeactivate();
}

BOOLEAN	CReverseCamera::isSpeedNormal() const
{
	return FALSE;
}

BOOLEAN	CReverseCamera::isSpeedHigh() const
{
	return FALSE;
}
BOOLEAN	CReverseCamera::isCANOnOffRequestShowCamera() const
{
	return CCanProcessor::getInstance()->isCANOnOffShowRearCam();
}

TRC_SCOPE_DEF(ADAS, CReverseCamera, isSpeedTooHigh);
BOOLEAN	CReverseCamera::isSpeedTooHigh()
{
    TRC_SCOPE(ADAS, CReverseCamera, isSpeedTooHigh);
	Float32 fSpeed = CCanProcessor::getInstance()->getSpeed();
	if(( fSpeed > (Float32)((EOL::getRevGelDeactSpeed(getPos()) + EOL::getRevGelSpeedHysteresis(getPos() ) )))
     &&(CCanProcessor::getInstance()->isDrivingForward()))
	{
		DBG_MSG(("CReverseCamera::isSpeedTooHigh : fSpeed = %f5.2\n", fSpeed));
        m_bSpeedHighSate = TRUE;
		return TRUE;
	}
    m_bSpeedHighSate = FALSE;
	return FALSE;
}

BOOLEAN	CReverseCamera::isNeedTimerDeactivated() const
{
	//return ( CAdasCtrl::getInstance()->isTimerDeactivate( getPos() ) );
	return TRUE;
}

void CReverseCamera::startDeactivateTimer()
{
	if( m_pDeactivatedTimer )
	{
		m_pDeactivatedTimer->start();
	}

	//onExitRvsTimer(this);
}

//
void CReverseCamera::stopDeactivateTimer()
{
    if (m_pDeactivatedTimer != NULL && m_pDeactivatedTimer->isRunning())
    {
        m_pDeactivatedTimer->stop();
    }
}
//add for SCANIA new reuqest:hard pin active will cancel rear gear state, and back to HMI when exit
BOOLEAN	CReverseCamera::isEitherHardPinActived()
{
    return ((isPinOnOffRequestShowCamera(eCamera1))||(isPinOnOffRequestShowCamera(eCamera2)));
}

BOOLEAN CReverseCamera::isInReverse()
{
    return CCanProcessor::getInstance()->isInReverse();
}
BOOLEAN CReverseCamera::isNotInReverse()
{
    return CCanProcessor::getInstance()->isNotInReverse();
}
//---------------------------------------------------------
CFrontCamera::CFrontCamera(EPos ePos)
: CCamera(ePos,eType_Front)
{

}

CFrontCamera::~CFrontCamera()
{

}

TRC_SCOPE_DEF(ADAS, CFrontCamera, canAutoActivated);
BOOLEAN CFrontCamera::canAutoActivated()
{
    TRC_SCOPE(ADAS, CFrontCamera, canAutoActivated);
    
	if(isPinOnOffRequestShowCamera(getPos()))
	{
        DBG_MSG(("CFrontCamera::canAutoActivated() success @ PIN request\n"));
        m_bSpeedHighSate = FALSE;
        setAutoActivatedType_HardPin();
        return TRUE;
	}

	if(isCANOnOffRequestShowCamera())
	{
        DBG_MSG(("CFrontCamera::canAutoActivated() success @ CAN request\n"));
        m_bSpeedHighSate = FALSE;
        m_eAutoActiveType = eType_CAN_REQUEST;
        return TRUE;
	}

  //to support tester use case set park breake even speed is high
    if(isNotInReverse())
    {
    	if(!isActivated())
    	{
            if(isSpeedNormal( ))
            {
                m_bSpeedHighSate = FALSE;
            }
            else
            {
                m_bSpeedHighSate = TRUE;
            }
            
        }
        else
        {
            if(!isSpeedTooHigh( ))
            {
                m_bSpeedHighSate = FALSE;
            }
            else
            {
                m_bSpeedHighSate = TRUE;
            }
        }
    }
    else
    {
        m_bSpeedHighSate = FALSE;
    }

    
   if((isInReverse())||(!isParkBrakeSwitchNotSet()))
   {
        DBG_MSG(("CFrontCamera::canAutoActivated() fail @ isInReverse())||(!isParkBrakeSwitchNotSet())\n"));
        setAutoActivatedType_NULL();
        return FALSE;
	}
	if( isSpeedTooHigh() )
	{
        DBG_MSG(("CFrontCamera::canAutoActivated() fail @ SpeedTooHigh\n"));
        setAutoActivatedType_NULL();
        ResetLastManualActivated();
        return FALSE;
	}
    //font camera active failed by speed use case if not possible cause speed is not possble to jump to high
	if( isNotInReverse() && isParkBrakeSwitchNotSet( ) && isSpeedNormal( )&&(!isActivated()))
	{
		DBG_MSG(("CFrontCamera::canAutoActivated success @  isNotInReverse() && isParkBrakeSwitchNotSet( ) && isSpeedNormal()&&(!isActivated())\n"));
        m_eAutoActiveType = eType_CAN_SPEED;
        return TRUE;
	}
	else if( isNotInReverse() && isParkBrakeSwitchNotSet( ) && (!isSpeedTooHigh( ))&& isActivated())
	{
		DBG_MSG(("CFrontCamera::canAutoActivated success @  isNotInReverse() && isParkBrakeSwitchNotSet( ) && (!isSpeedTooHigh( ))&&(isActivated())\n"));
        m_eAutoActiveType = eType_CAN_SPEED;
        return TRUE;
	}
    DBG_MSG(("exit CFrontCamera::canAutoActivated() fail @ all\n"));
    setAutoActivatedType_NULL();
    return FALSE;
}

//it is not possible to cancel autoactive state until speed too high
//when auto active cancled it is not possible to active before speed lower than high speed limit
BOOLEAN CFrontCamera::canManualActivated()
{
    if(eStatus_ManualActivated == getStatus()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
    {
        return FALSE;
    }
	if( isAutoActivated() )
		return FALSE;

	if( !isSpeedNormal() )
	{
        m_bSpeedHighSate = TRUE;
        ResetLastManualActivated();
        return FALSE;
    }	
    else
    {
        m_bSpeedHighSate = FALSE;
        setLastManualActivated();
        return TRUE;
    }
}

TRC_SCOPE_DEF(ADAS, CFrontCamera, canManualDeactivated);
BOOLEAN	CFrontCamera::canManualDeactivated()
{
    TRC_SCOPE(ADAS, CFrontCamera, canManualDeactivated);
	if( isAutoActivated())
	{
        DBG_MSG(("CFrontCamera::canManualDeactivated() fail @ already AutoActivated\n"));
		return FALSE;
	}
    DBG_MSG(("CFrontCamera::canManualDeactivated() success\n"));
	ResetLastManualActivated();
	return TRUE;
}

BOOLEAN	CFrontCamera::isSpeedNormal() const
{
	Float32 fSpeed = CCanProcessor::getInstance()->getSpeed();
	if( fSpeed <= (Float32 )EOL::getFrontUpperSpeedLimit() )
		return TRUE;

	return FALSE;
}

BOOLEAN	CFrontCamera::isSpeedHigh() const
{
	return FALSE;
}

BOOLEAN	CFrontCamera::isSpeedTooHigh()
{
	Float32 fSpeed = CCanProcessor::getInstance()->getSpeed();
	if( fSpeed > (Float32 )(( EOL::getFrontUpperSpeedLimit() + EOL::getFrontUpperSpeedHysteresis() )) )
	{
        //m_bSpeedHighSate = TRUE;
        return TRUE;
    }
    //m_bSpeedHighSate = FALSE;
	return FALSE;
}
BOOLEAN	CFrontCamera::isCANOnOffRequestShowCamera() const
{
	return CCanProcessor::getInstance()->isCANOnOffShowFrntCam();
}

//---------------------------------------------------------
CGeneralCamera::CGeneralCamera(EPos ePos)
: CCamera(ePos, eType_General)
{

}

CGeneralCamera::~CGeneralCamera()
{

}

TRC_SCOPE_DEF(ADAS, CGeneralCamera, canAutoActivated);
BOOLEAN CGeneralCamera::canAutoActivated()
{
    TRC_SCOPE(ADAS, CGeneralCamera, canAutoActivated);
	DBG_MSG(("enter CGeneralCamera::canAutoActivated()\n"));
    //remove speed too high state for event auto event may have high priority than speed
   //every auto event will set state as deactive as default state
   m_eAutoActiveType = eType_NULL;
   if(isPinOnOffRequestShowCamera(getPos()))
	{
        DBG_MSG(("CGeneralCamera::canAutoActivated() success @ PIN request\n"));
        setAutoActivatedType_HardPin();
        m_bSpeedHighSate = FALSE;
	//update last speed state before return
	if(isSpeedNormal()) m_eSpeedLastState = eSpeedLastState_Normal;	
	if(isSpeedTooHigh()) m_eSpeedLastState = eSpeedLastState_TooHigh;
        return TRUE;
	}
    // check CAN active conditon -- shall be combined by speed
    //last actived type!!! to suppoert HMI show override screen!!  
	if(isCANOnOffRequestShowCamera())
	{
        DBG_MSG(("CGeneralCamera::canAutoActivated() success @ CAN request\n"));
        m_eAutoActiveType = eType_CAN_REQUEST;
        //m_bSpeedHighSate = FALSE;
        //return TRUE;
	}   

	DBG_MSG(("CGeneralCamera check WorkLightCondition \n"));
	if(EOL::isGelActivateWorkLightOn(getPos()) ) DBG_MSG(("worklight is On \n"));
	if( CCanProcessor::getInstance()->IsWorkLightToggleOn()) DBG_MSG(("toggleSwitch is on\n"));
	BOOLEAN bWorkLightCondition = ( EOL::isGelActivateWorkLightOn(getPos()) &&
			(CCanProcessor::getInstance()->IsWorkLightToggleOn()) ) ;

	if( bWorkLightCondition )
	{
		DBG_MSG(("CGeneralCamera::canAutoActivated() success @ WorkLightCondition\n"));
        m_eAutoActiveType = eType_CAN_WORKLIGHT;
        //m_bSpeedHighSate = FALSE;
        //return TRUE;
	}
//new spec : rmove wheelpos EOL
   
	if( EOL::isGelActivateDirIndicatorOn(getPos()) )
	{
		//if( EOL::getWheelPos() == EOL::eLHD )
		//{
			if ( CCanProcessor::getInstance()->isIndicatorRightIntendedOn() 
				&& (!CCanProcessor::getInstance()->isIndicatorLeftIntendedOn()) )
				{
                    DBG_MSG(("CGeneralCamera::canAutoActivated() success @ RightIntendedOn\n"));
                    m_eAutoActiveType = eType_CAN_DIRECTION;
                    //m_bSpeedHighSate = FALSE;
                    //return TRUE;
            }
		//}
		//else if( EOL::getWheelPos() == EOL::eRHD )
		//{
			else if ( CCanProcessor::getInstance()->isIndicatorLeftIntendedOn() 
				&& (!CCanProcessor::getInstance()->isIndicatorRightIntendedOn()) )
			{
                DBG_MSG(("CGeneralCamera::canAutoActivated() success @ LeftIntendedOn\n"));
                m_eAutoActiveType = eType_CAN_DIRECTION;
                //m_bSpeedHighSate = FALSE;
                //return TRUE;
            }
			else
			{
				DBG_MSG(("CGeneralCamera check DirIndicator: disabled! \n"));
			}
		//}
	}
    //for normal speed update , acitved by manually active
    //update speed for HMI will check speed but not send camera request
    //clear auto active state if driving forward and speed state is high
    if(!isInReverse())
	{
        //auto deactive use case: munually actived -> auto deactive 
        if(isSpeedTooHigh())
        {
    		DBG_MSG(("CGeneralCamera::canAutoActivated() fail @ isInReverse && bSpeedTooHigh\n"));
            m_bSpeedHighSate = TRUE;
            m_eAutoActiveType = eType_NULL;
            ResetLastManualActivated();
			m_eSpeedLastState = eSpeedLastState_TooHigh;//update state only before return process
            return FALSE;
        }
        //update speed state for HMI not send camera  event but only getState
        if(getStatus() == eStatus_Deactivated)
        {
            //if speed is not too high, when reqeust on this state, it shall be activated or not
            //need to identify it is back from high speed or not reach high speed yet
		    if(isSpeedNormal())
			{
				m_bSpeedHighSate = FALSE;
			}
			else
			{
			   //active failed use case: munually active failed for speed restriction 
			   	if(m_eSpeedLastState == eSpeedLastState_Normal)
				{
					DBG_MSG(("CGeneralCamera::canAutoActivated() success for speed is high but rise from normal \n"));
					m_bSpeedHighSate = FALSE;
				}
				else if(m_eSpeedLastState == eSpeedLastState_TooHigh)
				{
					DBG_MSG(("CGeneralCamera::canAutoActivated() fail for speed ishigh but back from too high \n"));
				    m_bSpeedHighSate = TRUE;
	                m_eAutoActiveType = eType_NULL;
	                ResetLastManualActivated();				
	                return FALSE;
				}

			}		           
        }  
		
	}
    else
    {
        m_bSpeedHighSate = FALSE;
    }
	//update last speed state before return
	if(isSpeedNormal()) m_eSpeedLastState = eSpeedLastState_Normal;	
	if(isSpeedTooHigh()) m_eSpeedLastState = eSpeedLastState_TooHigh;

    if(m_eAutoActiveType != eType_NULL)
    {
         DBG_MSG(("exit CGeneralCamera::canAutoActivated() success @ all\n"));
         return TRUE;
    }
    else
    {
        DBG_MSG(("exit CGeneralCamera::canAutoActivated() failed @ all\n"));
        return FALSE;
    }
}

//HMI will not manully send request if last state is speed deactive camera
TRC_SCOPE_DEF(ADAS, CGeneralCamera, canManualActivated);
BOOLEAN CGeneralCamera::canManualActivated()
{
    TRC_SCOPE(ADAS, CGeneralCamera, canManualActivated);
    if(eStatus_ManualActivated == getStatus()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
    {
        return FALSE;
    }
    //CR46 - CAN on off is not overridable , worklight and direction is overidable
    //override will cancel the autoactivitate state?
	//if( isAutoActivated())
	//	return FALSE;
	//HMI will also block manually request on hardpin actived case for non-overidable state
	if(( isAutoActivated()&& isHardPinActivated())
		||isCANOnOffRequestShowCamera())
	{
		DBG_MSG(("exit CGeneralCamera::canManualActivated() fail @Hard Pin/CAN command Activated \n"));
		return FALSE;
	}
	else if(isAutoActivated()&& isWorkLgtDirtIndiActivated())
	{
		DBG_MSG(("exit CGeneralCamera::canManualActivated() - override general camera on worklight/dirIndicator!\n"));
		CCanProcessor::getInstance()->vDisableWorkLightSwitch();
		CCanProcessor::getInstance()->vDisableIndicatorLeft();
		CCanProcessor::getInstance()->vDisableIndicatorRight();
		tagSwitchParams* pSwitchParams;// fake input 
		CAdasCtrl::getInstance()->onAutoUpdateState(pSwitchParams);//triiger CAN state to updated	
	}


	if( (getStatus() == eStatus_Deactivated) && isSpeedHigh() )
	{
        //use case for active failed
        m_bSpeedHighSate = TRUE;
		return FALSE;
	}
    
	if( isSpeedTooHigh() && !isInReverse() )
	{
        m_bSpeedHighSate = TRUE;
        ResetLastManualActivated();
		return FALSE;
	}
    m_bSpeedHighSate = FALSE;
    setLastManualActivated();
    

	return TRUE;
}

TRC_SCOPE_DEF(ADAS, CGeneralCamera, canManualDeactivated);
BOOLEAN	CGeneralCamera::canManualDeactivated()
{
    TRC_SCOPE(ADAS, CGeneralCamera, canManualDeactivated);
	if( isAutoActivated()&& isHardPinActivated())
	{
		DBG_MSG(("exit CGeneralCamera::canManualDeactivated() fail @isHardPinActivated \n"));
		return FALSE;
	}
	else if(isAutoActivated()&& isWorkLgtDirtIndiActivated())
	{
		DBG_MSG(("exit CGeneralCamera::canManualDeactivated() - override general camera on worklight/dirIndicator!\n"));
		CCanProcessor::getInstance()->vDisableWorkLightSwitch();
		CCanProcessor::getInstance()->vDisableIndicatorLeft();
		CCanProcessor::getInstance()->vDisableIndicatorRight();
		tagSwitchParams* pSwitchParams;// fake input 
		CAdasCtrl::getInstance()->onAutoUpdateState(pSwitchParams);//triiger CAN state to updated
	}
	DBG_MSG(("exit CGeneralCamera::canManualDeactivated() success \n"));
	ResetLastManualActivated();
	return TRUE;
}

BOOLEAN	CGeneralCamera::isSpeedNormal() const
{
	Float32 fSpeed = CCanProcessor::getInstance()->getSpeed();
	if( fSpeed <= (Float32 )EOL::getRevGelDeactSpeed(getPos()) )
		return TRUE;

	return FALSE;
}

BOOLEAN	CGeneralCamera::isSpeedHigh() const
{
	Float32 fSpeed = CCanProcessor::getInstance()->getSpeed();
	if( fSpeed > (Float32 )EOL::getRevGelDeactSpeed( getPos() ) )
		return TRUE;

	return FALSE;
}

BOOLEAN	CGeneralCamera::isSpeedTooHigh()
{
	Float32 fSpeed = CCanProcessor::getInstance()->getSpeed();
	if( fSpeed > (Float32 )( EOL::getRevGelDeactSpeed(getPos()) + EOL::getRevGelSpeedHysteresis(getPos() ) ) )
	{
        //m_bSpeedHighSate = TRUE;
        return TRUE;
    }
    //m_bSpeedHighSate = FALSE;
	return FALSE;
}
//todo: not support camera3 and camera4
BOOLEAN	CGeneralCamera::isCANOnOffRequestShowCamera() const
{
	return (((CCanProcessor::getInstance()->isCANOnOffShowGenCam1())&&(CCamera::eCamera1 == getPos()))
         ||((CCanProcessor::getInstance()->isCANOnOffShowGenCam2())&&(CCamera::eCamera2 == getPos())));
}

BOOLEAN	CGeneralCamera::isCANOnOffShowGenCamera1() const
{
	return CCanProcessor::getInstance()->isCANOnOffShowGenCam1();
}

BOOLEAN	CGeneralCamera::isCANOnOffShowGenCamera2() const
{
	return CCanProcessor::getInstance()->isCANOnOffShowGenCam2();
}
BOOLEAN	CGeneralCamera::isCANOnOffShowGenCamera3() const
{
	return CCanProcessor::getInstance()->isCANOnOffShowGenCam3();
}
BOOLEAN	CGeneralCamera::isCANOnOffShowGenCamera4() const
{
	return CCanProcessor::getInstance()->isCANOnOffShowGenCam4();
}

