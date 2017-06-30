#ifndef _CCAMERA_FAULT_CHECK
#define _CCAMERA_FAULT_CHECK


#include "svs.h"
#include "CCamera.hpp"

class CCameraFaultCheck
{
public:
	enum EStatus
	{
		eStatus_Valid,
		eStatus_Invalid,
		eStatus_Deactivate,
	};
public:
	CCameraFaultCheck(CCamera::EPos ePos);
	virtual ~CCameraFaultCheck();

	void	start();
	void	stop();
	void	reset(BOOLEAN bRestInCheck=TRUE);

	void	onVsyncValid(CCamera::EPos ePos);
	void 	onVsyncInvalid(CCamera::EPos ePos);
	//timer
	virtual void 	onCheckFaultDebounceTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus);
	virtual void 	onCheckFaultHealingTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus);

private:
	CCamera::EPos	m_ePos;
	BOOLEAN			m_bInCheck;
	EStatus			m_eCameraStatus;
	CTimer			m_debounceTimer;
	CTimer			m_healingTimer;
};

class CCameraFaultCheckSCAINA : public CCameraFaultCheck
{
public:
	CCameraFaultCheckSCAINA(CCamera::EPos ePos);
	virtual ~CCameraFaultCheckSCAINA();

	//timer
	void 	onCheckFaultDebounceTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus){printf("no CheckFault on DebounceTimer for SCAINA \n");};
	void 	onCheckFaultHealingTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus){printf("no CheckFault on HealingTimer for SCAINA \n");};
};

#endif
