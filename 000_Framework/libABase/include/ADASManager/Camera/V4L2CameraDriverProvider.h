
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__

#include "CameraDriverProvider.h"
#include "CameraDriverProviderFactory.h"
#include "CameraDisplay.h"

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

#define WRITE_FILE

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define DEFAULT_PIXEL_FORMAT V4L2_PIX_FMT_YUYV
#define NB_BUFFER 10

#define AllocBufferCount 10

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

typedef enum {
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
} eIo_method;

struct UserBuffer {
    VOID* start;
    UInt32 length;
};

class V4L2CameraDriverProvider : public CameraDriverProvider
{
public:
    V4L2CameraDriverProvider(const string& cameraName, eIo_method m);

    ~V4L2CameraDriverProvider();

    Int32 OpenDriver() override;
    Int32 CloseDriver() override;

    Int32 InitDevice() override;
    Int32 UninitDevice() override;

    Int32 GetCapture() override;
    Int32 StopCapture() override;

    VOID update() override;
    VOID ShowInfo() override;

private:
    Int32 Init_read(UInt32 buffer_size);
    Int32 Init_mmap();
    Int32 Init_userp(UInt32 buffer_size);
    Int32 Read_frame();
    Int32 xioctl(Int32 fd, UInt64 request, VOID* argp);
    void CloseFd(const Int32 fd);

#ifdef WRITE_FILE
    VOID Process_image(const VOID* p, Int32 size);
#endif

    VOID Display(VOID* p, Int32 width, Int32 height);

private:
    struct VideoInfo *m_pVideoInfo = nullptr;
    eIo_method m_eIo = IO_METHOD_MMAP;

    struct UserBuffer* m_pBuffers = nullptr;

    Int32 BufferCountReal = AllocBufferCount;

    BOOLEAN m_bIsStarted = FALSE;

    BOOLEAN m_bIsStreamOff = FALSE;

    CameraDisplay* m_display = NULL;

    viewInfo m_viewInfo{640, 480, {0, 0}, 1};

#ifdef WRITE_FILE
    FILE *m_pFp = nullptr;
    string m_strFilename = string("test.yuv");
#endif
};

class V4L2CameraDriverProviderFactory : public CameraDriverProviderFactory
{
public:
    CameraDriverProvider* CreateCameraDriverProvider(const string& cameraName) override {
        return new V4L2CameraDriverProvider(cameraName, IO_METHOD_MMAP);
    }

    ~V4L2CameraDriverProviderFactory() {}
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_V4L2CAMERADRIVERPROVIDER_H__