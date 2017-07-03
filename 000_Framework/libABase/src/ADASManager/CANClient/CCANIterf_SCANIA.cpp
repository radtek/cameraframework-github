
#include "MessageDefineSCANIA.hpp"
#include "CCANIterf_SCANIA.h"
#include "CCameraSysManager.h"
#include "CSocketIPC.h"
//align the cycle timer out -- max cycle is 3 seconds, if 4 seconds not receved 3 count, just take last state 
//for auto test purpose, not check debounce feature now
#define CAN_MSG_DEBOUNCE_TIME    4000

#if 0
#define CRUISEVEHSPEED 	"/pps/can/CruiseVehSpeed?wait,delta,nopersist"
#define CUVINFO	 		"/pps/can/CuvInfo?wait,delta,nopersist"
#define CANONOFF	 		"/pps/can/Camera?wait,delta,nopersist"
#endif
#define CRUISEVEHSPEED 	"/pps/can/CruiseVehSpeed"
#define CUVINFO	 		"/pps/can/CuvInfo"
#define CANONOFF	    "/pps/can/Camera"

#define DEBUGSKIPFRAME	    "/pps/can/Diag/skipframe"

CCANIterfSCAINA* CCANIterfSCAINA::s_pInstance = NULL;

CCANIterfSCAINA* CCANIterfSCAINA::getInstance()
{
	if ( s_pInstance == NULL )
	{
		s_pInstance = new CCANIterfSCAINA();
	}

	return s_pInstance;
}
TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, vCB_DebounceWorkLight);
void vCB_DebounceWorkLight(tagSwitchParams *debounced,tagSwitchParams *current,tagSwitchParams *last)
{
	TRC_SCOPE(ADAS, CCANIterfSCAINA, vCB_DebounceWorkLight);
	debounced->eWorkLigthToggleSwitch = current->eWorkLigthToggleSwitch;
	CCANIterfSCAINA::getInstance()->vUpdateTimerOutCANSig();
	last->eWorkLigthToggleSwitch = current->eWorkLigthToggleSwitch;
	DBG_WARNING(("debuonce timer out: eWorkLigthToggleSwitch state now is %d \n",last->eWorkLigthToggleSwitch));
}
TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, vCB_DebounceLeftTurn);
void vCB_DebounceLeftTurn(tagSwitchParams *debounced,tagSwitchParams *current,tagSwitchParams *last)
{
	TRC_SCOPE(ADAS, CCANIterfSCAINA, vCB_DebounceLeftTurn);
	debounced->eLeftIndicatorIntended = current->eLeftIndicatorIntended;
	CCANIterfSCAINA::getInstance()->vUpdateTimerOutCANSig();
	last->eLeftIndicatorIntended = current->eLeftIndicatorIntended;
	DBG_WARNING(("debuonce timer out: eLeftIndicatorIntended state now is %d \n",last->eLeftIndicatorIntended));
}
TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, vCB_DebounceRightTurn);
void vCB_DebounceRightTurn(tagSwitchParams *debounced,tagSwitchParams *current,tagSwitchParams *last)
{
	TRC_SCOPE(ADAS, CCANIterfSCAINA, vCB_DebounceRightTurn);
	debounced->eRightIndicatorIntended = current->eRightIndicatorIntended;
	CCANIterfSCAINA::getInstance()->vUpdateTimerOutCANSig();
	last->eRightIndicatorIntended = current->eRightIndicatorIntended;
	DBG_WARNING(("debuonce timer out: eRightIndicatorIntended state now is %d \n",last->eRightIndicatorIntended));
}

TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, vUpdateTimerOutCANSig);
void CCANIterfSCAINA::vUpdateTimerOutCANSig()
{
	TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, vUpdateTimerOutCANSig);
	asynSendMessage(m_DebouncedSwitchParams, sizeof(tagSwitchParams));
}

TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, CCANIterfSCAINA);
CCANIterfSCAINA::CCANIterfSCAINA()
{
    TRC_SCOPE(ADAS, CCANIterfSCAINA, CCANIterfSCAINA);
	m_pWorklightDT = new CCANDebounceT(CAN_MSG_DEBOUNCE_TIME,&vCB_DebounceWorkLight,"WorkLight");
	m_pLeftTurnDT = new CCANDebounceT(CAN_MSG_DEBOUNCE_TIME,&vCB_DebounceLeftTurn,"LeftTurn");
	m_pRightTurnDT = new CCANDebounceT(CAN_MSG_DEBOUNCE_TIME,&vCB_DebounceRightTurn,"RightTurn");

	m_DebouncedSwitchParams.eReverseSwitch = eSV_Off;
	m_DebouncedSwitchParams.eLeftIndicatorIntended = eSV_Off;
	m_DebouncedSwitchParams.eRightIndicatorIntended = eSV_Off;
	m_DebouncedSwitchParams.eWorkLigthToggleSwitch = eSV_Off;

	//to supoort timer out on debounce proecss, keep the last recevied state
	m_CurSwitchParams.eReverseSwitch = eSV_Off;
	m_CurSwitchParams.eLeftIndicatorIntended = eSV_Off;
	m_CurSwitchParams.eRightIndicatorIntended = eSV_Off;
	m_CurSwitchParams.eWorkLigthToggleSwitch = eSV_Off;

	m_LastSwitchParams.eReverseSwitch = eSV_Off;
	m_LastSwitchParams.eLeftIndicatorIntended = eSV_Off;
	m_LastSwitchParams.eRightIndicatorIntended = eSV_Off;
	m_LastSwitchParams.eWorkLigthToggleSwitch = eSV_Off;

	DBG_MSG(("CCANIterfSCAINA::created!!\n "));
}

CCANIterfSCAINA::~CCANIterfSCAINA()
{
	delete m_pWorklightDT;
	delete m_pLeftTurnDT;
	delete m_pRightTurnDT;	
	delete s_pInstance;
	s_pInstance = NULL;
}

TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, onCruiseControlVehSpeed);
void CCANIterfSCAINA::onCruiseControlVehSpeed(const string& strData)
{
    TRC_SCOPE(ADAS, CCANIterfSCAINA, onCruiseControlVehSpeed);
	DBG_MSG(("CCANPPSParser::onCruiseControlVehSpeed %s\n ", strData.c_str()));

	map<string,string> mapParam;
    mapParam["WhlVehSpeed"]="NoVal";
    mapParam["ParkBrkSwitch"]="NoVal";
	if (!CBasePPSParser::parse((char*)strData.c_str(), mapParam))
	{
		mapParam.clear();
		DBG_MSG(("CCANPPSParser::onCruiseControlVehSpeed: failed to parse\n"));
		return;
	}
    
    tagCruiseControlVehSpeed tagSpeed;
    static tagCruiseControlVehSpeed LasttagSpeed;
    static bool bFirst = true;
    if(bFirst)
    {
        LasttagSpeed.uiWheelBasedVehSpeed = 0;
        LasttagSpeed.eParkBrakeSwitch= ePBS_NotAvailable;
    }


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
        DBG_MSG(("CCANPPSParser::onCruiseControlVehSpeed: failed to parse WhlVehSpeed, use 0 as default\n"));
    }
	//special case for default value from map is not match expected behaviour
    if("NoVal" != mapParam["ParkBrkSwitch"])
    {   
        tagSpeed.eParkBrakeSwitch = (EParkBrakeSwitch)StringUtil::toUInt( mapParam["ParkBrkSwitch"].c_str());
        if((ePBS_NotAvailable==tagSpeed.eParkBrakeSwitch)
        ||(ePBS_Error==tagSpeed.eParkBrakeSwitch))
        {
            //just keep last state
            tagSpeed.eParkBrakeSwitch = LasttagSpeed.eParkBrakeSwitch;
        }  
    }
    else
    {
        tagSpeed.eParkBrakeSwitch = ePBS_NotAvailable;
        DBG_MSG(("CCANPPSParser::onCruiseControlVehSpeed: failed to parse ParkBrkSwitch, use ePBS_NotAvailable as default\n"));
    }    
    
    DBG_MSG(("CCANIterfSCAINA::onCruiseControlVehSpeed - speed %6.3f(%d) park gear =%d\n ",((Float32)tagSpeed.uiWheelBasedVehSpeed/256),tagSpeed.uiWheelBasedVehSpeed,tagSpeed.eParkBrakeSwitch));
    
