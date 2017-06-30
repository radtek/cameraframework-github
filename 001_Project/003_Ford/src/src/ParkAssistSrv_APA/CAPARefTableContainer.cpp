#include "CAPARefTableContainer.hpp"
#include "ParkAssistSrv_Manager/CPAMPresctrl.hpp"

using namespace std;

CAPARefTableContainer * CAPARefTableContainer::m_pobjRefTableContainer = NULL;

CAPARefTableContainer::CAPARefTableContainer()
{
    LOG_INFO(LOG_COMMON,"CAPARefTableContainer constructor");
}

CAPARefTableContainer::~CAPARefTableContainer()
{

}

CAPARefTableContainer * CAPARefTableContainer::getInstance()
{
    if(NULL == m_pobjRefTableContainer)
    {
        m_pobjRefTableContainer = new CAPARefTableContainer;
    }

    LOG_INFO(LOG_APA, "CAPARefTableContainer::getInstance() -> Value is %p, m_pobjRefTableContainer");
    return m_pobjRefTableContainer;
}


void CAPARefTableContainer::CreatePositionalScanLeftRightTable()
{
    //Insert the elements to the map.
    LOG_INFO(LOG_APA, "CreatePositionalScanLeftRightTable()....");
    m_objScanleftTableMap[17] = v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_LeftActive_RightPassive ;
    m_objScanleftTableMap[21] = v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_LeftActive_RightPassive ;
    m_objScanleftTableMap[20] = v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_LeftPassive_RightActive ;
    m_objScanleftTableMap[24] = v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_LeftPassive_RightActive ;
    
}

void CAPARefTableContainer::CreatePositionalSymbol1Table()
{
    LOG_INFO(LOG_APA, "CreatePositionalSymbol1Table()....");
    m_objPositionalSymbol1TableMap[44] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
    m_objPositionalSymbol1TableMap[184] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
    m_objPositionalSymbol1TableMap[228] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
    m_objPositionalSymbol1TableMap[264] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
    m_objPositionalSymbol1TableMap[740] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
    m_objPositionalSymbol1TableMap[204] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Stop;
    m_objPositionalSymbol1TableMap[182] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Stop;
    m_objPositionalSymbol1TableMap[464] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_DownArrowWithBlackColour;
    m_objPositionalSymbol1TableMap[639] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Withfill;
    m_objPositionalSymbol1TableMap[2530] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_DownArrowWithGreenColour;
    m_objPositionalSymbol1TableMap[726] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Flag;
    m_objPositionalSymbol1TableMap[516] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_UpArrowWithBlackColour;
    m_objPositionalSymbol1TableMap[728] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Withfill;
    m_objPositionalSymbol1TableMap[3332] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_UpArrowWithGreenColour;
    m_objPositionalSymbol1TableMap[2955] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_DownArrowWithGreenColour;
    m_objPositionalSymbol1TableMap[3008] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_UpArrowWithGreenColour;
    m_objPositionalSymbol1TableMap[680] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
    m_objPositionalSymbol1TableMap[288] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_CrossMark;
    m_objPositionalSymbol1TableMap[988] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_CrossMark;
    m_objPositionalSymbol1TableMap[1280] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_CrossMark;
    m_objPositionalSymbol1TableMap[105] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_SlowDown;
    m_objPositionalSymbol1TableMap[198] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_SlowDown;
    m_objPositionalSymbol1TableMap[345] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Note;
    m_objPositionalSymbol1TableMap[1920] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Note;
    m_objPositionalSymbol1TableMap[875] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Shiftto1;
    m_objPositionalSymbol1TableMap[156] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Flag;
    m_objPositionalSymbol1TableMap[189] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Caution;
    m_objPositionalSymbol1TableMap[2884] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_DoorOpen;
    m_objPositionalSymbol1TableMap[1508] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Park;
    m_objPositionalSymbol1TableMap[5730] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Park;
    m_objPositionalSymbol1TableMap[6479] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_DoorOpen;
    m_objPositionalSymbol1TableMap[5504] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
    m_objPositionalSymbol1TableMap[6105] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Park;
}
void CAPARefTableContainer::CreatePositionalSymbol2Table()
{
    LOG_INFO(LOG_APA, "CreatePositionalSymbol2Table()....");
    m_objPositionalSymbol2TableMap[66]  = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_R;
    m_objPositionalSymbol2TableMap[144] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_P;
    m_objPositionalSymbol2TableMap[198] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_R;
    m_objPositionalSymbol2TableMap[176] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_R;
    m_objPositionalSymbol2TableMap[350] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_N;
    m_objPositionalSymbol2TableMap[456] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_D;
    m_objPositionalSymbol2TableMap[322] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_SHIFT_R;
    m_objPositionalSymbol2TableMap[448] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_Shift_1;
    m_objPositionalSymbol2TableMap[522] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Symbol_Wait;
    m_objPositionalSymbol2TableMap[400] = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Symbol_Park;
}

void CAPARefTableContainer::CreatePositionalText1Table()
{
    LOG_INFO(LOG_APA, "CreatePositionalText1Table()....");
    m_objPositionalText1TableMap[49]  = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Scanning;
    m_objPositionalText1TableMap[106] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Scanning;
    m_objPositionalText1TableMap[165] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Select_Side;
    m_objPositionalText1TableMap[232] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Right_Side_Selected;
    m_objPositionalText1TableMap[275] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Left_Side_Selected;
    m_objPositionalText1TableMap[618] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Select_Left_Side;
    m_objPositionalText1TableMap[805] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Select_Right_Side;
    m_objPositionalText1TableMap[416] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Release_Steering_Wheel;
    m_objPositionalText1TableMap[270] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Space_Found;
    m_objPositionalText1TableMap[340] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Space_Found;
    m_objPositionalText1TableMap[539] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Space_Found;
    m_objPositionalText1TableMap[636] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Space_Found;
    m_objPositionalText1TableMap[884] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Stop_Red_Text;
    m_objPositionalText1TableMap[812] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Stop_Red_Text;
    m_objPositionalText1TableMap[1110] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Stop_Red_Text;
    m_objPositionalText1TableMap[928] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Stop_Red_Text;
    m_objPositionalText1TableMap[595] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Drive_Forward_Slowly_Green_Text;
    m_objPositionalText1TableMap[792] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Drive_Backward_Slowly_Green_Text;
    m_objPositionalText1TableMap[1254] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Finished_Take_Control;
    m_objPositionalText1TableMap[180] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Slow_Down;
    m_objPositionalText1TableMap[630] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled;
    m_objPositionalText1TableMap[968] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Wheel_Slip;
    m_objPositionalText1TableMap[1794] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Door_Open;
    m_objPositionalText1TableMap[2064] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_High_Inclination;
    m_objPositionalText1TableMap[1650] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Obstacle_In_Path;
    m_objPositionalText1TableMap[1508] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled;
    m_objPositionalText1TableMap[3078] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Steering_Intervention;
    m_objPositionalText1TableMap[3584] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled;
    m_objPositionalText1TableMap[2088] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled;
    m_objPositionalText1TableMap[3000] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Auto_Break;
    m_objPositionalText1TableMap[5673] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Sensors_Blocked;
    m_objPositionalText1TableMap[7776] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Trailer_Attached;
    m_objPositionalText1TableMap[8877] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Sensors_Blocked;
    m_objPositionalText1TableMap[9282] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Sensors_Blocked;
    m_objPositionalText1TableMap[10080] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Sensors_Blocked;
    m_objPositionalText1TableMap[3708] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Paused;
    m_objPositionalText1TableMap[2442] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Paused;
    m_objPositionalText1TableMap[3002] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Paused;
    m_objPositionalText1TableMap[5382] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Release_Steering_Wheel;
    m_objPositionalText1TableMap[280] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Active_park_Assist;
    m_objPositionalText1TableMap[1435] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Shift_To_1;
    m_objPositionalText1TableMap[3360] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Shift_To_P;
    m_objPositionalText1TableMap[645] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Active_park_Not_Available;
    m_objPositionalText1TableMap[220] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Slow_Down;
    m_objPositionalText1TableMap[630] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Finished;
    m_objPositionalText1TableMap[828] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Finished;
    m_objPositionalText1TableMap[1974] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Hold_Park_Button;
    m_objPositionalText1TableMap[4896] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Attention;
    m_objPositionalText1TableMap[4557] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Attention;
    m_objPositionalText1TableMap[2950] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Obstracle_In_Path;
    m_objPositionalText1TableMap[7038] = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Accel_Pedal_Inactive;


}

void CAPARefTableContainer::CreatePositionalText2Table()
{
   // m_objPositionalText2TableMap[0] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Blank;
    LOG_INFO(LOG_APA, "CreatePositionalText2Table()....");
    m_objPositionalText2TableMap[46] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Stop;
    m_objPositionalText2TableMap[98] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Drive_Forward;
    m_objPositionalText2TableMap[159] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Drive_Forward;
    m_objPositionalText2TableMap[228] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Drive_Forward_Green_Text;
    m_objPositionalText2TableMap[305] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Drive_Forward_Green_Text;
    m_objPositionalText2TableMap[588] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_Drive;

   
    m_objPositionalText2TableMap[78] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Stop;
  //  m_objPositionalText2TableMap[183] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Drive_Forward;
    m_objPositionalText2TableMap[228] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Drive_Forward_Green_Text;
    m_objPositionalText2TableMap[305] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Drive_Forward_Green_Text;
    m_objPositionalText2TableMap[576] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_Drive;
  //  m_objPositionalText2TableMap[364] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_Reverse;
    m_objPositionalText2TableMap[448] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_Reverse;
    m_objPositionalText2TableMap[870] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_Reverse;
    m_objPositionalText2TableMap[792] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_Reverse;
//    m_objPositionalText2TableMap[114] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_Forward;
    m_objPositionalText2TableMap[506] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_N;
    m_objPositionalText2TableMap[840] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_N;
    m_objPositionalText2TableMap[572] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Prepare_To_Stop;
    m_objPositionalText2TableMap[490] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Prepare_To_Stop;
    m_objPositionalText2TableMap[629] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Take_Control;
    m_objPositionalText2TableMap[1188] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Take_Control;
    m_objPositionalText2TableMap[1292] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Object_In_Path;
    m_objPositionalText2TableMap[1860] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Auto_Break_Activated;
    m_objPositionalText2TableMap[1134] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Press_Button_To_Resume;
    m_objPositionalText2TableMap[1210] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Wheel_Slip;
    m_objPositionalText2TableMap[1587] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_TC_Off;
    m_objPositionalText2TableMap[1728] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_HighSpeed;
    m_objPositionalText2TableMap[2775] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Driver_Use_Breaks;
    m_objPositionalText2TableMap[6136] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Sensor_Blocked;
    m_objPositionalText2TableMap[5967] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Trailer_Attached;
    m_objPositionalText2TableMap[4508] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Sensor_Blocked;
    m_objPositionalText2TableMap[7279] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Sensor_Blocked;
    m_objPositionalText2TableMap[7980] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Sensor_Blocked;
    m_objPositionalText2TableMap[3875] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Remove_Hands;
    m_objPositionalText2TableMap[4448] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Wrong_direction;
    m_objPositionalText2TableMap[4719] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Release_Break_To_Start;
    m_objPositionalText2TableMap[2600] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Check_Surroundings;
    m_objPositionalText2TableMap[3649] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Close_Door;
    m_objPositionalText2TableMap[6300] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Release_SteeringWheel;
    m_objPositionalText2TableMap[2795] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Hold_Button_To_Resume;
    m_objPositionalText2TableMap[2552] = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Wait_For_Steering;

}


// Parsing zone Starts
/*
    This section contains functions which are used for parsing the reference tables
*/
void CAPARefTableContainer::ParsePositionalScanLeftRightTable()
{

    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    int l_intCalVal = 0;
    LOG_INFO(LOG_APA, "Entry ParsePositionalScanLeftRightTable");
    do
    {
        v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus l_eHMILeftStatusData = 
            v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_Blank;
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalScanLeftRightTable -> l_pobjPAMPresCtrl is NULL");
            break;
        }
        if(2 != l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            l_pobjPAMPresCtrl->m_pobjAPAStub->setScanLeftRightStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_Blank);
            LOG_INFO(LOG_APA, "l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat is not 2");
            break;
        }
        if(0 != l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
        {
            l_pobjPAMPresCtrl->m_pobjAPAStub->setScanLeftRightStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_Blank);
            LOG_INFO(LOG_APA, "ApaPrkAidMsgTxt_D_Rq is not 0 ....");
            break;
        }
        if((-1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) || (-1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) || (-1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat) 
            || (-1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat))
        {           
            l_pobjPAMPresCtrl->m_pobjAPAStub->setScanLeftRightStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_Blank);
            LOG_INFO(LOG_APA, "All the values are Not present > ParsePositionalScanLeftRightTable...");
            break;
        }

        LOG_INFO(LOG_APA, "ParsePositionalScanLeftRightTable All the values are  present...");
        
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            l_intCalVal += (l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat * e_ApaSys_D_Stat) + (l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat * e_ApaSteScanMde_D_Stat);
        }
        if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat || 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
        {
            l_intCalVal += (l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat * e_ApaActvSide2_D_Stat);
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat || 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
        {
            l_intCalVal += (l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat * e_ApaMde_D_Stat);
        }

        if(m_objScanleftTableMap.find(l_intCalVal) != m_objScanleftTableMap.end())
        {
            LOG_INFO(LOG_APA, "ParsePositionalScanLeftRightTable Enum to be send to HMI is.... %d", m_objScanleftTableMap.find(l_intCalVal)->second);

            l_eHMILeftStatusData = static_cast<v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::Literal>(m_objScanleftTableMap.find(l_intCalVal)->second);
            l_pobjPAMPresCtrl->m_pobjAPAStub->setScanLeftRightStatusAttribute(l_eHMILeftStatusData);
        }
        else
        {
            LOG_INFO(LOG_APA, "ParsePositionalScanLeftRightTable Value is not present in Map....");
            l_pobjPAMPresCtrl->m_pobjAPAStub->setScanLeftRightStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_Blank);
        }

    }while(0);

}

void CAPARefTableContainer::ParsePositionalSymbol1Table()
{
    int l_intFindVal = 0;
    bool l_bIsFound = false;
    
    v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info l_eFireData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Blank;
    
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalSymbol1Table -> l_pobjPAMPresCtrl is NULL");
            break;
        }

        LOG_INFO(LOG_APA, "CAPARefTableContainer::ParsePositionalSymbol1Table() -> Values are %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSelSapp_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaSelPpa_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSelPoa_D_Stat, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv,
        l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv, l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv, l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq,  l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq);
        if(6 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table -> 6");
            l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Flag;
            FirePositionalSymbol1(l_eFireData);
            l_bIsFound = true;
            break;
        }
        if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table -> 7");
            l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Caution;
            FirePositionalSymbol1(l_eFireData);
            l_bIsFound = true;
            break;
        }
        if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table -> 5");
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Note;
                FirePositionalSymbol1(l_eFireData);
                l_bIsFound = true;
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                if(e_Transmission_Manual == l_pobjPAMPresCtrl->m_objContext.m_eTransType)
                {
                    l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Shiftto1;
                }
                else
                {
                    l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_ShifttoD;
                }
                FirePositionalSymbol1(l_eFireData);
                l_bIsFound = true;
                break;
            }
        }
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table ->3");
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_SlowDown;
                FirePositionalSymbol1(l_eFireData);
                l_bIsFound = true;
                break;
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_SlowDown;
                FirePositionalSymbol1(l_eFireData);
                l_bIsFound = true;
                break;
            }
        }

        if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table ->4");
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
                FirePositionalSymbol1(l_eFireData);
                l_bIsFound = true;
                break;
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_CrossMark;
                FirePositionalSymbol1(l_eFireData);
                l_bIsFound = true;
                break;            
            }
            if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_CrossMark;
                FirePositionalSymbol1(l_eFireData);
                l_bIsFound = true;
                break;
            }
            if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_CrossMark;
                FirePositionalSymbol1(l_eFireData);
                l_bIsFound = true;
                break;
            }
        }

        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table ->2 & 2 ");
            int l_intFixed = (l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat * e_ApaSys_D_Stat)+ (e_ApaSteScanMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat);

            l_intFindVal = l_intFixed + (e_ApaLongCtl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv);

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal) ;
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            
            l_intFindVal = 2 * (l_intFixed + (e_ApaScan_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat) + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) + 
                                    (e_ApaSteWhl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv));

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal) ;
            if(true == l_bIsFound)
            {
                break;
            }            
            l_intFindVal = 0;

            l_intFindVal = 3 * (l_intFixed + (e_ApaMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) + (e_ApaScan_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat) + 
                            (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv));

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal) ;
            if(true == l_bIsFound)
            {
                break;
            }            
            l_intFindVal = l_intFindVal - e_ApaGearShif_D_RqDrv;
            
            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal) ;
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;

            l_intFindVal = 6 * (l_intFixed + (e_ApaLongCtl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv));           

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal) ;
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 29 * (l_intFixed + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) + (e_ApaAcsy_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv));           
            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal) ;
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
        }
        
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table ->2 & 3 ");
            int l_intFindVal = 0; int l_intFixed = 0;
            l_intFixed = (l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat * e_ApaSys_D_Stat)+ (e_ApaSteScanMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat);
            if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_RemoveHands;
                FirePositionalSymbol1(l_eFireData);
                break;
            }
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)
            {
                l_eFireData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Stop;
                FirePositionalSymbol1(l_eFireData);
                break;
            }
            l_intFindVal = 8 * (l_intFixed + (l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv * e_ApaLongCtl_D_RqDrv) + (e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq));
            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 9 * (l_intFixed + (l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv * e_ApaLongCtl_D_RqDrv) + (e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq));

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 10 * (l_intFixed + (l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv * e_ApaLongCtl_D_RqDrv) + (e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq));

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 11 * (l_intFixed + (l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat * e_ApaMde_D_Stat) + (l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv * e_ApaLongCtl_D_RqDrv)
                +(l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv * e_ApaSteWhl_D_RqDrv));

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 28 * (l_intFixed + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) + (e_ApaSteWhl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) + 
                                (e_ApaAcsy_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) + (e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq));

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 30 * (l_intFixed + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) + (e_ApaSteWhl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) + 
                                (e_ApaAcsy_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) + (e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq));

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
        }

        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table ->2 & 1");
            int l_intFixed = (l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat + (l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv * e_ApaLongCtl_D_RqDrv) + 
                (l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat * e_ApaTrgtDist_D_Stat) + (l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq * e_ApaMsgTxt_D_Rq));

            l_intFindVal = 0;
            l_intFindVal = 12 * l_intFixed;
            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 13 * l_intFixed;
            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 14 * l_intFixed;
            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 9 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol1Table ->2 & 9 ");
            int l_intFixed = 0;
            int l_intFindVal = 0;
            l_intFixed = (l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) + 
                (e_ApaSteWhl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) + (e_ApaAcsy_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) + (e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq));

            
            l_intFindVal = 31 * l_intFixed;
            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 32 * l_intFixed;

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);

            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 33 * l_intFixed;

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);

            if(true == l_bIsFound)
            {
                break;
            }
            l_intFixed = 0;
            l_intFindVal = 0;
            l_intFixed = (l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat + (e_ApaLongCtl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) + 
                (e_ApaSteWhl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) + (e_ApaAcsy_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) + (e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq));
            l_intFindVal = 15 * l_intFixed;

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
            l_intFindVal = 0;
            l_intFindVal = 16 * l_intFixed;

            l_bIsFound = IsValueFoundPositionalSymbol1(l_intFindVal);
            if(true == l_bIsFound)
            {
                break;
            }
        }

        LOG_INFO(LOG_APA, "Value Not Found in ParsePositionalSymbol1Table()");
        if(false == l_bIsFound)
        {
            FirePositionalSymbol1(l_eFireData);
            // fire blank to HMI
        }
    }while(0);
}


void CAPARefTableContainer::FirePositionalSymbol1(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info p_ePositionalSymbol1Info)
{
    LOG_INFO(LOG_APA, " FirePositionalSymbol1 Data is %d", p_ePositionalSymbol1Info);
    // Fire to HMI
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if(NULL != l_pobjPAMPresCtrl)
    {
        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalSymbol1StatusAttribute(p_ePositionalSymbol1Info);
    }
    else
    {
        LOG_ERROR(LOG_APA, "CAPARefTableContainer::FirePositionalSymbol1 -> l_pobjPAMPresCtrl is NULL...");
    }
}
bool CAPARefTableContainer::IsValueFoundPositionalSymbol1(int p_intVal)
{
    bool l_bRet = false;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info l_eHMIDataSymbol1 = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Blank;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            break;
        }
        if(NULL == l_pobjPAMPresCtrl->m_pobjAPAStub)
        {
            break;
        }
        if(m_objPositionalSymbol1TableMap.find(p_intVal) != m_objPositionalSymbol1TableMap.end())
        {
            //Fire to HMI
            l_eHMIDataSymbol1 = static_cast<v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::Literal>(m_objPositionalSymbol1TableMap.find(p_intVal)->second);
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalSymbol1StatusAttribute(l_eHMIDataSymbol1);
            l_bRet = true;
        }
    }while(0);
    LOG_INFO(LOG_APA, " FirePositionalSymbol1 Data is and return value is  %d %d ", l_eHMIDataSymbol1, l_bRet);
    return l_bRet;
}


void CAPARefTableContainer::ParsePositionalSymbol2Table()
{
    int l_intFixed = 0;
    int l_intValueToBeChecked = 0;
    bool l_bFound = false;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info l_eFireDataSymbol2 = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Symbol_Blank;
    LOG_ERROR(LOG_APA, "ParsePositionalSymbol2Table -> Entry");
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalSymbol2Table -> l_pobjPAMPresCtrl is NULL");
            break;
        }
        
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv && 4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {   
            LOG_INFO(LOG_APA, "ParsePositionalSymbol2Table -> 3 ,4 ");
            // fire
            l_eFireDataSymbol2 = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Symbol_Park;
            FirePositionalSymbol2(l_eFireDataSymbol2);
            l_bFound = true;
            break;
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol2Table ->  2,3,2");
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                if(e_Transmission_Manual == l_pobjPAMPresCtrl->m_objContext.m_eTransType)
                {
                    l_eFireDataSymbol2 = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_SHIFT_R;
                }
                else
                {
                    l_eFireDataSymbol2 = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_R;
                }
                FirePositionalSymbol2(l_eFireDataSymbol2);
                l_bFound = true;
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                l_eFireDataSymbol2 = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_Shift_1;
                FirePositionalSymbol2(l_eFireDataSymbol2);
                l_bFound = true;
                break;
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
            {
                l_eFireDataSymbol2 = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Symbol_Wait;
                FirePositionalSymbol2(l_eFireDataSymbol2);
                l_bFound = true;
                break;
            }
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol2Table ->  2,2");

            l_intFixed = (l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat * e_ApaSys_D_Stat) + 
                (l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat * e_ApaSteScanMde_D_Stat) ;
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)
            {
                l_eFireDataSymbol2 = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Letter_R;
                FirePositionalSymbol2(l_eFireDataSymbol2);
                l_bFound = true;
                break;
            }
            // Remaining Rows to be checked are  1,2,3,5,6
            // Checking Row1 and Row2 are both are same

            l_intValueToBeChecked = 2*(l_intFixed + (e_ApaMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) + 
                (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv));
            
            l_bFound = IsValueFoundPositionalSymbol2(l_intValueToBeChecked);
            if(true == l_bFound)
            {
                break;
            }
            
            l_intValueToBeChecked  = 0;
            l_intValueToBeChecked = 3 * (l_intFixed + (e_ApaMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) + 
                (e_ApaScan_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat) + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv));

            l_bFound = IsValueFoundPositionalSymbol2(l_intValueToBeChecked);
            if(true == l_bFound)
            {
                break;
            }
            l_intValueToBeChecked  = 0;
            l_intValueToBeChecked = 6 * (l_intFixed + (e_ApaMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) + 
                (e_ApaScan_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat) + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv));

            l_bFound = IsValueFoundPositionalSymbol2(l_intValueToBeChecked);
            if(true == l_bFound)
            {
                break;
            }
            l_intValueToBeChecked  = 0;
            l_intValueToBeChecked = 5 * (l_intFixed + (e_ApaScan_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat) + (e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv));

            l_bFound = IsValueFoundPositionalSymbol2(l_intValueToBeChecked);
            if(true == l_bFound)
            {
                break;
            }
        }

        if(false == l_bFound)
        {
            //Firing Blank to HMI
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalSymbol2StatusAttribute(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Symbol_Blank);
            LOG_ERROR(LOG_APA, "Value Not Present in Symbol2.. >> Firing Blank");
        }
    }while(0);
    
}

bool CAPARefTableContainer::IsValueFoundPositionalSymbol2(int p_intVal)
{
    bool l_bRet = false;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info l_eSymbol2HMIData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Symbol_Blank;

    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            break;
        }
        if(NULL == l_pobjPAMPresCtrl->m_pobjAPAStub)
        {
            break;
        }
        if(m_objPositionalSymbol2TableMap.find(p_intVal) != m_objPositionalSymbol2TableMap.end())
        {
            l_eSymbol2HMIData = static_cast<v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::Literal>(m_objPositionalSymbol2TableMap.find(p_intVal)->second);
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalSymbol2StatusAttribute(l_eSymbol2HMIData);
            l_bRet = true;
        }
    }while(0);
    
    LOG_INFO(LOG_APA, "Enum for FirePositionalSymbol2 and IsValueFoundPositionalSymbol2 return data is %d %d", l_bRet, l_eSymbol2HMIData);

    return l_bRet;

}
void CAPARefTableContainer::FirePositionalSymbol2(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info p_ePositionalSymbol2Info)
{
    // Fire to HMI
    LOG_INFO(LOG_APA, "Enum for FirePositionalSymbol2 is %d", p_ePositionalSymbol2Info);
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if(NULL != l_pobjPAMPresCtrl)
    {
        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalSymbol2StatusAttribute(p_ePositionalSymbol2Info);
    }
}
void CAPARefTableContainer::ParsePositionalText1Table()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enPositionalText1 l_eText1HMIData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Blank;
    LOG_INFO(LOG_APA, "ParsePositionalText1Table ->Entry");
    int l_intValueForHMI = 0;             
    bool l_bRes = false;


    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "CAPARefTableContainer::ParsePositionalText1Table() -> l_pobjPAMPresCtrl is NULL");
            break;
        }

        int l_intSignal1 = e_ApaSys_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat;
        int l_intSignal2 = e_ApaSteScanMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat;
        int l_intSignal3 = e_ApaActvSide2_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat;
        int l_intSignal4 = e_ApaMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat;
        int l_intSignal8 = e_ApaScan_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat;
        int l_intSignal9 = e_ApaLongCtl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv;
        int l_intSignal10 = e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv;
        int l_intSignal11 = e_ApaSteWhl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv;
        int l_intSignal12 = e_ApaAcsy_D_RqDrv *l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv;
        //int l_intSignal13 = e_ApaTrgtDist_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat;
        int l_intSignal14 = e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq;
        //int l_intSignal15 = e_ApaPrkAidMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq;

        if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalText1Table -> '7' ");
            l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Active_park_Assist;
            FirePositionalText1(l_eText1HMIData);
            l_bRes = true;
            break;            
        }
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat  )
        {
            LOG_INFO(LOG_APA, "ParsePositionalText1Table -> '3' ");
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Slow_Down;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;       
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Slow_Down;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;   
            }
        }
        if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)  && (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) && (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
        {
            l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Obstacle_In_Path;
            FirePositionalText1(l_eText1HMIData);
            l_bRes = true;
            break;   
        }

        if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)  && (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) && (9== l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
        {
            l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Accel_Pedal_Inactive;
            FirePositionalText1(l_eText1HMIData);
            l_bRes = true;
            break;   
        }
        if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Shift_To_1;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;   
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Active_park_Not_Available;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;   
            }
        }
        if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalText1Table -> '4' ");
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv )
            {
                if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
                    {
                        if(8 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
                        {
                            l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Sensors_Blocked;
                            FirePositionalText1(l_eText1HMIData);
                            l_bRes = true;
                            break;
                        }
                        if(12 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
                        {
                            l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Trailer_Attached;
                            FirePositionalText1(l_eText1HMIData);
                            l_bRes = true;
                            break;
                        }
                        if(13 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
                        {
                            l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Sensors_Blocked;
                            FirePositionalText1(l_eText1HMIData);
                            l_bRes = true;
                            break;
                        }
                        if(14 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
                        {
                            l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Sensors_Blocked;
                            FirePositionalText1(l_eText1HMIData);
                            l_bRes = true;
                            break;
                        }
                        if(15 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
                        {
                            l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Sensors_Blocked;
                            FirePositionalText1(l_eText1HMIData);
                            l_bRes = true;
                            break;
                        }

                    }
                    else
                    {
                        l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled;
                        FirePositionalText1(l_eText1HMIData);
                        l_bRes = true;
                        break;
                    }
                }
                if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Wheel_Slip;
                    FirePositionalText1(l_eText1HMIData);
                    l_bRes = true;
                    break;
                }
                if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_High_Inclination;
                    FirePositionalText1(l_eText1HMIData);
                    l_bRes = true;
                    break;
                }
                if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled;
                    FirePositionalText1(l_eText1HMIData);
                    l_bRes = true;
                    break;
                }
                if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Steering_Intervention;
                    FirePositionalText1(l_eText1HMIData);
                    l_bRes = true;
                    break;
                }
                if(8 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled;
                    FirePositionalText1(l_eText1HMIData);
                    l_bRes = true;
                    break;
                }
                if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled;
                    FirePositionalText1(l_eText1HMIData);
                    l_bRes = true;
                    break;
                }
                if(6 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Auto_Break;
                    FirePositionalText1(l_eText1HMIData);
                    l_bRes = true;
                    break;
                }
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv && 7 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Release_Steering_Wheel;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;
            }
            if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Obstacle_In_Path;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;
            }
            if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Cancelled_Door_Open;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;
            }
        }

        if(6 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalText1Table -> '6' ");
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Finished;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Finished;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;
            }
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalText1Table -> '2 & 2' ");

            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
            {
                l_eText1HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Hold_Park_Button;
                FirePositionalText1(l_eText1HMIData);
                l_bRes = true;
                break;
            }
            
            int l_intFixedVal = (l_intSignal1) + (l_intSignal2);

            l_intValueForHMI = l_intFixedVal + l_intSignal4 + 
                                l_intSignal8 + l_intSignal9 ;
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            
            l_intValueForHMI = 2 * l_intValueForHMI;
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;
            l_intValueForHMI = 3 * (l_intFixedVal + l_intSignal3 + l_intSignal4 + l_intSignal12);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;
            l_intValueForHMI = 4 * (l_intFixedVal + l_intSignal3 + l_intSignal4 + l_intSignal8 + 
                                    l_intSignal10 + l_intSignal12);     
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;    

            l_intValueForHMI = 5 * (l_intFixedVal + l_intSignal3 + l_intSignal4 + l_intSignal8 + 
                                    l_intSignal10 + l_intSignal12);   
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;
            
            l_intValueForHMI = 6 * (l_intFixedVal + l_intSignal4 + 
                                l_intSignal9 + 
                                l_intSignal12);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;           

            l_intValueForHMI = 7 * (l_intFixedVal + l_intSignal4 + 
                                        l_intSignal9 + l_intSignal12);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  
            l_intValueForHMI = 8 * (l_intFixedVal + l_intSignal8 + l_intSignal11 );
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;      
            l_intValueForHMI = 9 * (l_intFixedVal + l_intSignal4 + l_intSignal8);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 10 * (l_intFixedVal + l_intSignal4 + l_intSignal8);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 11 * (l_intFixedVal + l_intSignal4 + l_intSignal8 + l_intSignal11);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 12 * (l_intFixedVal + l_intSignal4 + l_intSignal8 + l_intSignal11);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 42 * (l_intFixedVal + l_intSignal4 + l_intSignal8 + l_intSignal10);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;              
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalText1Table -> '2 & 3' ");
            int l_intFixedVal = (l_intSignal1 + l_intSignal2);
            l_intValueForHMI = 0;
            l_intValueForHMI = 13 * (l_intFixedVal + l_intSignal9 + l_intSignal10 + l_intSignal12);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 14 * (l_intFixedVal + l_intSignal9 + l_intSignal10 + l_intSignal12);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 15 * (l_intFixedVal + l_intSignal9 + l_intSignal12);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 16 * (l_intFixedVal + l_intSignal9 + l_intSignal10 + l_intSignal11);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 17 * (l_intFixedVal + l_intSignal9 );
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  
            l_intValueForHMI = 18 * (l_intFixedVal + l_intSignal9 );
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 19 * (l_intFixedVal + l_intSignal4 + l_intSignal9 + l_intSignal11 + l_intSignal14);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 36 * (l_intFixedVal + l_intSignal10 + l_intSignal12 + l_intSignal11 + l_intSignal14) ;
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 37 * (l_intFixedVal + l_intSignal10 + l_intSignal12 + l_intSignal11 + l_intSignal14);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 38 * (l_intFixedVal + l_intSignal10 + l_intSignal12 + l_intSignal11 + l_intSignal14);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 48 * (l_intFixedVal + l_intSignal10 + l_intSignal12 + l_intSignal9);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  

            l_intValueForHMI = 49 * (l_intFixedVal + l_intSignal10 + l_intSignal12 + l_intSignal9);
            l_bRes = IsValueFoundInPositionalText1(l_intValueForHMI);
            if(true == l_bRes)
            {
                break;
            }
            l_intValueForHMI = 0;  
        }
        if(false == l_bRes)
        {    
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText1Attribute(v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Blank );
            LOG_INFO(LOG_APA, "ParsePositionalText1Table -> 'Firing Blank as Data Not Found' ");
            // fire blank to HMI
        }
    }while(0);
}

bool CAPARefTableContainer::IsValueFoundInPositionalText1(int p_intVal)
{
    bool l_bRet = false;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "IsValueFoundInPositionalText1 -> l_pobjPAMPresCtrl is NULL");
            break;
        }
        if(NULL == l_pobjPAMPresCtrl->m_pobjAPAStub)
        {
            LOG_ERROR(LOG_APA, "IsValueFoundInPositionalText1 -> m_pobjAPAStub is NULL");
            break;
        }
        if(m_objPositionalText1TableMap.find(p_intVal) != m_objPositionalText1TableMap.end())
        {
            v1::com::harman::ParkAssist::APABaseType::enPositionalText1 l_eText1HMIData = 
                v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Blank;

            l_eText1HMIData = static_cast<v1::com::harman::ParkAssist::APABaseType::enPositionalText1::Literal>(m_objPositionalText1TableMap.find(p_intVal)->second);
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText1Attribute(l_eText1HMIData);
            LOG_INFO(LOG_APA, "Text 1 p_intVal :%d and value is %d",p_intVal,m_objPositionalText1TableMap.find(p_intVal)->second);
            l_bRet = true;

        }

    }while(0);
    LOG_INFO(LOG_APA, "IsValueFoundInPositionalText1 return data is %d", l_bRet);
    return l_bRet;

}
void CAPARefTableContainer::FirePositionalText1(v1::com::harman::ParkAssist::APABaseType::enPositionalText1 p_eText1HMIData)
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        LOG_INFO(LOG_APA, "FirePositionalText1  data is %d", p_eText1HMIData);
        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText1Attribute(p_eText1HMIData);
    }
    else
    {
        LOG_ERROR(LOG_APA, "FirePositionalText1 -> l_pobjPAMPresCtrl / l_pobjPAMPresCtrl->m_pobjAPAStub is NULL");
    }
}
void CAPARefTableContainer::ParsePositionalText2Table()
{
    bool l_bIsFound = false;
    int l_intFindVal = 0;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enPositionalText2 l_eText22HMIData = 
                v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Blank;

    int l_ApaMde_Value = 0;
    int l_ApaSys_Value = 0;
    int l_ApaSteScanMde_value = 0;
    int l_ApaLongCtlRqDrv_value = 0;
    int l_ApaScan_value = 0;
    int l_ApaGearShift_value = 0;
    int l_ApaSteWhl_value = 0;
    int l_ApaAcsy_value = 0;
    int l_ApaMsgTxt_value = 0;
    int l_PrkMsgTxt_value = 0;
    int l_intFixed = 0;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalText2Table -> l_pobjPAMPresCtrl is NULL");
            break;
        }

        LOG_INFO(LOG_APA, "ParsePositionalText2Table() Values are %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSelSapp_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaSelPpa_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSelPoa_D_Stat, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv,
        l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv, l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv, l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq,  l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq);
    
        
        if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) 
        {
            if( 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
            {
                LOG_INFO(LOG_APA, "ParsePositionalText2Table 2 value : System Fault");
                l_bIsFound = true;
                l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_System_Fault;
                l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
            }

            if( 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
            {
                LOG_INFO(LOG_APA, "ParsePositionalText2Table value : Take control");
                l_bIsFound = true;
                l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Take_Control;
                l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
            }
            break; 
        }
        
        if((6 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)) 
        {
            LOG_INFO(LOG_APA, "ParsePositionalText2Table value : Take control");
            l_bIsFound = true;
            l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Take_Control;
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
            break;
        }

        if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                LOG_INFO(LOG_APA, "ParsePositionalText2Table value : High Inclination activated");
                l_bIsFound = true;
                l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_High_Inclination;
                l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                LOG_INFO(LOG_APA, "ParsePositionalText2Table value : T/C off");
                 l_bIsFound = true;
                l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_TC_Off;
                l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
                break;

            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                if((13 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq) ||(14 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq) || (15 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq) )
                {
                    LOG_INFO(LOG_APA, "ParsePositionalText2Table value : sensor Blocked");
                    l_bIsFound = true;
                    l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Sensor_Blocked;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
                    break;
                }
                if(12 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
                {
                    LOG_INFO(LOG_APA, "ParsePositionalText2Table value : Trailer attached");
                    l_bIsFound = true;
                    l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Trailer_Attached;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
                    break;

                }

            }
                break;
        }

        if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) &&(6 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq) ) 
        {
              LOG_INFO(LOG_APA, "ParsePositionalText2Table value : e_Text2_Auto_Break_Activated");
              l_bIsFound = true;
              l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Auto_Break_Activated;
              l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
              break;
        }

        l_ApaMde_Value = e_ApaMde_D_Stat* l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat;
        l_ApaSys_Value =  e_ApaSys_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat ;
        l_ApaSteScanMde_value = e_ApaSteScanMde_D_Stat * l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat;
        l_ApaLongCtlRqDrv_value = e_ApaLongCtl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv;
        l_ApaScan_value = e_ApaScan_D_Stat* l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat;
        l_ApaGearShift_value = e_ApaGearShif_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv;
        l_ApaSteWhl_value = e_ApaSteWhl_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv;
        l_ApaAcsy_value = e_ApaAcsy_D_RqDrv * l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv;
        l_ApaMsgTxt_value =e_ApaMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq;
        l_PrkMsgTxt_value = e_ApaPrkAidMsgTxt_D_Rq * l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq;
        
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table -> 2 & 2 ");
            l_intFixed =l_ApaSys_Value+ l_ApaSteScanMde_value;

            l_intFindVal = l_intFixed +l_ApaLongCtlRqDrv_value + l_ApaGearShift_value +l_ApaAcsy_value;

            LOG_INFO(LOG_APA, "Atita Row 1 : l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            
            if(true == l_bIsFound)       
            {
                LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table value :row 1  Stop");
                break;
            }

            
            l_intFindVal = 0;
            l_intFindVal = l_intFixed + l_ApaMde_Value+l_ApaLongCtlRqDrv_value + l_ApaScan_value;

            //For row 2 
            LOG_INFO(LOG_APA, "Atita Row 2,3,4 : l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            l_bIsFound = IsValueFoundPositionalText2((2*l_intFindVal)) ;
            
            if(true == l_bIsFound)       
            {
                LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table value :row 2 drive forward");
                break;
            }

            //For Row 3
             l_bIsFound = IsValueFoundPositionalText2((3*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                LOG_INFO(LOG_APA, "Atita text 2 value :row 3 drive forward");
                break;
            }
              //For Row 4
             l_bIsFound = IsValueFoundPositionalText2((4*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table value :row 4 drive forward grean text");
                break;
            }
              //For Row 5
             l_bIsFound = IsValueFoundPositionalText2((5*l_intFindVal)) ;
             if(true == l_bIsFound)       
            {
                LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table value :row 5 drive forward grean text");
                break;
            }

             l_intFindVal = 0;
             LOG_INFO(LOG_APA, "Atita Row 6 and 9 : l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            //For row 6 , 9
            if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
                {
                    LOG_INFO(LOG_APA, "ParsePositionalText2Table value : e_Text2_Take_Control");
                    l_bIsFound = true;
                    l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Take_Control;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
                    break;
                
                }
                
                l_intFindVal = (l_intFixed + l_ApaMde_Value+l_ApaGearShift_value + l_ApaScan_value +l_ApaSteWhl_value);
                
                  //For Row 6
                 l_bIsFound = IsValueFoundPositionalText2((6*l_intFindVal)) ;
                 if(true == l_bIsFound)       
                {
                    LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table value :Shift to drive");
                    break;
                }
                  //For Row 9
                 l_bIsFound = IsValueFoundPositionalText2((9*l_intFindVal)) ;
                 if(true == l_bIsFound)       
                {
                    LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table Shift to reverse");
                    break;
                }
            } 
            //For row 7 and 8 

            l_intFindVal = 0;
            l_intFindVal = (l_intFixed + l_ApaMde_Value+l_ApaLongCtlRqDrv_value+ l_ApaGearShift_value);
             LOG_INFO(LOG_APA, "Atita Row 7 and 8 : l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            l_bIsFound = IsValueFoundPositionalText2((7*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table value :Shift to reverse");
                break;
            }

            l_bIsFound = IsValueFoundPositionalText2((8*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table value :Shift to reverse");
                break;
            }

              //For row no 11
            if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                LOG_INFO(LOG_APA, "Atita ParsePositionalText2Table value :Shift to N");
                l_bIsFound = true;
                l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Shift_To_N;
                l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
                break;

            }
            l_intFindVal = 0;
            //For row no 12 
            l_intFindVal = 12 *(l_intFixed + l_ApaScan_value+l_ApaGearShift_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
             LOG_INFO(LOG_APA, "Atita Row 12 and 8 : l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            if(true == l_bIsFound)       
            {
                break;
            }

            l_intFindVal = 0;
            //For row no 39
            l_intFindVal = 39 *(l_intFixed + l_ApaScan_value+l_ApaLongCtlRqDrv_value+l_ApaGearShift_value+l_ApaAcsy_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
             LOG_INFO(LOG_APA, "Atita Row 9  : l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            if(true == l_bIsFound)       
            {
                break;
            }
            
         }
         if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
         {
            
            l_intFindVal = 0;
            l_intFixed =l_ApaSys_Value+ l_ApaSteScanMde_value;
            //For row 10 Text 2 in APA spec
            l_intFindVal = 10 *(l_intFixed + l_ApaLongCtlRqDrv_value+l_ApaGearShift_value+l_ApaAcsy_value);
             LOG_INFO(LOG_APA, "Atita Row 10 ,13 and 14 : l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
             }
            //For row 13 and 14 of Text 2 in APA spec
            if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)||(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv))
            {
                l_bIsFound = true;
                l_eText22HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Prepare_To_Stop;
                l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
                break;
            }

            l_intFindVal = 0;
            //For row 18 Text 2 in APA spec
            l_intFindVal = 18 *(l_intFixed +l_ApaMde_Value+l_ApaLongCtlRqDrv_value+l_ApaSteWhl_value);
           LOG_INFO(LOG_APA, "Atita Row 18,40,41,42,43 and 44: l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
            }

             //For row 40 Text 2 in APA spec
            l_intFindVal = 40 *(l_intFixed +l_ApaLongCtlRqDrv_value+l_ApaAcsy_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                 break;
             }

            //For row 41 Text 2 in APA spec
            l_intFindVal = 41 *(l_intFixed+l_ApaGearShift_value+l_ApaSteWhl_value+l_ApaAcsy_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
             }

             //For row 42 Text 2 in APA spec
            l_intFindVal = 42 *(l_intFixed+l_ApaGearShift_value+l_ApaSteWhl_value+l_ApaAcsy_value+l_ApaMsgTxt_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
             }

            //For row 43 Text 2 in APA spec
            l_intFindVal = 43 *(l_intFixed+l_ApaGearShift_value+l_ApaSteWhl_value+l_ApaAcsy_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
             }

              //For row 44 Text 2 in APA spec
            l_intFindVal = 44 *(l_intFixed+l_ApaLongCtlRqDrv_value+l_ApaGearShift_value+l_ApaSteWhl_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            //Row 15
            l_intFindVal = 15 *(l_intFixed + l_ApaLongCtlRqDrv_value+l_ApaGearShift_value+l_ApaAcsy_value);
            LOG_INFO(LOG_APA, "Atita Row 15 l_intFixed:%d  and l_intFindVal :%d",l_intFixed,l_intFindVal);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
             }

        }

        if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            l_intFixed =l_ApaSys_Value;
            l_intFindVal = 21 *(l_intFixed+l_ApaAcsy_value+l_ApaMsgTxt_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_intFindVal = (l_intFixed+l_ApaSteWhl_value+l_ApaAcsy_value+l_ApaMsgTxt_value);
            l_bIsFound = IsValueFoundPositionalText2((22*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }
            l_bIsFound = IsValueFoundPositionalText2((23*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_intFindVal = 24*(l_intFixed+l_ApaAcsy_value+l_ApaMsgTxt_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_intFindVal = 25*(l_intFixed+l_ApaSteWhl_value+l_ApaAcsy_value+l_ApaMsgTxt_value);
            l_bIsFound = IsValueFoundPositionalText2(l_intFindVal) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_intFindVal = (l_intFixed+l_ApaSteWhl_value+l_ApaAcsy_value+l_ApaMsgTxt_value+l_PrkMsgTxt_value);
            l_bIsFound = IsValueFoundPositionalText2((26*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_bIsFound = IsValueFoundPositionalText2((27*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_bIsFound = IsValueFoundPositionalText2((28*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_bIsFound = IsValueFoundPositionalText2((29*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_bIsFound = IsValueFoundPositionalText2((30*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }
                            
            l_intFindVal = (l_intFixed+l_ApaSteWhl_value+l_ApaAcsy_value+l_ApaMsgTxt_value);
            l_bIsFound = IsValueFoundPositionalText2((31*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }

            l_bIsFound = IsValueFoundPositionalText2((32*l_intFindVal)) ;
            if(true == l_bIsFound)       
            {
                break;
            }
                       
        }
        if(false == l_bIsFound)
        {
            LOG_ERROR(LOG_APA, "PositionalText2 -> Blank Data %d", l_eText22HMIData);
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
        }       
    } while(0);  
}


bool CAPARefTableContainer::IsValueFoundPositionalText2(int p_intVal)
{
    bool l_bRet = false;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enPositionalText2 l_eText22HMIData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Blank;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "IsValueFoundPositionalText2 -> l_pobjPAMPresCtrl is NULL");
            break;
        }
        if(NULL == l_pobjPAMPresCtrl->m_pobjAPAStub)
        {
            LOG_ERROR(LOG_APA, "IsValueFoundPositionalText2 -> m_pobjAPAStub is NULL");
            break;
        }
        if(m_objPositionalText2TableMap.find(p_intVal) != m_objPositionalText2TableMap.end())
        {
             //Checking valid text is found cosponsoring to given index
             if((m_objPositionalText2TableMap.find(p_intVal)->second) > 0 && ((m_objPositionalText2TableMap.find(p_intVal)->second) < 29))
             {
                l_eText22HMIData = static_cast<v1::com::harman::ParkAssist::APABaseType::enPositionalText2::Literal> (m_objPositionalText2TableMap.find(p_intVal)->second);
                //Informing Hmi to Fire data
                l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText2Attribute(l_eText22HMIData);
                l_bRet = true;
             }
        }
    }while(0);      

    LOG_INFO(LOG_APA, "IsValueFoundPositionalText2 Data and Return from IsValueFoundPositionalText2 %d %d", l_eText22HMIData, l_bRet);
    return l_bRet;

}
void CAPARefTableContainer::ParsePositionalCarLeftTable()
{
    bool l_bIsFound = false;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalCarLeftTable -> l_pobjPAMPresCtrl is NULL");
            break;
        }

        if((2 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (3 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat))
        {
            LOG_ERROR(LOG_APA, "l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat is not 2 or 3");
            break;
        }
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
        {
            // Fire
            l_bIsFound = true;
            break;
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                l_bIsFound = true;
                break;
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                l_bIsFound = true;
                break;
            }
        }

        LOG_INFO(LOG_APA, "ParsePositionalCarLeftTable Data is %d", l_bIsFound);
        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalCarLeftAttribute(l_bIsFound);

    }while(0);
}
void CAPARefTableContainer::ParsePositionalCarRightTable()
{
    bool l_bIsFound = false;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalCarRightTable -> l_pobjPAMPresCtrl is NULL");
            break;
        }

        if((2 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (3 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat))
        {
            LOG_INFO(LOG_APA, "l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat is not 2 or 3");
            break;
        }
        
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
        {
            // Fire
            l_bIsFound = true;
            break;
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
        {
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                l_bIsFound = true;
                break;
            }
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                l_bIsFound = true;
                break;
            }
        }
        LOG_INFO(LOG_APA, "ParsePositionalCarRightTable Data is %d", l_bIsFound);

        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalCarRightAttribute(l_bIsFound);
        
    }while(0);
}
void CAPARefTableContainer::ParsePositionalCarPOATable()
{
    bool l_bIsFound = false;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;

    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalCarPOATable -> l_pobjPAMPresCtrl is NULL");
            break;
        }
        if(2 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_ERROR(LOG_APA, "l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat is not 2");
            break;
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat && 4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
        {
            // fire to HMI
            l_bIsFound = true;
        }
        
    }while(0);

    LOG_INFO(LOG_APA, "ParsePositionalCarPOATable Data is %d", l_bIsFound);

    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalCarPOAAttribute(l_bIsFound);
    //
}



void CAPARefTableContainer::ParsePositionalParkScenarioLeftTable()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft l_eParkScenarioLeft = 
        v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_Blank;
    LOG_INFO(LOG_APA, "Entry -> ParsePositionalParkScenarioLeftTable");

    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalParkScenarioLeftTable -> l_pobjPAMPresCtrl is NULL");
            break;
        }
        if(NULL == l_pobjPAMPresCtrl->m_pobjAPAStub)
        {
            break;
        }

        if((2 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (3 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat))
        {
            LOG_ERROR(LOG_APA, "l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat is not 2 or 3");
            break;
        }
        
        LOG_INFO(LOG_APA, "Signal Values are %d %d %d %d %d %d", l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat,
            l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat,
            l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv);
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
        {
            LOG_INFO(LOG_APA, "3, 1, 1");
            
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                // Fire to HMI
                l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_NoSlot_Found_Graphics_SAPP_L;
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                // fire to HMI
                l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_NoSlot_Found_Graphics_PPA_L;
                break;
            }
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat 
            && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
        {
            LOG_INFO(LOG_APA, "2, 2, 1");
            do
            {
                if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat)
                {
                    if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat )
                    {
                        l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_NoSlot_Found_Graphics_SAPP_L;
                        break;
                    }
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat )
                    {
                        l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_NoSlot_Found_Graphics_PPA_L;
                        break;
                    }   
                }
                if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat)
                {
                    if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv )
                    {
                        l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_SlotReady_Graphics_SAPP_L;
                        break;
                    }
                    if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 != l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
                    {
                        l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_SlotFound_Graphics_SAPP_L;
                        break;
                    }
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv )
                    {
                        l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_SlotReady_Graphics_PPA_L;
                        break;
                    }
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 != l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv )
                    {
                        l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_SlotFound_Graphics_PPA_L;
                        break;
                    }
                    break;
                }
                if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat)
                {
                    if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
                    {
                        l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_SlotFound_Graphics_SAPP_L;
                        break;
                    }
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
                    {
                        l_eParkScenarioLeft = v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_SlotFound_Graphics_PPA_L;
                        break;
                    }
                }

            }while(0);

        }

    }while(0);
    
    LOG_INFO(LOG_APA, "ParsePositionalParkScenarioLeftTable Enum is %d", l_eParkScenarioLeft);
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        l_pobjPAMPresCtrl->m_pobjAPAStub->setParkScenarioLeftAttribute(l_eParkScenarioLeft);
    }
}
void CAPARefTableContainer::ParsePositionalParkScenarioRightTable()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight l_eParkScenarioRight = 
        v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_Blank;
    LOG_INFO(LOG_APA, "Entry -> ParsePositionalParkScenarioRightTable");
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalParkScenarioRightTable -> l_pobjPAMPresCtrl is NULL");
            break;
        }
        if(NULL == l_pobjPAMPresCtrl->m_pobjAPAStub)
        {
            break;
        }

        if((2 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (3 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat))
        {
            LOG_ERROR(LOG_APA, "l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat is not 2 or 3");
            break;
        }
        
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalParkScenarioRightTable -> 3,1,2");
            
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                // Fire to HMI
                l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_NoSlot_Found_Graphics_SAPP_R;
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
            {
                // fire to HMI
                l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_NoSlot_Found_Graphics_PPA_R;
                break;
            }
        }
        
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat 
            && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalParkScenarioRightTable -> 2,2,2");
            do
            {
                if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat)
                {
                    if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat )
                    {
                        l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_NoSlot_Found_Graphics_SAPP_R;
                        break;
                    }
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat )
                    {
                        l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_NoSlot_Found_Graphics_PPA_R;
                        break;
                    }
                }
                if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat)
                {
                    if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv )
                    {
                        l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_SlotReady_Graphics_SAPP_R;
                        break;
                    }
                    if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 != l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
                    {
                        l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_SlotFound_Graphics_SAPP_R;
                        break;
                    }
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv )
                    {
                        l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_SlotReady_Graphics_PPA_R;
                        break;
                    }
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 != l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv )
                    {
                        l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_SlotFound_Graphics_PPA_R;
                        break;
                    }
                    break;
                }
                if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat)
                {
                    if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
                    {
                        l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_SlotFound_Graphics_SAPP_R;
                        break;
                    }
                    if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
                    {
                        l_eParkScenarioRight = v1::com::harman::ParkAssist::APABaseType::enParkScenarioRight::e_Park_ScenarioRight_SlotFound_Graphics_PPA_R;
                        break;
                    }
                }

            }while(0);

        }
    }while(0);
    LOG_INFO(LOG_APA, "ParsePositionalParkScenarioRightTable Enum is %d", l_eParkScenarioRight);
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        l_pobjPAMPresCtrl->m_pobjAPAStub->setParkScenarioRightAttribute(l_eParkScenarioRight);
    }
}
void CAPARefTableContainer::ParsePositionalParkScenarioPOATable()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    bool l_bHMIData = false;
    if(NULL != l_pobjPAMPresCtrl)
    {
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat && 4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
        {
            l_bHMIData = true;
            // fire to HMI
        }
        LOG_INFO(LOG_APA, "ParsePositionalParkScenarioPOATable -> Data is %d", l_bHMIData);
        l_pobjPAMPresCtrl->m_pobjAPAStub->setParkScenarioPOAAttribute(l_bHMIData);
    }
    else
    {
        LOG_ERROR(LOG_APA, "ParsePositionalParkScenarioPOATable -> l_pobjPAMPresCtrl Is NULL...");
    }
}
void CAPARefTableContainer::ParsePositionalCarNonRVCSacTable()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    bool l_bHMIData = false;

    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "ParsePositionalCarNonRVCSacTable -> l_pobjPAMPresCtrl is NULL");
            break;
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
            {
                l_bHMIData = true;
                break;
            }
        }
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
            {
                l_bHMIData = true;
                break;
            }
        }
        if(4 <= l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat <= 7)
        {
            l_bHMIData = true;
        }

        LOG_INFO(LOG_APA, "setCarNonRVCSacAttribute Data is %d", l_bHMIData);
        l_pobjPAMPresCtrl->m_pobjAPAStub->setCarNonRVCSacAttribute(l_bHMIData);
        
    }
    while(0);
}

void CAPARefTableContainer::ParsePositionalPOASelectdTable()
{
    v1::com::harman::ParkAssist::APABaseType::enPositionalPOARightSelected l_eHMIRightData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalPOARightSelected::e_Park_POA_Right_Selected_Arrow_Blank;

    v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeftSelected l_eHMILeftData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeftSelected::e_Park_POA_Left_Selected_Arrow_Blank;
    
    bool l_bIsFound = false;

    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "l_pobjPAMPresCtrl Is NULL -> ParsePositionalPOASelectdTable");
            break;
        }

        if(2 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            break;
            LOG_ERROR(LOG_APA, "ParsePositionalPOASelectdTable intApaSys_D_Stat is not 2");
        }

        

        if( (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat ) &&
            (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) &&
            (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat))
        {
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
            {
                if( (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat) ||
                    (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat))
                {
                    LOG_INFO(LOG_APA, "ParsePositionalPOASelectdTable : Show Right Indiactor");
                    l_eHMIRightData = v1::com::harman::ParkAssist::APABaseType::enPositionalPOARightSelected::e_Park_POA_Right_Selected_Arrow_Show ;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalPOALeftSelectedAttribute(l_eHMILeftData);
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalPOARightSelectedAttribute(l_eHMIRightData);
                    l_bIsFound = true;
                    break;

                }
            }
            else if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
            {
                if( (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat) ||
                    (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat))
                {
                    LOG_INFO(LOG_APA, "ParsePositionalPOASelectdTable : Show Left Indiactor");
                    l_eHMILeftData = v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeftSelected::e_Park_POA_Left_Selected_Arrow_Show;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalPOALeftSelectedAttribute(l_eHMILeftData);
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalPOARightSelectedAttribute(l_eHMIRightData);
                    l_bIsFound = true;
                    break;
                }
            }
            else
            {
                LOG_INFO(LOG_APA, "ParsePositionalPOASelectdTable Else part...");
            }
        }

        if(false == l_bIsFound)
        {
            LOG_INFO(LOG_APA, "Not Found ParsePositionalPOASelectdTable");
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalPOALeftSelectedAttribute(l_eHMILeftData);
            l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalPOARightSelectedAttribute(l_eHMIRightData);        
        }
    }while(0);      
}
void CAPARefTableContainer::ParsePositionalParkInArrowTable()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    bool l_bIsFound = false;

    v1::com::harman::ParkAssist::APABaseType::enParkInArrow l_eParkInArrowData = 
        v1::com::harman::ParkAssist::APABaseType::enParkInArrow::e_Park_InArrow_Blank;
    do
    {

        if(l_pobjPAMPresCtrl == NULL)
        {
            LOG_ERROR(LOG_APA, "l_pobjPAMPresCtrl -> ParsePositionalParkInArrowTable is NULL");
        }

        if(2 != l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_ERROR(LOG_APA, "l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat is not 2");
            break;
        }
        
        LOG_INFO(LOG_APA, "ParkInArrowTable Values are %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat,
            l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat, 
            l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSelSapp_D_Stat,
            l_pobjPAMPresCtrl->m_objContext.m_intApaSelPpa_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSelPoa_D_Stat, 
            l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv,
            l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv, l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv, 
            l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv, l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat,
            l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq,  l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq);

        
        if( (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) &&
            (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) &&
            (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat)       &&
            (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)   &&
            (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)  &&
            (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) )
        {
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
            {
                if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
                {
                    LOG_INFO(LOG_APA, "ParsePositionalParkInArrowTable :Right Down");
                    l_eParkInArrowData = v1::com::harman::ParkAssist::APABaseType::enParkInArrow::e_Park_Right_Down_Arrow;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setParkInArrowAttribute(l_eParkInArrowData);
                    l_bIsFound = true;
                    break;
                }
                if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
                {
                    LOG_INFO(LOG_APA, "ParsePositionalParkInArrowTable :Right Right ");
                    l_eParkInArrowData = v1::com::harman::ParkAssist::APABaseType::enParkInArrow::e_Park_Right_Arrow;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setParkInArrowAttribute(l_eParkInArrowData);
                    l_bIsFound = true;
                    break;
                }
            }
            
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat)
            {
                if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
                {
                    LOG_INFO(LOG_APA, "ParsePositionalParkInArrowTable :Left Down");
                    l_eParkInArrowData = v1::com::harman::ParkAssist::APABaseType::enParkInArrow::e_Park_Left_Down_Arrow;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setParkInArrowAttribute(l_eParkInArrowData);
                    l_bIsFound = true;
                    break;
                }
                if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat)
                {
                    LOG_INFO(LOG_APA, "ParsePositionalParkInArrowTable :Left Left ");
                    l_eParkInArrowData = v1::com::harman::ParkAssist::APABaseType::enParkInArrow::e_Park_Left_Arrow;
                    l_pobjPAMPresCtrl->m_pobjAPAStub->setParkInArrowAttribute(l_eParkInArrowData);
                    l_bIsFound = true;
                    break;
                }
                
            }
            
        }

        if(l_bIsFound == false)
        {
            l_pobjPAMPresCtrl->m_pobjAPAStub->setParkInArrowAttribute(l_eParkInArrowData);
            LOG_INFO(LOG_APA, "ParsePositionalParkInArrowTable :Show blank");
        }
        
    } while(0); 
}

