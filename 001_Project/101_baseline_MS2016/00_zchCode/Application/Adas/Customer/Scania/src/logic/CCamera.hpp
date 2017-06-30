#ifndef _CADAS_CTRL_CAMAERASTATE_HPP_
#define _CADAS_CTRL_CAMAERASTATE_HPP_

#include "svs.h"

class CCamera
{
public: // enum struct
	enum EType
	{
		eType_Off,
		eType_General,
		eType_Reverse,
		eType_Front,
	};
	
	enum ESpeedLastState
	{
		eSpeedLastState_0,
		eSpeedLastState_Normal,
		eSpeedLastState_TooHigh,
	};

	//MAN TRUCK have dependency on active source!!
	//new design need active souce type!
	enum EAutoActiveType
	{
		eType_PIN1,
		eType_PIN2,
		eType_CAN_REVERSE,
		eType_CAN_REQUEST,
		eType_CAN_SPEED_DEA_REAR,
		eType_CAN_SPEED,
		eType_CAN_WORKLIGHT,
		eType_CAN_DIRECTION,
		eType_NULL,
	};
	/*
	 1 --  Activated
	 2 --  Deactivated
	 3 --  Not Connected
	 4 --  Not Initialised - Sent when camera config has not read from EOL
	 //5 --  WrongSwitchNoCamera
	 6 --  ImageFrozen
	 7 --  ShowDefaultImage before camera is rendered when camera is activated
	 * */
	enum EStatus
	{
		// internal
		eStatus_ManualActivated			= 0x0200,
		eStatus_AutoActivated			= 0x1200,
		//eStatus_ManualActivated		= 0x0200,
		eStatus_Deactivated 		= 0x0100,

		//eStatus_General				= 0x1200,	//0x1000 | eStatus_Activated
		//eStatus_Reverse				= 0x2200,	//0x2000 | eStatus_Activated
		//eStatus_Front				= 0x3200,	//0x3000 | eStatus_Activated
	};

	enum EShowState
	{
		eShowState_Hide		= 0x0001,
		eShowState_onGoing	= 0x0100,
		eShowState_Showing	= 0x1100
	};

#if 0
todo
1 --  Activated
2 --  Deactivated
3 --  Not Connected - no valid camera input
4 --  Not Initialised - Sent when camera config has not read from EOL
5 --  ActivationOngoing - sent when camera is switched and after some time if the camera signal is valid, ADAS will send the activated state to HMI

#endif
	enum EExternalStatus
	{
		eEStatus_Activated			= 1,
		eEStatus_Deactivated 		= 2,
		// for external
		eEStatus_NotConnected		= 3,	// 0x0001 | eStatus_Activated
		eEStatus_NotInitialised 	= 4,	// 0x0002 | eStatus_Deactivated/eStatus_Activated
		//eStatus_WrongSwitch 		= 0x0104,	// 0x0004 | eStatus_Deactivated this can not be supported maybe activated but can not switch
		eEStatus_ActivationOngoing 	= 5,
		eEStatus_ImageFrozen		= 6,	// 0x0005 | eStatus_Activated
		eEStatus_ShowDefaultImage	= 7,	// 0x0006 | eStatus_Activated
	};


	enum ETriggerMethod
	{
		eTrig_OverSpeed	= -2,
		eTrig_Off		= -1,
		eTrig_HardPin	= 0,
		eTrig_CAN		= 1,
		eTrig_HMI		= 2,
		eTrig_Detect 	=3,
		//CR46- for general camera can comman  only - hmi dependency
		eTrig_CANCOMMAND	=4 
	};


	enum EPos
	{
		eCamera1 = 0,
		eCamera2 = 1,
		eCameraNum,
	};

public:
	CCamera(EPos ePos, EType eType);

	virtual ~CCamera()	{;}

	virtual BOOLEAN 		canAutoActivated() = 0;//include checking all auto active events: CAN/Hard pin
	virtual BOOLEAN 		canManualActivated()  = 0;
	virtual BOOLEAN			canManualDeactivated()  = 0;

	virtual void			SetStateManualActivate()	{ m_eStatus = eStatus_ManualActivated; }
	virtual void			SetStateAutoActivate()		{ m_eStatus = eStatus_AutoActivated; }
    //new design to cancel manually active state on a successful auto active event from another camera->20170527 keep manualy as HMI depends on this
	virtual void			SetStateDeactivate()		{ m_eStatus = eStatus_Deactivated; hide();}
	virtual void			show();
	virtual void			hide();

	EStatus 				getStatus() const			{ return m_eStatus; }
	EPos					getPos() const				{ return m_ePos;	}
	EType					getType() const				{ return m_eType;	}
	BOOLEAN					isOffCamera() const			{ return (m_eType == eType_Off);	}
	BOOLEAN 				isAutoActivated() const		{ return ( m_eStatus == eStatus_AutoActivated );	}
    BOOLEAN 				isManualActivated() const		{ return ( m_eStatus == eStatus_ManualActivated );	}
	EExternalStatus			getExternalStatus() const;
	BOOLEAN					isActivated() const			{ return (m_eStatus != eStatus_Deactivated); }
	BOOLEAN					isInShow() const			{ return ( (m_eShowState & eShowState_onGoing) != 0);	}

	BOOLEAN					getSignalValid() const			{ return m_bVsynValid;	}
	void					setSignalValid(BOOLEAN bValid);

	void 					onShowTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus);
    BOOLEAN     isLastManualActivated()                 { return m_bManualActivatedLastScreen;	}
	void 		setLastManualActivated()				{ m_bManualActivatedLastScreen = TRUE; }
	void 		ResetLastManualActivated()				{ m_bManualActivatedLastScreen = FALSE;	}
    //only get correct AA type in Auto Active state
	EAutoActiveType getAutoActiveType() const 				{ return m_eAutoActiveType;             }
    void 		setAutoActivatedType_NULL()				{ m_eAutoActiveType = eType_NULL;	}
    void 		setAutoActivatedType_HardPin()		    { if(m_ePos == eCamera1) m_eAutoActiveType = eType_PIN1; if(m_ePos == eCamera2) m_eAutoActiveType = eType_PIN2;	}
    //void 		setAutoActivatedType_CAN()				{ m_eAutoActiveType = eType_CAN;	}
    BOOLEAN     isHardPinActivated()                    { return (m_eAutoActiveType == eType_PIN1)||(m_eAutoActiveType == eType_PIN2);}
	//CR46 : HMI dependency, general camera CAN request take as trigger method 4 - non overridale
    BOOLEAN    	isCANCommandActivated()                    { return (m_eAutoActiveType == eType_CAN_REQUEST);}
    BOOLEAN     isCANSwitchActivated() const
    { 
       return ((m_eAutoActiveType == eType_CAN_REVERSE)
             ||(m_eAutoActiveType == eType_CAN_REQUEST)
             ||(m_eAutoActiveType == eType_CAN_WORKLIGHT)
             ||(m_eAutoActiveType == eType_CAN_DIRECTION));
    }
    BOOLEAN     isCANSpeedActivated() const
    { 
       return (m_eAutoActiveType == eType_CAN_SPEED);
    }
    
    BOOLEAN     isCANSpeedActivatedRearCam() const
    { 
       return (m_eAutoActiveType == eType_CAN_SPEED_DEA_REAR);
    }
    //specail case for overide state for rear cam
    BOOLEAN     isRearGearActivatedRearCam() const
    { 
       return ((isCANSpeedActivatedRearCam())
             ||(m_eAutoActiveType == eType_CAN_REVERSE));
    }
    
    BOOLEAN     isCANActivated() const
    { 
       return (isCANSwitchActivated()|| isCANSpeedActivated()||isCANSpeedActivatedRearCam());
    }

	//For CR 46
    BOOLEAN   isWorkLgtDirtIndiActivated() const
    { 
       return ((m_eAutoActiveType == eType_CAN_WORKLIGHT)
             ||(m_eAutoActiveType == eType_CAN_DIRECTION));
    }
	
    //virtual BOOLEAN     isStandbyWakeUp()    const       { return FALSE;}
    virtual BOOLEAN     isStandbyWakeUp();
    void        stopShowTimer();
    BOOLEAN     isInStartUpPhase()                       { return m_bStartup;}
    void        setStartupState(BOOLEAN state)           { m_bStartup = state;}
    void		SetVsynSigIsReadyToChk(BOOLEAN state) 	 { m_bVsynSigIsReadyToChk = state;}
    void		startShowTimer();
    void        stopKPIshowTimer()              {m_KPIshowTimer.stop();};
    void		startKPIshowTimer()             {m_KPIshowTimer.start();};   
    BOOLEAN	    IsRunningKPIshowTimer()         {return m_KPIshowTimer.isRunning();};
    void        OnKPIshowTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus);
    BOOLEAN     IsSpeedHighState()               {return m_bSpeedHighSate;};
protected:
	void 		setStatus(EStatus eStatus)				{ m_eStatus = eStatus;	}
	BOOLEAN		isInReverse() const;
    BOOLEAN		isNotInReverse() const;
	BOOLEAN		isParkBrakeSwitchNotSet() const;
	BOOLEAN		isPinOnOffRequestShowCamera(EPos epos) const;
	EAutoActiveType m_eAutoActiveType;
    BOOLEAN		m_bSpeedHighSate;//use case: failed to active due to speedhigh; succeed to deactive dut to speedtoo high
	ESpeedLastState m_eSpeedLastState;

