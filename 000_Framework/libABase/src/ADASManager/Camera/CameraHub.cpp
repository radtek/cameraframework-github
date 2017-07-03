
#include "ADASManager/Camera/CameraHub.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

// VOID CameraHub::DispatchMessage(shared_ptr<MessageForQueue> m)
// {
//     for (auto it = m_CamerasMap.begin(); it != m_CamerasMap.end(); ++it) {
//         std::cout << "CameraHub::DispatchMessage to " << it->first << endl;
//         it->second->m_pStateMachine->SendMessage(m);
//     }
// }

Camera* CameraHub::SubscribeToFrontCamera(Observer* observer)
{
    if(nullptr != m_pFrontCamera) {
        m_pFrontCamera->Attach(observer);
    } else {
        ALOGE("m_pFrontCamera == nullptr !!!! \n");
    }
    return m_pFrontCamera;
}

Camera* CameraHub::SubscribeToReserveCamera(Observer* observer)
{
    if(nullptr != m_pReserveCamera) {
        m_pReserveCamera->Attach(observer);
    } else {
        ALOGE("m_pReserveCamera == nullptr !!!! \n");
    }
    return m_pReserveCamera;
}

Camera* CameraHub::SubscribeToLeftCamera(Observer* observer)
{
    if(nullptr != m_pLeftCamera) {
        m_pLeftCamera->Attach(observer);
    } else {
        ALOGE("m_pLeftCamera == nullptr !!!! \n");
    }
    return m_pLeftCamera;
}

Camera* CameraHub::SubscribeToRightCamera(Observer* observer)
{
    if(nullptr != m_pRightCamera) {
        m_pRightCamera->Attach(observer);
    } else {
        ALOGE("m_pRightCamera == nullptr !!!! \n");
    }
    return m_pRightCamera;
}

VOID CameraHub::CancelSubscribeToFrontCamera(Observer* observer)
{
    if(nullptr != m_pFrontCamera) {
        m_pFrontCamera->Detach(observer);
    } else {
        ALOGE("m_pFrontCamera == nullptr !!!! \n");
    }
}

VOID CameraHub::CancelSubscribeToReserveCamera(Observer* observer)
{
    if(nullptr != m_pReserveCamera) {
        m_pReserveCamera->Detach(observer);
    } else {
        ALOGE("m_pReserveCamera == nullptr !!!! \n");
    }
}

VOID CameraHub::CancelSubscribeToLeftCamera(Observer* observer)
{
    if(nullptr != m_pLeftCamera) {
        m_pLeftCamera->Detach(observer);
    } else {
        ALOGE("m_pLeftCamera == nullptr !!!! \n");
    }
}

VOID CameraHub::CancelSubscribeToRightCamera(Observer* observer)
{
    if(nullptr != m_pRightCamera) {
        m_pRightCamera->Detach(observer);
    } else {
        ALOGE("m_pRightCamera == nullptr !!!! \n");
    }
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harman