
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

VOID FrontCamera::CloseCamera()
{
    ALOGI("FrontCamera::CloseCamera!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_CloseCamera, FRONTCAMERANAME));
}

Int32 FrontCamera::StartCapture()
{
    ALOGI("FrontCamera::StartCapture!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_StartCapture, FRONTCAMERANAME));
}

Int32 FrontCamera::StopCapture()
{
    ALOGI("FrontCamera::StopCapture!\n");
    m_pStateMachine->SendMessage(new MessageForQueue(0 /*not used now*/, eCameraStateTriggerEvent_StopCapture, FRONTCAMERANAME));
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman