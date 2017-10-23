
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__

#include "MessageForQueue.h"
#include "CameraEventDefine.h"
#include "AFoundation.h"

using namespace Harman::Adas::AFramework::AFoundation;

using namespace std;

using Harman::Adas::AFramework::AFoundation::MessageForQueue;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

struct CameraMessageInternal : public MessageForQueue
{
public:
    CameraMessageInternal(Enum_CameraStateTriggerEvent_Internal event)
        : MessageForQueue(0, 0, nullptr)
        , m_uiEvent(event)
    {}

public:
    UInt32 Enum_CameraStateTriggerEvent_Internal m_uiEvent;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__
