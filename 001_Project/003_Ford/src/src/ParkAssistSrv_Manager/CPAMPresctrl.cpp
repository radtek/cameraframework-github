/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            CPAMPresctrl.cpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           Creates RVC,APA,VPA presctrl and subscribe to AMB interface . Once AMB interface is Avaliabel then  subscribe required attribute  with AMB .
*                  
*/
#include"CPAMPresctrl.hpp"

using namespace std;
using namespace placeholders;

CPAMPresctrl * CPAMPresctrl::m_pobjPAMPresCtrl = NULL;
#define PCL_LDBID_EOL  0x71     /*!< value to access End of line data */ 
#define EOL_ID_SIZE 4
#define ADJ_E2P_DIAG_EOL_DE07_HMI_REARVIEW_CAMERA_ID   0x809d0001u
#define ADJ_E2P_DIAG_EOL_DE07_HMI_REARVIEW_CAMERA_SIZE 0x1u
#define ADJ_E2P_DIAG_EOL_DE07_HMI_PARKINGAID_MODE_ID   0x809f0001u
#define ADJ_E2P_DIAG_EOL_DE07_HMI_PARKINGAID_MODE_SIZE 0x1u

CPAMPresctrl:: CPAMPresctrl():
    bIndexerCameraInfoAvailable(false),
    bIndexerBodyInfoInfoAvailable(false),
    bIndexerEngineDataAvailable(false),
    bIndexerCameraClientAvailable(false),
    m_pobjAMBCamerainfoProxy(nullptr),
    m_pobjAMBBodyCntlInfoProxy(nullptr),
    m_AMBEngineProxy(nullptr),
    m_AMBCamClientProxy(nullptr),
    m_NSMProxy(nullptr),
    m_AMBApaPxy(nullptr)
{
    LOG_INFO(LOG_COMMON,"CPAMPresctrl Constructor") ;

    //Initializing Persistency
    PAMSrv_InitializePersistency();
}


CPAMPresctrl::~CPAMPresctrl()
{
    LOG_INFO(LOG_COMMON,"CPAMPresctrl Destructor") ;
    bIndexerCameraInfoAvailable   =false ;
    bIndexerBodyInfoInfoAvailable =false ;
    bIndexerEngineDataAvailable   =false ;
    bIndexerCameraClientAvailable =false ;
    m_pobjAMBCamerainfoProxy   =   nullptr;
    m_pobjAMBBodyCntlInfoProxy =    nullptr;
    m_AMBEngineProxy    =   nullptr;
    m_AMBCamClientProxy = nullptr;
    m_AMBApaPxy = nullptr;


    //Deinitializing Persistency
    PAMSrv_DeinitializePersistency();
}

/**
    @brief Call back from NSM whether interface is ready or no
    @param : CommonAPI::AvailabilityStatus
*/
void CPAMPresctrl::NsmInfoAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus )
{
   EParkAssitGenRet l_eStatus = e_ParkAssitSuccess;
   if(p_eAvailStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(LOG_RVC, "NSM info interface is ready") ;
        l_eStatus = SubScribeToNsmInfoEvents();
        if(l_eStatus == e_ParkAssitFailure)
        {
            LOG_INFO(LOG_RVC, "Can't able to subscribe to NSM proxy ") ;
            //To do how to handle error condition
        }
    }
    else
    {
        //wait until interface is ready
        LOG_ERROR(LOG_RVC, "NSM info interface is Not Avaliabel") ;
    }

}

/**
    @brief Call back from AMB to inform whether Camera info interface is ready to use 
    @param : CommonAPI::AvailabilityStatus
*/
void CPAMPresctrl::CamerainfoPxyAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus )
{
   EParkAssitGenRet l_status = e_ParkAssitSuccess;
   if(p_eAvailStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(LOG_RVC,"Camera info AMB Proxy is Avaliabel") ;
        bIndexerCameraInfoAvailable = true;
        //Check whether all AMB interface are ready . If then inform RVC presctrl to request default camera properties
        IsAllAMBInterfaceAvaliabel();
        //Subscribe to Camera info interface notification
        l_status = SubScribeToCameraInfoEvents();
        if(l_status == e_ParkAssitFailure)
        {
            LOG_ERROR(LOG_RVC,"Can't able to subscribe to Body control AMB proxy") ;
            //To do how to handle error condition
        }
    }
    else
    {
        //wait until interface is ready
        LOG_ERROR(LOG_RVC,"Camera info AMB Proxy is Not Avaliabel") ;
        bIndexerCameraInfoAvailable = false;
    }

}

/**
    @brief Call back from AMB to inform whether Engine info Proxy is ready 
    @param : CommonAPI::AvailabilityStatus
*/
void CPAMPresctrl::EngineInfoPxyAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus )
{
    EParkAssitGenRet l_eStatus = e_ParkAssitSuccess;
   if(p_eAvailStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(LOG_RVC,"Engine info AMB Proxy is Avaliabel") ;
        bIndexerEngineDataAvailable = true;
        //Check whether all AMB interface are ready . If then inform RVC presctrl to request default camera properties
        IsAllAMBInterfaceAvaliabel();
        //Subscribe to Engine data interface notification
        l_eStatus=  SubScribeToEngineInfoEvents();
        if(l_eStatus == e_ParkAssitFailure)
        {
            LOG_ERROR(LOG_RVC,"Can't able to subscribe to Engine proxy") ;
            //To do how to handel error condition
        }
    }
    else
    {
        //wait until interface is ready
        LOG_ERROR(LOG_RVC,"Engine info AMB Proxy is Not Avaliabel") ;
        bIndexerEngineDataAvailable = false;
    }

}

/**
    @brief Call back from AMB to inform whether Body control AMB proxy is ready to use
    @param : CommonAPI::AvailabilityStatus
*/
void CPAMPresctrl::BodyControlPxyAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus )
{
   EParkAssitGenRet l_eStatus = e_ParkAssitSuccess;
   if(p_eAvailStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(LOG_RVC,"Body control AMB Proxy is Avaliabel") ;
        bIndexerBodyInfoInfoAvailable = true;
        //Check whether all AMB interface are ready . If then inform RVC presctrl to request default camera properties
        IsAllAMBInterfaceAvaliabel();
        //Subscribe to Engine data interface notification
        l_eStatus = SubScribeToBodyInfoEvents();
        if(l_eStatus == e_ParkAssitFailure)
        {
            LOG_ERROR(LOG_RVC,"Can't able to subscribe to Body control AMB proxy") ;
            //To do how to handel error condition
        }
    }
    else
    {
        //wait until interface is ready
        LOG_ERROR(LOG_RVC,"Body control AMB Proxy is Not Avaliabel") ;
        bIndexerBodyInfoInfoAvailable = false;
    }

}

/**
    @brief Call back from AMB to inform whether AMB APA interface is ready to use 
    @param : CommonAPI::AvailabilityStatus
*/
void CPAMPresctrl::ApaProxyAvilabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus )
{
   EParkAssitGenRet l_eStatus = e_ParkAssitSuccess;
   if(p_eAvailStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(LOG_RVC,"AMB APA Proxy is Avaliabel") ;
        //Subscribe to APA interface notification
        l_eStatus = SubScribeToAPAInfoEvents();
        if(l_eStatus == e_ParkAssitFailure)
        {
            LOG_INFO(LOG_RVC,"Can't able to subscribe AMB APA proxy ") ;
            //To do how to handle error condition
        }
    }
    else
    {
        //wait until interface is ready
        LOG_INFO(LOG_RVC,"APA Proxy is Not Avaliabel") ;

    }

}

/**
    @brief Call back from AMB to inform whether Rear Camera client interface is ready to use 
    @param : CommonAPI::AvailabilityStatus
*/
void CPAMPresctrl::RVCProxyAvailabilityCB( CommonAPI::AvailabilityStatus p_eAvailStatus)
{
   EParkAssitGenRet l_eStatus = e_ParkAssitSuccess;
   if(p_eAvailStatus == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(LOG_RVC,"AMB Rear view Camera info AMB Proxy is Avaliabel") ;
        bIndexerCameraClientAvailable = true;
        //Subscribe to Camera info interface notification
        l_eStatus = SubScribeToRearCameraInfoEvents();
        if(l_eStatus == e_ParkAssitFailure)
        {
            LOG_INFO(LOG_RVC,"Can't able to subscribe to Body control AMB proxy") ;
            //To do how to handle error condition
        }
    }
    else
    {
        //wait until interface is ready
        LOG_INFO(LOG_RVC,"Camera info AMB Proxy is Not Avaliabel") ;
        bIndexerCameraClientAvailable = false;
    }

}

/**
    @brief Verify Whether all AMB interface are Ready 
    @param : CommonAPI::AvailabilityStatus
*/
void CPAMPresctrl::IsAllAMBInterfaceAvaliabel()
{
    LOG_INFO(LOG_RVC,"Check Whether All AMB Interface Avaliabel");
    if((bIndexerCameraInfoAvailable == true) && (bIndexerBodyInfoInfoAvailable == true) && (bIndexerEngineDataAvailable == true))
    {
        if(nullptr != m_pobjRVCServiceStub)
        {
            //if all AMB interfaces are then inform RVC presctrl to set all camera setting properties
            //Setting default RVC setting once all AMb interface are Avaliabel
            LOG_INFO(LOG_RVC,"Before Setting camera setting towards AMB") ;
            m_pobjRVCServiceStub->SetCameraInfoDefaultSettings();
            LOG_INFO(LOG_RVC,"Setting camera setting towards AMB") ;
        }
    
    }
}
/**
    @brief De initializing RVC Presctrl  
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::InitializePAM()
{
    // Entry point to PAM Process
    LOG_INFO(LOG_RVC, "PAM Initialize");
    EParkAssitGenRet l_status = e_ParkAssitSuccess;

    do
    {
        ReadEOLServieSupport();
        //Getting shared pointer of AMB and Subscribing call back to notify once AMB interfaces are ready

        // RVC Initialization
        l_status = InitializeRVC();
        if(e_ParkAssitFailure == l_status)
        {
            LOG_ERROR(LOG_RVC, "RVC Initialize failed");
            break;
        }

        // APA initialization
        l_status = InitializeAPA();
        if(e_ParkAssitFailure == l_status)
        {
            LOG_ERROR(LOG_RVC, "APA Initialize failed");
            break;
        }   

        // PDC initialization
        l_status = InitializePDC();
        if(e_ParkAssitFailure == l_status)
        {
            LOG_ERROR(LOG_RVC, "APA Initialize failed");
            break;
        }    
        
        l_status= InitializeAMBProxy(); 
        if(l_status == e_ParkAssitFailure)
        {
            LOG_ERROR(LOG_RVC, "InitializeAMBProxy failed");
            //AMB registration failed and cant proceed further 
            break;
        }   
        l_status =  RegisterRVCServiceToDBus();
        if(e_ParkAssitFailure == l_status)
        {
            LOG_ERROR(LOG_RVC, "RegisterRVCServiceToDBus failed");
            break;
        }   
        l_status =  RegisterAPAServiceToDBus();
        if(e_ParkAssitFailure == l_status)
        {
            LOG_ERROR(LOG_RVC, "RegisterAPAServiceToDBus failed");
            break;
        }   
        l_status =  RegisterPDCServiceToDBus();
        if(e_ParkAssitFailure == l_status)
        {
            LOG_ERROR(LOG_RVC, "RegisterPDCServiceToDBus failed");
            break;
        }   
        
    }while(0);

    return l_status;
}


EParkAssitGenRet CPAMPresctrl::InitializeAPA()
{
    EParkAssitGenRet l_eRet = e_ParkAssitSuccess;
    m_pobjAPAStub = std::make_shared<v0::com::harman::ParkAssist::APAServiceStubImpl>(&m_objContext);
    if(NULL == m_pobjAPAStub)
    {
        l_eRet = e_ParkAssitFailure;
    }
    return l_eRet;
}
EParkAssitGenRet CPAMPresctrl::InitializeRVC()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess;
    do
    {
        //Registering RVC to D-BUS
        l_status = InitializeRVCStub(); 
        if(l_status == e_ParkAssitFailure)
        {
            //Return if Dubs registration failed
            break;
        }
        
        //Initialising Rvc presctrl , Initializing Threads to Read and process events 
        m_pobjRVCServiceStub->InitializeRVCStub(); 
       
    
    }while(0);  
    
    return l_status;
}

EParkAssitGenRet CPAMPresctrl::InitializePDC()
{

    LOG_INFO(LOG_PDC, "InitializePDC Started...\n");
    EParkAssitGenRet l_status = e_ParkAssitSuccess;

    m_PDCServiceStub = std::make_shared<v0::com::harman::ParkAssist::PDCServiceStubImpl>(&m_objContext);
    if(NULL == m_PDCServiceStub)
    {
        l_status = e_ParkAssitFailure;
    }
    return l_status;    
}
/**
    @brief De initializing RVC Presctrl  
    @param : None
*/
void  CPAMPresctrl::DeInitialize()
{
    LOG_INFO(LOG_RVC,"PAM DEInitialize ") ;
}

/**
    @brief Subscribing to NSM
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::SubScribeToNsmInfoEvents()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess; 
    if(nullptr != m_NSMProxy)
    {
        //Subscribe to NSM  to notify whether NsmSessionState is active or inactive  
        m_NSMProxy->getVehiclePowerModeAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::onNsmSessionStateChange,&m_AMBConsumerHandler,_1) );
        LOG_INFO(LOG_RVC,"SubScribe To SessionStateChange events");
    }
     else
    {
        LOG_INFO(LOG_RVC,"PAM Unable to SubScribe To SubScribeToCNsmInfoEvents");
        l_status = e_ParkAssitFailure;
    }
    return l_status;

}

/**
    @brief Subscribing to Rear Camera client Info Events
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::SubScribeToAPAInfoEvents()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess; 
    if(nullptr != m_AMBApaPxy)
    {
        //Subscribing to VehCharcter setting attribute to get notification related vehicle characteristic from camera info proxy
        LOG_INFO(LOG_RVC,"PAM SubScribe to APA Events success");
       
        if((m_objContext.m_bContextIsAPASupported) ||(m_objContext.m_bContextIsRVCSupported))
        {   
            m_AMBApaPxy->getParkAid_Data_HS3Attribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::APASrv_ParkAidDataHS3UpdateCB, &m_AMBConsumerHandler, _1));
            //Register following signal only when RVC or APA is configured

        }
        
        if(m_objContext.m_bContextIsAPASupported)
        {
            //Register following signal only when APA is configured
            m_AMBApaPxy->getApaMde_D_StatAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::APASrv_ActiveApaModeUpdate, &m_AMBConsumerHandler, _1));
        }   
    }
    else
    {
         LOG_INFO(LOG_RVC,"PAM SubScribe to Rear view Camera client Failed");
     //   l_status = e_ParkAssitFailure;
    }
    return l_status;
}

/**
    @brief Subscribing to Rear Camera client Info Events
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::SubScribeToRearCameraInfoEvents()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess; 
    if(nullptr != m_AMBCamClientProxy)
    {
        //Subscribing to VehCharcter setting attribute to get notification related vehicle characteristic from camera info proxy
        LOG_INFO(LOG_RVC,"PAM SubScribe to Rear view Camera client Info success");
        m_AMBCamClientProxy->getGearRvrse_D_ActlAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::VehRevGearNotifyCallBack,&m_AMBConsumerHandler,_1));
    
    }
    else
    {
         LOG_INFO(LOG_RVC,"PAM SubScribe to Rear view Camera client Failed");
     //   l_status = e_ParkAssitFailure;
    }
    return l_status;
}
/**
    @brief Subscribing to Camera Info Events
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::SubScribeToCameraInfoEvents()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess; 
    if(nullptr != m_pobjAMBCamerainfoProxy)
    {
        //Subscribing to VehCharcter setting attribute to get notification related vehicle characteristic from camera info proxy
        LOG_INFO(LOG_RVC,"PAM SubScribeToCameraInfoEvents success");
        m_pobjAMBCamerainfoProxy->getVehCharacteristicSet2_HS3Attribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::VehCharNotifyCallBack,&m_AMBConsumerHandler,_1));
        m_pobjAMBCamerainfoProxy->getVehCharacteristicSet2_HS3_sig_0Attribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::Sig0AttributeCallBack,&m_AMBConsumerHandler,_1));
        m_pobjAMBCamerainfoProxy->getVehCharacteristicSet2_HS3_sig_2Attribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::Sig2AttributeCallBack,&m_AMBConsumerHandler,_1));
        m_pobjAMBCamerainfoProxy->getPAC_Send_Signals_sig_0Attribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::SplitViewResponceCallBack,&m_AMBConsumerHandler,_1));
    }
    else
    {
        LOG_INFO(LOG_RVC,"PAM Unable to SubScribe To CameraInfoEvents");
        l_status = e_ParkAssitFailure;
    }
    return l_status;
}



/**
    @brief Subscribing to Park Brake Status notification from AMB 
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::SubScribeToEngineInfoEvents()
{
     EParkAssitGenRet l_status = e_ParkAssitSuccess; 
    if(nullptr != m_AMBEngineProxy)
    {
        //Subscribing to PrkBrkActv attribute to get Manual brake status from Engine info AMB proxy
        LOG_INFO(LOG_RVC,"PAM subscribing to :ParkBrkStatus Attribute");
        m_AMBEngineProxy->getPrkBrkActv_B_ActlAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::ParkBrkStatusNotifyCallBack,&m_AMBConsumerHandler,_1));
        //Subscribing to Trunk status attribute to get Ajar or close notification from AMB
        m_AMBEngineProxy->getDrStatTgate_B_Actl_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::TrunkStatusNotifyCallBack,&m_AMBConsumerHandler,_1));
        //Subscribing to Ignition status attribute to get Ignition status of vehicle
        m_AMBEngineProxy->getIgnition_Status_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::IginitionStatusCallback,&m_AMBConsumerHandler,_1));
		m_AMBEngineProxy->getPrkBrkStatusAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::EleBrkStatusCallback,&m_AMBConsumerHandler,_1));
    
    }
    else
    {
        LOG_INFO(LOG_RVC,"PAM Unable to subscribe to :ParkBrkStatus Attribute ");
        l_status = e_ParkAssitFailure;
    }
    return l_status;


}

/**
    @brief Subscribing to Gear position notification from AMB 
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::SubScribeToBodyInfoEvents()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess;
    if(nullptr != m_pobjAMBBodyCntlInfoProxy)
    {
          //Subscribing to GearPostionNotify attribute to get Manual Gear status from Body control AMB proxy
        LOG_INFO(LOG_RVC,"PAM subscribing to GearPostionNotify Attribute");
        m_pobjAMBBodyCntlInfoProxy->getBody_Info_1_HS3_sig_0Attribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::GearPostionNotifyCallBack,&m_AMBConsumerHandler,_1));
        m_pobjAMBBodyCntlInfoProxy->getVeh_V_ActlEngAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::VehicelSpeedNotifyCallBack,&m_AMBConsumerHandler,_1));
    
    }
    else
    {
        LOG_INFO(LOG_RVC,"PAM Unable to subscribe to GearPostionNotify Attribute");
         l_status = e_ParkAssitFailure;
    }
    return l_status;


}
/**
    @brief  Creating RVCpresctrl and Registering with dbus 
    @param : None
**/
EParkAssitGenRet CPAMPresctrl::InitializeRVCStub()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess;

    m_pobjRVCServiceStub = std::make_shared<v0::com::harman::ParkAssist::RVCServiceStubImpl>(&m_objContext);
    if(NULL == m_pobjRVCServiceStub)
    {
        l_status = e_ParkAssitFailure;
    }
    else
    {
        LOG_INFO(LOG_APA, "InitializeRVCStub() Success");
        //Providing RvcPresctrl Handel to consumer class  because it can redirect all AMb received events to RVC presctrl
        m_AMBConsumerHandler.InitializeAMBConsumerHandler(&m_objContext);
    }
    return l_status;    
}

/**
    @brief  initializing and subscribing  to AMB 
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::InitializeAMBProxy()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess;
    runtime = CommonAPI::Runtime::get();
    
    do
    {
        if(!runtime)
        {
            LOG_INFO(LOG_RVC,"PAM InitializeAMBProxy Runtime failed");
            l_status = e_ParkAssitFailure;
            break;
        }   
        else
        {
            //Register the attribute only if RVC is configured

            // Getting shared pointer of AMB camera inform interface from dbus
            m_pobjAMBCamerainfoProxy = runtime->buildProxy<camerainfoProxy>(domain, CameraInfoinstance, connectionAMBCameraPxy);
            if(!m_pobjAMBCamerainfoProxy)
            {
                LOG_INFO(LOG_RVC,"Getting Runtime instance for Camera info is failed ");
                l_status = e_ParkAssitFailure;
                break;
            } 
            else
            {
                LOG_INFO(LOG_RVC,"Registering  to CamerainfoListener");
                //Registering function to Camera info interface  for notifying AMB camera info  Availability
                m_pobjAMBCamerainfoProxy->getProxyStatusEvent().subscribe(std::bind(&CPAMPresctrl::CamerainfoPxyAvailabilityCB,this,_1) );
            }
            
            // Getting shared pointer of AMB bodycontroldata interface from dbus
            m_pobjAMBBodyCntlInfoProxy = runtime->buildProxy<bodycontroldataProxy>(domain, BodyInfoinstance, connectionAMBBodyCntlInfoPxy);
            if(!m_pobjAMBBodyCntlInfoProxy)
            {
                LOG_INFO(LOG_RVC," Getting Runtime instance for Body control  is failed ");
                l_status = e_ParkAssitFailure;
                break;
            } 
            else
            {
                LOG_INFO(LOG_RVC,"Registering  to Body Control Listener");
                //Registering function to Body Control  AMB interface  for notifying  Availability
                m_pobjAMBBodyCntlInfoProxy->getProxyStatusEvent().subscribe(std::bind(&CPAMPresctrl::BodyControlPxyAvailabilityCB,this,_1) );
            }
            
            // Getting shared pointer of AMB Engine dtaa  interface from dbus
            m_AMBEngineProxy = runtime->buildProxy<enginedataProxy>(domain, EngineInfoinstance, connectionAMBEngineProxy);
            if(!m_AMBEngineProxy)
            {
                LOG_INFO(LOG_RVC," Getting Runtime instance for enginedataProxy is failed ");
                l_status = e_ParkAssitFailure;
                break;
            } 
            else
            {
                LOG_INFO(LOG_RVC,"Registering  to Engine Data Listener");
                //Registering function to Engine data AMB interface  for notifying  Availability
                m_AMBEngineProxy->getProxyStatusEvent().subscribe(std::bind(&CPAMPresctrl::EngineInfoPxyAvailabilityCB,this,_1) );
            } 
            
            // Getting shared pointer of Rear Camera client  interface from dbus
            m_AMBCamClientProxy = runtime->buildProxy<rearviewcamclientProxy>(domain,RearViewInfoinstance,connectionAMBRvcClientProxy);
            if(!m_AMBCamClientProxy)
            {
                LOG_INFO(LOG_RVC,"Getting Runtime instance for Rear view Camera info is failed ");
                l_status = e_ParkAssitFailure;
                break;
            } 
            else
            {
                LOG_INFO(LOG_RVC,"Registering  to Rear view Camera client info Listener");
                //Registering function to AMB Rear Camera client  interface  for notifying AMB camera info  Availability
                m_AMBCamClientProxy->getProxyStatusEvent().subscribe(std::bind(&CPAMPresctrl::RVCProxyAvailabilityCB,this,_1) );
            }
            
            // Getting shared pointer of AMB APA interface from dbus
            m_AMBApaPxy = runtime->buildProxy<actvparkassistProxy>(domain,APAInfoinstance,connectionAMBAPAClientProxy);
            if(!m_AMBApaPxy)
            {
                LOG_INFO(LOG_RVC,"Getting Runtime instance for Rear view Camera info is failed ");
                l_status = e_ParkAssitFailure;
                break;
            } 
            else
            {
                LOG_INFO(LOG_RVC,"Registering  to Rear view Camera client info Listener");
                //Registering function to AMB Rear Camera client  interface  for notifying AMB camera info  Availability
                m_AMBApaPxy->getProxyStatusEvent().subscribe(std::bind(&CPAMPresctrl::ApaProxyAvilabilityCB,this,_1) );
            }

            m_AMBvisualparkassistProxy = runtime->buildProxy<visualparkassistProxy>(domain, VPAInfoinstance, connectionAMBVPAPxy);
            LOG_INFO(LOG_RVC," start Runtime instance for visualparkassistProxy");

            if(!m_AMBvisualparkassistProxy)
            {
                LOG_INFO(LOG_RVC, " Getting Runtime instance for visualparkassistProxy is failed ");
                l_status = e_ParkAssitFailure;
                break;
            } 
            else
            {
                LOG_INFO(LOG_RVC,"Registering  to visualparkassist Listener");
                //Registering function to vpa AMB interface  for notifying  Availability
                m_AMBvisualparkassistProxy->getProxyStatusEvent().subscribe(std::bind(&CPAMPresctrl::PDCProxyAvilabilityCB,this,_1) );
            } 

            LOG_INFO(LOG_RVC," end Runtime instance for visualparkassistProxy ");

        }
    }while(0);

  
 return l_status;

}

/**
    @brief  initializing and subscribing NSM proxy event
    @param : None
*/

EParkAssitGenRet CPAMPresctrl::InitializeNSMProxy()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess;
    runtime = CommonAPI::Runtime::get();
    if(!runtime)
    {
        LOG_INFO(LOG_RVC,"PAM InitializeAMBProxy Runtime failed");
        l_status = e_ParkAssitFailure;
    }   
    else
    {
        // Getting shared pointer of NSM
        m_NSMProxy = runtime->buildProxy<ConsumerProxy>(domain, NsmInfoinstance, connectionNsmPxy);
        if(!m_NSMProxy)
        {
            LOG_INFO(LOG_RVC,"Getting Runtime instance for NSM proxy ");
            l_status = e_ParkAssitFailure;
        } 
        else
        {
            LOG_INFO(LOG_RVC,"Subscribing to getProxyStatusEvent");
            //Registering function to NSM interface  for notifying it's  Availability
            m_NSMProxy->getProxyStatusEvent().subscribe(std::bind(&CPAMPresctrl::NsmInfoAvailabilityCB,this,_1) );
        }
    }
        return l_status;

}


void CPAMPresctrl::PDCProxyAvilabilityCB( CommonAPI::AvailabilityStatus status )
{
   EParkAssitGenRet l_status = e_ParkAssitSuccess;
   if(status == CommonAPI::AvailabilityStatus::AVAILABLE )
    {
        LOG_INFO(LOG_RVC,"vpa AMB Proxy is Avaliabel") ;

        l_status=  SubScribeToVisualParkAssitEvents();
        if(l_status == e_ParkAssitFailure)
        {
            LOG_INFO(LOG_RVC,"Can't able to subscribe to vpa proxy") ;
        }
    }
    else
    {
        LOG_INFO(LOG_RVC,"vpa AMB Proxy is Not Avaliabel") ;
        l_status = e_ParkAssitFailure;
    }

}
CPAMPresctrl * CPAMPresctrl::getInstance()
{
    if(NULL == m_pobjPAMPresCtrl)
    {
        m_pobjPAMPresCtrl = new CPAMPresctrl;
    }

    return m_pobjPAMPresCtrl;
}

/**
    @brief Subscribing to vpa notification from AMB 
    @param : None
*/
EParkAssitGenRet CPAMPresctrl::SubScribeToVisualParkAssitEvents()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess;
    if(nullptr != m_AMBvisualparkassistProxy)
    {
        //Subscribing to GearPostionNotify attribute
        LOG_INFO(LOG_PDC,"PAM subscribing to VPA Attribute");
        
        if((m_objContext.m_bIsPDCSupported) ||( m_objContext.m_bContextIsAPASupported))
        {
            //Register only if APA and VPA configured
            //This signal is required for both APA and PDC
            m_AMBvisualparkassistProxy->getPrkAidMsgTxt_D_RqAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidMsgTxt_D_Rq_enumAttribute,&m_AMBConsumerHandler,_1));
        }
        if(m_objContext.m_bIsPDCSupported)
        {
            //Register only if PDC is configured
            m_AMBvisualparkassistProxy->getPrkAidSnsFlCrnr_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidSnsFlCrnr_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getPrkAidSnsFlCntr_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidSnsFlCntr_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getPrkAidSnsFrCrnr_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidSnsFrCrnr_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getPrkAidSnsFrCntr_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidSnsFrCntr_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));

            m_AMBvisualparkassistProxy->getPrkAidSnsRlCrnr_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidSnsRlCrnr_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getPrkAidSnsRlCntr_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidSnsRlCntr_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getPrkAidSnsRrCrnr_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidSnsRrCrnr_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getPrkAidSnsRrCntr_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getPrkAidSnsRrCntr_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));

            m_AMBvisualparkassistProxy->getSidePrkSnsL1_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getSidePrkSnsL1_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getSidePrkSnsL2_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getSidePrkSnsL2_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getSidePrkSnsL3_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getSidePrkSnsL3_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getSidePrkSnsL4_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getSidePrkSnsL4_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));

            m_AMBvisualparkassistProxy->getSidePrkSnsR1_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getSidePrkSnsR1_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getSidePrkSnsR2_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getSidePrkSnsR2_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getSidePrkSnsR3_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getSidePrkSnsR3_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
            m_AMBvisualparkassistProxy->getSidePrkSnsR4_D_Stat_enumAttribute().getChangedEvent().subscribe(std::bind(&AMBConsumerHandler::CB_getSidePrkSnsR4_D_Stat_enumAttribute,&m_AMBConsumerHandler,_1));
        }
    }
    else
    {
        LOG_INFO(LOG_PDC,"PAM Unable to subscribe to GearPostionNotify Attribute");
         l_status = e_ParkAssitFailure;
    }
    return l_status;
}


void CPAMPresctrl::ReadEOLServieSupport()
{
    // Read RVC Support
    int l_status = 0;
    int l_EolValue = 0;
    int TransType = 0;
    unsigned long sysSetIDRVC = ADJ_E2P_DIAG_EOL_DE07_HMI_REARVIEW_CAMERA_ID;

    char EOLId[EOL_ID_SIZE];
    memset(EOLId, 0, EOL_ID_SIZE);
    char l_CharEOLRvcData[1] = "";
    
    EOLId[0] = (sysSetIDRVC >> 24) & 0xFF;    
    EOLId[1] = (sysSetIDRVC >> 16) & 0xFF;    
    EOLId[2] = (sysSetIDRVC >> 8) & 0xFF;    
    EOLId[3] = (sysSetIDRVC & 0xFF);

    l_status = pclKeyReadData(PCL_LDBID_EOL, (const char *)EOLId, PCL_STD_USER_NO, PCL_STD_SEAT_NO, (unsigned char*)l_CharEOLRvcData, ADJ_E2P_DIAG_EOL_DE07_HMI_REARVIEW_CAMERA_SIZE);

    if(l_status)
    {
        l_EolValue = l_CharEOLRvcData[0];

        LOG_INFO(LOG_COMMON, "RVC EOL Data is %d", l_EolValue);
        if( 1 ==  l_EolValue)
        {
            LOG_INFO(LOG_RVC, "RVC is Not configured");
            m_objContext.m_bContextIsRVCSupported = false;
        }
        else
        {
            m_objContext.m_bContextIsRVCSupported = true;
            LOG_INFO(LOG_RVC, "RVC is configured");
        }
    }
    else
    {
        //Not able to read the data from persistence and assuming  that RVC is configured
        m_objContext.m_bContextIsRVCSupported = true;
        LOG_INFO(LOG_RVC, "RVC is configured because unable to read");
    }

    
    // Read APA and PDC Support
    unsigned long sysSetIDAPA = ADJ_E2P_DIAG_EOL_DE07_HMI_PARKINGAID_MODE_ID;
    memset(EOLId, 0, EOL_ID_SIZE);
    char l_CharEOLAPAData[1]="";
    
    EOLId[0] = (sysSetIDAPA >> 24) & 0xFF;    
    EOLId[1] = (sysSetIDAPA >> 16) & 0xFF;    
    EOLId[2] = (sysSetIDAPA >> 8) & 0xFF;    
    EOLId[3] = (sysSetIDAPA & 0xFF);


    l_status =  pclKeyReadData(PCL_LDBID_EOL, (const char *)EOLId, PCL_STD_USER_NO, PCL_STD_SEAT_NO, (unsigned char*)l_CharEOLAPAData, ADJ_E2P_DIAG_EOL_DE07_HMI_PARKINGAID_MODE_SIZE);

    if(l_status > 0)
    {
        //  0x1, 0x9 –  value indicates  APA_Cfg=FALSE, PDC_Cfg=FALSE
        //  0x2, 0x3 -   value indicates  APA_Cfg=FALSE, PDC_Cfg=TRUE
        //  0x4, 0x5, 0x6, 0x7, 0x8 – value indicates  APA_Cfg=TRUE, PDC_Cfg=TRUE
        
        l_EolValue = l_CharEOLAPAData[0];
	    LOG_INFO(LOG_COMMON, "RAW EOL Data is %d", l_EolValue);
		TransType = (l_EolValue & 0x20) >> 5 ;
		if(1 == TransType)
		{
			m_objContext.m_eTransType = e_Transmission_Auto;
		}
		else
		{
			m_objContext.m_eTransType = e_Transmission_Manual;
		}
		l_EolValue = (l_EolValue & 0x0f);
        
		LOG_INFO(LOG_COMMON, " EOL for Transmission Type: %d", TransType)
		LOG_INFO(LOG_COMMON, "EOL Data for APA and PDC feature configuration is  %d", l_EolValue);
        if(1 == l_EolValue || 0X9 == l_EolValue)
        {
            m_objContext.m_bContextIsAPASupported = false;
            m_objContext.m_bIsPDCSupported = false;
            LOG_INFO(LOG_COMMON, "APA and PDC Not Supported");
        }
        else if(2 == l_EolValue || 3 == l_EolValue)
        {
            m_objContext.m_bContextIsAPASupported = false;
            m_objContext.m_bIsPDCSupported = true;
            LOG_INFO(LOG_COMMON, "APA Not Supported PDC Supported");

        }
        else
        {
            LOG_INFO(LOG_COMMON, "APA and PDC Supported");
            m_objContext.m_bContextIsAPASupported = true;
            m_objContext.m_bIsPDCSupported = true;
        }
    }
    else
    {
        //Not able to read EOl parameter hence assuming that APA and VPA are active
        m_objContext.m_bContextIsAPASupported = true;
        m_objContext.m_bIsPDCSupported = true;
        LOG_INFO(LOG_COMMON, "APA and PDC Supported because unable to read EOL Data");
    }


	//To be Removed  once EOL parameter reading will be provided by platfrom
//	m_objContext.m_bContextIsAPASupported = true;
 //   m_objContext.m_bIsPDCSupported = true;
//	m_objContext.m_bContextIsRVCSupported = true;
    // Test Code To Read Persisted Data

    int l_intCameraDelay = 0;
    char l_charbuffCameraDelayData[CAMERA_DELAY_DATA_SIZE]; 
    memset(l_charbuffCameraDelayData, 0, CAMERA_DELAY_DATA_SIZE);
    pclKeyReadData(PCL_LDBID_PAM, KEY_CAMERA_DELAY, USER_NUMBER, SEAT_NUMBER, (unsigned char*)l_charbuffCameraDelayData, CAMERA_DELAY_DATA_SIZE);
    l_intCameraDelay = atoi(l_charbuffCameraDelayData);
    LOG_INFO(LOG_COMMON,"Camera Delay Setting in read persistency is %d", l_intCameraDelay);
    m_objContext.m_bIsCameraDealyOn = l_intCameraDelay;



    int l_intEnhancedParkAid = 0;
    char l_charbuffEnhancedParkAid[ENHANCED_PARK_AID_DATA_SIZE]; 
    memset(l_charbuffCameraDelayData, 0, ENHANCED_PARK_AID_DATA_SIZE);
    pclKeyReadData(PCL_LDBID_PAM, KEY_ENHANCED_PARK_AID, USER_NUMBER, SEAT_NUMBER, (unsigned char*)l_charbuffEnhancedParkAid, ENHANCED_PARK_AID_DATA_SIZE);
    l_intEnhancedParkAid = atoi(l_charbuffEnhancedParkAid);
    LOG_INFO(LOG_COMMON,"EnhancedParkAid Setting in read persistency is %d", l_intEnhancedParkAid);
    m_objContext.m_bIsEnahancedParkAidOn = l_intEnhancedParkAid;

}

void CPAMPresctrl::PAMSrv_InitializePersistency()
{
    //Initializing Persistency
    pclInitLibrary(APP_NAME, PCL_SHUTDOWN_TYPE_NONE);
    LOG_INFO(LOG_COMMON, "initPersLibrary.Done");
}

void CPAMPresctrl::PAMSrv_DeinitializePersistency()
{
    pclDeinitLibrary();
    LOG_INFO(LOG_COMMON, "DeInitPersLibrary.Done");
}

EParkAssitGenRet CPAMPresctrl::RegisterRVCServiceToDBus()
{
    EParkAssitGenRet l_status = e_ParkAssitSuccess;
    std::string connection = "ParkAssist";
    runtime = CommonAPI::Runtime::get();
    if(!runtime)
    {
        //Not able to get Runtime instance
        LOG_INFO(LOG_RVC,"PAM RegisterRVCServiceToDBus Runtime failed");
        l_status = e_ParkAssitFailure;
    
    }
    else
    {
        //Creating  RVC Presctrl and registering with  Dbus
        std::string instance = "ParkAssist.RVCInstance";
        runtime->registerService(domain, instance, m_pobjRVCServiceStub, connection);

        //Providing Camera info and body control info handle AMB provide class . So AMB provider can interact with AMB for sending CAN signal
        m_AMBProviderHandler.InitializeAMBProviderHandler(m_pobjAMBCamerainfoProxy, m_pobjAMBBodyCntlInfoProxy, m_AMBApaPxy);
        LOG_INFO(LOG_RVC,"PAM Registering RVC service");
    }
    return l_status; 
}
EParkAssitGenRet CPAMPresctrl::RegisterAPAServiceToDBus()
{
    LOG_INFO(LOG_PDC, "RegisterAPAServiceToDBus Started...\n");
    
    EParkAssitGenRet l_eRet = e_ParkAssitSuccess;
    runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string connection = "ParkAssist";
    std::string instance = "ParkAssist.APAInstance";
    if(NULL == runtime)
    {
        l_eRet = e_ParkAssitFailure;
        LOG_ERROR(LOG_PDC,"PAM RegisterAPAServiceToDBus Runtime failed");
        
    }
    else
    {
        LOG_INFO(LOG_PDC,"PAM RegisterAPAServiceToDBus Successs");
        runtime->registerService(domain, instance, m_pobjAPAStub, connection);
    }
    return l_eRet;
}
EParkAssitGenRet CPAMPresctrl::RegisterPDCServiceToDBus()
{
    LOG_INFO(LOG_PDC, "RegisterPDCServiceToDBus Started...\n");
    EParkAssitGenRet l_status = e_ParkAssitSuccess;
    std::string connection = "ParkAssist";
    runtime = CommonAPI::Runtime::get();
    if(!runtime)
    {
        //Not able to get Runtime instance
        LOG_ERROR(LOG_PDC,"PAM RegisterPDCServiceToDBus Runtime failed");
        l_status = e_ParkAssitFailure;
    }
    else
    {
        //Creating  RVC Presctrl and registering with  Dbus
        LOG_INFO(LOG_PDC,"PAM RegisterPDCServiceToDBus Successs");
        std::string instance = "ParkAssist.PDCInstance";
        runtime->registerService(domain, instance, m_PDCServiceStub, connection);
    }
    return l_status;   
}
