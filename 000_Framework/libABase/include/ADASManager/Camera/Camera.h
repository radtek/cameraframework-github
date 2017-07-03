
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__

#include "Subject.h"
#include "State.h"
#include "StateMachine.h"
#include "CameraEventDefine.h"

#include <set>

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

    virtual VOID CloseCamera() = 0;

protected:
    Camera(const string& name, StateMachine* sm)
        : Subject(name)
        , m_pStateMachine(sm)
    {}

public:
    StateMachine* m_pStateMachine = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERA_H__