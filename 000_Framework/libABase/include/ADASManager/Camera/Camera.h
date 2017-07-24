
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__

#include "Subject.h"
#include "State.h"
#include "StateMachine.h"
#include "CameraEventDefine.h"
//#include "CameraDriverProvider.h"
#include "CameraDriverProviderFactory.h"
#include "CameraStateMachine.h"

using namespace std;

using Harman::Adas::AFramework::AFoundation::Subject;
using Harman::Adas::AFramework::AFoundation::StateMachine;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class Camera : public Subject
{
public:
    ~Camera()
    {
        if(nullptr != m_pStateMachine) {
            delete m_pStateMachine;
            m_pStateMachine = nullptr;
        }
    }

    Enum_VehicleCameraState GetCameraState();

    virtual VOID OpenCamera() = 0;

    // if isReal == FALSE : CloseCamera just CALL StopCapture, do not CALL Uninit_device() && close(fd)       normal   call
    // if isReal == TRUE  : CloseCamera will CALL StopCapture AND Uninit_device() AND close(fd)               poweroff call
    virtual VOID CloseCamera(const BOOLEAN isReal) = 0;

protected:
    Camera(const string& name, StateMachine* sm)
        : Subject(name)
        , m_pStateMachine(sm)
    {
        CameraStateMachine* csm = dynamic_cast<CameraStateMachine*>(m_pStateMachine);
        if (csm != nullptr) {
            ALOGI("Camera : %s SetDriverProvider !!!!\n", name.c_str());
            csm->SetDriverProvider(CameraDriverProviderFactory::CreateCameraDriverProvider(name));
        } else {
            ALOGE("Camera : %s SetDriverProvider failed !!!!\n", name.c_str());
        }
    }

public:
    StateMachine* m_pStateMachine = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__