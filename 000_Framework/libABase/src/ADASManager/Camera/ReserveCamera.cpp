
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

VOID ReserveCamera::CloseCamera()
{
    ALOGI("ReserveCamera::CloseCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera, RESERVECAMERANAME));
}

Int32 ReserveCamera::StartCapture()
{
    ALOGI("ReserveCamera::StartCapture!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_StartCapture, RESERVECAMERANAME));
}

Int32 ReserveCamera::StopCapture()
{
    ALOGI("ReserveCamera::StopCapture!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_StopCapture, RESERVECAMERANAME));
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman