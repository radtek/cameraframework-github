/*********************************************************************
* Project         Ford LCIS- Park-Asist
* (c) copyright   2016
* Company         Harman International
*                 All rights reserved
*
*Secrecy Level    STRICTLY CONFIDENTIAL
*********************************************************************/
/**
* @file            Commoncore.hpp
* @ingroup         Park-Asist
* @author          Atita Halemani and Ashwini Shamaprasad (Atita.Halemani@harman.com and Ashwini.Shamaprasad@harman.com)
* @brief           Adding common header files 
*                  
*/

#ifndef PARK_ASSIST_TABLE_CONTAINER_HPP
#define PARK_ASSIST_TABLE_CONTAINER_HPP

#include "ParkAssistSrv_Common/CommonCore.hpp"

std::unordered_map<uint16_t, const char*> ParkAssistLoggingContexts = {
    { LOG_RVC,"RVC" }
    ,{ LOG_APA, "APA" }
    ,{ LOG_PDC, "PDC" }
    ,{ LOG_COMMON, "PARK_COMMON"}
};
    
// Update this map immediately as soon as one new reqid is added
std::unordered_map <uint64_t, Request> ParkAssistRequestList = {
        
    // RVC ReqIDs
    {e_ParkAssist_RVC_ZOOM_REQUEST,  {"SetZoomRequest", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u }},
	{e_ParkAssist_RVC_SPLITVIEW_REQUEST, {"SplitViewReq", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_GUIDELINES_REQUEST, {"RVCGuideLines", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_SPLITVIEW_RESPONSE, {"SplitViewResp", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_VEHICLE_CHAR_NTFY, {"VehCharNtfy", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_GEAR_POSTION, {"GearPosition", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_VEHICLE_MAXSPEED, {"VehicleSpeed", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_PARK_BREAK_ACTIVE_STATUS, {"ParkBrakeStatus", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_DOOR_OPEN_STATUS, {"DoorOpenStatus", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_NSM_STATUS, {"NsmStatus", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_IGNITION_STATUS, {"IginitionStatus", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_ENHANCEDMODE_REQUEST, {"EnhancedParkMode", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_MANUAL_GEAR_STATUS, {"ManualGearStatus", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_RVC_PDC_GUIDE_STATUS, {"PDCGuideStatus", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_RVC_CAMERA_ZOOM_STATUS, {"CameraZoomStatus", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
	{e_ParkAssist_RVC_ELEC_PARK_BREAK_STATUS, {"ElecBrkStatus", e_PARKASSIST_RVC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    //APA ReqIDs
    
    {e_ParkAssist_APA_SET_APAMODE_REQ, {"APAModeReq", e_PARKASSIST_APA_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_APA_PARKAID_HS3_DATA_UPDATE_NTFY, {"ParkAidHS3DataUpdate", e_PARKASSIST_APA_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_APA_ACTIVE_APA_MODE_UPDATE_NTFY, {"ActiveModeUpdate", e_PARKASSIST_APA_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_APA_GEARSHIFT_REQ_DRIVER_STATUS_UPDATE_NTFY, {"GearShiftReqStatus", e_PARKASSIST_APA_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},

    // PDC ReqIds

    {e_ParkAssist_VPA_PARKAID_MSGTXT_UPDATE, {"ParkAidMsgTxtUpdate", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_RICRNR_UPDATE, {"ParkSensorRICRNR", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_RICNTR_UPDATE, {"ParkSensorRICNTR", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_RRCNTR_UPDATE, {"ParkSensorRRCNTR", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_RRCRNR_UPDATE, {"ParkSensorRRCRNR", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_FICRNR_UPDATE, {"ParkSensorFICRNR", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_FRCRNR_UPDATE, {"ParkSensorFRCRNR", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_FRCNTR_UPDATE, {"ParkSensorFRCNTR", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},    
    {e_ParkAssist_VPA_PARKAID_SENSOR_FICNTR_UPDATE, {"ParkSensorFICNTR", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_L1_UPDATE, {"ParkSensorL1", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_L2_UPDATE, {"ParkSensorL2", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_L3_UPDATE, {"ParkSensorL3", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_L4_UPDATE, {"ParkSensorL4", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_R1_UPDATE, {"ParkSensorR1", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_R2_UPDATE, {"ParkSensorR2", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_R3_UPDATE, {"ParkSensorR3", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_PARKAID_SENSOR_R4_UPDATE, {"ParkSensorR4", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},
    {e_ParkAssist_VPA_CANCEL_PDC_REQUEST, {"CancelPDCReq", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}},


    {e_ParkAssist_MANAGE_SCREEN_POSITION, {"ManageScreen", e_PARKASSIST_PDC_GROUP, e_REQUEST_CANCEL_OLD_REQ, 0u}}

};




#endif
