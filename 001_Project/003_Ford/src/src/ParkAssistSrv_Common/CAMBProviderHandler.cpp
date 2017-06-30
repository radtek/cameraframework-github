/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            CAMBProviderHandler.cpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           CAMBProviderHandler provide the interface to RVC,APA ,VPA and in turn requests events to AMB 
*                  
*/

#include"CAMBProviderHandler.hpp"

using namespace std::placeholders;

CAMBProviderHandler:: CAMBProviderHandler() :m_pobjAMBCamerainfoProxy(nullptr), m_pobjAMBBodyCntlInfoProxy(nullptr),m_AMBApaPxy(nullptr)
{
    LOG_INFO(LOG_COMMON,"CAMBProviderHandler constructor");

}


CAMBProviderHandler::~CAMBProviderHandler()
{
    LOG_INFO(LOG_COMMON,"CAMBProviderHandler Destructor");
}

/**
* @brief Function to initialise  CAMBProviderHandler and providing interface to set AMBCameraInfo handle
* @param  camerainfoProxy - to get Shared pointer of camerainfoProxy interface
*/
void CAMBProviderHandler::InitializeAMBProviderHandler(std::shared_ptr<camerainfoProxy<>> &p_pobjAMBCameraInfo, std::shared_ptr<bodycontroldataProxy<>> &p_pobjAMB_BodyCntlInfoProxy,
                                                                std::shared_ptr<actvparkassistProxy<>> &p_pobjAMBApaPxy)
{
    if(NULL != p_pobjAMBCameraInfo && NULL != p_pobjAMB_BodyCntlInfoProxy && NULL != p_pobjAMBApaPxy)
    {
        m_pobjAMBCamerainfoProxy = p_pobjAMBCameraInfo;
        m_pobjAMBBodyCntlInfoProxy = p_pobjAMB_BodyCntlInfoProxy;
        m_AMBApaPxy = p_pobjAMBApaPxy;
        LOG_INFO(LOG_RVC,"InitializeAMBProviderHandler ");
    }    
}

/**
* @brief Function to De initialize  CAMBProviderHandler 
* @param  None
*/
void CAMBProviderHandler::Deinitialize()
{
    LOG_INFO(LOG_RVC,"CAMBProviderHandler DeInitialize Called");
}


/**
 * @brief Function to interact with AMB to set/reset zoom
 * @param  OnOff - Value is true for setting zoom and false for resetting the zoom
 */
void CAMBProviderHandler::SetRVCZoom(bool OnOff)
{
    camerainfo_types::CamraZoomMan_D_Rq_enum l_UpdatedValue;
    LOG_INFO(LOG_RVC,"SetRVCZoom called");
    if((nullptr !=m_pobjAMBCamerainfoProxy)&&(true == OnOff))
    {
        //Requesting ECU through AMB to zoom in RVC image 
        m_pobjAMBCamerainfoProxy->getCamraZoomMan_D_Rq_enumAttribute().setValueAsync(camerainfo_types::CamraZoomMan_D_Rq_enum::En_Zoom_Level_III,(std::bind(&CAMBProviderHandler::asyncZommAttributeCallback, this, _1,_2)));
    }
    else if((nullptr !=m_pobjAMBCamerainfoProxy)&&(false == OnOff))
    {
       //Requesting ECU through AMB to zoom out RVC image 
        m_pobjAMBCamerainfoProxy->getCamraZoomMan_D_Rq_enumAttribute().setValueAsync(camerainfo_types::CamraZoomMan_D_Rq_enum::En_Off,(std::bind(&CAMBProviderHandler::asyncZommAttributeCallback, this, _1,_2)));
    }

}


/**
 * @brief Function to interact with AMB to set/reset Split-view for camera
 * @param  OnOff - Value is true for setting Split-view and false for resetting the Split-view
 */
void CAMBProviderHandler::SetRVCSplitView(bool OnOff)
{
    camerainfo_types::CamraViewSplit_B_Rq_enum l_UpdatedValue;
    LOG_INFO(LOG_RVC,"SetRVCSplitView called");
    if((nullptr !=m_pobjAMBCamerainfoProxy)&&(true == OnOff))
    {
        //Requesting ECU through AMB to Enable Split VIew image 
        m_pobjAMBCamerainfoProxy->getCamraViewSplit_B_Rq_enumAttribute().setValueAsync(camerainfo_types::CamraViewSplit_B_Rq_enum::En_On,(std::bind(&CAMBProviderHandler::asyncSplitViewAttributeCallback, this, _1,_2)));
    }
    else if((nullptr !=m_pobjAMBCamerainfoProxy)&&(false == OnOff))
    {
       //Requesting ECU through AMB to Dis-able Split VIew image 
        m_pobjAMBCamerainfoProxy->getCamraViewSplit_B_Rq_enumAttribute().setValueAsync(camerainfo_types::CamraViewSplit_B_Rq_enum::En_Off,(std::bind(&CAMBProviderHandler::asyncSplitViewAttributeCallback, this, _1,_2)));
    }

}

/**
 * @brief Function to interact with AMB to set/reset Enhanced Park aid for camera
 * @param  OnOff - Value is true for setting Enhanced Park aid and false for resetting the Split-view
 */
void CAMBProviderHandler::SetEnhancedParkMode(bool OnOff)
{
     // To do implement once AMB provides CAN SIgnals
    LOG_INFO(LOG_RVC,"SetEnhancedParkMode is called");
    if( ( nullptr != m_pobjAMBBodyCntlInfoProxy ) && ( true == OnOff ) )
    {
       //DistanceBarSetting_enm::On is used to set enhanced park mode 
	     LOG_INFO(LOG_RVC,"SetEnhancedParkMode true ");
        m_pobjAMBBodyCntlInfoProxy->getDistanceBarSetting_enumAttribute().setValueAsync(bodycontroldata_types::DistanceBarSetting_enum::En_On,(std::bind(&CAMBProviderHandler::asyncDistanceBarSettingAttributeCallback, this, _1,_2)));
    }
    else if( ( nullptr !=m_pobjAMBBodyCntlInfoProxy ) && ( false == OnOff ) )
    {
        //DistanceBarSetting_enm::Off is used to set enhanced park mode
		 LOG_INFO(LOG_RVC,"SetEnhancedParkMode as false  ");
        m_pobjAMBBodyCntlInfoProxy->getDistanceBarSetting_enumAttribute().setValueAsync(bodycontroldata_types::DistanceBarSetting_enum::En_Off,(std::bind(&CAMBProviderHandler::asyncDistanceBarSettingAttributeCallback, this, _1,_2)));
    }


}

/**
 *  @brief Function to set Static Guideline for RVC
 *  @param : 
*/
void CAMBProviderHandler::SetStaticGuideLine()
{
    if(nullptr !=m_pobjAMBCamerainfoProxy)
    {
       //Sending CAN message to camera ECU through AMB camera info interface to enable Static guideline 
        m_pobjAMBCamerainfoProxy->getCamraOvrlStat_D_Rq_enumAttribute().setValueAsync(camerainfo_types::CamraOvrlStat_D_Rq_enum::En_On,(std::bind(&CAMBProviderHandler::asyncCamraOvrlStatAttributeCallback, this, _1,_2)));
        LOG_INFO(LOG_RVC,"Setting static guideline On for RVC always for RVC");
    }
    
}

/**
 *  @brief Function to set Dynamic Guideline for RVC
 *  @param :s
*/
void CAMBProviderHandler::SetDyanamicGuideLine()
{
    if(nullptr !=m_pobjAMBCamerainfoProxy)
    {
        //Sending CAN message to camera ECU through AMB camera info interface to enable Dynamic guideline 
        m_pobjAMBCamerainfoProxy->getCamraOvrlDyn_D_Rq_enumAttribute().setValueAsync(camerainfo_types::CamraOvrlDyn_D_Rq_enum::En_On,(std::bind(&CAMBProviderHandler::asyncCamraOvrlDynAttributeCallback, this, _1,_2)));
        LOG_INFO(LOG_RVC,"Setting DyanamicGuideLine On for RVC always for RVC");
    }
    
}


