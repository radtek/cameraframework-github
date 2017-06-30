
#include "CCamera.hpp"
#include "CCameraMANCoach.hpp"
#include "CCameraMANTruck.hpp"
#include "../CEOL.hpp"
#include "CScaniaOnOffClient.hpp"
#include "CCanProcessor.hpp"

static const UInt32 s_num = 16;
struct tagCameraPriority
{
	CCamera::EType 		eFirstType;
	CCamera::EType 		eSecondType;
	CCamera::EPos		ePos;
	BOOLEAN				bCanToggle;
};

//SCANIA CR46 update FRS526_104
static tagCameraPriority s_aryPriority[s_num] =
{
		{CCamera::eType_Off, 				CCamera::eType_Off, 		CCamera::eCameraNum, 	FALSE},
		{CCamera::eType_Off, 				CCamera::eType_General, 	CCamera::eCamera2, 		FALSE},
		{CCamera::eType_Off, 				CCamera::eType_Reverse, 	CCamera::eCamera2, 		FALSE},
		{CCamera::eType_Off, 				CCamera::eType_Front, 		CCamera::eCamera2, 		FALSE},
		{CCamera::eType_General, 			CCamera::eType_Off, 		CCamera::eCamera1, 		FALSE},
		{CCamera::eType_General, 			CCamera::eType_General, 	CCamera::eCamera1, 		TRUE},
		{CCamera::eType_General, 			CCamera::eType_Reverse, 	CCamera::eCamera1, 		FALSE},
		{CCamera::eType_General, 			CCamera::eType_Front, 		CCamera::eCamera2, 		FALSE},
		{CCamera::eType_Reverse, 			CCamera::eType_Off, 		CCamera::eCamera1, 		FALSE},
		{CCamera::eType_Reverse, 			CCamera::eType_General, 	CCamera::eCamera2, 		FALSE},
		{CCamera::eType_Reverse, 			CCamera::eType_Reverse, 	CCamera::eCamera1, 		TRUE},
		{CCamera::eType_Reverse, 			CCamera::eType_Front, 		CCamera::eCamera2, 		FALSE},
		{CCamera::eType_Front, 				CCamera::eType_Off, 		CCamera::eCamera1, 		FALSE},
		{CCamera::eType_Front, 				CCamera::eType_General, 	CCamera::eCamera1, 		FALSE},
		{CCamera::eType_Front, 				CCamera::eType_Reverse, 	CCamera::eCamera1,		FALSE},
		{CCamera::eType_Front, 				CCamera::eType_Front, 		CCamera::eCamera1, 		FALSE},
};

CAdasCameraPrio::CAdasCameraPrio(const CCamera* pCamera1,const CCamera* pCamera2)
	:m_pPrioCamera1(pCamera1)
	,m_pPrioCamera2(pCamera2)
{
	;
}

CAdasCameraPrio::~CAdasCameraPrio()
{
  //m_pPrioCamera1 = NULL;
  //m_pPrioCamera2 = NULL;
};

CCamera::EPos CAdasCameraPrio::getPrioCameraOnMultiActive() const
{
   CCamera::EType eCamera1Type = EOL::getCameraType(CCamera::eCamera1);
   CCamera::EType eCamera2Type = EOL::getCameraType(CCamera::eCamera2);

   for( UInt32 i = 0 ;i < s_num; ++i )
   {
	   if( s_aryPriority[i].eFirstType == eCamera1Type && s_aryPriority[i].eSecondType == eCamera2Type  )
	   {
		   if( s_aryPriority[i].ePos != CCamera::eCameraNum )
		   {
			   return s_aryPriority[i].ePos;
		   }
	   }
   }
   return CCamera::eCameraNum;
}

CCamera::EPos CAdasCameraPrio::getPrioCameraOnToggle(CCamera::EPos CurrShowCameraPos) const
{
	CCamera::EType eCamera1Type = EOL::getCameraType(CCamera::eCamera1);
	CCamera::EType eCamera2Type = EOL::getCameraType(CCamera::eCamera2);

   for( UInt32 i = 0 ;i < s_num; ++i )
   {
	   if( (s_aryPriority[i].eFirstType == eCamera1Type) && (s_aryPriority[i].eSecondType == eCamera2Type)  )
	   {
		   if( s_aryPriority[i].bCanToggle )
		   {
			   if( CurrShowCameraPos == CCamera::eCamera1 )
			   {
				   return CCamera::eCamera2;
			   }
			   else if( CurrShowCameraPos != CCamera::eCamera1 )
			   {// may there is a bug
				   return CCamera::eCamera1;
			   }
		   }
		   break;
	   }
   }
   return CCamera::eCameraNum;
}


//====
static const UInt32 s_numMT = 4;
struct tagCameraPriorityMT
{
	CCamera::EAutoActiveType 		eFirstType;
	CCamera::EAutoActiveType 		eSecondType;
	CCamera::EPos				ePos;
};

#if 0   
Korn, Torsten (EXTERN: EEFC) [Torsten.Korn-ext@man.eu]
Use case Truck:
-	Trigger camera function via camera HK on faceplate
-	Trigger camera function via rear gear

Use case Coach:
-	Trigger camera function via camera HK on faceplate
-	Trigger camera function via camera input pins 1
-	Trigger camera function via camera input pins 2


From this point of view there will be no conflict between the rear gear and the input pins. But because every trigger is possible in all use cases, even if it is not planed to be used, we need to assign a priority. The last discussed priorities were:

Priority:
-	(lowest) Camera HK < Rear Gear signal camera 2 < Rear Gear signal  camera 1 < Video input pin 1 < video input pin 2 (highest)
#endif
//walk thought from left to right, expect HK, auto active type only vaild when camera is autoacitved
static tagCameraPriorityMT s_aryPriorityMT[s_numMT] =
{
        //Rear Gear signal camera 2
    	{CCamera::eType_CAN_REVERSE, 			CCamera::eType_CAN_REVERSE, 	CCamera::eCamera1},
        {CCamera::eType_CAN_REVERSE, 			CCamera::eType_PIN2, 	        CCamera::eCamera2},
    	{CCamera::eType_PIN1, 			        CCamera::eType_CAN_REVERSE, 	CCamera::eCamera1},
        {CCamera::eType_PIN1, 			        CCamera::eType_PIN2, 	        CCamera::eCamera2},
};

CAdasCameraPrioMT::CAdasCameraPrioMT(const CCamera* pCamera1,const CCamera* pCamera2)
	:CAdasCameraPrio(pCamera1,pCamera2)
{
   printf("created CAdasCameraPrioMT !!\n");
}

CAdasCameraPrioMT::~CAdasCameraPrioMT()
{

}
TRC_SCOPE_DEF(ADAS, CAdasCameraPrioMT, getPrioCameraOnMultiActive);
CCamera::EPos CAdasCameraPrioMT::getPrioCameraOnMultiActive() const
{
   TRC_SCOPE(ADAS, CAdasCameraPrioMT, getPrioCameraOnMultiActive);
   CCamera::EAutoActiveType eCamera1Type = m_pPrioCamera1->getAutoActiveType();
   CCamera::EAutoActiveType eCamera2Type = m_pPrioCamera2->getAutoActiveType();
   DBG_MSG(("CAdasCameraPrioMT - getPrioCameraOnMultiActive cam1 = %d cam2 = %d \n",eCamera1Type,eCamera2Type));
   //MAN special use case - rear camera deactivated but not override
   if(CCamera::eType_CAN_SPEED_DEA_REAR == eCamera1Type) eCamera1Type = CCamera::eType_CAN_REVERSE;
   if(CCamera::eType_CAN_SPEED_DEA_REAR == eCamera2Type) eCamera2Type = CCamera::eType_CAN_REVERSE;
   for( UInt32 i = 0 ;i < s_numMT; ++i )
   {
	   if( s_aryPriorityMT[i].eFirstType == eCamera1Type && s_aryPriorityMT[i].eSecondType == eCamera2Type  )
	   {
		   if( s_aryPriorityMT[i].ePos != CCamera::eCameraNum )
		   {
			   return s_aryPriorityMT[i].ePos;
		   }
	   }
   }
   DBG_MSG(("error: CAdasCameraPrioMT - getPrioCameraOnMultiActive cam1 = %d cam2 = %d \n",eCamera1Type,eCamera2Type));
   return CCamera::eCameraNum;
}
TRC_SCOPE_DEF(ADAS, CAdasCameraPrioMT, CAdasCameraPrioMT);
CCamera::EPos CAdasCameraPrioMT::getPrioCameraOnToggle(CCamera::EPos CurrShowCameraPos) const
{
	TRC_SCOPE(ADAS, CAdasCameraPrioMT, CAdasCameraPrioMT);
	DBG_MSG(("CAdasCameraPrioMT - getPrioCameraOnToggle no CR for it\n"));
	return CCamera::eCameraNum;
}
//------------------------------------------------------------------------------
CCamera::EStatus	CCameraCtrl::m_aryStatus[CCamera::eCameraNum] = {CCamera::eStatus_Deactivated,CCamera::eStatus_Deactivated};
CCamera*			CCameraCtrl::m_ppCamera[CCamera::eCameraNum]= {NULL,NULL};
CCameraCtrl::CCameraCtrl()
: m_eShowCameraPos(CCamera::eCameraNum)
, m_bInToogleState(FALSE)
, m_eState(eState_AllDeactive)
, m_pCAdasCameraPrio(NULL)
, m_bManuallyClose(FALSE)
{
	m_ppCamera[0] = NULL;
	m_ppCamera[1] = NULL;
	//memset(&m_ppCamera,sizeof(m_ppCamera),0);
	for(UInt32 i = 0; i < eCameraNum; ++i)
	{
		m_aryStatus[i] = CCamera::eStatus_Deactivated;	// maybe not connected
		m_ppCamera[i] = NULL;
	}

}

CCameraCtrl::~CCameraCtrl()
{

}

TRC_SCOPE_DEF(ADAS, CCameraCtrl, initialize);
BOOLEAN CCameraCtrl::initialize()
{
    TRC_SCOPE(ADAS, CCameraCtrl, initialize);
	// TODO according to the EOL
	if( m_ppCamera[0] == NULL || m_ppCamera[1] == NULL )
	{
		DBG_MSG(("CCameraCtrl initialize begin**********************************ver1\n"));
		CCamera::EType eCamera1Type = EOL::getCameraType(CCamera::eCamera1);
		CCamera::EType eCamera2Type = EOL::getCameraType(CCamera::eCamera2);

		m_ppCamera[0] = createCamera(eCamera1Type, CCamera::eCamera1);
		if( m_ppCamera[0] == NULL )
		{
			DBG_ERROR(("createCamera1 %d failed\n", (UInt32)eCamera1Type));
			return FALSE;
		}
        else
        {
			DBG_MSG(("createCamera1 = %d success\n", (UInt32)eCamera1Type));
        }

		m_ppCamera[1] = createCamera(eCamera2Type, CCamera::eCamera2);
		if( m_ppCamera[1] == NULL )
		{
			DBG_ERROR(("createCamera2 %d failed", (UInt32)eCamera2Type));
			return FALSE;
		}
        else
        {
			DBG_MSG(("createCamera2 = %d success\n", (UInt32)eCamera2Type));
        }
        
		DBG_MSG(("CCameraCtrl initialize end******************************************\n"));

	}
    //for MAN coach and trunk shared same proprity table for show two "autoactived" camera in system
   	if(Env::isMANTarget())
	{
		m_pCAdasCameraPrio = new CAdasCameraPrioMT((const CCamera*)m_ppCamera[0],(const CCamera*)m_ppCamera[1]);
	}
	else
	{
		m_pCAdasCameraPrio = new CAdasCameraPrio((const CCamera*)m_ppCamera[0],(const CCamera*)m_ppCamera[1]);
	}
	return TRUE;
}

void	CCameraCtrl::unInitialize()
{
	// TODO release camera
	if( m_ppCamera[0] )
	{
		delete m_ppCamera[0];
		m_ppCamera[0] = NULL;
	}

	if( m_ppCamera[1] )
	{
		delete m_ppCamera[1];
		m_ppCamera[1] = NULL;
	}
}
TRC_SCOPE_DEF(ADAS, CCameraCtrl, updateCameraStateManually);
void CCameraCtrl::updateCameraStateManually(EOperation eOp)
{
    TRC_SCOPE(ADAS, CCameraCtrl, updateCameraStateManually);
    
    UInt32 uidx = 0;
    if((eOp == eOp_ShowCamera1)||(eOp == eOp_HideCamera1))
    {
        uidx = 0;
    }
    else if((eOp == eOp_ShowCamera2)||(eOp == eOp_HideCamera2))
    {
        uidx = 1;
    }
    else
    {
        DBG_ERROR(("enter updateCameraStateManually fail on eOp =%d \n",eOp));
        return;
    }
    DBG_MSG(("enter updateCameraStateManually pos = %d ,eOp =%d\n",uidx, eOp));

    CCamera* pCamera = m_ppCamera[uidx];
    if( pCamera )
	{
		CCamera::EStatus eStatus = pCamera->getStatus();
		if((eStatus == CCamera::eStatus_AutoActivated)&&(0==uidx))
		{
            //use case is manually show on a already auto actived camera
            if(eOp == eOp_ShowCamera1)
            {
            	updateState(eOp_A2MCamera1);
            }
			else
			{
				updateState(eOp_DeaCamera1);
			}
            CCanProcessor::getInstance()->cancelRearGearState(TRUE);         
        }
        else if((eStatus == CCamera::eStatus_AutoActivated)&&(1==uidx))
        {
            if(eOp == eOp_ShowCamera2)
            {
            	updateState(eOp_A2MCamera2);
            }
			else
			{
				updateState(eOp_DeaCamera2);
			}

            CCanProcessor::getInstance()->cancelRearGearState(TRUE);
        }
        else
        {
            updateState(eOp);
        }
	}   
    else
    {
        DBG_ERROR(("enter updateCameraStateManually fail on not cam on pos =%d \n",uidx));
        return;
    }
   
    DBG_MSG(("exit updateCameraStateManually state %d @pos%d, pos1-state= %d, pos2-state=%d\n", m_eState,uidx,m_aryStatus[0],m_aryStatus[1]));
}

//todo: not process CAN state properly
TRC_SCOPE_DEF(ADAS, CCameraCtrl, updateCameraStateAuto);
void CCameraCtrl::updateCameraStateAuto(UInt32 uidx)
{
    TRC_SCOPE(ADAS, CCameraCtrl, updateCameraStateAuto);
	DBG_MSG(("enter updateCameraStateByCAN state %d @ pos %u\n", m_eState,uidx));
	if( uidx >= eCameraNum )
	{
		return;
	}

	CCamera* pCamera = m_ppCamera[uidx];
   //ALL CAN msg to active camera is autoActive type
   //first decide if autoActive is possible --reverse gear and speed
   //then decide if still keep manuale active state

	if( pCamera )
	{
		CCamera::EStatus eStatus = pCamera->getStatus();
		switch(eStatus)
		{
		case CCamera::eStatus_ManualActivated:
			if( pCamera->canAutoActivated() )
			{
				if( uidx == CCamera::eCamera1 ) updateState(eOp_AACamera1);
				else updateState(eOp_AACamera2);
			}
         //if autoactive is not fullfilled then need check if other active source for camera
         //use case for Manually actived camera deactivated by auto event: HK on - speed off
			else if( !pCamera->canManualActivated() )
			{
				//pCamera->deactivate();
				if( uidx == CCamera::eCamera1 ) updateState(eOp_DeaCamera1);
				else updateState(eOp_DeaCamera2);
			}
			break;
		case CCamera::eStatus_AutoActivated:
			if( !pCamera->canAutoActivated() )
			{
			//the only use case to check last manually activated state is on a auto active state cancelled
				if(pCamera->isLastManualActivated())//this auto A2M will not be triggered
				// ||pCamera->isCANSpeedActivatedRearCam())
				{
                    //case 1 : "previously manually actived" request found -- not set this state 20160713
					//case 2 : "speed not exceed limit" actived request found - only for MAN now
					if( uidx == CCamera::eCamera1 ) updateState(eOp_A2MCamera1);
					else updateState(eOp_A2MCamera2);
				}  
                else
				{
					//pCamera->deactivate();
					if( uidx == CCamera::eCamera1 ) updateState(eOp_DeaCamera1);
					else updateState(eOp_DeaCamera2);
				}
			}
			//update state again to update priority -- MAN Truck case
			else
			{
				if( uidx == CCamera::eCamera1 ) updateState(eOp_AACamera1);
				else updateState(eOp_AACamera2);
			}
			break;
		case CCamera::eStatus_Deactivated:
			if( pCamera->canAutoActivated() )
			{
				//pCamera->autoActivate();
				if( uidx == CCamera::eCamera1 ) updateState(eOp_AACamera1);
				else updateState(eOp_AACamera2);
			}
			else
			{
				if(pCamera->isLastManualActivated())
				{
					DBG_MSG(("found last manual when auto actived failed,resumed last manual actived state \n"));

					pCamera->SetStateManualActivate();
				}  
				else{}
			}
			break;
		}
	#if 0
        //new design: auto cancel manaull


	y active state on a auto active request 
        int AnotherCamId = ( uidx == CCamera::eCamera1 )?CCamera::eCamera2 :CCamera::eCamera1;
        CCamera* pCameraAutoset = m_ppCamera[AnotherCamId];//need update another cam by backgroud 
        if(pCameraAutoset)
        {
            if((pCameraAutoset->getStatus() == CCamera::eStatus_ManualActivated) 
                    &&(pCamera->getStatus() == CCamera::eStatus_AutoActivated))
            {
                //if another cam is manually acitve 
                 DBG_MSG(("updateCameraState for one auto acitve and one manully active 1 \n"));
            	EOperation CancelManuallyActCam = ( AnotherCamId == CCamera::eCamera1 )? eOp_DeaCamera1 :eOp_DeaCamera2;
                updateState(CancelManuallyActCam);
                m_aryStatus[AnotherCamId] = pCameraAutoset->getStatus();
            }
            else if((pCameraAutoset->getStatus() == CCamera::eStatus_AutoActivated) 
                    &&(pCamera->getStatus() == CCamera::eStatus_ManualActivated))
            {
                //if another cam is auto acitve 
                 DBG_MSG(("updateCameraState for one auto acitve and one manully active 2 \n"));
                EOperation CancelManuallyActCam = ( uidx == CCamera::eCamera1 )? eOp_DeaCamera1 :eOp_DeaCamera2;
                updateState(CancelManuallyActCam);
                //m_aryStatus[uidx] = pCameraAutoset->getStatus();    
            }
        }
	#endif
   }
   DBG_MSG(("exit updateCameraStateByCAN state %d @pos%d, pos1-state= %d, pos2-state=%d\n", m_eState,uidx,m_aryStatus[0],m_aryStatus[1]));
}
//todo: MAN state control
//create different state control according to platform
TRC_SCOPE_DEF(ADAS, CCameraCtrl, updateState);
void CCameraCtrl::updateState(EOperation eOp)
{
    TRC_SCOPE(ADAS, CCameraCtrl, updateState);
	DBG_MSG(("updateState state=%d op=%d\n", m_eState, eOp));
	
	switch(m_eState)
	{
	case eState_AllDeactive:
//todo: camera setting mode is only for mantain LSM
//then remove it , it should maintain in HMI side
#if 0      
		if( eOp == eOp_EnterCameraSetting )
		{
		//todo:should keep setting mode as LSM in ADAS side? or should HMI resend setting state to ADAS
		//this state should maintained in HMI side and removed from ADAS
			m_eState = eState_CameraSetting;
			DBG_MSG(("enter CameraSetting state\n"));
			// is this possible: camera activated by toggle and adas is asked to enter camera setting state
		}
#endif      
		if( eOp == eOp_AACamera1 )
		{
			m_eState = eState_OneAACamera;
			m_ppCamera[CCamera::eCamera1]->SetStateAutoActivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_AACamera2 )
		{
			m_eState = eState_OneAACamera;
			m_ppCamera[CCamera::eCamera2]->SetStateAutoActivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_Toggle )
		{
			normalToggle();
		}
		else if( eOp == eOp_DeaCamera1 )
		{
		//todo:
		//when all camera deavtived, what action is expected on deactive signal?
			m_ppCamera[CCamera::eCamera1]->SetStateDeactivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_DeaCamera2 )
		{	
		//todo:
			m_ppCamera[CCamera::eCamera2]->SetStateDeactivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_ShowCamera1 )
		{
			cameraSettingShowCamera(CCamera::eCamera1);
		}
		else if( eOp == eOp_ShowCamera2  )
		{
			cameraSettingShowCamera( CCamera::eCamera2);
		}
		else if( eOp == eOp_HideCamera1 )
		{
			m_ppCamera[0]->SetStateDeactivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_HideCamera2  )
		{
			m_ppCamera[1]->SetStateDeactivate();
			refreshShowCamera();
		}

		break;
   //todo: never go to this state
	case eState_CameraSetting:
      //todo: merge this state on HMI setcameraActiove request
      //limit only receive show/hide camera under this state now
      //HMI must save LSM state
		if( eOp == eOp_AACamera1 )
		{
			m_eState = eState_OneAACamera;
			m_ppCamera[CCamera::eCamera1]->SetStateAutoActivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_AACamera2 )
		{
			m_eState = eState_OneAACamera;
			m_ppCamera[CCamera::eCamera2]->SetStateAutoActivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_Toggle)
		{
			cameraSettingStateToggle();
		}
		else if( eOp == eOp_ShowCamera1 )
		{
			DBG_MSG(("showCamera op\n"));

			cameraSettingShowCamera(CCamera::eCamera1);
			DBG_MSG(("showCamera op finish\n"));
		}
		else if( eOp == eOp_ShowCamera2  )
		{
			cameraSettingShowCamera( CCamera::eCamera2);
		}
		else if( eOp == eOp_HideCamera1 )
		{
			m_ppCamera[0]->SetStateDeactivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_HideCamera2  )
		{
			m_ppCamera[1]->SetStateDeactivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_ExitCameraSetting )
		{
			m_eState = eState_AllDeactive;
			m_ppCamera[0]->SetStateDeactivate();
			m_ppCamera[1]->SetStateDeactivate();
			refreshShowCamera();
		}

		break;
	case eState_OneAACamera:
		if( eOp == eOp_DeaCamera1 )
		{
			if( m_ppCamera[0]->isAutoActivated() )
				m_eState = eState_AllDeactive;
			m_ppCamera[0]->SetStateDeactivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_A2MCamera1 )
		{
			if( m_ppCamera[0]->isAutoActivated() )
			{
				m_eState = eState_AllDeactive;
				m_ppCamera[0]->SetStateManualActivate();
                m_ppCamera[0]->setAutoActivatedType_NULL();
                //standby use case will failed on cancel rear gear process
                //cancel camera refresh to avoid on this specil state updata
				refreshShowCamera();
			}
			else
			{
				DBG_MSG(("wrong state - camera one is not auto activated\n"));
			}
		}
		else if( eOp == eOp_DeaCamera2 )
		{
			if( m_ppCamera[1]->isAutoActivated() )
					m_eState = eState_AllDeactive;
				m_ppCamera[1]->SetStateDeactivate();
			refreshShowCamera();
		}
		else if( eOp == eOp_A2MCamera2 )
		{
			if( m_ppCamera[1]->isAutoActivated() )
			{
				m_eState = eState_AllDeactive;
				m_ppCamera[1]->SetStateManualActivate();
                m_ppCamera[1]->setAutoActivatedType_NULL();
				refreshShowCamera();
			}
			else
			{
				DBG_MSG(("wrong state - camera two is not auto activated\n"));
			}
		}		
		else if( eOp == eOp_AACamera1 )
		{
			if(!m_ppCamera[0]->isAutoActivated() )
			{
				m_eState = eState_TwoAACamera;
				m_ppCamera[0]->SetStateAutoActivate();
				refreshShowCamera();
			}
			else
			{
                //if current state is standby, need to send out power off reqeust
                //speed/gear/request CAN hardpin
                 if(m_ppCamera[m_eShowCameraPos]->isStandbyWakeUp()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
                 {
                    DBG_MSG(("CCameraCtrl::already showCamera1 @ standby mode \n"));
                    CScaniaOnOffClient::getInstance()->onOffPmodePostEvent(0,FALSE);
                 } 				
                 DBG_MSG(("no change - camera1 is already auto activated\n"));
			}
		}
		else if( eOp == eOp_AACamera2 )
		{
			if(!m_ppCamera[1]->isAutoActivated() )
			{
				m_eState = eState_TwoAACamera;
				m_ppCamera[1]->SetStateAutoActivate();
				refreshShowCamera();
			}
			else
			{
                 //if current state is standby, need to send out power off reqeust
                 //speed/gear/request CAN hardpin
                 if(m_ppCamera[m_eShowCameraPos]->isStandbyWakeUp()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
                 {
                    DBG_MSG(("CCameraCtrl::already showCamera2 @ standby mode \n"));
                    CScaniaOnOffClient::getInstance()->onOffPmodePostEvent(1,FALSE);
                 } 	
				DBG_MSG(("no change - camera2 is already auto activated\n"));
			}
		}		
		else if( eOp == eOp_Toggle)
		{
			DBG_MSG(("can not toggle when one camera is auto actived!\n"));
		}
        else if(( eOp == eOp_ShowCamera1 )|| (eOp == eOp_ShowCamera2 ))
        {
            DBG_MSG(("can not ShowCamera when one camera is auto actived!\n"));
        }
        else if(( eOp == eOp_HideCamera1 )|| (eOp == eOp_HideCamera2 ))
        {
            DBG_MSG(("need check: manually set Camera to deactivated when one camera is auto activated by CAN!\n")); 
            EnableManuallyClose();
        }

		break;
	case eState_TwoAACamera:
		if( eOp == eOp_DeaCamera1)
		{
			m_eState = eState_OneAACamera;
			m_ppCamera[CCamera::eCamera1]->SetStateDeactivate();
            //specail case = two rear camera, rear camera can be override on manually cancel
            if(( m_ppCamera[CCamera::eCamera1]->getType()== m_ppCamera[CCamera::eCamera2]->getType())
              &&((CCamera::eType_Reverse)== m_ppCamera[CCamera::eCamera1]->getType())
              &&(m_ppCamera[CCamera::eCamera1]->getAutoActiveType() == m_ppCamera[CCamera::eCamera2]->getAutoActiveType())
              &&(!m_ppCamera[CCamera::eCamera1]->isHardPinActivated()))
            {
                DBG_MSG(("two rear camera deactivated at same time happened!@eOp_DeaCamera1\n"));
				m_ppCamera[CCamera::eCamera2]->SetStateDeactivate();
                m_ppCamera[CCamera::eCamera2]->setAutoActivatedType_NULL();
                m_eState = eState_AllDeactive;
            }
			refreshShowCamera();
		}
		else if( eOp == eOp_DeaCamera2)
		{
			m_eState = eState_OneAACamera;
			m_ppCamera[CCamera::eCamera2]->SetStateDeactivate();
            //specail case = two rear camera, rear camera can be override on manually cancel
            if(( m_ppCamera[CCamera::eCamera1]->getType()== m_ppCamera[CCamera::eCamera2]->getType())
              &&((CCamera::eType_Reverse)== m_ppCamera[CCamera::eCamera1]->getType())
              &&(m_ppCamera[CCamera::eCamera1]->getAutoActiveType() == m_ppCamera[CCamera::eCamera2]->getAutoActiveType())
              &&(!m_ppCamera[CCamera::eCamera1]->isHardPinActivated()))
            {
                DBG_MSG(("two rear camera deactivated at same time happened!@eOp_DeaCamera2\n"));
				m_ppCamera[CCamera::eCamera1]->SetStateDeactivate();
                m_ppCamera[CCamera::eCamera1]->setAutoActivatedType_NULL();
                m_eState = eState_AllDeactive;
            }            
			refreshShowCamera();
		}
		else if( eOp == eOp_A2MCamera1 )
		{
			if( m_ppCamera[0]->isAutoActivated() )
			{
				m_eState = eState_OneAACamera;
				m_ppCamera[0]->SetStateManualActivate();
                m_ppCamera[0]->setAutoActivatedType_NULL();
                //specail case = two rear camera, rear camera can be override on manually cancel
                if(( m_ppCamera[0]->getType()== m_ppCamera[1]->getType())
                  &&((CCamera::eType_Reverse)== m_ppCamera[0]->getType())
                  &&(m_ppCamera[0]->getAutoActiveType() == m_ppCamera[1]->getAutoActiveType())
                  &&(!m_ppCamera[0]->isHardPinActivated()))
                {
                    DBG_MSG(("two rear camera deactivated at same time happened!@eOp_A2MCamera1\n"));
    				//m_ppCamera[1]->SetStateManualActivate();
                    m_ppCamera[1]->setAutoActivatedType_NULL();
                }
				refreshShowCamera();			
			}
			else
			{
				DBG_MSG(("wrong state - camera one is not auto activated\n"));
			}
		}
		else if( eOp == eOp_A2MCamera2 )
		{
			if( m_ppCamera[1]->isAutoActivated() )
			{
				m_eState = eState_OneAACamera;
				m_ppCamera[1]->SetStateManualActivate();
                m_ppCamera[1]->setAutoActivatedType_NULL();
                //specail case = two rear camera, rear camera can be override on manually cancel
                if(( m_ppCamera[0]->getType()== m_ppCamera[1]->getType())
                  &&((CCamera::eType_Reverse)== m_ppCamera[0]->getType())
				  &&(m_ppCamera[0]->getAutoActiveType() == m_ppCamera[1]->getAutoActiveType())
				  &&(!m_ppCamera[0]->isHardPinActivated()))

                {
                    DBG_MSG(("two rear camera deactivated at same time happened!@eOp_A2MCamera2\n"));
    				//m_ppCamera[0]->SetStateManualActivate();
                    m_ppCamera[0]->setAutoActivatedType_NULL();
                }
				refreshShowCamera();
			}
			else
			{
				DBG_MSG(("wrong state - camera two is not auto activated\n"));
			}
		}		
		else if( eOp == eOp_Toggle)
		{
			aaTwoCameraToggle();
		}
      else if(( eOp == eOp_ShowCamera1 )|| (eOp == eOp_ShowCamera2 ))
      {
         DBG_MSG(("can not ShowCamera when two camera is auto actived!\n"));
      }
      else if(( eOp == eOp_HideCamera1 )|| (eOp == eOp_HideCamera2 ))
      {
         DBG_MSG(("manually set Camera to deactivated when one camera is auto activated by CAN!\n")); 
         //NOT CHANGE STATE, but only deactivated camera
         EnableManuallyClose();
      }
	  //for autoActive on same camera, priority may need updata!! *MAN-Truck case!
      else if(( eOp == eOp_AACamera1 )|| (eOp == eOp_AACamera2 ))
      {
	  	 refreshShowCamera();
         DBG_MSG(("for another autoActive request on same camera, priority may need updata!! *MAN-Truck case!!\n"));
      }
    
	  
		break;

	}
	
	for(UInt32 i = 0; i < eCameraNum; ++i)
	{
		CCamera* pCamera = m_ppCamera[i];
		if( pCamera )
		m_aryStatus[i] = pCamera->getStatus();
	}
	DBG_MSG(("updateState end %d\n", m_eState));
}
//preprocess for reduce internal msg queue usage
TRC_SCOPE_DEF(ADAS, CCameraCtrl, canToggleSwitchCamera);
BOOLEAN CCameraCtrl::canToggleSwitchCamera()
{
   TRC_SCOPE(ADAS, CCameraCtrl, canToggleSwitchCamera);
   DBG_MSG(("adas pre-check: canToggleSwitchCamera\n" ));
	// may be there is bug
	//todo preprocess before toggle??
	//if autoAct 1 cam, ignore toggle --rear camera is overridable
	//if autoAci 2 cam, toggle between 
	//if deact 2 cam, manually act one
	// if manually act 1 cam, manually act two
	// if manually act 2 cam, toogle to another cam
	//if(Env::isMANTarget()) sync to SCANIA
	//todo - if cancel here, action will tranfer to toggle active cam1
    
	
    //because logic rear gear is cancelled here, so use manually request to another one instead
	CCamera* pCam1 = m_ppCamera[CCamera::eCamera1];
	CCamera* pCam2 = m_ppCamera[CCamera::eCamera2];
	BOOLEAN bCam1 =  (pCam1&&(pCam1->getType()==CCamera::eType_Reverse)&&pCam1->isRearGearActivatedRearCam());
	BOOLEAN bCam2 =  (pCam2&&(pCam2->getType()==CCamera::eType_Reverse)&&pCam2->isRearGearActivatedRearCam());
    CReverseCameraMT::SetSpeedRestrictInvalid();
    if((eState_OneAACamera==m_eState)&&(bCam1)&&(pCam2))
    {
        DBG_MSG(("override cam1 on canToggleSwitchCamera\n" ));
        CCanProcessor::getInstance()->cancelRearGearState(TRUE);
        updateCameraStateManually(CCameraCtrl::eOp_ShowCamera2);
        return FALSE;
    }
    else if((eState_OneAACamera==m_eState)&&(bCam2)&&(pCam1))
    {
        DBG_MSG(("override cam2 on canToggleSwitchCamera\n" ));
        CCanProcessor::getInstance()->cancelRearGearState(TRUE);
        updateCameraStateManually(CCameraCtrl::eOp_ShowCamera1);
        return FALSE;
    }
    //special case for two rear camera in system
    else if((eState_TwoAACamera==m_eState)&&(bCam2)&&(bCam2))
    {
        DBG_MSG(("two auto case: override rev cam1 on canToggleSwitchCamera\n" ));
        CCanProcessor::getInstance()->cancelRearGearState(TRUE);
        updateCameraStateManually(CCameraCtrl::eOp_ShowCamera2);
        return FALSE;
    }
    
	return TRUE;
}

void CCameraCtrl::toggleSwitchCamera()
{
	updateState(eOp_Toggle);
}

BOOLEAN	CCameraCtrl::canManualActivate(CCamera::EPos ePos) const
{
	if( m_ppCamera[ePos] && m_eState != eState_TwoAACamera )
	{
		return m_ppCamera[ePos]->canManualActivated();
	}
	return FALSE;
}

BOOLEAN	CCameraCtrl::canManualDeactivate(CCamera::EPos ePos) const
{
	if( m_ppCamera[ePos] )
	{
		return m_ppCamera[ePos]->canManualDeactivated();
	}
	return FALSE;
}

BOOLEAN CCameraCtrl::isAllCamerasOff()
{
	for( UInt32 i = 0 ;i < eCameraNum; ++i )
	{
		if(( m_ppCamera[i])&&( m_aryStatus[i]!= CCamera::eStatus_Deactivated ))
		{
			return FALSE;
		}
	}

	return TRUE;
}

TRC_SCOPE_DEF(ADAS, CCameraCtrl, getCamera);
CCamera* CCameraCtrl::getCamera(CCamera::EPos ePos)
{
    if (CCamera::eCameraNum <= ePos)
    {
       TRC_SCOPE(ADAS, CCameraCtrl, getCamera);
       DBG_ERROR(("CCameraCtrl::getCamera id %d is outof limit\n",ePos));
       return NULL;
    }
    else
    {
       return m_ppCamera[ePos];
    }
}

CCamera* CCameraCtrl::getCamera(CCamera::EType eType)
{
	for( UInt32 i = 0 ;i < eCameraNum; ++i )
	{
		if( m_ppCamera[i] != NULL && m_ppCamera[i]->getType() == eType )
		{
			return m_ppCamera[i];
		}
	}

	return NULL;
}
TRC_SCOPE_DEF(ADAS, CCameraCtrl, setCurShowCameraValid);
void CCameraCtrl::setCurShowCameraValid(BOOLEAN b)
{
    TRC_SCOPE(ADAS, CCameraCtrl, setCurShowCameraValid);
	DBG_MSG(("CCameraCtrl::setCurShowCameraValid %s\n", b?"true":"false"));
	if( m_eShowCameraPos != CCamera::eCameraNum )
	{
		DBG_MSG(("CCameraCtrl::setCurShowCameraValid 11111%s\n", b?"true":"false"));
		m_ppCamera[m_eShowCameraPos]->setSignalValid(b);
	}
}
TRC_SCOPE_DEF(ADAS, CCameraCtrl, createCamera);
CCamera* CCameraCtrl::createCamera(CCamera::EType eType, CCamera::EPos ePos)
{
    TRC_SCOPE(ADAS, CCameraCtrl, createCamera);
//create MAN camera module -  reuse part of SCAINA camera module 
//keep coach and truck sepreated as customer may change request for special variant
//if reverse control EOL para is not set, just create general camera module for MAN
//front camera is not created for MAN dont have request to no override on front camera, it may cause HMI confuse
   if(Env::isMANTarget())
   {
       if(EOL::IsMANTruckTarget())
       {
          DBG_MSG(("CCameraCtrl::createCamera isMANTruckTarget\n"));
          if(CCamera::eType_Off == eType)
          {
             return new COffCamera(ePos);
          }
          else if(EOL::IfNeedCheckReverseGear(ePos))
          {
             return new CReverseCameraMT(ePos);
          }
          else
          {
             return new CGeneralCameraMT(ePos);
          }
       }
       else if(EOL::IsMANCoachTarget())
       {
          DBG_MSG(("CCameraCtrl::createCamera isMANCoachTarget\n"));
          if(CCamera::eType_Off == eType)
          {
             return new COffCamera(ePos);
          }
          else if(EOL::IfNeedCheckReverseGear(ePos))
          {
             return new CReverseCameraMC(ePos);
          }
          else
          {
             return new CGeneralCameraMC(ePos);
          }   
       }
   }
   else
   {
        DBG_MSG(("CCameraCtrl::createCamera Scaina\n"));
       	switch(eType)
       	{
       	case CCamera::eType_Off:
       		{
       			return new COffCamera(ePos);
       		}
       	case CCamera::eType_General:
       		{
       			return new CGeneralCamera(ePos);
       		}
       	case CCamera::eType_Reverse:
       		{
       			return new CReverseCamera(ePos);
       		}
       	case CCamera::eType_Front:
       		{
       			return new CFrontCamera(ePos);
       		}
       	}
   }
//DBG_MSG(("CCameraCtrl::createCamera end!! ePos= %d\n",ePos));
	return NULL;
}

TRC_SCOPE_DEF(ADAS, CCameraCtrl, showCamera);
void CCameraCtrl::showCamera(CCamera::EPos ePos)
{
    TRC_SCOPE(ADAS, CCameraCtrl, showCamera);
    //todo already show the same channel -- how to update it??
	if( m_eShowCameraPos != ePos )
	{
		if( m_eShowCameraPos != CCamera::eCameraNum )
		{
			CScaniaOnOffClient::getInstance()->requestPowerOnCamera(m_eShowCameraPos, 0,TRUE);
			m_ppCamera[m_eShowCameraPos]->hide();
		}

        m_eShowCameraPos = ePos;
        DBG_MSG(("CCameraCtrl::showCamera set m_eShowCameraPos =  %d\n", ePos));
        if( ePos == CCamera::eCameraNum)
        { 
            //all camera off state,send signal to ONOFF service to notify camera all off 
            CScaniaOnOffClient::getInstance()->onOffPmodePostEvent(4, FALSE);
        	return;
        }
        else
        {
             CScaniaOnOffClient::getInstance()->requestPowerOnCamera(ePos, 1,TRUE);
             if(m_ppCamera[m_eShowCameraPos]->isStandbyWakeUp()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
             {
                DBG_MSG(("CCameraCtrl::showCamera @ standby mode =  %d\n", ePos));
                CScaniaOnOffClient::getInstance()->onOffPmodePostEvent(ePos,m_ppCamera[m_eShowCameraPos]->isManualActivated());
             }      
             m_ppCamera[ePos]->show();
      }
	}
    else
    //when system in standby mode, camera state is not off,
    //but out of standby mode request should not ignored by a same pos request!
    {
        if( ePos != CCamera::eCameraNum)
        {
             CScaniaOnOffClient::getInstance()->requestPowerOnCamera(ePos, 1,TRUE);
             if(m_ppCamera[m_eShowCameraPos]->isStandbyWakeUp()&&CScaniaOnOffClient::getInstance()->isInStandbyState())
             {
                DBG_MSG(("same request:CCameraCtrl::showCamera @ standby mode =  %d\n", ePos));
                CScaniaOnOffClient::getInstance()->onOffPmodePostEvent(ePos,m_ppCamera[m_eShowCameraPos]->isManualActivated());
             }  
        }
        else
        {
            DBG_MSG(("same request: CCameraCtrl::hideCamera @ standby mode =  %d\n", ePos));
        }
    }
}

UInt32 CCameraCtrl::getAutoActivatedCameraNum() const
{
	UInt32 uiNum = 0;
	for( UInt32 i = 0 ;i < eCameraNum; ++i )
	{
		if( m_ppCamera[i] != NULL && m_ppCamera[i]->getStatus() == CCamera::eStatus_AutoActivated )
		{
			uiNum +=1;
		}
	}
	return uiNum;
}
TRC_SCOPE_DEF(ADAS, CCameraCtrl, cameraSettingStateToggle);
void CCameraCtrl::cameraSettingStateToggle()
{
    TRC_SCOPE(ADAS, CCameraCtrl, cameraSettingStateToggle);
	CCamera::EPos ePos = m_eShowCameraPos;
	DBG_MSG(("camera setting toggle %d\n", ePos));
	for( Int32 i = 0 ; i < eCameraNum; ++i )
	{
		if( ePos != i && m_ppCamera[i]->getType() != CCamera::eType_Off  )
		{
			if( ePos != CCamera::eCameraNum )
			{
				m_ppCamera[ePos]->SetStateDeactivate();
				m_ppCamera[ePos]->ResetLastManualActivated();
			}
			m_ppCamera[i]->SetStateManualActivate();
			showCamera( CCamera::EPos(i) );
			break;
		}
	}
}
//toggle when no camera auto active  -- eState_AllDeactive
//MAN platform have different behavior...
TRC_SCOPE_DEF(ADAS, CCameraCtrl, normalToggle);
void CCameraCtrl::normalToggle()
{
    TRC_SCOPE(ADAS, CCameraCtrl, normalToggle);
    BOOLEAN bSendActiveFailMsg = FALSE;
	if( m_eShowCameraPos == CCamera::eCameraNum )
	{
		if( m_ppCamera[0]->getType() != CCamera::eType_Off )
		{
			DBG_MSG(("Toggle active camera1 ver1\n"));
			if( m_ppCamera[0]->canManualActivated() )
			{
				m_ppCamera[0]->SetStateManualActivate();
				m_ppCamera[1]->SetStateDeactivate();
				m_ppCamera[1]->ResetLastManualActivated();
				showCamera(CCamera::eCamera1);
			}
             else
             {
                bSendActiveFailMsg =  TRUE;
                DBG_MSG(("Toggle active camera1 failed\n"));
             }
		}
		else if( m_ppCamera[1]->getType() != CCamera::eType_Off )
		{	
         DBG_MSG(("Toggle active camera2\n"));
			if( m_ppCamera[1]->canManualActivated() )
			{
				m_ppCamera[1]->SetStateManualActivate();
				m_ppCamera[0]->SetStateDeactivate();
				m_ppCamera[0]->ResetLastManualActivated();
				showCamera(CCamera::eCamera2);
			}
         else
         {
            bSendActiveFailMsg =  TRUE;
            DBG_MSG(("Toggle active camera2 failed\n"));
         }
         
		}
      else
      {
         bSendActiveFailMsg =  TRUE;
         DBG_MSG(("no camera config in system, no action on toggle\n"));

      }
	}
	else if((( m_eShowCameraPos == CCamera::eCamera1 )
      &&(m_ppCamera[1]->getType() == CCamera::eType_Off ))
      ||(( m_eShowCameraPos == CCamera::eCamera2 )
      &&(m_ppCamera[0]->getType() == CCamera::eType_Off )))
   {
        bSendActiveFailMsg =  TRUE;
        DBG_MSG(("only one camera in system, nothing happend on multi-Toggle\n"));
      //only one camera in system
      //keep show current camera
   }  
	else if(( m_eShowCameraPos == CCamera::eCamera1 )
      &&(m_ppCamera[1]->getType() != CCamera::eType_Off ))
 	{	
 	
      DBG_MSG(("Toggle switch to camera2\n"));
		if( m_ppCamera[1]->canManualActivated() )
		{
			m_ppCamera[1]->SetStateManualActivate();
			showCamera(CCamera::eCamera2);
			m_ppCamera[0]->SetStateDeactivate();
			m_ppCamera[0]->ResetLastManualActivated();
		}
      else
      {
         bSendActiveFailMsg =  TRUE;
         DBG_MSG(("can not toggle switch to camera2 due to restriction\n"));
      }
	}
	else if(( m_eShowCameraPos == CCamera::eCamera2 )
      &&(m_ppCamera[0]->getType() != CCamera::eType_Off ))
 	{	
 	   DBG_MSG(("Toggle switch to camera1\n"));
		if( m_ppCamera[0]->canManualActivated() )
		{
			m_ppCamera[0]->SetStateManualActivate();
			m_ppCamera[1]->SetStateDeactivate();
			m_ppCamera[1]->ResetLastManualActivated();
			showCamera(CCamera::eCamera1);
		}
      else
      {
         bSendActiveFailMsg =  TRUE;
         DBG_MSG(("can not toggle switch to camera1 due to restriction\n"));
      }
	}

    if(bSendActiveFailMsg)
    {
        SEND_BASEMESSAGE(eMsgType_HMIToggleRequestFailed,eGetCameraState);
    }
}

void CCameraCtrl::aaTwoCameraToggle()
{
   showCamera(m_pCAdasCameraPrio->getPrioCameraOnToggle(m_eShowCameraPos));
}

void CCameraCtrl::refreshShowCamera()
{
   if( m_eState == eState_TwoAACamera )
   {
	   showCamera(m_pCAdasCameraPrio->getPrioCameraOnMultiActive());
   }
   else if( m_eState == eState_OneAACamera )
   {
	   if(  m_ppCamera[0]->isAutoActivated() )
	   {
		   showCamera(CCamera::eCamera1);
	   }
	   else
	   {
		   showCamera(CCamera::eCamera2);
	   }
   }
   else if( m_eState == eState_AllDeactive || m_eState == eState_CameraSetting )
   {
	   if(  m_ppCamera[0]->getStatus() == CCamera::eStatus_ManualActivated )
	   {
		   showCamera(CCamera::eCamera1);
	   }
	   else if(  m_ppCamera[1]->getStatus() == CCamera::eStatus_ManualActivated )
	   {
		   showCamera(CCamera::eCamera2);
	   }
	   else
	   {
		   showCamera(CCamera::eCameraNum);
	   }
   }
}
TRC_SCOPE_DEF(ADAS, CCameraCtrl, cameraSettingShowCamera);
void CCameraCtrl::cameraSettingShowCamera(CCamera::EPos ePos)
{
    TRC_SCOPE(ADAS, CCameraCtrl, cameraSettingShowCamera);
	DBG_MSG(("cameraSettingShowCamera\n"));
	for(UInt32 i = 0 ;i < 2; ++i)
	{
		//DBG_MSG(("%u ",i));
		if( m_ppCamera[i] )
		{
			if( CCamera::EPos(i) == ePos )
			{
				m_ppCamera[i]->SetStateManualActivate();
				showCamera(ePos);
			}
			else
			{
				m_ppCamera[i]->SetStateDeactivate();
				m_ppCamera[i]->ResetLastManualActivated();
			}
		}
	}
	DBG_MSG(("cameraSettingShowCamera end\n"));
}
