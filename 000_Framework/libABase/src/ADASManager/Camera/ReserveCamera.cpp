
#include "ADASManager/Camera/ReserveCamera.h"
#include "MessageForQueue.h"

#include <string>

using Harman::Adas::AFramework::AFoundation::MessageForQueue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

VOID ReserveCamera::OpenCamera()
{
    ALOGI("ReserveCamera::OpenCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_OpenCamera, "ReserveCamera"));
}

VOID ReserveCamera::CloseCamera()
{
    ALOGI("ReserveCamera::CloseCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera, "ReserveCamera"));
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman