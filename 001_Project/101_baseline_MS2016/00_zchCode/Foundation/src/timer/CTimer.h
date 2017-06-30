
#ifndef __CTIMER_H_INCLUDED__
#define __CTIMER_H_INCLUDED__

#include "common.h"


	class CTimer
	{
	public:// const define

	private:// const define

	public:// embed class or struct or enum
		enum ETimerStatus
		{
			TS_TIMER = 0,
			TS_TIMER_COMPLETE,
		};

		typedef CFunctorArg3<CTimer*, UInt32, ETimerStatus>	CFunctor;

	private:// embed class or struct or enum
		friend class CTimerManager;

	public:// method

		CTimer();
		CTimer(UInt32 uiDelay, UInt32 uiRepeatCount = 0);
		virtual ~CTimer();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		* @brief	Set a listener to response to the timer event.
		*
		* @param	pListener	A class implemented ITimerListener to response to the timer event.
		*/
		void	setCallBack(CFunctor *pCompleteFunctor, CFunctor* pTimerFunctor = NULL)
		{
			//m_pListener = pListener;
			m_pCompleteFunctor = pCompleteFunctor;
			m_pTimerFunctor	= pTimerFunctor;
		}

		/**
		* @brief	Set delay time to the timer.
		*
		* @param	uiValue	The unit is millisecond.
		*/
		void	setDelay(UInt32 uiPeriod_ms);

		UInt32	getDelay() const		{ return m_uiDelay; }

		/**
		* @brief	Set repeat count to the timer.
		*
		* @param	uiValue	If it is 0, the timer runs all the while.
		*/
		void	setRepeatCount(UInt32 uiValue);

		UInt32	getRepeatCount() const	{ return m_uiRepeatCount; }

		UInt32	getCurrentCount() const	{ return m_uiCurrentCount; }	

		BOOLEAN	isRunning() const		{ return m_bRunning; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		* Reset the timer, and the current count will be set to 0.
		*			
		*/
		void	reset();

		/**
		* Start the timer again from the last current count.
		*
		*/
		void	start();

		/**
		*  the timer without reseting current count to 0.
		*
		*/
		void	stop();
		void	onCallback();

	protected:// method
		CTimer(const CTimer&){}
		CTimer& operator =(const CTimer&){return *this;}

	private:// method
		
	protected:// property
		BOOLEAN		createTimer();
		void		destroyTimer();
		BOOLEAN		checkTimerRunning();
		void		setTimer(UInt32 uiPeriod_ms, BOOLEAN bLoop=FALSE);
		//void		stopTimer();
		
	private:// property
		CFunctor*		m_pTimerFunctor;
		CFunctor*		m_pCompleteFunctor;

		UInt32			m_uiDelay;
		UInt32			m_uiRepeatCount;
		UInt32			m_uiCurrentCount;
		BOOLEAN			m_bRunning;
		BOOLEAN			m_bLoop;
		UInt32			m_uiInterval;


		timer_t			m_timerId;
	};

#endif
