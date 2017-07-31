
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
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_OpenCamera, RESERVECAMERANAME));
}

VOID ReserveCamera::CloseCamera(const BOOLEAN isReal)
{
    ALOGI("ReserveCamera::CloseCamera(%s)!\n", (isReal ? "TRUE" : "FALSE"));
    if(isReal) {
        m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera_DriverTrue, RESERVECAMERANAME));
    } else {
        m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera_DriverFalse, RESERVECAMERANAME));
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman