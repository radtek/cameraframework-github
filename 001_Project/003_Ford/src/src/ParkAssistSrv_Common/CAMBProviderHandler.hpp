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
#ifndef AMB_PROVIDER_HANDLER_HPP
#define AMB_PROVIDER_HANDLER_HPP
#include "ParkAssistSrv_Common/CommonCore.hpp"
#include "ParkAssistSrv_APA/APAServiceStubImpl.hpp"
#include "ParkAssistSrv_RVC/RVCServiceStubImpl.hpp"
#include "ParkAssistSrv_Common/CPAMContext.hpp"
#include "ParkAssistSrv_PDC/PDCServiceStubImpl.hpp"

using namespace v0::org::harman::ford;

class CAMBProviderHandler
{
    public:
    CAMBProviderHandler();
    ~CAMBProviderHandler();

    /**
     * @brief Function to initialise  CAMBProviderHandler and providing interface to set AmbianceInfo handle
     * @param  vehAmbianceInfoAMBvehAmbianceInfo - to get Shared pointer of AmbianceInfoAMB interface
     */
    void InitializeAMBProviderHandler(std::shared_ptr<camerainfoProxy<>> &p_pobjAMBCameraInfo, std::shared_ptr<bodycontroldataProxy<>> &p_pobjAMB_BodyCntlInfoProxy,
                                                        std::shared_ptr<actvparkassistProxy<>> &p_pobjAMBApaPxy);
    
    /**
     * @brief Function to De initialize  CAMBProviderHandler 
     * @param  None
     */
    void Deinitialize();
    
    /**
     * @brief Function to interact with AMB to set/reset zoom
     * @param  OnOff - Value is true for setting zoom and false for resetting the zoom
     */
    void SetRVCZoom(bool OnOff);
    
    /**
     * @brief Function to interact with AMB to set/reset Split-view for camera
     * @param  OnOff - Value is true for setting Split-view and false for resetting the Split-view
     */
    void SetRVCSplitView(bool OnOff);
    
    /**
     * @brief Function to interact with AMB to set/reset Enhanced Park aid for camera
     * @param  OnOff - Value is true for setting Enhanced Park aid and false for resetting the Split-view
     */
	 
	 
    void SetEnhancedParkMode(bool OnOff);
    
	/**
     * @brief Function to set static guide line for Rare view camera
     * @param : none
     * @param : none
    */

	void SetStaticGuideLine();
	
	/**
     * @brief Function to set Dynamic guide line for Rare view camera
     * @param : none
     * @param : none
    */
	void SetDyanamicGuideLine();
	void SetCentreGuideLine();
    /**
     *  @brief Function Callback from AMB to inform whether setting of CamraOvrlStatAttribute is succeed or failed
     * @param : CamraOvrlStat_D_Rq_enm
     * @param : CallStatus
    */
	
	void asyncCamraOvrlStatAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraOvrlStat_D_Rq_enum &value);
    
    /**
     *@brief Function Callback from AMB to inform whether setting of CamraOvrlDynAttribute is succeed or failed
      @param : CamraOvrlDyn_D_Rq_enm
      @param : CallStatus
    */
    void asyncCamraOvrlDynAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraOvrlDyn_D_Rq_enum &value);
    
    /**
     * @brief Function Callback from AMB to inform whether setting of CamraOvrlTowAttribute is succeed or failed
       @param : DistanceBarSetting_enm
       @param : CallStatus
    */
    void asyncDistanceBarSettingAttributeCallback(const CommonAPI::CallStatus &status,const bodycontroldata_types::DistanceBarSetting_enum &value);
    
    /**
     *@brief  Function Callback from AMB to inform whether setting of CamraOvrlTow_D_Rq_enm is succeed or failed
     @param : CamraOvrlTow_D_Rq_enm
     @param : CallStatus
    */
    void asyncCamraOvrlTowAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraOvrlTow_D_Rq_enum &value);
    
    /**
     *@brief  Function Callback from AMB to inform whether setting of ZommAttribute is succeed or failed
     @param : CamraZoomMan_D_Rq_enm
     @param : CallStatus
    */
    void asyncZommAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraZoomMan_D_Rq_enum &value);
	
	void asyncSplitViewAttributeCallback(const CommonAPI::CallStatus &status,const camerainfo_types::CamraViewSplit_B_Rq_enum &value);

    void APAModeReqToAMB(v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum p_eApaMdeStat);
    void APAModeReqCB (const CommonAPI::CallStatus &status, const v0::org::harman::ford::actvparkassist_types::ApaMdeStat_D_RqDrv_enum &p_eApaMdeStat);
    private :
        std::shared_ptr<camerainfoProxy<>> m_pobjAMBCamerainfoProxy;
        std::shared_ptr<bodycontroldataProxy<>> m_pobjAMBBodyCntlInfoProxy;
        std::shared_ptr<actvparkassistProxy<>> m_AMBApaPxy;
};


#endif
