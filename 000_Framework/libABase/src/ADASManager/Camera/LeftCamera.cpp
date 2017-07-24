
#include "ADASManager/Camera/LeftCamera.h"
#include "MessageForQueue.h"

#include <string>

using Harman::Adas::AFramework::AFoundation::MessageForQueue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

VOID LeftCamera::OpenCamera()
{
    ALOGI("LeftCamera::OpenCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_OpenCamera, LEFTCAMERANAME));
}

VOID LeftCamera::CloseCamera(const BOOLEAN isReal)
{
    ALOGI("LeftCamera::CloseCamera(%s)!\n", (isReal ? "TRUE" : "FALSE"));
    if(isReal) {
        m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera_DriverTrue, LEFTCAMERANAME));
    } else {
        m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera_DriverFalse, LEFTCAMERANAME));
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman