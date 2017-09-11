
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

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include <sched.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define ARRAY_SIZE(a)   (sizeof(a)/sizeof((a)[0]))

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
    } while (-1 == ret && EINTR == errno);

    return ret;
}

// static BYTE *textFileRead(char * filename)
// {
//     BYTE *s = (BYTE *)malloc(640*480*2);
//     memset(s, 0, 640*480*2);
//     FILE *infile = fopen(filename, "rb");
//     int len = fread(s, 1, 640*480*2, infile);
//     ALOGD("V4L2CameraDriverProvider::textFileRead = %d, s = %p\n", len, s);
//     fclose(infile);

//     s[len] = 0;
//     return s;
// }

V4L2CameraDriverProvider::V4L2CameraDriverProvider(const string& cameraName, eIo_method m)
    : CameraDriverProvider(cameraName)
    , m_eIo(m)
{
    // Allocate memory for video info structure
    m_pVideoInfo = (struct VideoInfo*)calloc(1, sizeof(struct VideoInfo));
    if(!m_pVideoInfo){
        ALOGE("calloc failed\n");
    }

    ALOGE("***********************************************************************\n");

    if(m_displaySample == nullptr) {
        m_displaySample = new DisplaySample();
    }

    if(m_pPaint == nullptr) {
        m_pPaint = new PaintImpl();
    }

    ALOGD("provider for camera : %s,  DriverPath : %s\n", cameraName.c_str(), m_strDriverPath.c_str());
}

V4L2CameraDriverProvider::~V4L2CameraDriverProvider()
{
    // Close the camera handle and free the video info structure
    if(m_bHasInit) UninitDevice();
    if(m_bIsOpened) CloseDriver();

    if(m_pVideoInfo)
    {
        free(m_pVideoInfo);
        m_pVideoInfo = nullptr;
    }

    if(m_displaySample != nullptr)
    {
        delete m_displaySample;
        m_displaySample = nullptr;
    }

    if(m_pPaint != nullptr)
    {
        m_pPaint->shutDown();
        delete m_pPaint;
        m_pPaint = nullptr;
    }

    m_bIsStarted = FALSE;
}

void V4L2CameraDriverProvider::CloseFd(const Int32 fd)
{
    close(fd);
    m_bIsOpened = FALSE;
}

ECode V4L2CameraDriverProvider::OpenDriver()
{
    ALOGD("V4L2CameraDriverProvider::OpenDriver\n");

    struct stat st;

    if(-1 == stat(m_strDriverPath.c_str(), &st)){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error %s Cannot identify : %s\n", m_strDriverPath.c_str(), strerror(errno));
        return -1;
    }

    if(!S_ISCHR(st.st_mode)){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error %s is no device : %s\n", m_strDriverPath.c_str(), strerror(errno));
        return -1;
    }

    if((m_iFd = open(m_strDriverPath.c_str(), O_RDWR, 0)) == -1){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error while opening handle to V4L2 Camera: %s\n", strerror(errno));
        return -1;
    }

    Int32 ret = xioctl(m_iFd, VIDIOC_QUERYCAP, &m_pVideoInfo->cap);
    if(ret < 0){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error when querying the capabilities of the V4L2 Camera\n");
        CloseFd(m_iFd);
        return -1;
    }

    if((m_pVideoInfo->cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error while adapter initialization: video capture not supported.\n");
        CloseFd(m_iFd);
        return -1;
    }

    if(!(m_pVideoInfo->cap.capabilities & V4L2_CAP_STREAMING)){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error while adapter initialization: Capture device does not support streaming i/o.\n");
        CloseFd(m_iFd);
        return -1;
    }

#ifdef WRITE_FILE
    if((m_pFp = fopen(m_strFilename.c_str(), "wa+")) == nullptr){
        ALOGE("V4L2CameraDriverProvider::OpenDriver : Error while fopen : %s.\n", m_strFilename.c_str());
        CloseFd(m_iFd);
        return -1;
    }
#endif

    m_bIsOpened = TRUE;

    return NO_ERROR;
}

ECode V4L2CameraDriverProvider::Init_read(UInt32 buffer_size)
{
    ALOGD("V4L2CameraDriverProvider::Init_read\n");

    m_pBuffers = (struct UserBuffer*)calloc(1, sizeof(struct UserBuffer));

    if(!m_pBuffers){
        ALOGE("Out of memory\n");
        return -1;
    }

    m_pBuffers[0].length = buffer_size;
    m_pBuffers[0].start = malloc(buffer_size);

    if(!m_pBuffers[0].start){
        ALOGE("Out of memory\n");
        return -1;
    }
    return NO_ERROR;
}

ECode V4L2CameraDriverProvider::Init_mmap()
{
    ALOGD("V4L2CameraDriverProvider::Init_mmap\n");

    struct v4l2_requestbuffers req;

    CLEAR(req);

    req.count = BufferCountReal;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if(-1 == xioctl(m_iFd, VIDIOC_REQBUFS, &req)){
        if(EINVAL == errno){
            ALOGE("%s(%s) does not support memory mapping\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
            return -1;
        }else{
            ALOGE("VIDIOC_REQBUFS error");
            return -1;
        }
    }

    if(req.count < 2){
        ALOGE("Insufficient buffer memory on %s(%s)\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
        return -1;
    }

    m_pBuffers = (struct UserBuffer*)calloc(req.count, sizeof(struct UserBuffer));

    if(!m_pBuffers){
        ALOGE("Out of memory\n");
        return -1;
    }

    for(BufferCountReal = 0; BufferCountReal < req.count; ++BufferCountReal){
        struct v4l2_buffer buf;

        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = BufferCountReal;

        if(-1 == xioctl(m_iFd, VIDIOC_QUERYBUF, &buf)){
            ALOGE("VIDIOC_QUERYBUF error");
            return -1;
        }

        ALOGD("Init_mmap buf.length = %d\n", buf.length);

        m_pBuffers[BufferCountReal].length = buf.length; //1845760; buf.length
        m_pBuffers[BufferCountReal].start = mmap(NULL /* start anywhere */, buf.length,
                PROT_READ | PROT_WRITE /* required */,
                MAP_SHARED /* recommended */, m_iFd, buf.m.offset);

        if(MAP_FAILED == m_pBuffers[BufferCountReal].start){
            ALOGE("mmap error");
            return -1;
        }
    }
    return NO_ERROR;
}

ECode V4L2CameraDriverProvider::Init_userp(UInt32 buffer_size)
{
    ALOGD("V4L2CameraDriverProvider::Init_userp\n");

    struct v4l2_requestbuffers req;
    UInt32 page_size;

    page_size = getpagesize();
    buffer_size = (buffer_size + page_size - 1) & ~(page_size - 1);

    CLEAR(req);

    req.count = AllocBufferCount;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_USERPTR;

    if(-1 == xioctl(m_iFd, VIDIOC_REQBUFS, &req)){
        if(EINVAL == errno){
            ALOGE("%s(%s) does not support user pointer i/o\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
            return -1;
        }else{
            ALOGE("VIDIOC_REQBUFS error");
            return -1;
        }
    }

    m_pBuffers = (struct UserBuffer*)calloc(req.count, sizeof(struct UserBuffer));

    if(!m_pBuffers){
        ALOGE("Out of memory\n");
        return -1;
    }

    for(BufferCountReal = 0; BufferCountReal < req.count; ++BufferCountReal){
        m_pBuffers[BufferCountReal].length = buffer_size;
        m_pBuffers[BufferCountReal].start = memalign(/* boundary */page_size,
                buffer_size);

        if(!m_pBuffers[BufferCountReal].start){
            ALOGE("Out of memory\n");
            return -1;
        }
    }
    return NO_ERROR;
}


static struct v4l2_format_info {
    const char *name;
    unsigned int fourcc;
    unsigned char n_planes;
} pixel_formats[] = {
    { "RGB332", V4L2_PIX_FMT_RGB332, 1 },
    { "RGB444", V4L2_PIX_FMT_RGB444, 1 },
    { "ARGB444", V4L2_PIX_FMT_ARGB444, 1 },
    { "XRGB444", V4L2_PIX_FMT_XRGB444, 1 },
    { "RGB555", V4L2_PIX_FMT_RGB555, 1 },
    { "ARGB555", V4L2_PIX_FMT_ARGB555, 1 },
    { "XRGB555", V4L2_PIX_FMT_XRGB555, 1 },
    { "RGB565", V4L2_PIX_FMT_RGB565, 1 },
    { "RGB555X", V4L2_PIX_FMT_RGB555X, 1 },
    { "RGB565X", V4L2_PIX_FMT_RGB565X, 1 },
    { "BGR666", V4L2_PIX_FMT_BGR666, 1 },
    { "BGR24", V4L2_PIX_FMT_BGR24, 1 },
    { "RGB24", V4L2_PIX_FMT_RGB24, 1 },
    { "BGR32", V4L2_PIX_FMT_BGR32, 1 },
    { "ABGR32", V4L2_PIX_FMT_ABGR32, 1 },
    { "XBGR32", V4L2_PIX_FMT_XBGR32, 1 },
    { "RGB32", V4L2_PIX_FMT_RGB32, 1 },
    { "ARGB32", V4L2_PIX_FMT_ARGB32, 1 },
    { "XRGB32", V4L2_PIX_FMT_XRGB32, 1 },
   // { "HSV24", V4L2_PIX_FMT_HSV24, 1 },
    //{ "HSV32", V4L2_PIX_FMT_HSV32, 1 },
    { "Y8", V4L2_PIX_FMT_GREY, 1 },
    { "Y10", V4L2_PIX_FMT_Y10, 1 },
    { "Y12", V4L2_PIX_FMT_Y12, 1 },
    { "Y16", V4L2_PIX_FMT_Y16, 1 },
    { "UYVY", V4L2_PIX_FMT_UYVY, 1 },
    { "VYUY", V4L2_PIX_FMT_VYUY, 1 },
    { "YUYV", V4L2_PIX_FMT_YUYV, 1 },
    { "YVYU", V4L2_PIX_FMT_YVYU, 1 },
    { "NV12", V4L2_PIX_FMT_NV12, 1 },
    { "NV12M", V4L2_PIX_FMT_NV12M, 2 },
    { "NV21", V4L2_PIX_FMT_NV21, 1 },
    { "NV21M", V4L2_PIX_FMT_NV21M, 2 },
    { "NV16", V4L2_PIX_FMT_NV16, 1 },
    { "NV16M", V4L2_PIX_FMT_NV16M, 2 },
    { "NV61", V4L2_PIX_FMT_NV61, 1 },
    { "NV61M", V4L2_PIX_FMT_NV61M, 2 },
    { "NV24", V4L2_PIX_FMT_NV24, 1 },
    { "NV42", V4L2_PIX_FMT_NV42, 1 },
    { "YUV420M", V4L2_PIX_FMT_YUV420M, 3 },
    //{ "YUV422M", V4L2_PIX_FMT_YUV422M, 3 },
    //{ "YUV444M", V4L2_PIX_FMT_YUV444M, 3 },
    { "YVU420M", V4L2_PIX_FMT_YVU420M, 3 },
    //{ "YVU422M", V4L2_PIX_FMT_YVU422M, 3 },
    //{ "YVU444M", V4L2_PIX_FMT_YVU444M, 3 },
    { "SBGGR8", V4L2_PIX_FMT_SBGGR8, 1 },
    { "SGBRG8", V4L2_PIX_FMT_SGBRG8, 1 },
    { "SGRBG8", V4L2_PIX_FMT_SGRBG8, 1 },
    { "SRGGB8", V4L2_PIX_FMT_SRGGB8, 1 },
    { "SBGGR10_DPCM8", V4L2_PIX_FMT_SBGGR10DPCM8, 1 },
    { "SGBRG10_DPCM8", V4L2_PIX_FMT_SGBRG10DPCM8, 1 },
    { "SGRBG10_DPCM8", V4L2_PIX_FMT_SGRBG10DPCM8, 1 },
    { "SRGGB10_DPCM8", V4L2_PIX_FMT_SRGGB10DPCM8, 1 },
    { "SBGGR10", V4L2_PIX_FMT_SBGGR10, 1 },
    { "SGBRG10", V4L2_PIX_FMT_SGBRG10, 1 },
    { "SGRBG10", V4L2_PIX_FMT_SGRBG10, 1 },
    { "SRGGB10", V4L2_PIX_FMT_SRGGB10, 1 },
    { "SBGGR10P", V4L2_PIX_FMT_SBGGR10P, 1 },
    { "SGBRG10P", V4L2_PIX_FMT_SGBRG10P, 1 },
    { "SGRBG10P", V4L2_PIX_FMT_SGRBG10P, 1 },
    { "SRGGB10P", V4L2_PIX_FMT_SRGGB10P, 1 },
    { "SBGGR12", V4L2_PIX_FMT_SBGGR12, 1 },
    { "SGBRG12", V4L2_PIX_FMT_SGBRG12, 1 },
    { "SGRBG12", V4L2_PIX_FMT_SGRBG12, 1 },
    { "SRGGB12", V4L2_PIX_FMT_SRGGB12, 1 },
    { "DV", V4L2_PIX_FMT_DV, 1 },
    { "MJPEG", V4L2_PIX_FMT_MJPEG, 1 },
    { "MPEG", V4L2_PIX_FMT_MPEG, 1 },
};

static const struct v4l2_format_info *v4l2_format_by_fourcc(unsigned int fourcc)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(pixel_formats); ++i) {
        if (pixel_formats[i].fourcc == fourcc)
            return &pixel_formats[i];
    }

    return NULL;
}

static const char *v4l2_format_name(unsigned int fourcc)
{
    const struct v4l2_format_info *info;
    static char name[5];
    unsigned int i;

    info = v4l2_format_by_fourcc(fourcc);
    if (info)
        return info->name;

    for (i = 0; i < 4; ++i) {
        name[i] = fourcc & 0xff;
        fourcc >>= 8;
    }

    name[4] = '\0';
    return name;
}

static const struct {
    const char *name;
    enum v4l2_field field;
} fields[] = {
    { "any", V4L2_FIELD_ANY },
    { "none", V4L2_FIELD_NONE },
    { "top", V4L2_FIELD_TOP },
    { "bottom", V4L2_FIELD_BOTTOM },
    { "interlaced", V4L2_FIELD_INTERLACED },
    { "seq-tb", V4L2_FIELD_SEQ_TB },
    { "seq-bt", V4L2_FIELD_SEQ_BT },
    { "alternate", V4L2_FIELD_ALTERNATE },
    { "interlaced-tb", V4L2_FIELD_INTERLACED_TB },
    { "interlaced-bt", V4L2_FIELD_INTERLACED_BT },
};

static const char *v4l2_field_name(enum v4l2_field field)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(fields); ++i) {
        if (fields[i].field == field)
            return fields[i].name;
    }

    return "unknown";
}

ECode V4L2CameraDriverProvider::InitDevice()
{
    ALOGD("V4L2CameraDriverProvider::InitDevice\n");

    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    UInt32 min;

    if(-1 == xioctl(m_iFd, VIDIOC_QUERYCAP, &cap)){
        if(EINVAL == errno){
            ALOGE("%s(%s) is no V4L2 device\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
            return -1;
        }else{
            ALOGE("VIDIOC_QUERYCAP error");
            return -1;
        }
    }

    if(!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)){
        ALOGE("%s(%s) is no video capture device\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
        return -1;
    }

    switch (m_eIo){
        case IO_METHOD_READ:
            if(!(cap.capabilities & V4L2_CAP_READWRITE)){
                ALOGE("%s(%s) does not support read i/o\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
                return -1;
            }
            break;

        case IO_METHOD_MMAP:
        case IO_METHOD_USERPTR:
            if(!(cap.capabilities & V4L2_CAP_STREAMING)){
                ALOGE("%s(%s) does not support streaming i/o\n", m_strCameraName.c_str(), m_strDriverPath.c_str());
                return -1;
            }
            break;
    }

    /* Select video input, video standard and tune here. */

    CLEAR(cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(0 == xioctl(m_iFd, VIDIOC_CROPCAP, &cropcap)){
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        if(-1 == xioctl(m_iFd, VIDIOC_S_CROP, &crop)){
            switch (errno){
                case EINVAL:
                    /* Cropping not supported. */
                    break;
                default:
                    /* Errors ignored. */
                    break;
            }
        }
    }else{
        /* Errors ignored. */
    }

    CLEAR(fmt);

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width = 1280;
    fmt.fmt.pix.height = 720;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;  //V4L2_PIX_FMT_YUYV
    fmt.fmt.pix.field = V4L2_FIELD_ANY;   //V4L2_FIELD_ANY  V4L2_FIELD_INTERLACED

    fmt.fmt.pix.field = 0;
    fmt.fmt.pix.bytesperline = 0;
    fmt.fmt.pix.sizeimage = 0;
    fmt.fmt.pix.priv = V4L2_PIX_FMT_PRIV_MAGIC;
    fmt.fmt.pix.flags = 0;

    printf("=====video_set_format======fmt.fmt.pix.width=%d\n",fmt.fmt.pix.width);
    printf("=====video_set_format======fmt.fmt.pix.height=%d\n",fmt.fmt.pix.height);
    printf("=====video_set_format======fmt.fmt.pix.pixelformat=%d\n",fmt.fmt.pix.pixelformat);
    printf("=====video_set_format======fmt.fmt.pix.field=%d\n",fmt.fmt.pix.field);
    printf("=====video_set_format======fmt.fmt.pix.bytesperline=%d\n",fmt.fmt.pix.bytesperline);
    printf("=====video_set_format======fmt.fmt.pix.sizeimage=%d\n",fmt.fmt.pix.sizeimage);
    printf("=====video_set_format======fmt.fmt.pix.flags=%d\n",fmt.fmt.pix.flags);

    if(-1 == xioctl(m_iFd, VIDIOC_S_FMT, &fmt)){
        ALOGE("VIDIOC_S_FMT error");
        return -1;
    }

    printf("+++++++++++++++++Video format set: %s (%08x) %ux%u (stride %u) field %s buffer size %u\n",
            v4l2_format_name(fmt.fmt.pix.pixelformat), fmt.fmt.pix.pixelformat,
            fmt.fmt.pix.width, fmt.fmt.pix.height, fmt.fmt.pix.bytesperline,
            v4l2_field_name((enum v4l2_field)fmt.fmt.pix.field),
            fmt.fmt.pix.sizeimage);

    /* Note VIDIOC_S_FMT may change width and height. */

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if(fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if(fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    Int32 ret;
    switch(m_eIo){
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

ECode V4L2CameraDriverProvider::UninitDevice()
{
    ALOGD("V4L2CameraDriverProvider::UninitDevice\n");

    UInt32 i;

    switch (m_eIo){
        case IO_METHOD_READ:
            free(m_pBuffers[0].start);
            break;

        case IO_METHOD_MMAP:
            for(i = 0; i < BufferCountReal; ++i)
                if(-1 == munmap(m_pBuffers[i].start, m_pBuffers[i].length)){
                    ALOGE("munmap error");
                    return -1;
                }
            break;

        case IO_METHOD_USERPTR:
            for(i = 0; i < BufferCountReal; ++i)
                free(m_pBuffers[i].start);
            break;
    }

    free(m_pBuffers);

    m_bHasInit = FALSE;

    return NO_ERROR;
}

VOID V4L2CameraDriverProvider::ShowInfo()
{
    ALOGD("V4L2CameraDriverProvider::ShowInfo\n");

    // 获取驱动信息
    struct v4l2_capability cap;
    int ret = xioctl(m_iFd, VIDIOC_QUERYCAP, &cap);
    if (ret < 0) {
        ALOGE("VIDIOC_QUERYCAP failed (%d)\n", ret);
    }
    // Print capability infomations
    printf("Capability Informations:----------------------------\n");
    printf(" driver: %s\n", cap.driver);
    printf(" card: %s\n", cap.card);
    printf(" bus_info: %s\n", cap.bus_info);
    printf(" version: %08X\n", cap.version);
    printf(" capabilities: %08X\n", cap.capabilities);
    printf("\n");


    // 获取视频格式
    struct v4l2_format fmt;
    memset(&fmt, 0, sizeof(fmt));
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;


    ret = xioctl(m_iFd, VIDIOC_G_FMT, &fmt);
    if (ret < 0) {
        ALOGE("VIDIOC_G_FMT failed (%d)\n", ret);
    }
    // Print Stream Format
    printf("\n\nStream Format Informations:---------------------\n");
    printf(" type: %d\n", fmt.type);
    printf(" width: %d\n", fmt.fmt.pix.width);
    printf(" height: %d\n", fmt.fmt.pix.height);
    char fmtstr[8];
    memset(fmtstr, 0, 8);
    memcpy(fmtstr, &fmt.fmt.pix.pixelformat, 4);
    printf(" pixelformat: %s\n", fmtstr);
    printf(" field: %d\n", fmt.fmt.pix.field);
    printf(" bytesperline: %d\n", fmt.fmt.pix.bytesperline);
    printf(" sizeimage: %d\n", fmt.fmt.pix.sizeimage);
    printf(" colorspace: %d\n", fmt.fmt.pix.colorspace);
    printf(" priv: %d\n", fmt.fmt.pix.priv);
    printf(" raw_date: %s\n", fmt.fmt.raw_data);
    printf("\n");


    // 查询当前视频设备支持的视频格式：request = VIDIOC_ENUM_FMT
    // int ioctl(int fd, int request, struct v4l2_fmtdesc *argp);
    printf("\n");
    struct v4l2_fmtdesc fmtdesc;
    fmtdesc.index=0;
    fmtdesc.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;   //V4L2_BUF_TYPE_VIDEO_CAPTURE V4L2_BUF_TYPE_VIDEO_OUTPUT  V4L2_BUF_TYPE_VIDEO_OVERLAY
    printf("Support format:------------------------------------\n");
    while(ioctl(m_iFd, VIDIOC_ENUM_FMT, &fmtdesc) != -1)
    {
        printf("\t%d.%s\n",fmtdesc.index+1,fmtdesc.description);
        fmtdesc.index++;
    }
    printf("\n");

    return;
}

#ifdef WRITE_FILE
VOID V4L2CameraDriverProvider::Process_image(const VOID* p, Int32 size){
    ALOGD("V4L2CameraDriverProvider::Process_image, size=%d\n", size);
    fwrite(p, size, 1, m_pFp);
    //fflush(m_pFp);
}
#endif

VOID V4L2CameraDriverProvider::Display(VOID* p, Int32 width, Int32 height)
{

    m_pPaint->update(width, height, p);
    m_pPaint->draw();
    m_displaySample->Start();

}

ECode V4L2CameraDriverProvider::Read_frame()
{
    ALOGD("V4L2CameraDriverProvider::Read_frame\n");

    struct v4l2_buffer buf;
    UInt32 i;

    switch (m_eIo){
        case IO_METHOD_READ:
            if(-1 == read(m_iFd, m_pBuffers[0].start, m_pBuffers[0].length)){
                switch (errno){
                    case EAGAIN:
                        return -1;

                    case EIO:
                        /* Could ignore EIO, see spec. */
                        /* fall through */
                    default:
                        ALOGE("read error");
                        return -1;
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

            if(-1 == xioctl(m_iFd, VIDIOC_DQBUF, &buf)){
                switch (errno){
                    case EAGAIN:
                        return -1;

                    case EIO:
                        /* Could ignore EIO, see spec. */
                        /* fall through */

                    default:
                        //errno_exit("VIDIOC_DQBUF");
                        if(m_bIsStreamOff) return 0;

                        ALOGE("VIDIOC_DQBUF error");
                        return -1;
                }
            }

            assert(buf.index < BufferCountReal);

        #ifdef WRITE_FILE
            Process_image(m_pBuffers[buf.index].start, buf.length);
        #endif
            ALOGD("xiaole---debug start Display\n");
            Display(m_pBuffers[buf.index].start, 1280, 720);

            if(-1 == xioctl(m_iFd, VIDIOC_QBUF, &buf)){
                //errno_exit("VIDIOC_QBUF");
                ALOGE("VIDIOC_QBUF error\n");
                return -1;
            }

            break;

        case IO_METHOD_USERPTR:
            CLEAR(buf);

            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_USERPTR;

            if(-1 == xioctl(m_iFd, VIDIOC_DQBUF, &buf)){
                switch (errno){
                    case EAGAIN:
                        return -1;

                    case EIO:
                        /* Could ignore EIO, see spec. */
                        /* fall through */

                    default:
                        if(m_bIsStreamOff) return 0;

                        ALOGE("VIDIOC_DQBUF error");
                        return -1;
                }
            }

            for(i = 0; i < BufferCountReal; ++i){
                if(buf.m.userptr == (unsigned long) m_pBuffers[i].start
                        && buf.length == m_pBuffers[i].length)
                    break;
            }

            assert(i < BufferCountReal);

        #ifdef WRITE_FILE
            Process_image((VOID *)buf.m.userptr, buf.length);
        #endif

            Display(m_pBuffers[buf.index].start, 1280, 720);

            if(-1 == xioctl(m_iFd, VIDIOC_QBUF, &buf)){
                ALOGE("VIDIOC_QBUF error");
                return -1;
            }

            break;
    }

    return NO_ERROR;
}

VOID V4L2CameraDriverProvider::update()
{
    ALOGD("V4L2CameraDriverProvider::update\n");

    if(!m_bEglInitFlag) {
        m_displaySample->Init();
        m_pPaint->init();
        m_bEglInitFlag = TRUE;

    }

    if(!m_bIsStreamOff){
        Read_frame();
    }

    // while (m_bIsContinueGet){

    //     Read_frame();


    //     for(;;){
    //         fd_set fds;
    //         struct timeval tv;
    //         Int32 r;

    //         FD_ZERO(&fds);
    //         FD_SET(m_iFd, &fds);

    //         /* Timeout. */
    //         tv.tv_sec = 2;
    //         tv.tv_usec = 0;

    //         r = select(m_iFd + 1, &fds, NULL, NULL, &tv);

    //         if(-1 == r){
    //             if(EINTR == errno)
    //                 continue;

    //             ALOGE("select");
    //             //return -1;
    //             return;
    //         }

    //         if(0 == r){
    //             ALOGE("select timeout\n");
    //             //return -1;
    //             return;
    //         }

    //         if(Read_frame())
    //             break;

    //         /* EAGAIN - continue select loop. */
    //     }
    // }
}

ECode V4L2CameraDriverProvider::GetCapture()
{
    ALOGD("V4L2CameraDriverProvider::GetCapture, BufferCountReal=%d\n", BufferCountReal);

    UInt32 i;
    enum v4l2_buf_type type;

    switch (m_eIo){
        case IO_METHOD_READ:
            /* Nothing to do. */
            break;

        case IO_METHOD_MMAP:
            for(i = 0; i < BufferCountReal; ++i){
                struct v4l2_buffer buf;
                CLEAR(buf);

                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_MMAP;
                buf.index = i;

                if(-1 == xioctl(m_iFd, VIDIOC_QBUF, &buf)){
                    ALOGE("VIDIOC_QBUF error\n");
                    return -1;
                }
            }

            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

            if(-1 == xioctl(m_iFd, VIDIOC_STREAMON, &type)){
                ALOGE("VIDIOC_STREAMON error\n");
                return -1;
            }

            break;

        case IO_METHOD_USERPTR:
            for(i = 0; i < BufferCountReal; ++i){
                struct v4l2_buffer buf;

                CLEAR(buf);

                buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
                buf.memory = V4L2_MEMORY_USERPTR;
                buf.index = i;
                buf.m.userptr = (unsigned long) m_pBuffers[i].start;
                buf.length = m_pBuffers[i].length;

                if(-1 == xioctl(m_iFd, VIDIOC_QBUF, &buf)){
                    ALOGE("VIDIOC_QBUF error\n");
                    return -1;
                }
            }

            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

            if(-1 == xioctl(m_iFd, VIDIOC_STREAMON, &type)){
                ALOGE("VIDIOC_STREAMON error\n");
                return -1;
            }

            break;
    }

    if(!m_bIsStarted){
        m_bIsStreamOff = FALSE;
        start();
        m_bIsStarted = TRUE;
    }else{
        m_bIsStreamOff = FALSE;
        resume();
    }

    return NO_ERROR;
}

ECode V4L2CameraDriverProvider::StopCapture()
{
    ALOGD("V4L2CameraDriverProvider::StopCapture\n");

    enum v4l2_buf_type type;

    switch (m_eIo){
        case IO_METHOD_READ:
            /* Nothing to do. */
            break;

        case IO_METHOD_MMAP:
        case IO_METHOD_USERPTR:
            type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            m_bIsStreamOff = TRUE;
            pause();
            if(-1 == xioctl(m_iFd, VIDIOC_STREAMOFF, &type)){
                ALOGE("VIDIOC_STREAMOFF error\n");
                return -1;
            }

            break;
    }
    return NO_ERROR;
}

ECode V4L2CameraDriverProvider::CloseDriver()
{
    ALOGD("V4L2CameraDriverProvider::CloseDriver\n");

    // Close the camera handle and free the video info structure
    if(0 == close(m_iFd)){
        ALOGI("close %s success, m_iFd=%d\n", m_strDriverPath.c_str(), m_iFd);
    }else{
        ALOGE("close %s failed, m_iFd=%d\n", m_strDriverPath.c_str(), m_iFd);
    }

    m_iFd = -1;
    m_bIsOpened = FALSE;
    quit();
    m_bIsStarted = FALSE;

#ifdef WRITE_FILE
    fclose(m_pFp);
#endif

    return NO_ERROR;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman