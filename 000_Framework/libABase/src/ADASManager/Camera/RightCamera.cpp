
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

VOID RightCamera::CloseCamera()
{
    ALOGI("RightCamera::CloseCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera, RIGHTCAMERANAME));
}

Int32 RightCamera::StartCapture()
{
    ALOGI("RightCamera::StartCapture!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_StartCapture, RIGHTCAMERANAME));
}

Int32 RightCamera::StopCapture()
{
    ALOGI("RightCamera::StopCapture!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_StopCapture, RIGHTCAMERANAME));
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman