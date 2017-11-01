
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_PLATFORMDEF_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_PLATFORMDEF_H__

#include <stdio.h>
#include <queue>
#include <string>

using namespace std;

/******************************WIN_OS**********************************************/
//#define WIN_OS
//#define LINUX_OS
//#define QNX_OS
#ifdef WIN_OS
//#ifdef _cplusplus
//extern "C" {
//#endif
#include "..\..\..\003_OpenSrc\poco-1.7.8\Foundation\include\Poco\thread.h"
#include "..\..\..\003_OpenSrc\poco-1.7.8\Foundation\include\Poco\Event.h"
//#ifdef _cplusplus
//}
//#endif
#define APP_OS_TYPE "WIN_OS"
#endif

/******************************QNX_OS**********************************************/
#ifdef QNX_OS
#include <stdio.h>
#include <stdlib.h>
#include <sys/neutrino.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

#define APP_OS_TYPE "QNX_OS"
#endif

/******************************LINUX_OS**********************************************/
#ifdef LINUX_OS
#include <thread>
#include <condition_variable>
#include <mutex>

#define APP_OS_TYPE "LINUX_OS"
#endif

/******************************UNKNOWN_OS**********************************************/
#ifndef  APP_OS_TYPE
#define  APP_OS_TYPE  "UNKNOWN_OS"
#endif

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

#define PRINT_APP_OS_TYPE printf("Current OS is : %s\n", APP_OS_TYPE)

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_PLATFORMDEF_H__