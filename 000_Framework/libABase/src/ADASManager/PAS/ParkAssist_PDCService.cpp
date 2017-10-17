
#include "PAS/ParkAssist_PDCService.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace ABase {
namespace ADASManager {

CPDCService::CPDCService(const std::string& strName, CMessageQueue* pMsgQueue)
    : CMQRunnableService(strName, pMsgQueue)
{
}

void CPDCService::beforeHandleMsgQueue()
{
}

void CPDCService::afterHandleMsgQueue()
{
}

int CPDCService::iPDCInit()
{
    ALOGD(" PDCService::iPDCInit() \n");
    return 0;
}

int CPDCService::iPDCStart()
{
    ALOGD(" PDCService::iPDCStart() \n");
    return 0;
}

int CPDCService::iPDCPause()
{
    ALOGD(" PDCService::iPDCPause() \n");
    return 0;
}

int CPDCService::PDCResume()
{
    ALOGD(" PDCService::PDCResume() \n");
    resume();
    return 0;
}

int CPDCService::PDCStop()
{
    ALOGD(" PDCService::PDCStop() \n");
    pause();
    return 0;
}

int CPDCService::PDCExit()
{
    ALOGD(" PDCService::PDCExit() \n");
    resume();
    return 0;
}

bool CPDCService::initialize()
{
    return false;
}

bool CPDCService::unitialize()
{
    return false;
}

} // namespace ADASManager
} // namespace ABase
} // namespace AFramework
} // namespace Adas
} // namespace Harmane