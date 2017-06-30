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

#ifndef COMMON_CORE_HPP
#define COMMON_CORE_HPP

#include<memory>
#include<thread>
#include<condition_variable>
#include <mutex>
#include <chrono>
#include <iostream>
#include <string>
#include<queue>
#include<atomic>
#include<stdint.h>
#include <algorithm>
#include <functional>
#include <chrono>
#include <unordered_map>
#include <set>
#include <cstdint>
#include <CommonAPI/CommonAPI.hpp>
#include <fstream>


#include "PAMPresctrl_Utils.h"
#include "Timer.hpp"
#include "v0/org/harman/ford/rearviewcamclientProxy.hpp"
#include "v0/org/harman/ford/rearviewcamclient.hpp"
#include "v0/org/harman/ford/camerainfoProxy.hpp"
#include "v0/org/harman/ford/camerainfo.hpp"
#include "v0/org/harman/ford/bodycontroldataProxy.hpp"
#include "v0/org/harman/ford/bodycontroldata.hpp"
#include "v0/org/harman/ford/enginedata.hpp"
#include "v0/org/harman/ford/enginedataProxy.hpp"
#include "v2/org/genivi/NodeStateManager/Consumer.hpp"
#include "v2/org/genivi/NodeStateManager/ConsumerProxy.hpp"
#include "v0/org/harman/ford/actvparkassist.hpp"
#include "v0/org/harman/ford/actvparkassistProxy.hpp"
#include "v0/org/harman/ford/visualparkassistProxy.hpp"
#include "v0/org/harman/ford/visualparkassist.hpp"


#include <core/PresCtrl.h>
#include <core/RequestBase.h>
#include <core/logging.h>
#include <core/CommonAPIClientAbstraction.h>

#define RVC_MAX_VEHICLE_SPEED 10
#define STANDARD_TIMEOUT_AMB_VALUE -10
#define LOG_RVC 1
#define LOG_APA 2
#define LOG_PDC 3
#define LOG_COMMON 4
typedef enum _EParkAssistGenRet
{
    e_ParkAssitFailure,
    e_ParkAssitSuccess
}EParkAssitGenRet;


typedef enum _EParkAssistReqIds
{

// Start RVC ReqIds
    e_ParkAssist_RVC_ZOOM_REQUEST = 1 ,
    e_ParkAssist_RVC_SPLITVIEW_REQUEST ,
    e_ParkAssist_RVC_SPLITVIEW_RESPONSE ,
    e_ParkAssist_RVC_VECHILE_CHARACTERISTIC ,
    e_ParkAssist_RVC_GEAR_POSTION ,
    e_ParkAssist_RVC_PARK_BREAK_ACTIVE_STATUS ,
    e_ParkAssist_RVC_OFF_REQUEST ,
    e_ParkAssist_RVC_ENHANCEDMODE_REQUEST ,
    e_ParkAssist_RVC_GUIDELINES_REQUEST ,
    e_ParkAssist_RVC_VEHICLE_MAXSPEED ,
    e_ParkAssist_RVC_EXIT_REQUEST ,
    e_ParkAssist_RVC_DOOR_OPEN_STATUS ,
    e_ParkAssist_RVC_MANUAL_GEAR_STATUS ,
    e_ParkAssist_RVC_VEHICLE_CHAR_NTFY,
    e_ParkAssist_RVC_NSM_STATUS,
	e_ParkAssist_RVC_IGNITION_STATUS,
	e_ParkAssist_RVC_PDC_GUIDE_STATUS,
    e_ParkAssist_RVC_CAMERA_ZOOM_STATUS,
    e_ParkAssist_RVC_ELEC_PARK_BREAK_STATUS,

    
// End Rvc ReqIds

// Start of APA ReqIds
    e_ParkAssist_APA_SET_APAMODE_REQ,
    e_ParkAssist_APA_ACTIVE_APA_MODE_UPDATE_NTFY,
    e_ParkAssist_APA_GEARSHIFT_REQ_DRIVER_STATUS_UPDATE_NTFY,


    e_ParkAssist_APA_PARKAID_HS3_DATA_UPDATE_NTFY,

// End APA ReqIds


// Start Of PDC ReqIds

    e_ParkAssist_VPA_PARKAID_MSGTXT_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_RICRNR_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_RICNTR_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_RRCNTR_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_RRCRNR_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_FICRNR_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_FRCRNR_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_FRCNTR_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_FICNTR_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_L1_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_L2_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_L3_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_L4_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_R1_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_R2_UPDATE,
    e_ParkAssist_VPA_PARKAID_SENSOR_R3_UPDATE, 
    e_ParkAssist_VPA_PARKAID_SENSOR_R4_UPDATE,
    e_ParkAssist_VPA_CANCEL_PDC_REQUEST,
//End Of PDC ReqIds

e_ParkAssist_MANAGE_SCREEN_POSITION
    
}EParkAssistReqId;

typedef enum _EParkAssistGroups
{
    e_PARKASSIST_RVC_GROUP,
    e_PARKASSIST_APA_GROUP,
    e_PARKASSIST_PDC_GROUP
}EParkAssistGroup;


// Persistency Criterias
// ===============================================================================
//Including Persistency Headers
#include "persistence_client_library_file.h"
#include "persistence_client_library_key.h"
#include "persistence_client_library.h"

#define USER_NUMBER 1
#define SEAT_NUMBER 1
#define KEY_CAMERA_DELAY "CAMERA_DELAY"
#define KEY_ENHANCED_PARK_AID "ENHANCED_PARK_AID"
#define PCL_LDBID_PAM 0XFFFF
#define CAMERA_DELAY_DATA_SIZE 4
#define ENHANCED_PARK_AID_DATA_SIZE 4

#endif
