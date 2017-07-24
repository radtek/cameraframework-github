
#include "ADASManager/Camera/CameraDriverProvider.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

Int32 CameraDriverProvider::OpenCamera()
{
    if(!m_bIsOpened && (-1 == OpenDriver()) ){
        ALOGE("CameraDriverProvider : OpenDriver failed !!! \n");
        return -1;
    }

#ifdef DEBUG
    ShowInfo();
#endif

    if(!m_bHasInit && (-1 == InitDevice()) ){
        ALOGE("CameraDriverProvider : InitDevice failed !!! \n");
        return -1;
    }

    if (m_bIsOpened && m_bHasInit) {
        GetCapture();
    }

    return 0;
}

Int32 CameraDriverProvider::CloseCamera(const BOOLEAN isReal)
{
    if (isReal) {
        StopCapture();
        UninitDevice();
        CloseDriver();
    } else {
        StopCapture();
    }

    return 0;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman