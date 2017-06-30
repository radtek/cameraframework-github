#ifndef _ADAS_CRUNNABLE_H_
#define _ADAS_CRUNNABLE_H_

#ifdef PLATFORM_QNX
#include "Poco/Runnable.h"
using Poco::Runnable;
typedef Runnable	IRunnable;
#endif

#ifdef PLATFORM_WIN
#include "./windows/IRunnable.h"
#endif

#endif /* _CRUNNABLE_H_ */

