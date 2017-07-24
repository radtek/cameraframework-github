
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
    ALOGI("RightCamera::OpenCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_OpenCamera, RIGHTCAMERANAME));
}

VOID RightCamera::CloseCamera(const BOOLEAN isReal)
{
    ALOGI("RightCamera::CloseCamera(%s)!\n", (isReal ? "TRUE" : "FALSE"));
    if(isReal) {
        m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera_DriverTrue, RIGHTCAMERANAME));
    } else {
        m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera_DriverFalse, RIGHTCAMERANAME));
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman