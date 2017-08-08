
#ifdef LINUX_OS
#include "../include/CEvent.h"
#else
#include "..\include\CEvent.h"
#endif

#ifndef WIN_OS

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

CEvent::CEvent()
    : m_bAuto(FALSE)
    , m_bState(TRUE)
    , m_onPauseFunc(NULL)
{
    //unique_lock<mutex>lock(m_mutex,defer_lock);
    // lock.unlock();
    ALOGD("CEvent::CEvent created\n");
}

CEvent::CEvent(BOOLEAN autoReset, CEVENTCALLBACK func,VOID* pCBPara)
    : m_bAuto(autoReset)
    , m_bState(TRUE)
    , m_onPauseFunc(func)
    , m_CallBackPara(pCBPara)
{
    //unique_lock<mutex>lock(m_mutex,defer_lock);
    // lock.unlock();
    ALOGD("CEvent created\n");
}

CEvent::CEvent(BOOLEAN autoReset,string sEventOwner)
    : m_bAuto(autoReset)
    , m_bState(TRUE)
    , m_onPauseFunc(NULL)
    , m_sEventOwner(sEventOwner)
{
    ALOGD("CEvent default created\n");
}

CEvent::~CEvent()
{
    ALOGD("CEvent release\n");
}

VOID CEvent::wait()
{
#ifdef QNX_OS
    pthread_mutex_lock(&m_mutex);
#endif
#ifdef LINUX_OS
    unique_lock<mutex>lockevent(m_mutex);
#endif
    //lock.unlock();
    //PDCC_LOG_INFO("CEvent::CEvent wait start\n");


    while (!m_bState)
    {
        ALOGI("wait start\n");
        if(m_onPauseFunc) {
            ALOGI("wait call back!!\n");
            m_onPauseFunc(m_CallBackPara);   
        }
#ifdef QNX_OS
        pthread_cond_wait(&m_cond, &m_mutex);
#endif
#ifdef LINUX_OS
        m_cond.wait(lockevent);
#endif
    }




    if( m_bAuto )
        m_bState = FALSE;
#ifdef QNX_OS
    pthread_mutex_unlock(&m_mutex);
#endif
#ifdef LINUX_OS
    lockevent.unlock();
#endif

    //PDCC_LOG_INFO("CEvent::wait end\n");
}

BOOLEAN CEvent::wait(long milliseconds)
{
    ALOGI("wait for x ms is not implement\n");
    return FALSE;
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // WIN_OS