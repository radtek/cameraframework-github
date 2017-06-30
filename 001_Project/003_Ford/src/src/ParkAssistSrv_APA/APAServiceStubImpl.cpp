/**
 * generated by Voice CodeGen Version: R1_v1.3.0
 * generated on: Thu Nov 24 16:30:49 IST 2016
 */
#include "ParkAssistSrv_Common/CPresCoreHandler.hpp"
#include "CAPARefTableContainer.hpp"
#include "APAServiceStubImpl.hpp"
namespace v0 {
namespace com {
namespace harman {
namespace ParkAssist {

APAServiceStubImpl::APAServiceStubImpl(CContext *p_pobjContext):m_pobjContext(p_pobjContext)
{
    LOG_INFO(LOG_COMMON,"APAServiceStubImpl constructor");
    if(m_pobjContext->m_bContextIsAPASupported)
    {
        LOG_INFO(LOG_COMMON,"APAServiceStubImpl::APAServiceStubImpl -> APA Eol configured");
        setAPAStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enAPAStatus::e_APA_Off);
        
    }
    else
    {   
        LOG_INFO(LOG_COMMON,"APAServiceStubImpl::APAServiceStubImpl -> APA Eol Not configured");
        setAPAStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enAPAStatus::e_APA_NOT_CONFIGURED);
    }
    //v1::com::harman::ParkAssist::APABaseType::ListAPAavaliabilityInfo l_vectListVal;
    //l_vectListVal.clear();  

