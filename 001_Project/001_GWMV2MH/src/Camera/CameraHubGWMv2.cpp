
#include "Camera/CameraHubGWMv2.h"
#include "Camera/CameraStateMachineGWMv2.h"
#include "ADASManager/Camera/FrontCamera.h"
#include "ADASManager/Camera/ReserveCamera.h"
#include "ADASManager/Camera/LeftCamera.h"
#include "ADASManager/Camera/RightCamera.h"
#include "ADASManager/Camera/V4L2CameraDriverProvider.h"

#include <iostream>

using Harman::Adas::AFramework::ABase::ADASManager::FrontCamera;
using Harman::Adas::AFramework::ABase::ADASManager::ReserveCamera;
using Harman::Adas::AFramework::ABase::ADASManager::LeftCamera;
using Harman::Adas::AFramework::ABase::ADASManager::RightCamera;
using Harman::Adas::AFramework::ABase::ADASManager::V4L2CameraDriverProviderFactory;

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
    ALOGD("cameraCreatFlag = %d\n", cameraCreatFlag);
    if(0x01 == (cameraCreatFlag & 0x01)) {
        // obj:V4L2CameraDriverProviderFactory delete in ~CameraStateMachineGWMv2()
        // obj:CameraStateMachineGWMv2 delete in ~Camera()
        m_pRightCamera = new RightCamera(RIGHTCAMERANAME, new CameraStateMachineGWMv2(RIGHTCAMERANAME, new V4L2CameraDriverProviderFactory()));
        ALOGI("create camera : RightCamera success !!!\n");
    }
    cameraCreatFlag = cameraCreatFlag >> 1;

    if(0x01 == (cameraCreatFlag & 0x01)) {
        // obj:V4L2CameraDriverProviderFactory delete in ~CameraStateMachineGWMv2()
        // obj:CameraStateMachineGWMv2 delete in ~Camera()
        m_pLeftCamera = new LeftCamera(LEFTCAMERANAME, new CameraStateMachineGWMv2(LEFTCAMERANAME, new V4L2CameraDriverProviderFactory()));
        ALOGI("create camera : LeftCamera success !!!\n");
    }
    cameraCreatFlag = cameraCreatFlag >> 1;

    if(0x01 == (cameraCreatFlag & 0x01)) {
        // obj:V4L2CameraDriverProviderFactory delete in ~CameraStateMachineGWMv2()
        // obj:CameraStateMachineGWMv2 delete in ~Camera()
        m_pReserveCamera = new ReserveCamera(RESERVECAMERANAME, new CameraStateMachineGWMv2(RESERVECAMERANAME, new V4L2CameraDriverProviderFactory()));
        ALOGI("create camera : ReserveCamera success !!!\n");
    }
    cameraCreatFlag = cameraCreatFlag >> 1;

    if(0x01 == (cameraCreatFlag & 0x01)) {
        // obj:V4L2CameraDriverProviderFactory delete in ~CameraStateMachineGWMv2()
        // obj:CameraStateMachineGWMv2 delete in ~Camera()
        m_pFrontCamera = new FrontCamera(FRONTCAMERANAME, new CameraStateMachineGWMv2(FRONTCAMERANAME, new V4L2CameraDriverProviderFactory()));
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