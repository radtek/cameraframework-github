
#ifndef __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_MESSAGEJUSTFORQUEUEUSE_H__
#define __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_MESSAGEJUSTFORQUEUEUSE_H__

#include "TypeDefine.h"

namespace Harman {
namespace Adas {
namespace AFramework {
namespace AFoundation {

class MessageForQueue
{
public:
    MessageForQueue(UInt32 uiType, UInt32 uiID, const string& pData)
        : m_uiSerialNumber(0)
        , m_uiModuleType(uiType)
        , m_uiMeaasgeID(uiID)
        , m_strArgs(pData)
    {}

    MessageForQueue()
        : m_uiSerialNumber(0)
        , m_uiModuleType(0)
        , m_uiMeaasgeID(0)
        , m_strArgs(nullptr)
    {}

public:
    UInt32 m_uiSerialNumber;
    UInt32 m_uiModuleType;   // moduleID
    UInt32 m_uiMeaasgeID;    // messageID
    const string m_strArgs;  // messageArgs
};

} // namespace AFoundation
} // namespace AFramework
} // namespace Adas
} // namespace Harman

#endif // __HARMAN_ADAS_AFRAMEWORK_AFOUNDATION_MESSAGEJUSTFORQUEUEUSE_H__