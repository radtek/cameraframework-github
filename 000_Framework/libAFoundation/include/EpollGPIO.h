
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_EPOLLGPIO_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_EPOLLGPIO_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "TypeDefine.h"
#include "Epoller.h"
#include "CRunableBase.h"
#include "CFunctor.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

typedef CFunctorArg1<unsigned int>  CALLBACK_CFunctor;

class EpollGPIO : public CRunableBase
{
public:
    EpollGPIO(const string& strName, int gpioNum, CALLBACK_CFunctor* fun);

    ~EpollGPIO();

    VOID update() override;

private:
    /* gpio export */
    int GPIO_Export(unsigned int gpio);

    /* gpio unexport */
    int GPIO_Unexport(unsigned int gpio);

    /* gpio set dir */
    int GPIO_Set_Dir(unsigned int gpio, const char *dir);

    /* gpio set value */
    int GPIO_Set_Value(unsigned int gpio, unsigned int value);

    /* gpio get value */
    int GPIO_Get_Value(unsigned int gpio, unsigned int *value);

    /* gpio set edge */
    int GPIO_Set_Edge(unsigned int gpio, const char *edge);

    /* gpio fd open */
    int GPIO_Open_Fd(unsigned int gpio, unsigned int dir);

    /* gpio fd close */
    int GPIO_Close_Fd(int fd);

private:
    int m_iReserveGearGPIO;
    int m_iGpioFd;
    int m_iEpollFd;
    char m_cGpiobuf[MAX_BUF];

    Epoller* m_pEpoll;
    CALLBACK_CFunctor* m_pFun;
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_EPOLLGPIO_H__