/**
 *  @brief Function to set Centre Guideline for RVC
 *  @param :s
*/
void CAMBProviderHandler::SetCentreGuideLine()
{
    if(nullptr !=m_pobjAMBCamerainfoProxy)
    {
        LOG_INFO(LOG_RVC,"Set Centre GuideLine for RVC");
        m_pobjAMBCamerainfoProxy->getCamraOvrlTow_D_Rq_enumAttribute().setValueAsync(camerainfo_types::CamraOvrlTow_D_Rq_enum::En_On,(std::bind(&CAMBProviderHandler::asyncCamraOvrlTowAttributeCallback, this, _1,_2)));
    }
    
}

/**
 *  @brief Function Callback from AMB to inform whether setting of CamraOvrlStatAttribute is succeed or failed
 * @param : CamraOvrlStat_D_Rq_enm
 * @param : CallStatus
*/
void CAMBProviderHandler::asyncCamraOvrlStatAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraOvrlStat_D_Rq_enum &value)
{
    LOG_INFO(LOG_RVC,"asyncCamraOvrlStatAttributeCallback called");
}

/**
 *@brief Function Callback from AMB to inform whether setting of CamraOvrlDynAttribute is succeed or failed
  @param : CamraOvrlDyn_D_Rq_enm
  @param : CallStatus
*/
void CAMBProviderHandler::asyncCamraOvrlDynAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraOvrlDyn_D_Rq_enum &value)
{
    LOG_INFO(LOG_RVC,"asyncCamraOvrlDynAttributeCallback called");
}

/**
 * @brief Function Callback from AMB to inform whether setting of enhanced mode setting is succeed or failed
   @param : DistanceBarSetting_enm
   @param : CallStatus
*/
void CAMBProviderHandler::asyncDistanceBarSettingAttributeCallback(const CommonAPI::CallStatus &status,const bodycontroldata_types::DistanceBarSetting_enum &value)
{
    LOG_INFO(LOG_RVC,"asyncDistanceBarSettingAttributeCallback called");
}

/**
 *@brief  Function Callback from AMB to inform whether setting of CamraOvrlTow_D_Rq_enm is succeed or failed
 *@param : CamraOvrlTow_D_Rq_enm
 * @param : CallStatus
*/
void CAMBProviderHandler::asyncCamraOvrlTowAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraOvrlTow_D_Rq_enum &value)
{
    LOG_INFO(LOG_RVC,"asyncCamraOvrlTowAttributeCallback called");
}

/**
 *@brief  Function Callback from AMB to inform whether setting of ZommAttribute is succeed or failed
 @param : CamraZoomMan_D_Rq_enm
 @param : CallStatus
*/
void CAMBProviderHandler::asyncZommAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraZoomMan_D_Rq_enum &value)
{
    LOG_INFO(LOG_RVC,"asyncZommAttributeCallback called");
} 

void CAMBProviderHandler::APAModeReqCB(const CommonAPI::CallStatus &status, const v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum &p_eApaMdeStat)
{
    LOG_INFO(LOG_APA,"APAModeReqCB called");

}
void CAMBProviderHandler::asyncSplitViewAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraViewSplit_B_Rq_enum &value)
{
    LOG_INFO(LOG_RVC,"asyncSplitViewAttributeCallback called");
} 

void CAMBProviderHandler::APAModeReqToAMB(v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum p_eApaMdeStat)
{
    LOG_INFO(LOG_APA, "APAModeReqToAMB And Data is >> %d", p_eApaMdeStat);
    if(NULL != m_AMBApaPxy)
    {
        m_AMBApaPxy->getApaMdeStat_D_RqDrv_enumAttribute().setValueAsync(p_eApaMdeStat,(std::bind(&CAMBProviderHandler::APAModeReqCB, this, _1,_2)));
    }
}
