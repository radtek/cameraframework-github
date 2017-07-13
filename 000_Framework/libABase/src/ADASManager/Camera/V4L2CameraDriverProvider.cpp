
#include "ADASManager/Camera/V4L2CameraDriverProvider.h"

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <string.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <stdlib.h>

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

V4L2CameraDriverProvider::V4L2CameraDriverProvider(const string& cameraName)
    : CameraDriverProvider(cameraName)
{
    ALOGI("V4L2CameraDriverProvider provider for camera : %s,  DriverPath : %s\n", cameraName.c_str(), m_strDriverPath.c_str());
}

V4L2CameraDriverProvider::~V4L2CameraDriverProvider()
{

}

BOOLEAN V4L2CameraDriverProvider::IsOpen()
{
    ALOGI("V4L2CameraDriverProvider::IsOpen, m_iFd = %d\n", m_iFd);

    // struct stat buf;
    // if (fstat(m_iFd, &buf) == -1) {
    //     ALOGE("stat");
    //     return FALSE;
    // } else {
    //     return TRUE;
    // }


    // struct stat _stat;
    // int ret = -1;
    // if(!fcntl(fd, F_GETFL)) {
    //     if(!fstat(fd, &_stat)) {
    //         if(_stat.st_nlink >= 1)
    //             ret = 0;
    //         else
    //             printf("File was deleted!\n");
    //     }
    // }
    // if(errno != 0)
    //     perror("check_fd_fine");
    // return ret;
    return m_iFd != -1;
}

void V4L2CameraDriverProvider::ShowInfo()
{
    ALOGI("V4L2CameraDriverProvider::ShowInfo\n");
}

int V4L2CameraDriverProvider::OpenDriver()
{
    ALOGI("V4L2CameraDriverProvider::OpenDriver\n");

    m_iFd = open(m_strDriverPath.c_str(), O_RDWR, 0);
    if (m_iFd < 0) {
        ALOGE("V4L2CameraDriverProvider::OpenDriver %s failed, m_iFd=%d\n", m_strDriverPath.c_str(), m_iFd);
        return -1;
    } else {
        ALOGI("V4L2CameraDriverProvider::OpenDriver %s success, m_iFd = %d\n", m_strDriverPath.c_str(), m_iFd);
    }
    return 0;
}

void V4L2CameraDriverProvider::SetParam()
{
    ALOGI("V4L2CameraDriverProvider::SetParam\n");
    return;
}

void V4L2CameraDriverProvider::AllocMemory()
{
    ALOGI("V4L2CameraDriverProvider::AllocMemory\n");
    return;
}

void V4L2CameraDriverProvider::GetCapture()
{
    ALOGI("V4L2CameraDriverProvider::GetCapture\n");
    return;
}

void V4L2CameraDriverProvider::CloseDriver()
{
    ALOGI("V4L2CameraDriverProvider::CloseDriver\n");

    if(0 == close(m_iFd)){
        ALOGI("V4L2CameraDriverProvider::CloseDriver %s success, m_iFd=%d\n", m_strDriverPath.c_str(), m_iFd);
    } else {
        ALOGE("V4L2CameraDriverProvider::CloseDriver %s failed, m_iFd=%d\n", m_strDriverPath.c_str(), m_iFd);
    }

    m_iFd = -1;
    return;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman