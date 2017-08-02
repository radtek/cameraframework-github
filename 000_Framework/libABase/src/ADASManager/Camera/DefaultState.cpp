
#include "ADASManager/Camera/DefaultState.h"
#include "ADASManager/Camera/CameraStateMachine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

DefaultState::~DefaultState()
{}

VOID DefaultState::Enter() const
{
    ALOGI("Enter state : %s !\n", GetStateName().c_str());
}

VOID DefaultState::Exit() const
{
    ALOGI("Exit state : %s !\n", GetStateName().c_str());
}

BOOLEAN DefaultState::ProcessMessage(UInt32 uiType, UInt32 uiID, const string& pData) const
{
    ALOGI("ProcessMessage : message id = %d !\n", uiID);

    switch(uiType)
    {
        case 1 :
            break;
        case 2 :
            break;
        default:
            break;
    }
    return TRUE;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman