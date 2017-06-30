
#include "CEvent.h"



CEvent::CEvent(bool autoReset, CALLBACK func)
: m_bAuto(autoReset)
, m_bState(true)
, m_onPauseFunc(func)
{
	pthread_mutex_init(&m_mutex, NULL);
	//pthread_condattr_setclock(&m_condAttr, CLOCK_MONOTONIC);
	pthread_cond_init(&m_cond, NULL);
}

CEvent::~CEvent()
{
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
	//		pthread_condattr_destroy(&m_condAttr);
}

void CEvent::wait()
{
	pthread_mutex_lock(&m_mutex);

	while (!m_bState)
	{
		if(m_onPauseFunc)
			m_onPauseFunc();
		pthread_cond_wait(&m_cond, &m_mutex);
	}
	if( m_bAuto )
		m_bState = false;

	pthread_mutex_unlock(&m_mutex);
}

bool CEvent::wait(long milliseconds)
{
	return false;
}


