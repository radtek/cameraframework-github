
#include "Camera/CameraHubGWMv2.h"
#include "Camera/CameraStateMachineGWMv2.h"
#include "ADASManager/Camera/FrontCamera.h"
#include "ADASManager/Camera/ReserveCamera.h"
#include "ADASManager/Camera/LeftCamera.h"
#include "ADASManager/Camera/RightCamera.h"

#include <iostream>

using Harman::Adas::AFramework::ABase::ADASManager::FrontCamera;
using Harman::Adas::AFramework::ABase::ADASManager::ReserveCamera;
using Harman::Adas::AFramework::ABase::ADASManager::LeftCamera;
using Harman::Adas::AFramework::ABase::ADASManager::RightCamera;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {
namespace Camera {

mutex CameraHubGWMv2::mMutex;

CameraHubGWMv2* CameraHubGWMv2::GetInstanceC98(BYTE cameraCreatFlag)
{
    unique_lock<mutex>lock_msg(mMutex);
    static CameraHubGWMv2 instance{cameraCreatFlag};
    lock_msg.unlock();
    return &instance;
}

CameraHubGWMv2* CameraHubGWMv2::GetInstanceC11(BYTE cameraCreatFlag)
{
    static CameraHubGWMv2 instance{cameraCreatFlag};
    return &instance;
}

CameraHubGWMv2::CameraHubGWMv2(BYTE cameraCreatFlag)
{
    ALOGI("cameraCreatFlag = %d\n", cameraCreatFlag);
    if(0x01 == (cameraCreatFlag & 0x01)) {
        m_pRightCamera = new RightCamera(RIGHTCAMERANAME, new CameraStateMachineGWMv2(RIGHTCAMERANAME)); //CameraStateMachineGWMv2 delete in ~Camera()
        //m_CamerasMap[RIGHTCAMERANAME] = m_pRightCamera;
        ALOGI("create camera : RightCamera success !!!\n");
    }
    cameraCreatFlag = cameraCreatFlag >> 1;

    if(0x01 == (cameraCreatFlag & 0x01)) {
        m_pLeftCamera = new LeftCamera(LEFTCAMERANAME, new CameraStateMachineGWMv2(LEFTCAMERANAME)); //CameraStateMachineGWMv2 delete in ~Camera()
        //m_CamerasMap[LEFTCAMERANAME] = m_pLeftCamera;
        ALOGI("create camera : LeftCamera success !!!\n");
    }
    cameraCreatFlag = cameraCreatFlag >> 1;

    if(0x01 == (cameraCreatFlag & 0x01)) {
        m_pReserveCamera = new ReserveCamera(RESERVECAMERANAME, new CameraStateMachineGWMv2(RESERVECAMERANAME)); //CameraStateMachineGWMv2 delete in ~Camera()
        //m_CamerasMap[RESERVECAMERANAME] = m_pReserveCamera;
        ALOGI("create camera : ReserveCamera success !!!\n");
    }
    cameraCreatFlag = cameraCreatFlag >> 1;

    if(0x01 == (cameraCreatFlag & 0x01)) {
        m_pFrontCamera = new FrontCamera(FRONTCAMERANAME, new CameraStateMachineGWMv2(FRONTCAMERANAME)); //CameraStateMachineGWMv2 delete in ~Camera()
        //m_CamerasMap[FRONTCAMERANAME] = m_pFrontCamera;
        ALOGI("create camera : FrontCamera success !!!\n");
    }
}

CameraHubGWMv2::~CameraHubGWMv2()
{
    //cout << "CameraHubGWMv2::~CameraHubGWMv2()" << endl;
    if(nullptr != m_pFrontCamera) {
        delete m_pFrontCamera;
        m_pFrontCamera = nullptr;
    }
    if(nullptr != m_pReserveCamera) {
        delete m_pReserveCamera;
        m_pReserveCamera = nullptr;
    }
    if(nullptr != m_pLeftCamera) {
        delete m_pLeftCamera;
        m_pLeftCamera = nullptr;
    }
    if(nullptr != m_pRightCamera) {
        delete m_pRightCamera;
        m_pRightCamera = nullptr;
    }
}

} // namespace Camera
} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman