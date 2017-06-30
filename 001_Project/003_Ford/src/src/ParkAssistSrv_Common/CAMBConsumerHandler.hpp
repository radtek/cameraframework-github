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

#ifndef AMB_CONSUMER_HANDLER_HPP
#define AMB_CONSUMER_HANDLER_HPP

#include "ParkAssistSrv_Common/CommonCore.hpp"
#include "ParkAssistSrv_Common/CPAMContext.hpp"

using namespace v0::org::harman::ford;
using namespace v2::org::genivi::NodeStateManager;

class AMBConsumerHandler
{
    public:
        
    AMBConsumerHandler();
    ~AMBConsumerHandler();
    

    /**
      @brief initializing all variable and providing  interface to set RVVservicestub  pointer. 
      @param  RVCServiceStubImpl shared Pointer
     */
    void InitializeAMBConsumerHandler(CContext *p_pobjContext);
    
    
    /**
     * @brief Callback function from AMB to indicate Vehicle Characteristic  properties are changed  and routes AMB events to required module(RVC,APA and VPA) 
      @param  VehCharacteristicSet2
     */
    void VehCharNotifyCallBack(camerainfo_types::VehCharacteristicSet2_HS3_struct obj);
    
    /**
     *@brief Callback function from AMB to indicate GearPostion of Vehicle got changed  and routes AMB events to required module(RVC,APA and VPA) 
      @param  TransmissionModeExtension
     */
    void GearPostionNotifyCallBack(v0::org::harman::ford::bodycontroldata_types::Body_Info_1_HS3_sig_0_struct p_stGearLvrPos);
    
    /**
     *@brief Callback function from AMB to indicate parking brake status of Vehicle changed and routes AMB events to required module(RVC,APA and VPA) 
      @param  ParkingBrakeActiveStatus
     */
    void ParkBrkStatusNotifyCallBack(v0::org::harman::ford::enginedata_types::PrkBrkActv_B_Actl_struct obj);
     /**
     *@brief Callback function from AMB to indicate whether Trunk status is open or closed  
      @param  ParkingBrakeActiveStatus
     */

    void TrunkStatusNotifyCallBack(enginedata_types::DrStatTgate_B_Actl_enum obj);
	
	  /**
     *@brief Callback function from AMB to indicate whether Electronic brake is applied 
      @param  ParkingBrakeActiveStatus
     */	 
	 void EleBrkStatusCallback(enginedata_types::PrkBrkStatus_struct obj);
    
       /**
     *@brief Callback function from NSM to indicate whether NsmSessionState is active or inavtive  
      @param  ParkingBrakeActiveStatus
     */
   void onNsmSessionStateChange(std::string VehiclePowerMode);
    
     /**
     * @brief Callback function from AMB to indicate Reverse gear status on manual transmission
      @param  VehCharacteristicSet2
     */
    void VehRevGearNotifyCallBack(v0::org::harman::ford::rearviewcamclient_types::GearRvrse_D_Actl_struct p_stRevGear);
     
    void VehicelSpeedNotifyCallBack(v0::org::harman::ford::bodycontroldata_types::Veh_V_ActlEng_struct p_stVeh_V_ActlEng_structData);

    void IginitionStatusCallback(enginedata_types::Ignition_Status_enum obj);
    //APA Event Call Back Starts  
   
    void APASrv_ActiveApaModeUpdate(v0::org::harman::ford::actvparkassist_types::ApaMde_D_Stat_struct p_eActiveFeature);
    void ApaGearShif_D_RqDrvStatus(v0::org::harman::ford::actvparkassist_types::ApaGearShif_D_RqDrv_enum p_eApaGearShif_D_RqDrv);
    void Deinitialize();


// PDC CallBacks Start

    void CB_getPrkAidMsgTxt_D_Rq_enumAttribute(v0::org::harman::ford::visualparkassist_types::PrkAidMsgTxt_D_Rq_struct p_stPrkAidMsgTxt_D_RqData);
     
    void CB_getPrkAidSnsRlCrnr_D_Stat_enumAttribute(v0::org::harman::ford::visualparkassist_types::PrkAidSnsRlCrnr_D_Stat_enum value);
    void CB_getPrkAidSnsRlCntr_D_Stat_enumAttribute(v0::org::harman::ford::visualparkassist_types::PrkAidSnsRlCntr_D_Stat_enum value);
    void CB_getPrkAidSnsRrCntr_D_Stat_enumAttribute(v0::org::harman::ford::visualparkassist_types::PrkAidSnsRrCntr_D_Stat_enum value);
    void CB_getPrkAidSnsRrCrnr_D_Stat_enumAttribute(v0::org::harman::ford::visualparkassist_types::PrkAidSnsRrCrnr_D_Stat_enum value);

    void CB_getPrkAidSnsFlCrnr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsFlCrnr_D_Stat_enum value);
    void CB_getPrkAidSnsFlCntr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsFlCntr_D_Stat_enum value);
    void CB_getPrkAidSnsFrCntr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsFrCntr_D_Stat_enum value);
    void CB_getPrkAidSnsFrCrnr_D_Stat_enumAttribute(visualparkassist_types::PrkAidSnsFrCrnr_D_Stat_enum value);

    void CB_getSidePrkSnsL1_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsL1_D_Stat_enum value);
    void CB_getSidePrkSnsL2_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsL2_D_Stat_enum value);
    void CB_getSidePrkSnsL3_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsL3_D_Stat_enum value);
    void CB_getSidePrkSnsL4_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsL4_D_Stat_enum value);

    void CB_getSidePrkSnsR1_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsR1_D_Stat_enum value);
    void CB_getSidePrkSnsR2_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsR2_D_Stat_enum value);
    void CB_getSidePrkSnsR3_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsR3_D_Stat_enum value);
    void CB_getSidePrkSnsR4_D_Stat_enumAttribute(visualparkassist_types::SidePrkSnsR4_D_Stat_enum value);

    void Sig0AttributeCallBack(v0::org::harman::ford::camerainfo_types::VehCharacteristicSet2_HS3_sig_0_struct p_stSig0Data);
    void Sig2AttributeCallBack(v0::org::harman::ford::camerainfo_types::VehCharacteristicSet2_HS3_sig_2_struct p_stSig2Data);
	void SplitViewResponceCallBack(v0::org::harman::ford::camerainfo_types::PAC_Send_Signals_sig_0_struct  p_stSplitViewData);
	 
    void APASrv_ParkAidDataHS3UpdateCB(v0::org::harman::ford::actvparkassist_types::ParkAid_Data_HS3_struct p_stParkAidData);

    private :
        
        bool m_bCameraMaxSpeed;
        CContext *m_pobjContext;
        void PostChangeInSpeedToPresCore(bool p_bIsMaxSpeed);
};

#endif
