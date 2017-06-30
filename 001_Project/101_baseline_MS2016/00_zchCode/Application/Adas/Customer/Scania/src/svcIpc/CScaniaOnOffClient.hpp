#ifndef _CSCANIAONOFF_CLIENT_HPP
#define _CSCANIAONOFF_CLIENT_HPP

#include "svs.h"
#include "MessageDefineSCANIA.hpp"
#include "CCamera.hpp"

#define SANDBY_MODE_COMM     2
#define SANDBY_MODE_MAN      8
#define SANDBY_MODE_SCAINA   1

class CScaniaOnOffClient : public CBaseDBUSParser
{
public:	//enum struct typedef

	enum EStandby
	{
		EOutOfStandby   = 0,
		EStandbySCAINA  = 1,
		EStandbyComm    = 2,
		EStandbyMAN     = 8,
	};

    enum EStandbyWakeUpReqCode
	{
		E_MANWakeUp     = 23,
		E_SCAINAWakeUp  = 21,
		E_HKWakeUp      = 22,
	};
    
    enum EPowerOffModeReqCode
	{
        E_NULLPowOffMode  = 0,
		E_SCAINAPowOffMode  = 23,
	};
    
public: // method
   static CScaniaOnOffClient* getInstance();
   static void delInstance();
   ~CScaniaOnOffClient();

   // request
   //power supply for sania is always on, the control logic is MAN actually
   void requestPowerOnCamera(UInt32 uidx, UInt32 uiState,BOOLEAN bCamState);
   void getPowerModeInfo();
   void onOffPmodePostEvent(UInt32 uidx,BOOLEAN bHKWakeup);
   // response
   void processPowerOnResponse(const string& strData);
   void procgetPowerModeInfoResp(const string& strData);

   //signal
   void onCameraStatusInfo(const string& strData);
   void onpowerModeInfo(const string& strData);
   BOOLEAN  isScaniaPinShowCam(CCamera::EPos ePos) const  { return (m_eLogicPINOnOffCam[ePos] == ePINOnOff_On);         }
   BOOLEAN  isScaniaPinHideCam(CCamera::EPos ePos) const  { return (m_eLogicPINOnOffCam[ePos] == ePINOnOff_Off);        }

   void  FastSetScaniaPinShowCam(CCamera::EPos ePos)   {  m_eLogicPINOnOffCam[ePos] = ePINOnOff_On;        }
   void  FastSetScaniaPinHideCam(CCamera::EPos ePos)   {  m_eLogicPINOnOffCam[ePos] = ePINOnOff_Off;        }
   BOOLEAN  isInStandbyState();
   void  vSetLogicPinOff() {m_eLogicPINOnOffCam[0]=ePINOnOff_Off;m_eLogicPINOnOffCam[1]=ePINOnOff_Off;};
protected: // method
   CScaniaOnOffClient();

private: // data
   static CScaniaOnOffClient*		s_pInstance;
   EPINOnOffValue     m_ePINOnOffCam[2];
   EPINOnOffValue     m_eLogicPINOnOffCam[2];
   EStandby           m_eCurpowerMode;
   EStandby           m_eConfigStandbyCode;
   EPowerOffModeReqCode  m_eConfigPowerOffModeReqCode;
   EStandbyWakeUpReqCode m_eConfigWakeUpReqCode;
   ECamOnOffValue     m_eCamOnOffState[2];
   BOOLEAN            m_bPowModeDefault;
   BOOLEAN            m_bHardKeyWakeUpCycle;
   UInt32			  m_uiCameraOneLastStatus;
   UInt32			  m_uiCameraTwoLastStatus;
};

#endif
