/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            AMBConsumerHandler.cpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           AMBConsumerHandler Consumes events from AMB and routes to required module(RVC,APA and VPA)
*                  based on the events it received.
*                  
*/

#include"CAMBConsumerHandler.hpp"
#include "ParkAssistSrv_Common/CPresCoreHandler.hpp"

#define PDC_IS_ON 5

#define MULTIPLICATION_FACTOR 0.01
#define TIMER_CALLBACK 5
AMBConsumerHandler:: AMBConsumerHandler()
{
    m_bCameraMaxSpeed = false;
    m_pobjContext = NULL;
    LOG_INFO(LOG_COMMON,"AMBConsumerHandler constructor");
}


AMBConsumerHandler::~AMBConsumerHandler()
{
    
}


/**
    @brief initializing all variable and providing  interface to set RVVservicestub  pointer. 
    @param  RVCServiceStubImpl shared Pointer
 */
void AMBConsumerHandler::InitializeAMBConsumerHandler(CContext *p_pobjContext)
{
    if(NULL != p_pobjContext)
    {
        m_pobjContext = p_pobjContext;
    }
    LOG_ERROR(LOG_COMMON, "InitializeAMBConsumerHandler ....");
}

// ============================================RVC SECTION START===============================================================//


/**
    @brief Callback function from AMB to indicate Vehicle Characteristic  properties are changed  and routes AMB events to required module(RVC,APA and VPA) 
    @param  VehCharacteristicSet2
 */
void AMBConsumerHandler::VehCharNotifyCallBack(v0::org::harman::ford::camerainfo_types::VehCharacteristicSet2_HS3_struct p_stSet2Data)
{

    if(NULL != m_pobjContext)
    {

        m_pobjContext->m_intContextCamraOvrlStat = p_stSet2Data.getCamraOvrlStat_D_Actl_enum();

        
        //m_pobjContext->m_intContextCamraOvrlDyn = p_pstVehChar.getCamraOvrlDyn_D_Actl_enum();
        
    }
    //Process the request and inform HMI the current status of camera image properties
    EParkAssistReqId l_eReqId = e_ParkAssist_RVC_VEHICLE_CHAR_NTFY;
    LOG_INFO(LOG_RVC, "VehCharacteristicSet2_HS3_struct received...\n");
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);

}


void AMBConsumerHandler::Sig0AttributeCallBack(v0::org::harman::ford::camerainfo_types::VehCharacteristicSet2_HS3_sig_0_struct p_stSig0Data)
{
    LOG_INFO(LOG_RVC, "Sig0AttributeCallBack received...\n");
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextCamPDCGuidStat = p_stSig0Data.getCamPDCGuidStat_enum();
        EParkAssistReqId l_eReqId = e_ParkAssist_RVC_PDC_GUIDE_STATUS;
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);

    }
    else
    {
        LOG_ERROR(LOG_RVC, "m_pobjContext is NULL...");
    }
}

void AMBConsumerHandler::Sig2AttributeCallBack(v0::org::harman::ford::camerainfo_types::VehCharacteristicSet2_HS3_sig_2_struct p_stSig2Data)
{
    LOG_INFO(LOG_RVC, "Sig2AttributeCallBack received...\n");
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextCamraZoom = p_stSig2Data.getCamraZoomMan_D_Actl_enum();
        EParkAssistReqId l_eReqId = e_ParkAssist_RVC_CAMERA_ZOOM_STATUS;
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);

    }
    else
    {
        LOG_ERROR(LOG_RVC, "m_pobjContext is NULL...");
    }
}
void  AMBConsumerHandler::SplitViewResponceCallBack(v0::org::harman::ford::camerainfo_types::PAC_Send_Signals_sig_0_struct p_stSplitViewData)
{
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextCamraSplitView = p_stSplitViewData.getCamraViewSplit_D_Actl_enum();
        EParkAssistReqId l_eReqId = e_ParkAssist_RVC_SPLITVIEW_RESPONSE;
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);

    }
    else
    {
        LOG_ERROR(LOG_RVC, "m_pobjContext is NULL...");
    }

}

/**
    @brief Callback function from AMB to indicate GearPostion of Vehicle got changed  and routes AMB events to required module(RVC,APA and VPA) 
    @param  TransmissionModeExtension
*/

void AMBConsumerHandler::GearPostionNotifyCallBack(v0::org::harman::ford::bodycontroldata_types::Body_Info_1_HS3_sig_0_struct p_stGearLvrPos)
{
    if(NULL != m_pobjContext)
    {
        LOG_INFO(LOG_RVC, "GearPostionNotifyCallBack received from AMB..\n");

        m_pobjContext->m_eContextGearLvrPos = p_stGearLvrPos.getGearLvrPos_D_Actl_enum();

    }
        //Process the request and inform HMI the current status of camera image properties
    EParkAssistReqId l_eReqId = e_ParkAssist_RVC_GEAR_POSTION;
    LOG_INFO(LOG_RVC, "GearPostionNotifyCallBack received...\n");
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);

}
/**
    @brief Callback function from AMB to indicate current speed of vehicle
    @param  uint16_t speed of vehicle in km/hr
*/
void AMBConsumerHandler::VehicelSpeedNotifyCallBack(v0::org::harman::ford::bodycontroldata_types::Veh_V_ActlEng_struct p_stVeh_V_ActlEng_structData)
{

    uint16_t l_CurrentVehSpeedPhysicalVal = 0;
    if(p_stVeh_V_ActlEng_structData.getStatus() == 0)
    {
        l_CurrentVehSpeedPhysicalVal = p_stVeh_V_ActlEng_structData.getVeh_V_ActlEng()* MULTIPLICATION_FACTOR;
    }
    else
    {
        // Handle Timeout
    }
    LOG_INFO(LOG_RVC,"Vehicle speed Raw Value:[%d] Physical Value:[%d] ",p_stVeh_V_ActlEng_structData.getVeh_V_ActlEng(), l_CurrentVehSpeedPhysicalVal);
    //Verify whether current vehicle speed is greater 10kmph and previously already updated to RVC presctrl
    if((l_CurrentVehSpeedPhysicalVal > RVC_MAX_VEHICLE_SPEED) && (m_bCameraMaxSpeed == false))
    {
        //inform Rvc presctrl that camera speed is more than 10km/hr
        LOG_INFO(LOG_RVC,"Vehicle speed is more than 10kmph");
        m_bCameraMaxSpeed = true;
        PostChangeInSpeedToPresCore(m_bCameraMaxSpeed);
    }
    else if((l_CurrentVehSpeedPhysicalVal <= RVC_MAX_VEHICLE_SPEED) && (m_bCameraMaxSpeed ==true))
    {
        LOG_INFO(LOG_RVC,"Vehicle speed is Less than 10kmph");
        m_bCameraMaxSpeed = false;
        PostChangeInSpeedToPresCore(m_bCameraMaxSpeed);    
    }
    else
    {

        LOG_INFO(LOG_RVC,"Already updated to RVC presctrl");
    }
}

void AMBConsumerHandler::PostChangeInSpeedToPresCore(bool p_bIsMaxSpeed)
{
    if(nullptr != m_pobjContext)
    {
        m_pobjContext->m_bContextCameraMaxSpeed = p_bIsMaxSpeed;
        EParkAssistReqId l_eReqId = e_ParkAssist_RVC_VEHICLE_MAXSPEED;
        LOG_INFO(LOG_RVC, "VehicelSpeedNotifyCallBack received...\n");
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
    }
}

/**
    @brief Callback function from AMB to indicate parking brake status of Vehicle changed and routes AMB events to required module(RVC,APA and VPA) 
    @param  ParkingBrakeActiveStatus
*/
void AMBConsumerHandler::ParkBrkStatusNotifyCallBack(v0::org::harman::ford::enginedata_types::PrkBrkActv_B_Actl_struct p_stPrkBrkActvStatus)
{
    if(NULL != m_pobjContext)
    {
        if(p_stPrkBrkActvStatus.getStatus() == 0)
        {
            m_pobjContext->m_eContextPrkBrkActvStatus = p_stPrkBrkActvStatus.getPrkBrkActv_B_Actl_enum();
            EParkAssistReqId l_eReqId = e_ParkAssist_RVC_PARK_BREAK_ACTIVE_STATUS;
            LOG_INFO(LOG_RVC, "VehicelSpeedNotifyCallBack received...\n");
            CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
        }
        else
        {
            // Handle Timeout
        }

    }
}

void AMBConsumerHandler::EleBrkStatusCallback(enginedata_types::PrkBrkStatus_struct p_stPrkBrStatus)
{
     if(NULL != m_pobjContext)
    {
        if(p_stPrkBrStatus.getStatus() == 0)
        {
            m_pobjContext->m_eContextElePrkStatus = p_stPrkBrStatus.getPrkBrkStatus_enum();
            EParkAssistReqId l_eReqId = e_ParkAssist_RVC_ELEC_PARK_BREAK_STATUS;
            LOG_INFO(LOG_RVC, "EleBrkStatusCallback received...\n");
            CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
        }
        else
        {
            // Handle Timeout
        }

    }

}
/**
    @Brief:Notification from AMB related to trunk status of vehicle
    @param  DrStatTgate_B_Actl_enum
 */

void AMBConsumerHandler::TrunkStatusNotifyCallBack(enginedata_types::DrStatTgate_B_Actl_enum p_eDoorOpenStatus)
{

    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_eContextDoorOpenStatus = p_eDoorOpenStatus;
        EParkAssistReqId l_eReqId = e_ParkAssist_RVC_DOOR_OPEN_STATUS;
        LOG_INFO(LOG_RVC, "TrunkStatusNotifyCallBack received\n ");
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
    }
}

/**
    @Brief:Notification from NSM related to NSM state is active or inactive
    @param  
 */


void AMBConsumerHandler::onNsmSessionStateChange(std::string VehiclePowerMode)
{
    bool l_nsmSessionState = false;
    LOG_INFO(LOG_RVC,"onNsmSessionStateChange Callback");
    //Checking whether NSM state is active or inactive
    if((VehiclePowerMode.compare("VPM_OFF") == 0 ) ||(VehiclePowerMode.compare("VPM_STANDBY") == 0)||(VehiclePowerMode.compare("VPM_SLEEP") == 0) )
    {
        LOG_INFO(LOG_RVC,"UpdateNSMState as standby");
        //NSM state is inactive and Informing RVC presctrl to switch off the RVC display
        l_nsmSessionState = true;
    }
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_bContextNsmSessionState = l_nsmSessionState;
        EParkAssistReqId l_eReqId = e_ParkAssist_RVC_NSM_STATUS;
        LOG_INFO(LOG_RVC, "NSM callback  received StandbyState:%d \n",l_nsmSessionState);
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
    }
    
} 


/**
    @Brief:Notification from AMB related to manual status of gear
    @param  
 */

void AMBConsumerHandler::VehRevGearNotifyCallBack(v0::org::harman::ford::rearviewcamclient_types::GearRvrse_D_Actl_struct p_stRevGear)
{
    if(NULL != m_pobjContext)
    {
        if(p_stRevGear.getStatus() == 0)
        {
            m_pobjContext->m_eRevGearStatus = p_stRevGear.getGearRvrse_D_Actl_enum();
        }
        else
        {
            // handle timeout
        }
        EParkAssistReqId l_eReqId = e_ParkAssist_RVC_MANUAL_GEAR_STATUS;
        LOG_INFO(LOG_RVC, "Veh RevGear NotifyCallBackreceived \n");
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
    }
}


void AMBConsumerHandler::IginitionStatusCallback(enginedata_types::Ignition_Status_enum obj)
{
    bool l_Ignitionoff = true;
    if((enginedata_types::Ignition_Status_enum::En_Run == obj)||(enginedata_types::Ignition_Status_enum::En_Start == obj)) 
    {
        //No need to switch off the camera if ignition is run and start
        l_Ignitionoff = false;
    }
    // Only post the message to prescore on value changed 
     if(NULL != m_pobjContext && l_Ignitionoff != m_pobjContext->m_bContextIgnStatus)
    {
        m_pobjContext->m_bContextIgnStatus = l_Ignitionoff;
        EParkAssistReqId l_eReqId = e_ParkAssist_RVC_IGNITION_STATUS;
        LOG_INFO(LOG_RVC, "IginitionStatusCallback received l_Ignitionoff:%d \n",l_Ignitionoff);
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
    }

    
} 

// ============================================APA SECTION START===============================================================//

void AMBConsumerHandler::APASrv_ParkAidDataHS3UpdateCB(v0::org::harman::ford::actvparkassist_types::ParkAid_Data_HS3_struct p_stParkAidData)
{
    LOG_INFO(LOG_APA, "APASrv_ParkAidDataHS3UpdateCB Received...");
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intApaTrgtDist_D_Stat     = p_stParkAidData.getApaTrgtDist_D_Stat_enum();
        m_pobjContext->m_intApaMsgTxt_D_Rq         = p_stParkAidData.getApaMsgTxt_D_Rq_enum();
        m_pobjContext->m_intApaActvSide2_D_Stat    = p_stParkAidData.getApaActvSide2_D_Stat_enum();
        m_pobjContext->m_intApaAcsy_D_RqDrv        = p_stParkAidData.getApaAcsy_D_RqDrv_enum();
        m_pobjContext->m_intApaScan_D_Stat         = p_stParkAidData.getApaScan_D_Stat_enum();
        m_pobjContext->m_intApaLongCtl_D_RqDrv     = p_stParkAidData.getApaLongCtl_D_RqDrv_enum();
        m_pobjContext->m_intApaGearShif_D_RqDrv    = p_stParkAidData.getApaGearShif_D_RqDrv_enum();
        m_pobjContext->m_eContextApaGearShifStatus = p_stParkAidData.getApaGearShif_D_RqDrv_enum();
        m_pobjContext->m_intApaSteScanMde_D_Stat   = p_stParkAidData.getApaSteScanMde_D_Stat_enum();
        m_pobjContext->m_intApaSelSapp_D_Stat      = p_stParkAidData.getApaSelSapp_D_Stat_enum();
        m_pobjContext->m_intApaSelPpa_D_Stat       = p_stParkAidData.getApaSelPpa_D_Stat_enum();
        m_pobjContext->m_intApaSelPoa_D_Stat       = p_stParkAidData.getApaSelPoa_D_Stat_enum();
        m_pobjContext->m_intApaSys_D_Stat          = p_stParkAidData.getApaSys_D_Stat_enum();
        m_pobjContext->m_eContextApaStatus         = p_stParkAidData.getApaSys_D_Stat_enum();
        m_pobjContext->m_intApaSteWhl_D_RqDrv      = p_stParkAidData.getApaSteWhl_D_RqDrv_enum();


        EParkAssistReqId l_eReqId = e_ParkAssist_APA_PARKAID_HS3_DATA_UPDATE_NTFY;
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
    }
    else
    {
        LOG_ERROR(LOG_APA, "AMBConsumerHandler::APASrv_ParkAidDataHS3UpdateCB ->m_pobjContext is NULL");
    }
}

void AMBConsumerHandler::APASrv_ActiveApaModeUpdate(v0::org::harman::ford::actvparkassist_types::ApaMde_D_Stat_struct p_stActiveFeature)
{
    LOG_INFO(LOG_APA, "APASrv_ActiveApaModeUpdate received...\n");
    
    if(NULL != m_pobjContext)
    {
        if(p_stActiveFeature.getStatus() == 0)
        {
            m_pobjContext->m_intApaMde_D_Stat = p_stActiveFeature.getApaMde_D_Stat_enum();
        }
        else
        {
            LOG_ERROR(LOG_APA, "APASrv_ActiveApaModeUpdate -> Timeout received");
            m_pobjContext->m_intApaMde_D_Stat =  STANDARD_TIMEOUT_AMB_VALUE;
        }
    }

    EParkAssistReqId l_eReqId = e_ParkAssist_APA_ACTIVE_APA_MODE_UPDATE_NTFY;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::ApaGearShif_D_RqDrvStatus(v0::org::harman::ford::actvparkassist_types::ApaGearShif_D_RqDrv_enum p_eApaGearShif_D_RqDrv)
{
    LOG_INFO(LOG_APA, "ApaGearShif_D_RqDrvStatus received...\n");
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intApaGearShif_D_RqDrv = p_eApaGearShif_D_RqDrv;
        m_pobjContext->m_eContextApaGearShifStatus = p_eApaGearShif_D_RqDrv;
    }

    EParkAssistReqId l_eReqId = e_ParkAssist_APA_GEARSHIFT_REQ_DRIVER_STATUS_UPDATE_NTFY;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

// ============================================APA SECTION END===============================================================//


// ============================================PDC SECTION START===============================================================//

void AMBConsumerHandler::CB_getPrkAidMsgTxt_D_Rq_enumAttribute(v0::org::harman::ford::visualparkassist_types::PrkAidMsgTxt_D_Rq_struct p_stPrkAidMsgTxt_D_RqData)
{
    LOG_INFO(LOG_PDC, "CB_getPrkAidMsgTxt_D_Rq_enumAttribute AMB msg:Txt:%d ",(int)p_stPrkAidMsgTxt_D_RqData.getPrkAidMsgTxt_D_Rq_enum());
    if(NULL != m_pobjContext)
    {   
        if(p_stPrkAidMsgTxt_D_RqData.getStatus() == 0)
        {
            m_pobjContext->m_intContextPrkAidMsgTxt = p_stPrkAidMsgTxt_D_RqData.getPrkAidMsgTxt_D_Rq_enum();
            m_pobjContext->m_intApaPrkAidMsgTxt_D_Rq = p_stPrkAidMsgTxt_D_RqData.getPrkAidMsgTxt_D_Rq_enum();
        }
        else
        {
            m_pobjContext->m_intContextPrkAidMsgTxt = STANDARD_TIMEOUT_AMB_VALUE;
            m_pobjContext->m_intApaPrkAidMsgTxt_D_Rq = STANDARD_TIMEOUT_AMB_VALUE;
            //Handle Timeout
        }
    }

    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_MSGTXT_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getPrkAidSnsRlCrnr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsRlCrnr_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getPrkAidSnsRlCrnr_D_Stat_enumAttribute received AMB msg:r1:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextPrkAidSnsRlCrnr = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_RICRNR_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getPrkAidSnsRlCntr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsRlCntr_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getPrkAidSnsRlCntr_D_Stat_enumAttribute received AMB msg:r2:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextPrkAidSnsRlCntr = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_RICNTR_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getPrkAidSnsRrCntr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsRrCntr_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getPrkAidSnsRrCntr_D_Stat_enumAttribute received AMB msg:r3:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextPrkAidSnsRrCntr = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_RRCNTR_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getPrkAidSnsRrCrnr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsRrCrnr_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC, "CB_getPrkAidSnsRrCrnr_D_Stat_enumAttribute received AMB msg:r4:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextPrkAidSnsRrCrnr = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_RRCRNR_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}


void AMBConsumerHandler::CB_getPrkAidSnsFlCrnr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsFlCrnr_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getPrkAidSnsFlCrnr_D_Stat_enumAttribute received AMB msg:f1:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextPrkAidSnsFlCrnr = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_FICRNR_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getPrkAidSnsFlCntr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsFlCntr_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getPrkAidSnsFlCntr_D_Stat_enumAttribute received AMB msg:f2:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextPrkAidSnsFlCntr = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_FICNTR_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getPrkAidSnsFrCntr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsFrCntr_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getPrkAidSnsFrCntr_D_Stat_enumAttribute received AMB msg:f3:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextPrkAidSnsFrCntr = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_FRCNTR_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getPrkAidSnsFrCrnr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsFrCrnr_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getPrkAidSnsFrCrnr_D_Stat_enumAttribute received AMB msg:f4:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextPrkAidSnsFrCrnr = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_FRCRNR_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getSidePrkSnsL1_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsL1_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getSidePrkSnsL1_D_Stat_enumAttribute received AMB msg:l1:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextSidePrkSnsL1 = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_L1_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getSidePrkSnsL2_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsL2_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getSidePrkSnsL2_D_Stat_enumAttribute received AMB msg:l2:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextSidePrkSnsL2 = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_L2_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);       
}

void AMBConsumerHandler::CB_getSidePrkSnsL3_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsL3_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getSidePrkSnsL3_D_Stat_enumAttribute received AMB msg:l3:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextSidePrkSnsL3 = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_L3_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getSidePrkSnsL4_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsL4_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getSidePrkSnsL4_D_Stat_enumAttributes received AMB msg:l4:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextSidePrkSnsL4 = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_L4_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}


void AMBConsumerHandler::CB_getSidePrkSnsR1_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsR1_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getSidePrkSnsR1_D_Stat_enumAttribute received AMB msg:rt1:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextSidePrkSnsR1 = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_R1_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getSidePrkSnsR2_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsR2_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getSidePrkSnsR2_D_Stat_enumAttribute received AMB msg:rt2:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextSidePrkSnsR2 = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_R2_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getSidePrkSnsR3_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsR3_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getSidePrkSnsR3_D_Stat_enumAttribute received AMB msg:rt3:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextSidePrkSnsR4 = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_R3_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}

void AMBConsumerHandler::CB_getSidePrkSnsR4_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsR4_D_Stat_enum value)
{
    LOG_INFO(LOG_PDC,"CB_getSidePrkSnsR4_D_Stat_enumAttribute received AMB msg:rt4:%d ",(int)value);
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_intContextSidePrkSnsR4 = value;
    }
    EParkAssistReqId l_eReqId = e_ParkAssist_VPA_PARKAID_SENSOR_R4_UPDATE;
    CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
}




// ============================================PDC SECTION END===============================================================//

/**
    *@brief De initializing all variable of component
    @param  None
*/
void AMBConsumerHandler::Deinitialize()
{

}


