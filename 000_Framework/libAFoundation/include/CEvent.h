
#ifndef WIN_OS
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CEVENT_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CEVENT_H__

#include "TypeDefine.h"
#include "platformdef.h"
#include "TraceMacros.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class CEvent
{
public:
    typedef VOID (*CEVENTCALLBACK)(VOID*);

    CEvent();
    CEvent(BOOLEAN autoReset, string sEventOwner = "EventNameNULL");
    CEvent(BOOLEAN autoReset, CEVENTCALLBACK func, VOID* pCBPara);
    ~CEvent();
    VOID set();
    VOID wait();
    BOOLEAN wait(long milliseconds);
    VOID reset();
    VOID setAutoWait(BOOLEAN autoReset=TRUE) {m_bAuto = autoReset;};
    VOID setOwner(string  sEventOwner) {m_sEventOwner = sEventOwner;};

private:
    BOOLEAN            m_bAuto;
    volatile BOOLEAN   m_bState;
#ifdef QNX_OS
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
#endif
#ifdef LINUX_OS
    mutex m_mutex;
    condition_variable  m_cond;
#endif
    CEVENTCALLBACK        m_onPauseFunc;
    string  m_sEventOwner;
    VOID* m_CallBackPara;
};

// inlines
inline VOID CEvent::set()
{
    ALOGI("set by %s\n",m_sEventOwner.c_str());
#ifdef QNX_OS
    if (pthread_mutex_lock(&m_mutex))
        return;
        //throw SystemException("cannot signal event (lock)");
    m_bState = TRUE;
    if (pthread_cond_broadcast(&m_cond))
    {
        pthread_mutex_unlock(&m_mutex);
        //throw SystemException("cannot signal event");
        return;
    }
    pthread_mutex_unlock(&m_mutex);
#endif
#ifdef LINUX_OS
    std::unique_lock<mutex>lockset(m_mutex);
    m_bState = TRUE;
    lockset.unlock();
    m_cond.notify_one();
#endif
}

// inlines
inline VOID CEvent::reset()
{
    ALOGI("reset by %s\n",m_sEventOwner.c_str());
#ifdef QNX_OS
    if (pthread_mutex_lock(&m_mutex))
        ;//throw SystemException("cannot reset event");
    m_bState = FALSE;
    pthread_mutex_unlock(&m_mutex);
#endif
#ifdef LINUX_OS
    std::unique_lock<mutex>lockreset(m_mutex);
    m_bState = FALSE;
    lockreset.unlock();
#endif
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CEVENT_H__
#endif // WIN_OS