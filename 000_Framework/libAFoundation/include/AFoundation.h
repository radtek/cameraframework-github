
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_AFOUNDATION_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_AFOUNDATION_H__

#include "TypeDefine.h"
#include "platformdef.h"
#include "CEvent.h"
#include "MessageForQueue.h"
#include "CMessageHandler.h"
#include "CRunableBase.h"
#include "CMQRunnableService.h"
#include "TraceMacros.h"
#include "CTimer.h"
#include "Epoller.h"
#include "ThreadPool.h"
#ifndef _UBUNTU_
#include "EpollGPIO.h"
#include "NanoIPC.h"
#endif
#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_AFOUNDATION_H__