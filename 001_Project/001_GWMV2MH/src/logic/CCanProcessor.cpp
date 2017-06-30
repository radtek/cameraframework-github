#include "CCanProcessor.hpp"
#include "CAdasCtrl.hpp"
#include "MessageDefine.hpp"

#include "CCameraMANTruck.hpp"
#include "Env.hpp"
CCanProcessor* CCanProcessor::s_pInstance = NULL;
TRC_SCOPE_DEF(ADAS, CCanProcessor, getInstance);
CCanProcessor* CCanProcessor::getInstance()
{
   if(s_pInstance == NULL)
   {
      TRC_SCOPE(ADAS, CCanProcessor, getInstance);
      DBG_MSG(("CCanProcessor created!!\n"));
	   s_pInstance = new CCanProcessor();
   }
   return s_pInstance;
}

void CCanProcessor::delInstance()
{
   if(s_pInstance != NULL)
   {
      delete s_pInstance;
      s_pInstance = NULL;
   }
}

CCanProcessor::~CCanProcessor()
{
	s_pInstance = NULL;
}

CCanProcessor::CCanProcessor()
{
   memset(&m_tagCruCtrlVehSpeed,0, sizeof(m_tagCruCtrlVehSpeed));
   memset(&m_tagSwitchParams,0, sizeof(m_tagSwitchParams));
   memset(&m_CANRequestOnOffCamera,0, sizeof(m_CANRequestOnOffCamera));
   m_tagCruCtrlVehSpeed.eParkBrakeSwitch = ePBS_NotAvailable;
   m_tagCruCtrlVehSpeed.uiWheelBasedVehSpeed= 0;

   m_tagSwitchParams.eLeftIndicatorIntended = eSV_NotAvailable;
   m_tagSwitchParams.eRightIndicatorIntended= eSV_NotAvailable;
   m_tagSwitchParams.eReverseSwitch= eSV_Off;
   m_tagSwitchParams.eWorkLigthToggleSwitch= eSV_NotAvailable;

   m_CANRequestOnOffCamera.eFrntVwCam = eCANOnOff_Off;
   m_CANRequestOnOffCamera.eGenCam1= eCANOnOff_Off;
   m_CANRequestOnOffCamera.eGenCam2= eCANOnOff_Off;
   m_CANRequestOnOffCamera.eGenCam3= eCANOnOff_Off;
   m_CANRequestOnOffCamera.eGenCam4= eCANOnOff_Off;
   m_CANRequestOnOffCamera.eRearVwCam= eCANOnOff_Off;


    
    //logic state for all event to support standby event cancel camera active state
    m_LogicPBSwich = ePBS_Set;
    m_LogicRightIndicatorIntender = eSV_Off;
    m_LogicLeftIndicatorIntender = eSV_Off;
    m_LogicWorkLigthToggleSwitch = eSV_Off;
    m_LogicReverseGearState= eSV_Off;
    #if 1
    //logic state for direcly request
    m_LogicRearVwCam = eCANOnOff_Off;
    m_LogicFrntVwCam = eCANOnOff_Off;
    m_LogicGenCam1 = eCANOnOff_Off;
    m_LogicGenCam2 = eCANOnOff_Off;
    #endif
   //this->registerEventCallback(eCruiseControlVehSpeed,makeFunctor(this,&CCanProcessor::onCruiseControlVehSpeed));
   //this->registerEventCallback(eDirectionSwitchParams,makeFunctor(this,&CCanProcessor::onSwitchParams));
}

BEGIN_DISPATCH(CCanProcessor)
	DISPATCH_EVENT(eCruiseControlVehSpeed, onCruiseControlVehSpeed)
	DISPATCH_EVENT(eDirectionSwitchParams, onSwitchParams)
	DISPATCH_EVENT(eCANRequestOnOffCamera, onCANOnOffParams)
END_DISPATCH

