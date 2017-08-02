
#include "ADASManager/Camera/OtherCameraDriverProvider.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

OtherCameraDriverProvider::OtherCameraDriverProvider(const string& cameraName)
    : CameraDriverProvider(cameraName)
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
}

OtherCameraDriverProvider::~OtherCameraDriverProvider()
{
}

Int32 OtherCameraDriverProvider::OpenDriver()
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
    return 0;
}

Int32 OtherCameraDriverProvider::CloseDriver()
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
    return 0;
}

VOID OtherCameraDriverProvider::ShowInfo()
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
    return;
}

Int32 OtherCameraDriverProvider::GetCapture()
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
    return 0;
}

Int32 OtherCameraDriverProvider::StopCapture()
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
    return 0;
}

Int32 OtherCameraDriverProvider::InitDevice()
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
    return 0;
}

Int32 OtherCameraDriverProvider::UninitDevice()
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
    return 0;
}

VOID OtherCameraDriverProvider::update()
{
    ALOGE("Not Implement, just a template for extending other way to talk with camera driver! \n");
    return;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman