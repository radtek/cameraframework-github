
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

#define CLEAR(x) memset (&(x), 0, sizeof (x))

/**
*function name: xioctl
*description:
*Do ioctl and retry if error was EINTR(“A signal was caught during the ioctl() operation”)
*/
Int32 V4L2CameraDriverProvider::xioctl(Int32 fd, UInt64 request, VOID* argp)
{
    Int32 ret;

    do {
        ret = ioctl(fd, request, argp);
        ALOGI("V4L2CameraDriverProvider::xioctl ret = %d, m_bIsStreamOff=%d, request=%lu, VIDIOC_DQBUF=%lu\n", ret,m_bIsStreamOff, request, VIDIOC_DQBUF);
        if(-1 == ret && m_bIsStreamOff /*&& request == VIDIOC_DQBUF*/) {
            ALOGI("V4L2CameraDriverProvider::xioctl return 0\n");
            return 0;
        }
    } while (-1 == ret && EINTR == errno);

    return ret;
}

V4L2CameraDriverProvider::V4L2CameraDriverProvider(const string& cameraName, eIo_method m)
    : CameraDriverProvider(cameraName)
    , m_eIo(m)
{
    // Allocate memory for video info structure
    m_pVideoInfo = (struct VideoInfo*)calloc(1, sizeof(struct VideoInfo));
    if(!m_pVideoInfo){
        ALOGE("V4L2CameraDriverProvider : calloc failed\n");
    }

    ALOGI("V4L2CameraDriverProvider provider for camera : %s,  DriverPath : %s\n", cameraName.c_str(), m_strDriverPath.c_str());
}

V4L2CameraDriverProvider::~V4L2CameraDriverProvider()
{
    // Close the camera handle and free the video info structure
    CloseDriver();

    if(m_pVideoInfo)
    {
        free(m_pVideoInfo);
        m_pVideoInfo = nullptr;
    }

    m_bIsStarted = FALSE;
}

Int32 V4L2CameraDriverProvider::OpenDriver()
{
    ALOGI("V4L2CameraDriverProvider::OpenDriver\n");

    struct stat st;

    if (-1 == stat(m_strDriverPath.c_str(), &st)) {
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error %s Cannot identify : %s\n", m_strDriverPath.c_str(), strerror(errno));
        return -1;
    }

    if (!S_ISCHR(st.st_mode)) {
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error %s is no device : %s\n", m_strDriverPath.c_str(), strerror(errno));
        return -1;
    }

    Int32 ret = -1;

    if((m_iFd = open(m_strDriverPath.c_str(), O_RDWR, 0)) == -1){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error while opening handle to V4L2 Camera: %s\n", strerror(errno));
        return -1;
    }

    ret = xioctl(m_iFd, VIDIOC_QUERYCAP, &m_pVideoInfo->cap);
    if(ret < 0){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error when querying the capabilities of the V4L2 Camera\n");
        close(m_iFd);
        return -1;
    }

    if((m_pVideoInfo->cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error while adapter initialization: video capture not supported.\n");
        close(m_iFd);
        return -1;
    }

    if(!(m_pVideoInfo->cap.capabilities & V4L2_CAP_STREAMING)){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error while adapter initialization: Capture device does not support streaming i/o.\n");
        close(m_iFd);
        return -1;
    }

    m_bIsOpened = TRUE;

#ifdef WRITE_FILE
    m_pFp = fopen(m_strFilename.c_str(), "wa+");
#endif

    return 0;
}

Int32 V4L2CameraDriverProvider::Init_read(UInt32 buffer_size)
{
    ALOGI("V4L2CameraDriverProvider::Init_read\n");

    m_pBuffers = (struct UserBuffer*)calloc(1, sizeof(struct UserBuffer));

    if (!m_pBuffers) {
        ALOGE("Out of memory\n");
        return -1;
    }

    m_pBuffers[0].length = buffer_size;
    m_pBuffers[0].start = malloc(buffer_size);

    if (!m_pBuffers[0].start) {
        ALOGE("Out of memory\n");
        return -1;
    }
    return 0;
}

Int32 V4L2CameraDriverProvider::Init_mmap()
{
    ALOGI("V4L2CameraDriverProvider::Init_mmap\n");

    struct v4l2_requestbuffers req;

    CLEAR(req);

    req.count = BufferCountReal;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(m_iFd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            ALOGE("%s(%s) does not support memory mapping\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
            return -1;
        } else {
            ALOGE("VIDIOC_REQBUFS");
            return -1;
        }
    }

    if (req.count < 2) {
        ALOGE("Insufficient buffer memory on %s(%s)\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
        return -1;
    }

    m_pBuffers = (struct UserBuffer*)calloc(req.count, sizeof(struct UserBuffer));

    if (!m_pBuffers) {
        ALOGE("Out of memory\n");
        return -1;
    }

    for (BufferCountReal = 0; BufferCountReal < req.count; ++BufferCountReal) {
        struct v4l2_buffer buf;

        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = BufferCountReal;

        if (-1 == xioctl(m_iFd, VIDIOC_QUERYBUF, &buf)) {
            ALOGE("VIDIOC_QUERYBUF");
            return -1;
        }

        m_pBuffers[BufferCountReal].length = buf.length;
        m_pBuffers[BufferCountReal].start = mmap(NULL /* start anywhere */, buf.length,
                PROT_READ | PROT_WRITE /* required */,
                MAP_SHARED /* recommended */, m_iFd, buf.m.offset);

        if (MAP_FAILED == m_pBuffers[BufferCountReal].start) {
            ALOGE("mmap");
            return -1;
        }
    }
    return 0;
}

Int32 V4L2CameraDriverProvider::Init_userp(UInt32 buffer_size)
{
    ALOGI("V4L2CameraDriverProvider::Init_userp\n");

    struct v4l2_requestbuffers req;
    UInt32 page_size;

    page_size = getpagesize();
    buffer_size = (buffer_size + page_size - 1) & ~(page_size - 1);

    CLEAR(req);

    req.count = AllocBufferCount;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_USERPTR;

    if (-1 == xioctl(m_iFd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            ALOGE("%s(%s) does not support user pointer i/o\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
            return -1;
        } else {
            ALOGE("VIDIOC_REQBUFS");
            return -1;
        }
    }

    m_pBuffers = (struct UserBuffer*)calloc(AllocBufferCount, sizeof(struct UserBuffer));

    if (!m_pBuffers) {
        ALOGE("Out of memory\n");
        return -1;
    }

    for (BufferCountReal = 0; BufferCountReal < AllocBufferCount; ++BufferCountReal) {
        m_pBuffers[BufferCountReal].length = buffer_size;
        m_pBuffers[BufferCountReal].start = memalign(/* boundary */page_size,
                buffer_size);

        if (!m_pBuffers[BufferCountReal].start) {
            ALOGE("Out of memory\n");
            return -1;
        }
    }
    return 0;
}

Int32 V4L2CameraDriverProvider::InitDevice()
{
    ALOGI("V4L2CameraDriverProvider::InitDevice\n");

    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    UInt32 min;

    if (-1 == xioctl(m_iFd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            ALOGE("%s(%s) is no V4L2 device\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
            return -1;
        } else {
            ALOGE("VIDIOC_QUERYCAP");
            return -1;
        }
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        ALOGE("%s(%s) is no video capture device\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
        return -1;
    }

    switch (m_eIo) {
        case IO_METHOD_READ:
            if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
                ALOGE("%s(%s) does not support read i/o\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
                return -1;
            }
            break;

        case IO_METHOD_MMAP:
        case IO_METHOD_USERPTR:
            if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
                ALOGE("%s(%s) does not support streaming i/o\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
                return -1;
            }
            break;
    }

    /* Select video input, video standard and tune here. */

    CLEAR(cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (0 == xioctl(m_iFd, VIDIOC_CROPCAP, &cropcap)) {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        if (-1 == xioctl(m_iFd, VIDIOC_S_CROP, &crop)) {
            switch (errno) {
                case EINVAL:
                    /* Cropping not supported. */
                    break;
                default:
                    /* Errors ignored. */
                    break;
            }
        }
    } else {
        /* Errors ignored. */
    }

    CLEAR(fmt);

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 640;
    fmt.fmt.pix.height = 480;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

    if (-1 == xioctl(m_iFd, VIDIOC_S_FMT, &fmt)) {
        ALOGE("VIDIOC_S_FMT");
        return -1;
    }

    /* Note VIDIOC_S_FMT may change width and height. */

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    Int32 ret;
    switch (m_eIo) {
        case IO_METHOD_READ:
            ret = Init_read(fmt.fmt.pix.sizeimage);
            break;
        case IO_METHOD_MMAP:
            ret = Init_mmap();
            break;
        case IO_METHOD_USERPTR:
            ret = Init_userp(fmt.fmt.pix.sizeimage);
            break;
    }

    if(!ret){
        m_bHasInit = TRUE;
    }
    return ret;
}

Int32 V4L2CameraDriverProvider::UninitDevice()
{
    ALOGI("V4L2CameraDriverProvider::UninitDevice\n");

    UInt32 i;

    switch (m_eIo) {
        case IO_METHOD_READ:
            free(m_pBuffers[0].start);
            break;

        case IO_METHOD_MMAP:
            for (i = 0; i < BufferCountReal; ++i)
                if (-1 == munmap(m_pBuffers[i].start, m_pBuffers[i].length)) {
                    ALOGE("munmap");
                    return -1;
                }
            break;

        case IO_METHOD_USERPTR:
            for (i = 0; i < BufferCountReal; ++i)
                free(m_pBuffers[i].start);
            break;
    }

    free(m_pBuffers);

    m_bHasInit = FALSE;
}

VOID V4L2CameraDriverProvider::ShowInfo()
{
    ALOGI("V4L2CameraDriverProvider::ShowInfo\n");

    return;
}

#ifdef WRITE_FILE
VOID V4L2CameraDriverProvider::Process_image(const VOID * p, Int32 size) {
    ALOGI("V4L2CameraDriverProvider::Process_image\n");
    fwrite(p, size, 1, m_pFp);
}
#endif

Int32 V4L2CameraDriverProvider::Read_frame()
{
    ALOGI("V4L2CameraDriverProvider::Read_frame\n");

    struct v4l2_buffer buf;
    UInt32 i;

    switch (m_eIo) {
        case IO_METHOD_READ:
            if (-1 == read(m_iFd, m_pBuffers[0].start, m_pBuffers[0].length)) {
                switch (errno) {
                    case EAGAIN:
                        return 0;

                    case EIO:
                        /* Could ignore EIO, see spec. */
                        /* fall through */
                    default:
                        ALOGE("Read_frame");
                        return 0; ///////////////////////////////////
                }
            }
        #ifdef WRITE_FILE
            Process_image(m_pBuffers[0].start, m_pBuffers[0].length);
        #endif

            break;

        case IO_METHOD_MMAP:
            CLEAR(buf);

            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            ALOGI("V4L2CameraDriverProvider::Read_frame VIDIOC_DQBUF = %lu\n", VIDIOC_DQBUF);
            if(!m_bIsStreamOff) {
                if (-1 == xioctl(m_iFd, VIDIOC_DQBUF, &buf)) {
                    switch (errno) {
                        case EAGAIN:
                            return 0;

                        case EIO:
                            /* Could ignore EIO, see spec. */
                            /* fall through */

                        default:
                            //errno_exit("VIDIOC_DQBUF");
                            ALOGE("VIDIOC_DQBUF\n");
                            return 0; ///////////////////////////////////////////
                    }
                }
            } else {
                return 1;
            }

            assert(buf.index < BufferCountReal);

        #ifdef WRITE_FILE
            Process_image(m_pBuffers[buf.index].start, buf.length);
        #endif

            if (-1 == xioctl(m_iFd, VIDIOC_QBUF, &buf)) {
                //errno_exit("VIDIOC_QBUF");
                ALOGE("VIDIOC_QBUF\n");
                return 0; ///////////////////////////////////////////
            }

            break;

        case IO_METHOD_USERPTR:
            CLEAR(buf);

            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_USERPTR;

            if (-1 == xioctl(m_iFd, VIDIOC_DQBUF, &buf)) {
                switch (errno) {
                    case EAGAIN:
                        return 0;

                    case EIO:
                        /* Could ignore EIO, see spec. */
                        /* fall through */

                    default:
                        ALOGE("VIDIOC_DQBUF");
                        return 0;////////////////////////////////////////
                }
            }

            for (i = 0; i < BufferCountReal; ++i) {
                if (buf.m.userptr == (unsigned long) m_pBuffers[i].start
                        && buf.length == m_pBuffers[i].length)
                    break;
            }

            assert(i < BufferCountReal);

        #ifdef WRITE_FILE
            Process_image((VOID *)buf.m.userptr, buf.length);
        #endif

            if (-1 == xioctl(m_iFd, VIDIOC_QBUF, &buf)) {
                ALOGE("VIDIOC_QBUF");
                return 0;////////////////////////////////////////
            }

            break;
    }

    return 1;
}

VOID V4L2CameraDriverProvider::update()
{
    ALOGI("V4L2CameraDriverProvider::update\n");

    if(!m_bIsStreamOff) {
        Read_frame();
    }

    // while (m_bIsContinueGet) {

    //     Read_frame();


    //     for (;;) {
    //         fd_set fds;
    //         struct timeval tv;
    //         Int32 r;

    //         FD_ZERO(&fds);
    //         FD_SET(m_iFd, &fds);

    //         /* Timeout. */
    //         tv.tv_sec = 2;
    //         tv.tv_usec = 0;

    //         r = select(m_iFd + 1, &fds, NULL, NULL, &tv);

    //         if (-1 == r) {
    //             if (EINTR == errno)
    //                 continue;

    //             ALOGE("select");
    //             //return -1;
    //             return;
    //         }

    //         if (0 == r) {
    //             ALOGE("select timeout\n");
    //             //return -1;
    //             return;
    //         }

    //         if (Read_frame())
    //             break;

    //         /* EAGAIN - continue select loop. */
    //     }
    // }
}

Int32 V4L2CameraDriverProvider::GetCapture()
{
    ALOGI("V4L2CameraDriverProvider::GetCapture\n");

    UInt32 i;
    enum v4l2_buf_type type;

    switch (m_eIo) {
        case IO_METHOD_READ:
            /* Nothing to do. */
            break;

        case IO_METHOD_MMAP:
            for (i = 0; i < BufferCountReal; ++i) {
                struct v4l2_buffer buf;
                CLEAR(buf);

                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_MMAP;
                buf.index = i;

                if (-1 == xioctl(m_iFd, VIDIOC_QBUF, &buf)){
                    ALOGE("V4L2CameraDriverProvider::GetCapture error VIDIOC_QBUF\n");
                    return -1;
                }
            }

            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

            if (-1 == xioctl(m_iFd, VIDIOC_STREAMON, &type)) {
                ALOGE("V4L2CameraDriverProvider::GetCapture error VIDIOC_STREAMON\n");
                return -1;
            }

            break;

        case IO_METHOD_USERPTR:
            for (i = 0; i < BufferCountReal; ++i) {
                struct v4l2_buffer buf;

                CLEAR(buf);

                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_USERPTR;
                buf.index = i;
                buf.m.userptr = (unsigned long) m_pBuffers[i].start;
                buf.length = m_pBuffers[i].length;

                if (-1 == xioctl(m_iFd, VIDIOC_QBUF, &buf)) {
                    ALOGE("V4L2CameraDriverProvider::GetCapture error VIDIOC_QBUF\n");
                    return -1;
                }
            }

            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

            if (-1 == xioctl(m_iFd, VIDIOC_STREAMON, &type)) {
                ALOGE("V4L2CameraDriverProvider::GetCapture error VIDIOC_STREAMON\n");
                return -1;
            }

            break;
    }

    if (!m_bIsStarted) {
        m_bIsStreamOff = FALSE;
        start();
        m_bIsStarted = TRUE;
    } else {
        m_bIsStreamOff = FALSE;
        resume();
    }

    return 0;
}

Int32 V4L2CameraDriverProvider::StopCapture()
{
    ALOGI("V4L2CameraDriverProvider::StopCapture\n");

    enum v4l2_buf_type type;

    switch (m_eIo) {
        case IO_METHOD_READ:
            /* Nothing to do. */
            break;

        case IO_METHOD_MMAP:
        case IO_METHOD_USERPTR:
            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            m_bIsStreamOff = TRUE;
            pause();

            //sleep(1);
            if (-1 == xioctl(m_iFd, VIDIOC_STREAMOFF, &type)) {
                ALOGE("V4L2CameraDriverProvider::StopCapture error\n");
                return -1;
            }

            break;
    }
    return 0;
}

Int32 V4L2CameraDriverProvider::CloseDriver()
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
    quit();

#ifdef WRITE_FILE
    fclose(m_pFp);
#endif

    return 0;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman