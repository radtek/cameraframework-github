
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_EPOLLER_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_EPOLLER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "TypeDefine.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

/**
 * @brief epoller操作类，已经默认采用了EPOLLET方式做触发
 */
class Epoller
{
public:

    /**
    * @brief 构造函数.
    *
    * @param bEt 默认是ET模式，当状态发生变化的时候才获得通知
    */
    Epoller(BOOLEAN bEt = TRUE)
        : m_iEpollFd(-1)
        , m_pPevs(nullptr)
        , m_bEt(bEt)
        , m_iMaxConnections(1024)
    {
    }

    /**
    * @brief 析够函数.
    */
    ~Epoller()
    {
        if(m_pPevs != NULL)
        {
            delete[] m_pPevs;
            m_pPevs = NULL;
        }

        if(m_iEpollFd > 0)
        {
            close(m_iEpollFd);
        }
    }

    /**
    * @brief 生成 epoll句柄.
    *
    * @param max_connections epoll服务需要支持的最大连接数
    */
    VOID Create(Int32 max_connections);

    /**
    * @brief 添加监听句柄.
    *
    * @param fd    句柄
    * @param data  辅助的数据, 可以后续在epoll_event中获取到
    * @param event 需要监听的事件EPOLLIN|EPOLLOUT
    *
    */
    VOID Add(Int32 fd, long long data, __uint32_t event);

    /**
    * @brief 修改句柄事件.
    *
    * @param fd    句柄
    * @param data  辅助的数据, 可以后续在epoll_event中获取到
    * @param event 需要监听的事件EPOLLIN|EPOLLOUT
    */
    VOID Mod(Int32 fd, long long data, __uint32_t event);

    /**
    * @brief 删除句柄事件.
    *
    * @param fd    句柄
    * @param data  辅助的数据, 可以后续在epoll_event中获取到
    * @param event 需要监听的事件EPOLLIN|EPOLLOUT
    */
    VOID Del(Int32 fd, long long data, __uint32_t event);

    /**
    * @brief 等待时间.
    *
    * @param millsecond 毫秒
    * @return Int32       有事件触发的句柄数
    */
    Int32 Wait(Int32 millsecond);

    /**
    * @brief 获取被触发的事件.
    *
    * @return struct epoll_event&被触发的事件
    */
    struct epoll_event& Get(Int32 i);

protected:

    /**
    * @brief 控制 epoll，将EPOLL设为边缘触发EPOLLET模式
    * @param fd    句柄，在create函数时被赋值
    * @param data  辅助的数据, 可以后续在epoll_event中获取到
    * @param event 需要监听的事件
    * @param op    EPOLL_CTL_ADD：注册新的 fd到epfd 中；
    *              EPOLL_CTL_MOD：修改已经注册的 fd的监听事件；
    *              EPOLL_CTL_DEL：从 epfd中删除一个fd；
    *
    */
    VOID Ctrl(Int32 fd, long long data, __uint32_t events, Int32 op);

protected:

    /**
    * epoll
    */
    Int32 m_iEpollFd;

    /**
    * 最大连接数
    */
    Int32 m_iMaxConnections;

    /*事件集
     * typedef union epoll_data
     * {
     *   void        *ptr;
     *   int          fd;
     *   __uint32_t   u32;
     *   __uint64_t   u64;
     * } epoll_data_t;
     *
     * struct epoll_event {
     * __uint32_t events; // Epoll events
     * epoll_data_t data; //User data variable
     * };
     */
    struct epoll_event *m_pPevs;

    /**
    * 是否是ET模式
    */
    BOOLEAN m_bEt;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_EPOLLER_H__