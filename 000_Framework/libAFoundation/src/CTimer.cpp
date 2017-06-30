
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "CTimer.h"
#include "TraceMacros.h"

#define CLOCKID CLOCK_MONOTONIC

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

CTimer::CTimer(CTimer_callback callback, Int32 value)
{
    struct sigevent evp;
    memset(&evp, 0, sizeof(struct sigevent));

    evp.sigev_value.sival_int = value;          //也是标识定时器的，这和timerid有什么区别？回调函数可以获得
    evp.sigev_notify = SIGEV_THREAD;            //线程通知的方式，派驻新线程
    evp.sigev_notify_function = callback;       //线程函数地址

#if 0
    if(timer_create(CLOCKID, &evp, &m_Timer) == -1)
    {
        ALOGE("fail to timer_create !!!\n");
    }
#endif	
}

CTimer::CTimer(CTimer_callback callback, VOID* value)
{
    struct sigevent evp;
    memset(&evp, 0, sizeof(struct sigevent));

    evp.sigev_value.sival_ptr = value;          //也是标识定时器的，这和timerid有什么区别？回调函数可以获得
    evp.sigev_notify = SIGEV_THREAD;            //线程通知的方式，派驻新线程
    evp.sigev_notify_function = callback;       //线程函数地址
#if 0
    if(timer_create(CLOCKID, &evp, &m_Timer) == -1)
    {
        ALOGE("fail to timer_create !!!\n");
    }
#endif
}

VOID CTimer::CTimer_setTime(Int32 seconds, Int32 milliseconds)
{
    struct itimerspec timeout;
    timeout.it_value.tv_sec = seconds;
    timeout.it_value.tv_nsec = milliseconds * 1000000L;  //NOTE: it's in nano seconds
    timeout.it_interval.tv_sec = 0;
    timeout.it_interval.tv_nsec = 0;
#if 0
    if(timer_settime(m_Timer, 0, &timeout, NULL))
        ALOGE("timer_settime error !!!\n");
#endif
}

VOID CTimer::CTimer_clear()
{
    struct itimerspec timeout;
    timeout.it_value.tv_sec = 0;
    timeout.it_value.tv_nsec = 0;  //NOTE: it's in nano seconds
    timeout.it_interval.tv_sec = 0;
    timeout.it_interval.tv_nsec = 0;
#if 0
    if(timer_settime(m_Timer, 0, &timeout, NULL))
        ALOGE("timer_settime error !!!\n");
#endif	
}

VOID CTimer::CTimer_delete()
{
#if 0
    if(timer_delete(m_Timer)) {
        ALOGE("timer_delete error !!!\n");
    }
#endif	
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman