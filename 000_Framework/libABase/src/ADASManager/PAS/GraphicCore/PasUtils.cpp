
#include "ADASManager/PAS/GraphicCore/PasUtils.h"
#include "ADASManager/PAS/GraphicCore/lodepng.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

BYTE* const PasUtils::LodePNGImage(const string& filename, /* out */ UInt32* const width, /* out */ UInt32* const height, BOOLEAN isCalculateValidErea, VALIDEREA* erea)
{
    ASSERT(width != nullptr);
    ASSERT(height != nullptr);
    if(isCalculateValidErea) {
        ASSERT(erea != nullptr);
    }

    UInt32 l_width = *width = 0;
    UInt32 l_height = *height = 0;
    if(isCalculateValidErea) {
        (*erea).beginIndex = 0;
        (*erea).endIndex = 0;
    }

    std::vector<BYTE> image;
    if(lodepng::decode(/* out */image, /* out */l_width, /* out */l_height, filename, LCT_RGBA, 8) != 0){
        ALOGE(" open file : %s fail\n", filename.c_str());
        return nullptr;
    }
    *width = l_width;
    *height = l_height;
    if(isCalculateValidErea) {
        (*erea).beginIndex = l_height*l_width*4;
    }

    ALOGD(" filename : %s, l_width = %u, l_height = %u image.size() = %d\n", filename.c_str(), l_width, l_height, image.size());

    if(!image.empty()){
        BYTE* buffer = (BYTE*)malloc(l_width * l_height * 4);   // free by class : ColorBlock
        if(nullptr == buffer) {
            ALOGE(" malloc failed !\n");
            return nullptr;
        }

        memcpy(buffer, &image[0], image.size()*sizeof(BYTE)); //dangerous but safe

        if(isCalculateValidErea){
            for(Int32 index = 0; index < l_width * l_height * 4;)
            {
                if(buffer[index+3]!=0)
                {
                    (*erea).beginIndex = index;
                    break;
                }
                index += 4;
            }
            for(Int32 index = l_width * l_height * 4 - 1; index > 0;)
            {
                if(buffer[index]!=0)
                {
                    (*erea).endIndex = index - 3;
                    break;
                }
                index -= 4;
            }
            ALOGD("      ValidErea : %s,  beginIndex = %u, endIndex = %u\n", filename.c_str(), (*erea).beginIndex, (*erea).endIndex);
        }

        return buffer;
    }else{
        return nullptr;
    }

    return nullptr;
}

Int32 PasUtils::SaveAsBmp(const CHAR* const path, const VOID* const databuffer, IMAGEINFO& imageinfo)
{
    ASSERT(path != nullptr);
    ASSERT(databuffer != nullptr);

    #define HEAD_MAX_SIZE 54
    #define bfSize  2  //4
    #define Width  18  //4
    #define Height 22  //4
    #define BitCount 28  //2
    #define SizeImage 34 //4

    static BYTE head[HEAD_MAX_SIZE] = {
        0x42,0x4d, //2 wbfType
        0x30,0x0C,0x01,0, //4 dwbfSize
        0,0, //2 wbfReserved1
        0,0, //2 wbfReserved2
        0x36,0,0,0,//4 dwbfOffBits

        0x28,0,0,0, //4 dwbiSize
        0x00,0,0,0, //4 lbiWidth
        0x00,0,0,0, //4 lbiHeight
        0x01,0,//2 wbiPlanes
        0x20,0,//2 wbiBitCount
        0,0,0,0, //4 dwbiCompression
        0x00,0x00,0x00,0x00, //4 dwbiSizeImage
        0x00,0x00,0x00,0x00, //4 lbiXPelsPerMeter
        0x00,0x00,0x00,0x00, //4  lbiYpelsPerMeter
        0,0,0,0,//4 dwbiClrUsed
        0,0,0,0//4 dwbiClrImportant
    };

    head[bfSize] = HEAD_MAX_SIZE + imageinfo.image_size;
    head[Width] = imageinfo.width;
    head[Height] = imageinfo.height;
    head[SizeImage] = imageinfo.image_size;
    head[BitCount] = 0x20;

    FILE* stream = fopen(path, "wb");
    if(stream == nullptr) {
        ALOGE("open file : %s failed ! \n", path);
        return -1;
    }

    if(-1 == fwrite(head,  HEAD_MAX_SIZE, 1, stream)){
        ALOGE("fwrite file : %s failed ! \n", path);
        if(-1 == fclose(stream)){
            ALOGE("fclose file : %s failed ! \n", path);
            return -1;
        }
        return -1;
    }
    if(-1 == fwrite(databuffer,  imageinfo.image_size, 1, stream)){
        ALOGE("fwrite file : %s failed ! \n", path);
        if(-1 == fclose(stream)){
            ALOGE("fclose file : %s failed ! \n", path);
            return -1;
        }
        return -1;
    }

    if(-1 == fclose(stream)){
        ALOGE("fclose file : %s failed ! \n", path);
        return -1;
    }

    #undef HEAD_MAX_SIZE
    #undef bfSize
    #undef Width
    #undef Height
    #undef BitCount
    #undef SizeImage

    return 0;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman