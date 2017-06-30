#include "CCaptureThread.h"
#include "videoCapture/CCaptureDriver.hpp"
#include "videoCapture/CQNXCaptureDriver.hpp"

BOOLEAN CCaptureThread::initialize()
{

	return TRUE;
}
TRC_SCOPE_DEF(ADAS, CCaptureThread, unInitialize);
void CCaptureThread::unInitialize()
{
	TRC_SCOPE(ADAS, CCaptureThread, unInitialize);
	DBG_MSG(("CVideoCaptureThread::unInitialize() begin!\n"));
	if( m_pCaptureDriver )
	{
		m_pCaptureDriver->bCapDisable();

		m_pCaptureDriver->vCapRelease();
		delete m_pCaptureDriver;
		m_pCaptureDriver = NULL;
	}

	if(m_pCaptureBufArray)
	{
		m_pCaptureBufArray->release();
		m_pCaptureBufArray = NULL;
	}
	DBG_MSG(("CVideoCaptureThread::unInitialize() end!\n"));
}

TRC_SCOPE_DEF(CCaptureThread, CCaptureThread, initialize_capture);
bool CCaptureThread::initialize_capture(void* pConfig, ECapDriverType eDriverType)
{
	TRC_SCOPE(CCaptureThread, CCaptureThread, initialize_capture);

	switch(eDriverType)
	{
	case eQNX_IMX6_7182:
		//m_pCapDriver = new CQNXCapDriver7182();
		DBG_MSG(("initialize capture type = eQNX_IMX6_7182\n"));
		break;
	case eQNX_J5:
		m_pCaptureDriver = new CQNXCaptureDriver();
		DBG_MSG(("initialize capture type = eQNX_J5\n"));
		break;
	default:
		break;
	}
	if(m_pCaptureDriver == NULL)
		return FALSE;

	if(!m_pCaptureDriver->bCapInit(pConfig))
	{
		DBG_ERROR(("Capture init failed!\n"));
		return FALSE;
	}

	if( m_pCaptureBufArray )
	{
		m_pCaptureDriver->bSetCapBuffer((void**)(m_pCaptureBufArray->getVirtualAddr()),
				m_pCaptureBufArray->getBufferNum(),
				m_pCaptureBufArray->getWidth(),
				m_pCaptureBufArray->getHeight(),
				m_pCaptureBufArray->getStride());

	}
	else
	{
		DBG_ERROR(("Error: Please create capture buffer before!\n"));
		return FALSE;
	}


	return TRUE;
}

