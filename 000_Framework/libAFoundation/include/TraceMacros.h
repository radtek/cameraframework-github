
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_TRACEMACROS_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_TRACEMACROS_H__

#include <thread>
#include "TypeDefine.h"

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <sys/syscall.h>
#include <stdarg.h>

#ifndef _UBUNTU_
#include <dlt/dlt.h>
#endif


//#include "../../ParkAssistSrv_Common/CommonCore.hpp"

#define PAM_LOG_INFO(B,...)          LOG_INFO(LOG_PDC,B, ## __VA_ARGS__)
#define PAM_LOG_DEBUG(B,...)         LOG_DEBUG(LOG_PDC,B, ## __VA_ARGS__)
#define PAM_LOG_WARNING(B,...)       LOG_WARNING(LOG_PDC,B, ## __VA_ARGS__)
#define PAM_LOG_ERROR(B,...)         LOG_ERROR(LOG_PDC,B, ## __VA_ARGS__)

#define PDCA_LOG_INFO(B,...)          LOG_INFO(LOG_PDC,B, ## __VA_ARGS__)
#define PDCL_LOG_INFO(B,...)          LOG_INFO(LOG_PDC,B, ## __VA_ARGS__)
#define PDCC_LOG_INFO(B,...)          LOG_INFO(LOG_PDC,B, ## __VA_ARGS__)


#ifdef  PAM_LOG_INFO
    #undef  PAM_LOG_INFO
#endif
#ifdef    PAM_LOG_DEBUG
    #undef  PAM_LOG_DEBUG
#endif
#ifdef    PAM_LOG_WARNING
    #undef  PAM_LOG_WARNING
#endif
#ifdef    PAM_LOG_ERROR
    #undef  PAM_LOG_ERROR
#endif
#ifdef    PDCA_LOG_INFO
    #undef  PDCA_LOG_INFO
#endif
#ifdef    PDCL_LOG_INFO
    #undef  PDCL_LOG_INFO
#endif
#ifdef    PDCC_LOG_INFO
    #undef  PDCC_LOG_INFO
#endif

#define PAM_LOG_INFO(B,...)            printf(B, ## __VA_ARGS__)
#define PAM_LOG_DEBUG(B,...)           printf(B, ## __VA_ARGS__)
#define PAM_LOG_WARNING(B,...)         printf(B, ## __VA_ARGS__)
#define PAM_LOG_ERROR(B,...)           printf(B, ## __VA_ARGS__)

#define PDCA_LOG_INFO(B,...)           printf(B, ## __VA_ARGS__)
#define PDCL_LOG_INFO(B,...)           printf(B, ## __VA_ARGS__)
#define PDCC_LOG_INFO(B,...)           printf(B, ## __VA_ARGS__)



//============================================================

#ifndef _UBUNTU_
#define DLTLOG
#endif

//#define CASECLIENT_LOG
#ifdef DLTLOG

#define AAP_SERVICE_LOG_TAG "adas"

#define PRINTINIT \
        DLT_REGISTER_APP("adas", "ADASService"); \


#define PRINTDEINIT \
        DLT_UNREGISTER_APP();

static void printMessages(DltLogLevelType type, const char *func, int line, const char *msgType, const char *format, ... )
{
    DLT_DECLARE_CONTEXT(DLT_AAContext);
    DLT_REGISTER_CONTEXT(DLT_AAContext, "MAIN", "ADAS_Service");
    do {
      char buffer[2056]; //Max 4096 bytes can be routed more than this would cause a crash.
      char tmpbuf[1024];
      {
        va_list args;
        va_start (args, format);
        vsnprintf (tmpbuf, sizeof (tmpbuf), format, args);
        va_end (args);
      }
      snprintf (buffer, sizeof (buffer), "%s [%s:%d:%s] : %s", AAP_SERVICE_LOG_TAG, func, line, msgType, tmpbuf);
      DLT_LOG (DLT_AAContext, type, DLT_STRING(buffer));
    }while(0);

    DLT_UNREGISTER_CONTEXT(DLT_AAContext);
}

#define ALOGV(format, args...)   \
    do {        \
        printMessages(DLT_LOG_VERBOSE,  __func__, __LINE__, "Dbg1", format, ##args);    \
    }while(0)

#define ALOGI(format, args...)   \
    do {    \
        printMessages(DLT_LOG_INFO, __func__, __LINE__, "Info", format, ##args);    \
    }while(0)

#define ALOGD(format, args...)   \
    do {        \
        printMessages(DLT_LOG_DEBUG , __func__, __LINE__, "Dbg", format, ##args);    \
    }while(0)

#define ALOGW(format, args...)   \
    do {        \
        printMessages(DLT_LOG_WARN, __func__, __LINE__, "Warning", format, ##args);    \
    }while(0)

#define ALOGE(format, args...)   \
    do {        \
        printMessages(DLT_LOG_ERROR,  __func__, __LINE__, "Error", format, ##args);    \
    }while(0)


 //DLTLOG


/********************Log Level(Just define one of them)********************************
 * #define DEBUG:   debug log info,     include *DEBUG*   *WARNING* *INFO*  *ERROR* log
 * #define WARNING: warning log info,   include *WARNING* *INFO*    *ERROR*         log
 * #define INFO:    key point log info, include *INFO*    *ERROR*                   log
 * #define ERROR:   error log info,     include *ERROR*                             log
 **************************************************************************************/
#else

    #ifndef    DEBUG
    #define DEBUG
    #endif
    //#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)  std::this_thread::get_id()

    static UInt64 GetTickCount()
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    }

    #ifndef ALOGD
        #ifdef DEBUG
            #define WARNING
            #define ALOGD(fmt, ...)\
                fprintf(stdout, "DBUG:[%lu]:[%s]:[%d]:[%ld]: " fmt, GetTickCount(), __FUNCTION__, __LINE__, (long int)syscall(__NR_gettid), ##__VA_ARGS__);
        #else
            #define ALOGD(fmt, ...) ((void)0)
        #endif //#ifdef DEBUG
    #endif //#ifndef ALOGD

    #ifndef ALOGW   // color : yellow
        #ifdef WARNING
            #define INFO
            #define ALOGW(fmt, ...)\
                fprintf(stdout, "\033[33mWARNING\033[0m:[%lu]:[%s]:[%d]:[%ld]: " fmt, GetTickCount(), __FUNCTION__, __LINE__, (long int)syscall(__NR_gettid), ##__VA_ARGS__);
        #else
            #define ALOGW(fmt, ...) ((void)0)
        #endif //#ifdef WARNING
    #endif //#ifndef ALOGW

    #ifndef ALOGI
        #ifdef INFO
            #define ERROR
            #define ALOGI(fmt, ...)\
                fprintf(stdout, "INFO:[%lu]:[%s]:[%d]:[%ld]: " fmt, GetTickCount(), __FUNCTION__, __LINE__, (long int)syscall(__NR_gettid), ##__VA_ARGS__);
        #else
            #define ALOGI(fmt, ...) ((void)0)
        #endif //#ifdef INFO
    #endif //#ifndef ALOGI

    #ifndef ALOGE // color : red
        #ifdef ERROR
            #define ALOGE(fmt, ...)\
                fprintf(stderr, "\033[31mERROR\033[0m:[%lu]:[%s]:[%d]:[%ld]: " fmt, GetTickCount(), __FUNCTION__, __LINE__, (long int)syscall(__NR_gettid), ##__VA_ARGS__);
        #else
            #define ALOGE(fmt, ...) ((void)0)
        #endif //#ifdef ERROR
    #endif //#ifndef ALOGE

#endif


#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_TRACEMACROS_H__



// 简单的说就是ESC[*m，ESC的八进制为\033，*可以是多个属性的组合，用分号隔开。

// 例：
// #include
// int main()
// {
//     printf("\033[31mThis is RED.\n\033[0m");
//     return 0;
// }
// 31m代表字体为红色，0m代表关闭所有属性。

// 常用的ANSI控制码如下（有些不支持）：
// \033[0m 关闭所有属性
// \033[1m 高亮
// \033[2m 亮度减半
// \033[3m 斜体
// \033[4m 下划线
// \033[5m 闪烁
// \033[6m 快闪
// \033[7m 反显
// \033[8m 消隐
// \033[9m 中间一道横线
// 10-19 关于字体的
// 21-29 基本与1-9正好相反
// 30-37 设置前景色
// 40-47 设置背景色
// 30:黑
// 31:红
// 32:绿
// 33:黄
// 34:蓝色
// 35:紫色
// 36:深绿
// 37:白色
// 38 打开下划线,设置默认前景色
// 39 关闭下划线,设置默认前景色
// 40 黑色背景
// 41 红色背景
// 42 绿色背景
// 43 棕色背景
// 44 蓝色背景
// 45 品红背景
// 46 孔雀蓝背景
// 47 白色背景
// 48 不知道什么东西
// 49 设置默认背景色
// 50-89 没用
// 90-109 又是设置前景背景的，比之前的颜色浅
// \033[nA 光标上移n行
// \033[nB 光标下移n行
// \033[nC 光标右移n行
// \033[nD 光标左移n行
// \033[y;xH设置光标位置
// \033[2J 清屏
// \033[K 清除从光标到行尾的内容
// \033[s 保存光标位置
// \033[u 恢复光标位置
// \033[?25l 隐藏光标
// \033[?25h 显示光标