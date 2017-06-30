#include "CDiagnosticProcessor.hpp"
#include "CAdasCtrl.hpp"
#include "Env.hpp"

CDiagnosticProcessor* CDiagnosticProcessor::s_pInstance = NULL;
CDiagnosticProcessor* CDiagnosticProcessor::getInstance()
{
   if(s_pInstance == NULL)
   {
	   s_pInstance = new CDiagnosticProcessor();
   }
   return s_pInstance;
}

void CDiagnosticProcessor::delInstance()
{
#if 0
   if(m_camera1FaultCheck != NULL)
   {
      delete m_camera1FaultCheck;
      m_camera1FaultCheck = NULL;
   }   
   if(m_camera2FaultCheck != NULL)
   {
      delete m_camera2FaultCheck;
      m_camera2FaultCheck = NULL;
   }
#endif
   if(s_pInstance != NULL)
   {
      delete s_pInstance;
      s_pInstance = NULL;
   }
}

CDiagnosticProcessor::~CDiagnosticProcessor()
{
	s_pInstance = NULL;
}

CDiagnosticProcessor::CDiagnosticProcessor()
{
	if(Env::isMANTarget())
	{
	    m_camera1FaultCheck = new CCameraFaultCheck(CCamera::eCamera1);
		m_camera2FaultCheck = new CCameraFaultCheck(CCamera::eCamera2);	
		printf("MAN CCameraFaultCheck created \n");
	}
	else if(Env::isScaniaTarget())
	{
	    m_camera1FaultCheck = (CCameraFaultCheck*)new CCameraFaultCheckSCAINA(CCamera::eCamera1);
		m_camera2FaultCheck = (CCameraFaultCheck*)new CCameraFaultCheckSCAINA(CCamera::eCamera2);
		printf("SCAINA CCameraFaultCheck created \n");
	}
	onCheckFaultStart(NULL);
}

BEGIN_DISPATCH(CDiagnosticProcessor)
	DISPATCH_EVENT(eDiag_Start, onCheckFaultStart)
	DISPATCH_EVENT(eDiag_Stop, onCheckFaultStop)
	DISPATCH_EVENT(eDiag_ResetCamera1, onCheckFaultResetCamera1)
	DISPATCH_EVENT(eDiag_ResetCamera2, onCheckFaultResetCamera2)
END_DISPATCH

void CDiagnosticProcessor::onCheckFaultStart(void* )
{
	m_camera1FaultCheck->start();
	m_camera2FaultCheck->start();
}

void CDiagnosticProcessor::onCheckFaultStop(void*)
{
	m_camera1FaultCheck->stop();
	m_camera2FaultCheck->stop();
}

void CDiagnosticProcessor::onCheckFaultResetCamera1(void*)
{
	m_camera1FaultCheck->reset();
}

void CDiagnosticProcessor::onCheckFaultResetCamera2(void*)
{
	m_camera2FaultCheck->reset();
}
TRC_SCOPE_DEF(ADAS, CDiagnosticProcessor, onVsyncValid);
void CDiagnosticProcessor::onVsyncValid(CCamera::EPos ePos)
{
	if( ePos == CCamera::eCamera1 )
	{
		m_camera1FaultCheck->onVsyncValid(ePos);
	}
	else if( ePos == CCamera::eCamera2 )
	{
		m_camera2FaultCheck->onVsyncValid(ePos);
	}
	else
	{
		TRC_SCOPE(ADAS, CDiagnosticProcessor, onVsyncValid);
		DBG_ERROR(("CDiagnosticProcessor::onVsyncValid error\n"));
	}
}

TRC_SCOPE_DEF(ADAS, CDiagnosticProcessor, onVsyncInvalid);
void CDiagnosticProcessor::onVsyncInvalid(CCamera::EPos ePos)
{
	if( ePos == CCamera::eCamera1 )
	{
		m_camera1FaultCheck->onVsyncInvalid(ePos);
	}
	else if( ePos == CCamera::eCamera2 )
	{
		m_camera2FaultCheck->onVsyncInvalid(ePos);
	}
	else
	{
		TRC_SCOPE(ADAS, CDiagnosticProcessor, onVsyncInvalid);
		DBG_ERROR(("CDiagnosticProcessor::onVsyncInvalid error\n"));
	}
}

void CDiagnosticProcessor::onShowCamera(CCamera::EPos ePos)
{
	m_camera1FaultCheck->reset(FALSE);
	m_camera2FaultCheck->reset(FALSE);
}

void	CDiagnosticProcessor::onHideCamera(CCamera::EPos ePos)
{
	//m_camera1FaultCheck->reset();
	//m_camera2FaultCheck->reset();
}