TRC_SCOPE_DEF(ADAS, CCanProcessor, onCruiseControlVehSpeed);
void CCanProcessor::onCruiseControlVehSpeed(void* pData)
{
    static EParkBrakeSwitch m_eLastParkingSwitch = ePBS_Set;
	if(pData!=NULL)
	{
        TRC_SCOPE(ADAS, CCanProcessor, onCruiseControlVehSpeed);
		tagCruiseControlVehSpeed* pSpeed = (tagCruiseControlVehSpeed*)pData;
    	//	if(pSpeed)
    	//	{
    			m_tagCruCtrlVehSpeed = *pSpeed;
                
    		//pSpeed->release();
    	//	}
        //todo: not put into msg que, process directly, how to handle fast switch case?
        if (m_eLastParkingSwitch!= m_tagCruCtrlVehSpeed.eParkBrakeSwitch)
        {
            m_LogicPBSwich = m_tagCruCtrlVehSpeed.eParkBrakeSwitch;
        }
            
   		DBG_MSG(("CCanProcessor::onCruiseControlVehSpeed,pSpeed=(%6.3f)%d,park=%d\n",((Float32)m_tagCruCtrlVehSpeed.uiWheelBasedVehSpeed/256),m_tagCruCtrlVehSpeed.uiWheelBasedVehSpeed,m_tagCruCtrlVehSpeed.eParkBrakeSwitch));
		CCamera* pCam1 = CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(CCamera::eCamera1);
		CCamera* pCam2 = CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(CCamera::eCamera2);
        //for parking break auto active front camera case
		if ((m_eLastParkingSwitch!= m_tagCruCtrlVehSpeed.eParkBrakeSwitch)
             && (ePBS_NotSet== m_tagCruCtrlVehSpeed.eParkBrakeSwitch)
             &&((pCam1&& pCam1->canAutoActivated()&&pCam1->isCANSpeedActivated())
		        ||(pCam2&& pCam2->canAutoActivated()&&pCam2->isCANSpeedActivated())))
		        //gear must be released in this case
		        CReverseCamera::vSetDirectlyCancelRearCam();

        m_eLastParkingSwitch = m_tagCruCtrlVehSpeed.eParkBrakeSwitch;
		CAdasCtrl::getInstance()->onAutoUpdateState(pData);
	}
}

TRC_SCOPE_DEF(ADAS, CCanProcessor, onSwitchParams);
void CCanProcessor::onSwitchParams(void* pData)
{
    static ESwitchValue m_eLastReverseSwitch = eSV_Off;
    static ESwitchValue m_eLastWorkLigthToggleSwitch = eSV_Off;
    static ESwitchValue m_eLastLeftIndicatorIntended = eSV_Off;
    static ESwitchValue m_eLastRightIndicatorIntended = eSV_Off;
    
    TRC_SCOPE(ADAS, CCanProcessor, onSwitchParams);
	tagSwitchParams* pSwitchParams = (tagSwitchParams*)pData;
	if(pSwitchParams)
	{
		m_tagSwitchParams = *pSwitchParams;
		//pSwitchParams->release();
        //this active request will enable auto deactive by speed  
        //or disabled by a user interaction of hard key or pin
        //a repeat rear gear on event will be ignorned
        //sync/reset logic gear state for rear camera only, on rear gear state change 
        if((m_tagSwitchParams.eReverseSwitch==eSV_On)&&(m_eLastReverseSwitch == eSV_Off))
        {
            m_LogicReverseGearState = eSV_On; 
        }
        else if((m_tagSwitchParams.eReverseSwitch==eSV_Off)&&(m_eLastReverseSwitch == eSV_On))
        {
            m_LogicReverseGearState = eSV_Off;
        }
        else
        {

        }   
		//error and not available state is porssed before send to this call back process
		//only on a system event for !on->on then set logic to on
        if(m_tagSwitchParams.eWorkLigthToggleSwitch==eSV_On)
        {
            if(m_eLastWorkLigthToggleSwitch != eSV_On) m_LogicWorkLigthToggleSwitch = eSV_On; 
        }
        else
        {
            m_LogicWorkLigthToggleSwitch = eSV_Off;
        }
  
		//direct indicator received here is debounced
        if(m_tagSwitchParams.eLeftIndicatorIntended==eSV_On)
        {
			if(m_eLastLeftIndicatorIntended != eSV_On) m_LogicLeftIndicatorIntender = eSV_On; 
        }
        else
        {
            m_LogicLeftIndicatorIntender = eSV_Off;
        }

        if(m_tagSwitchParams.eRightIndicatorIntended==eSV_On)
        {
			if(m_eLastRightIndicatorIntended != eSV_On) m_LogicRightIndicatorIntender = eSV_On; 
        }
        else
        {
            m_LogicRightIndicatorIntender = eSV_Off;
        }  
        
        if((m_tagSwitchParams.eReverseSwitch==eSV_On)&&(m_eLastReverseSwitch == eSV_Off))
        {
            CReverseCameraMT::SetSpeedRestrictValid();
            CReverseCamera::vCancelDirectlyCancelRearCam();
            CReverseCameraMT::vCancelDirectlyCancelRearCam();
        }
        else
        {
        //if working light on , canccel rear gear
			CCamera* pCam1 = CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(CCamera::eCamera1);
			CCamera* pCam2 = CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(CCamera::eCamera2);
            //if p1 = general cam and condition is good, than rear camera state update will not change here
			BOOLEAN bCam1 =  (pCam1&&(pCam1->getType()!=CCamera::eType_Reverse)&& pCam1->canAutoActivated()&&pCam1->isCANSwitchActivated());
			BOOLEAN bCam2 =  (pCam2&&(pCam2->getType()!=CCamera::eType_Reverse)&& pCam2->canAutoActivated()&&pCam2->isCANSwitchActivated());
            //if(bCam1||bCam2)
				//cancelRearGearState(TRUE);//CR46 general cam have higher prio than rear cam
            //for front camera active on rear gear release use case
            bCam1 = (pCam1&&(pCam1->getType()!=CCamera::eType_Reverse)&& pCam1->canAutoActivated()&&pCam1->isCANSpeedActivated());
			bCam2 = (pCam2&&(pCam2->getType()!=CCamera::eType_Reverse)&&  pCam2->canAutoActivated()&&pCam2->isCANSpeedActivated());
            if(bCam1||bCam2)
				CReverseCamera::vSetDirectlyCancelRearCam();
        }

        m_eLastReverseSwitch = m_tagSwitchParams.eReverseSwitch;
        m_eLastWorkLigthToggleSwitch = m_tagSwitchParams.eWorkLigthToggleSwitch;
        m_eLastLeftIndicatorIntended = m_tagSwitchParams.eLeftIndicatorIntended;
        m_eLastRightIndicatorIntended = m_tagSwitchParams.eRightIndicatorIntended;
	}

	DBG_MSG(("logic gear=%d, actual gear=%d\n", m_LogicReverseGearState,m_tagSwitchParams.eReverseSwitch));
	CAdasCtrl::getInstance()->onAutoUpdateState(pData);


}

//this method  only call on MAN platform when hard key request received
//cancel speed auto hide on rvc case(1/2) : cancel when a user input happens
TRC_SCOPE_DEF(ADAS, CCanProcessor, CancelRearGearState);
void CCanProcessor::cancelRearGearState(BOOLEAN bIsDirectlyCancel)
{
    TRC_SCOPE(ADAS, CCanProcessor, CancelRearGearState);
	DBG_MSG(("CCanProcessor::CancelRearGearState\n"));
    //cancel auto hide porcess after gear is cancelled manually on MAN, for SCANIA, always auto hide on high speed
    CReverseCameraMT::SetSpeedRestrictInvalid();
    //SCANIA shall cancel auto hide timer
    CReverseCamera::vDisableAutoHideTimer();
    tagSwitchParams* pSwitchParams;// fake input 
    if(bIsDirectlyCancel)
    {
        //for as of now override cancel rear gear will not auto transfer to manually active state
        //so cancel logic rear gear for rear camera immediately
        //and a normal cancel rear gear event will keep camera in CAN  active state
        //switch to close state immediately
        if((!CReverseCamera::bDirectlyCancelledRearCam())&&Env::isScaniaTarget())
        {
            CReverseCamera::vSetDirectlyCancelRearCam();
            //manually override rear camera before timer out/speed high use case
            if(eSV_Off == m_LogicReverseGearState)
             CAdasCtrl::getInstance()->onAutoUpdateState(pSwitchParams);
        }
        else if(!CReverseCameraMT::bDirectlyCancelledRearCam())
        {
            CReverseCameraMT::vSetDirectlyCancelRearCam();
            //manually override rear camera before speed high use case
            if(eSV_Off == m_LogicReverseGearState)
             CAdasCtrl::getInstance()->onAutoUpdateState(pSwitchParams);
        }     
    }
    //if this off is not loggicall set , then directly cancel state may not correct on manully request
    if(eSV_Off == m_LogicReverseGearState) return;
    m_LogicReverseGearState = eSV_Off;
	CAdasCtrl::getInstance()->onAutoUpdateState(pSwitchParams);
}

TRC_SCOPE_DEF(ADAS, CCanProcessor, vDisableRearGearLogicState);
void CCanProcessor::vDisableRearGearLogicState()
{
    TRC_SCOPE(ADAS, CCanProcessor, vDisableRearGearLogicState);
    m_LogicReverseGearState= eSV_Off;
    DBG_MSG(("CCanProcessor::vDisableRearGearLogicState on standby event happened\n"));
}

TRC_SCOPE_DEF(ADAS, CCanProcessor, vDisableLogicState);
void CCanProcessor::vDisableLogicState()
{
    TRC_SCOPE(ADAS, CCanProcessor, vDisableLogicState);
    //m_LogicPBSwich = ePBS_Set;
    m_LogicRightIndicatorIntender = eSV_Off;
    m_LogicLeftIndicatorIntender = eSV_Off;
    m_LogicWorkLigthToggleSwitch = eSV_Off;
    m_LogicRearVwCam = eCANOnOff_Off;
    m_LogicFrntVwCam = eCANOnOff_Off;
    m_LogicGenCam1 = eCANOnOff_Off;
    m_LogicGenCam2 = eCANOnOff_Off;
    DBG_MSG(("CCanProcessor::vDisableLogicState on standby event happened\n"));
}


TRC_SCOPE_DEF(ADAS, CCanProcessor, vSetRearGearLogicState);
void CCanProcessor::vSetRearGearLogicState()
{
    TRC_SCOPE(ADAS, CCanProcessor, vSetRearGearLogicState);
    void *pData;
    //only rear camera is overridable
    m_LogicReverseGearState= eSV_On;
    DBG_MSG(("CCanProcessor::vSetRearGearLogicState on outof standby event happened\n"));
}
TRC_SCOPE_DEF(ADAS, CCanProcessor, vSetRearOnoffLogicState);
void CCanProcessor::vSetRearOnoffLogicState()
{
    TRC_SCOPE(ADAS, CCanProcessor, vSetRearGearLogicState);
    void *pData;
    m_LogicRearVwCam= eCANOnOff_On;
    DBG_MSG(("CCanProcessor::vSetRearOnoffLogicState on outof standby event happened\n"));
}
TRC_SCOPE_DEF(ADAS, CCanProcessor, vSetFrontOnoffLogicState);
void CCanProcessor::vSetFrontOnoffLogicState()
{
    TRC_SCOPE(ADAS, CCanProcessor, vSetFrontOnoffLogicState);
    void *pData;
    m_LogicFrntVwCam= eCANOnOff_On;
    DBG_MSG(("CCanProcessor::vSetFrontOnoffLogicState on outof standby event happened\n"));
}
TRC_SCOPE_DEF(ADAS, CCanProcessor, vSetGen1OnoffLogicState);
void CCanProcessor::vSetGen1OnoffLogicState()
{
    TRC_SCOPE(ADAS, CCanProcessor, vSetGen1OnoffLogicState);
    void *pData;
    m_LogicGenCam1= eCANOnOff_On;
    DBG_MSG(("CCanProcessor::vSetGen1OnoffLogicState on outof standby event happened\n"));
}
TRC_SCOPE_DEF(ADAS, CCanProcessor, vSetGen2OnoffLogicState);
void CCanProcessor::vSetGen2OnoffLogicState()
{
    TRC_SCOPE(ADAS, CCanProcessor, vSetGen2OnoffLogicState);
    void *pData;
    m_LogicGenCam2= eCANOnOff_On;
    DBG_MSG(("CCanProcessor::vSetGen2OnoffLogicState on outof standby event happened\n"));
}

TRC_SCOPE_DEF(ADAS, CCanProcessor, onCANOnOffParams);
void CCanProcessor::onCANOnOffParams(void* pData)
{
    TRC_SCOPE(ADAS, CCanProcessor, onCANOnOffParams);
    static ECANOnOffValue m_eLastRearCamOnOff = eCANOnOff_Off;
    static ECANOnOffValue m_eLastFrontCamOnOff = eCANOnOff_Off;
    static ECANOnOffValue m_eLastGenCam1OnOff = eCANOnOff_Off;
    static ECANOnOffValue m_eLastGenCam2OnOff = eCANOnOff_Off;    
    
	tagCANRequestOnOffCamera* pCANOnOffParams = (tagCANRequestOnOffCamera*)pData;
	if(pCANOnOffParams)
	{
		m_CANRequestOnOffCamera = *pCANOnOffParams;
        //check if work light  on ...

	}
    DBG_MSG(("CCanProcessor::onCANOnOffParams\n"));
    #if 1
    //if can request camera on ,cancel rear gear 
	CCamera* pCam1 = CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(CCamera::eCamera1);
	CCamera* pCam2 = CAdasCtrl::getInstance()->getCameraCtrl()->getCamera(CCamera::eCamera2);
	BOOLEAN bCam1 =  (pCam1&&(pCam1->getType()!=CCamera::eType_Reverse)&& pCam1->canAutoActivated()&&pCam1->isCANSwitchActivated());
	BOOLEAN bCam2 =  (pCam2&&(pCam2->getType()!=CCamera::eType_Reverse)&& pCam2->canAutoActivated()&&pCam2->isCANSwitchActivated());
	//CR46 - general cam have higher prio than rear, keep rear active at background
    //if(bCam1||bCam2)
	//	cancelRearGearState(TRUE);
    #endif

    if(m_CANRequestOnOffCamera.eRearVwCam!= m_eLastRearCamOnOff)
    {
        m_LogicRearVwCam = m_CANRequestOnOffCamera.eRearVwCam;
    }
    if(m_CANRequestOnOffCamera.eFrntVwCam!=m_eLastFrontCamOnOff)
    {
        m_LogicFrntVwCam = m_CANRequestOnOffCamera.eFrntVwCam;
    }
    if(m_CANRequestOnOffCamera.eGenCam1!=m_eLastGenCam1OnOff)
    {
        m_LogicGenCam1 = m_CANRequestOnOffCamera.eGenCam1;
    }
    if(m_CANRequestOnOffCamera.eGenCam2!=m_eLastGenCam2OnOff)
    {
        m_LogicGenCam2 = m_CANRequestOnOffCamera.eGenCam2;
    }
    
    m_eLastRearCamOnOff = m_CANRequestOnOffCamera.eRearVwCam;
    m_eLastFrontCamOnOff =  m_CANRequestOnOffCamera.eFrntVwCam;
    m_eLastGenCam1OnOff =  m_CANRequestOnOffCamera.eGenCam1;
    m_eLastGenCam2OnOff =  m_CANRequestOnOffCamera.eGenCam2;   
    DBG_MSG(("logic onoff=%d%d%d%d\n", m_LogicRearVwCam,m_LogicFrntVwCam,m_LogicGenCam1,m_LogicGenCam2));
	CAdasCtrl::getInstance()->onAutoUpdateState(pData);
}



