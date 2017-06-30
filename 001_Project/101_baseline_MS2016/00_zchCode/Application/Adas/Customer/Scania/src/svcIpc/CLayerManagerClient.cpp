#include "CLayerManagerClient.hpp"

#define LAYERMANAGER_DBUS_NAME 	"com.harman.service.LayerManager"
#define LAYERMANAGER_OBJ_NAME  	"/com/harman/service/LayerManager"


CLayerManagerClient* CLayerManagerClient::s_pInstance = NULL;

CLayerManagerClient* CLayerManagerClient::getInstance()
{
	if ( s_pInstance == NULL )
	{
		s_pInstance = new CLayerManagerClient();
	}

	return s_pInstance;
}

CLayerManagerClient::CLayerManagerClient()
{
	registerTarget(LAYERMANAGER_DBUS_NAME,LAYERMANAGER_OBJ_NAME);
	registerAResponseCallback("requestDisplay", makeFunctor(this, &CLayerManagerClient::onRspRequestShowADASLayer));

}

CLayerManagerClient::~CLayerManagerClient()
{
	s_pInstance = NULL;
}
//need send only in wakeup case
//graphic layer should only be seen in wakeup case
void CLayerManagerClient::RequestShowADASLayer()
{
	string strParams;
	Json::Value jsonParams;
    Json::Value jsonParams1;
	Json::FastWriter writer;
	
	jsonParams["requester"] = "ADAS_camera";

	jsonParams["value"] = "true";

	strParams = writer.write(jsonParams);

	ainvoke("requestDisplay", strParams);
    jsonParams1["requester"] = "ADAS_graphic";

	jsonParams1["value"] = "true";

	strParams = writer.write(jsonParams1);

	ainvoke("requestDisplay", strParams);
}

void CLayerManagerClient::onRspRequestShowADASLayer(const string& strData)
{
	//fprintf(stderr,"\n CLayerManagerClient::onRspRequestShowADASLayer\n");
}


