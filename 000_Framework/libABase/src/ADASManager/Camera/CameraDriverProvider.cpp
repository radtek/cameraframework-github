
#include "ADASManager/Camera/CameraDriverProvider.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

#define CAMERA_DEVICE0 "/dev/video32"
#define CAMERA_DEVICE1 "/dev/video1"
#define CAMERA_DEVICE2 "/dev/video2"
#define CAMERA_DEVICE3 "/dev/video3"

//maybe read from EOL
map<string, string> CameraDriverProvider::m_mapCameraMapDevicePath =
        {{FRONTCAMERANAME,   CAMERA_DEVICE0},
         {RESERVECAMERANAME, CAMERA_DEVICE0},
         {LEFTCAMERANAME,    CAMERA_DEVICE0},
         {RIGHTCAMERANAME,   CAMERA_DEVICE0}};

Int32 CameraDriverProvider::OpenCamera()
{
    if(!m_bIsOpened && (-1 == OpenDriver()) ){
        ALOGE("CameraDriverProvider : OpenDriver failed !!! \n");
        return -1;
    }

    if(!m_bHasInit && (-1 == InitDevice()) ){
        ALOGE("CameraDriverProvider : InitDevice failed !!! \n");
        return -1;
    }

#ifdef DEBUG
    ShowInfo();
#endif

    return 0;
}

Int32 CameraDriverProvider::CloseCamera()
{
    UninitDevice();
    CloseDriver();

    return 0;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman