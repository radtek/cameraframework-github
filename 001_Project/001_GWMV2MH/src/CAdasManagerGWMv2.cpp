
#include "CAdasManagerGWMv2.h"
#include "AdasModuleCtrlImpl.h"
#include "CMessageQueue.h"
#include "CMessageHandler.h"
#include "Rvc/RvcMsgQDefine.h"
#include "ADASManager/Camera/CameraEventDefine.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

#if defined(_LOW_LEVEL_VEHICLE_)
    string moduleTab[] = {
        ADAS_MODULE_RVC,
        ADAS_MODULE_PAS,
        //ADAS_MODULE_APA,
        STRING_NULL
    };
#elif defined(_HIGH_LEVEL_VEHICLE_)
    string moduleTab[] = {
        //ADAS_MODULE_AVM,
        ADAS_MODULE_PAS,
        //ADAS_MODULE_APA,
        STRING_NULL
    };
#endif

CAdasManagerGWMv2* CAdasManagerGWMv2::s_pInstance = NULL;

CAdasManagerGWMv2* CAdasManagerGWMv2::getInstance()
{
    if( s_pInstance == NULL)
    {
        s_pInstance = new CAdasManagerGWMv2();
    }

    return s_pInstance;
}

VOID CAdasManagerGWMv2::deleteInstance()
{
    if( s_pInstance != NULL )
    {
        delete s_pInstance;
        s_pInstance = NULL;
    }
}

CAdasManagerGWMv2::CAdasManagerGWMv2()
    : CAdasManager(string("adas"), new CMessageQueue(string("adas"), 300, (CMessageHandler*)(AdasModuleCtrlImpl::getInstance())))
{
    ALOGD("CAdasManagerGWMv2\n");
    REGCB_CCR(makeFunctor(this, &CAdasManagerGWMv2::vCaseCallbackGWMv2));
}

CAdasManagerGWMv2::~CAdasManagerGWMv2()
{
}

VOID CAdasManagerGWMv2::init()
{
    ALOGD("CAdasManagerGWMv2 init\n");

    BYTE cameraFlag = 0;
    for(auto mode : moduleTab)
    {
        if(mode == ADAS_MODULE_RVC) {
            cameraFlag |= s_RVC_Map_Cameras;
        }else if(mode == ADAS_MODULE_AVM) {
            cameraFlag |= s_AVM_Map_Cameras;
        }else if(mode == ADAS_MODULE_PAS) {
            cameraFlag |= s_PAS_Map_Cameras;
        }else if(mode == ADAS_MODULE_APA) {
            cameraFlag |= s_APA_Map_Cameras;
        }else if(mode == ADAS_MODULE_SVC) {
            cameraFlag |= s_SVC_Map_Cameras;
        }else if(mode  == ADAS_MODULE_COMMON) {
            ALOGE("error module name ADAS_MODULE_COMMON\n");
        }else{
            ALOGE("error module name\n");
        }
    }
    AdasModuleCtrlImpl::getInstance()->CreateModules(moduleTab, cameraFlag);
    AdasModuleCtrlImpl::getInstance()->ModuleInit();
}

VOID CAdasManagerGWMv2::vCaseCallbackGWMv2(const string& strMockIPC)
{
	ALOGD("CAdasManagerGWMv2 received Mock IPC :%s  \n", strMockIPC.c_str());
	vCaseCallback(strMockIPC.c_str());
}

} // namespace GWMV2MH
} // namespace AProject
} // namespace Adas
} // namespace Harman