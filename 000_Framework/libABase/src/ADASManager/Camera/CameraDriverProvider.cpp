
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

    SetParam();

    AllocMemory();

    GetCapture();

    return 0;
}

Int32 CameraDriverProvider::CloseCamera()
{
    if(m_bIsOpened){
        //StopGetCapture(); ~~~~~~~~~~~~~~~~~~~~~~~~
    }

    return 0;
}

Int32 CameraDriverProvider::PowOffCamera()
{
    if(m_bIsOpened){
        CloseDriver();
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman