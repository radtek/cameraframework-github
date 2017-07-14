
#include "ADASManager/Camera/CameraDriverProvider.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

int CameraDriverProvider::OpenCamera()
{
    if(!IsOpen()){
        OpenDriver();
    }

    SetParam();

    AllocMemory();

    GetCapture();

    return 0;
}

int CameraDriverProvider::CloseCamera()
{
    if(IsOpen()){
        CloseDriver();
    }

    return 0;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman