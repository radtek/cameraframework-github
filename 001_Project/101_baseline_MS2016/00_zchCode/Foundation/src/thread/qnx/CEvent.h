#ifndef _CEVENTIMPL_H
#define _CEVENTIMPL_H

#include <pthread.h>

class CEvent
{
public:
	typedef void (*CALLBACK)();

public:
	CEvent(bool autoReset, CALLBACK func=NULL);
	~CEvent();
	void set();
	void wait();
	bool wait(long milliseconds);
	void reset();

private:
	bool            m_bAuto;
	volatile bool   m_bState;
	pthread_mutex_t m_mutex;
	pthread_cond_t  m_cond;
	CALLBACK		m_onPauseFunc;
};


//
// inlines
//
inline void CEvent::set()
{
	if (pthread_mutex_lock(&m_mutex))
		return;
		//throw SystemException("cannot signal event (lock)");
	m_bState = true;
	if (pthread_cond_broadcast(&m_cond))
	{
		pthread_mutex_unlock(&m_mutex);
		//throw SystemException("cannot signal event");
		return;
	}
	pthread_mutex_unlock(&m_mutex);
}


inline void CEvent::reset()
{
	if (pthread_mutex_lock(&m_mutex))
		;//throw SystemException("cannot reset event");
	m_bState = false;
	pthread_mutex_unlock(&m_mutex);
}


#endif

