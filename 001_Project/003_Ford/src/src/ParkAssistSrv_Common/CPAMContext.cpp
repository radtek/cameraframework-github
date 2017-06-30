#include "CPAMContext.hpp"

#define CFG_FILE_PATH "/mnt/data/PAM_Configuration/Timer.cfg"

CContext::CContext():m_bContextIsRVCSupported(false),m_bContextIsAPASupported(false),m_bIsPDCSupported(false)
{
    LOG_INFO(LOG_COMMON,"CContext constructor");

    m_intContextCamPDCGuidStat = 0;
    m_intContextCamraOvrlDyn = 0;
    m_intContextCamraOvrlStat = 0;
    m_intContextCamraZoom = 0;
    m_intContextCamraSplitView = 0;
    m_bContextCameraMaxSpeed= false;
    m_eContextGearLvrPos =  bodycontroldata_types::GearLvrPos_D_Actl_enum::En_Unknown_Position;
    m_eContextPrkBrkActvStatus = enginedata_types::PrkBrkActv_B_Actl_enum::En_Inactive;
    m_eContextElePrkStatus = enginedata_types::PrkBrkStatus_enum::En_Not_Used;
    m_eContextDoorOpenStatus = enginedata_types::DrStatTgate_B_Actl_enum ::En_Closed;
    m_bContextNsmSessionState = false;
    m_bContextIgnStatus = false;
    m_eRevGearStatus = rearviewcamclient_types::GearRvrse_D_Actl_enum::En_NotUsed_1;
    m_eContextApaGearShifStatus = actvparkassist_types::ApaGearShif_D_RqDrv_enum::En_NotUsed_1;
    m_bIsRVCOn = false;
    m_bIsAPAOn = false;
    m_bIsPDCOn = false;
    m_bIsCameraDealyOn = false;
    m_bIsEnahancedParkAidOn = false;
    m_ContextUser_no = USER_NUMBER;
    m_ContextSeat_no = SEAT_NUMBER;
    m_bIsScanInProgress = false;
    m_eTransType = e_Transmission_Invalid;
    m_intPDC_Actv_MM_Timr_CfgData = 250;
    m_intPDC_Fault_Timr_CfgData = 250;
    m_intCamra_Fault_Timr_CfgData = 1000;
    m_intAPA_Actv_MM_Timr_CfgData = 250;
    m_intCamra_Exit_Timr_CfgData = 2000;


    ReadTimerConfigurationFile();

}

CContext::~CContext()
{
    // Storing Data to persistency
    LOG_INFO(LOG_COMMON, "CContext::~CContext() Called...");
}

void CContext::WriteDataToPersistency(EPersistencyParam l_ePersistencyParam)
{
    int retVal = 0;
    char l_buff[CAMERA_DELAY_DATA_SIZE] ;
    char l_buffEnhancedParkAid[ENHANCED_PARK_AID_DATA_SIZE] ;
    
    LOG_INFO(LOG_COMMON, "CContext::WriteAmbientColorToPersistency :: Camera Delay is [%d] and Enhanced Park Aid is [%d]", 
        m_bIsCameraDealyOn, m_bIsEnahancedParkAidOn);
    
    if(e_Persistency_CameraDelay == l_ePersistencyParam)
    {   
        memset(l_buff, 0, CAMERA_DELAY_DATA_SIZE);    
        snprintf(l_buff, CAMERA_DELAY_DATA_SIZE, "%d", m_bIsCameraDealyOn);
        
        retVal = pclKeyWriteData(PCL_LDBID_PAM, KEY_CAMERA_DELAY, m_ContextUser_no, m_ContextSeat_no, (unsigned char*)(l_buff), CAMERA_DELAY_DATA_SIZE);
        LOG_INFO(LOG_COMMON,"NO ofBytes written Camera Delay %d", retVal);
    }
    else if(e_Persistency_EnhancedMode == l_ePersistencyParam)
    {
        memset(l_buffEnhancedParkAid, 0, ENHANCED_PARK_AID_DATA_SIZE);    
        snprintf(l_buffEnhancedParkAid, ENHANCED_PARK_AID_DATA_SIZE, "%d", m_bIsEnahancedParkAidOn);
        retVal = pclKeyWriteData(PCL_LDBID_PAM, KEY_ENHANCED_PARK_AID, m_ContextUser_no, m_ContextSeat_no, (unsigned char*)(l_buffEnhancedParkAid), ENHANCED_PARK_AID_DATA_SIZE);
        LOG_INFO(LOG_COMMON,"NO ofBytes written Enhanced Park Aid %d", retVal);
    }   
}

void CContext::ReadTimerConfigurationFile()
{
    LOG_INFO(LOG_COMMON, "CContext::ReadTimerConfigurationFile()...");
    ifstream ifs(CFG_FILE_PATH);  


    do
    {
        if(ifs.fail())
        {
            LOG_ERROR(LOG_COMMON, "ReadTimerConfigurationFile():: File open failed");
            break;
        }

        if(ifs.is_open())
        {
            LOG_INFO(LOG_COMMON, "ReadTimerConfigurationFile() :: File Open Success");
            string TimerCfgData((istreambuf_iterator<char>(ifs)),                        
            (istreambuf_iterator<char>() ));

            int pos = TimerCfgData.find("APA_Actv_MM_Timr_Cfg");
            int require_pos = pos + strlen("APA_Actv_MM_Timr_Cfg") + 1 ;// this is for "="

            m_intAPA_Actv_MM_Timr_CfgData = stoi(TimerCfgData.substr(require_pos));


            LOG_INFO(LOG_COMMON, "requiredData ::APA_Actv_MM_Timr_Cfg is %d", m_intAPA_Actv_MM_Timr_CfgData );

            pos = TimerCfgData.find("Camra_Fault_Timr_Cfg");
            require_pos = pos + strlen("Camra_Fault_Timr_Cfg") + 1 ;// this is for "="

            m_intCamra_Fault_Timr_CfgData = stoi(TimerCfgData.substr(require_pos));

            LOG_INFO(LOG_COMMON, "requiredData ::Camra_Fault_Timr_Cfg is %d", m_intCamra_Fault_Timr_CfgData );


            pos = TimerCfgData.find("PDC_Fault_Timr_Cfg");
            require_pos = pos + strlen("PDC_Fault_Timr_Cfg") + 1 ;// this is for "="

            m_intPDC_Fault_Timr_CfgData = stoi(TimerCfgData.substr(require_pos));

            LOG_INFO(LOG_COMMON, "requiredData ::PDC_Fault_Timr_Cfg is %d", m_intPDC_Fault_Timr_CfgData );


            pos = TimerCfgData.find("PDC_Actv_MM_Timr_Cfg");
            require_pos = pos + strlen("PDC_Actv_MM_Timr_Cfg") + 1 ;// this is for "="

            m_intPDC_Actv_MM_Timr_CfgData = stoi(TimerCfgData.substr(require_pos));
            LOG_INFO(LOG_COMMON, "requiredData ::PDC_Actv_MM_Timr_Cfg is %d", m_intPDC_Actv_MM_Timr_CfgData );
        }

        ifs.close();
    }while(0);
}

