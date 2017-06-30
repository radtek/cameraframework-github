
#include "CEvent.h"

CEvent::CEvent()
: m_bAuto(false)
, m_bState(true)
, m_onPauseFunc(NULL)
{
	
	//unique_lock<mutex>lock(m_mutex,std::defer_lock);
   // lock.unlock();
    printf("CEvent::CEvent created\n");
}


CEvent::CEvent(bool autoReset, CALLBACK func,void* pCBPara)
: m_bAuto(autoReset)
, m_bState(true)
, m_onPauseFunc(func)
, m_CallBackPara(pCBPara)
{
	
	//unique_lock<mutex>lock(m_mutex,std::defer_lock);
   // lock.unlock();
    printf("CEvent::CEvent created\n");
}

CEvent::CEvent(bool autoReset,string sEventOwner)
: m_bAuto(autoReset)
, m_bState(true)
, m_onPauseFunc(NULL)
, m_sEventOwner(sEventOwner)
{
    printf("CEvent::CEvent default created\n");
}

CEvent::~CEvent()
{
	PDCC_LOG_INFO("CEvent::CEvent release\n");
}

void CEvent::wait()
{
    unique_lock<std::mutex>lockevent(m_mutex);
    //lock.unlock();
    //PDCC_LOG_INFO("CEvent::CEvent wait start\n");
	

	while (!m_bState)
	{
		PDCC_LOG_INFO("CEvent::wait start\n");
		if(m_onPauseFunc) {
		PDCC_LOG_INFO("CEvent::wait call back!!\n");
			m_onPauseFunc(m_CallBackPara);	}
		m_cond.wait(lockevent);
	}
	if( m_bAuto )
		m_bState = false;

	lockevent.unlock();
	//PDCC_LOG_INFO("CEvent::wait end\n");
}

bool CEvent::wait(long milliseconds)
{
	PDCC_LOG_INFO("CEvent::wait for x ms is not implement\n");
	return false;
}


