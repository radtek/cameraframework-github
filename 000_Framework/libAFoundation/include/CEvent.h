
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

    CEvent()
        : m_bAuto(FALSE)
        , m_bState(TRUE)
        , m_onPauseFunc(NULL)
    {
        
    }

    CEvent(BOOLEAN autoReset, string sEventOwner = "EventNameNULL")
        : m_bAuto(autoReset)
        , m_bState(TRUE)
        , m_onPauseFunc(NULL)
        , m_sEventOwner(sEventOwner)
    {
        
    }

    CEvent(BOOLEAN autoReset, CEVENTCALLBACK func, VOID* pCBPara)
        : m_bAuto(autoReset)
        , m_bState(TRUE)
        , m_onPauseFunc(func)
        , m_CallBackPara(pCBPara)
    {
    }

    ~CEvent()
    {
    }

    VOID set() {
        ALOGI("Thread restart by %s\n",m_sEventOwner.c_str());
        std::unique_lock<mutex>lockset(m_mutex);
        m_bState = TRUE;
        m_cond.notify_one();
    }

    VOID reset() {
        ALOGI("Thread paused by %s\n",m_sEventOwner.c_str());
        std::unique_lock<mutex>lockreset(m_mutex);
        m_bState = FALSE;
    }

    VOID wait()
    {

        std::unique_lock<mutex>lockevent(m_mutex);

        while (!m_bState)
        {
            ALOGI("Thread waiting ......\n");
            if(m_onPauseFunc) {
                m_onPauseFunc(m_CallBackPara);
            }

            m_cond.wait(lockevent);
        }

        if(m_bAuto) {
            m_bState = FALSE;
        }
    }

    VOID setAutoWait(BOOLEAN autoReset=TRUE) {m_bAuto = autoReset;};
    VOID setOwner(string  sEventOwner) {m_sEventOwner = sEventOwner;};

private:
    volatile BOOLEAN m_bAuto;
    volatile BOOLEAN m_bState;

    CEVENTCALLBACK m_onPauseFunc;
    string  m_sEventOwner;
    VOID* m_CallBackPara;

    mutex m_mutex;
    condition_variable  m_cond;

};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CEVENT_H__
#endif // WIN_OS