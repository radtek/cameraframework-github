/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            CPAMPresctrl.hpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           Creates RVC,APA,VPA presctrl and subscribe to AMB interface . Once AMB interface is Avaliabel then  subscribe required attribute  with AMB .
*                  
*/
#ifndef RVC_PRESCTRL_HPP
#define RVC_PRESCTRL_HPP

#include "ParkAssistSrv_Common/CommonCore.hpp"
#include "ParkAssistSrv_Common/CAMBConsumerHandler.hpp"
#include "ParkAssistSrv_Common/CAMBProviderHandler.hpp"
#include "ParkAssistSrv_Common/CPAMContext.hpp"

#include "ParkAssistSrv_PDC/PDCFactory.h"
#include "ParkAssistSrv_PDC/PDCServiceFord.h"

using namespace v0::org::harman::ford;
using namespace v0::com::harman::ParkAssist;
using namespace v2::org::genivi::NodeStateManager;

#define APP_NAME "PAMService"

class CPAMPresctrl
{
    public: 
        
    bool bIndexerCameraInfoAvailable;
    bool bIndexerBodyInfoInfoAvailable;
    bool bIndexerEngineDataAvailable;
    bool bIndexerCameraClientAvailable;
    
    std::shared_ptr<CommonAPI::Runtime> runtime;
    std::shared_ptr<RVCServiceStubImpl> m_pobjRVCServiceStub;
    std::shared_ptr<camerainfoProxy<>> m_pobjAMBCamerainfoProxy;
    std::shared_ptr<bodycontroldataProxy<>> m_pobjAMBBodyCntlInfoProxy;
    std::shared_ptr<enginedataProxy<>> m_AMBEngineProxy;
    std::shared_ptr<rearviewcamclientProxy<>> m_AMBCamClientProxy;
    std::shared_ptr<ConsumerProxy<>> m_NSMProxy;
    std::shared_ptr<actvparkassistProxy<>> m_AMBApaPxy;
     
    std::shared_ptr<APAServiceStubImpl> m_pobjAPAStub; 
    std::shared_ptr<PDCServiceStubImpl> m_PDCServiceStub; 

    std::shared_ptr<visualparkassistProxy<>> m_AMBvisualparkassistProxy;

    ~CPAMPresctrl(); 
    
    /**
     *@brief Creating RVC Presctrl  and regitering with AMB events 
     @param : None
     @param : None
    */
    EParkAssitGenRet InitializePAM();
    EParkAssitGenRet InitializeRVC();
    EParkAssitGenRet InitializeAPA();
    EParkAssitGenRet InitializePDC();

    EParkAssitGenRet RegisterRVCServiceToDBus();
    EParkAssitGenRet RegisterAPAServiceToDBus();
    EParkAssitGenRet RegisterPDCServiceToDBus();
    /**
     @brief De initializing RVC Presctrl  
     @param : None
     @param : None
    */
    void DeInitialize();
    
    /**
     @brief Call back from AMB to inform whether Camerainfo is ready 
     @param : CommonAPI::AvailabilityStatus
    */
    void CamerainfoPxyAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus );

    /**
     @brief Call back from AMB to inform whether BodyCntlInfo is ready 
     @param : CommonAPI::AvailabilityStatus
    */
    void BodyControlPxyAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus );
    
    /**
     @brief Call back from NSM to inform whether NSM is ready 
     @param : CommonAPI::AvailabilityStatus
    */
    void NsmInfoAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus );

    void EngineInfoPxyAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus );
     /**
     @brief Call back from AMB to inform whether EngineInfo is ready 
     @param : CommonAPI::AvailabilityStatus
    */
    /**
     @brief Call back from AMB to inform whether Rear-view client interface  is ready 
     @param : CommonAPI::AvailabilityStatus
    */
    void RVCProxyAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus );


    void ApaProxyAvilabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus );

    void  PDCProxyAvilabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus );

//  Static object creation
    static CPAMPresctrl *m_pobjPAMPresCtrl;
    static CPAMPresctrl * getInstance();
    
    CAMBProviderHandler m_AMBProviderHandler;
    AMBConsumerHandler m_AMBConsumerHandler;
    CContext m_objContext;






     //Providing RvcPresctrl Handel to consumer class  because it can redirect all AMb received events to RVC presctrl
    
   PDCFactory *pTest = PDCFactory::getInstance();
   PDCServiceFord *m_PDCServiceFord = pTest->vSetup();

        
    private :
        
    std::string domain = "local";
    std::string CameraInfoinstance = "AutomotiveMessageBrokerProvider.ford_Camerainfo";
    std::string BodyInfoinstance = "AutomotiveMessageBrokerProvider.ford_BodyCtrlData";
    std::string EngineInfoinstance = "AutomotiveMessageBrokerProvider.ford_engineData";
    std::string RearViewInfoinstance = "AutomotiveMessageBrokerProvider.ford_RearViewCamClient";
    std::string APAInfoinstance = "AutomotiveMessageBrokerProvider.ford_Activeparkassist";
    std::string NsmInfoinstance = "NodeStateManager.inst0";
    std::string VPAInfoinstance = "AutomotiveMessageBrokerProvider.ford_VisualParkAssist";

    std::string connectionAMBCameraPxy = "AMB_CameraInfo";
    std::string connectionAMBBodyCntlInfoPxy = "AMB_BodyControlInfo";
    std::string connectionAMBEngineProxy = "AMB_EngineDataInfo"; 
    std::string connectionNsmPxy = "NSM_ProxyInfo";
    std::string connectionAMBRvcClientProxy = "AMB_RVCInfo";
    std::string connectionAMBAPAClientProxy = "AMB_APAProxyInfo";
    std::string connectionAMBVPAPxy = "AMB_VPAInfo";

    //Constructore made private due to singleton
    CPAMPresctrl();

    
    /**
     *@brief  initializing and subscribing  to AMB 
     @param : None
    */
    EParkAssitGenRet InitializeAMBProxy();
    
    EParkAssitGenRet InitializeNSMProxy();
    /**
     *@brief  Creating RVCpresctrl and Registering with dbus 
     @param : None
     @param : None
    */
    EParkAssitGenRet InitializeRVCStub();
    
    /**
     *@brief Subscribing to camera AMB interface AMB  
     @param : None
    */
    EParkAssitGenRet SubScribeToCameraInfoEvents();
      
    /**
     *@brief Subscribing to VechileInfo AMB interface AMB  
     @param : None
    */
    EParkAssitGenRet SubScribeToVehicleInfoEvents();
    
     /**
     *@brief Subscribing to Body Info AMB interface   
     @param : None
    */
    EParkAssitGenRet SubScribeToBodyInfoEvents();
    
    /**
     *@brief Subscribing to Engine Info AMB interface   
     @param : None
    */
    EParkAssitGenRet SubScribeToEngineInfoEvents();
    EParkAssitGenRet SubScribeToNsmInfoEvents();
    /**
     *@brief Subscribing to AMB rear view client attributes   
     @param : None
    */
    EParkAssitGenRet SubScribeToRearCameraInfoEvents();
    
    /**
     *@brief Subscribing to AMB APA to attributes   
     @param : None
    */
    EParkAssitGenRet SubScribeToAPAInfoEvents();
/*    @brief Verify Whether all AMB interface are Ready 
    @param : CommonAPI::AvailabilityStatus
    */
    void IsAllAMBInterfaceAvaliabel();

    EParkAssitGenRet SubScribeToVisualParkAssitEvents();

    void ReadEOLServieSupport();
    void PAMSrv_InitializePersistency();
    void PAMSrv_DeinitializePersistency();
    
};

#endif 
