
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
    // Allocate memory for video info structure
    mVideoInfo = (struct VideoInfo*)calloc(1, sizeof(struct VideoInfo));
    if(!mVideoInfo){
        ALOGE("V4L2CameraDriverProvider : calloc failed\n");
    }

    ALOGI("V4L2CameraDriverProvider provider for camera : %s,  DriverPath : %s\n", cameraName.c_str(), m_strDriverPath.c_str());
}

Int32 V4L2CameraDriverProvider::OpenDriver()
{
    ALOGI("V4L2CameraDriverProvider::OpenDriver\n");

    Int32 ret = -1;

    if((m_iFd = open(m_strDriverPath.c_str(), O_RDWR, 0)) == -1){
        ALOGE("V4L2CameraDriverProvider : Error while opening handle to V4L2 Camera: %s\n", strerror(errno));
        return -1;
    }

    ret = ioctl(m_iFd, VIDIOC_QUERYCAP, &mVideoInfo->cap);
    if(ret < 0){
        ALOGE("V4L2CameraDriverProvider : Error when querying the capabilities of the V4L Camera\n");
        return -1;
    }

    if((mVideoInfo->cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0){
        ALOGE("V4L2CameraDriverProvider : Error while adapter initialization: video capture not supported.\n");
        return -1;
    }

    if(!(mVideoInfo->cap.capabilities & V4L2_CAP_STREAMING)){
        ALOGE("V4L2CameraDriverProvider : Error while adapter initialization: Capture device does not support streaming i/o.\n");
        return -1;
    }

    m_bIsOpened = TRUE;
    return ret;
}

V4L2CameraDriverProvider::~V4L2CameraDriverProvider()
{
    // Close the camera handle and free the video info structure
    CloseDriver();

    if(mVideoInfo)
    {
        free(mVideoInfo);
        mVideoInfo = nullptr;
    }
}

VOID V4L2CameraDriverProvider::CloseDriver()
{
    ALOGI("V4L2CameraDriverProvider::CloseDriver\n");

    // Close the camera handle and free the video info structure
    if(0 == close(m_iFd)){
        ALOGI("V4L2CameraDriverProvider::CloseDriver %s success, m_iFd=%d\n", m_strDriverPath.c_str(), m_iFd);
    } else {
        ALOGE("V4L2CameraDriverProvider::CloseDriver %s failed, m_iFd=%d\n", m_strDriverPath.c_str(), m_iFd);
    }
    m_iFd = -1;
    m_bIsOpened = FALSE;
}

VOID V4L2CameraDriverProvider::ShowInfo()
{
    ALOGI("V4L2CameraDriverProvider::ShowInfo\n");
}

VOID V4L2CameraDriverProvider::SetParam()
{
    ALOGI("V4L2CameraDriverProvider::SetParam\n");
    return;
}

VOID V4L2CameraDriverProvider::AllocMemory()
{
    ALOGI("V4L2CameraDriverProvider::AllocMemory\n");
    return;
}

VOID V4L2CameraDriverProvider::GetCapture()
{
    ALOGI("V4L2CameraDriverProvider::GetCapture\n");
    return;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman