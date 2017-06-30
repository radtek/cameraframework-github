#ifndef _COMMON_H
#define _COMMON_H

#ifdef PLATFORM_QNX
#include <unistd.h>
#include <signal.h>
#endif

#include "common/ADASMarco.h"
#include "common/TypeDefine.h"
#include "common/CCRef.h"
#include "common/CFunctor.h"
#include "common/StringUtil.h"

#include "log/TraceMacros.h"

#include "thread/CEvent.h"
#include "thread/Mutex.h"
#include "thread/Thread.h"
#include "thread/IRunnable.h"

#include "math/C3DMatrix3.h"
#include "math/C3DMatrix4.h"
#include "math/C3DVector3.h"
#include "math/C3DVector4.h"
#include "math/CMath.h"
#include "math/C3DQuaternion.h"
#include "math/CRectangle.h"

#ifdef PLATFORM_QNX

inline UInt32 getTickCount()
{
	static struct timespec rt;
	//clock_gettime(CLOCK_REALTIME, &rt);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &rt);
	return rt.tv_sec * 1000 + rt.tv_nsec/1000000;
}

#endif

#endif
