
#include "ADASManager/Camera/CameraDriverProviderFactory.h"
#include "ADASManager/Camera/V4L2CameraDriverProvider.h"

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
    Enum_TheWayToTalkWithCameraDriver way = m_mapCameraMapProvider[cameraName];

    ALOGI("cameraName : %s, choose provider : id = %d !\n", cameraName.c_str(), way);

    if(way == eTalkWithCameraDriver_V4L2){
        return new V4L2CameraDriverProvider(cameraName);
    } else if (way == eTalkWithCameraDriver_OTHERS){
        //return new OtherCameraDriverProvider(cameraName);
    } else {
        return nullptr;
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman