#ifndef PAM_CONTEXT_HPP
#define PAM_CONTEXT_HPP

// This class is responsible for storing all necessary data for decision making

#include "ParkAssistSrv_Common/CommonCore.hpp"
#include "v0/com/harman/ParkAssist/APAServiceStubDefault.hpp"
#include "v0/com/harman/ParkAssist/RVCServiceStubDefault.hpp"
#include "v0/com/harman/ParkAssist/PDCServiceStubDefault.hpp"

#include "v0/org/harman/ford/actvparkassist.hpp"
#include "v0/org/harman/ford/enginedata.hpp"
#include "v0/org/harman/ford/bodycontroldata.hpp"
#include "v0/org/harman/ford/camerainfo.hpp"
#include "v0/org/harman/ford/rearviewcamclient.hpp"

using namespace v0::org::harman::ford;
using namespace v2::org::genivi::NodeStateManager;

// Enum defines the signals with unique values to be used for the tables
typedef enum _EPersistencyParam
{
    e_Persistency_Invalid   	  = -1,
	e_Persistency_CameraDelay     = 0,
	e_Persistency_EnhancedMode    = 1,

    
}EPersistencyParam;

// Enum defines the signals with unique values to be used for the tables
typedef enum _ETransmissionType
{
    e_Transmission_Invalid        = -1,
    e_Transmission_Manual         = 0,
    e_Transmission_Auto           = 1,

    
}ETransmissionParam;
class CContext
{
    public:
        CContext();
        ~CContext();

// ================================================== APA SECTION START =====================================================================
        int m_intApaSys_D_Stat = -1, m_intApaSteScanMde_D_Stat = -1, m_intApaActvSide2_D_Stat = -1, m_intApaMde_D_Stat = -1;
        int m_intApaSelSapp_D_Stat  = -1, m_intApaSelPpa_D_Stat = -1, m_intApaSelPoa_D_Stat = -1, m_intApaScan_D_Stat  = -1;
        int m_intApaLongCtl_D_RqDrv = -1, m_intApaGearShif_D_RqDrv = -1, m_intApaSteWhl_D_RqDrv = -1, m_intApaAcsy_D_RqDrv = -1;
        int m_intApaTrgtDist_D_Stat = -1, m_intApaMsgTxt_D_Rq = -1, m_intApaPrkAidMsgTxt_D_Rq = -1;

        // Required to Update APA Feature Availability Attribute to HMI
        bool m_bIsScanInProgress;
// =================================================== APA SECTION END ========================================================================

        int m_intContextCamPDCGuidStat, m_intContextCamraOvrlDyn, m_intContextCamraOvrlStat, m_intContextCamraZoom,m_intContextCamraSplitView;

        v1::com::harman::ParkAssist::APABaseType::enAPAMode m_eContextAPAModeReq;
        bodycontroldata_types::GearLvrPos_D_Actl_enum m_eContextGearLvrPos;
        enginedata_types::PrkBrkActv_B_Actl_enum m_eContextPrkBrkActvStatus;
		enginedata_types::PrkBrkStatus_enum m_eContextElePrkStatus;
        enginedata_types::DrStatTgate_B_Actl_enum m_eContextDoorOpenStatus;
        bool m_bContextCameraMaxSpeed;
        bool m_bContextNsmSessionState;
        rearviewcamclient_types::GearRvrse_D_Actl_enum m_eRevGearStatus;
        actvparkassist_types::ApaSys_D_Stat_enum m_eContextApaStatus;
        actvparkassist_types::ApaGearShif_D_RqDrv_enum m_eContextApaGearShifStatus;
        bool m_bContextIgnStatus;
        bool m_bIsRVCOn, m_bIsAPAOn, m_bIsPDCOn;

        
        // PDC Data Starts


        int m_intContextPrkAidMsgTxt = 0, m_intContextPrkAidSnsRlCrnr = 0, m_intContextPrkAidSnsRlCntr= 0, m_intContextPrkAidSnsRrCntr = 0;
        int m_intContextPrkAidSnsRrCrnr = 0, m_intContextPrkAidSnsFlCrnr = 0, m_intContextPrkAidSnsFlCntr = 0, m_intContextPrkAidSnsFrCntr = 0, m_intContextPrkAidSnsFrCrnr = 0;
        int m_intContextSidePrkSnsL1 = 0, m_intContextSidePrkSnsL2 = 0, m_intContextSidePrkSnsL3 = 0, m_intContextSidePrkSnsL4 = 0;
        int m_intContextSidePrkSnsR1 = 0, m_intContextSidePrkSnsR2 = 0, m_intContextSidePrkSnsR3 = 0, m_intContextSidePrkSnsR4 = 0;


        //EOL Data Section

        bool m_bContextIsRVCSupported, m_bContextIsAPASupported, m_bIsPDCSupported;
        bool m_bIsCameraDealyOn, m_bIsEnahancedParkAidOn;

        // Timer Configuration

        int m_intPDC_Actv_MM_Timr_CfgData, m_intPDC_Fault_Timr_CfgData , m_intCamra_Fault_Timr_CfgData , 
            m_intAPA_Actv_MM_Timr_CfgData , m_intCamra_Exit_Timr_CfgData ;
        
        void WriteDataToPersistency(EPersistencyParam l_ePersistencyParam);
		ETransmissionParam m_eTransType;

        void ReadTimerConfigurationFile();

    private :
        
        unsigned int m_ContextUser_no;
        unsigned int m_ContextSeat_no;  
};

#endif