//when speed is zero ,even parking  is error still send to active a defult parking state
    if((LasttagSpeed.uiWheelBasedVehSpeed != tagSpeed.uiWheelBasedVehSpeed)
      ||(0==tagSpeed.uiWheelBasedVehSpeed)  
      ||(LasttagSpeed.eParkBrakeSwitch!=tagSpeed.eParkBrakeSwitch))
    {
        asynSendMessage(tagSpeed, sizeof(tagCruiseControlVehSpeed));
    }
    LasttagSpeed.uiWheelBasedVehSpeed = tagSpeed.uiWheelBasedVehSpeed;
    LasttagSpeed.eParkBrakeSwitch= tagSpeed.eParkBrakeSwitch;
}

TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, ondebug);
void CCANIterfSCAINA::ondebug(const string& strData)
{
    TRC_SCOPE(ADAS, CCANIterfSCAINA, onCruiseControlVehSpeed);
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
		SENDTO_CCR(("*Tag%s\n",  mapParam["autoTestInfo"].c_str()));
    }
    else
    {
		;
    } 

}

/*direction/worklight debounce process
this debounce is mean to hide the flicker when direction/worklight activated camera change from on -> off
CAN will send 3 cycle msg and service side will take as show/hide reqeust and make camera view flcking
start a timer and a counter on detecting a change on direction/worklight change 
check value...
time out 3 seconds, reset timer 
count 3 consecutive CAN input ONLY(maybe less then 3 seconds, reset timer) 
**AFTER DEBOUNCE PROCESS STARTED,if another signal changed also consider it as CAN cycle 
system:CAN signal is bit message in a data type
*/     


TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, onDirectionSwitchParams);
void CCANIterfSCAINA::onDirectionSwitchParams(const string& strData)
{
    TRC_SCOPE(ADAS, CCANIterfSCAINA, onDirectionSwitchParams);
	DBG_MSG(("CCANPPSParser::onDirectionSwitchParams %s\n ", strData.c_str()));

	map<string,string> mapParam;
	if (!CBasePPSParser::parse((char*)strData.c_str(), mapParam))
	{
		mapParam.clear();
		DBG_MSG(("CCANPPSParser::onDirectionSwitchParams: failed to parse\n"));
		return;
	}

    m_CurSwitchParams.eReverseSwitch = (ESwitchValue)StringUtil::toUInt( mapParam["RevSwtch"].c_str() );
	m_CurSwitchParams.eLeftIndicatorIntended = (ESwitchValue)StringUtil::toUInt( mapParam["DirIndLeft"].c_str() );
	m_CurSwitchParams.eRightIndicatorIntended = (ESwitchValue)StringUtil::toUInt( mapParam["DirIndRight"].c_str() );
	m_CurSwitchParams.eWorkLigthToggleSwitch = (ESwitchValue)StringUtil::toUInt( mapParam["WrkLtTgleSwtch"].c_str() );	
	//CR46  !=on then close camera
	if(( m_CurSwitchParams.eWorkLigthToggleSwitch == eSV_NotAvailable) || (m_CurSwitchParams.eWorkLigthToggleSwitch == eSV_Error ))
	{
		m_CurSwitchParams.eWorkLigthToggleSwitch = eSV_Off;
	}

	//CR46 remove flicker on worklight and direction CAN activated camera when become on->off
	//conserder it is not possible that CAN message changed in one interruption
	//worklight is not debouced as spec request

	m_DebouncedSwitchParams.eReverseSwitch = m_CurSwitchParams.eReverseSwitch;
	m_pLeftTurnDT->vSetCANSigState(m_CurSwitchParams.eLeftIndicatorIntended,&m_DebouncedSwitchParams.eLeftIndicatorIntended);
	m_pRightTurnDT->vSetCANSigState(m_CurSwitchParams.eRightIndicatorIntended,&m_DebouncedSwitchParams.eRightIndicatorIntended);	
    m_DebouncedSwitchParams.eWorkLigthToggleSwitch = m_CurSwitchParams.eWorkLigthToggleSwitch;
    
	if(( m_DebouncedSwitchParams.eReverseSwitch == eSV_NotAvailable )|| (m_DebouncedSwitchParams.eReverseSwitch == eSV_Error ))
	{
        m_DebouncedSwitchParams.eReverseSwitch = m_LastSwitchParams.eReverseSwitch; 
		DBG_MSG(("CCanClient::onDirectionSwitchParams: ReverseSwitch error\n"));
	}
    //special use case for direction indicator ticket 1846972
	if(( m_DebouncedSwitchParams.eLeftIndicatorIntended == eSV_NotAvailable) || (m_DebouncedSwitchParams.eLeftIndicatorIntended == eSV_Error ))
	{
        //tagParams.eLeftIndicatorIntended = LasttagParams.eLeftIndicatorIntended ;
		DBG_MSG(("CCanClient::onDirectionSwitchParams: eLeftIndicatorIntended error\n"));
	}	
    if(( m_DebouncedSwitchParams.eRightIndicatorIntended == eSV_NotAvailable) || (m_DebouncedSwitchParams.eRightIndicatorIntended == eSV_Error ))
	{
        //tagParams.eRightIndicatorIntended = LasttagParams.eRightIndicatorIntended ;
		DBG_MSG(("CCanClient::onDirectionSwitchParams: eRightIndicatorIntended error\n"));
	}
    if(( m_DebouncedSwitchParams.eWorkLigthToggleSwitch == eSV_NotAvailable) || (m_DebouncedSwitchParams.eWorkLigthToggleSwitch == eSV_Error ))
	{
        m_DebouncedSwitchParams.eWorkLigthToggleSwitch = m_LastSwitchParams.eWorkLigthToggleSwitch ;
		DBG_MSG(("CCanClient::onDirectionSwitchParams: eWorkLigthToggleSwitch error\n"));
	}

    if((m_DebouncedSwitchParams.eReverseSwitch != m_LastSwitchParams.eReverseSwitch)
        ||(m_DebouncedSwitchParams.eLeftIndicatorIntended != m_LastSwitchParams.eLeftIndicatorIntended)
        ||(m_DebouncedSwitchParams.eRightIndicatorIntended != m_LastSwitchParams.eRightIndicatorIntended)
        ||(m_DebouncedSwitchParams.eWorkLigthToggleSwitch != m_LastSwitchParams.eWorkLigthToggleSwitch))
    {
        asynSendMessage(m_DebouncedSwitchParams, sizeof(tagSwitchParams));
    }
	   
    m_LastSwitchParams.eReverseSwitch = m_DebouncedSwitchParams.eReverseSwitch;
    m_LastSwitchParams.eLeftIndicatorIntended = m_DebouncedSwitchParams.eLeftIndicatorIntended;
    m_LastSwitchParams.eRightIndicatorIntended = m_DebouncedSwitchParams.eRightIndicatorIntended;
    m_LastSwitchParams.eWorkLigthToggleSwitch = m_DebouncedSwitchParams.eWorkLigthToggleSwitch;
}

TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, onCANRequestOnOffCamera);
void CCANIterfSCAINA::onCANRequestOnOffCamera(const string& strData)
{
    TRC_SCOPE(ADAS, CCANIterfSCAINA, onCANRequestOnOffCamera);
	DBG_MSG(("CCANPPSParser::onCANRequestOnOffCamera %s\n ", strData.c_str()));

	map<string,string> mapParam;
	if (!CBasePPSParser::parse((char*)strData.c_str(), mapParam))
	{
		mapParam.clear();
		DBG_MSG(("CCANPPSParser::onCANRequestOnOffCamera: failed to parse\n"));
		return;
	}

	tagCANRequestOnOffCamera tagParams;
    static tagCANRequestOnOffCamera LasttagParams;
    static bool bFirst = true;
    if(bFirst)
    {
        bFirst =false;
        LasttagParams.eGenCam1 = eCANOnOff_NotAvailable;
        LasttagParams.eGenCam2 = eCANOnOff_NotAvailable;
        LasttagParams.eGenCam3 = eCANOnOff_NotAvailable;
        LasttagParams.eGenCam4 = eCANOnOff_NotAvailable;
        LasttagParams.eFrntVwCam = eCANOnOff_NotAvailable;
        LasttagParams.eRearVwCam = eCANOnOff_NotAvailable;
    }
	tagParams.eGenCam1= (ECANOnOffValue)StringUtil::toUInt( mapParam["GenCam1"].c_str() );
	tagParams.eGenCam2= (ECANOnOffValue)StringUtil::toUInt( mapParam["GenCam2"].c_str() );
	tagParams.eGenCam3= (ECANOnOffValue)StringUtil::toUInt( mapParam["GenCam3"].c_str() );
	tagParams.eGenCam4= (ECANOnOffValue)StringUtil::toUInt( mapParam["GenCam4"].c_str() );
	tagParams.eFrntVwCam= (ECANOnOffValue)StringUtil::toUInt( mapParam["FrntVwCam"].c_str() );
	tagParams.eRearVwCam= (ECANOnOffValue)StringUtil::toUInt( mapParam["RearVwCam"].c_str() );
    
    if(( tagParams.eGenCam1 == eCANOnOff_NotAvailable) || (tagParams.eGenCam1 == eCANOnOff_Error ))
	{
        tagParams.eGenCam1 = LasttagParams.eGenCam1 ;
		DBG_MSG(("CCanClient::onCANRequestOnOffCamera: eGenCam1 error\n"));
	}
    if(( tagParams.eGenCam2 == eCANOnOff_NotAvailable) || (tagParams.eGenCam2 == eCANOnOff_Error ))
	{
        tagParams.eGenCam2 = LasttagParams.eGenCam2 ;
		DBG_MSG(("CCanClient::onCANRequestOnOffCamera: eGenCam2 error\n"));
	}
    if(( tagParams.eGenCam3 == eCANOnOff_NotAvailable) || (tagParams.eGenCam3 == eCANOnOff_Error ))
	{
        tagParams.eGenCam3 = LasttagParams.eGenCam3 ;
		DBG_MSG(("CCanClient::onCANRequestOnOffCamera: eGenCam3 error\n"));
	}
    if(( tagParams.eGenCam4 == eCANOnOff_NotAvailable) || (tagParams.eGenCam4 == eCANOnOff_Error ))
	{
        tagParams.eGenCam4 = LasttagParams.eGenCam4 ;
		DBG_MSG(("CCanClient::onCANRequestOnOffCamera: eGenCam4 error\n"));
	}
    if(( tagParams.eFrntVwCam == eCANOnOff_NotAvailable) || (tagParams.eFrntVwCam == eCANOnOff_Error ))
	{
        tagParams.eFrntVwCam = LasttagParams.eFrntVwCam ;
		DBG_MSG(("CCanClient::onCANRequestOnOffCamera: eFrntVwCam error\n"));
	}
    if(( tagParams.eRearVwCam== eCANOnOff_NotAvailable) || (tagParams.eRearVwCam == eCANOnOff_Error ))
	{
        tagParams.eRearVwCam = LasttagParams.eRearVwCam ;
		DBG_MSG(("CCanClient::onCANRequestOnOffCamera: eRearVwCam error\n"));
	}

    if((LasttagParams.eGenCam1 != tagParams.eGenCam1)
    ||(LasttagParams.eGenCam2 != tagParams.eGenCam2)
    ||(LasttagParams.eGenCam3 != tagParams.eGenCam3)
    ||(LasttagParams.eGenCam4 != tagParams.eGenCam4)
    ||(LasttagParams.eFrntVwCam != tagParams.eFrntVwCam)
    ||(LasttagParams.eRearVwCam != tagParams.eRearVwCam)) 
    {
	    asynSendMessage(tagParams, sizeof(tagCANRequestOnOffCamera));
    }
    LasttagParams.eGenCam1 = tagParams.eGenCam1;
    LasttagParams.eGenCam2 = tagParams.eGenCam2;
    LasttagParams.eGenCam3 = tagParams.eGenCam3;
    LasttagParams.eGenCam4 = tagParams.eGenCam4;
    LasttagParams.eFrntVwCam = tagParams.eFrntVwCam;
    LasttagParams.eRearVwCam = tagParams.eRearVwCam;    
}

TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, SetUpCANCmdTable);
void CCANIterfSCAINA::SetUpCANCmdTable(map<string,CFunctor*>* mapCANCMD)
{
    TRC_SCOPE(ADAS, CCANIterfSCAINA, SetUpCANCmdTable);
	mapCANCMD->insert( makePair(CRUISEVEHSPEED, makeFunctor(this, &CCANIterfSCAINA::onCruiseControlVehSpeed)) );
	mapCANCMD->insert( makePair(CUVINFO, 	   makeFunctor(this, &CCANIterfSCAINA::onDirectionSwitchParams)) );
	mapCANCMD->insert( makePair(CANONOFF,       makeFunctor(this, &CCANIterfSCAINA::onCANRequestOnOffCamera)) );
    //debug
    mapCANCMD->insert( makePair(DEBUGSKIPFRAME, makeFunctor(this, &CCANIterfSCAINA::ondebug)) );
    
	DBG_MSG(("CCANIterfSCAINA::SetUpCANCmdTable done!!\n "));
};


//------------------------------------------------
CCANDebounceT::CCANDebounceT(int iDenbounceTime, DEBOUNCE_CALLBACK pCBDebounce, string sOwner)
//:m_eDebouncedState(eSV_Off)
:m_iMsgDebounceCnt(0)
,m_bSwtichValid(FALSE)
,m_sOwnerName("CCANDebounceTOwnerNotSet")
{
	m_DebounceTimer.setCallBack(::makeFunctor(this, &CCANDebounceT::onDebounceTimer), NULL);
	m_DebounceTimer.setRepeatCount(1);
	m_DebounceTimer.setDelay(iDenbounceTime);
	m_DebounceTimer.stop();
	m_pfuncCBDebounce = pCBDebounce;
	m_sOwnerName = sOwner;

}
CCANDebounceT::~CCANDebounceT()
{

}

void CCANDebounceT::onDebounceTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
	//timer out only happens not receiving 3 CAN cycles
	//keep last state received from CAN
	vResetDebouncePro();
	//notify owner to updated CAN signal for timer out, this is an abnormal process
	tagSwitchParams* pDebouncedSwitchParams = CCANIterfSCAINA::getInstance()->pGetDebouncedSwtichVal();
	tagSwitchParams* pCurrentSwtichVal = CCANIterfSCAINA::getInstance()->pGetCurrentSwtichVal();
	tagSwitchParams* pLastSwtichVal = CCANIterfSCAINA::getInstance()->pGetLastSwtichVal();
	m_pfuncCBDebounce(pDebouncedSwitchParams,pCurrentSwtichVal,pLastSwtichVal);
}

void CCANDebounceT::vResetDebouncePro()
{
	m_DebounceTimer.stop();
	m_iMsgDebounceCnt=0;
}

//timer is mean to check the state keep != ON fro three cycles
//when state is from on-> not on , then debouce timer will be launched 
//debounce works on turn off event , not turn on 
TRC_SCOPE_DEF(ADAS, CCANIterfSCAINA, vSetCANSigState);
void CCANDebounceT::vSetCANSigState(ESwitchValue eState,ESwitchValue* peDebouncedState)
{
	TRC_SCOPE(ADAS, CCANIterfSCAINA, vSetCANSigState);
	//debouncing state - check 2nd and 3rd cycle after on->!on happened
	if(m_DebounceTimer.isRunning())
	{
		if(eSV_On==eState) 
		{	
			DBG_MSG(("%s CCANDebounceT::vSetCANSigState: restart timer for received On state during debounce state\n",m_sOwnerName.c_str()));
			vResetDebouncePro();	
			*peDebouncedState = eSV_On;
		}
		else
		{	
			m_iMsgDebounceCnt++;
			if(CAN_MSG_DEBOUNCE_CNT<=m_iMsgDebounceCnt)
			{
				//successfully found 3 consecutive !ON CAN state
				//set CAN state on to off
				vResetDebouncePro();
				*peDebouncedState = eSV_Off;
				DBG_MSG(("%s CCANDebounceT::vSetCANSigState: stop timer for debouce process successed\n",m_sOwnerName.c_str()));
			}
			else
			{
				//before receive 3 consutivbe cycles, keep ON state
				*peDebouncedState = eSV_On;
			}
		}

	}
	//found a on->!on event, take it as 1st consecutive cycle, trigger debouncing
	else if((*peDebouncedState == eSV_On)&&(*peDebouncedState != eState))
	{
		m_iMsgDebounceCnt =1;
		m_DebounceTimer.start();
		//start debounce process, keep ON state
		*peDebouncedState = eSV_On;
		DBG_MSG(("%s CCANDebounceT::vSetCANSigState: start timer for found a ON->!ON event \n",m_sOwnerName.c_str()));
	}
	//idle state
	else 
	{
		*peDebouncedState = eState;
	}
	
}




