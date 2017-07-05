
#include "ADASManager/Camera/RightCamera.h"
#include "MessageForQueue.h"

#include <string>

using Harman::Adas::AFramework::AFoundation::MessageForQueue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

VOID RightCamera::OpenCamera()
{
    ALOGI("OpenCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_OpenCamera, "RightCamera"));
}

VOID RightCamera::CloseCamera()
{
    ALOGI("CloseCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera, "RightCamera"));
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman