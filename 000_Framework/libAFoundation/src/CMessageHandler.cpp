
#ifdef LINUX_OS
#include "../include/CMessageHandler.h"
#else
#include "..\include\CMessageHandler.h"
#endif

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

VOID CMessageHandler::handle(MessageForQueue* pMsg)
{
    UInt32 ucType = pMsg->m_uiModuleType;
    UInt32 uiID =  pMsg->m_uiMeaasgeID;

    _handle(ucType, uiID, pMsg->m_strArgs);
}

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman