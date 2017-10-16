
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/epoll.h>

#include "EpollGPIO.h"
#include "TraceMacros.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

EpollGPIO::EpollGPIO(const string& strName, int gpioNum, CALLBACK_CFunctor* pFunctor)
    : CRunableBase(strName, FALSE)
    , m_iReserveGearGPIO(gpioNum)
    , m_iGpioFd(GPIO_Open_Fd(m_iReserveGearGPIO, O_RDONLY))
    , m_pEpoll(nullptr)
    , m_pFun(pFunctor)
{
    GPIO_Export(m_iReserveGearGPIO);
    GPIO_Set_Dir(m_iReserveGearGPIO, "in");
    GPIO_Set_Edge(m_iReserveGearGPIO, "both");
    ALOGD("Sucessfully Configure GPIO-%d as input\n", m_iReserveGearGPIO);

    m_pEpoll = new Epoller();
    m_pEpoll->Create(10);
    m_pEpoll->Add(m_iGpioFd, 0l, EPOLLPRI);
}

EpollGPIO::~EpollGPIO()
{
    GPIO_Close_Fd(m_iGpioFd);

    if(m_pEpoll != nullptr) {
        delete m_pEpoll;
        m_pEpoll = nullptr;
    }
}

VOID EpollGPIO::update()
{
    int num = m_pEpoll->Wait(-1);
    for(int i = 0;i < num; i++) {
        if (m_pEpoll->m_pEvents[i].events & EPOLLPRI) {
            memset(m_cGpiobuf, 0x00, sizeof(m_cGpiobuf));
            read(m_pEpoll->m_pEvents[i].data.fd, m_cGpiobuf, sizeof(m_cGpiobuf));
            lseek(m_pEpoll->m_pEvents[i].data.fd, 0, SEEK_SET);

            unsigned int valueback = REVERSE_GEAR_UNKNOWN_ACTION;
            GPIO_Get_Value(m_iReserveGearGPIO, &valueback);
            (*m_pFun)(valueback);

            ALOGD("reserveGearGPIO value = %u\n", valueback);
        }
    }
}

int EpollGPIO::GPIO_Export(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if (fd < 0) {
        ALOGE("Failed export GPIO-%d\n", gpio);
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    ALOGD("Sucessfully export GPIO-%d\n", gpio);
    return 0;
}

int EpollGPIO::GPIO_Unexport(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
    if (fd < 0) {
        ALOGE("Failed unexport GPIO-%d\n", gpio);
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    ALOGD("Sucessfully unexport GPIO-%d\n", gpio);
    return 0;
}

int EpollGPIO::GPIO_Set_Dir(unsigned int gpio, const char *dir)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", gpio);
    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        ALOGE("Failed set GPIO-%d direction\n", gpio);
        return fd;
    }

    write(fd, dir, strlen(dir)+1);
    close(fd);
    ALOGD("Sucessfully set GPIO-%d direction\n", gpio);
    return 0;
}

int EpollGPIO::GPIO_Set_Value(unsigned int gpio, unsigned int value)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        ALOGE("Failed set GPIO-%d value\n", gpio);
        return fd;
    }

    if (value!=0)
    {
        int i = write(fd, "1", 2);
        ALOGD("GPIO-%d value set high\n", gpio);
    } else {
        write(fd, "0", 2);
        ALOGD("GPIO-%d value set low\n", gpio);
    }

    close(fd);
    ALOGD("Sucessfully set GPIO-%d value\n", gpio);
    return 0;
}

int EpollGPIO::GPIO_Get_Value(unsigned int gpio, unsigned int *value)
{
    int fd, len;
    char buf[MAX_BUF];
    char ch;

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY);
    if (fd < 0) {
        ALOGE("Failed get GPIO-%d value\n", gpio);
        return fd;
    }

    read(fd, &ch, 1);

    if (ch != '0') {
        *value = 1;
    } else {
        *value = 0;
    }

    close(fd);
    ALOGD("Sucessfully get GPIO-%d value\n", gpio);
    return 0;
}

int EpollGPIO::GPIO_Set_Edge(unsigned int gpio, const char *edge)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        ALOGE("Failed set GPIO-%d edge\n", gpio);
        return fd;
    }

    write(fd, edge, strlen(edge) + 1);
    close(fd);
    return 0;
}

int EpollGPIO::GPIO_Open_Fd(unsigned int gpio, unsigned int dir)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, dir | O_NONBLOCK );
    if (fd < 0) {
        ALOGE("gpio/fd_open");
    }
    return fd;
}

int EpollGPIO::GPIO_Close_Fd(int fd)
{
    return close(fd);
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman