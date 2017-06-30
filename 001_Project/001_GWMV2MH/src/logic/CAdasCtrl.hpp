#ifndef _CADAS_CTRL_HPP_
#define _CADAS_CTRL_HPP_

#include "svs.h"
#include "CCamera.hpp"
#include "CAdasMsgQueDefine.hpp"
#include "CCameraSysManager.h"

class CAdasCtrl : public IAdasCtrl, CMessageSubHandler
{
public: // enum struct
	enum ECameraIdx
	{
		eCamera1,
		eCamera2,
		eAllCamera,
	};

public: // method
   static CAdasCtrl* getInstance();
   static void delInstance();
   virtual ~CAdasCtrl();

   DECLARE_DISPATCH
   
   virtual BOOLEAN 	initialize();
   virtual void		unInitialize();
   virtual void 	beforeHandleMessageQueue();
   virtual void 	afterHandleMessageQueue();
   virtual BOOLEAN	isNeedFastADAS();//extendable: different camera behaviour
   virtual void		startFastADAS();
   virtual void		startNormalADAS();
   virtual void		checkSystemEventAfterStartUp();
   

   bool 			bAdasInitCameraSystem();
   bool 			bAdasDestroyCameraSystem();

   void				setNeedUpdateCameraState(CCamera::EPos ePos);//todo: not implemented


   CCameraCtrl*		getCameraCtrl()		{ return m_pCameraCtrl;}

   tagQNXCaptureDriverConfig& getCaptureConfig()	{ return m_captureDriverCfg;	}

   // CAdasService
   BOOLEAN	canToggleSwitchCamera();
   void 	toggleSwitchCamera(void* pData);

   BOOLEAN	canManualActivateCamera1();
   BOOLEAN	canManualDeactivateCamera1();
   BOOLEAN	canManualActivateCamera2();
   BOOLEAN	canManualDeactivateCamera2();

   void		showCamera(void* pData);
   void		showGuideLine(void* pData);
   void		activeSettingMode(void* pData);

   void 	onGetCameraState(void* pData);
   void 	onGetCameraStateDiag(void* pData);
   void 	onGetCameraStateHMI(void* pData);
   
   void 	onGetCameraConfig(void* pData);

   void		onPowerOnOffSucceed(void* pData);
   void		onPowerOnOffFail(void* pData);

   void		setPosSize(void* pData);

   void 	setReverseTimerDeactivate(void* );

   void		onCaptureSignalEvent(void*);
   
   void		onAutoUpdateState(void*);//extendable: different camera behaviour
   void     onGuideLineTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus);
   CCamera::EPos getLastShowCameraPos() {return m_eLastShowCameraPos;};
private: // method
   CAdasCtrl();
   CTimer m_GuideLineTimer;

protected:// data

private:// data
   static CAdasCtrl* 		m_pInstance;

   tagQNXCaptureDriverConfig	m_captureDriverCfg;

   //todo:not used this data--used for CAN
   BOOLEAN					m_bNeedUpdateCameraState[CCameraCtrl::eCameraNum];
   BOOLEAN					m_bShowGuideLine;
   CCameraCtrl*				m_pCameraCtrl;

   CCameraCtrl::EState		m_eLastState;
   CCamera::EPos			m_eLastShowCameraPos;
   CCamera::EStatus			m_aryLastCameraStatus[CCameraCtrl::eCameraNum];
   //it is possible to save this state cause when auto actived , HMI can not cancel auto active state
   CCamera::EAutoActiveType	m_aryLastCameraAAType[CCameraCtrl::eCameraNum];
};

#endif  