    //setAPAModeAvailabilityInfoAttribute(v1::com::harman::ParkAssist::APABaseType::ListAPAavaliabilityInfo);
    v1::com::harman::ParkAssist::APABaseType::APAViewType l_eDefaultAPAViewType;
    memset(&l_eDefaultAPAViewType, 0, sizeof(l_eDefaultAPAViewType));
    setObjApaViewTypeAttribute(l_eDefaultAPAViewType);
    setCurrentApaActiveModeAttribute(v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Off);
    setScanLeftRightStatusAttribute(v1::com::harman::ParkAssist::APABaseType::enPositionalScanLeftRightStatus::e_Scan_Blank);
    setPositionalSymbol1StatusAttribute(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol1Info::e_Symbol1Info_Blank);
    setPositionalSymbol2StatusAttribute(v1::com::harman::ParkAssist::APABaseType::enPositionalSymbol2Info::e_Symbol2Info_Symbol_Blank);
    setPositionalText1Attribute(v1::com::harman::ParkAssist::APABaseType::enPositionalText1::e_Text1_Blank);
    setPositionalText2Attribute(v1::com::harman::ParkAssist::APABaseType::enPositionalText2::e_Text2_Blank);
    setPositionalCarLeftAttribute(false);
    setPositionalCarRightAttribute(false);
    setPositionalCarPOAAttribute(false);
    setParkScenarioLeftAttribute(v1::com::harman::ParkAssist::APABaseType::enParkScenarioLeft::e_Park_ScenarioLeft_Blank);
    setParkScenarioPOAAttribute(false);
    setParkScenarioPOAAttribute(false);
    setAPAErrorStatusAttribute(false);
    CreateReferenceTable();
}

APAServiceStubImpl::~APAServiceStubImpl()
{

}

void APAServiceStubImpl::SelectApaMode(const std::shared_ptr<CommonAPI::ClientId> _client, ::v1::com::harman::ParkAssist::APABaseType::enAPAMode m_eModeReq, SelectApaModeReply_t reply)
{
    if(NULL != m_pobjContext)
    {
        m_pobjContext->m_eContextAPAModeReq = m_eModeReq;
        EParkAssistReqId l_eReqId = e_ParkAssist_APA_SET_APAMODE_REQ;
        CPresCoreHandler::getInstance()->addRequestToPresCore(l_eReqId);
    }
    else
    {
        LOG_ERROR(LOG_APA, "APAServiceStubImpl::SelectApaMode -> m_pobjContext is Not NULL...");
    }
}


void APAServiceStubImpl::ApaMde_D_StatToTableMapping()
{
    CAPARefTableContainer *l_pobjRefTableContainer = CAPARefTableContainer::getInstance();
    if(NULL != l_pobjRefTableContainer && NULL != m_pobjContext)
    {
        LOG_INFO(LOG_APA, "APAServiceStubImpl::ApaMde_D_StatToTableMapping() -> Value is %d", m_pobjContext->m_intApaMde_D_Stat);
        if(2 == m_pobjContext->m_intApaMde_D_Stat || 3 == m_pobjContext->m_intApaMde_D_Stat)
        {
            l_pobjRefTableContainer->ParsePositionalScanLeftRightTable();// this table has to be parsed if value is 2
            l_pobjRefTableContainer->ParsePositionalCarLeftTable(); 
            l_pobjRefTableContainer->ParsePositionalCarRightTable();
            l_pobjRefTableContainer->ParsePositionalParkScenarioLeftTable();
            l_pobjRefTableContainer->ParsePositionalParkScenarioRightTable();
            l_pobjRefTableContainer->ParsePositionalParkInArrowTable();

        }
        if(4 == m_pobjContext->m_intApaMde_D_Stat)
        {
            l_pobjRefTableContainer->ParsePositionalSymbol1Table();
            l_pobjRefTableContainer->ParsePositionalSymbol2Table();
            l_pobjRefTableContainer->ParsePositionalCarPOATable();
            l_pobjRefTableContainer->ParsePositionalParkScenarioPOATable();
            l_pobjRefTableContainer->ParsePositionalPOALeftRightTable();
            l_pobjRefTableContainer->ParsePositionalPOASelectdTable();
            l_pobjRefTableContainer->ParsePositionalSymbol3Table();
            l_pobjRefTableContainer->ParsePositionalText3Table();
            l_pobjRefTableContainer->ParsePositionalText4Table();
        }
        l_pobjRefTableContainer->ParsePositionalText1Table();
        l_pobjRefTableContainer->ParsePositionalText2Table();
    }
    else
    {
        LOG_ERROR(LOG_APA, "ApaMde_D_StatToTableMapping ->l_pobjRefTableContainer is NULL ");
    }

}


void APAServiceStubImpl::ApaGearShif_D_RqDrvToTableMapping()
{

    CAPARefTableContainer *l_pobjRefTableContainer = CAPARefTableContainer::getInstance();
    if(NULL != l_pobjRefTableContainer && NULL != m_pobjContext)
    {
        LOG_INFO(LOG_APA, "APAServiceStubImpl::ApaGearShif_D_RqDrvToTableMapping() -> Value is %d", m_pobjContext->m_intApaGearShif_D_RqDrv);
        if(2 == m_pobjContext->m_intApaGearShif_D_RqDrv)
        {
            l_pobjRefTableContainer->ParsePositionalParkInArrowTable();
        }
        if(1 == m_pobjContext->m_intApaGearShif_D_RqDrv 
            || 2 == m_pobjContext->m_intApaGearShif_D_RqDrv 
            || 3 == m_pobjContext->m_intApaGearShif_D_RqDrv 
            || 4 == m_pobjContext->m_intApaGearShif_D_RqDrv)
        {
            l_pobjRefTableContainer->ParsePositionalSymbol1Table();
            l_pobjRefTableContainer->ParsePositionalText2Table();
            l_pobjRefTableContainer->ParsePositionalSymbol3Table();
            l_pobjRefTableContainer->ParsePositionalSymbol4Table();
        }
        if(1 == m_pobjContext->m_intApaGearShif_D_RqDrv 
            || 2 == m_pobjContext->m_intApaGearShif_D_RqDrv 
            || 3 == m_pobjContext->m_intApaGearShif_D_RqDrv 
            || 5 == m_pobjContext->m_intApaGearShif_D_RqDrv)
        {
            l_pobjRefTableContainer->ParsePositionalText1Table();
        }
        if(1 == m_pobjContext->m_intApaGearShif_D_RqDrv || 3 == m_pobjContext->m_intApaGearShif_D_RqDrv)
        {
            l_pobjRefTableContainer->ParsePositionalText3Table();
        }
        if(1 == m_pobjContext->m_intApaGearShif_D_RqDrv 
            || 2 == m_pobjContext->m_intApaGearShif_D_RqDrv 
            || 4 == m_pobjContext->m_intApaGearShif_D_RqDrv)
        {
             l_pobjRefTableContainer->ParsePositionalText4Table();
        }
        l_pobjRefTableContainer->ParsePositionalText5Table();
        l_pobjRefTableContainer->ParsePositionalSymbol2Table();
        l_pobjRefTableContainer->ParsePositionalParkScenarioLeftTable();
        l_pobjRefTableContainer->ParsePositionalParkScenarioRightTable();
    }
    else
    {
        LOG_ERROR(LOG_APA, "ApaGearShif_D_RqDrvToTableMapping ->l_pobjRefTableContainer && m_pobjContext is NULL ");
    }

}

// Creating reference tables on start-up which is one time activity for every power cycle
void APAServiceStubImpl::CreateReferenceTable()
{
    CAPARefTableContainer *l_pobjRefTableContainer = CAPARefTableContainer::getInstance();
    LOG_INFO(LOG_APA, "APAServiceStubImpl::CreateReferenceTable() Inside ...");
    if(NULL != l_pobjRefTableContainer)
    {
        l_pobjRefTableContainer->CreatePositionalScanLeftRightTable();
        l_pobjRefTableContainer->CreatePositionalSymbol1Table();
        l_pobjRefTableContainer->CreatePositionalSymbol2Table();
        l_pobjRefTableContainer->CreatePositionalText1Table();
        l_pobjRefTableContainer->CreatePositionalText2Table();
    }
    else
    {
        LOG_ERROR(LOG_APA, "CreateReferenceTable ->l_pobjRefTableContainer is NULL ");
    }

}

void APAServiceStubImpl::ParseAllTables()
{
    LOG_INFO(LOG_APA, "APAServiceStubImpl::ParseAllTables() -> Entry");
    CAPARefTableContainer *l_pobjRefTableContainer = CAPARefTableContainer::getInstance();

    do
    {
        if(NULL == l_pobjRefTableContainer)
        {
            LOG_ERROR(LOG_APA, "APAServiceStubImpl::ParseAllTables() -> l_pobjRefTableContainer is NULL");
            break;
        }
        
        l_pobjRefTableContainer->ParsePositionalScanLeftRightTable();// this table has to be parsed if value is 2
        l_pobjRefTableContainer->ParsePositionalCarPOATable();
        l_pobjRefTableContainer->ParsePositionalParkScenarioPOATable();
        l_pobjRefTableContainer->ParsePositionalParkInArrowTable();
        l_pobjRefTableContainer->ParsePositionalPOASelectdTable();
        l_pobjRefTableContainer->ParsePositionalText5Table();

        l_pobjRefTableContainer->ParsePositionalSymbol2Table(); // this table has to be parsed if value is 2 or 4
        l_pobjRefTableContainer->ParsePositionalPOALeftRightTable();
        l_pobjRefTableContainer->ParsePositionalSymbol4Table();


        l_pobjRefTableContainer->ParsePositionalCarLeftTable(); // this table has to be parsed if value is 2 or 3
        l_pobjRefTableContainer->ParsePositionalCarRightTable();
        l_pobjRefTableContainer->ParsePositionalParkScenarioLeftTable();
        l_pobjRefTableContainer->ParsePositionalParkScenarioRightTable();

        l_pobjRefTableContainer->ParsePositionalSymbol1Table();
        l_pobjRefTableContainer->ParsePositionalText1Table();
        l_pobjRefTableContainer->ParsePositionalText2Table();
        l_pobjRefTableContainer->ParsePositionalCarNonRVCSacTable();
        l_pobjRefTableContainer->ParsePositionalSymbol3Table();
        l_pobjRefTableContainer->ParsePositionalText3Table();
        l_pobjRefTableContainer->ParsePositionalText4Table();

        
    }while(0);

    LOG_INFO(LOG_APA, "APAServiceStubImpl::ParseAllTables() -> Exit");

}

void APAServiceStubImpl::ParsePrkAidMsgTxtTables()
{
    LOG_INFO(LOG_APA, "APAServiceStubImpl::ParseAllTables() -> Entry");
    CAPARefTableContainer *l_pobjRefTableContainer = CAPARefTableContainer::getInstance();
    l_pobjRefTableContainer->ParsePositionalScanLeftRightTable();
    l_pobjRefTableContainer->ParsePositionalSymbol4Table();
    l_pobjRefTableContainer->ParsePositionalText1Table();
    l_pobjRefTableContainer->ParsePositionalText2Table();
    l_pobjRefTableContainer->ParsePositionalText3Table();
    l_pobjRefTableContainer->ParsePositionalText4Table();

}

void APAServiceStubImpl::UpdateAPAFeatureAvailabilityToHMI()
{
    if(NULL != m_pobjContext)
    {
        LOG_INFO(LOG_APA, "APAServiceStubImpl::UpdateAPAFeatureAvailabilityToHMI()");
        v1::com::harman::ParkAssist::APABaseType::APAavaliabilityInfo l_stAPAAvailabilityInfo;
        memset(&l_stAPAAvailabilityInfo, 0, sizeof(l_stAPAAvailabilityInfo));
        v1::com::harman::ParkAssist::APABaseType::enAPAMode l_eAPAMode = 
            v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Off;
        
        v1::com::harman::ParkAssist::APABaseType::enModeSelectability l_eModeSelectability = 
            v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_Invalid;

        l_eAPAMode = v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Sapp;
        
        v1::com::harman::ParkAssist::APABaseType::ListAPAavaliabilityInfo l_vectListVal;
        l_vectListVal.clear();

        LOG_INFO(LOG_APA, "APAServiceStubImpl::UpdateAPAFeatureAvailabilityToHMI() -> Values are %d %d %d", m_pobjContext->m_intApaSelSapp_D_Stat, m_pobjContext->m_intApaSelPpa_D_Stat, m_pobjContext->m_intApaSelPoa_D_Stat);

        if(0 == m_pobjContext->m_intApaSelSapp_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_Invalid;
        }

        if(1 == m_pobjContext->m_intApaSelSapp_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_Selectable;
        }
        if(2 == m_pobjContext->m_intApaSelSapp_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_NotSelectable;
        }
        if(3 == m_pobjContext->m_intApaSelSapp_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_NotConfigured;
        }
        

        l_stAPAAvailabilityInfo.setM_eAPAMode(l_eAPAMode);
        l_stAPAAvailabilityInfo.setM_eModeSelectability(l_eModeSelectability);
        l_vectListVal.push_back(l_stAPAAvailabilityInfo);
        
        l_eAPAMode = v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Ppa;
        if(0 == m_pobjContext->m_intApaSelPpa_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_Invalid;
        }
        if(1 == m_pobjContext->m_intApaSelPpa_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_Selectable;
        }
        if(2 == m_pobjContext->m_intApaSelPpa_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_NotSelectable;
        }
        if(3 == m_pobjContext->m_intApaSelPpa_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_NotConfigured;
        }
        l_stAPAAvailabilityInfo.setM_eAPAMode(l_eAPAMode);
        l_stAPAAvailabilityInfo.setM_eModeSelectability(l_eModeSelectability);
        l_vectListVal.push_back(l_stAPAAvailabilityInfo);

        
        l_eAPAMode = v1::com::harman::ParkAssist::APABaseType::enAPAMode::e_Mode_Poa;
        if(0 == m_pobjContext->m_intApaSelPoa_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_Invalid;
        }
        if(1 == m_pobjContext->m_intApaSelPoa_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_Selectable;
        }
        if(2 == m_pobjContext->m_intApaSelPoa_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_NotSelectable;
        }
        if(3 == m_pobjContext->m_intApaSelPoa_D_Stat)
        {
            l_eModeSelectability = v1::com::harman::ParkAssist::APABaseType::enModeSelectability::e_NotConfigured;
        }
        l_stAPAAvailabilityInfo.setM_eAPAMode(l_eAPAMode);
        l_stAPAAvailabilityInfo.setM_eModeSelectability(l_eModeSelectability);
        l_vectListVal.push_back(l_stAPAAvailabilityInfo);

        LOG_INFO(LOG_APA, "Size of vector is %d", l_vectListVal.size());
        LOG_INFO(LOG_APA, "Vector Values are... %d %d",l_vectListVal[0].getM_eAPAMode(), l_vectListVal[0].getM_eModeSelectability());
        LOG_INFO(LOG_APA, "Vector Values are... %d %d",l_vectListVal[1].getM_eAPAMode(), l_vectListVal[1].getM_eModeSelectability());
        LOG_INFO(LOG_APA, "Vector Values are... %d %d",l_vectListVal[2].getM_eAPAMode(), l_vectListVal[2].getM_eModeSelectability());
        setAPAModeAvailabilityInfoAttribute(l_vectListVal); 
    }
}

} // namespace ParkAssist
} // namespace harman
} // namespace com
} // namespace v0

