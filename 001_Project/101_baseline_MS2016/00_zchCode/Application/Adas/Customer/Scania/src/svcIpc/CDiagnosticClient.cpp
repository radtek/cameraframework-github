#include "CDiagnosticClient.hpp"
#include "CAdasMsgQueDefine.hpp"

#define DIAGNOSTIC_DBUS_NAME 	"com.harman.service.Diagnostics"
#define DIAGNOSTIC_OBJ_NAME 	"/com/harman/service/Diagnostics"


CDiagnosticClient* CDiagnosticClient::s_pInstance = NULL;

CDiagnosticClient* CDiagnosticClient::getInstance()
{
	if ( s_pInstance == NULL )
	{
		s_pInstance = new CDiagnosticClient();
	}

	return s_pInstance;
}
/*
void CScaniaOnOffClient::delInstance()
{
	if ( s_pInstance == NULL )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}*/

CDiagnosticClient::CDiagnosticClient()
{
	registerTarget(DIAGNOSTIC_DBUS_NAME,DIAGNOSTIC_OBJ_NAME);
	//todo  async invole call back is missing
	registerAResponseCallback("CheckFault", makeFunctor(this, &CDiagnosticClient::onCheckFault));
	//registerSignalCallback("CruiseControlVehSpeed", makeFunctor(this, &CCanClient::onCruiseControlVehSpeed));
	//registerSignalCallback("DirectionSwitchParams", makeFunctor(this, &CCanClient::onDirectionSwitchParams));
}

CDiagnosticClient::~CDiagnosticClient()
{
	s_pInstance = NULL;
}
TRC_SCOPE_DEF(ADAS, CDiagnosticClient, reportFault);
void CDiagnosticClient::reportFault(EStatus eFaultStatus, CCamera::EPos ePos)
{
    TRC_SCOPE(ADAS, CDiagnosticClient, reportFault);
	string strParams;
	Json::Value jsonParams;
	Json::FastWriter writer;
	//string      strRet;

	jsonParams["FaultCode"] = ePos + eFaultID_Camera1Invalid;

	jsonParams["FaultStatus"] = eFaultStatus;


	strParams = writer.write(jsonParams);
	ainvoke("ReportFault", strParams);

	DBG_MSG(("ainvoke CDiagnosticClient::ReportFault %s\n", strParams.c_str()));
}

TRC_SCOPE_DEF(ADAS, CDiagnosticClient, onCheckFault);
void CDiagnosticClient::onCheckFault(const string& strData)
{
    TRC_SCOPE(ADAS, CDiagnosticClient, onCheckFault);
	Json::Value jsonParams;
	Json::Reader reader;
	DBG_MSG(("CDiagnosticClient::onCheckFault %s\n ", strData.c_str()));

	if (!reader.parse(strData, jsonParams, false))
	{
		jsonParams.clear();
		DBG_MSG(("CDiagnosticClient::onCheckFault failed to format json value\n"));
		return;
	}

	string strAction = jsonParams["ACTION"].asString();
	if( strAction == "RESET" )
	{
		Int32 iID = jsonParams["DTC_ID"].asInt();
		if( iID == eFaultID_Camera1Invalid )
		{
			SEND_BASEMESSAGE(eMsgType_Diagnostic,eDiag_ResetCamera1);
		}
		else if( iID == eFaultID_Camera2Invalid)
		{
			SEND_BASEMESSAGE(eMsgType_Diagnostic,eDiag_ResetCamera2);
		}

	}
	else if( strAction == "START" )
	{
		SEND_BASEMESSAGE(eMsgType_Diagnostic,eDiag_Start);
		//asynSendMessage(tagBaseMessage(eMsgType_Diagnostic,eDiag_Start), sizeof(tagBaseMessage));
	}
	else if( strAction == "STOP")
	{
		SEND_BASEMESSAGE(eMsgType_Diagnostic,eDiag_Stop);
		//asynSendMessage(tagBaseMessage(eMsgType_Diagnostic,eDiag_Stop), sizeof(tagBaseMessage));
	}
}
