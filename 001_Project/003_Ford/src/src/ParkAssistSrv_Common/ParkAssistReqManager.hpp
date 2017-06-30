/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            ParkAssistReqManager.hpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           AMBConsumerHandler Consumes events from AMB and routes to required module(RVC,APA and VPA)
*                  based on the events it received.
*                  
*/

#ifndef PARKASSIST_REQ_MANAGER_HPP
#define PARKASSIST_REQ_MANAGER_HPP
#include "ParkAssistSrv_Manager/CPAMPresctrl.hpp"

// ============================================RVC SECTION START===============================================================//

class ZoomRequest : public RequestBase
{
    public:
        ZoomRequest():RequestBase(e_ParkAssist_RVC_ZOOM_REQUEST, "ZoomRequest")
        {
            LOG_INFO(LOG_RVC, "Zoom Request Created...\n");
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class SplitViewRequest : public RequestBase
{
    public :
        SplitViewRequest():RequestBase(e_ParkAssist_RVC_SPLITVIEW_REQUEST, "SplitViewRequest")
        {
            LOG_INFO(LOG_RVC, "SplitViewRequest Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class EnhancedParkModeRequest : public RequestBase
{
    public :
        EnhancedParkModeRequest():RequestBase(e_ParkAssist_RVC_ENHANCEDMODE_REQUEST, "EnhancedParkModeRequest")
        {
            LOG_INFO(LOG_RVC, "EnhancedParkModeRequest Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class FixedCameraSetting : public RequestBase
{
    public :
        FixedCameraSetting():RequestBase(e_ParkAssist_RVC_GUIDELINES_REQUEST, "FixedCameraSetting")
        {
            LOG_INFO(LOG_RVC, "FixedCameraSetting Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class VehicleCharNtfy : public RequestBase
{
    public :
        VehicleCharNtfy():RequestBase(e_ParkAssist_RVC_VEHICLE_CHAR_NTFY, "VehicleCharNtfy")
        {
            LOG_INFO(LOG_RVC, "VehicleCharNtfy Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};


class PDCGuideStatus : public RequestBase
{
    public :
        PDCGuideStatus():RequestBase(e_ParkAssist_RVC_PDC_GUIDE_STATUS, "PDCGuideStatus")
        {
            LOG_INFO(LOG_RVC, "PDCGuideStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class CameraZoomStatus : public RequestBase
{
    public :
        CameraZoomStatus():RequestBase(e_ParkAssist_RVC_CAMERA_ZOOM_STATUS, "CameraZoomStatus")
        {
            LOG_INFO(LOG_RVC, "CameraZoomStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ElecBrkStatus : public RequestBase
{
    public :
        ElecBrkStatus():RequestBase(e_ParkAssist_RVC_ELEC_PARK_BREAK_STATUS, "ElecBrkStatus")
        {
            LOG_INFO(LOG_RVC, "ElecBrkStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class CameraSplitViewStatus : public RequestBase
{
    public :
        CameraSplitViewStatus():RequestBase(e_ParkAssist_RVC_SPLITVIEW_RESPONSE, "CameraSplitViewStatus")
        {
            LOG_INFO(LOG_RVC, "CameraSplitViewStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class CurrentGearPostion : public RequestBase
{
    public :
        CurrentGearPostion():RequestBase(e_ParkAssist_RVC_GEAR_POSTION, "CurrentGearPostion")
        {
            LOG_INFO(LOG_RVC, "CurrentGearPostion Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class VehicleSpeedNotify : public RequestBase
{
    public :
        VehicleSpeedNotify():RequestBase(e_ParkAssist_RVC_VEHICLE_MAXSPEED, "VehicleSpeedNotify")
        {
            LOG_INFO(LOG_RVC, "VehicleSpeedNotify Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class ParkBrkActvStatus : public RequestBase
{
    public :
        ParkBrkActvStatus():RequestBase(e_ParkAssist_RVC_PARK_BREAK_ACTIVE_STATUS, "ParkBrkActvStatus")
        {
            LOG_INFO(LOG_RVC, "ParkBrkActvStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class DoorOpenStatus : public RequestBase
{
    public :
        DoorOpenStatus():RequestBase(e_ParkAssist_RVC_DOOR_OPEN_STATUS, "DoorOpenStatus")
        {
            LOG_INFO(LOG_RVC, "DoorOpenStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class NsmStatus : public RequestBase
{
    public :
        NsmStatus():RequestBase(e_ParkAssist_RVC_NSM_STATUS, "NsmStatus")
        {
            LOG_INFO(LOG_RVC, "NsmStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

class ManualGearStatus : public RequestBase
{
    public :
        ManualGearStatus():RequestBase(e_ParkAssist_RVC_MANUAL_GEAR_STATUS, "ManualGearStatus")
        {
            LOG_INFO(LOG_RVC, "ManualGearStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class IgnStatus : public RequestBase
{
    public :
        IgnStatus():RequestBase(e_ParkAssist_RVC_IGNITION_STATUS, "IgnStatus")
        {
            LOG_INFO(LOG_RVC, "IgnStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};


class ParkAidHS3DataUpdate : public RequestBase
{
    public :
        ParkAidHS3DataUpdate():RequestBase(e_ParkAssist_APA_PARKAID_HS3_DATA_UPDATE_NTFY, "ParkAidHS3DataUpdate")
        {
            LOG_INFO(LOG_APA, "ParkAidHS3DataUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();
        void APASystemStatusUpdate();
        void ScanStatusUpdate();
        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};


// ============================================RVC SECTION END===============================================================//



// ============================================APA SECTION START===============================================================//


class ActiveApaModeUpdate : public RequestBase
{
    public :
        ActiveApaModeUpdate():RequestBase(e_ParkAssist_APA_ACTIVE_APA_MODE_UPDATE_NTFY, "ActiveApaModeUpdate")
        {
            LOG_INFO(LOG_APA, "ActiveApaModeUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};


class GearShiftReqDriverStatus : public RequestBase
{
    public :
        GearShiftReqDriverStatus():RequestBase(e_ParkAssist_APA_GEARSHIFT_REQ_DRIVER_STATUS_UPDATE_NTFY, "GearShiftReqDriverStatus")
        {
            LOG_INFO(LOG_APA, "GearShiftReqDriverStatus Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};




class SetApaModeReq : public RequestBase
{
    public :
        SetApaModeReq():RequestBase(e_ParkAssist_APA_SET_APAMODE_REQ, "SetApaModeReq")
        {
            LOG_INFO(LOG_APA, "SetApaModeReq Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};

// ============================================APA SECTION END===============================================================//


// ============================================PDC SECTION START===============================================================//


class ParkAidMsgTxtUpdate : public RequestBase
{
    public :
        ParkAidMsgTxtUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_MSGTXT_UPDATE, "ParkAidMsgTxtUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidMsgTxtUpdate Created...\n");   
            cout << "ParkAidMsgTxtUpdate Created...\n";
        }

        virtual void onRun();
        virtual void onCancelled();
        void CalculatePDCScreenLayout(bool p_bPDCStatus);
        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorRiCrnrUpdate : public RequestBase
{
    public :
        ParkAidSensorRiCrnrUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_RICRNR_UPDATE, "ParkAidSensorRiCrnrUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorRiCrnrUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorRiCntrUpdate : public RequestBase
{
    public :
        ParkAidSensorRiCntrUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_RICNTR_UPDATE, "ParkAidSensorRiCntrUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorRiCntrUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorRrCntrUpdate : public RequestBase
{
    public :
        ParkAidSensorRrCntrUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_RRCNTR_UPDATE, "ParkAidSensorRrCntrUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorRrCntrUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorRrCrnrUpdate : public RequestBase
{
    public :
        ParkAidSensorRrCrnrUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_RRCRNR_UPDATE, "ParkAidSensorRrCrnrUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorRrCrnrUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorFiCrnrUpdate : public RequestBase
{
    public :
        ParkAidSensorFiCrnrUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_FICRNR_UPDATE, "ParkAidSensorFiCrnrUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorFiCrnrUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorFrCrnrUpdate : public RequestBase
{
    public :
        ParkAidSensorFrCrnrUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_FRCRNR_UPDATE, "ParkAidSensorFrCrnrUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorFrCrnrUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorFrCntrUpdate : public RequestBase
{
    public :
        ParkAidSensorFrCntrUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_FRCNTR_UPDATE, "ParkAidSensorFrCntrUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorFrCntrUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorFiCntrUpdate : public RequestBase
{
    public :
        ParkAidSensorFiCntrUpdate():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_FICNTR_UPDATE, "ParkAidSensorFiCntrUpdate")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorFiCntrUpdate Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorL1Update : public RequestBase
{
    public :
        ParkAidSensorL1Update():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_L1_UPDATE, "ParkAidSensorL1Update")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorL1Update Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorL2Update : public RequestBase
{
    public :
        ParkAidSensorL2Update():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_L2_UPDATE, "ParkAidSensorL2Update")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorL2Update Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorL3Update : public RequestBase
{
    public :
        ParkAidSensorL3Update():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_L3_UPDATE, "ParkAidSensorL3Update")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorL3Update Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorL4Update : public RequestBase
{
    public :
        ParkAidSensorL4Update():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_L4_UPDATE, "ParkAidSensorL4Update")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorL4Update Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorR1Update : public RequestBase
{
    public :
        ParkAidSensorR1Update():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_R1_UPDATE, "ParkAidSensorR1Update")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorR1Update Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorR2Update : public RequestBase
{
    public :
        ParkAidSensorR2Update():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_R2_UPDATE, "ParkAidSensorR2Update")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorR2Update Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorR3Update : public RequestBase
{
    public :
        ParkAidSensorR3Update():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_R3_UPDATE, "ParkAidSensorR3Update")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorR3Update Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
class ParkAidSensorR4Update : public RequestBase
{
    public :
        ParkAidSensorR4Update():RequestBase(e_ParkAssist_VPA_PARKAID_SENSOR_R4_UPDATE, "ParkAidSensorR4Update")
        {
            LOG_INFO(LOG_PDC, "ParkAidSensorR4Update Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};


class CancelPDCReq : public RequestBase
{
    public :
        CancelPDCReq():RequestBase(e_ParkAssist_VPA_CANCEL_PDC_REQUEST, "CancelPDCReq")
        {
            LOG_INFO(LOG_PDC, "CancelPDCReq Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};
// ============================================PDC SECTION END===============================================================//

//================================================COMMON======================================================================//


class ManageScreenPositioning : public RequestBase
{
    public :
        ManageScreenPositioning():RequestBase(e_ParkAssist_MANAGE_SCREEN_POSITION, "ManageScreenPositioning")
        {
            LOG_INFO(LOG_PDC, "ManageScreenPositioning Created...\n");       
        }

        virtual void onRun();
        virtual void onCancelled();

        private:
            EParkAssistReqId m_eReqId;
            int SequenceNum;
};


#endif
