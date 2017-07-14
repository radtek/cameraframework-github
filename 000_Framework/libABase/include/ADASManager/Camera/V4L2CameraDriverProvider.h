
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__

#include "CameraDriverProvider.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <getopt.h>             /* getopt_long() */

#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <asm/types.h>          /* for videodev2.h */
#include <linux/videodev2.h>

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define DEFAULT_PIXEL_FORMAT V4L2_PIX_FMT_YUYV
#define NB_BUFFER 10

struct VideoInfo {
    struct v4l2_capability cap;
    struct v4l2_format format;
    struct v4l2_buffer buf;
    struct v4l2_requestbuffers rb;
    VOID *mem[NB_BUFFER];
    BOOLEAN isStreaming;
    Int32 width;
    Int32 height;
    Int32 formatIn;
    Int32 framesizeIn;
};

class V4L2CameraDriverProvider : public CameraDriverProvider
{
public:
    V4L2CameraDriverProvider(const string& cameraName);

    ~V4L2CameraDriverProvider();

    Int32 OpenDriver() override;
    VOID SetParam() override;
    VOID AllocMemory() override;
    VOID GetCapture() override;
    VOID CloseDriver() override;

    //BOOLEAN IsOpen() override;
    VOID ShowInfo() override;

private:
    struct VideoInfo *mVideoInfo = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__