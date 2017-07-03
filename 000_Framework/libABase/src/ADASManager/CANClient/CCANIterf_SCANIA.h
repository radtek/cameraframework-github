#ifndef _CCAN_INTF_SCANIA_H
#define _CCAN_INTF_SCANIA_H

#include "svs.h"
#include "ICANIterf.h"

typedef void (*DEBOUNCE_CALLBACK)(tagSwitchParams *debounced,tagSwitchParams *current,tagSwitchParams *last);
#define CAN_MSG_DEBOUNCE_CNT  3

class CCANDebounceT
{
public:// method
	CCANDebounceT(int iDenbounceTime, DEBOUNCE_CALLBACK pCBDebounce, string sOwnerName);
	void vSetCANSigState(ESwitchValue eState,ESwitchValue* peDebouncedState);
	//ESwitchValue eGetCANSigState();
	~CCANDebounceT();
private:
    void onDebounceTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus);
	void vResetDebouncePro();
    CTimer m_DebounceTimer;
	int m_iMsgDebounceCnt;
	//ESwitchValue m_eDebouncedState;
	BOOLEAN m_bSwtichValid; //found a valid ON->!ON
	DEBOUNCE_CALLBACK m_pfuncCBDebounce;
	string m_sOwnerName;
};

class CCANIterfSCAINA : public ICANIterf , CBasePPSParser
{

public:// method
	void SetUpCANCmdTable(map<string,CFunctor*>* mapCANCMD);
	static CCANIterfSCAINA* getInstance();
	~CCANIterfSCAINA();
	tagSwitchParams* pGetDebouncedSwtichVal() {return &m_DebouncedSwitchParams;};
	tagSwitchParams* pGetCurrentSwtichVal() {return &m_CurSwitchParams;};
	tagSwitchParams* pGetLastSwtichVal() {return &m_LastSwitchParams;};
	void vUpdateTimerOutCANSig();//this is abnormal process
private:
	CCANIterfSCAINA();
	static CCANIterfSCAINA*		s_pInstance;
    
    void onCruiseControlVehSpeed(const string& strData);
    void onDirectionSwitchParams(const string& strData);
    void onCANRequestOnOffCamera(const string& strData);

    void ondebug(const string& strData);
    tagSwitchParams m_DebouncedSwitchParams;
	tagSwitchParams m_CurSwitchParams;
	tagSwitchParams m_LastSwitchParams;
	CCANDebounceT* m_pWorklightDT;
	CCANDebounceT* m_pLeftTurnDT;
	CCANDebounceT* m_pRightTurnDT;
};

#endif
