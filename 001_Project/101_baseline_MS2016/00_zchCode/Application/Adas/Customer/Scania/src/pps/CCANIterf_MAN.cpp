
#include "MessageDefineMAN.hpp"
#include "CCANIterf_MAN.h"
#include "CCameraSysManager.h"
#define CANREVERSE              "/pps/can/CuvInfo"
#define CRUISEVEHSPEEDMAN       "/pps/can/CruiseVehSpeed"

#define DEBUGSKIPFRAME	    "/pps/can/Diag/skipframe"

CCANIterfMAN* CCANIterfMAN::s_pInstance = NULL;

CCANIterfMAN* CCANIterfMAN::getInstance()
{
	if ( s_pInstance == NULL )
	{
		s_pInstance = new CCANIterfMAN();
	}

	return s_pInstance;
}

TRC_SCOPE_DEF(ADAS, CCANIterfMAN, CCANIterfMAN);
CCANIterfMAN::CCANIterfMAN()
{
    TRC_SCOPE(ADAS, CCANIterfMAN, CCANIterfMAN);
	DBG_MSG(("CCANIterfMAN::created!!\n "));
}

CCANIterfMAN::~CCANIterfMAN()
{
	s_pInstance = NULL;
}

TRC_SCOPE_DEF(ADAS, CCANIterfMAN, onCruiseControlVehSpeedMAN);
void CCANIterfMAN::onCruiseControlVehSpeedMAN(const string& strData)
{
    TRC_SCOPE(ADAS, CCANIterfMAN, onCruiseControlVehSpeedMAN);
	DBG_MSG(("try CCANIterfMAN::onCruiseControlVehSpeed %s\n ", strData.c_str()));

    map<string,string> mapParam;
    mapParam["WhlVehSpeed"]="NoVal";
    mapParam["ParkBrkSwitch"]="NoVal";
	if (!CBasePPSParser::parse((char*)strData.c_str(), mapParam))
	{
		mapParam.clear();
		DBG_MSG(("CCANIterfMAN::onCruiseControlVehSpeed: failed to parse\n"));
		return;
	}
    
    tagCruiseControlVehSpeed tagSpeed;
    if("NoVal" != mapParam["WhlVehSpeed"])
    {
        tagSpeed.uiWheelBasedVehSpeed  = StringUtil::toUInt( mapParam["WhlVehSpeed"].c_str() );
		tagSpeed.uiWheelBasedVehSpeed  = (0xffff==tagSpeed.uiWheelBasedVehSpeed) ? 0 : tagSpeed.uiWheelBasedVehSpeed;
        //only process as float at last step ticket1793232 and 1891431
        //tagSpeed.uiWheelBasedVehSpeed  = tagSpeed.uiWheelBasedVehSpeed>>8;

    }
    else
    {
        tagSpeed.uiWheelBasedVehSpeed = 0;
        DBG_MSG(("CCANIterfMAN::onCruiseControlVehSpeed: failed to parse WhlVehSpeed, use 0 as default\n"));
    }
	//special case for default value from map is not match expected behaviour
    if("NoVal" != mapParam["ParkBrkSwitch"])
    {
        tagSpeed.eParkBrakeSwitch = (EParkBrakeSwitch)StringUtil::toUInt( mapParam["ParkBrkSwitch"].c_str() );;    }
    else
    {
        tagSpeed.eParkBrakeSwitch = ePBS_NotAvailable;
        DBG_MSG(("CCANIterfMAN::onCruiseControlVehSpeed: failed to parse ParkBrkSwitch, use ePBS_NotAvailable as default\n"));
    }    
    DBG_MSG(("CCANIterfSCAINA::onCruiseControlVehSpeed - speed %6.3f(%d) park gear =%d\n ",((Float32)tagSpeed.uiWheelBasedVehSpeed/256),tagSpeed.uiWheelBasedVehSpeed,tagSpeed.eParkBrakeSwitch));
	asynSendMessage(tagSpeed, sizeof(tagCruiseControlVehSpeed));

}
TRC_SCOPE_DEF(ADAS, CCANIterfMAN, onCANReverseGear);
void CCANIterfMAN::onCANReverseGear(const string& strData)
{
    TRC_SCOPE(ADAS, CCANIterfMAN, onCANReverseGear);
	DBG_MSG(("CCANIterfMAN::onCANReverseGear %s\n ", strData.c_str()));

	map<string,string> mapParam;
	if (!CBasePPSParser::parse((char*)strData.c_str(), mapParam))
	{
		mapParam.clear();
		DBG_MSG(("CCANIterfMAN::onCANReverseGear: failed to parse\n"));
		return;
	}

	tagSwitchParams tagParams;
    static tagSwitchParams LasttagParams;
    static bool bFirst = true;
    if(bFirst)
    {
        bFirst =false;
        LasttagParams.eReverseSwitch = eSV_NotAvailable;
    }
	tagParams.eReverseSwitch= (ESwitchValue)StringUtil::toUInt( mapParam["RevSwtch"].c_str() );
    if(( tagParams.eReverseSwitch == eSV_NotAvailable )|| (tagParams.eReverseSwitch == eSV_Error ))
	{
        tagParams.eReverseSwitch = LasttagParams.eReverseSwitch; 
		DBG_MSG(("CCanClient::onCANReverseGear: ReverseSwitch error\n"));
	}

    if( tagParams.eReverseSwitch != LasttagParams.eReverseSwitch )
    {
        asynSendMessage(tagParams, sizeof(tagSwitchParams));
    }
	
    LasttagParams.eReverseSwitch = tagParams.eReverseSwitch ; 
}

TRC_SCOPE_DEF(ADAS, CCANIterfMAN, ondebug);
void CCANIterfMAN::ondebug(const string& strData)
{
    TRC_SCOPE(ADAS, CCANIterfMAN, ondebug);
	DBG_MSG(("CCANPPSParser::ondebug %s\n ", strData.c_str()));

	map<string,string> mapParam;

     //debug skip frame
    mapParam["skipframe"]="NoVal";
    mapParam["autoTestInfo"]="NoVal";
	if (!CBasePPSParser::parse((char*)strData.c_str(), mapParam))
	{
		mapParam.clear();
		DBG_MSG(("CCANPPSParser::onCruiseControlVehSpeed: failed to parse\n"));
		return;
	}

    if("NoVal" != mapParam["skipframe"])
    {
       int skf  = StringUtil::toUInt( mapParam["skipframe"].c_str() );
       CCameraSysManager::getInstance()->setSkipFrame(skf);
    }
    else
    {
		CCameraSysManager::getInstance()->setSkipFrame(0);
    } 
    
    if("NoVal" != mapParam["autoTestInfo"])
    {
        DBG_MSG(("*Tag%s\n",  mapParam["autoTestInfo"].c_str()));
    }
    else
    {
		;
    } 
}

void CCANIterfMAN::SetUpCANCmdTable(map<string,CFunctor*>* mapCANCMD)
{
    mapCANCMD->insert( makePair(CRUISEVEHSPEEDMAN, makeFunctor(this, &CCANIterfMAN::onCruiseControlVehSpeedMAN)) );
	mapCANCMD->insert( makePair(CANREVERSE, makeFunctor(this, &CCANIterfMAN::onCANReverseGear)) );
    //debug
    mapCANCMD->insert( makePair(DEBUGSKIPFRAME, makeFunctor(this, &CCANIterfMAN::ondebug)) );

    
};

