
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_FRONTCAMERA_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_FRONTCAMERA_H__

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

class FrontCamera : public Camera
{
public:
    FrontCamera(const string& name, StateMachine* sm)
        : Camera(name, sm)
    {
        sm->SetOwner(this);
    }

    VOID OpenCamera() override;

    VOID CloseCamera() override;

    Int32 StartCapture() override;

    Int32 StopCapture() override;

    ~FrontCamera() {}
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_FRONTCAMERA_H__
