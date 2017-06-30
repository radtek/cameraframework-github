/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            CPresCoreHandler.cpp
* @ingroup         Park-Asist
* @author          Trilokesh Pradhan, Atita Halemani and Ashwini Shamaprasad (trilokesh.ranjan@harman.com, Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           CPresCoreHandler Consumes events from PresCore and routes to required module(RVC,APA and VPA)
*                  based on the events it received.
*                  
*/

#include "CPresCoreHandler.hpp"
#include "ParkAssistSrv_Common/ParkAssistReqManager.hpp"

CPresCoreHandler * CPresCoreHandler::m_pobjCPresCoreHandler = NULL;
CPresCoreHandler::CPresCoreHandler()
{
    LOG_INFO(LOG_COMMON,"CPresCoreHandler constructor");
	l_PtrReqBase = NULL;

}

CPresCoreHandler:: ~CPresCoreHandler()
{

}

CPresCoreHandler* CPresCoreHandler::getInstance()
{ 
    if(NULL == m_pobjCPresCoreHandler)
    {
        m_pobjCPresCoreHandler = new CPresCoreHandler;
    }
    return m_pobjCPresCoreHandler;
}
void CPresCoreHandler::addRequestToPresCore(EParkAssistReqId p_peParkAssistReqId)
{
    LOG_INFO(LOG_COMMON, "addRequestToPresCore Called and reqId is %d", p_peParkAssistReqId);
    PresCtrl::addRequest(p_peParkAssistReqId, std::bind(&CPresCoreHandler::CreateRequest, this, p_peParkAssistReqId));
}

RequestBase * CPresCoreHandler::CreateRequest(EParkAssistReqId p_peParkAssistReqId)
{
    // returning derive class object based on the event type

    LOG_INFO(LOG_COMMON, "CreateRequest Called and reqId is %d", p_peParkAssistReqId);
    do
    {
        if(e_ParkAssist_RVC_ZOOM_REQUEST == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ZoomRequest>();
            break;
        }
        if(e_ParkAssist_RVC_VEHICLE_CHAR_NTFY == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<VehicleCharNtfy>();
            break;
        }
        if(e_ParkAssist_RVC_SPLITVIEW_REQUEST == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<SplitViewRequest>();
            break;
        }
        if(e_ParkAssist_RVC_ENHANCEDMODE_REQUEST == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<EnhancedParkModeRequest>();
            break;
        }
        if(e_ParkAssist_RVC_GUIDELINES_REQUEST == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<FixedCameraSetting>();
            break;
        }
        if (e_ParkAssist_RVC_GEAR_POSTION == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<CurrentGearPostion>();
            break;
        }
        if(e_ParkAssist_APA_SET_APAMODE_REQ == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<SetApaModeReq>();
            break;
        }

        if(e_ParkAssist_APA_ACTIVE_APA_MODE_UPDATE_NTFY == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ActiveApaModeUpdate>();
            break;
        }

        if(e_ParkAssist_APA_GEARSHIFT_REQ_DRIVER_STATUS_UPDATE_NTFY == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<GearShiftReqDriverStatus>();
            break;
        }

        if(e_ParkAssist_RVC_VEHICLE_MAXSPEED == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<VehicleSpeedNotify>();
            break;
        }
        if(e_ParkAssist_RVC_PARK_BREAK_ACTIVE_STATUS == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<ParkBrkActvStatus>();
            break;
        }
        if(e_ParkAssist_RVC_DOOR_OPEN_STATUS == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<DoorOpenStatus>();
            break;
        }
        if(e_ParkAssist_RVC_NSM_STATUS == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<NsmStatus>();
            break;
        }
        if(e_ParkAssist_RVC_MANUAL_GEAR_STATUS == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<ManualGearStatus>();
            break;
        }
        if(e_ParkAssist_RVC_IGNITION_STATUS == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<IgnStatus>();
            break;
        }
		
		if(e_ParkAssist_RVC_SPLITVIEW_RESPONSE == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<CameraSplitViewStatus>();
            break;
        }
		
		if(e_ParkAssist_RVC_ELEC_PARK_BREAK_STATUS == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<ElecBrkStatus>();
            break;
        }

        if(e_ParkAssist_APA_PARKAID_HS3_DATA_UPDATE_NTFY == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<ParkAidHS3DataUpdate>();
            break;
        }

        //=========================================== PDC====================================================================
        if(e_ParkAssist_VPA_PARKAID_MSGTXT_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidMsgTxtUpdate>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_RICRNR_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorRiCrnrUpdate>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_RICNTR_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorRiCntrUpdate>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_RRCNTR_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorRrCntrUpdate>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_RRCRNR_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorRrCrnrUpdate>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_FICRNR_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorFiCrnrUpdate>();
            break;
        }


        if(e_ParkAssist_VPA_PARKAID_SENSOR_FRCRNR_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorFrCrnrUpdate>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_FRCNTR_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorFrCntrUpdate>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_FICNTR_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorFiCntrUpdate>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_L1_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorL1Update>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_L2_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorL2Update>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_L3_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorL3Update>();
            break;
        }

        if(e_ParkAssist_VPA_PARKAID_SENSOR_L4_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorL4Update>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_R1_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorR1Update>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_R2_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorR2Update>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_R3_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorR3Update>();
            break;
        }
        if(e_ParkAssist_VPA_PARKAID_SENSOR_R4_UPDATE == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<ParkAidSensorR4Update>();
            break;
        }
        if(e_ParkAssist_VPA_CANCEL_PDC_REQUEST == p_peParkAssistReqId)
        {
            l_PtrReqBase = std::make_shared<CancelPDCReq>();
            break;
        }


       // ============================================COMMON==========================================================//
            
        if(e_ParkAssist_MANAGE_SCREEN_POSITION == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<ManageScreenPositioning>();
            break;
        }
        if(e_ParkAssist_RVC_PDC_GUIDE_STATUS == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<PDCGuideStatus>();
            break;
        }
        if(e_ParkAssist_RVC_CAMERA_ZOOM_STATUS == p_peParkAssistReqId)
        {
			l_PtrReqBase = std::make_shared<CameraZoomStatus>();
            break;
        }
    }while(0);


    return (l_PtrReqBase.get());

}
