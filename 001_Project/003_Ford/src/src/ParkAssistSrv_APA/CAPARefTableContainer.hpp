#ifndef APA_REF_TABLE_CONTAINER_HPP
#define APA_REF_TABLE_CONTAINER_HPP

#include "v0/com/harman/ParkAssist/APAServiceStubDefault.hpp"

#include <spot/harman_kpimarker.h>
#include <time.h>
#include <sys/time.h>
#include <map>
#include <iostream>
using namespace std;
//using namespace placeholders;

#define SCANLEFTRIGHT_ROWSIZE 4 // Create separate const for different tables depending upon the row size
#define ALLTABLE_COLUMNSIZE 2 // This is constant for all the tables


// Enum defines the signals with unique values to be used for the tables
typedef enum _ESignalValues
{
    e_ApaSignal_Invalid     = -1,
    e_ApaSys_D_Stat = 1,        
    e_ApaSteScanMde_D_Stat = 2, 
    e_ApaActvSide2_D_Stat = 3,  
    e_ApaMde_D_Stat       = 4,
    e_ApaSelSapp_D_Stat   = 5,
    e_ApaSelPpa_D_Stat    = 6,
    e_ApaSelPoa_D_Stat    = 7,
    e_ApaScan_D_Stat      = 8,
    e_ApaLongCtl_D_RqDrv  = 9,
    e_ApaGearShif_D_RqDrv = 10,
    e_ApaSteWhl_D_RqDrv   = 11,
    e_ApaAcsy_D_RqDrv     = 12,
    e_ApaTrgtDist_D_Stat  = 13,
    e_ApaMsgTxt_D_Rq      = 14,
    e_ApaPrkAidMsgTxt_D_Rq = 15
    
}ESignalValues;


// This class is responsible for holding all the reference tables to be parsed based on the signal received
class CAPARefTableContainer
{
    public :
        static CAPARefTableContainer *m_pobjRefTableContainer;
        static CAPARefTableContainer * getInstance();
        
        ~CAPARefTableContainer();

        //Table creation functions
        void CreatePositionalScanLeftRightTable();
        void CreatePositionalSymbol1Table();
        void CreatePositionalSymbol2Table();
        void CreatePositionalText1Table();
        void CreatePositionalText2Table();


        //Parsing functions start
        void ParsePositionalScanLeftRightTable();
        void ParsePositionalSymbol1Table();
        void ParsePositionalSymbol2Table();
        void ParsePositionalText1Table();
        void ParsePositionalText2Table();
        void ParsePositionalCarLeftTable();
        void ParsePositionalCarRightTable();
        void ParsePositionalCarPOATable();
        void ParsePositionalParkScenarioLeftTable();
        void ParsePositionalParkScenarioRightTable();
        void ParsePositionalParkScenarioPOATable();
        void ParsePositionalCarNonRVCSacTable();
        void ParsePositionalParkInArrowTable();
        void ParsePositionalPOALeftRightTable();
        void ParsePositionalPOASelectdTable();
        void ParsePositionalSymbol3Table();
        void ParsePositionalSymbol4Table();
        void ParsePositionalText3Table();
        void ParsePositionalText4Table();
        void ParsePositionalText5Table();
    private:
        
        CAPARefTableContainer();

        std::map<int, int> m_objScanleftTableMap;
        std::map<int, int> m_objScanRightTableMap;
        std::map<int, int> m_objPositionalSymbol1TableMap;
        std::map<int, int> m_objPositionalSymbol2TableMap;
        std::map<int, int> m_objPositionalText1TableMap;
        std::map<int, int> m_objPositionalText2TableMap;


        void FirePositionalSymbol1(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info p_ePositionalSymbol1Info);
        void FirePositionalSymbol2(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info p_ePositionalSymbol2Info);
        bool IsValueFoundPositionalSymbol1(int p_intVal);

        bool IsValueFoundPositionalSymbol2(int p_intVal);
        bool IsValueFoundInPositionalText1(int p_intVal);
        void FirePositionalText1(v1::com::harman::ParkAssist::APABaseType::enPositionalText1 p_eText1HMIData);
        void FireSymbol3TableData(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol3 p_eSymbol3Data);
        bool IsValueFoundPositionalText2(int p_intVal);
 };

#endif