void CAPARefTableContainer::ParsePositionalPOALeftRightTable()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    bool l_bIsFound = false;
    
    v1::com::harman::ParkAssist::APABaseType::enPositionalPOARight l_ePOARightSelectedData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalPOARight::e_Park_POARight_Blank;
    
    v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeft l_ePositionalPOALeftDataHMI = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeft::e_Park_POALeft_Blank;
    
    do
    {

        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "l_pobjPAMPresCtrl -> ParsePositionalPOALeftRightTable is NULL");
            break;
        }
        
        if( (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) && (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) && 
                (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) ) 
        {
            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat) && (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
            {
                LOG_INFO(LOG_APA, "ParsePositionalPOALeftRightTable :Show left indicator");
                l_ePositionalPOALeftDataHMI = v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeft::e_Park_POALeft_Show_Left_Arrow;
                break;
            }

            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) && (7 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
            {
                LOG_INFO(LOG_APA, "ParsePositionalPOALeftRightTable :Show Left indicator with cross");
                l_ePositionalPOALeftDataHMI = v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeft::e_Park_POALeft_Show_Left_Arrow_With_CrossMark;
                break;
            }
        }
        
        LOG_INFO(LOG_APA, "ParsePositionalPOALeftRightTable are %d %d %d %d %d ", l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat,
            l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat, 
                l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv);
        
        if( (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) && (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) && 
                (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) ) 
        {
            if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat) && (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
            {
                LOG_INFO(LOG_APA, "ParsePositionalPOALeftRightTable :Show Right indicator");
                l_ePOARightSelectedData = v1::com::harman::ParkAssist::APABaseType::enPositionalPOARight::e_Park_POARight_Show_Right_Arrow;
                break;
            }
            if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat) && (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
            {
                l_ePositionalPOALeftDataHMI = v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeft::e_Park_POALeft_Show_Left_Arrow;
                l_ePOARightSelectedData = v1::com::harman::ParkAssist::APABaseType::enPositionalPOARight::e_Park_POARight_Show_Right_Arrow;
                break;
            }
            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) && (6 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
            {
                l_ePOARightSelectedData = v1::com::harman::ParkAssist::APABaseType::enPositionalPOARight::e_Park_POARight_Show_Right_Arrow_With_CrossMark;
                break;
            }
            
        }
        
        if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) 
        && (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) && (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat))
        {
            l_ePositionalPOALeftDataHMI = v1::com::harman::ParkAssist::APABaseType::enPositionalPOALeft::e_Park_POALeft_Show_Left_Arrow_With_CrossMark;
            l_ePOARightSelectedData = v1::com::harman::ParkAssist::APABaseType::enPositionalPOARight::e_Park_POARight_Show_Right_Arrow_With_CrossMark;

        }
    }while(0);

    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalPOARightAttribute(l_ePOARightSelectedData);
    l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalPOALeftAttribute(l_ePositionalPOALeftDataHMI);
}

void CAPARefTableContainer::ParsePositionalSymbol3Table()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    LOG_INFO(LOG_APA, "Entry -> ParsePositionalSymbol3Table");
    v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3 l_eSymbol3HMIData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Blank;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            break;
        }

        if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {   
            LOG_INFO(LOG_APA, "ParsePositionalSymbol3Table, 4 ");
            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) || 
                (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) || 
                (5 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Cross_Mark;
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_RemoveHands;
                break;
            }
        }
        if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol3Table, 5 ");
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                if(e_Transmission_Manual == l_pobjPAMPresCtrl->m_objContext.m_eTransType)
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Shift1;
                }
                else
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_ShiftToD;
                }
                break;
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Info;
                break;
            }
        }
        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol3Table, 3,3 ");
            l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Slow_Icon;
            break;
        }

        if(6 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol3Table, 6 ");
            l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Flag_Icon;
            break;
        }
        if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol3Table, 7 ");
            l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Flag_Icon;
            break;
        }        

        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol3Table, 2,3 ");
            if(0 == l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat)
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Green_Arrow_Up_Zero;
                break;
            }
            if(15 == l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat)
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Green_Arrow_Up_Fifteen;
                break;
            }
            if(l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat >= 1 && 
                l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat <= 14)
            {
                l_eSymbol3HMIData = static_cast<v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::Literal>(l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat + 22);
                break;
            }
        }

        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv )
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Stop;
                break;
            }
        }

        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv )
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Stop;
                break;
            }
            if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)
            {
                if(0 == l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat)
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Green_Arrow_Down_Zero;
                    break;
                }
                if(15 == l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat)
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Green_Arrow_Down_Fifteen;
                    break;
                }
                if(l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat >= 1 && 
                        l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat <= 14)
                {
                    l_eSymbol3HMIData = static_cast<v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::Literal>(l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat + 2);
                    break;
                }
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv && 1== l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                LOG_INFO(LOG_APA, "2,3,1,1");
                if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_RemoveHands;
                    break;
                }
                if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv && 5 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Door_Open;
                    break;
                }
                if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Park_Icon;
                    break;
                }                
            }
            if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv 
                && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
            {
                LOG_INFO(LOG_APA, "2,3,4,1,3");
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Flag_Icon;
                break;

            }

        }

        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            LOG_INFO(LOG_APA, "ParsePositionalSymbol3Table, 2 ");
            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) && (1 ==  l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
                && (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) && (9 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
            {
                LOG_INFO(LOG_APA, "2,1,1,3,9");
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Park_Icon;
                break;
            }

            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) && (2 ==  l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
                && (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) && (9 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_RemoveHands;
                LOG_INFO(LOG_APA, "2,1,2,1,9");
                break;
            }

            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) && (1 ==  l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
                && (5 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) && (9 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
            {
                LOG_INFO(LOG_APA, "2,1,1,5,9");
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Door_Open;
                break;
            }
            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) && (1 ==  l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
                && (5 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) && (9 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
            {
                LOG_INFO(LOG_APA, "2,1,1,1,9");
                if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv )
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Green_Arrow_Down_Fifteen;
                    break;
                }
                if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv )
                {
                    l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Green_Arrow_Up_Fifteen;
                    break;
                }
            }            
            if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) && 
                (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) )
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Stop;
                break;
            }
            if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) && 
                (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
            {
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_Info;
                break;
            }         

            if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) && (4== l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) 
                && (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat) && (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) 
                && (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) && (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv))
            {
                LOG_INFO(LOG_APA, "ParsePositionalSymbol3Table, 2,2,4,3,1,4,2 ");
                l_eSymbol3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3::e_Symbol3_RemoveHands;
                break;
            }
        }
        
    }while(0);

    FireSymbol3TableData(l_eSymbol3HMIData);
}

void CAPARefTableContainer::FireSymbol3TableData(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3 p_eSymbol3Data)
{
    LOG_INFO(LOG_APA, "FireSymbol3TableData -> Data is %d", p_eSymbol3Data);
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if(NULL != l_pobjPAMPresCtrl)
    {
        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalSymbol3Attribute(p_eSymbol3Data);
    }
    else
    {
        LOG_ERROR(LOG_APA, "FireSymbol3TableData -> l_pobjPAMPresCtrl is NULL...\n");
    }
}
void CAPARefTableContainer::ParsePositionalSymbol4Table()
{
    LOG_INFO(LOG_APA, "Entry ->ParsePositionalSymbol4Table()");
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    bool l_bIsS15Applicable = false;
    v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4 l_eSymbol4Data = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_Blank;
    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            break;
        }

        if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq || 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq
            || 5 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq || 8 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq
            || 9 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq  ||  10 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq 
            || 12== l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq  ||  13 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq
            || 14 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq ||  15 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
        {
            l_bIsS15Applicable = true;
        }

        LOG_INFO(LOG_APA, "ParsePositionalSymbol4Table -> l_bIsS15Applicable is %d", l_bIsS15Applicable);
        
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 9 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
        {
            LOG_INFO(LOG_APA, "Symbol 4 is Info");
            l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_Info;
            break;
        }
        if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv &&
            true == l_bIsS15Applicable)
        {
            LOG_INFO(LOG_APA, "Symbol 4 is Park");
            l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_Symbol_park;
            break;
        }
        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat 
            && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)
        {
            LOG_INFO(LOG_APA, "2,3,2");
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv && true == l_bIsS15Applicable)
            {
                LOG_INFO(LOG_APA, "Symbol 4 is ShiftToR");
                if(e_Transmission_Manual == l_pobjPAMPresCtrl->m_objContext.m_eTransType)
                {
                    l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_ShiftToR;
                }
                else
                {   
                    l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_Letter_R;
                }
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv && true == l_bIsS15Applicable)
            {
                LOG_INFO(LOG_APA, "Symbol 4 is Shift_To_1");
                if(e_Transmission_Manual == l_pobjPAMPresCtrl->m_objContext.m_eTransType)
                {
                    l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_Shift_To_1;
                }
                else
                {
                    l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_ShiftToD;
                }
                break;
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)
            {
                LOG_INFO(LOG_APA, "Symbol 4 is Symbol_Wait");
                l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_Symbol_Wait;
                break;
            }
        }

        if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat && 2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        {
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv && true == l_bIsS15Applicable)
            {   
                LOG_INFO(LOG_APA, "Symbol 4 is Remove_Hands");
                l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_Remove_Hands;
                break;
            }
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat && 1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv
                && 4 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                LOG_INFO(LOG_APA, "Symbol 4 is Letter N");
                l_eSymbol4Data = v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol4::e_Symbol4_Letter_N;
                break;
            }

        }
    }while(0);

    if(NULL != l_pobjPAMPresCtrl  && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalSymbol4Attribute(l_eSymbol4Data);
    }

}
void CAPARefTableContainer::ParsePositionalText3Table()
{
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    
    v1::com::harman::ParkAssist::APABaseType::enPositionalText3 l_eText3HMIData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Blank;

    do
    {
        if(NULL == l_pobjPAMPresCtrl)
        {
            LOG_ERROR(LOG_APA, "CAPARefTableContainer::ParsePositionalText3Table() -> l_pobjPAMPresCtrl is NULL...");
            break;
        }

        LOG_INFO(LOG_APA, "Text 2 Values are %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaActvSide2_D_Stat, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSelSapp_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaSelPpa_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaSelPoa_D_Stat, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat, l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv,
        l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv, l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv, 
        l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv, l_pobjPAMPresCtrl->m_objContext.m_intApaTrgtDist_D_Stat,
        l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq,  l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq);
    
        if((0 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) ||
        (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) )
        {
            //Exit invalid value
       
            LOG_INFO(LOG_APA, "text 4 value :Invalid value");
            break;
        }

        if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat )
        {
            LOG_INFO(LOG_APA, "text 3 value :System Fault");
            l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_System_Fault;
            break;
        }

        if(6 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat )
        {
            LOG_INFO(LOG_APA, "text 3 value :Finished");
            l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Finished;
            break;
        }

        if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat )
        {
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                 LOG_INFO(LOG_APA, "text 3 value :Not Available");
                 l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Not_Available;
                 break;
            }   

            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                 LOG_INFO(LOG_APA, "text 3 value :Shift to 1 (Manual) or Shift to D (Auto)");
                 l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Shift_To_D;
                 break;
            }
        }
        
        if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat))
        {
            LOG_INFO(LOG_APA, "text 3 value :Slow Down");
            l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Slow_Down;
            break;
        }

        if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (1 ==l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) && ((1 ==l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)))
        {
            if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) && 
            ((8 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)  ||
            (13 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)  || 
            (14 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)  ||
            (15 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq) ) )
            {
                //Text 3 value is stop
                 l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_Sensor_Blocked_520;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled, Sensors Blocked520");
            }
            else if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) && (12 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq))
            {
                //Text 3 value is stop
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_Trailer_Attached_521;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled, Trailer Attached521");
            }
            else
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled");
            }
            
           break;

        }
        if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (1 ==l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
        {
            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_Wheel_Slip;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled-Wheel slip");
            }
            else if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_518;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled518");
            }
            else if(8 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled");
            }
            else if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_519;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled519");
            }
            else if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_Steering_Intervention;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled-Steering intervention");
            }
            else if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_High_Inclination;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled-High inclination");
            }
            else if(6 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_AutoBrake;
                LOG_INFO(LOG_APA, "text 3 value :Cancelled: Autobrake");
            }
            else
            {
                LOG_INFO(LOG_APA, "text 3 value :not found and show blank ");
            }
            break;
        }

        if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && 
        (5 ==l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) &&
        (1 ==l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
        {
            l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_Door_Open;
            LOG_INFO(LOG_APA, "text 3 value :Cancelled-Door open ");
            break;

        }

        if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && 
        (4 ==l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) &&
        (1 ==l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
        {
            l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_Obstracle_InPath;
            LOG_INFO(LOG_APA, "text 3 value :Cancelled-Obstacle in path ");
            break;

        }

        if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && 
        (3 ==l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) &&
        (7 ==l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
        {
            l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Relese_Steering_Wheel;
            LOG_INFO(LOG_APA, "text 3 value :Release Steering Wheel ");
            break;
        }

        if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        && (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat)
        && (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv))
        {
            LOG_INFO(LOG_APA, "2 & 2 ");

            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)
            {
                //Text 3 value is stop
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Stop;
                LOG_INFO(LOG_APA, "text 3 value :Stop");
                break;
            }

        }

        if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        && (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat))
        {
            if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) && (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) && (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv))
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Finished;
                LOG_INFO(LOG_APA, "text 3 value :Finished");
                break;
            }

            if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) 
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Stop;
                LOG_INFO(LOG_APA, "text 3 value :stop");
                break;
            }

            if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) || (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)) 
            {
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Drive_Backward_Slowly;
                LOG_INFO(LOG_APA, "text 3 value :Drive Backward Slowly");
                break;
            }
            if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
            {
                if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    if((5 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) ||
                        (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) ||
                        (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
                    {
                        if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv)||
                           (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv))
                        {
                                   //Paused to be handeled after clarification
                               l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Paused;
                               LOG_INFO(LOG_APA, "text 3 value :Paused");
                               break;

                        }

                    }

                }
                l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Attention;
                LOG_INFO(LOG_APA, "text 3 value :Attention");
                break;
            }

        }

        if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) &&
        (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) &&
        (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)) 
        {
            LOG_INFO(LOG_APA, "text 3 value :Obstacle in path");
             l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_Obstracle_InPath;
            break;
        }

        if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) &&
        (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) &&
        (9 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
        {
            LOG_INFO(LOG_APA, "text 3 value :Obstacle in path");
             l_eText3HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText3::e_Text3_Cancelled_Obstracle_InPath;
            break;

        }

    }while(0);
    
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
         l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText3Attribute(l_eText3HMIData);   
    }


}


void CAPARefTableContainer::ParsePositionalText4Table()
{

    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;  
    v1::com::harman::ParkAssist::APABaseType::enPositionalText4 l_eText4HMIData = 
        v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Blank;
    do
    {
        if((0 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) ||
            (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) )
        {           //Exit invalid value
            LOG_INFO(LOG_APA, "text 4 value :Invalid value");
            break;

        }

        if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) 
        {
            if((7 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) 
            || (6 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
            || (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat))
            {
                l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Take_Control;
                LOG_INFO(LOG_APA, "text 4 value :Take control");
                break;
            }   
        }
         //Start Handeling All cases when ApaSys_D_Stat is 2 and ApaSteScanMde_D_Sta is 2
        if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) &&
            (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat))
            {
                if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv)
                {
                     l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Release_Steering;
                     LOG_INFO(LOG_APA, "text 4 value :Release Steering");
                     break;
                } 
                if( (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) &&
                    (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaScan_D_Stat)  &&
                    (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv))
                {
                    l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Shift_To_Neutral;
                     LOG_INFO(LOG_APA, "text 4 value :Shift to Neutral");
                     break;
                } 

            }

            //Start Handeling All cases when ApaSys_D_Stat is 2 and ApaSteScanMde_D_Sta is 3
            if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) &&
               (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat))
            {
                if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMde_D_Stat) &&
                   (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) &&
                   (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv))
                {
                     l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Take_Control;
                     LOG_INFO(LOG_APA, "text 4 value :Take Control");
                     break;
                } 
                
                if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) &&
                   (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv) &&
                   (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
                {
                     l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Shift_To_Reverse;
                     LOG_INFO(LOG_APA, "text 4 value :Shift to Reverse");
                     break;
                }

                if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) &&
                   (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
                {
                     l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Object_In_Path;
                     LOG_INFO(LOG_APA, "text 4 value :e_Text4_Object_In_Path");
                     break;
                }

                if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) ||
                    (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) )
                {
                    l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Prepare_To_Stop;
                     LOG_INFO(LOG_APA, "text 4 value :Prepare to Stop");
                     break;

                }
                
                if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv) 
                {
                     l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Check_Sarrounding;
                     LOG_INFO(LOG_APA, "text 4 value :Check Surroundings");
                     break;

                }

                if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)
                {
                    if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaLongCtl_D_RqDrv) &&
                       (2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv))
                    {
                        l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Wait_For_Steering;
                        LOG_INFO(LOG_APA, "text 4 value :Wait for Steering");
                        break;
                    }

                    if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) &&
                       (5 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
                    {
                         l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Close_Door;
                         LOG_INFO(LOG_APA, "text 4 value :Close door");
                         break;
                    }

                    if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) &&
                       (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
                    {
                         l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Release_Steering_Wheel;
                         LOG_INFO(LOG_APA, "text 4 value :Release steering wheel");
                         break;
                    }

                    if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) &&
                       (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv))
                    {
                         l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Hold_Button_To_Resume;
                         LOG_INFO(LOG_APA, "text 4 value :Hold button to resume");
                         break;
                    }
                }
                //exit because There is no other case when ApaSys_D_Stat is 2 
                break;
            }

         //Start Handeling remaining cases when ApaSys_D_Stat is 3
         if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat))
            {
                 if((3 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) &&(6 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq))
                 {
                     l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Auto_Brake_Activated;
                     LOG_INFO(LOG_APA, "text 4 value :Autobrake Activated");
                     break;
                 }
                //exit Other cases are not possibel ApaSys_D_Stat
                 break;
             }    

        //Handeling All cases when ApaSys_D_Stat is 5
        /***********************************Start********************************************************/
        if((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq) &&
            (5 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)) 
        {
            if((8 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)  ||
                (13 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)||
                (14 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)||
                (15 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq) ) 
             {
                l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Sensor_Blocked;
                 LOG_INFO(LOG_APA, "text 4 value :Sensor Blocked");
                 break;
              } 
              
              if(12 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
              {
                l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Trailer_Attached;
                 LOG_INFO(LOG_APA, "text 4 value :Trailer Attached");
                break;
              }

        }
        if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat)
        {
            if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_TC_Off;
                 LOG_INFO(LOG_APA, "text 4 value :T/C off");
                 break;

            }
            
            if(5 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
            {
                l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_High_Inclination;
                 LOG_INFO(LOG_APA, "text 4 value :High inclination");
                 break;

            }
           //exit because There is no other case when ApaSys_D_Stat is 5  
           break;
        }

        /***********************************End********************************************************/
        //Start Handeling All cases when ApaSys_D_Stat is 4,ApaSteWhl_D_RqDrv 1 and ApaAcsy_D_RqDrv 1 are const
          if((4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && 
             (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaSteWhl_D_RqDrv) &&
             (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)) 
             {

                if(1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    if((8 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq) ||
                       (13 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)||
                       (14 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)||
                       (15 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq) ) 
                        {
                            l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Sensor_Blocked;
                            LOG_INFO(LOG_APA, "text 4 value :Sensor Blocked");
                            break;
                         } 
                        
                        if(12 == l_pobjPAMPresCtrl->m_objContext.m_intApaPrkAidMsgTxt_D_Rq)
                        {
                             LOG_INFO(LOG_APA, "text 4 value :Sensor Blocked");
                             l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Trailer_Attached;
                             LOG_INFO(LOG_APA, "text 4 value :Sensor Blocked");
                             break;
                        }
                         
                         
                         
                }
                
                if(2 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Wheel_Slip;
                     LOG_INFO(LOG_APA, "text 4 value :Wheel Slip");
                    break;

                }

                if(3 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_TC_Off;
                     LOG_INFO(LOG_APA, "text 4 value :T/C OFF");
                    break;

                }

                if(4 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_High_Speed;
                     LOG_INFO(LOG_APA, "text 4 value :High Speed");
                    break;

                }

                if(7 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Remove_Hands;
                     LOG_INFO(LOG_APA, "text 4 value :Remove Hands");
                    break;

                }

                if(8 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq)
                {
                    l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Wrong_Direction;
                     LOG_INFO(LOG_APA, "text 4 value :Wrong Direction");
                     break;

                }
                
             }
          //End Handeling All cases when ApaSys_D_Stat is 4,ApaSteWhl_D_RqDrv 1 and ApaAcsy_D_RqDrv 1 are const   

          //Start Handeling remaining cases when ApaSys_D_Stat is 4
             if( (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && 
                 (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq) &&
                 (3 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)) 
             {
                  l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Hold_Button_To_Resume;
                  LOG_INFO(LOG_APA, "text 4 value :Driver: Press Button To Resume");
                  break;
             }
             
             if( (4 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && 
                 (6 == l_pobjPAMPresCtrl->m_objContext.m_intApaMsgTxt_D_Rq) &&
                 (1 == l_pobjPAMPresCtrl->m_objContext.m_intApaAcsy_D_RqDrv)) 
             {
                 l_eText4HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText4::e_Text4_Driver_Use_Brakes;
                  LOG_INFO(LOG_APA, "text 4 value :Driver: Use Brakes!");
                  break;
             }
             //End Handeling remaining cases when ApaSys_D_Stat is 4

    }while(0);  

    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        //Fire Blank   
        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText4Attribute(l_eText4HMIData);
    }
}
void CAPARefTableContainer::ParsePositionalText5Table()
{
    v1::com::harman::ParkAssist::APABaseType::enPositionalText5  l_eText5HMIData =  v1::com::harman::ParkAssist::APABaseType::enPositionalText5::e_Text5_Blank;
    CPAMPresctrl *l_pobjPAMPresCtrl = CPAMPresctrl::getInstance() ;
    if((2 == l_pobjPAMPresCtrl->m_objContext.m_intApaSys_D_Stat) && (3== l_pobjPAMPresCtrl->m_objContext.m_intApaSteScanMde_D_Stat) &&((1 == l_pobjPAMPresCtrl->m_objContext.m_intApaGearShif_D_RqDrv)))
    {
        //l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText5Attribute(l_eText4HMIData);
        l_eText5HMIData = v1::com::harman::ParkAssist::APABaseType::enPositionalText5::e_Text5_Shift_To_Cancel;
        LOG_INFO(LOG_APA, "text 5 value :Shift to cancel");
    }
    else
    {
        LOG_INFO(LOG_APA, "text 3 value :Blank Do not show ");
    }
    
    if(NULL != l_pobjPAMPresCtrl && NULL != l_pobjPAMPresCtrl->m_pobjAPAStub)
    {
        //Fire Blank   
        l_pobjPAMPresCtrl->m_pobjAPAStub->setPositionalText5Attribute(l_eText5HMIData);
    }
}

