
#include "AFoundation.h"
#include "ADASManager/CAdasManager.h"
#include "ADASManager/AdasModuleCtrl.h"
#include "CMessageHandler.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

CAdasManager::CAdasManager(const string& strName, CMessageQueue* pMsgQueue)
: CMQRunnableService(strName, pMsgQueue)
{
    ALOGD("CAdasManager\n");
    PRINT_APP_OS_TYPE;
    LAUNCH_CCR ;
   // REGCB_CCR(makeFunctor(this, &CAdasManager::vCaseCallback));
}

CAdasManager::~CAdasManager()
{
    ;
}

void CAdasManager::vAddModule()
{
   
    SENDTO_CCR("CAdasManager:vAddModule success! \n")  ;
}

void CAdasManager::afterHandleMessageQueue()
{

}

void CAdasManager::beforeHandleMessageQueue()
{

}

void CAdasManager::init()
{

}


}
}
}
}
}
