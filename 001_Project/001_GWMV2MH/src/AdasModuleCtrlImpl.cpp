
#include "AdasModuleCtrlImpl.h"
#include "Rvc/RvcStubImpl.h"
#include "Rvc/RvcMsgQDefine.h"
#include "Pas/PasStubImpl.h"
#include "ADASManager/Camera/CameraHub.h"
#include "Camera/CameraHubGWMv2.h"

using Harman::Adas::AProject::GWMV2MH::Camera::CameraHubGWMv2;

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

AdasModuleCtrlImpl* AdasModuleCtrlImpl::m_pInstance = NULL;

AdasModuleCtrlImpl* AdasModuleCtrlImpl::getInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new AdasModuleCtrlImpl();
    }
    return m_pInstance;
}

VOID AdasModuleCtrlImpl::deInstance()
{
    if(m_pInstance != NULL)
    {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

AdasModuleCtrlImpl::AdasModuleCtrlImpl()
{
}

AdasModuleCtrlImpl::~AdasModuleCtrlImpl()
{
}

a_status AdasModuleCtrlImpl::CreateModules(string moduleTab[], BYTE cameraFlag)
{
    CameraHub* camerahub = CameraHubGWMv2::GetInstanceC11(cameraFlag);

    for(int index=0; moduleTab[index] != STRING_NULL; ++index)
    {
        if(moduleTab[index] == ADAS_MODULE_RVC) {
            m_mModuleMap.insert(makePair((UInt32)eModuleType_RVC, static_cast<ModuleBase*>(new RvcStubImpl(camerahub))));
            ALOGI("CreateModules [%s]\n", moduleTab[index].c_str());
        }else if(moduleTab[index] == ADAS_MODULE_PAS) {
            m_mModuleMap.insert(makePair((UInt32)eModuleType_PAS, static_cast<ModuleBase*>(new PasStubImpl(camerahub))));
            ALOGI("CreateModules [%s]\n", moduleTab[index].c_str());
        }else if(moduleTab[index] == ADAS_MODULE_AVM) {
            ALOGE("error module name ADAS_MODULE_AVM, NOT IMPLEMENT\n");
        }else if(moduleTab[index] == ADAS_MODULE_APA) {
            ALOGE("error module name ADAS_MODULE_APA, NOT IMPLEMENT\n");
        }else if(moduleTab[index] == ADAS_MODULE_SVC) {
            ALOGE("error module name ADAS_MODULE_SVC, NOT IMPLEMENT\n");
        }else if(moduleTab[index]  == ADAS_MODULE_COMMON) {
            ALOGE("error module name ADAS_MODULE_COMMON\n");
        }else{
            ALOGE("error module name\n");
        }
    }
    return a_status(0);
}

a_status AdasModuleCtrlImpl::ModuleInit()
{
    ALOGD("ModuleInit\n");
    initialize();
    return a_status(0);
}

} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman