
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
        ALOGD("CEvent default created\n");
    }

    CEvent(BOOLEAN autoReset, string sEventOwner = "EventNameNULL")
        : m_bAuto(autoReset)
        , m_bState(TRUE)
        , m_onPauseFunc(NULL)
        , m_sEventOwner(sEventOwner)
    {
        ALOGD("CEvent eventOwner created\n");
    }

    CEvent(BOOLEAN autoReset, CEVENTCALLBACK func, VOID* pCBPara)
        : m_bAuto(autoReset)
        , m_bState(TRUE)
        , m_onPauseFunc(func)
        , m_CallBackPara(pCBPara)
    {
        ALOGD("CEvent callback created\n");
    }

    ~CEvent()
    {
        ALOGD("CEvent delete\n");
    }

    VOID set() {
        ALOGI("Thread restart by %s\n",m_sEventOwner.c_str());
    #ifdef QNX_OS
        if (pthread_mutex_lock(&m_mutex))
            return;
        m_bState = TRUE;
        if (pthread_cond_broadcast(&m_cond))
        {
            pthread_mutex_unlock(&m_mutex);
            return;
        }
        pthread_mutex_unlock(&m_mutex);
    #endif
    #ifdef LINUX_OS
        std::unique_lock<mutex>lockset(m_mutex);
        m_bState = TRUE;
        m_cond.notify_one();
    #endif
    }

    VOID reset() {
        ALOGI("Thread paused by %s\n",m_sEventOwner.c_str());
    #ifdef QNX_OS
        if (pthread_mutex_lock(&m_mutex))
            ;//throw SystemException("cannot reset event");
        m_bState = FALSE;
        pthread_mutex_unlock(&m_mutex);
    #endif
    #ifdef LINUX_OS
        std::unique_lock<mutex>lockreset(m_mutex);
        m_bState = FALSE;
    #endif
    }

    VOID wait()
    {
        #ifdef QNX_OS
        pthread_mutex_lock(&m_mutex);
    #endif
    #ifdef LINUX_OS
        unique_lock<mutex>lockevent(m_mutex);
    #endif

        while (!m_bState)
        {
            ALOGI("Thread waiting ......\n");
            if(m_onPauseFunc) {
                ALOGI("Thread call callbackFun!!\n");
                m_onPauseFunc(m_CallBackPara);
            }
        #ifdef QNX_OS
            pthread_cond_wait(&m_cond, &m_mutex);
        #endif
        #ifdef LINUX_OS
            m_cond.wait(lockevent);
        #endif
        }

        if(m_bAuto) {
            m_bState = FALSE;
        }

    #ifdef QNX_OS
        pthread_mutex_unlock(&m_mutex);
    #endif
    }

    BOOLEAN wait(long milliseconds)
    {
        ALOGE(" \"BOOLEAN wait(long milliseconds)\" not implement\n");
        return FALSE;
    }

    VOID setAutoWait(BOOLEAN autoReset=TRUE) {m_bAuto = autoReset;};
    VOID setOwner(string  sEventOwner) {m_sEventOwner = sEventOwner;};

private:
    volatile BOOLEAN m_bAuto;
    volatile BOOLEAN m_bState;

    CEVENTCALLBACK m_onPauseFunc;
    string  m_sEventOwner;
    VOID* m_CallBackPara;

#ifdef QNX_OS
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
#endif
#ifdef LINUX_OS
    mutex m_mutex;
    condition_variable  m_cond;
#endif
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CEVENT_H__
#endif // WIN_OS