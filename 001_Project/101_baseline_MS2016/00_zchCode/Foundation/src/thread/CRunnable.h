#ifndef _CRUNNABLE_QNX_H_
#define _CRUNNABLE_QNX_H_

#include "common.h"
#include "thread/Thread.h"
#include "thread/IRunnable.h"
#include "thread/CEvent.h"


class CRunnable : public IRunnable
{
public:
	CRunnable(const string& strName,CEvent::CALLBACK func);
	virtual ~CRunnable();

	//Thread APIs
	virtual void start();
	virtual void start(void* pData)	{;}
	virtual void quit();
	virtual void join();
	virtual void run();

	void	pause();
	void 	resume();

	BOOLEAN isQuit() const	{ return m_bQuit;	}

protected:
	virtual BOOLEAN initialize()	{ return TRUE; }
	virtual void 	unInitialize()	{}
	virtual void 	update() = 0;

protected:	// data

private:	// data
   //Thread
   Thread  			m_hThread;
   BOOLEAN		 	m_bQuit;
   CEvent	 		m_event;
   string			m_strThreadName;
};


#endif /* _CADAS_MANAGER_H_ */

