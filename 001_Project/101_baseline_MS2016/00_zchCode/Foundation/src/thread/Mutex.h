#ifndef _ADAS_MUTEX_H
#define _ADAS_MUTEX_H

#ifdef PLATFORM_QNX
#include "Poco/Mutex.h"
using Poco::Mutex;
#endif

#ifdef PLATFORM_WIN
#include "./windows/Mutex.h"
#endif


#endif
