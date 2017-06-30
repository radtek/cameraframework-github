#include "CTimer.h"
TRC_SCOPE_DEF(ADAS, CTimer, timer_thread_callback);
void timer_thread_callback (sigval arg)
{
	CTimer* pTimer = (CTimer*)(arg.sival_ptr);
	if( pTimer )
	{
		TRC_SCOPE(ADAS, CTimer, timer_thread_callback);
		DBG_MSG(("timer_thread_callback\n"));
		pTimer->onCallback();
	}
}

//---------------------------------------------------------
	CTimer::CTimer()
		: m_pTimerFunctor(NULL)
		, m_pCompleteFunctor(NULL)
		, m_uiDelay(0)
		, m_uiRepeatCount(0)
		, m_uiCurrentCount(0)
		, m_bRunning(FALSE)
		, m_uiInterval(0)
		, m_timerId(-1)
	{
		;
	}

	CTimer::CTimer(UInt32 uiDelay, UInt32 uiRepeatCount)
		: m_pTimerFunctor(NULL)
		, m_pCompleteFunctor(NULL)
		, m_uiDelay(uiDelay)
		, m_uiRepeatCount(uiRepeatCount)
		, m_uiCurrentCount(0)
		, m_bRunning(FALSE)
		, m_uiInterval(0)
		, m_timerId(-1)
	{
		;
	}

	CTimer::~CTimer()
	{
		stop();

		if(m_pTimerFunctor)
		{
			m_pTimerFunctor->release();
			m_pTimerFunctor = NULL;
		}

		if(m_pCompleteFunctor)
		{
			m_pCompleteFunctor->release();
			m_pCompleteFunctor = NULL;
		}
	}

	void CTimer::setDelay(UInt32 uiPeriod_ms)
	{
		m_uiDelay = uiPeriod_ms;
	}

	void CTimer::setRepeatCount(UInt32 uiValue)
	{
		m_uiRepeatCount = uiValue;
		m_uiCurrentCount = 0;

		m_bLoop = (m_uiRepeatCount != 1);
	}

	void CTimer::reset()
	{
		m_uiCurrentCount = 0;
		m_uiInterval = 0;
	}
	TRC_SCOPE_DEF(ADAS, CTimer, start);
	void CTimer::start()
	{
		TRC_SCOPE(ADAS, CTimer, start);
		if (m_bRunning == FALSE)
		{
			m_bRunning = TRUE;
			m_uiInterval = 0;

			createTimer();

			setTimer(m_uiDelay, m_bLoop);

			DBG_MSG(("CTimer::start m_timerId=%d\n",m_timerId));
		}
		else
		{
			m_uiInterval = 0;
		}
	}
	TRC_SCOPE_DEF(ADAS, CTimer, stop);
	void CTimer::stop()
	{
		TRC_SCOPE(ADAS, CTimer, stop);
		if( m_bRunning )
		{
			DBG_MSG(("CTimer::stop setTimer 0 m_timerId=%d\n",m_timerId));
			m_bRunning = FALSE;

			m_uiInterval = 0;
			setTimer(0);
		}
	}
	TRC_SCOPE_DEF(ADAS, CTimer, onCallback);
	void CTimer::onCallback()
	{
		TRC_SCOPE(ADAS, CTimer, onCallback);
		if (!m_bRunning)
		{
			DBG_ERROR(("CTimer::onCallback() m_bRunning false\n"));
			return;
		}

		m_uiCurrentCount++;

		if (m_uiRepeatCount == 0)	// LOOP
		{
			if( m_pTimerFunctor )
			{
				(*m_pTimerFunctor)(this,0,TS_TIMER);
			}
		}
		else
		{
			if (m_uiCurrentCount < m_uiRepeatCount)
			{
				if( m_pTimerFunctor )
				{
					(*m_pTimerFunctor)(this,m_uiCurrentCount,TS_TIMER);
				}
			}
			else if (m_uiCurrentCount == m_uiRepeatCount)
			{
				if( m_pCompleteFunctor )
				{
					(*m_pCompleteFunctor)(this,m_uiCurrentCount,TS_TIMER_COMPLETE);
				}
				m_bRunning = FALSE;

				m_uiInterval = 0;

				m_uiCurrentCount = 0;

				setTimer(0);
				DBG_MSG(("CTimer::onCallback setTimer 0 m_timerId=%d\n",m_timerId));
			}
			else
			{
				m_bRunning = FALSE;
				m_uiInterval = 0;

				m_uiCurrentCount = 0;
			}
		}
	}
	TRC_SCOPE_DEF(ADAS, CTimer, createTimer);
	BOOLEAN CTimer::createTimer()
	{
		TRC_SCOPE(ADAS, CTimer, createTimer);
		if( m_timerId != -1)
			return TRUE;

		struct sigevent se;

		/*
		* Set the sigevent structure to cause the signal to be
		* delivered by creating a new thread.
		*/
		se.sigev_notify            = SIGEV_THREAD;
		se.sigev_value.sival_ptr   = (void*)this;
		se.sigev_notify_function   = timer_thread_callback;
		se.sigev_notify_attributes = NULL;


		Int32 status = timer_create(CLOCK_MONOTONIC, &se, &m_timerId);
		
		DBG_MSG(("Creating timer %d\n",m_timerId));
		if (status == -1)
		{
			DBG_MSG(("Create timer error\n"));
			return FALSE;
		}
		return TRUE;
	}

	TRC_SCOPE_DEF(ADAS, CTimer, destroyTimer);
	void CTimer::destroyTimer()
	{
		TRC_SCOPE(ADAS, CTimer, destroyTimer);
		if( m_timerId != -1 )
		{
			timer_delete(m_timerId);
			DBG_MSG(("CTimer::destroyTimer %d\n",m_timerId));
			m_timerId = -1;
		}
	}

	BOOLEAN	CTimer::checkTimerRunning()
	{
		if( m_timerId == -1)
			return FALSE;

		struct itimerspec curr_value;

		timer_gettime(m_timerId, &curr_value);

		if( m_bLoop )
		{
			if ( curr_value.it_interval.tv_nsec > 0 || curr_value.it_interval.tv_sec > 0 )
				return TRUE;
		}
		else
		{
			if ( curr_value.it_value.tv_nsec > 0 || curr_value.it_value.tv_sec > 0 )
				return TRUE;
		}

		return FALSE;
	}
	TRC_SCOPE_DEF(ADAS, CTimer, setTimer);
	void CTimer::setTimer(UInt32 uiPeriod_ms, BOOLEAN bLoop)
	{
		TRC_SCOPE(ADAS, CTimer, setTimer);
		if( m_timerId == -1)
			return;

		Int32 status = 0;
		   struct itimerspec ts;
		   /*
		   * Specify a repeating timer that fires each 5 seconds.
		   */
		   ts.it_value.tv_sec     = uiPeriod_ms/1000;
		   ts.it_value.tv_nsec    = (uiPeriod_ms%1000)*1000000;

		   if(!bLoop )
		   {
		    ts.it_interval.tv_sec  = 0;
		    ts.it_interval.tv_nsec = 0;
		   }
		   else
		   {
		    ts.it_interval.tv_sec  = ts.it_value.tv_sec;
		    ts.it_interval.tv_nsec = ts.it_value.tv_nsec;
		   }

		   status = timer_settime(m_timerId, 0, &ts, 0);
		   DBG_MSG(("CTimer::setTimer m_timerId=%d,ts.it_value.tv_sec=%d,ts.it_value.tv_nsec=%d\n",
		   	m_timerId,ts.it_value.tv_sec,ts.it_value.tv_nsec));
		   if (status == -1)
			   DBG_MSG(("set Timer error\n"));
	}
