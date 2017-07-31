
#include "ADASManager/Camera/FrontCamera.h"
#include "MessageForQueue.h"

#include <string>

using Harman::Adas::AFramework::AFoundation::MessageForQueue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

VOID FrontCamera::OpenCamera()
{
    ALOGI("FrontCamera::OpenCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_OpenCamera, FRONTCAMERANAME));
}

VOID FrontCamera::CloseCamera(const BOOLEAN isReal)
{
    ALOGI("FrontCamera::CloseCamera(%s)!\n", (isReal ? "TRUE" : "FALSE"));
    if(isReal) {
        m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera_DriverTrue, FRONTCAMERANAME));
    } else {
        m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera_DriverFalse, FRONTCAMERANAME));
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman