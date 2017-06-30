/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            ParkAssistReqManager.cpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           AMBConsumerHandler Consumes events from AMB and routes to required module(RVC,APA and VPA)
*                  based on the events it received.
*                  
*/


#include "ParkAssistReqManager.hpp"
#include "ParkAssistSrv_Manager/CPAMPresctrl.hpp"
using namespace v0::org::harman::ford;
using namespace v2::org::genivi::NodeStateManager;

// TODO:-  Has to be changed based on RVC Status
#define VPA_w_bigger 152
#define VPA_h_bigger 228 
#define VPA_w_smaller 152
#define VPA_h_smaller 228
#define VPA_x_bigger ((800/2) - (VPA_w_bigger/2))
#define VPA_y_bigger ((480/2) - (VPA_h_bigger/2)) 
#define VPA_x_smaller (640)
#define VPA_y_smaller (240)

// ============================================RVC SECTION START===============================================================//

/**
    @brief process the Zoom Request from HMI and request to AMB
    @param:none
 */
void ZoomRequest::onRun()
{
    bool l_bZoomReq = false;
    LOG_INFO(LOG_RVC, "Zoom Request CB...");
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if(NULL != l_pobjPAMPresCtrl)
    {
        if(ParkAssistBaseType::enRVCZoom::RVC_Zoom_Off_Request == l_pobjPAMPresCtrl->m_pobjRVCServiceStub->getRVCZoomOnOffAttribute())
        {
            LOG_INFO(LOG_RVC, "Disabling Zoom..");
            l_bZoomReq = false;
        }
        else if(ParkAssistBaseType::enRVCZoom::RVC_Zoom_On_Request == l_pobjPAMPresCtrl->m_pobjRVCServiceStub->getRVCZoomOnOffAttribute())
        {
            LOG_INFO(LOG_RVC, "Enabling Zoom..");
            l_bZoomReq = true;
        }

        l_pobjPAMPresCtrl->m_AMBProviderHandler.SetRVCZoom(l_bZoomReq);

    }

    setCompleted();
    removeMe();
}

void ZoomRequest::onCancelled()
{
    removeMe();
}

/**
    @brief process the Split View Request from HMI and request to AMB
    @param:none
 */
void SplitViewRequest::onRun()
{
    bool l_bSplitViewReq = false;
    LOG_INFO(LOG_RVC, "Split View Request CB...");
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        if(ParkAssistBaseType::enRVCSplitView::RVC_SplitView_Off_Request == l_pobjPAMPresCtrl->m_pobjRVCServiceStub->getRVCSpiltViewOnOffAttribute())
        {
            LOG_INFO(LOG_RVC, "Disabling Split View request to camera ");
            l_bSplitViewReq = false;
        }
        else if(ParkAssistBaseType::enRVCSplitView::RVC_SplitView_on_Request == l_pobjPAMPresCtrl->m_pobjRVCServiceStub->getRVCSpiltViewOnOffAttribute())
        {
            LOG_INFO(LOG_RVC, "Enabling  Split View request to camera");
            l_bSplitViewReq = true;
        }

        l_pobjPAMPresCtrl->m_AMBProviderHandler.SetRVCSplitView(l_bSplitViewReq);

    }

    setCompleted();
    removeMe();
}

void SplitViewRequest::onCancelled()
{
    removeMe();
}


/**
    @brief process the enhanced mode request from HMI and request to AMB
    @param:none
 */
void EnhancedParkModeRequest::onRun()
{
    bool l_bEhcViewReq = false;
    LOG_INFO(LOG_RVC, "Enhanced Mode Request");
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        l_bEhcViewReq = l_pobjPAMPresCtrl->m_pobjRVCServiceStub->getRVCEnhancedPrkAidAttribute();
        l_pobjPAMPresCtrl->m_AMBProviderHandler.SetEnhancedParkMode(l_bEhcViewReq);
    }

    setCompleted();
    removeMe();
}

void EnhancedParkModeRequest::onCancelled()
{
    removeMe();
}

/**
    @Brief:set the fixed Camera setting value
    @param  None
 */
void FixedCameraSetting::onRun()
{
    LOG_INFO(LOG_RVC, "Zoom Request CB...");
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            break;
        }
        //Setting static guideline always on
        LOG_INFO(LOG_RVC,"Setting static guideline and dynamic guideline as on");
        l_pobjPAMPresCtrl->m_AMBProviderHandler.SetStaticGuideLine();
    
        //Setting Dynamic guideline always on
        l_pobjPAMPresCtrl->m_AMBProviderHandler.SetDyanamicGuideLine();
        
        //Set Centrer guideline always on
        l_pobjPAMPresCtrl->m_AMBProviderHandler.SetCentreGuideLine();

    }while(0);

    setCompleted();
    removeMe();
}

void FixedCameraSetting::onCancelled()
{
    removeMe();
}

void VehicleCharNtfy::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "VehicleCharNtfy::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->CamraOvrlStat(l_pobjPAMPresCtrl->m_objContext.m_intContextCamraOvrlStat);
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->CamraOvrlDyn(l_pobjPAMPresCtrl->m_objContext.m_intContextCamraOvrlDyn);
    }

    setCompleted();
    removeMe();
}
void VehicleCharNtfy::onCancelled()
{
    removeMe();
}

void PDCGuideStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "PDCGuideStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->CamPDCGuidStat(l_pobjPAMPresCtrl->m_objContext.m_intContextCamPDCGuidStat); 
    }

    setCompleted();
    removeMe();
}

void PDCGuideStatus::onCancelled()
{
    removeMe();
}

void CameraZoomStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "CameraZoomStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->ProcessZoomResponce(l_pobjPAMPresCtrl->m_objContext.m_intContextCamraZoom);
    }

    setCompleted();
    removeMe();
}

void CameraZoomStatus::onCancelled()
{
    removeMe();
}

void CameraSplitViewStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "CameraSplitViewStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->ProcessSplitViewResponce(l_pobjPAMPresCtrl->m_objContext.m_intContextCamraSplitView);
    }

    setCompleted();
    removeMe();
}

void CameraSplitViewStatus::onCancelled()
{
    removeMe();
}
void ElecBrkStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "ElecBrkStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->ProcessElecBrkStatuResponce(l_pobjPAMPresCtrl->m_objContext.m_eContextElePrkStatus);
    }

    setCompleted();
    removeMe();
}

void ElecBrkStatus::onCancelled()
{
    removeMe();
}


void CurrentGearPostion::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "CurrentGearPostion::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->NotifyGearPostion(l_pobjPAMPresCtrl->m_objContext.m_eContextGearLvrPos);
    }

    setCompleted();
    removeMe();
}
void CurrentGearPostion::onCancelled()
{
    removeMe();
}


void VehicleSpeedNotify::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "VehicleSpeedNotify::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->UpdateCameraSpeedState(l_pobjPAMPresCtrl->m_objContext.m_bContextCameraMaxSpeed);
    }

    setCompleted();
    removeMe();
}
void VehicleSpeedNotify::onCancelled()
{
    removeMe();
}


void ParkBrkActvStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "ParkBrkActvStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->NotifyParkBrkStatus(l_pobjPAMPresCtrl->m_objContext.m_eContextPrkBrkActvStatus);
    }

    setCompleted();
    removeMe();
}
void ParkBrkActvStatus::onCancelled()
{
    removeMe();
}

void DoorOpenStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "DoorOpenStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->UpdateVehicelTrunkStatus(l_pobjPAMPresCtrl->m_objContext.m_eContextDoorOpenStatus);
    }

    setCompleted();
    removeMe();
}
void DoorOpenStatus::onCancelled()
{
    removeMe();
}

void NsmStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "NsmStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->UpdateNSMState(l_pobjPAMPresCtrl->m_objContext.m_bContextNsmSessionState);
    }

    setCompleted();
    removeMe();
}
void NsmStatus::onCancelled()
{
    removeMe();
}

void ManualGearStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "ManualGearStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->UpdateManualGearStatus(l_pobjPAMPresCtrl->m_objContext.m_eRevGearStatus);
    }

    setCompleted();
    removeMe();
}
void ManualGearStatus::onCancelled()
{
    removeMe();
}

void IgnStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub)
    {
        LOG_INFO(LOG_RVC, "IgnStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->UpdateIgnitionState(l_pobjPAMPresCtrl->m_objContext.m_bContextIgnStatus);
    }

    setCompleted();
    removeMe();
}

void IgnStatus::onCancelled()
{
    removeMe();
}


// ============================================RVC SECTION END===============================================================//



// ============================================APA SECTION START===============================================================//

void ParkAidHS3DataUpdate::APASystemStatusUpdate()
{
    
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enAPAStatus l_eAPAStatus = v1::com::harman::ParkAssist::APABaseType::enAPAStatus::e_APA_On;
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        LOG_INFO(LOG_RVC, "APASystemStatusUpdate::onRun() called \n");
        if(l_pobjPAMPresCtrl->m_objContext.m_bContextIsAPASupported)
        {
            if((l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat == 1)  || 
                (0 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) || (7 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat))
            {
                l_eAPAStatus = v1::com::harman::ParkAssist::APABaseType::enAPAStatus::e_APA_Off;
                l_pobjPAMPresCtrl->m_objContext.m_bIsAPAOn = false;
                l_pobjPAMPresCtrl->m_pobjRVCServiceStub->RVCSwitchOffByAPA();
            }
            else
            {
                l_pobjPAMPresCtrl->m_objContext.m_bIsAPAOn = true;
            }
            
            l_pobjPAMPresCtrl->m_pobjAPAStub->setAPAStatusAttribute(l_eAPAStatus);
        }   

        if(l_pobjPAMPresCtrl->m_objContext.m_bContextIsRVCSupported)
        {
            l_pobjPAMPresCtrl->m_pobjRVCServiceStub->UpdateAPASystemStatus(l_pobjPAMPresCtrl->m_objContext.m_eContextApaStatus);
        }   
  
    }

}

void ParkAidHS3DataUpdate::onRun()
{
    LOG_INFO(LOG_APA, "SappSupportUpdate::onRun()");

    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    APASystemStatusUpdate();
    ScanStatusUpdate();
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        l_pobjPAMPresCtrl->m_pobjAPAStub->UpdateAPAFeatureAvailabilityToHMI();
        LOG_INFO(LOG_APA, "Table Parsing Starts");
        l_pobjPAMPresCtrl->m_pobjAPAStub->ParseAllTables();
        
    }
    setCompleted();
    removeMe();
}
void ParkAidHS3DataUpdate::onCancelled()
{
    removeMe();
}

void ParkAidHS3DataUpdate::ScanStatusUpdate()
{
    LOG_INFO(LOG_APA, "ScanStatusUpdate::onRun()");
    
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            l_pobjPAMPresCtrl->m_objContext.m_bIsScanInProgress = true;// to use in table where stescan other than 2 is not allowed
        }
        else
        {
            l_pobjPAMPresCtrl->m_objContext.m_bIsScanInProgress = false; // to use in table where stescan other than 2 is not allowed
        }
    }

}
void ActiveApaModeUpdate::onRun()
{
    LOG_INFO(LOG_APA, "ActiveApaModeUpdate::onRun()");

    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ActiveApaModeUpdate::onRun() -> l_pobjPAMPresCtrl is nULL");
            break;
        }
        if(STANDARD_TIMEOUT_AMB_VALUE == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
        {
            LOG_ERROR(LOG_APA, "ActiveApaModeUpdate::onRun() -> m_intApaMde_D_Stat Timeout and apa status is %d", l_pobjPAMPresCtrl->m_objContext.m_bIsAPAOn);
            if(l_pobjPAMPresCtrl->m_objContext.m_bIsAPAOn)
            {
                l_pobjPAMPresCtrl->m_pobjAPAStub->setAPAErrorStatusAttribute(true);
                break;
            }
        }
        if(NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
        {
            l_pobjPAMPresCtrl->m_pobjAPAStub->setAPAErrorStatusAttribute(false);
            v1::com::harman::ParkAssist::APABaseType::enAPAMode l_eCurrentApaMode = 
                v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Off;
            int l_ApaMdeStat = l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat;
            if(1 == l_ApaMdeStat)
            {
                l_pobjPAMPresCtrl->m_pobjAPAStub->setAPAStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enAPAStatus::e_APA_Off);
            }
            if(2 == l_ApaMdeStat)
            {
                l_eCurrentApaMode = v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Sapp;
            }
            if(3 == l_ApaMdeStat)
            {
                l_eCurrentApaMode = v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Ppa;
            }
            if(4 == l_ApaMdeStat)
            {
                l_eCurrentApaMode = v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Poa;
            }
            v1::com::harman::ParkAssist::APABaseType::APAViewType l_stAPAViewType ;
            memset(&l_stAPAViewType, 0, sizeof(l_stAPAViewType));
            l_stAPAViewType.setM_eAPAMode(l_eCurrentApaMode);

            v1::com::harman::ParkAssist::APABaseType::enAPAViewType l_eAPAViewType = v1::com::harman::ParkAssist::APABaseType::enAPAViewType::e_Invalid;
            if(true == l_pobjPAMPresCtrl->m_objContext.m_bContextIsRVCSupported)
            {
                if(true == l_pobjPAMPresCtrl->m_objContext.m_bIsRVCOn)
                {
                    l_eAPAViewType = v1::com::harman::ParkAssist::APABaseType::enAPAViewType::e_RVC_With_CameraImage;
                }
                else
                {
                    l_eAPAViewType = v1::com::harman::ParkAssist::APABaseType::enAPAViewType::e_RVC_Without_CameraImage;
                }
            }
            else
            {
                l_eAPAViewType = v1::com::harman::ParkAssist::APABaseType::enAPAViewType::e_WithoutRVC;
            }
            l_stAPAViewType.setM_eAPAViewType(l_eAPAViewType);
            LOG_INFO(LOG_APA, "Camera Info Data to HMI is %d %d", l_stAPAViewType.getM_eAPAMode(), l_stAPAViewType.getM_eAPAViewType());
            l_pobjPAMPresCtrl->m_pobjAPAStub->setObjApaViewTypeAttribute(l_stAPAViewType);
            l_pobjPAMPresCtrl->m_pobjAPAStub->setCurrentApaActiveModeAttribute(l_eCurrentApaMode);
            l_pobjPAMPresCtrl->m_pobjAPAStub->ApaMde_D_StatToTableMapping();
        }
    }while(0);

    setCompleted();
    removeMe();
}
void ActiveApaModeUpdate::onCancelled()
{
    removeMe();
}
void GearShiftReqDriverStatus::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjRVCServiceStub && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        LOG_INFO(LOG_RVC, "IgnStatus::onRun() called \n");
        l_pobjPAMPresCtrl->m_pobjRVCServiceStub->UpdateAPAGearStatus(l_pobjPAMPresCtrl->m_objContext.m_eContextApaGearShifStatus);
        l_pobjPAMPresCtrl->m_pobjAPAStub->ApaGearShif_D_RqDrvToTableMapping();
    }
    else
    {
        LOG_ERROR(LOG_APA, "GearShiftReqDriverStatus::onRun() ->  l_pobjPAMPresCtrl is NULL");
    }
    setCompleted();
    removeMe();

}
void GearShiftReqDriverStatus::onCancelled()
{
    removeMe();
}

void SetApaModeReq::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum l_eAPAModeReqToAMB = 
        v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum::En_Inactive;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            break;
        }
        LOG_INFO(LOG_APA, "SetApaModeReq::onRun() Data is >> %d", l_pobjPAMPresCtrl->m_objContext.m_eContextAPAModeReq);
        if(v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Off == l_pobjPAMPresCtrl->m_objContext.m_eContextAPAModeReq)
        {
            // TODO:- Remove Set HMI Attribute And add it in ApaMde_D_Stat_enumCB()
            l_eAPAModeReqToAMB = v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum::En_Off;
            l_pobjPAMPresCtrl->m_objContext.m_bIsAPAOn = false;
            l_pobjPAMPresCtrl->m_pobjAPAStub->setAPAStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enAPAStatus::e_APA_Off);
            l_pobjPAMPresCtrl->m_pobjRVCServiceStub->RVCSwitchOffByAPA();
            break;
        }
        if(v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Sapp == l_pobjPAMPresCtrl->m_objContext.m_eContextAPAModeReq)
        {
            l_eAPAModeReqToAMB = v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum::En_SAPP;
            break;
        }
        if(v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Ppa == l_pobjPAMPresCtrl->m_objContext.m_eContextAPAModeReq)
        {
            l_eAPAModeReqToAMB = v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum::En_PPA;
            break;
        }
        if(v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Poa == l_pobjPAMPresCtrl->m_objContext.m_eContextAPAModeReq)
        {
            l_eAPAModeReqToAMB = v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum::En_POA;
            break;
        }

        l_pobjPAMPresCtrl->m_AMBProviderHandler.APAModeReqToAMB(l_eAPAModeReqToAMB);
        

    }while(0);

    setCompleted();
    removeMe();
}
void SetApaModeReq::onCancelled()
{
    removeMe();
}

// ============================================APA SECTION END===============================================================//


// ============================================PDC SECTION START===============================================================//

void ParkAidMsgTxtUpdate::onRun()
{

    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    
    do
    {
        if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord && NULL != l_pobjPAMPresCtrl->m_PDCServiceStub)
        {
            //Verifying Eol Parameter
            if(l_pobjPAMPresCtrl->m_objContext.m_bIsPDCSupported)
            {
                if(STANDARD_TIMEOUT_AMB_VALUE == l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidMsgTxt)
                {
                    LOG_ERROR(LOG_PDC, "ParkAidMsgTxtUpdate::onRun() -> Timeout received and pdc status is %d", l_pobjPAMPresCtrl->m_objContext.m_bIsPDCOn);
                    if(l_pobjPAMPresCtrl->m_objContext.m_bIsPDCOn)
                    {
                        l_pobjPAMPresCtrl->m_PDCServiceStub->setPDCErrorStatusAttribute(true);
                        l_pobjPAMPresCtrl->m_objContext.m_bIsPDCOn = false;
                        l_pobjPAMPresCtrl->m_PDCServiceStub->PDCStatusChangeNotify(false);// setting the attribute to off for Time out case
                        break;
                    }
                }
                
                l_pobjPAMPresCtrl->m_PDCServiceStub->setPDCErrorStatusAttribute(false);
                bool l_bPDCStatus = false;
                LOG_INFO(LOG_PDC, "ParkAidMsgTxtUpdate::onRun() called \n");
                l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORTXT, PDCServiceFord::ePDCMSG, (int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidMsgTxt);
                l_bPDCStatus = l_pobjPAMPresCtrl->m_PDCServiceFord->bGetPDCState();
                l_pobjPAMPresCtrl->m_objContext.m_bIsPDCOn = l_bPDCStatus;
                CalculatePDCScreenLayout(l_bPDCStatus);
                l_pobjPAMPresCtrl->m_PDCServiceStub->PDCStatusChangeNotify(l_bPDCStatus);
                LOG_INFO(LOG_PDC, "Park-aid message :: %d l_bPDCStatus :%d\n",l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidMsgTxt,l_bPDCStatus);
            }  
            
            if(l_pobjPAMPresCtrl->m_objContext.m_bIsAPAOn == true)
            {
                 l_pobjPAMPresCtrl->m_pobjAPAStub->ParsePrkAidMsgTxtTables();
                 LOG_INFO(LOG_PDC, "ParkAidMsgTxtUpdate::APA is on  \n");
            
            }


        
        }
    }while(0);

    
    setCompleted();
    removeMe();
}
void ParkAidMsgTxtUpdate::onCancelled()
{
    removeMe();
}
void ParkAidMsgTxtUpdate::CalculatePDCScreenLayout(bool p_bPDCStatus)
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    LOG_INFO(LOG_PDC, "CalculatePDCScreenLayout Enetr\n");
    int l_Guideline;
    do
    {
        if(true == p_bPDCStatus)
        {
            if(NULL == l_pobjPAMPresCtrl)
            {
                break;
            }

            if(true == l_pobjPAMPresCtrl->m_objContext.m_bIsRVCOn)
            {
                //If RVC and PDC is ON, No need check for APA ,
                //PDC image will be always right

                l_Guideline= (int)PDCServiceFord::eGUIDELINETXT_OFF; 
                l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&l_Guideline);
                l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPASize(VPA_w_smaller, VPA_h_smaller);//to be desided by camera team
                l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPALeftBottom(VPA_x_smaller, VPA_y_smaller);//deside by camera team 
                LOG_INFO(LOG_PDC, "ManageScreenPositioning RVC and PDC ON...\n");
                

            }
            else if(true == l_pobjPAMPresCtrl->m_objContext.m_bIsAPAOn)
            {
                l_Guideline = (int)PDCServiceFord::eGUIDELINETXT_OFF; 
                l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&l_Guideline);
               //Coordinates For PDC to be set when APA is on
               //l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPASize(VPA_w_smaller, VPA_h_smaller);//to be desided by camera team
               //l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPALeftBottom(VPA_x_smaller, VPA_y_smaller);//deside by camera team 
                LOG_INFO(LOG_PDC, "ManageScreenPositioning RVC APA and  PDC ON...\n");
            
            }
            else
            {
                //Dedicated PDC
                //Should be turned on once AMB provides left and right radius signal
                l_Guideline = (int)PDCServiceFord::eGUIDELINETXT_ON; 
                l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&l_Guideline);
                l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPASize(VPA_w_bigger, VPA_h_bigger);//to be desided by camera team
                l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPALeftBottom(VPA_x_bigger, VPA_y_bigger);//deside by camera team 
                LOG_INFO(LOG_PDC, "ManageScreenPositioning Only PDC IS ON...\n");
            }
        }   

    }while(0);

}

void ParkAidSensorRiCrnrUpdate::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCRNR,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidSnsRlCrnr);
    }
    
    setCompleted();
    removeMe();
}
void ParkAidSensorRiCrnrUpdate::onCancelled()
{
    removeMe();
}
void ParkAidSensorRiCntrUpdate::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARLEFTCNTR,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidSnsRlCntr);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorRiCntrUpdate::onCancelled()
{
    removeMe();
}
void ParkAidSensorRrCntrUpdate::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARRIGHTCNTR,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidSnsRrCntr);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorRrCntrUpdate::onCancelled()
{
    removeMe();
}
void ParkAidSensorRrCrnrUpdate::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eREARRIGHTCRNR,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidSnsRrCrnr);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorRrCrnrUpdate::onCancelled()
{
    removeMe();
}
void ParkAidSensorFiCrnrUpdate::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTLEFTCRNR,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidSnsFlCrnr);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorFiCrnrUpdate::onCancelled()
{
    removeMe();
}
void ParkAidSensorFrCrnrUpdate::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTLEFTCNTR,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidSnsFlCntr);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorFrCrnrUpdate::onCancelled()
{
    removeMe();
}
void ParkAidSensorFrCntrUpdate::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {

        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTRIGHTCNTR,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidSnsFrCntr);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorFrCntrUpdate::onCancelled()
{
    removeMe();
}
void ParkAidSensorFiCntrUpdate::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {

        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eFRONTRIGHTCRNR,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextPrkAidSnsFrCrnr);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorFiCntrUpdate::onCancelled()
{
    removeMe();
}
void ParkAidSensorL1Update::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT1,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextSidePrkSnsL1);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorL1Update::onCancelled()
{
    removeMe();
}
void ParkAidSensorL2Update::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT2,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextSidePrkSnsL2);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorL2Update::onCancelled()
{
    removeMe();
}
void ParkAidSensorL3Update::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT3,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextSidePrkSnsL3);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorL3Update::onCancelled()
{
    removeMe();
}
void ParkAidSensorL4Update::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDELEFT4,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextSidePrkSnsL4);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorL4Update::onCancelled()
{
    removeMe();
}
void ParkAidSensorR1Update::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDERIGHT1,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextSidePrkSnsR1);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorR1Update::onCancelled()
{
    removeMe();
}
void ParkAidSensorR2Update::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDERIGHT2,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextSidePrkSnsR2);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorR2Update::onCancelled()
{
    removeMe();
}
void ParkAidSensorR3Update::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDERIGHT3,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextSidePrkSnsR3);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorR3Update::onCancelled()
{
    removeMe();
}
void ParkAidSensorR4Update::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eSENSORDISTANCE,PDCServiceFord::eSIDERIGHT4,(int*)&l_pobjPAMPresCtrl->m_objContext.m_intContextSidePrkSnsR4);
    }
    setCompleted();
    removeMe();
}
void ParkAidSensorR4Update::onCancelled()
{
    removeMe();
}


void CancelPDCReq::onRun()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    LOG_INFO(LOG_PDC, "CancelPDCReq::onRun() Called...\n");
    if(NULL != l_pobjPAMPresCtrl &&  NULL != l_pobjPAMPresCtrl->m_PDCServiceFord)
    {
        if(true == l_pobjPAMPresCtrl->m_PDCServiceFord->bGetPDCState())
        {
            l_pobjPAMPresCtrl->m_PDCServiceFord->SetPDCViewState(false);
            l_pobjPAMPresCtrl->m_objContext.m_bIsPDCOn = false;
            l_pobjPAMPresCtrl->m_PDCServiceStub->PDCStatusChangeNotify(false);// setting the attribute to off for Time out case            LOG_INFO(LOG_PDC, "SetPDCViewState Stop called...\n");
        }
        else
        {
            LOG_INFO(LOG_PDC, "PDC Is Already Off ..\n");
        }
    }
    setCompleted();
    removeMe();
}
void CancelPDCReq::onCancelled()
{
    removeMe();
}

// ============================================PDC SECTION END===============================================================//

//==================================================COMMON======================================================================//
void ManageScreenPositioning::onRun()
{
    LOG_INFO(LOG_PDC, "ManageScreenPositioning::onRun() Called...\n");
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    int l_Guideline;
    // Logic to handle screen positioning

    do
    {
        if(NULL == l_pobjPAMPresCtrl &&  NULL == l_pobjPAMPresCtrl->m_PDCServiceFord && NULL == l_pobjPAMPresCtrl->m_PDCServiceStub)
        {
            break;
        }

        if(true == l_pobjPAMPresCtrl->m_objContext.m_bIsPDCOn)
        {
            //IF RVC is off , The PDC car image depends on whether APA is on or off
            if(true == l_pobjPAMPresCtrl->m_objContext.m_bIsRVCOn)
            {
                //If RVC and PDC is ON, No need check for APA ,
                //PDC image will be always right

                l_Guideline= (int)PDCServiceFord::eGUIDELINETXT_OFF; 
                l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&l_Guideline);
                l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPASize(VPA_w_smaller, VPA_h_smaller);//to be desided by camera team
                l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPALeftBottom(VPA_x_smaller, VPA_y_smaller);//deside by camera team 
                LOG_INFO(LOG_PDC, "ManageScreenPositioning RVC and PDC ON...\n");
                

            }
            else if(true == l_pobjPAMPresCtrl->m_objContext.m_bIsAPAOn)
            {
                l_Guideline = (int)PDCServiceFord::eGUIDELINETXT_OFF; 
                l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&l_Guideline);
               //Coordinates For PDC to be set when APA is on
               //l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPASize(VPA_w_smaller, VPA_h_smaller);//to be desided by camera team
               //l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPALeftBottom(VPA_x_smaller, VPA_y_smaller);//deside by camera team 
                LOG_INFO(LOG_PDC, "ManageScreenPositioning RVC APA and  PDC ON...\n");
            
            }
            else
            {
                //Dedicated PDC
                //Should be turned on once AMB provides left and right radius signal
                l_Guideline = (int)PDCServiceFord::eGUIDELINETXT_ON; 
                l_pobjPAMPresCtrl->m_PDCServiceFord->pushPDCMsg(PDCServiceFord::eGUIDELINECMD,PDCServiceFord::eGUIDELINESTATE,(int*)&l_Guideline);
                l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPASize(VPA_w_bigger, VPA_h_bigger);//to be desided by camera team
                l_pobjPAMPresCtrl->m_PDCServiceFord->bSetVPALeftBottom(VPA_x_bigger, VPA_y_bigger);//deside by camera team 
                LOG_INFO(LOG_PDC, "ManageScreenPositioning Only PDC IS ON...\n");
            }
            // TODO:- check for APA Status
        }
        
    }while(0);

    setCompleted();
    removeMe();
}
void ManageScreenPositioning::onCancelled()
{
    removeMe();
}


