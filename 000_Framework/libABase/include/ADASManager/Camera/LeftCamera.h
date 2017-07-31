
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_LETFCAMERA_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_LETFCAMERA_H__

#include "Camera.h"
#include "StateMachine.h"

using namespace std;

using Harman::Adas::AFramework::AFoundation::StateMachine;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class LeftCamera : public Camera
{
public:
    LeftCamera(const string& name, StateMachine* sm)
        : Camera(name, sm)
    {
        sm->SetOwner(this);
    }

    VOID OpenCamera() override;

    // if isReal == FALSE : CloseCamera just CALL StopCapture, do not CALL Uninit_device() && close(fd)
    // if isReal == TRUE  : CloseCamera will CALL StopCapture AND Uninit_device() AND close(fd)
    VOID CloseCamera(const BOOLEAN isReal) override;

    ~LeftCamera() {}
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_LETFCAMERA_H__
