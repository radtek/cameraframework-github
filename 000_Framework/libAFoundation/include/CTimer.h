
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CTIMER_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CTIMER_H__

#include <time.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "TypeDefine.h"

using namespace std;

typedef union sigval TimeValue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class CTimer
{
public:
    typedef VOID (*CTimer_callback)(TimeValue v);

    CTimer(CTimer_callback onTimeout, Int32 value);

    CTimer(CTimer_callback onTimeout, VOID* value);

    VOID CTimer_setTime(Int32 seconds, Int32 milliseconds);

    VOID CTimer_clear();

    VOID CTimer_delete();

    ~CTimer() { CTimer_delete(); }

private:
    timer_t m_Timer;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // #ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_CTIMER_H__