private:
	EStatus 		m_eStatus;
	EPos			m_ePos;
	EType			m_eType;
	BOOLEAN			m_bVsynValid;
    BOOLEAN         m_bVsynSigIsReadyToChk;
	//BOOLEAN			m_bInShow;
	EShowState		m_eShowState;
	CTimer			m_showTimer;
	BOOLEAN			m_bManualActivatedLastScreen;
	BOOLEAN			m_bStartup;
    CTimer			m_KPIshowTimer;
};

class CReverseCamera : public CCamera
{
public:

public:
	CReverseCamera(EPos ePos);
	virtual ~CReverseCamera();

	virtual BOOLEAN 		canAutoActivated() ;
	virtual BOOLEAN 		canManualActivated() ;
	virtual BOOLEAN			canManualDeactivated() ;
	virtual void			deactivate();
    virtual BOOLEAN			isInReverse() ; //reverse gear will overide by hard key
    virtual BOOLEAN	        isNotInReverse();
	static void				stopDeactivateTimer();	// this method will be called after updateCameraState every time
	void					onExitRvsTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus);
    //stop timer but go A2M state
    static void             vDisableAutoHideTimer() {m_bEnableAutoHideTimer = FALSE; stopDeactivateTimer();};
    void                    vEnableAutoHideTimer()  {m_bEnableAutoHideTimer = TRUE;};
    BOOLEAN                 bIsAutoHideTimerEnabled()  { return m_bEnableAutoHideTimer;};
    static void             vSetDirectlyCancelRearCam() ;
    static void             vCancelDirectlyCancelRearCam();
    static BOOLEAN          bDirectlyCancelledRearCam();
	BOOLEAN					isSpeedNormal() const;
	BOOLEAN					isSpeedHigh() const;
	BOOLEAN					isSpeedTooHigh();
	BOOLEAN					isNeedTimerDeactivated() const;
    BOOLEAN                 isCANOnOffRequestShowCamera() const;
	void					startDeactivateTimer();
    BOOLEAN                 isEitherHardPinActived();

private:
    //rear camera only have one timer defined in system
	static CTimer* 			m_pDeactivatedTimer;
	UInt32					m_uiDeactivatedTime;
    BOOLEAN                 m_bLsatIsReverseState;
    static BOOLEAN          m_bEnableAutoHideTimer;
    static BOOLEAN          m_bDirectlyCancelRearCam[CCamera::eCameraNum];
};

class CFrontCamera : public CCamera
{
public:

public:
	CFrontCamera(EPos ePos);
	virtual ~CFrontCamera();

	virtual BOOLEAN 		canAutoActivated();
	virtual BOOLEAN 		canManualActivated() ;
	virtual BOOLEAN			canManualDeactivated() ;
private:
	BOOLEAN					isSpeedNormal() const;
	BOOLEAN					isSpeedHigh() const;
	BOOLEAN					isSpeedTooHigh();
   BOOLEAN              isCANOnOffRequestShowCamera() const;
};

class CGeneralCamera : public CCamera
{
public:

public:
	CGeneralCamera(EPos ePos);
	virtual ~CGeneralCamera();

	virtual BOOLEAN 		canAutoActivated();
	virtual BOOLEAN 		canManualActivated() ;
	virtual BOOLEAN			canManualDeactivated() ;
public:
	BOOLEAN					isSpeedNormal() const;
	BOOLEAN					isSpeedHigh() const;
	BOOLEAN					isSpeedTooHigh();
   BOOLEAN              isCANOnOffRequestShowCamera() const;

private:
   BOOLEAN              isCANOnOffShowGenCamera1() const;
   BOOLEAN              isCANOnOffShowGenCamera2() const;
   BOOLEAN              isCANOnOffShowGenCamera3() const;
   BOOLEAN              isCANOnOffShowGenCamera4() const;
};

class COffCamera : public CCamera
{
public:
	COffCamera(EPos ePos)
	: CCamera(ePos, eType_Off)
	{
		;
	}

	virtual BOOLEAN 		canAutoActivated() 			{ return FALSE; }
	virtual BOOLEAN 		canManualActivated()  	{ return FALSE; }
	virtual BOOLEAN			canManualDeactivated()  { return FALSE; }
	virtual void			activate()		{}
	virtual void			deactivate()	{}
};
//------------
class CAdasCameraPrio
{
public:
	CAdasCameraPrio(const CCamera* pCamera1,const CCamera* pCamera2);
	virtual ~CAdasCameraPrio();
	virtual CCamera::EPos 	getPrioCameraOnMultiActive() const;
	virtual CCamera::EPos 	getPrioCameraOnToggle(CCamera::EPos CurrShowCameraPos) const;
protected:
	const CCamera*				m_pPrioCamera1;
	const CCamera*				m_pPrioCamera2;
};


class CAdasCameraPrioMT : public CAdasCameraPrio
{
public:
	CAdasCameraPrioMT(const CCamera* pCamera1,const CCamera* pCamera2);
	virtual ~CAdasCameraPrioMT();
	virtual CCamera::EPos 	getPrioCameraOnMultiActive() const;
	virtual CCamera::EPos 	getPrioCameraOnToggle(CCamera::EPos CurrShowCameraPos) const;
};
//------------

class CCameraCtrl
{
public: // enum struct typedef
	enum { eCameraNum = 2 };
	enum EManualActivateCamera
	{
		eManualActivate,
		eManualDeactivate,
		eManualNon,
	};

	enum EState
	{
        //start with non-zero as a bug -- value 256 found 
		eState_AllDeactive =1,//meaning no auto actived cameara
		eState_CameraSetting,
		eState_OneAACamera,
		eState_TwoAACamera,


	};

	enum EOperation
	{
		eOp_Toggle,
		eOp_EnterCameraSetting,
		eOp_ExitCameraSetting,
		eOp_AACamera1,
		eOp_DeaCamera1,
		eOp_AACamera2,
		eOp_DeaCamera2,
		eOp_ShowCamera1,
		eOp_ShowCamera2,
		eOp_HideCamera1,
		eOp_HideCamera2,
		eOp_A2MCamera1,
		eOp_A2MCamera2,

	};

public: // method
	CCameraCtrl();
	~CCameraCtrl();

	BOOLEAN initialize();
	void	unInitialize();

	void 	updateCameraStateAuto(UInt32 uidx);
    void 	updateCameraStateManually(EOperation eOp);
	void	updateState(EOperation eOp);

	BOOLEAN	canToggleSwitchCamera();
	void 	toggleSwitchCamera();

	BOOLEAN	canManualActivate(CCamera::EPos ePos) const;
	BOOLEAN	canManualDeactivate(CCamera::EPos ePos) const;

	static BOOLEAN isAllCamerasOff();

	CCamera*	getCamera(CCamera::EPos ePos);
	CCamera*	getCamera(CCamera::EType eType);

	static CCamera::EStatus getCameraStatus(CCamera::EPos ePos)
	{
		return m_aryStatus[ePos];
	}   
    
	CCamera::EAutoActiveType getCameraActiveType(CCamera::EPos ePos) const
	{
        if(m_ppCamera[ePos])
        {
            return m_ppCamera[ePos]->getAutoActiveType();
        }
        else
        {
            return CCamera:: eType_NULL;
        }
	}
	CCamera::EPos 		getCurShowCameraPos() const	{ return m_eShowCameraPos;	}
	CCameraCtrl::EState	getState() const			{ return m_eState;			}

	void	setCurShowCameraValid(BOOLEAN b);

	void	onOff()                         		 {m_eShowCameraPos = CCamera::eCameraNum;}
	BOOLEAN    IsManuallyClosed() const              {return m_bManuallyClose;}
    //
    void	EnableManuallyClose()           		{m_bManuallyClose   = TRUE;}
    //deactivate camera until next request to show anyone of the camera coming up - specail case is hide request or front camera use case
    //for hide camera on speed high or CAN CMD, one or two actived use case, the manually closed camera view is not expected to show on screen.so camera state of show should not send out
    //for front camera, not possible to recevie manually deactive on CAN request
    void	DisableManuallyClose()          		{m_bManuallyClose   = FALSE;}
    
protected:// method


private: // method
	CCamera*createCamera(CCamera::EType eType, CCamera::EPos ePos);
	void 	showCamera(CCamera::EPos);
	UInt32 	getAutoActivatedCameraNum() const;
	void 	cameraSettingStateToggle();
	void	normalToggle();
	void	aaTwoCameraToggle();
	void	refreshShowCamera();
	void	cameraSettingShowCamera(CCamera::EPos);

private:// data
   //todo: add MAN camera behaviour
	static CCamera*			m_ppCamera[eCameraNum];
	static CCamera::EStatus	m_aryStatus[eCameraNum];//camera active state - manually or auto or deactive--copy from camera object
	CCamera::EPos			m_eShowCameraPos;
	BOOLEAN					m_bInToogleState;
	EState					m_eState;//number of camera active state - deactive(=normal) or auto or setting
    CAdasCameraPrio*        m_pCAdasCameraPrio;
    //to support HMI overridable mode
    BOOLEAN                 m_bManuallyClose;
};

#endif  

