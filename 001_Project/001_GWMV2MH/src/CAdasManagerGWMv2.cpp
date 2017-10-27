#include "CAdasManagerGWMv2.h"
#include "CMessageQueue.h"
#include "CMessageHandler.h"
#include "Rvc/RvcMsgQDefine.h"
#include "ADASManager/Camera/CameraEventDefine.h"

namespace Harman {
namespace Adas {
namespace AProject {
namespace GWMV2MH {

string moduleTab[] = {
    ADAS_MODULE_RVC,
    STRING_NULL
};

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
    :CMQRunnableService(string("adas"), new CMessageQueue(string("adas"), 9, (CMessageHandler*)(AdasModuleCtrlImpl::getInstance())))
{
    ALOGD("CAdasManagerGWMv2\n");
}

CAdasManagerGWMv2::~CAdasManagerGWMv2()
{
    ;
}


BOOLEAN CAdasManagerGWMv2::initialize(string sServiceName)
{
    ALOGD("******init ServiceName[%s]********\n", sServiceName.c_str());

    BYTE cameraFlag = 0;
    for(auto mode : moduleTab)
    {
        if(mode == ADAS_MODULE_RVC)
        {
            cameraFlag |= s_RVC_Map_Cameras;
        }
        #if 0
        else if(mode == ADAS_MODULE_SVC)
        {
            cameraFlag |= s_SVC_Map_Cameras;
        }
        else if(mode == ADAS_MODULE_AVM)
        {
            cameraFlag |= s_AVM_Map_Cameras;make 
        }
        else if(mode == ADAS_MODULE_PAS)
        {
            cameraFlag |= s_PAS_Map_Cameras;
        }
        else if(mode == ADAS_MODULE_APA)
        {
            cameraFlag |= s_APA_Map_Cameras;
        }
        else if(moduleTab[index]  == ADAS_MODULE_COMMON)
        {

        }
        #endif
    }

    AdasModuleCtrlImpl::getInstance()->CreateModules(moduleTab, cameraFlag);

    AdasModuleCtrlImpl::getInstance()->ModuleInit();
    return TRUE;
}

VOID CAdasManagerGWMv2::vCaseCallbackGWMv2(const string& strMockIPC)
{

}

}
}
}
}
