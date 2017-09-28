
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "Epoller.h"
#include "TraceMacros.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

VOID Epoller::Create(Int32 max_connections)
{
    m_iMaxConnections = max_connections;

    // int epoll_create(int size);
    // 创建一个epoll的句柄，size用来告诉内核需要监听的数目一共有多大。当创建好epoll句柄后，
    // 它就是会占用一个fd值，在linux下如果查看/proc/进程id/fd/，是能够看到这个fd的，
    // 所以在使用完epoll后，必须调用close() 关闭，否则可能导致fd被耗尽。
    m_iEpollFd = epoll_create(m_iMaxConnections + 1);

    if(m_pEvents != NULL)
    {
        delete[] m_pEvents;
    }

    m_pEvents = new epoll_event[m_iMaxConnections + 1];
}

VOID Epoller::Add(Int32 fd, long long data, __uint32_t event)
{
    Ctrl(fd, data, event, EPOLL_CTL_ADD);
}

VOID Epoller::Mod(Int32 fd, long long data, __uint32_t event)
{
    Ctrl(fd, data, event, EPOLL_CTL_MOD);
}

VOID Epoller::Del(Int32 fd, long long data, __uint32_t event)
{
    Ctrl(fd, data, event, EPOLL_CTL_DEL);
}

Int32 Epoller::Wait(Int32 millsecond)
{
    /*
     *  int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
     *  参数events用来从内核得到事件的集合，maxevents 告之内核这个events有多大，
     *  这个 maxevents 的值不能大于创建 epoll_create() 时的size，
     *  参数 timeout 是超时时间（毫秒，0会立即返回，-1将不确定，也有说法说是永久阻塞）,
     *  该函数返回需要处理的事件数目，如返回0表示已超时。
     */
    return epoll_wait(m_iEpollFd , m_pEvents , m_iMaxConnections + 1, millsecond);
}

struct epoll_event& Epoller::Get(Int32 i)
{
    assert(m_pEvents != 0);
    return m_pEvents[i];
}

VOID Epoller::Ctrl(Int32 fd, long long data, __uint32_t events, Int32 op)
{
    struct epoll_event ev;
    //ev.data.u64 = data;
    if(m_bEt) {
        ev.events = events | EPOLLET ;
    } else {
        ev.events = events;
    }
    ev.data.fd = fd;

    /*
     *  int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
     *  epoll的事件注册函数，第一个参数是 epoll_create() 的返回值，
     *  第二个参数表示动作:
     *    EPOLL_CTL_ADD    注册新的fd到epfd中；
     *    EPOLL_CTL_MOD    修改已经注册的fd的监听事件；
     *    EPOLL_CTL_DEL    从epfd中删除一个fd；
     *  第三个参数是需要监听的fd，
     *  第四个参数是告诉内核需要监听什么事:
     *    EPOLLIN      表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
     *    EPOLLOUT     表示对应的文件描述符可以写；
     *    EPOLLPRI     表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
     *    EPOLLERR     表示对应的文件描述符发生错误；
     *    EPOLLHUP     表示对应的文件描述符被挂断；
     *    EPOLLET      将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
     *    EPOLLONESHOT 只监听一次事件，当监听完这次事件之后,
     *                 如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里。
     */
    epoll_ctl(m_iEpollFd, op, fd, &ev);
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman