
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

VOID LeftCamera::CloseCamera()
{
    ALOGI("LeftCamera::CloseCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera, LEFTCAMERANAME));
}

Int32 LeftCamera::StartCapture()
{
    ALOGI("LeftCamera::StartCapture!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_StartCapture, LEFTCAMERANAME));
}

Int32 LeftCamera::StopCapture()
{
    ALOGI("LeftCamera::StopCapture!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_StopCapture, LEFTCAMERANAME));
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman