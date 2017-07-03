
#include "ADASManager/Camera/Camera.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

Enum_VehicleCameraState Camera::GetCameraState()
{
    if(nullptr != m_pStateMachine){
        return (Enum_VehicleCameraState)m_pStateMachine->CurrentStateToInt();
    } else {
        ALOGE("%s do not has a StateMachine !!!!\n", GetSubjectName().c_str());
        return eSVS_Camera_State_Invalid;
    }
    return eSVS_Camera_State_Invalid;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman