#ifndef _ADAS_EVENT_H
#define _ADAS_EVENT_H

#ifdef PLATFORM_QNX
#include "./qnx/CEvent.h"
#endif

#ifdef PLATFORM_WIN
#include "./windows/CEvent.h"
#endif


#endif
