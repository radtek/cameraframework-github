#include "CCameraFaultCheck.hpp"
#include "CEOL.hpp"
#include "CAdasCtrl.hpp"
#include "CDiagnosticClient.hpp"
#define DIAGNOSIS_REPORT_DEBOUNCE_TIME    5000
#define DIAGNOSIS_REPORT_HEALING_TIME    5000 

CCameraFaultCheckSCAINA::CCameraFaultCheckSCAINA(CCamera::EPos ePos)
:CCameraFaultCheck(ePos)
{
	//setPos(ePos);
	stop();
}

CCameraFaultCheckSCAINA::~CCameraFaultCheckSCAINA()
{
	stop();
}
//===
CCameraFaultCheck::CCameraFaultCheck(CCamera::EPos ePos)
: m_ePos(ePos)
, m_bInCheck(FALSE)
, m_eCameraStatus(eStatus_Deactivate)
{
	//todo timer setdealy
	 m_debounceTimer.setCallBack(::makeFunctor(this, &CCameraFaultCheck::onCheckFaultDebounceTimer), NULL);
	 m_debounceTimer.setRepeatCount(1);
	 m_debounceTimer.setDelay(DIAGNOSIS_REPORT_DEBOUNCE_TIME);

	 m_healingTimer.setCallBack(::makeFunctor(this, &CCameraFaultCheck::onCheckFaultHealingTimer), NULL);
	 m_healingTimer.setRepeatCount(1);
	 m_healingTimer.setDelay(DIAGNOSIS_REPORT_HEALING_TIME);
}

CCameraFaultCheck::~CCameraFaultCheck()
{
	stop();
}

void CCameraFaultCheck::start()
{
	if( m_bInCheck == FALSE )
	{
		m_bInCheck = TRUE;

		CCameraCtrl* pCameraCtrl = CAdasCtrl::getInstance()->getCameraCtrl();
		CCamera* pCamera = pCameraCtrl->getCamera(m_ePos);
		if( pCamera && pCamera->isInShow() )
		{
			BOOLEAN bSignalValid = pCamera->getSignalValid();
			if( bSignalValid )
			{
				m_debounceTimer.stop();
				m_healingTimer.start();
			}
			else
			{
				m_healingTimer.stop();
				m_debounceTimer.start();
			}
		}
	}
}

void CCameraFaultCheck::stop()
{
	m_bInCheck = FALSE;
	m_debounceTimer.stop();
	m_healingTimer.stop();
}
TRC_SCOPE_DEF(ADAS, CCameraFaultCheck, reset);
void CCameraFaultCheck::reset(BOOLEAN bRestInCheck)
{
    TRC_SCOPE(ADAS, CCameraFaultCheck, reset);
	//if( m_bInCheck == FALSE )
	{
	if( bRestInCheck )
		m_bInCheck = TRUE;

		m_debounceTimer.stop();
		m_healingTimer.stop();
		m_eCameraStatus = eStatus_Deactivate;

		DBG_MSG(("CCameraFaultCheck::reset() pos = %u\n", (UInt32)m_ePos));

		CCameraCtrl* pCameraCtrl = CAdasCtrl::getInstance()->getCameraCtrl();
		CCamera* pCamera = pCameraCtrl->getCamera(m_ePos);
		if( m_bInCheck && pCamera && pCamera->isInShow() )
		{
			DBG_MSG(("CCameraFaultCheck::reset() Show\n"));
			BOOLEAN bSignalValid = pCamera->getSignalValid();
			if( bSignalValid )
			{
				m_debounceTimer.stop();
				m_healingTimer.start();
			}
			else
			{
				m_healingTimer.stop();
				m_debounceTimer.start();
			}
		}
	}
}

void CCameraFaultCheck::onVsyncValid(CCamera::EPos ePos)
{
	if( m_bInCheck )
	{
		m_debounceTimer.stop();

		if( m_eCameraStatus != eStatus_Valid )
		{
			m_healingTimer.start();
		}
	}
}

void CCameraFaultCheck::onVsyncInvalid(CCamera::EPos ePos)
{
	if( m_bInCheck )
	{
		m_healingTimer.stop();

		if( m_eCameraStatus != eStatus_Invalid )
		{
			m_debounceTimer.start();
		}
	}
}

void CCameraFaultCheck::onCheckFaultDebounceTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
	m_eCameraStatus = eStatus_Invalid;
    //camera fault is active, not camera signal is active
	CDiagnosticClient::getInstance()->reportFault(CDiagnosticClient::eACTIVE_CONFIRM,m_ePos);
}

void CCameraFaultCheck::onCheckFaultHealingTimer(CTimer*, UInt32 uiRepeatCnt, CTimer::ETimerStatus eStatus)
{
	m_eCameraStatus = eStatus_Valid;

	CDiagnosticClient::getInstance()->reportFault(CDiagnosticClient::eINACTIVE_CONFIRM,m_ePos);
}
