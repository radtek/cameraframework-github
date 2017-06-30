#ifndef _CEVENTIMPL_H
#define _CEVENTIMPL_H

#include <condition_variable>
#include <mutex>
#include "TraceMacros.h"
using namespace std;
class CEvent
{
public:
	typedef void (*CALLBACK)(void*);

	CEvent();
	CEvent(bool autoReset,string sEventOwner = "EventNameNULL");
    CEvent(bool autoReset, CALLBACK func,void* pCBPara);
	~CEvent();
	void set();
	void wait();
	bool wait(long milliseconds);
	void reset();
	void setAutoWait(bool autoReset=true) {m_bAuto=autoReset;}; 
	void setOwner(std::string  sEventOwner) {m_sEventOwner = sEventOwner;};
private:
	bool            m_bAuto;
	volatile bool   m_bState;
	std::mutex m_mutex;
	std::condition_variable  m_cond;
	CALLBACK		m_onPauseFunc;
	std::string  m_sEventOwner;
	void* m_CallBackPara;
};


//
// inlines
//
inline void CEvent::set()
{
	PDCC_LOG_INFO("CEvent::set by %s\n",m_sEventOwner.c_str());
    unique_lock<std::mutex>lockset(m_mutex);
	m_bState = true;
	lockset.unlock();
	m_cond.notify_one();
}


inline void CEvent::reset()
{
	PDCC_LOG_INFO("CEvent::reset by %s\n",m_sEventOwner.c_str());
    unique_lock<std::mutex>lockreset(m_mutex);
	m_bState = false;
	lockreset.unlock();
	PDCC_LOG_INFO("CEvent::reset end\n");
}


#endif

