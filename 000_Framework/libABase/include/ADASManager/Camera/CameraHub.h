
#ifndef __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERAHUB_H__
#define __HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERAHUB_H__

#include "Camera.h"
#include "Observer.h"
#include "Subject.h"
#include "MessageForQueue.h"

#include <memory>
#include <string>

using Harman::Adas::AFramework::AFoundation::Observer;
using Harman::Adas::AFramework::AFoundation::Subject;
using Harman::Adas::AFramework::AFoundation::MessageForQueue;

using namespace std;

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

class CameraHub : public Observer
{
public:
    CameraHub(const string& name)
        : Observer(name)
    {}

    //VOID DispatchMessage(shared_ptr<MessageForQueue> m);

    //other model call
    Camera* SubscribeToFrontCamera(Observer* observer);
    Camera* SubscribeToReserveCamera(Observer* observer);
    Camera* SubscribeToLeftCamera(Observer* observer);
    Camera* SubscribeToRightCamera(Observer* observer);

    //other model call
    VOID CancelSubscribeToFrontCamera(Observer* observer);
    VOID CancelSubscribeToReserveCamera(Observer* observer);
    VOID CancelSubscribeToLeftCamera(Observer* observer);
    VOID CancelSubscribeToRightCamera(Observer* observer);

    ~CameraHub() {}

public:
    map<string, Int32> m_CamerasState;
    map<string, Camera*> m_CamerasMap;

    Camera* m_pFrontCamera = nullptr;
    Camera* m_pReserveCamera = nullptr;
    Camera* m_pLeftCamera = nullptr;
    Camera* m_pRightCamera = nullptr;
};

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif //__HARMAN_ADAS_AFRAMEWORK_ABASE_ADASMANAGER_CAMERA_CAMERAHUB_H__