

#include "MessageDefineSCANIA.hpp"
#include "MessageDefine.hpp"
#include "CCanClient.hpp"
#define CAN_DBUS_NAME 	"com.harman.service.canadapterservice"
#define CAN_OBJ_NAME 	"/com/harman/service/canadapterservice"


CCanClient* CCanClient::s_pInstance = NULL;

CCanClient* CCanClient::getInstance()
{
	if ( s_pInstance == NULL )
	{
		s_pInstance = new CCanClient();
	}

	return s_pInstance;
}
/*
void CCanClient::delInstance()
{
	if ( s_pInstance == NULL )
	{
		delete s_pInstance;
		s_pInstance = NULL;
	}
}*/
//todo: this dbus interface may not used anymore
CCanClient::CCanClient()
{
	registerTarget(CAN_DBUS_NAME,CAN_OBJ_NAME);
	registerSignalCallback("CruiseControlVehSpeed", makeFunctor(this, &CCanClient::onCruiseControlVehSpeed));
	registerSignalCallback("DirectionSwitchParams", makeFunctor(this, &CCanClient::onDirectionSwitchParams));
   //not sure what is the name on dbus for CAN
	registerSignalCallback("CANRequestOnOffCamera", makeFunctor(this, &CCanClient::onCANRequestOnOffCamera));
}

CCanClient::~CCanClient()
{
	s_pInstance = NULL;
}
TRC_SCOPE_DEF(ADAS, CCanClient, onCruiseControlVehSpeed);
void CCanClient::onCruiseControlVehSpeed(const string& strData)
{
    TRC_SCOPE(ADAS, CCanClient, onCruiseControlVehSpeed);
	Json::Value jsonParams;
	Json::Reader reader;
	DBG_MSG(("CCanClient::onCruiseControlVehSpeed %s\n ", strData.c_str()));

	if (!reader.parse(strData, jsonParams, false))
	{
		jsonParams.clear();
		DBG_MSG(("CCanClient::onCruiseControlVehSpeed: failed to format json value\n"));
		return;
	}

	tagCruiseControlVehSpeed tagspeed;
	tagspeed.uiWheelBasedVehSpeed  = jsonParams["VehSpeed"].asUInt();
	tagspeed.uiWheelBasedVehSpeed  = (0xffff==tagspeed.uiWheelBasedVehSpeed) ? 0 : tagspeed.uiWheelBasedVehSpeed;
    //only process as float at last step ticket1793232 and 1891431
    //tagspeed.uiWheelBasedVehSpeed  = tagspeed.uiWheelBasedVehSpeed>>8;
	tagspeed.eParkBrakeSwitch = (EParkBrakeSwitch)jsonParams["ParkingBrake"].asUInt();

	asynSendMessage(tagspeed, sizeof(tagspeed));
}
TRC_SCOPE_DEF(ADAS, CCanClient, onDirectionSwitchParams);
void CCanClient::onDirectionSwitchParams(const string& strData)
{
    TRC_SCOPE(ADAS, CCanClient, onDirectionSwitchParams);
	Json::Value jsonParams;
	Json::Reader reader;

	DBG_MSG(("CCanClient::onDirectionSwitchParams %s\n ", strData.c_str()));

	if (!reader.parse(strData, jsonParams, false))
	{
		jsonParams.clear();
		DBG_MSG(("CCanClient::onDirectionSwitchParams: failed to format json value\n"));
		return;
	}

	tagSwitchParams tagSwitchParams;
	tagSwitchParams.eLeftIndicatorIntended = (ESwitchValue)jsonParams["LeftIndicator"].asInt();
	tagSwitchParams.eRightIndicatorIntended = (ESwitchValue)jsonParams["RightIndicator"].asInt();
	tagSwitchParams.eWorkLigthToggleSwitch = (ESwitchValue)jsonParams["ToggleSwitch"].asInt();
	tagSwitchParams.eReverseSwitch = (ESwitchValue)jsonParams["ReverseSwitch"].asInt();
	if( tagSwitchParams.eReverseSwitch == eSV_NotAvailable || tagSwitchParams.eReverseSwitch == eSV_Error )
	{
		DBG_MSG(("CCanClient::onDirectionSwitchParams: ReverseSwitch error\n"));
		return;
	}

	//asynSendMessage(eDirectionSwitchParams, pTagSwitchParams);
	asynSendMessage(tagSwitchParams, sizeof(tagSwitchParams));

}
TRC_SCOPE_DEF(ADAS, CCanClient, onCANRequestOnOffCamera);
void CCanClient::onCANRequestOnOffCamera(const string& strData)
{
    TRC_SCOPE(ADAS, CCanClient, onCANRequestOnOffCamera);
	Json::Value jsonParams;
	Json::Reader reader;
	DBG_MSG(("CCanClient::onCANRequestOnOffCamera %s\n ", strData.c_str()));

	if (!reader.parse(strData, jsonParams, false))
	{
		jsonParams.clear();
		DBG_MSG(("CCanClient::onCANRequestOnOffCamera: failed to format json value\n"));
		return;
	}

	tagCANRequestOnOffCamera tagParams;
	tagParams.eGenCam1  = (ECANOnOffValue)jsonParams["GenCam1"].asUInt();
	tagParams.eGenCam2  = (ECANOnOffValue)jsonParams["GenCam2"].asUInt();
	tagParams.eGenCam3  = (ECANOnOffValue)jsonParams["GenCam3"].asUInt();
	tagParams.eGenCam4  = (ECANOnOffValue)jsonParams["GenCam4"].asUInt();
	tagParams.eFrntVwCam  = (ECANOnOffValue)jsonParams["FrntVwCam"].asUInt();
	tagParams.eRearVwCam  = (ECANOnOffValue)jsonParams["RearVwCam"].asUInt();


	asynSendMessage(tagParams, sizeof(tagParams));
}


