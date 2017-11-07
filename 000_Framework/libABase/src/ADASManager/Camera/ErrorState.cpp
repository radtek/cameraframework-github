#include "ADASManager/Camera/ErrorState.h"
#include "ADASManager/Camera/CameraStateMachine.h"
#include <iostream>

using namespace Harman::Adas::AFramework::AFoundation;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

VOID ErrorState::Enter() const
{
    ALOGI("Enter state : %s !\n", GetStateName().c_str());
}

VOID ErrorState::Exit() const
{
    ALOGI("Exit state : %s !\n", GetStateName().c_str());
}

BOOLEAN ErrorState::ProcessMessage(UInt32 uiType, UInt32 uiMessageID, const string& pData) const
{


}

}
}
}
}
}