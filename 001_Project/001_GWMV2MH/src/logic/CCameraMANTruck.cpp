#include "CCamera.hpp"
#include "CCameraMANTruck.hpp"
#include "CCameraSysManager.h"
#include "CAdasCtrl.hpp"
#include "CCanProcessor.hpp"
#include "../CEOL.hpp"
#include "CScaniaGraphicsImpl.hpp"
#include "CDiagnosticProcessor.hpp"
#include "CScaniaOnOffClient.hpp"

//hardpin has higher priority
BOOLEAN      CReverseCameraMT::m_bIsSpeedRestrictValid=FALSE;
BOOLEAN      CReverseCameraMT::m_bDirectlyCancelRearCam[CCamera::eCameraNum] = {FALSE,FALSE};

TRC_SCOPE_DEF(ADAS, CReverseCameraMT, CReverseCameraMT);
CReverseCameraMT::CReverseCameraMT(EPos ePos)
: CCamera(ePos, CCamera::eType_Reverse)
, m_bLsatIsReverseState(FALSE)
{
    TRC_SCOPE(ADAS, CReverseCameraMT, CReverseCameraMT);
    DBG_MSG(("*********CReverseCameraMT created on pos %d!*********\n",ePos));
}
CReverseCameraMT::~CReverseCameraMT()
{

}

void CReverseCameraMT::vSetDirectlyCancelRearCam()   
{
    for(int i=0;i<CCamera::eCameraNum;i++)
    {
        m_bDirectlyCancelRearCam[i]=TRUE;
    }
}

void CReverseCameraMT::vCancelDirectlyCancelRearCam()   
{
    for(int i=0;i<CCamera::eCameraNum;i++)
    {
        m_bDirectlyCancelRearCam[i]=FALSE;
    }
}
BOOLEAN CReverseCameraMT::bDirectlyCancelledRearCam()   
{
    for(int i=0;i<CCamera::eCameraNum;i++)
    {
        if (m_bDirectlyCancelRearCam[i]==TRUE)
            return TRUE;
    }
    return FALSE;
}
//hard pin has higher priority
#if 0
for MAN system, hardpin and rear gear event will not coming up within one target
Use case Truck:
-	Trigger camera function via camera HK on faceplate
-	Trigger camera function via rear gear

Use case Coach:
-	Trigger camera function via camera HK on faceplate
-	Trigger camera function via camera input pins 1
-	Trigger camera function via camera input pins 2
#endif

//special case for reverse cam is actived by HK:  expected auto deactivited by speed exceed to limit
//use case is covered in canManually actived process

//rear camera checks a logic rear state, which can be cancelled by HK/HP
BOOLEAN CReverseCameraMT::isInReverse()
{
    return CCanProcessor::getInstance()->isInReverse();
}
BOOLEAN CReverseCameraMT::isNotInReverse()
{
    return CCanProcessor::getInstance()->isNotInReverse();
}


TRC_SCOPE_DEF(ADAS, CReverseCameraMT, canAutoActivated);
BOOLEAN CReverseCameraMT::canAutoActivated()
{
    TRC_SCOPE(ADAS, CReverseCameraMT, canAutoActivated);
	setAutoActivatedType_NULL();
	//this two state is mean to detect hard pin coming up after reverse event, only this case speed auto hide is invalid for rvc
    static bool bWaitHardPinEvent = TRUE;
	static bool bWaitReverseEvent = TRUE;
    //todo customer new request to hardpin has high priority
	//cancel speed auto hide on rvc case(2/2) : cancel when a hard pin active  happens
    if(isPinOnOffRequestShowCamera(getPos())&&EOL::IfNeedCheckHardPin(getPos()))
	{ 
        //only rvs already show to driver a hardpin active event shall cancel speed restrict state
        //bug: hmi will sent reqeust  at background on hardpin deactive event , but not show the view actually.
        //but it will not affect CAN use case for last maunlly active only maintained for hard pin
        //note1 - when hard pin and rear gear both enabled, we need check which coming up first
		//note1 - filer speed event and other event here
		if(bWaitHardPinEvent&& (!bWaitReverseEvent))
		{
			SetSpeedRestrictInvalid();
			bWaitHardPinEvent = FALSE;
		}
		else
		{
		
		}
        m_bLsatIsReverseState = FALSE;
    	setAutoActivatedType_HardPin();
		DBG_MSG(("CReverseCameraMT::canAutoActivated() success @ isPinOnOffRequestShowCamera %d@ pos%d\n",getAutoActiveType(),getPos()));
		//if rear gear actived after a hard pin event 
		return TRUE;
	}
	//in hardpin active camera case: only after hardpin disabled then we need check/act on rear gear
    //as hardpin has higher priority than rear gear, both pin should be considered
    //this check is only possible when another hard pin is active ,so auto acitve for this cam is false;
    else if(isEitherHardPinActived())
	{
        if(bWaitHardPinEvent&& (!bWaitReverseEvent))
		{
			SetSpeedRestrictInvalid();
			bWaitHardPinEvent = FALSE;
		}
		else
		{
		    ;
		}
		DBG_MSG(("CReverseCameraMT::canAutoActivated() failed @ detected a hardpin active event on the other camera!! \n"));
		return FALSE;
	}
    else
    {
        bWaitHardPinEvent = TRUE;
    }

    //check with munually  override requsest 
    if((CCamera::eCameraNum > getPos())&& m_bDirectlyCancelRearCam[getPos()])
    {
        m_bDirectlyCancelRearCam[getPos()] = FALSE;
        m_bLsatIsReverseState = FALSE;
        DBG_MSG(("CMANReverseCamera::canAutoActivated() failed @ logically cancel rear gear, override request rear camera close immediately\n"));
        setAutoActivatedType_NULL();
        ResetLastManualActivated();//tbd
        isSpeedHigh() ;//update speed state
        return FALSE;
    }
	if(isInReverse()) // Now reverse priority highest
	{
	  m_bLsatIsReverseState = TRUE;
      DBG_MSG(("CReverseCameraMT::canAutoActivated() success @ isInReverse@ pos%d\n",getPos()));
	  m_eAutoActiveType = eType_CAN_REVERSE;
	  bWaitReverseEvent = FALSE;
	}
    else 
    {   
		bWaitReverseEvent = TRUE;     
        if(m_bLsatIsReverseState)
    	{
#if 0
//customer reqeust is not to cancel camera for parking secnario, gear changes but camera is not hide until manullt cancelled
            if(!EOL::IfNeedCheckSpeedRestriction())  
            {
               LsatReverseStateT = FALSE;
               DBG_MSG(("CReverseCameraMT::canAutoActivated() failed @  not need to check speed & rear gear inactive1@ pos%d\n",getPos()));
            }
            //cancel reverse gear but speed low
            else 
#endif    
            if( !isSpeedHigh() )
            {
                DBG_MSG(("CReverseCameraMT::canAutoActivated() success @  SpeednotHigh & rear gear keeplast state@ pos%d\n",getPos()));
                //NOT UPDATE FOR OVERRIDE USE CASE
                m_eAutoActiveType = eType_CAN_SPEED_DEA_REAR;
            }
            //cancel reverse gear but speed high
            else
            {
               m_bLsatIsReverseState = FALSE;
               ResetLastManualActivated();
               DBG_MSG(("CReverseCameraMT::canAutoActivated() failed @  Speedhigh & rear gear inactive1@ pos%d\n",getPos()));
            }
    	}
		//not rear gear state but high speed deactive use case is covered in CanManuallyActive process
    	else if(isSpeedHigh())
    	{
           ResetLastManualActivated(); 
           DBG_MSG(("CReverseCameraMT::canAutoActivated() failed @  SpeedHigh & rear gear inactive2@ pos%d\n",getPos()));
    	}
        else
        {
           DBG_MSG(("CReverseCameraMT::canAutoActivated() fail @  SpeedLow & last rear gear state = inactive@ pos%d\n",getPos()));
        }
    }

	if(eType_NULL!=getAutoActiveType())
     //&&(eType_CAN_SPEED_DEA_REAR!=getAutoActiveType()))
	{
		return TRUE;
	}
	else
	{
		DBG_MSG(("exit CReverseCameraMT::canAutoActivated() fail @ all@ pos%d\n",getPos()));
		return FALSE;
	}

}
TRC_SCOPE_DEF(ADAS, CReverseCameraMT, canManualActivated);
BOOLEAN CReverseCameraMT::canManualActivated() 
{
    TRC_SCOPE(ADAS, CReverseCameraMT, canManualActivated);
    if(eStatus_ManualActivated == getStatus()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
    {
        return FALSE;
    }    
	if(isEitherHardPinActived())
	{
       DBG_MSG(("CReverseCameraMT::canManualActivated() fail @ already AutoActivated@ pos%d\n",getPos()));
	   return FALSE;
	}

	//if(isInReverse())
	//{
    //   DBG_MSG(("CReverseCameraMT::canManualActivated() fail @ already InReverse@ pos%d\n",getPos()));
	//   return FALSE;
	//}

    if(isSpeedHigh())
    {
       ResetLastManualActivated(); 
       DBG_MSG(("CReverseCameraMT::canManualActivated() fail @ not in reverse and speed high@ pos%d\n",getPos()));
	   return FALSE;
    }
    m_bLsatIsReverseState = FALSE;
    DBG_MSG(("CReverseCameraMT::canManualActivated() success @ all@ pos%d\n",getPos()));
	setLastManualActivated();
	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CReverseCameraMT, canManualDeactivated);
BOOLEAN	CReverseCameraMT::canManualDeactivated() 
{
    TRC_SCOPE(ADAS, CReverseCameraMT, canManualDeactivated);
	if(isEitherHardPinActived())
	{
		DBG_MSG(("exit Camera%d-MT::canManualDeactivated() fail @isHardPinActivated @ pos%d\n",getPos()));
		return FALSE;
	}
    m_bLsatIsReverseState = FALSE;
    //on showoff cmd: expcept hardpin active 
#if 0
	if((EOL::IfNeedCheckReverseGear())&&( isInReverse() )) // Now reverse priority highest
	{
       DBG_MSG(("CReverseCameraMT::canManualDeactivated() fail @ already InReverse\n"));
	   return FALSE;
	}
#endif    
    DBG_MSG(("exit CReverseCameraMT::canManualDeactivated() success @ all@ pos%d\n",getPos()));
	ResetLastManualActivated();
	return TRUE;
}

void CReverseCameraMT::deactivate()
{
	CCamera::SetStateDeactivate();
}

TRC_SCOPE_DEF(ADAS, CReverseCameraMT, isSpeedHigh);
BOOLEAN	CReverseCameraMT::isSpeedHigh()
{
    //new reqeust:only valid after rear gear disengage and no other hardkey/hardpin event happened!
    //add use case for rear gear active toggle by Camera key but car still drive backward
	Float32 fSpeed = CCanProcessor::getInstance()->getSpeed();
	if( fSpeed > (Float32 )(EOL::getRevGelDeactSpeed(CCamera::EPos(getPos()+2)))//MAN speed is saved in pos3 and pos4
      &&EOL::IfNeedCheckSpeedRestriction()
      &&CCanProcessor::getInstance()->isDrivingForward()
      &&m_bIsSpeedRestrictValid)
	{
        TRC_SCOPE(ADAS, CReverseCameraMT, isSpeedHigh);
        m_bSpeedHighSate = TRUE;
		DBG_MSG(("CReverseCameraMT::isSpeedHigh : fSpeed = %5.2f@ pos%d\n",fSpeed,getPos()));
		return TRUE;
	}
    m_bSpeedHighSate = FALSE;
	return FALSE;
}
BOOLEAN	CReverseCameraMT::isEitherHardPinActived()
{
    return ((isPinOnOffRequestShowCamera(eCamera1)&&EOL::IfNeedCheckHardPin(eCamera1))||(isPinOnOffRequestShowCamera(eCamera2)&&EOL::IfNeedCheckHardPin(eCamera2)));
}

//MAN Truck Camera2 - assume it is general camera
TRC_SCOPE_DEF(ADAS, CGeneralCameraMT, CGeneralCameraMT);
CGeneralCameraMT::CGeneralCameraMT(EPos ePos)
: CCamera(ePos, eType_General)
{
    TRC_SCOPE(ADAS, CGeneralCameraMT, CGeneralCameraMT);
    DBG_MSG(("*********CGeneralCameraMT created on pos %d!\n*********",ePos));
}

CGeneralCameraMT::~CGeneralCameraMT()
{

}

BOOLEAN	CGeneralCameraMT::isEitherHardPinActived()
{
    return ((isPinOnOffRequestShowCamera(eCamera1)&&EOL::IfNeedCheckHardPin(eCamera1))||(isPinOnOffRequestShowCamera(eCamera2)&&EOL::IfNeedCheckHardPin(eCamera2)));
}
TRC_SCOPE_DEF(ADAS, CGeneralCameraMT, canAutoActivated);
BOOLEAN CGeneralCameraMT::canAutoActivated()
{
    TRC_SCOPE(ADAS, CGeneralCameraMT, canAutoActivated);
	if(isPinOnOffRequestShowCamera(getPos())&&EOL::IfNeedCheckHardPin(getPos()))
	{
	   DBG_MSG(("CGeneralCameraMT::canAutoActivated() success @ PIN activate@ pos%d\n",getPos()));
       setAutoActivatedType_HardPin();
	   return TRUE;
	}
    
    if(isSpeedHigh())
    {
       ResetLastManualActivated(); 
       DBG_MSG(("CReverseCameraMT::canManualActivated() fail @ not in reverse and speed high@ pos%d\n",getPos()));
	   return FALSE;
    }
    
	DBG_MSG(("CGeneralCameraMT::canAutoActivated()fails on MAN Trunk camera@ pos%d\n",getPos()));
    setAutoActivatedType_NULL();
	return FALSE;
}

//accpet manully active in rear gear engaged state
//then send a internal request to cancel rear gear and auto active state, amke state change to manully actived by last acived state 
TRC_SCOPE_DEF(ADAS, CGeneralCameraMT, canManualActivated);
BOOLEAN CGeneralCameraMT::canManualActivated() 
{
    TRC_SCOPE(ADAS, CGeneralCameraMT, canManualActivated);
    if(eStatus_ManualActivated == getStatus()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
    {
        return FALSE;
    }    
	if(isEitherHardPinActived())
	{
       DBG_MSG(("CGeneralCameraMT::canManualActivated() fail @ already AutoActivated@ pos%d\n",getPos()));
	   return FALSE;
	}
	if(isSpeedHigh())
	{
       ResetLastManualActivated(); 
       DBG_MSG(("CGeneralCameraMT::canManualActivated() fail @ forward & high speed @ pos%d\n",getPos()));
	   return FALSE;
	}

	DBG_MSG(("CGeneralCameraMT::canManualActivated()success@ pos%d\n",getPos()));
	setLastManualActivated();
	return TRUE;
}

TRC_SCOPE_DEF(ADAS, CGeneralCameraMT, canManualDeactivated);
BOOLEAN	CGeneralCameraMT::canManualDeactivated() 
{
    TRC_SCOPE(ADAS, CGeneralCameraMT, canManualDeactivated);
	if( isEitherHardPinActived())
	{
		DBG_MSG(("exit Camera2-MT::canManualDeactivated() fail @isHardPinActivated@ pos%d\n",getPos()));
		return FALSE;
	}
	DBG_MSG(("CGeneralCameraMT::canManualDeactivated()success@ pos%d\n",getPos()));
	ResetLastManualActivated();
	return TRUE;
}

TRC_SCOPE_DEF(ADAS, CGeneralCameraMT, isSpeedHigh);
BOOLEAN	CGeneralCameraMT::isSpeedHigh()
{
//customer new request: speed restrictionis only valid on rear gear actived camera    
#if 0    
	Float32 fSpeed = CCanProcessor::getInstance()->getSpeed();
	if( fSpeed >= (EOL::getRevGelDeactSpeed(CCamera::EPos(getPos()+2)))//MAN speed is saved in pos3 and pos4
      &&EOL::IfNeedCheckSpeedRestriction()
      &&(CCanProcessor::getInstance()->isDrivingForward()))
	{
        TRC_SCOPE(ADAS, CGeneralCameraMT, isSpeedHigh);
        m_bSpeedHighSate = TRUE;
		DBG_MSG(("CGeneralCameraMT::isSpeedHigh : uiSpeed = %u@ pos%d\n", uiSpeed,getPos()));
		return TRUE;
	}
    m_bSpeedHighSate = FALSE;
#endif    
	return FALSE;
}

