
#include "CRunnable.h"


CRunnable::CRunnable(const string& strName,CEvent::CALLBACK func)
: m_bQuit(FALSE)
, m_event(FALSE,func)
, m_strThreadName(strName)
{
	;
}

CRunnable::~CRunnable()
{
	;
}

TRC_SCOPE_DEF(CRunnable, CRunnable, run);
void CRunnable::run()
{
	TRC_SCOPE(CRunnable, CRunnable, run);
	//m_hThread.setName(m_strThreadName);
#ifdef PLATFORM_QNX
	pthread_setname_np(pthread_self(), m_strThreadName.c_str());
#endif
	DBG_MSG(("CRunnable::run thread id = %d  name = %s...start\n ", m_hThread.id(), m_strThreadName.c_str()));

	if( !initialize() )
	{
		DBG_MSG(("CRunnable::run initialize failed\n"));
		return;
	}

	while(!m_bQuit )
	{
		m_event.wait();
		update();
	}

	unInitialize();

	DBG_MSG(("CRunnable::run thread id = %d  name = %s...exit \n ", m_hThread.id(), m_strThreadName.c_str()));
	return;
}

void CRunnable::start()
{
	m_hThread.start(*this);
}

TRC_SCOPE_DEF(ADAS, CRunnable, quit);
void CRunnable::quit()
{
   TRC_SCOPE(ADAS, CRunnable, quit);
   DBG_MSG(("CRunnable::quit()\n"));
   m_event.set();
   m_bQuit = true;
}

void CRunnable::join()
{
   m_hThread.join();
}

void CRunnable::pause()
{
	m_event.reset();
}

void CRunnable::resume()
{
	m_event.set();
}

