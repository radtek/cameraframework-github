
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_RIGHTCAMERA_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_RIGHTCAMERA_H__

#include "Camera.h"
#include "StateMachine.h"
#include "AFoundation.h"

using namespace Harman::Adas::AFramework::AFoundation;

using namespace std;

using Harman::Adas::AFramework::AFoundation::StateMachine;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class RightCamera : public Camera
{
public:
    RightCamera(const string& name, StateMachine* sm)
        : Camera(name, sm)
    {
        sm->SetOwner(this);
    }

    VOID OpenCamera() override;

    VOID CloseCamera() override;

    Int32 StartCapture() override;

    Int32 StopCapture() override;

    ~RightCamera() {}
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_RIGHTCAMERA_H__
