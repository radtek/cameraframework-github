
#include "ADASManager/Camera/CameraDriverProviderFactory.h"
#include "ADASManager/Camera/V4L2CameraDriverProvider.h"
#include "ADASManager/Camera/OtherCameraDriverProvider.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define CAMERA_DEVICE0 "/dev/video0"
#define CAMERA_DEVICE1 "/dev/video1"
#define CAMERA_DEVICE2 "/dev/video2"
#define CAMERA_DEVICE3 "/dev/video3"

//maybe read from EOL
map<string, Enum_TheWayToTalkWithCameraDriver> CameraDriverProviderFactory::m_mapCameraMapProvider =
        {{FRONTCAMERANAME,   eTalkWithCameraDriver_V4L2},
         {RESERVECAMERANAME, eTalkWithCameraDriver_V4L2},
         {LEFTCAMERANAME,    eTalkWithCameraDriver_V4L2},
         {RIGHTCAMERANAME,   eTalkWithCameraDriver_V4L2}};

//maybe read from EOL
map<string, string> CameraDriverProviderFactory::m_mapCameraMapDevicePath =
        {{FRONTCAMERANAME,   CAMERA_DEVICE0},
         {RESERVECAMERANAME, CAMERA_DEVICE0},
         {LEFTCAMERANAME,    CAMERA_DEVICE0},
         {RIGHTCAMERANAME,   CAMERA_DEVICE0}};

CameraDriverProvider* CameraDriverProviderFactory::CreateCameraDriverProvider(const string& cameraName)
{
    ALOGI("CameraDriverProviderFactory cameraName = %s !\n", cameraName.c_str());
    switch(m_mapCameraMapProvider[cameraName]){
        case eTalkWithCameraDriver_V4L2 :
            ALOGI("cameraName : %s, choose provider : id = %d !\n", cameraName.c_str(), eTalkWithCameraDriver_V4L2);
            return new V4L2CameraDriverProvider(cameraName, IO_METHOD_MMAP);
        case eTalkWithCameraDriver_OTHERS :
            ALOGE("cameraName : %s, choose provider : id = %d do not implement !\n", cameraName.c_str(), eTalkWithCameraDriver_OTHERS);
            return new OtherCameraDriverProvider(cameraName);
        default :
            ALOGE("cameraName : %s, choose provider : id unknow !\n", cameraName.c_str());
            return nullptr;
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman