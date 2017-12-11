
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASUTILS_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASUTILS_H__

#include <iostream>

#include "TypeDefine.h"
#include "TraceMacros.h"

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define  IMAGEINFO_MAX_SIZE 472

typedef struct imageInformation
{
    Int32 image_size;
    Int32 width;
    Int32 height;
    Int32 crop_X;
    Int32 crop_Y;
    Int32 crop_width;
    Int32 crop_height;
    Int32 screen_X;
    Int32 screen_Y;
    Int32 movie;
    CHAR reserved[IMAGEINFO_MAX_SIZE];
} IMAGEINFO;

typedef struct validArea
{
    UInt32 beginX;
    UInt32 beginY;
    UInt32 endX;
    UInt32 endY;
} VALIDEREA;

class PasUtils
{
public:
    static BYTE* const LodePNGImage(const string& filename, /* out */ UInt32* const width, /* out */ UInt32* const height, BOOLEAN isCalculateValidErea, VALIDEREA* erea);

    static Int32 SaveAsBmp(const CHAR* const path, const VOID* const databuffer, IMAGEINFO& imageinfo);
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane

#endif // __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_PASUTILS_H__